/**********************************************************************************
 * Trabalho prático 1 - Climbing Stairs                                           *
 *                                                                                *
 * Autor: Gabriel Leite Bessa                                                     *
 * Data: 24/02/2023                                                               *
 *                                                                                *
 * Você está subindo uma escada. São necessários n passos para chegar ao topo.    *
 * Cada vez você pode subir 1 ou 2 degraus. De quantas maneiras distintas você    *
 * pode subir até o topo?                                                         *
 *                                                                                *
 **********************************************************************************/

// Algumas demonstrações de combinações
// n = 4
// 1 + 1 + 1 + 1
// 1 + 1 + 2
// 2 + 2
// 2 + 1 + 1
// 1 + 2 + 1
// t = 5

// n = 5
// 1 + 1 + 1 + 1 + 1
// 2 + 1 + 1 + 1
// 2 + 2 + 1
// 1 + 2 + 2
// 1 + 1 + 1 + 2
// 2 + 1 + 2
// 1 + 2 + 1 + 1
// 1 + 1 + 2 + 1
// t = 8

//  x   y
//  2   2
//  3   3
//  4   5
//  5   8
//  6   13

#include <stdio.h>
#include <stdlib.h>

long FibonacciRecursivo(int n);
long FibonacciIterativo(int n);

int main() {
    int nDegraus;

    printf("Número de degraus: ");
    scanf("%i", &nDegraus);

    if ((nDegraus < 1) || (nDegraus > 45))
        exit(0); // Executa uma verificação se o número de degraus não ultrapassam os limites

    // Fibonacci iterativo conseguefazer com nDegraus > 45
    printf("Número de combinações: %li\n", FibonacciIterativo(nDegraus)); // Realiza os cálculos e imprime na tela

    return 0;
}

/*
===============================================
FibonacciRecursivo

    Calcula a série de Fibonacci até o inteiro
    n recursivamente. Consome mais recursos 
    que o iterativo.

    Retorna um long para compatibilidade com a
    função principal
    
===============================================
*/
long FibonacciRecursivo(int n) {
    if (n <= 1)
        return 1; // Base da recursão
    return FibonacciRecursivo(n - 1) + FibonacciRecursivo(n - 2); //
}

/*
===============================================
FibonacciIterativo

    Calcula a série de Fibonacci até o inteiro
    n de forma iterativa.

    Retorna um long pois a série pode
    extrapolar a máxima representação que um
    inteiro consegue.

===============================================
*/
long FibonacciIterativo(int n) {
    long sum, temp1 = 0, temp2 = 1; // Define a variável sum e os dois primeiros termos em temp1 e temp2

    for (int i = 1; i <= n; i++) {
        sum = temp1 + temp2;
        temp1 = temp2;
        temp2 = sum;
    }

    return sum;
}