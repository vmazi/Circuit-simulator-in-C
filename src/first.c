#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "first.h"
int* datamap;

void createdatamap(){
  datamap = (int*) calloc(57,sizeof(int));
}

void destroydatamap(){
  free(datamap);
  datamap = NULL;
}

int getindex(char a){
  int index = (int)a;
  index = index-65;
  return index;
}

void AND(int a, int b,int*c){

  *c =  a&&b;

}
void OR(int a, int b,int*c){

  *c =  a||b;

}
void NOT(int a, int*b){

  *b = !a;

}

int* greytobin(int* a,int bits){
  int i;
  int* grey = (int*)malloc(bits * sizeof(int));
  grey[0] = a[0];
  for(i = 1; i<bits;i++){
 
    grey[i]=grey[i-1]^a[i];

  }
  return grey;
}
int bintodec(int* a,int bits){
  int out,i,j;
  j =0;
  out = 0;
  for(i=bits-1;i>-1;i--){
    if(a[j]== 1){
      out = out + (int)pow(2,i);
    }
    j++;
  }
  return out;
}
int greytodec(int* grey, int bits){
  int* bin = greytobin(grey,bits);
  int dec = bintodec(bin,bits);
  free(bin);
  return dec;

}
void MUX(int* grey,int bits,int* outsig, int* out){

 *out = outsig[greytodec(grey,bits)];

}
void DECODER(int* grey,int bits,char *outsig){
  char c;
  c = outsig[greytodec(grey,bits)];
  datamap[getindex(c)] = 1;

}


void printout( int num, char* outs){
  int i;
  for(i=0;i<num;i++){
    printf("%d ",datamap[getindex(outs[i])]);
  }
  printf("\n");
}
int main (int argc, char** argv){
 
  FILE* circ;
  FILE* inp;
  char c;
  char str[20];
  char* outs;
  char * outsig;
  int num =0;
  int numout = 0;
  int i;
  char* inputs;
  char* inputx;
  char* inputz;
  inp = fopen(argv[2],"r");
  int* outx;  
  int a;
  int b;
  int* greys;
  while(1){
    circ = fopen(argv[1],"r");
    createdatamap();
    while(1){
      
     if(fscanf(circ,"%s",str)==EOF){
       
	break;
      } 
      
      if(strcmp("INPUTVAR",str)==0){
	fscanf(circ,"%d",&num);
	inputs = (char*) malloc(num * sizeof(char));
	for(i=0;i<num;i++){
	  fscanf(circ," %c",&inputs[i]);
     	}
	for(i=0;i<num;i++){
           if( fscanf(inp,"%d",&datamap[getindex(inputs[i])])==EOF){
	    return 0;
	  } 
	}
	free(inputs);      
      } 
      else if(strcmp("OUTPUTVAR",str) ==0){
	fscanf(circ,"%d",&numout);
	outs = (char*) malloc(numout * sizeof(char));
	for(i=0;i<numout;i++){
          fscanf(circ," %c",&outs[i]);
	  
        }

      }

      else if(strcmp("AND",str)==0){

	fscanf(circ," %c",&c);
	if(isalpha(c)){
	  a = datamap[getindex(c)];
	}
	else{
	  a = (int)c - '0';
	}
	fscanf(circ," %c",&c);
	if(isalpha(c)){
          b = datamap[getindex(c)];
        }
        else{
          b = (int)c - '0';
        }
	fscanf(circ," %c",&c);
	AND(a,b,&datamap[getindex(c)]);
	
      }  

      else if(strcmp("OR",str)== 0){

	fscanf(circ," %c",&c);
        if(isalpha(c)){
          a = datamap[getindex(c)];
        }
        else{
          a = (int)c - '0';
        }
        fscanf(circ," %c",&c);
        if(isalpha(c)){
          b = datamap[getindex(c)];
        }
        else{
          b = (int)c - '0';
        }
        fscanf(circ," %c",&c);
        OR(a,b,&datamap[getindex(c)]);	
      }
      else if(strcmp("NOT",str)== 0){
	
	fscanf(circ," %c",&c);
        if(isalpha(c)){
          a = datamap[getindex(c)];
        }
        else{
          a = (int)c - '0';
        }
	fscanf(circ," %c",&c);
	NOT(a,&datamap[getindex(c)]);
      }
      else if(strcmp("DECODER",str)==0){
	
	fscanf(circ,"%d",&num);
        inputz = (char*) malloc(num * sizeof(char));
	greys = (int*) malloc(num * sizeof(int));

	for(i=0;i<num;i++){
          fscanf(circ," %c",&inputz[i]);
        }
	for(i = 0;i<num;i++){
	  if(isalpha(inputz[i])){
	    greys[i]=datamap[getindex(inputz[i])];
	  }
	  else{
	    greys[i] = (int)inputz[i]- '0';
	  }
	}
	a = pow(2,num);
	outsig = (char*)malloc(a*sizeof(char));
	for( i=0;i<a;i++){
	  fscanf(circ," %c",&outsig[i]);
	}
	DECODER(greys,num,outsig);
	free(outsig);
	free(greys);
	free(inputz);
      }
      else if(strcmp("MULTIPLEXER",str)==0){
	fscanf(circ,"%d",&num);
	outx = (int*)malloc(num*sizeof(int));
	for(i=0;i<num;i++){

	  fscanf(circ," %c",&c);
	  if(isalpha(c)){
	      outx[i] = datamap[getindex(c)];
	    }
	    else{
	      outx[i] = (int)c - '0';
	    }

	}
	num = (int)(log(num)/log(2));
	inputx = (char*)calloc(num,sizeof(char));
	for(i=0;i<num;i++){
	  fscanf(circ," %c",&inputx[i]);
	}
	greys = (int*) malloc(num * sizeof(int));
	for(i = 0;i<num;i++){
	  if(isalpha(inputx[i])){
	      greys[i]=datamap[getindex(inputx[i])];
	    }
	    else{
	      greys[i] = (int)inputx[i] - '0';
	    }
        }
	  fscanf(circ," %c",&c);
	  MUX(greys,num,outx,&datamap[getindex(c)]);
	  free(greys);
	  free(outx);
	  free(inputx);
      }
    }
    printout(numout,outs);
    destroydatamap();
    fclose(circ);
  }
 

}
