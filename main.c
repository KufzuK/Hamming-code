#include "code.h"

int main()
{
	data* signal = create_empty_code();
	rand_fill_code(signal);	 	

	printf("%d %d \n", signal->length, signal->check_bit_num);

	printf("signal \n");
	for (int i = 0; i < signal->length; i++)
	{
		printf("%c", signal->code[i]);
	}
	
	printf("\n");
	
	printf("wide signal \n");

	for (int i = 0; i < signal->total_len; i++)
	{
		printf("%c", signal->expanded_code[i]);
	}
	printf("\n");


	encode(signal);


	printf("only bits \n");

	for (int i = 0; i < signal->check_bit_num; i++)
	{
		printf("%c", signal->check_bit[i]);
	}
	
	printf("\n");
	
	printf("wide signal after coding\n");

	for (int i = 0; i < signal->total_len; i++)
	{
		printf("%c", signal->expanded_code[i]);
	}
	printf("\n");

	printf("now harm\n");

	int err_bit = harm(signal);

	
	printf("signal, err in  %d \n", err_bit);

	for (int i = 0; i < signal->length; i++)
	{
		printf("%c", signal->code[i]);
	}

	printf("\n");
	struct_decode(signal);
	
	printf("now decoded\n");
	for (int i = 0; i < signal->length; i++)
	{
		printf("%c", signal->code[i]);
	}


/*	while (1)
	{
		int n = -1;
		printf("enter the bit number \n");
		scanf("%d", &n);
		
		if (n == -1)
			break;		

		printf("\n");

		int a = def_bit_val(signal, n);
		printf("%d \n type -1 if you want to stop", a);
	}
*/

	printf("\n");

	

}
