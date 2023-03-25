#include "code.h"

int main()
{
	data* signal = create_empty_code();
	rand_fill_code(signal);	 	

	for (int i = 0; i < signal->length; i++)
	{
		printf("%c", signal->code[i]);
	}
	
	printf("\n");

	printf("%d %d \n", signal->length, signal->check_bit_num);
	

	int a = extra_check_bits(16);
	printf("num of bits %d \n", a);
}
