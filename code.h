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

typedef struct    data
{
	type*         code;
	type*    check_bit;
	int         length;
	int  check_bit_num;

}                 data;



data*             create_empty_code();

data*  rand_fill_code(data*     data);

data*          encode(data*   signal);

data*            harm(data*   signal);

int            decode(data*   signal);

int   calc_check_bits(data*   signal);

int  extra_check_bits(       int len);

