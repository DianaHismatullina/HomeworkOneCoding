// Homework_One.cpp : Defines the entry point for the console application.

#include "stdafx.h" 
#include <math.h> 
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


unsigned right(unsigned a, int n) //  n - размер блока в битах
{
	// a- исходное значение
	unsigned maska = 0; // Маска для получения правых L битов (младшие L разрядов должны быть 1)
	for (int i = 0; i<3; i++)
	{
		maska <<= 1; // Сдвиг влево на 1 бит
		maska += 1; // Младший бит в 1
	}
	unsigned b = a & maska; // Сохранил младщие L бит в b
	b <<= (n - 3); // Сдвигаем младшие биты в начало блока
	a >>= 3; // Сдвиг вправо на L бит
	return a | b; // Получаем результат
}

unsigned left(unsigned a, int n) // Сдвиг влево на L бит, n - размер блока в битах
{
	// a- исходное значение
	unsigned maska = 0; // Маска для получения левых L битов (старшие L разрядов должны быть 1)
	for (int i = 0; i<3; i++)
	{
		maska <<= 1; // Сдвиг влево на 1 бит
		maska += 1; // Младший бит в 1
	}
	maska <<= (n - 3); // Младшие биты сдвигаем в старшую часть блока

	unsigned b = a & maska; // Сохранил старшие L бит в b
	b >>= (n - 3); // Сдвигаем старшие биты в младшую часть
	a <<= 3; // Сдвиг влево на L бит
	return a | b; // Получаем результат
}

// Одна функция шифрует и дешифрует (работает с блоками по 2 байта)
void shifrDeshifr(char *in, char *out, int n, int key, int reg)
{
	// При шифровании сдвигаем на 2 бита влево 
	/* in - входной массив
	out - выходной массив
	n - размерности массивов
	key - секретный ключ
	reg - режим работы функции 1 - режим шифрования 2 - режим расшифрования
	*/
	srand(key); // Инициализация генератора секретным ключом для получения гаммы
				// Работаем с блоками по 2 байта
	unsigned short a, b, gamma; // Входное и выходное значения
	int l; // Размер блока в байтах
	for (int i = 0; i < n; i += 2)
	{
		if (n % 2 != 0 && i == n - 1) // Условие последний блок не полный - 1 байт
		{
			a = 0;
			l = 1;

		}
		else l = 2;
		memcpy(&a, in + i, l); // Копируем l байта из входного массива
		if (reg == 2) // Режим дешифрования
			a = right(a, l * 8); // Сдвигаем на 2 бита вправо
		gamma = rand();
		b = gamma ^ a;
		if (reg == 1) b = left(b, l * 8); // Сдвигаем на 2 бита влево при шифровании
		memcpy(out + i, &b, l); // Копируем l байта в выходной массив

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
	gamma = rand() % 36000; /* 194 Для проверки на q */
	printf_s("\n gamma = %d ", gamma);

	// Шифруем
	shifrDeshifr(str, strSh, n, gamma, 1);
	// Печаем зашифрованный массив по символьно и коды (т.к. данные двоичные)
	printf("\n After coding: \n%s\n", strSh);
	

	// Расшифруем
	shifrDeshifr(strSh, strDeSh, n, gamma, 2);
	strDeSh[n] = 0; // Строка заканчивается 0
					 // Печать строки после расшифровки
	printf("\n After decoding:\n%s\n", strDeSh);
	system("pause");

	return 0;
}
