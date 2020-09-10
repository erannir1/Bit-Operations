#define _CRT_SECURE_NO_WARNINGS  
#define MAXINT 32
#include <stdio.h>
#include <stdlib.h>

int power(int base, int exp)
{
	int i = 0, result = 1;
	for (i; i < exp; i++)
		result = result * base;
	return result;
}

int str_len(char *str)
{
	int length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return length;
}

char* int_to_bin_str(int num) // reciving the binary representation of the number from the user
{
	int ind = 0, i = 0, c, cap = sizeof(char), length = 0;
	char *bin_str, *result;
	if (NULL == (bin_str = (char*)malloc(cap)))
	{
		printf("Error: failed to allocate memory\n"); // prints Error message
		return NULL;
	}

	while (num != 0)
	{
		if (ind == (cap - 1))
		{
			if (cap > MAXINT || NULL == (bin_str = (char*)realloc(bin_str, cap + 1)))
			{
				printf("Error: failed to allocate memory\n");
				exit(1);
			}
			cap += 1;
		}
		if (num & 1 == 1) {
			bin_str[ind++] = '1';
		}
		else {
			bin_str[ind++] = '0';
		}
		num = num >> 1;
	}
	bin_str[ind] = '\0';
	if (NULL == (result = (char*)malloc(str_len(bin_str) + 1)))
		exit(1);
	length = str_len(bin_str);
	for (i; i < str_len(bin_str); i++) {
		result[i] = bin_str[length - i - 1];
	}
	result[i] = '\0';

	return result;
}

char* recive_str()
{
	int ind = 0, c, cap = sizeof(char);
	char *bin_str;
	c = getchar();
	if (NULL == (bin_str = (char*)malloc(cap)))
	{
		printf("Error: failed to allocate memory\n");
		return NULL;
	}

	for (c = getchar(); c != '\n'; c = getchar())
	{
		if (ind == (cap - 1))
		{
			if (cap > MAXINT || NULL == (bin_str = (char*)realloc(bin_str, cap + 1)))
			{
				printf("Error: failed to allocate memory\n");
				exit(1);
			}
			cap += 1;
		}
		bin_str[ind++] = c;
	}
	bin_str[ind] = '\0';
	return bin_str;
}

int bin_to_int(char *bin_str)
{
	int i = 0, result = 0, length = str_len(bin_str), j = 0;
	while (bin_str[i] == '0') // do nothing but increase index
		i++;
	while (bin_str[i] != '\0')
	{
		if (bin_str[i] == '1')
			result += power(2, length - i - 1); // one is multiplied withe 2 power the index of the one
		i++;
	}
	return result;
}

void bin_to_int_out(FILE *fp) //printing the function result
{
	printf("Please enter binary number input: ");
	char *bin_str = recive_str();
	int dec_num = 0;
	dec_num = bin_to_int(bin_str);
	printf("The decimal number of %s is %ld\n", bin_str, dec_num);
	fprintf(fp, "Q1\nThe decimal number of %s is %ld\n", bin_str, dec_num);
	free(bin_str);
}

void int2bin(int num, FILE *fp) // converting  int to binary representation
{	
	if (num > 2147483647)
	{
		printf("The recived number is bigger than int size\n");
		return;
	}
	if (num == 0)
		return;
	if ((num & 1) == 1) //if and mask with 1 is 1 
	{ 
		int2bin(num >> 1,fp); // recursive call to the function with one right shift
		printf("1"); // print 1
		fprintf(fp,"1"); // print 1 in file
	}
	else
	{
		int2bin(num >> 1,fp); // recursive call to the function with one right shift
		printf("0"); // print 0
		fprintf(fp, "0"); // print 0 in file
	}
}

void int2rev_bin(int dec_num, FILE *fp)
{
	int flag = 0; // start to print only after flag higher than 0
	while (dec_num != 0)
	{
		if (dec_num & 1 == 1)
		{
			printf("1");
			fprintf(fp, "1");
			flag++;
		}
		else
		{
			if (flag != 0) // start to print from the first one
			{
				printf("0");
				fprintf(fp, "0");
			}
		}
		dec_num >>= 1;
	}
}

void int2bin_out(FILE *fp)
{
	int n = 0;
	printf("Please enter an integer number: ");
	scanf("%d", &n);
	printf("The original number:\n");
	fprintf(fp, "Q2\nThe original number: ");
	int2bin(n, fp);
	printf("\n");
	fprintf(fp,"\n");
	printf("Reversed bits number:\n");
	fprintf(fp, "Reversed bits number: ");
	int2rev_bin(n, fp);
	printf("\n");
	fprintf(fp, "\n");
}

int get_dec_num(int bits)
{
	int n = 0, obj = 0;
	for (int i = 0; i < 3; i++)
	{
		obj = bits % 10;
		n += (obj * power(2, i));
		bits /= 10;
	}
	return n;
}

char* add_bts_to_bin(char* bin_str, char* mask, char* result, int bin_str_length, int msk_length)
{
	int i = 0, msk_index = 0;
	if (bin_str_length > msk_length)// check if the length of the mask is lower then the length of the binary string
	{
		for (i; i < bin_str_length - msk_length; i++){
			result[i] = bin_str[i];
		}
		for (i; i < bin_str_length - msk_length + 3; i++){
			result[i] = mask[msk_index];
			msk_index++;
		}
		for (i; i < bin_str_length; i++){
			result[i] = bin_str[i];
		}
		result[i] = '\0';
		return result;
	}

	if (msk_length > bin_str_length) // check if the length of the mask is bigger then the length of the binary string
	{
		for (i; i < msk_length - bin_str_length; i++){
			result[i] = mask[i];
		}
		for (i; i < msk_length; i++){
			result[i] = bin_str[i];
		}
		result[i] = '\0';
		return result;
	}

	if (msk_length == bin_str_length) //check if the length of the binary string and the mask are equal
	{
		for (i; i < 3; i++) {
			result[i] = mask[i];
		}
		for (i; i < msk_length; i++){
			result[i] = bin_str[i];
		}
		result[i] = '\0';
		return result;
	}
}

void add_3_bits_with_shift_out(FILE *fp)
{
	int dec_num = 0, shift = 0, mask_length = 0, bin_length = 0, reslen = 0, result = 0;
	char threebits[4], *mask, *bin_str, *bin_str_result;
	printf("Please enter an integer number:");
	scanf("%d", &dec_num);
	printf("Please enter three bits to change:");
	scanf("%s", threebits);
	printf("Please enter the shift for the change:");
	scanf("%d", &shift);
	if (shift > 29)
	{
		printf("The recived number is bigger than int size\n");
		return;
	}
	if (NULL == (mask = (char*)malloc(shift + 4)))
	{
		printf("Error: failed to allocate memory\n");
		return NULL;
	}
	for (int i = 0; i < shift + 3; i++)
	{
		if (i < 3)
			mask[i] = threebits[i];
		else
			mask[i] = '0';
	}
	mask[shift + 3] = '\0';
	bin_str = int_to_bin_str(dec_num);
	mask_length = str_len(mask);
	bin_length = str_len(bin_str);
	if (mask_length > bin_length)
	{
		reslen = mask_length;
	}
	else
	{
		reslen = bin_length;
	}
	if (NULL == (bin_str_result = (char*)malloc(reslen + 1))) return NULL;
	bin_str_result = add_bts_to_bin(bin_str, mask, bin_str_result, bin_length, mask_length);
	result = bin_to_int(bin_str_result);
	free(bin_str);
	free(bin_str_result);
	free(mask);
	printf("The original number is %d, The new number is %d\n", dec_num, result);
	fprintf(fp, "Q3\nThe original number is %d, The new number is %d\n", dec_num, result);
}

int main(int argc ,char *argv[])
{
	int choice = -1;
	FILE *fp;
	unsigned int num=0;
	if (argc != 2) {
		printf("Not enough arguments\n");
		return 1;
	}
	if ((fp = fopen(argv[1], "w")) == NULL)
	{
		printf("File didn't open\n");
		return 1;
	}
	do
	{
		printf("Please choose a question by entering 1 - 3:\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
		{
			bin_to_int_out(fp);
			break;
		}
		case 2:
		{
			int2bin_out(fp);
			break;
		}
		case 3:
			add_3_bits_with_shift_out(fp);
			break;
		}
	} while (choice != 0);
	fclose(fp);
	return 0;
}