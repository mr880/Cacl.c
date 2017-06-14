#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* create a struct to store arrays*/
typedef struct ArrStruct
{
	int* arr1; 

	int* arr2;

} ArrStruct;

/* create struct to store input variables*/
typedef struct Structure
{
	//argv[2]
	char *input1;
	//argv[3]
	char *input2;
	//argv[1]
	char operation;
	//argv[4]
	char baseType;
} Structure;


/*Struct creator*/
Structure *makeStruc(char *arg2, char *arg3, char* arg1, char* arg4){
	//make new struc
	Structure *struc1 = malloc(sizeof(Structure));
	//allocate memory for arg2 and copy string 
	struc1->input1 = malloc(sizeof(char)*strlen(arg2)+1);
	strcpy(struc1->input1, arg2);
	//allocate mem for arg 3 and copy 
	struc1->input2 = malloc(sizeof(char)*strlen(arg3)+1);
	strcpy(struc1->input2, arg3);

	/*start initial operation check*/
	if(arg1[1]!='\0'){
		fprintf(stderr, "ERROR: Operator entered is too large, try '-' , '+' or '*'\n");
		exit(1);
	}
	
	switch(*arg1){
		case '-': case '+': case '*':
			break;
		default:
			fprintf(stderr, "ERROR: invalid operator.\n");
			exit(1);
			break;
	}

	/*end operation check*/

	struc1->operation = *arg1;

	/*check validity of base type*/
	if(arg4[1]!='\0'){
		fprintf(stderr, "ERROR: Base input is too long. Try 'b','o','d' or 'x'\n");
		exit(1);
	}

	switch(*arg4){
		case 'b': case 'o': case 'd': case 'x':
			break;
		default: 
			fprintf(stderr, "ERROR: Invalid base type.\n");
			exit(1);
			break;
	}
	/*end base type validity check*/

	struc1->baseType = *arg4;
	return struc1;
}

/*array creator*/
ArrStruct *makeArrStruct(int* arrA, int *arrB){
	
	ArrStruct *array1 = malloc(sizeof(ArrStruct));
	array1->arr1 = arrA;
	array1->arr2 = arrB;
	
	return array1;
}

void dec2binConv(int input, int* arr){
	
	int num = 0;
	int i = 31;

	while(input != 0){
		num = input % 2;
		input = input - num;
		if(input != 0){
			input = input / 2;
		}
		arr[i] = num;
		i--;
	}
}
void dec2OctConv(int input, int* arr){
	
	int num = 0;
	int i = 31;

	while(input != 0){
		num = input % 8;
		input = input - num;
		if(input != 0){
			input = input / 8;
		}
		arr[i] = num;
		i--;
	}
}
void dec2HexConv(int input, int* arr){
	
	int num = 0;
	int i = 31;

	while(input != 0){
		num = input % 16;
		input = input - num;
		if(input != 0){
			input = input / 16;
		}
		arr[i] = num;
		i--;
	}
}
void dec2DecConv(int input, int* arr){
	
	int num = 0;
	int i = 31;

	while(input != 0){
		num = input % 10;
		input = input - num;
		if(input != 0){
			input = input / 10;
		}
		arr[i] = num;
		i--;
	}
}
/*initial check to ensure inputs are entered*/
int initialCheck(int arg){
	//check if there is an argument entered
	if(arg<2){
		fprintf(stderr, "ERROR: No arguments!\n");
		return 1;
	}
	//check if there is a first argument
	else if(arg<3){
		fprintf(stderr, "ERROR: Missing first argument!\n");
		return 1;
	}
	//check if there is a second argument
	else if(arg<4){
		fprintf(stderr, "ERROR: Missing second argument!\n");
		return 1;
	}	
	//check for base value
	else if(arg<5){
		fprintf(stderr, "ERROR: Missing base value!\n");
		return 1;
	}
	return 0;
}

/*checks for minus in inputs*/
int negCheck(char *input){

	if(*input == '-'){
		return 1;
	}
	else
		return 0;
}

/*check if our output is negative*/
int negCheck2(int input){
	if(input < 0){
		return 1;
	}
	else
		return 0;
}

/*binary to decimal converter*/
int bin2dec(int len, char* input){

	int num = 0;
	int exponent = len - 1;
	
	/*if the input value furthest to the left is '1',
	the length of the char value at that position - 1,
	is our exponent to our base 2*/

	while(*input != '\0'){
		if(*input == '1'){
			//uses pow() function of base 2 
			num += pow(2, exponent);
			//increase input
			input++;
			//decrease exponent
			exponent--;
		}
		else if(*input == '0'){
			input++;
			exponent--;
		}
	}
	return num; 
}

/*decimal(char) to decimal(integer) converter*/
int dec2dec(int len, char* input){
	/*declare variables*/
	int num = 0;
	int exp = len - 1;

	/* we use a base 10 conversion loop that allows
	us to place numbers into their correct positions*/

	while(*input!='\0'){

		switch(*input){

			case '0':
				break; 
			case '1':
				num += pow(10, exp);
				break;
			case '2':
				num += 2* (pow(10, exp));
				break;
			case '3':
				num += 3* (pow(10, exp));
				break;
			case '4':
				num += 4* (pow(10, exp));
				break;
			case '5':
				num += 5* (pow(10, exp));
				break;
			case '6':
				num += 6* (pow(10, exp));
				break;
			case '7':
				num += 7* (pow(10, exp));
				break;
			case '8':
				num += 8* (pow(10, exp));
				break;
			case '9':
				num += 9* (pow(10, exp));
				break;
		}
		//move input forward and decrease our exponent
		input++;
		exp--;
	}
	return num;
}

/*octal to decimal converter*/
int oct2dec(int len, char* input){
	/*declare variables*/
	int num = 0;
	int exp = len -1; 
	/* we use relatively the same formula for binary
	decimal, octal, and hexadecimal*/
	while(*input != '\0'){
		switch(*input){
			case '0':
				break;
			case '1':
				num += pow(8, exp);
				break;
			case '2':
				num += 2*(pow(8, exp));
				break;
			case '3':
				num += 3*(pow(8, exp));
				break;
			case '4':
				num += 4*(pow(8, exp));
				break;
			case '5':
				num += 5*(pow(8, exp));
				break;
			case '6':
				num += 6*(pow(8, exp));
				break;
			case '7':
				num += 7*(pow(8, exp));
				break;
		}
		input++;
		exp--;
	}
	return num;
}

/*hexadecimal to decimal converter*/
int hex2dec(int len, char* input){
	/*declare variables*/
	int num = 0;
	int exp = len - 1; 

	/* we have to start our hex check with 
	a check for a '0' at the start and an 'x'
	or an 'X' following */

	if(*input == 0){ 
		input++;
		exp--;
		if(*input == 'X'|| *input == 'x'){ 
			input++;
			exp--;
		}
	}

	while(*input != '\0'){
		switch(*input){
			case '0':
				break;
			case '1':
				num += pow(16, exp);
				break;
			case '2':
				num += 2* pow(16, exp);
				break;
			case '3':
				num += 3* pow(16, exp);
				break;
			case '4':
				num += 4* pow(16, exp);
				break;
			case '5':
				num += 5* pow(16, exp);
				break;
			case '6':
				num += 6* pow(16, exp);
					break;
			case '7':
				num += 7* pow(16, exp);
				break;
			case '8':
				num += 8* pow(16, exp);
				break;	
			case '9':
				num += 9* pow(16, exp);
				break;
			case 'a': case 'A':
				num += 10* pow(16, exp);
				break;
			case 'b': case 'B':
				num += 11* pow(16, exp);
				break;
			case 'c': case 'C':
				num += 12* pow(16, exp);
				break;
			case 'd': case 'D':
				num += 13* pow(16, exp);
				break;
			case 'e': case 'E':
				num += 14* pow(16, exp);
				break;
			case 'f': case 'F':
				num += 15* pow(16, exp);
				break;
			default:
				fprintf(stderr, "ERROR: Invalid Hexadecimal Imput!\n");
				exit(1);
				break;
		}
		input++;
		exp--;
	}
	return num;
}

/*create a function to funnel input numbers into their converters*/
int funnel(char *input){
	/*initialize our variables*/
	int num = 0;
	int isNeg = 0;
	/* we use the length of the input to inform our conversion
		functions so that we can keep track of the multiple 
		of the base type when number conversion takes place */ 
	int inputlen = strlen(input);

	//begin with error check
	if(inputlen<=1){
		fprintf(stderr,"ERROR: Input missing number!\n");
		exit(1);
	}
	//negative input check
	if(negCheck(input)==1){
		input++;
		isNeg++; //for later use
		inputlen--;
	}
	
		
	inputlen--;
	
	/*now we funnel our inputs into their converter 
	functions to turn them into decimal integer values*/
	switch(*input){
		case 'b':
			input++;
			num = bin2dec(inputlen, input);
			break;
		case 'd':
			input++;
			num = dec2dec(inputlen, input);
			break;
		case 'o':
			input++;
			num = oct2dec(inputlen, input);
			break;
		case 'x':
			input++;
			num = hex2dec(inputlen, input);
			break;
	}
	if(isNeg == 1){
		num *= (-1);
	}
	return num; 
}

/*where we perform our simple maths after conversion*/
int math(int A, int B, char op){
	//output integer
	int out = 0;

	if(op == '+'){
		out = A + B;
	}
	else if(op == '-'){
		out = A - B;
	}
	else if(op == '*'){
		out = A * B; 
	}
	return out; 
}

void joinArrs(int *arr2, int *arr1){
	int remainder = 0;
	int i = 31;
	int num = 0;

	while(i!=0){
		num = (((arr2[i]%2)+(arr1[i]%2) + remainder) % 2);
		remainder = (((arr2[i]%2)+(arr1[i]%2) + remainder) / 2);
		arr2[i]=num;
		i--;
	}
}

void joinArrsOct(int *arr2, int *arr1){
	int remainder = 0;
	int i = 31;
	int num = 0;

	while(i!=0){
		num = (((arr2[i]%8)+(arr1[i]%8) + remainder) % 8);
		remainder = (((arr2[i]%8)+(arr1[i]%8) + remainder) / 8);
		arr2[i]=num;
		i--;
	}
}

void joinArrsDec(int *arr2, int *arr1){
	int remainder = 0;
	int i = 31;
	int num = 0;

	while(i!=0){
		num = (((arr2[i]%10)+(arr1[i]%10) + remainder) % 10);
		remainder = (((arr2[i]%10)+(arr1[i]%10) + remainder) / 10);
		arr2[i]=num;
		i--;
	}
}

void joinArrsHex(int *arr2, int *arr1){
	int remainder = 0;
	int i = 31;
	int num = 0;

	while(i!=0){
		num = (((arr2[i]%16)+(arr1[i]%16) + remainder) % 16);
		remainder = (((arr2[i]%16)+(arr1[i]%16) + remainder) / 16);
		arr2[i]=num;
		i--;
	}
}

/*convert and print binary outputs*/
void int2bin(int output){

	int arrA[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int arrB[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//create arrays ^^
	ArrStruct *newArrays = makeArrStruct(arrA, arrB);
	//messy variables :(
	int num = output;
	//int base =2; 
	int remainder=0;
	int i = 0;
	int exp = 0;
	int isNeg = 0;

	int num1 = 0;
	//negative check
	if(output<0){
		num = num *(-1);
		isNeg = 1;
	}

	while(num != 0){

		remainder = num % 10;

		if(remainder != 0){

			dec2binConv((remainder*pow(10,exp)), newArrays->arr1);
			joinArrs(newArrays->arr2, newArrays->arr1);

		}
		//remove remainder from value
		num -= remainder;

		if(num!=0){
			num=num/10;
		}
		exp++;
	}

	if(isNeg == 1){
		printf("-");
	}
	//delete leading zeros
	
	while(newArrays->arr2[i]== 0){

		i++;
		if(i==32){
			printf("0");
			break;
		}
	}

	num1 = newArrays->arr2[i];

	printf("b");

	while(i != 32){
		num1 = newArrays->arr2[i];
		if(num1== 0){
			printf("0");
		}
		else if(num1==1){
			printf("1");
		}
		i++;
	}
	printf("\n");

}
/*prints char decimals from type int*/
void int2Dec(int output){
	
	int arrA[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int arrB[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//create arrays ^^
	ArrStruct *newArrays = makeArrStruct(arrA, arrB);
	//messy variables :(
	int num = output;
	//int base =10; 
	int remainder=0;
	int i = 0;
	int exp = 0;
	int isNeg = 0;

	int num1 = 0;
	//negative check
	if(output<0){
		num = num *(-1);
		isNeg = 1;
	}

	while(num != 0){

		remainder = num % 10;

		if(remainder != 0){

			dec2DecConv((remainder*pow(10,exp)), newArrays->arr1);
			joinArrsDec(newArrays->arr2, newArrays->arr1);

		}
		//remove remainder from value
		num -= remainder;

		if(num!=0){
			num=num/10;
		}
		exp++;
	}

	if(isNeg == 1){
		printf("-");
	}
	//delete leading zeros
	
	while(newArrays->arr2[i]== 0){

		i++;
		if(i==32){
			printf("0");
			break;
		}
	}

	num1 = newArrays->arr2[i];
	printf("d");

	while(i!=32){
		
		num1 =  newArrays->arr2[i];

		if(num1 == 0)
			printf("0");
		else if(num1 == 1)
			printf("1");
		else if(num1 == 2)
			printf("2");
		else if(num1 == 3)
			printf("3");
		else if(num1 == 4)
			printf("4");
		else if(num1 == 5)
			printf("5");
		else if(num1 == 6)
			printf("6");
		else if(num1 == 7)
			printf("7");
		else if(num1 == 8)
			printf("8");
		else if(num1 == 9)
			printf("9");
		
		i++;
		
	}
	printf("\n");
	
}
/*convert and print octal outputs*/
void int2oct(int output){
	int arrA[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int arrB[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//create arrays ^^
	ArrStruct *newArrays = makeArrStruct(arrA, arrB);
	//messy variables :(
	int num = output;
	//int base =8; 
	int remainder=0;
	int i = 0;
	int exp = 0;
	int isNeg = 0;

	int num1 = 0;
	//negative check
	if(output<0){
		num = num *(-1);
		isNeg = 1;
	}

	while(num != 0){

		remainder = num % 10;

		if(remainder != 0){

			dec2OctConv((remainder*pow(10,exp)), newArrays->arr1);
			joinArrsOct(newArrays->arr2, newArrays->arr1);

		}
		//remove remainder from value
		num -= remainder;

		if(num!=0){
			num=num/10;
		}
		exp++;
	}

	if(isNeg == 1){
		printf("-");
	}
	//delete leading zeros
	
	while(newArrays->arr2[i]== 0){

		i++;
		if(i==32){
			printf("0");
			break;
		}
	}

	num1 = newArrays->arr2[i];

	printf("o");

			while (i != 32) {

				num1 = newArrays->arr2[i];

				if(num1 == 0)
					printf("0");
				else if(num1 == 1)
					printf("1");
				else if(num1 == 2)
					printf("2");
				else if(num1 == 3)
					printf("3");
				else if(num1 == 4)
					printf("4");
				else if(num1 == 5)
					printf("5");
				else if(num1 == 6)
					printf("6");
				else if(num1 == 7)
					printf("7");
				i++;

			}

			printf("\n");

}
/*convert and print hex outputs*/
void int2hex(int output){
	int arrA[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int arrB[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//create arrays ^^
	ArrStruct *newArrays = makeArrStruct(arrA, arrB);
	//messy variables :(
	int num = output;
	//int base =8; 
	int remainder=0;
	int i = 0;
	int exp = 0;
	int isNeg = 0;

	int num1 = 0;
	//negative check
	if(output<0){
		num = num *(-1);
		isNeg = 1;
	}

	while(num != 0){

		remainder = num % 10;

		if(remainder != 0){

			dec2HexConv((remainder*pow(10,exp)), newArrays->arr1);
			joinArrsHex(newArrays->arr2, newArrays->arr1);

		}
		//remove remainder from value
		num -= remainder;

		if(num!=0){
			num=num/10;
		}
		exp++;
	}

	if(isNeg == 1){
		printf("-");
	}
	//delete leading zeros
	
	while(newArrays->arr2[i]== 0){

		i++;
		if(i==32){
			printf("0");
			break;
		}
	}

	num1 = newArrays->arr2[i];

	printf("x");

		while (i != 32) {

			num1 = newArrays->arr2[i];

			if(num1 == 0)
				printf("0");
			if(num1 == 1)
				printf("1");
			if(num1 == 2)
				printf("2");
			if(num1 == 3)
				printf("3");
			if(num1 == 4)
				printf("4");
			if(num1 == 5)
				printf("5");
			if(num1 == 6)
				printf("6");
			if(num1 == 7)
				printf("7");
			if(num1 == 8)
				printf("8");
			if(num1 == 9)
				printf("9");
			if(num1 == 10)
				printf("A");
			if(num1 == 11)
				printf("B");
			if(num1 == 12)
				printf("C");
			if(num1 == 13)
				printf("D");
			if(num1 == 14)
				printf("E");
			if(num1 == 15)
				printf("F");

			i++;

		}

		printf("\n");
}

int main(int argc, char **argv){

	//stores first integer input
	int inputA;
	//stores second integer input
	int inputB;
	//output integer
	int output;
	//check for initial error conditions
	if(initialCheck(argc) == 1){
		exit(1);
	}

	//create new structure and do some checks...
	Structure *strc = makeStruc(argv[2], argv[3],argv[1], argv[4]);
	//create first and second input
	inputA = funnel(strc->input1);
	inputB = funnel(strc->input2);
	//where we perform our maths
	output = math(inputA, inputB, strc->operation);
	//after math, we convert to our inputted base type
	//printf("%d \n", output);
	//create base type char
	char outBase = strc -> baseType;
	//call function to convert our output to its final basetype
	
	if(outBase == 'd'){
		int2Dec(output);
	}
	else if(outBase == 'b'){
		int2bin(output);
	}
	else if(outBase == 'o'){
		int2oct(output);
	}
	else if(outBase == 'x'){
		int2hex(output);
	}
	//garbage collection
	free(strc->input1);
	free(strc->input2);
	free(strc);

	exit(0);

}