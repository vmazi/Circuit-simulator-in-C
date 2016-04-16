#ifndef FIRST_H_
#define FIRST_H_


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int* datamap;
void createdatamap();
void destroydatamap();
int getindex(char a);
void AND(int a, int b,int*c);
void OR(int a, int b,int*c);
void NOT(int a, int*b);
int* greytobin(int* a,int bits);
int bintodec(int* a,int bits);
int greytodec(int* grey, int bits);
void MUX(int* grey,int bits,int* outsig, int* out);
void DECODER(int* grey,int bits,char *outsig);
void printout( int num, char* outs);

#endif //FIRST_H_
