import json
import math
import MySQLdb
import os
import sys
import tempfile

# python update_ngsqc_dbs.py
# python ngs-qc/libquartiles.py quartiles.json && rm quartiles.json
# python ngs-qc/libtargets targets.txt && rm targets.txt

def update(host, user, passwd, db, outdir=tempfile.gettempdir()):
    if not os.path.isdir(outdir):
        os.makedirs(outdir)

    targets_f = os.path.join(outdir, "targets.txt")
    quartiles_f = os.path.join(outdir, "quartiles.json")

    con = MySQLdb.connect(host=host, user=user, passwd=passwd, db=db)
    cur = con.cursor()
    cur.execute("SELECT SECID, target_molecule_common, organism, TMRS, UMRS, `stampsQC_2.5`, stampsQC_5, stampsQC_10  FROM `ngs_sample`")

    with open(targets_f, "w") as fh:
        for row in cur.fetchall():
            fh.write("\t".join(str(e) for e in row) + "\n")

    versions = {}
    cur.execute("SELECT version FROM version_bgs")
    for row in cur.fetchall():
        v = row[0]
        versions[v] = None

    cur.execute("SELECT version, `qc25_2.5`, `qc50_2.5`, `qc75_2.5`, qc25_5, qc50_5, qc75_5, qc25_10, qc50_10, qc75_10 from quartiles_bgs_history")
    for row in cur.fetchall():
        v = row[0]

        if v in versions:
            versions[v] = {
                2.5: {25: row[1], 50: row[2], 75: row[3]},
                5: {25: row[4], 50: row[5], 75: row[6]},
                10: {25: row[7], 50: row[8], 75: row[9]}
            }

    print versions
    v = [v for v, val in versions.items() if val is None]
    print v
    if len(v) == 1:
        v = v[0]
        cur.execute("SELECT `qc25_2.5`, `qc50_2.5`, `qc75_2.5`, qc25_5, qc50_5, qc75_5, qc25_10, qc50_10, qc75_10 from quartiles_bgs")
        row = cur.fetchone()
        versions[v] = {
            2.5: {25: math.log(row[0], 2), 50: math.log(row[1], 2), 75: math.log(row[2], 2)},
            5: {25: math.log(row[3], 2), 50: math.log(row[4], 2), 75: math.log(row[5], 2)},
            10: {25: math.log(row[6], 2), 50: math.log(row[7], 2), 75: math.log(row[8], 2)}
        }
    else:
        print "Error in versions/quartiles"

    with open(quartiles_f, "w") as fp:
        json.dump(versions, fp, ensure_ascii=True, encoding="utf-8")

    cur.close()
    con.close()

    return targets_f, quartiles_f

if __name__ == '__main__':
    targets_f, quartiles_f = update(host="cholley-pc", user="hglab", passwd="hglab123", db="NGSQC_database")
    print targets_f
    print quartiles_f
