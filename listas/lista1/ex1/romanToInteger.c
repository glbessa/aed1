/**********************************************************************************
 * Problema Roman to Integer do LeetCode                                          *
 *                                                                                *
 * Fazer um programa que dado um certo número romano converta ele para um inteiro * 
 * https://leetcode.com/problems/roman-to-integer/description/                    *
 *                                                                                *
 *                                                                                *
 **********************************************************************************/

// 
// https://leetcode.com/problems/roman-to-integer/description/

#include <stdio.h>

#define MAX_LENGTH 50

int main() 
{
	char romanNumber[MAX_LENGTH];

	scanf("%s", romanNumber); //leitura do numero romano

	int number = 0;
	int i = 0; //contador de posicoes

	/*
	 *  Rotina para verificar os algarismos romanos e converte-los para inteiro
	 */
	
	while (romanNumber[i] != '\0')
	{
		switch (romanNumber[i])
		{
			case 'I':
				if (romanNumber[i+1] == 'V') {
					/* verificando os casos IV */
					number += 4;
					i++;
				} else if (romanNumber[i+1] == 'X') {
					/* verificando os caso IX */
					number += 9;
					i++;
				} else {
					number += 1;
				}
				break;
			case 'V':
				number += 5;
				break;
			case 'X':
				if (romanNumber[i+1] == 'L') { 
					/* verificando os casos XL */
					number += 40;
					i++;
				} else if (romanNumber[i+1] == 'C') {
					/* verificando os casos XC */
					number += 90;
					i++;
				} else {
					number += 10;
				}
				break;
			case 'L':
				number += 50;
				break;
			case 'C':
				if (romanNumber[i+1] == 'D') {
					/* verificando os casos CD */
					number += 400;
					i++;
				} else if (romanNumber[i+1] == 'M')	{
					/* verificando os casos CM */
					number += 900;
					i++;
				} else {
					number += 100;
				}
				break;
			case 'D':
				number += 500;
				break;
			case 'M':
				number += 1000;
				break;
			default:
				break;
		}
		i++;
	}

	printf("%s = %i\n", romanNumber, number);

	return 0;
}

