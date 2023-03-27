#include "code.h"

int MAX_BIT_NUM   = 20;

int calc_check_bits(int len)
{
	if (len < 1)
		return -1;


	int last_check_bit = 1;
	int count          = 0;


	while(last_check_bit <= len + count)
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

	data1->length        =               rand()  %  MAX_BIT_NUM;
	
	data1->check_bit_num =       calc_check_bits(data1->length);

	data1->total_len     = data1->length + data1->check_bit_num;

//************************************************************************


	type* code1      = (type*) calloc(data1->length,        sizeof(type));
	type* check_bit1 = (type*) calloc(data1->check_bit_num, sizeof(type));
	type* expand1    = (type*) calloc(data1->total_len,     sizeof(type));


	data1->code          =      code1;
	data1->check_bit     = check_bit1;
	data1->expanded_code =    expand1;


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
	for (int i = 0; i < data->check_bit_num; i++)
	{
		data->check_bit[i] = '0';
	}

	int extra_count = 2;
	int  next_c_bit = 4;

	data->expanded_code[0] = '0';
	data->expanded_code[1] = '0';


	for (int i = 0; i < data->length; i++)
	{
		int cur_bit = rand() % 2;
		
		if (extra_count == next_c_bit - 1)
		{
			data->expanded_code[extra_count] = '0';
			next_c_bit *= 2;
			extra_count++;
		}


		if (cur_bit == 0)
		{
			data->code[i] = '0';
			data->expanded_code[extra_count] = '0';
			extra_count++;			

			//printf("curbit = 0, and i = %d, extra_count = %d \n", i, extra_count);
			continue;
		}


		data->code[i] = '1';
		data->expanded_code[extra_count] = '1';
		extra_count++;

		printf("curbit = 1, and i = %d, extra_count = %d \n", i, extra_count);
	}

	#endif     // randomising in case type = char



	#ifdef cond
	
	int num_of_1 = rand() % data->length;

	// to be written

	#endif     // randomising in case type = int


	return data;
}



/// here supposed that controlling bits are put into bits under powers of 2 -> all the code is getting longer


type def_bit_val(data* signal, int number)
{

	if (number < 0) // need to add cond number > 2^ num_of_bits
		return -1;
	
	int step = number + 1;
	int sum  =          0;

	for (int i = number; i < signal->total_len; i += 2 * step)
	{
		for (int j = 0; j < step; j++)
		{

			if (i + j >= signal->total_len)
			{
				break;
			}

			sum += signal->expanded_code[i + j] - '0';
		}
	}


/// conditional compilation must be added for case type = int
	if (sum % 2 == 1)
	{
		return '1';
	}
	
	return '0';
}

///*********** conditional compilation must be added for case type = int
data* encode(data* signal)
{
	if (signal == NULL || signal->code == NULL || signal->check_bit == NULL)
		return NULL;
	
	if (signal->length <= 1 || signal->check_bit_num <= 1)
		return NULL;


	int cur_bit = 1;


	for (int i = 0; i < signal->check_bit_num; i++)
	{
		type cur_val = def_bit_val(signal, cur_bit - 1);

		signal->check_bit[i]               = cur_val;
		signal->expanded_code[cur_bit - 1] = cur_val;

		cur_bit *= 2;
	}
}




/// one random bit of initial code is changed to opposite, then changed appropriate bit in expanded code. controlling bits supposed to be unchanged.

int harm(data* signal)
{
	int  err_bit = rand() % signal->length;
//	printf("err_bit = %d, length = %d \n", err_bit, signal->length);
	int long_bit = err_bit + calc_check_bits(err_bit + 1);

//	printf("long_bit = %d, long_length = %d \n", long_bit, signal->total_len);
	if (signal->code[err_bit] == '1')
	{
		signal->code[err_bit]           = '0';
		signal->expanded_code[long_bit] = '0';
		return err_bit;
	}

	signal->code[err_bit]           = '1';
	signal->expanded_code[long_bit] = '1';

	return err_bit;
}


data* struct_decode(data* signal)
{
	type* init_bits = (type*) calloc(signal->check_bit_num, sizeof(type));

	
	for (int i = 0; i < signal->check_bit_num; i++)
	{
		init_bits[i] = signal->check_bit[i];
	}


	printf(" befroe only bits \n");

	for (int i = 0; i < signal->check_bit_num; i++)
	{
		printf("%c", signal->check_bit[i]);
	}
	
	printf("\n");
	encode(signal);	

	printf(" after  only bits \n");

	for (int i = 0; i < signal->check_bit_num; i++)
	{
		printf("%c", signal->check_bit[i]);
	}
	
	printf("\n");
	int  err_bit = 0;
	int long_bit = 1;

	for (int i = 0; i < signal->check_bit_num; i++)
	{
		if (init_bits[i] != signal->check_bit[i])
		{
			err_bit += long_bit;
		}
		long_bit *= 2;
	}
	
	free(init_bits);
	
	err_bit--;
	//int long_bit = err_bit + calc_check_bits(err_bit + 1);


	if (err_bit < 0)  
		return signal;
 /// no mistakes or more than 1 (impossible if code is harmed by function harm()

	
	if (signal->code[err_bit] == '1')
	{
		signal->code[err_bit]           = '0';
		signal->expanded_code[long_bit] = '0';
		return signal;
	}

	signal->code[err_bit]           = '1';
	signal->expanded_code[long_bit] = '1';

	return signal;
}


/*
data* array_decode(type* code)
{

}*/
void print_line(type* line, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%c", line[i]);
	}
	printf("\n");
}

void print_data(data* signal)
{
	printf("************start of data************** \n");
	printf("the code \n");
	print_line(signal->code, signal->length);

	printf("\n");
	printf("the expanded code \n");

	print_line(signal->expanded_code, signal->total_len);
	printf("\n");

	printf("only the bits \n");
	
	print_line(signal->check_bit, signal->check_bit_num);
	
	printf("\n");
	printf("************  end of data************** \n");
	printf("\n");
}
