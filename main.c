#include "code.h"

int main()
{
	data* signal = create_empty_code();
	rand_fill_code(signal);	 	

	printf("%d %d \n", signal->length, signal->check_bit_num);

	printf("before \n");

	color_data(signal, -1);

	encode(signal);

	printf("after \n");
	color_data(signal, -1);

	printf("now harm\n");

///**********************************************************
	int err_bit = harm_old(signal, -1);

	
	printf("signal, err in  %d \n", err_bit);

	color_data(signal, err_bit);


	///-*********************************************************
	struct_decode(signal);
	
	printf("now decoded\n");
	

	color_data(signal, err_bit);
		
	destructor(signal);

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


	printf("example from article\n");


	
	type* line      = (type*) calloc(17, sizeof(type));
	type* long_line = (type*) calloc(22, sizeof(type));
	type* bits      = (type*) calloc(6,  sizeof(type));
	
	data* example = (data*) calloc(1, sizeof(data));

	char line1[17]      =      "0100010000111101";
	char long_line1[22] = "000010000100001011101";
	char bits1[6]       =	              "00000";

	
//	char line1[12]      =           "1000001";
//	char long_line1[16] =       "00100000001";
//	char bits1[5]       =	           "0000";
	
	
	
	strcpy(line, line1);	
	strcpy(bits, bits1);

	strcpy(long_line, long_line1);


	example->code          =      line;	
	example->expanded_code = long_line;	
	example->check_bit     =      bits;	

	example->length = 16;
	example->check_bit_num = 5;
	example->total_len = 21;
	printf("%s \n", example->check_bit);

	color_data(example, -1);

	encode(example);

	color_data(example, -1);

	int err = harm_old(example, 6);

	printf("error must be in %d bit \n", err);
	color_data(example, err);

	struct_decode(example);
	printf("must be decode\nd");
	color_data(example, err);
	
	destructor(example);
	
	//destructor(example);

	/*
	example->code =          "0100010000111101";
	example->expanded_code = "000100001000011011101";
	example->check_bit     = "00000";
	*/

}
