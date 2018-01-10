#include <stdio.h>
#include <stdlib.h>
#include "operation_functions.h"


int main(int argc, char *argv[])
{

 //variables that start with _ are pointers
 //variables that start and end with _ are pointers to pointers, 
 //variables that start with letters are not pointers
 struct complex_tag *_a,*_b,*_div, *_add, *_sub, **_add_, **_sub_, a, b, div = {0,0}, add = {1,2}, sub = {3,4};
 int addSub, division;

 //checking for sufficient number of arguments
 if (argc < 5){
  printf("Need more arguments\n");
  return 0;
 }

 a.real = atof(argv[1]);
 a.imaginary = atof(argv[2]);
 b.real = atof(argv[3]);
 b.imaginary = atof(argv[4]);
 _a = &a;
 _b = &b;
 _div = &div;
 _add = &add;
 _sub = &sub;
 _add_ = &_add;
 _sub_ = &_sub;
 
 //display entered complex numbers
 printf("\nENTERED COMPLEX NUMBERS:\n(%f) + (%f)i\n(%f) + (%f)i\n", a.real, a.imaginary, b.real, b.imaginary);

 division = divide(_a, _b, _div);

 //display division result
 if (division == 0){
  printf("\nDIVISION RESULTS:\n(%f) + (%f)i\n\n", (*_div).real, (*_div).imaginary);
 } else {
  printf("\nDIVISION RESULTS:\nCan't divide, denomenator = 0\n\n");
 }

  Complex_type mult = multiply(*_a,*_b);

  //display multiplication result 
  printf("MULTIPLICATION RESULTS:\n(%f) + (%f)i\n\n", mult.real, mult.imaginary);

  addSub = add_subtract(*_a, *_b, _add_, _sub_);
 
  //print error message if memory could not be allocated, else print addition and subtraction results
  if (addSub == -1){
   printf("Can't subtract or add\n");
  } else {
   printf("ADDITION RESULTS:\n(%f) + (%f)i\n\n", (**_add_).real, (**_add_).imaginary);
   printf("SUBTRACTION RESULTS:\n(%f) + (%f)i\n\n", (**_sub_).real, (**_sub_).imaginary);
  }
}

