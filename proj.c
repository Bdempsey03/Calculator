#include <string.h>
#include <stdio.h>
#include "proj.h"
#include <limits.h>
#include <math.h>
void checkInfo(char input[25]);


int main(){

	char input[25]; //user input
	int result; //result of comparing with "help"

	printf("Ahoy t' Ben's calculator! Wha' can I do fer ye?\n");
	printf("Enter \"quit\" to quit\n");
	while(strcmp(input, "quit\n")!=0){//loop until quit
		printf(">>");
		fgets(input, sizeof(input), stdin); //I tried scanf but it wouldn't accept spaces as input
		if(strcmp(input, "\n")==0)//this is rough patch work because fgets will take the \n from previous commands as input
		fgets(input, sizeof(input), stdin);
		result = strcmp(input, "help\n");
		if(result==0)//if they typed "help"
			printf("Addition\nSubtraction\nMultiplication\nExponentiation\nFloor Division\nBit Counting\nSumation\nFactorial\nGCD\n");
		else if(strcmp(input, "quit\n")==0)
			break;
		else{
			checkInfo(input);//else check if it was a different command
			}
		}
	}
void checkInfo(char input[25]){
	int iresult; // int result of string compares
	int flag=0; //checks to see if a valid command was entered
	iresult = strcmp(input, "info Addition\n");//All have same format. Check string, if command then give info on that command
	        if(iresult==0){
			flag = 1;
	                printf("\nAddition takes two operands and adds them together. The two operands cannot add to be greater than 2,147,483,648\n");
		}
	iresult = strcmp(input, "info Subtraction\n");
	        if(iresult==0){
	                printf("\nSubtraction takes two operands and subtracts the second from the first. The result cannot be less than MIN_INT\n");
			flag = 1;
		}
	iresult = strcmp(input, "info Multiplication\n");
	        if(iresult==0){
	                printf("\nMultiplication takes two operands and returns the product of them. It cannot exceed MAX_INT or be less than MIN_INT\n");
			flag = 1;
		}
	iresult = strcmp(input, "info Floor Division\n");
	        if(iresult==0){
                	printf("\nThis is division and the floor function. This will return the largest integer equal to or less than the division result. It takes two operands where the first is the dividend and the second is the divisor. Division by zero is not allowed. MIN_INT divided by -1 is not allowed\n");
			flag = 1;
		}
	iresult = strcmp(input, "info Exponentiation\n");
	        if(iresult==0){
	                printf("\nExponentiation takes two operands and multiplies the first operand by itself the number of times specified by the second operand. Negative exponents will always result in 0. Exponent cannot exceed 31 unless base is 1. (Some massive inputs can still give erroneous output)\n");
			flag = 1;
		}
	iresult = strcmp(input, "info Bit Counting\n");
	        if(iresult==0){
	                printf("\nBit Counting takes one decimal operand and counts the number of ones in its binary representation.\n");
			flag = 1;
		}
	iresult = strcmp(input, "info Sum\n");
	        if(iresult==0){
	                printf("\nSumation adds all the integers in the range [a,b]. 'a' and 'b' are operands specified by the user. The sumation cannot exceed MAX_INT\n");
			flag = 1;
		}
	iresult = strcmp(input, "info Factorial\n");
        	if(iresult==0){
                	printf("\nFactorial takes one input 'n' and returns n*(n-1)*...*1\n");
			flag = 1;
		}
	iresult = strcmp(input, "info GCD\n");
	        if(iresult==0){
	                printf("\nGCD takes two operands and finds the greatest common divisor of the two operands.\n");
			flag = 1;
		}

//MATH FUNCTIONS
	int return_value; //result of operation
	int operand_a;
	int operand_b;
//factorial
	iresult = strcmp(input, "Factorial\n"); //same format for all. If string is this command then request operands
		if(iresult==0){
			printf("Wha' be yer operand?:");
			scanf("%d",&operand_a);//first operand
			return_value = factorial(operand_a);
			if(return_value==153)//error value for factorial is 0x99 or 153. This means negative input or too large
				printf("invalid input! Ye can't input negatives or large number");
			else
				printf("%d ! = %d\n", operand_a, return_value);//print result
			flag = 1;//we did a command so dont say "invalid command"
		}
//add
	iresult = strcmp(input, "Addition\n");
		if(iresult==0){
			printf("Wha' be yer first value?:");
			scanf("%d", &operand_a);
			printf("Wha' be yer second value?");
			scanf("%d", &operand_b);
			if((operand_a > 0)&&(operand_b > INT_MAX - operand_a)){//Checks result isnt greater than MAX_INT
				printf("invalid input size. Overflowing!");
			}else{
				return_value = addition(operand_a, operand_b);//if valid then do operation
				printf("%d + %d = %d\n", operand_a, operand_b, return_value);
				}
			flag = 1;
		}
//sub
	iresult = strcmp(input, "Subtraction\n");//similar to above
		if(iresult==0){
			printf("Wha' be yer first value?");
			scanf("%d", &operand_a);
			printf("Wha' be yer second value?");
			scanf("%d", &operand_b);
			if((operand_a < 0) && (operand_b > INT_MAX + operand_a)){
				printf("invalid input size. Underflowing!");
			}else{
				return_value = subtraction(operand_a, operand_b);
				printf("%d - %d = %d\n", operand_a, operand_b, return_value);
				}
			flag = 1;
		}
//mult
	iresult = strcmp(input, "Multiplication\n");
		if(iresult==0){
			printf("Wha' be yer first value?");
			scanf("%d", &operand_a);
			printf("Wha' be yer second value?");
			scanf("%d", &operand_b);
			if((fabs(operand_a) > INT_MAX / fabs(operand_b))){//used absolute values to allow negatives
				printf("invalid input size. Overflowing!\n");
			}else{
				return_value = multiplication(operand_a, operand_b);
				printf("%d * %d = %d\n", operand_a, operand_b, return_value);
				}
			flag = 1;
		}
//division
	iresult = strcmp(input, "Floor Division\n");
		if(iresult==0){
			printf("Wha' be yer first value?");
			scanf("%d", &operand_a);
			printf("Wha' be yer second value? (non-zero):");
			scanf("%d", &operand_b);
			if(((operand_a == -1)&&(operand_b == INT_MIN))||operand_b==0){//overflow due to twos complement rules
				printf("invalid input. Divide by 0 or Underflow!\n");
			}else{
				return_value = division(operand_a, operand_b);
				printf("|_%d / %d_| = %d\n", operand_a, operand_b, return_value);
				}
			flag = 1;
		}
//Exponentiation
	iresult = strcmp(input, "Exponentiation\n");
		if(iresult==0){
			printf("Wha' be yer base's value?");
			scanf("%d", &operand_a);
			printf("Wha' be yer exponent value?");
			scanf("%d", &operand_b);
			return_value = exponentiation(operand_a, operand_b);
			if(return_value == -1){
				printf("invalid input. Overflowing!\n");//seen as invalid if base greater than 1 and exponent greater than 31
									//this still allows some invalid inputs but I dont know how to solve that
			}else{
				printf("%d ^ %d = %d\n", operand_a, operand_b, return_value);
			}
			flag = 1;
		}
//Bit counting
	iresult = strcmp(input, "Bit Counting\n");//similar to above
		if(iresult==0){
			printf("Wha' be yer value's decimal representation?");
			scanf("%d", &operand_a);
			return_value = bit_counting(operand_a);
			printf("%d has %d ones\n", operand_a, return_value);
			flag = 1;
		}
//Sumation
	iresult = strcmp(input, "Sumation\n");
		if(iresult==0){
			printf("Wha' be yer starting value?");
			scanf("%d", &operand_a);
			printf("Wha' be yer ending value?");
			scanf("%d", &operand_b);
			return_value = sumation(operand_a, operand_b);
			if(return_value == -1){//returns -1 if invalid (problems with negative
				printf("invalid input. Overflowing!");
			}else{
				printf("sum(%d to %d) = %d\n", operand_a, operand_b, return_value);
			}
			flag = 1;
		}
//GCD
   	 iresult = strcmp(input, "GCD\n");
                if(iresult==0){
                        printf("Wha' be yer first value?");
                        scanf("%d", &operand_a);
                        printf("Wha' be yer second value?");
                        scanf("%d", &operand_b);
                        return_value = gcd(operand_a, operand_b);
                        printf("gcd(%d, %d) = %d\n", operand_a, operand_b, return_value);
                        flag = 1;
                }
		if(flag!=1){//if no valid command was entered
			printf("\nYer command was invalid. Please type \"help\" fer help.\n");
		}
	}
