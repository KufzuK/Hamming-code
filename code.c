#include "code.h"

int MAX_BIT_NUM   = 20;

int calc_check_bits(data* data)
{
	if (data == NULL)
		return -1;
	
	if (data->length <= 1)
		return -1;


	int last_check_bit = 1;
	int count          = 0;


	while(last_check_bit <= data->length)
	{
		last_check_bit *= 2;
		count++;
	}	

	//data->check_bit_num = count;

//	printf();

	return count;
}


int  extra_check_bits(int len)
{

	int last_check_bit = 1;
	int count          = 0;


	while(last_check_bit <= len)
	{
		last_check_bit *= 2;
		count++;
	}

	return count;
}



data* create_empty_code()
{
	data* data1 = (data*) calloc(1, sizeof(data));


//************************************************************************
	srand(time(NULL));

	data1->length        = rand()  %  MAX_BIT_NUM;
	
	data1->check_bit_num = calc_check_bits(data1);

//************************************************************************


	type* code1      = (type*) calloc(data1->length,        sizeof(type));
	type* check_bit1 = (type*) calloc(data1->check_bit_num, sizeof(type));

	data1->code       =      code1;
	data1->check_bit  = check_bit1;

	return data1;
}


data*  rand_fill_code(data* data)
{
	if (data         == NULL)
		return NULL;

	if (data->code   == NULL)
		return NULL;

	if (data->length <=    1)
		return NULL;


	#ifndef cond	

	for (int i = 0; i < data->length; i++)
	{
		int cur_bit = rand() % 2;
		
		if (cur_bit == 0)
		{
			data->code[i] = '0';
			continue;
		}

		data->code[i] = '1';
	}

	#endif     // randomising in case type = char



	#ifdef cond
	
	int num_of_1 = rand() % data->length;

	// to be written

	#endif     // randomising in case type = int


	return data;
}

/*
data* encode(data* signal)
{
	if (signal == NULL || signal->code == NULL || signal->check_bit == NULL)
		return NULL;
	
	if (signal->length <= 1 || signal->check_bit_num <= 1)
		return NULL;

	return signal;	
}
*/




