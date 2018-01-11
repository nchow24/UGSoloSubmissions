#ifndef OPERATION_FUNCTIONS_H_
#define OPERATION_FUNCTIONS_H_

//structure for question a)
struct complex_tag
{
 double real;
 double imaginary;
};

//structure for question b)
typedef struct
{
 double real;
 double imaginary;
} Complex_type;

//prototypes for functions
Complex_type multiply(struct complex_tag x, struct complex_tag y);
int divide(struct complex_tag *a, struct complex_tag *b, struct complex_tag *c);
int add_subtract(struct complex_tag a, struct complex_tag b, struct complex_tag **c, struct complex_tag **d);

#endif