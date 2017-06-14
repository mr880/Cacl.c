#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//*****Structure*****//
typedef struct Argument
{
	char* input;

	char* type; 

} Argument;

typedef struct Array
{
	int* numArray;

} Array;

//creates struct 
Argument *createArg(char* arg1, char* arg2){

	Argument *newArg = malloc(sizeof(Argument));
	
	newArg->input = malloc(sizeof(char)*strlen(arg1)+1);
	strcpy(newArg->input, arg1);

	newArg->type = malloc(sizeof(char)*(strlen(arg2)));
	strcpy(newArg->type, arg2);

	return newArg; 
}
//creates new array 
Array *createArray(int* arr){

	Array *newFloatArr = malloc(sizeof(Array));

	newFloatArr->numArray = arr;

	return newFloatArr;
}

//"int" and "float" check
int typeCheck(char* ptr){
	

	
	
		//check that type spells 'int'
		if(*ptr == 'i'){
			ptr++;
			if(*ptr == 'n'){
				ptr++;
				if(*ptr == 't'){
					ptr++;
					if(*ptr == '\0'){
						return 1;
					}
					else{
						fprintf(stderr, "ERROR: Did you mean 'int'?\n");
						exit(1);
					}
				}
				else{
					fprintf(stderr, "ERROR: Did you mean 'int'?\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "ERROR: Did you mean 'int'?\n");
				exit(1);
			}
		}
		//check that type spells 'float'
		else if(*ptr =='f'){
			ptr++;
			if(*ptr == 'l'){
				ptr++;
				if(*ptr == 'o'){
					ptr++;
					if(*ptr == 'a'){
						ptr++;
						if(*ptr == 't'){
							ptr++;
							if(*ptr == '\0'){
								return 2;
							}
							else{
								fprintf(stderr, "ERROR: Did you mean 'float'?\n");
								exit(1);
							}
						}
						else{
							fprintf(stderr, "ERROR: Did you mean 'float'?\n");
							exit(1);
						}
					}
					else{
						fprintf(stderr, "ERROR: Did you mean 'float'?\n");
						exit(1);
					}
				}
				else{
					fprintf(stderr, "ERROR: Did you mean 'float'?\n");
					exit(1);
				}
			}
			else{
				fprintf(stderr, "ERROR: Did you mean 'float'?\n");
				exit(1);
			}
		}
		//error
		else
			fprintf(stderr, "ERROR: Format Type entered not 'int', or 'float'\n");
			exit(1);
	

}

//create a minus sign check for the first char in our argument
int negCheck(char *ptr){
	
	//if argument starts with 1, it is negative..
	if(*ptr=='1')
		return 1;
	else
		return 0;
}

int char_to_int(char *ptr){
	
	int num = 0;
	int isNeg = negCheck(ptr);
	//exponent of base 2 starts at 30
	int exp = 30;

	//incriment the string placement by one to bypass the negative check
	ptr++;

	switch(isNeg){
		//negative case
		case 1:
			//janky adjustment
			num += 1;
			
			while(*ptr != '\0'){
				switch(*ptr){
					case '0':
						num += pow(2,exp);
						break;
					case '1':
						break;
				}
				exp--;
				ptr++;
			}
			break;
		//positive case
		case 0: 

			while(*ptr != '\0'){
				switch(*ptr){
					case '1':
						num += pow(2,exp);
						break;
					case '0':
						break;
				}
				exp--;
				ptr++;
			}

			break;
	}
	
	return num;

}

float toFloat(char *ptr){

	float num = 0;
	int exp = 0;
	float fraction = 0;
	int i = 0;
	int j = 7;
	int isNeg = 0;
	
	//neg check and move pointer forward
	if(*ptr == '1'){
		isNeg++;
		ptr++;
	}
	else{
		ptr++;
	}
	//finds the value of our exponent moving pointer forward
	while(i != 8){
		switch(*ptr){
			case '1':
				exp += pow(2,j);
				break;
			case '0':
				break;
		}
		ptr++;
		j--;
		i++;
	}
	int x = 0;
	int k = -1;
	//finds value of our fraction moving pointer to the end
	while(x!=23){
		switch(*ptr){
			case '1':
				fraction += pow(2,k);
				break;
			case '0':
				break;
		}
		k--;
		x++;
		ptr++;
	}
	//printf("%d \n", exp);
	//printf("%f \n", fraction);
	//simple math to find our float value before we turn it to scientific notation
	num = (1 + fraction) * pow(2,exp-127);

	//special case (zero check)
	if(exp == 0 && fraction == 0){
		if(isNeg == 1){
			printf("-0.0e0\n");
			exit(0);
		}
		else{
			printf("0.0e0\n");
			exit(0);
		}
	}
	//special case neg and pos infinity check
	else if(exp == 255 && fraction == 0){
		if(isNeg == 1){
			printf("ninf\n");
			exit(0);
		}
		else {

			printf("pinf\n");
			exit(0);

		}
	}
	else if(exp == 255 && fraction != 0){

		if(isNeg == 1){

			printf("-NaN\n");
			exit(0);

		}

		else {

			printf("NaN\n");
			exit(0);

		
		}
	}

	//printf("$%f\n", num);
	
	return num;
}

//put our float into scientific notation
void float2dec(float numf, int count){

	
	//set variables
	
	//int i = 7;
	//int j = 7;
	int newNum = 0;
	int newnewNum = 0;
	int newCount = 0;
	int x = 1;
	float floatnew = 0;

	//for numbers to the power of 0
	if(count == 0){
		
		/*Error Correction for when floats are multiplied by big numbers*/
		newNum = numf * 1000000;
		floatnew = numf * 1000000 ;
		
		if((float)newNum < floatnew){
			newNum += 1;
		}
		/*End Error Correction*/

	
		
	 	//gets rid of trailing zeros
		while(newnewNum == 0){
			newnewNum = newNum % 10;
			if (newnewNum == 0){
				newNum = newNum / 10;
				newnewNum = newNum;
			}

			else{
		
				newnewNum = newNum;
			}

		}
		
		//create temp var
		int temp = newNum;
		
		//count how big our new int is
		while(temp != 0){
			temp = temp / 10;
			newCount++;
		}
		//creat new count variable
		int newnewCount = newCount;
		
		
		//create char int to hold our number
		int a[newCount];
		Array *arr = createArray(a);
		
		//printf("newcount = %d\n",newCount);
		//place values into our int array
		int k = 1;
		while((newCount - k + 1) != 0){
			newnewNum = newNum % 10;
			
			newNum = newNum / 10;
			arr->numArray[newCount-k] = newnewNum;
			newnewNum = newNum;
			//printf("%d",arr->numArray[newCount-k]);
			k++;
		}
		
		

		//print out our float
		printf("%d.",arr->numArray[0]);
		while(x!=newnewCount){
			printf("%d",arr->numArray[x]);
			x++;
		}
		printf("e");
		printf("%d\n", 0);
		
		free(arr);
	}
	//in the case of small numbers
	else if(count < 0){
		numf *= 10;
		newNum = (int)numf;
		//printf("%d \n", newNum);
	
	int secondNum = newNum % 10;
	int firstNum = newNum / 10;

	printf("%d.%de%d\n",firstNum, secondNum, count);
	
	}
}

void moveDec(float num, int isNeg){
	
	//represents our exponent
	int count = 0;
	//int negCheck= isNeg;
	
	
		//if number is between 0 and 1 (all fractions)
	if(isNeg == 0 && num < 10){	
		if(num<1.0 && num>0.0){
			
			while(num<1){
				num = num * 10;
				//printf("%f \n", num);
				count--;
			}
	
			float2dec(num, count);

		}
		
		//if number is between 1 and 10
		else if(num>=1 && num<10){
			
			float2dec(num, count);
			
		}
	}
	
		//if number is greater then 10
	else if(num>10){
		
		//initiate variables
		float temp = num; 
		int count = 0;
		int subtract = 0;
		int exp = 0;
		
		int i = 7;
		
		//how long is our float?
		while(temp > 0.1){
			temp = temp / 10;
			count++;
		}
		
		//make an adjustment for decimal placement
		count--;
		
		
		//find value to be used as a cutoff for our conversion to Scientific Notation
		subtract = count - 7;


		//trim our float and add to its exponent value
		while(subtract!=0){
			num = num/10;
			subtract--;
			exp++;
		}
		
		//create array
		int a[8]={0,0,0,0,0,0,0,0};
		Array *arr = createArray(a);

		//place values into int array
		//int num2 = (int)num / 1;
		int num1 = (int)num / 1; 
	
		//puts values in an int array
		for(i=6; num1!=0; i--){
			arr->numArray[i]= num1 % 10;
			//printf("Array: %d\n", arr->numArray[i]);
			num1 = num1 / 10;
		}

		//housekeeping our values and add a counter var
		int j = 1;
		exp = exp + 6;

		
			
		
		if(isNeg ==1){
			/*print our output*/ 
			printf("-%d.",arr->numArray[0]);
			while(j!=7){
				printf("%d",arr->numArray[j]);
				j++;
			}
			printf("e%d\n",exp);
			/*end print*/
		}
		else if(isNeg ==0){
			/*print our output*/ 
			printf("%d.",arr->numArray[0]);
			while(j!=7){
				printf("%d",arr->numArray[j]);
				j++;
			}
			printf("e%d\n",exp);
			/*end print*/
		}
		//garbage collection
		free(arr);

	}
	
	
	
}


int main(int argc, char** argv){

	float numf = 0;
	int num = 0;
	int isNeg = 0;
	int isInt = 0;
	int isFloat = 0;
	int negFloatCount = 0;
	//create a char* of size 8 for our float manipulation
	

	//initial checks
	if(argc <2){

		fprintf(stderr, "ERROR: Enter An Argument!\n");
		exit(1);
	}
	else if (argc < 3){

		fprintf(stderr, "ERROR: Enter Type!\n");
		exit(1);
	}

	//create new structure
	Argument *binInput = createArg(argv[1], argv[2]);

	//check if bit sequence is negative
	if(negCheck(binInput->input)==1)
		isNeg++;
	
	//check for which type we are dealing with/error checks with type
	if(typeCheck(binInput->type)==1)
		isInt++;
		
	else if(typeCheck(binInput->type)==2)
		isFloat++;

	if(isInt == 1){
		if(isNeg==1)
			printf("-");
		num = char_to_int(binInput->input);
		printf("%d \n", num);
	}

	else if(isFloat == 1){
		if(isNeg==1){
			
			negFloatCount++;
		}
		numf = toFloat(binInput->input);
		//printf("*%f* \n", numf);

		moveDec(numf,negFloatCount);
		
		
	}

	free(binInput->input);
	free(binInput->type);
	free(binInput);
	exit(1);



}