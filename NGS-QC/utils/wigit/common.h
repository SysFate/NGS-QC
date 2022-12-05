/* 
 * File:   common.h
 * Author: blum
 *
 * Created on 14 avril 2015, 17:21
 */

#ifndef COMMON_H
#define	COMMON_H

/* How big is this array? */
#define array_size(a) (sizeof(a)/sizeof((a)[0]))

#define BUFF_SIZE 1024

/* Like chopString, but specialized for white space separators. */
int chop_by_space(char *in, char *outArray[], int outSize);

FILE *try_open(char *path, char *mode);

long tolong(char *string);

char *lower(char *string);

void rtrim(char *str);

void ltrim(char *str);

void trim(char *str);

void strupper(char *string);

/* Returns 1 if two strings same. */
#define equals(a,b) (strcmp(a,b)==0)

/* Chop line by white space. */
#define chop_line(line, words) chop_by_space(line, words, array_size(words))

#endif	/* COMMON_H */

