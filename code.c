#include "code.h"

int MAX_BIT_NUM   = 20;



///**************************************************************************
void destructor(data* signal)
{
	free(signal->code);
	free(signal->expanded_code);
	free(signal->check_bit);
	free(signal);
}

///**************************************************************************




///**************************************************************************
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

///**************************************************************************



///**************************************************************************
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

///**************************************************************************


data* create_empty_code()
{
	data* data1 = (data*) calloc(1, sizeof(data));


/// -------------------------------------------------------------------------
	srand(time(NULL));

	data1->length        =               rand()  %  MAX_BIT_NUM;
	
	data1->check_bit_num =       calc_check_bits(data1->length);

	data1->total_len     = data1->length + data1->check_bit_num;

/// -------------------------------------------------------------------------


	type* code1      = (type*) calloc(data1->length,        sizeof(type));
	type* check_bit1 = (type*) calloc(data1->check_bit_num, sizeof(type));
	type* expand1    = (type*) calloc(data1->total_len,     sizeof(type));


	data1->code          =      code1;
	data1->check_bit     = check_bit1;
	data1->expanded_code =    expand1;


	return data1;
}

///**************************************************************************




///**************************************************************************
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
			continue;
		}


		data->code[i] = '1';
		data->expanded_code[extra_count] = '1';
		extra_count++;
	}

	#endif     // randomising in case type = char



	#ifdef cond
	
	int num_of_1 = rand() % data->length;

	// to be written

	#endif     // randomising in case type = int


	return data;
}


#if(0)

///**************************************************************************

data* fill_code(char* init_code)
{
	
	data* data1 = (data*) calloc(1, sizeof(data));


/// -------------------------------------------------------------------------
	srand(time(NULL));

	data1->length        =                    strlen(init_code);
	
	data1->check_bit_num =       calc_check_bits(data1->length);

	data1->total_len     = data1->length + data1->check_bit_num;
}

/// here supposed that controlling bits are put into bits under powers of 2 -> all the code is getting longer
#endif



///**************************************************************************
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
	//		printf("number = %d,  i = %d,   j = %d, step = %d \n", number, i, j, step);
			if (i + j >= signal->total_len)
			{
	//			printf("Time to stop \n");
				break;
			}

			sum += signal->expanded_code[i + j] - '0';
		
	//		printf("The sum now = %d \n", sum);
		}
	}


/// conditional compilation must be added for case type = int
	if (sum % 2 == 1)
	{
		return '1';
	}
	
	
	return '0';
}

///**************************************************************************



void nul_bits(data* signal)
{
	int long_bit = 1;

	for (int i = 0; i < signal->check_bit_num; i++)
	{
		signal->check_bit[i]               = '0';
		signal->expanded_code[long_bit - 1] = '0';
		long_bit *= 2;
	}
}


///*********** conditional compilation must be added for case type = int


///**************************************************************************
data* encode(data* signal)
{
	if (signal == NULL || signal->code == NULL || signal->check_bit == NULL)
		return NULL;
	
	if (signal->length <= 1 || signal->check_bit_num <= 1)
		return NULL;
	
	nul_bits(signal);	

	int cur_bit = 1;


	
	for (int i = 0; i < signal->check_bit_num; i++)
	{
		type cur_val = def_bit_val(signal, cur_bit - 1);
		//printf("curbit = %d, cur_val = %c \n", cur_bit, cur_val);
		

		signal->expanded_code[cur_bit - 1] = cur_val;

		signal->check_bit[i]               = cur_val;

		cur_bit *= 2;
	}
}

///**************************************************************************




/// if err == -1, one random bit of initial code is changed to opposite, then changed appropriate bit in expanded code. controlling bits supposed to be unchanged.

/// if positive number, err is number of bit to be changed


///**************************************************************************
int harm(data* signal, int err)
{
	int err_bit = err;
	if (err == -1)
	{
		err_bit = rand() % signal->total_len;
	}

	int long_bit = err_bit + calc_check_bits(err_bit);

	if (signal->expanded_code[err_bit] == '1')
	{
		//signal->code[err_bit]           = '0';
		signal->expanded_code[long_bit] = '0';
		return err_bit;
	}

	//signal->code[err_bit]           = '1';
	signal->expanded_code[long_bit] = '1';

	return err_bit;
}
///**************************************************************************




/// if err == -1, one random bit of initial code is changed to opposite, then changed appropriate bit in expanded code. controlling bits supposed to be unchanged.

/// if positive number, err is number of bit to be changed


///**************************************************************************
int harm_old(data* signal, int err)
{
	int err_bit = err;
	if (err == -1)
	{
		err_bit = rand() % signal->length;
	}

	int long_bit = err_bit + calc_check_bits(err_bit + 1);

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
///**************************************************************************


///**************************************************************************
data* struct_decode(data* signal)
{
	type* init_bits = (type*) calloc(signal->check_bit_num, sizeof(type));

	
	for (int i = 0; i < signal->check_bit_num; i++)
	{
		init_bits[i] = signal->check_bit[i];
	}

	encode(signal);	
	
	//printf(" after   \n");
	color_data(signal, -1);

	
	printf("\n");
	int  err_bit = 0;
	int long_bit = 1;

	for (int i = 0; i < signal->check_bit_num; i++)
	{
		if (init_bits[i] != signal->check_bit[i])
		{
	//		printf("init_bit[%d] = %c, signal->check_bit[%d] = %c, long_bit = %d \n", i, init_bits[i], i, signal->check_bit[i], long_bit);

			err_bit += long_bit;
		}
		
		if (init_bits[i] == signal->check_bit[i])
		{
			//printf("init_bit[%d] = %c, signal->check_bit[%d] = %c, long_bit = %d \n", i, init_bits[i], i, signal->check_bit[i], long_bit);
		}

		long_bit *= 2;
	}
	
	free(init_bits);
	
	err_bit--;
	//int long_bit = err_bit + calc_check_bits(err_bit + 1);

	printf("err must be in %d bit \n", err_bit);
	
	if (err_bit < 0)  
		return signal;
 /// no mistakes or more than 1 (impossible if code is harmed by function harm()

	
	if (signal->expanded_code[err_bit] == '1')
	{
		signal->expanded_code[err_bit]  = '0';
		//signal->expanded_code[long_bit] = '0';
		struct_rem_bits(signal);
		return signal;
	}

	signal->expanded_code[err_bit]           = '1';
//	signal->expanded_code[long_bit] = '1';

	struct_rem_bits(signal);
	return signal;
}

///**************************************************************************

void struct_rem_bits(data* signal)
{
	int long_bit = 1;
	int calc     = 0;

	for (int i = 0; i < signal->total_len; i++)
	{
		if (long_bit - 1 == i)
		{
			long_bit *= 2;
			calc++;
			continue;
		}

		signal->code[i - calc] = signal->expanded_code[i];
	}
}


///**************************************************************************
void print_line(type* line, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("%c", line[i]);
	}
	printf("\n");
}
///**************************************************************************




///**************************************************************************
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

///**************************************************************************


/// type = 1, 2 or 3 (the code, the code with controlling bits, only the bits)
/// err_bit the bit of error; if no error, put -1


///**************************************************************************
void color_print_line(type* line, int len, int type, int err_bit)
{
	if (type == CODE)	
	{	
		for (int i = 0; i < len; i++)
		{
			if (i == err_bit)
			{	
    			printf("\x1B[38;2;255;0;0m");
				printf("%c", line[i]);
				printf("\x1B[0m");
				continue;
			}
			printf("%c", line[i]);
		}
		printf("\n");
		return;
	}
	
	if (type == WIDE_CODE)
	{
		int color_bit = 1;
		int long_bit = err_bit + calc_check_bits(err_bit + 1);

		for (int i = 0; i < len; i++)
		{
			if (i == long_bit)
			{	
    			printf("\x1B[38;2;255;0;0m");
				printf("%c", line[i]);
				printf("\x1B[0m");
				continue;
			}


			if (color_bit - 1 == i)
			{
    			printf("\x1B[38;2;40;254;2m");
				printf("%c", line[i]);
				printf("\x1B[0m");
				color_bit *= 2;
				continue;
			}
			printf("%c", line[i]);
		}
		printf("\n");
	}

	if (type == BITS)
	{		
   		printf("\x1B[38;2;40;254;2m");	
	
		for (int i = 0; i < len; i++)
		{	
			printf("%c", line[i]);
		}
		printf("\x1B[0m");
	}

	printf("\n");
}
///**************************************************************************




/// second argument must be a number of bit, not position (so the least is 0;) -1 if no error painted need



///**************************************************************************
void color_data(data* signal, int err_bit)
{

	printf("************start of data************** \n");
	printf("the code \n");
	color_print_line(signal->code, signal->length, CODE, err_bit);

	printf("\n");
	printf("the expanded code \n");

	color_print_line(signal->expanded_code, signal->total_len, WIDE_CODE, err_bit);
	printf("\n");

	printf("only the bits \n");
	
	color_print_line(signal->check_bit, signal->check_bit_num, BITS, err_bit);
	
	printf("\n");
	printf("************  end of data************** \n");
	printf("\n");
}
///**************************************************************************




