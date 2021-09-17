#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

void print(double coff[], int order)
{
	int zeroCounter = 0; //counter to count zeros at the beginning of the remainder array
	for (int i = 0; i <= order; i++)
	{
		if (coff[i] == 0) { zeroCounter++; continue; }
		if (i > zeroCounter && coff[i] < 0) printf(" ");
		else if (i > zeroCounter) printf(" + ");
		if (i == order) { printf("%0.17g", coff[i]); continue; }
		if (coff[i] == 1 && order - i == 1) { printf("X"); continue; }
		if (coff[i] == -1 && order - i == 1) { printf("-X"); continue; }
		if (coff[i] == 1) { printf("X^%d", order - i); continue; }
		if (coff[i] == -1) { printf("-X^%d", order - i); continue; }
		if (order - i == 1) { printf("%0.17gX", coff[i]); continue; }
		printf("%0.17gX^%d", coff[i], order - i);
	}
}

int polyDivide()
{
	double num[100] = { 0 }; //zero initialized array to store cofficients of the numerator
	double den[100] = { 0 }; //zero initialized array to store cofficients of the denomenator
	int orderN;  //order of numerator
	int orderD;   //order of denomenator
	int orderR;    //order of result
	double result[100] = { 0 };  //zero initialized array to store cofficients of result
	double temp[200] = { 0 }; // temporary array for multiplication process

	printf("Enter the order of the numerator:\n");
	scanf("%d", &orderN);
	printf("Enter the order of the denomenator:\n");
	scanf("%d", &orderD);
	orderR = orderN - orderD;

	printf("Enter the cofficients of the numerator seperated by spaces from a%d to a0 (order of numerator and denomenator must be smaller than 100):\n", orderN);
	for (int i = 0; i <= orderN; i++)
		scanf("%lf", &num[i]);

	printf("Enter the cofficients of the denomenator seperated by spaces from a%d to a0 (division by zero will crash the program):\n", orderD);
	for (int i = 0; i <= orderD; i++)
		scanf("%lf", &den[i]);


	if (orderR < 0)
	{
		printf("(");
		print(num, orderN);
		printf(")/");
		print(den, orderD);
		return 0; //function returns zero if order of numerator is smaller than the order of denomerator
	}
	//The idea of the program is based on the shape of the output in the long division:
	/*
	  example (if the order of the result =3):
	  i=0 xxxx  the result[i] =first number after zero divided by denomenator cofficient of the highest power
	  i=1 0xxx
	  i=2 00xx
	  i=3 000x  the x that remains in the last line in the remainder of the division
	*/
	for (int i = 0; i <= orderR; i++)
	{
		result[i] = num[i] / den[0];
		for (int j = 0; j <= orderN; j++)
			temp[orderN - (orderR - i + orderD - j)] = result[i] * den[j];  /* this line to make sure that each order is stored in
																			its right place in temo the highest order is at temp[0] ,
																			lower is at temp[1] ... free term is at temp[orderN]*/
		for (int j = 0; j <= orderN; j++)
			num[j] -= temp[j];

		for (int j = 0; j <= orderN; j++)	temp[j] = 0;  // resetting temp to zero
	}

	printf("result of division is: ");
	print(result, orderR);

	int remainder = 0;
	for (int i = 0; i <= orderN; i++)
	{
		if (num[i] != 0) { remainder++; break; }
	}
	if (remainder == 0) return -1; // if there is no remainder the function returns -1
	printf(" + ");
	printf("( ");
	print(num, orderN);
	printf(" )/( ");
	print(den, orderD);
	printf(" )");
	return 1; //if there is remainder the function returns 1
}

int main()
{
	polyDivide();
}