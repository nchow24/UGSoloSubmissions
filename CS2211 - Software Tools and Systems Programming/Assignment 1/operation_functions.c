#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"

//multiplication function for question b)
Complex_type multiply(struct complex_tag x, struct complex_tag y){
 double real = (x.real*y.real)-(x.imaginary*y.imaginary);
 double imaginary = (y.real*x.imaginary)+(x.real*y.imaginary);
 Complex_type c;
 c.real = real;
 c.imaginary = imaginary;
 return c;
}

//division function for question c)
int divide(struct complex_tag *a, struct complex_tag *b, struct complex_tag *c){
 double division_real = (((*a).real*(*b).real)+((*a).imaginary*(*b).imaginary))/(((*b).real*(*b).real)+((*b).imaginary*(*b).imaginary));
 double division_imaginary =  (((*b).real*(*a).imaginary)-((*a).real*(*b).imaginary))/(((*b).real*(*b).real)+((*b).imaginary*(*b).imaginary));
 (*c).real = division_real;
 (*c).imaginary = division_imaginary;

 //if denomenator is 0, then there will be a division error
 if ((((*b).real*(*b).real)+((*b).imaginary*(*b).imaginary)) == 0){
  return -2;
 } else {
  return 0;
 }
}

//addition and subtraction function for question d)
int add_subtract(struct complex_tag a, struct complex_tag b, struct complex_tag **c, struct complex_tag **d){
 
 //dynamic memory allocation
 struct complex_tag *sum, *diff;
 sum = malloc(sizeof(struct complex_tag));
 diff = malloc(sizeof(struct complex_tag));
 if (!sum || !diff){
  printf("Error in allocating memory\n");
  return -1;
 }
  
 //calculate sum 
 double sum_real = a.real + b.real;
 double sum_imaginary = a.imaginary + b.imaginary;

 //calculate difference
 double diff_real = a.real - b.real;
 double diff_imaginary = a.imaginary - b.imaginary;

 (*sum).real = sum_real;
 (*sum).imaginary = sum_imaginary;
 (*diff).real = diff_real;
 (*diff).imaginary = diff_imaginary;
 
 //return created structures to the last 2 parameters
 *c = sum;
 *d = diff;

 free(sum);
 free(diff);

 return 0;
}