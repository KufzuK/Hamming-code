#include "code.h"

int main()
{
	data* signal = create_empty_code();
	rand_fill_code(signal);	 	

	printf("%d %d \n", signal->length, signal->check_bit_num);

	printf("before \n");

	print_data(signal);

	encode(signal);

	printf("after \n");
	print_data(signal);

	printf("now harm\n");

///**********************************************************
	int err_bit = harm(signal);

	
	printf("signal, err in  %d \n", err_bit);

	print_data(signal);


	///-*********************************************************
	struct_decode(signal);
	
	printf("now decoded\n");
	

	print_data(signal);

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
