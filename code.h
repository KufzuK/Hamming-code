#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/// if int not defined, initial data is in char*

#ifndef INT

typedef char type;

#endif // no INT

///----------------------------------------------------------------

#ifdef INT

typedef int  type;

#endif //    INT

/// add conditional compilation (char or inta data)

typedef struct     data
{
	type*          code;
	type*     check_bit;
	type* expanded_code;
	int          length;
	int   check_bit_num;
	int       total_len;

}                  data;



data*             create_empty_code();

data*  rand_fill_code(data*     data);

data*          encode(data*   signal);

int              harm(data*   signal);

int            decode(data*   signal);

int   calc_check_bits(int        len);

void       destructor(data*   signal);

data*   struct_decode(data*   signal);

type   def_bit_val   (data*   signal, int number);

int  extra_check_bits(       int len);

data*    array_decode(type*     code);

void print_line(type* line, int len);

void print_data(data* signal);
