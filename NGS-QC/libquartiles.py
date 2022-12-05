#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Created on 27/03/15

@author: Matthias Blum
"""

import os
import sqlite3


def get(bg='global'):
    """
    Get the quartiles score for each dispersion of a given background subtraction mode
    :param bg:  "global" for Poisson distribution (only one currently supported)
    :return:
    """
    dbfile = os.path.join(os.path.dirname(__file__), 'db', 'quartiles.db')
    con = sqlite3.connect(dbfile)
    cur = con.cursor()
    cur.execute('SELECT disp, quartile, value, version FROM quartile WHERE bg=? ORDER BY version DESC', (bg,))
    res = cur.fetchall()
    cur.close()
    con.close()

    quartiles = {}
    version = None
    for row in res:
        version = row[3]
        if row[0] not in quartiles:
            quartiles[row[0]] = {row[1]: row[2]}
        else:
            quartiles[row[0]][row[1]] = row[2]

    return quartiles, version