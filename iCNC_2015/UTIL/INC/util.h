#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<string.h>
#include"../../LINK/INC/link.h"


void delByteSpace(char* bytePtr,int size);
void clear(DEC_DATA *decDataPtr);
void passDigit(DEC_DATA *decDataPtr);
char *passFloat(DEC_DATA *decDataPtr);
void passSpace(DEC_DATA *decDataPtr);

#endif