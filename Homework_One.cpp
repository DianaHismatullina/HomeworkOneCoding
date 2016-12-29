// Homework_One.cpp : Defines the entry point for the console application.

#include "stdafx.h" 
#include <math.h> 
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned right(unsigned a, int n)
{
	unsigned maska = 0; 
	for (int i = 0; i<3; i++)
	{
		maska <<= 1; 
		maska += 1; 
	}
	unsigned b = a & maska; 
	b <<= (n - 3);
	a >>= 3; 
	return a | b; 
}

unsigned left(unsigned a, int n) 
{
	unsigned maska = 0;
	for (int i = 0; i<3; i++)
	{
		maska <<= 1; 
		maska += 1;
	}
	maska <<= (n - 3);

	unsigned b = a & maska; 
	b >>= (n - 3); 
	a <<= 3; 
	return a | b; 
}

void shifrDeshifr(char *in, char *out, int n, int key, int reg)
{
	srand(key); 
	unsigned short a, b, gamma; 
	int l; 
	for (int i = 0; i < n; i += 2)
	{
		if (n % 2 != 0 && i == n - 1) 
		{
			a = 0;
			l = 1;

		}
		else l = 2;
		memcpy(&a, in + i, l); 
		if (reg == 2) 
			a = right(a, l * 8); 
		gamma = rand();
		b = gamma ^ a;
		if (reg == 1) b = left(b, l * 8); 
		memcpy(out + i, &b, l);

	}
}


int main()

{

	int gamma;
	int n = 0;
	int i = 0;

	char strSh[256];
	char strDeSh[256];
	char str[256];
	printf_s("\n Enter the string str="); gets_s(str, 255);

	for (; str[n]; n++);
	printf_s("\n n = %d", n);

	srand(time(NULL));
	gamma = rand() % 36000;
	printf_s("\n gamma = %d ", gamma);

	
	shifrDeshifr(str, strSh, n, gamma, 1);
	printf("\n After coding: \n%s\n", strSh);
	

	
	shifrDeshifr(strSh, strDeSh, n, gamma, 2);
	strDeSh[n] = 0;
	printf("\n After decoding:\n%s\n", strDeSh);
	system("pause");

	return 0;
}
