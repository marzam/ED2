#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int forca_bruta(char *X, char *Y, int n, int m){
   int posicao = -1;
   return posicao;
}

int main (int ac, char **av){
   char *X = "bababaeabaeabaeaabaeabaeaaebe\0";
   char *Y = "abaeabaeaae\0";
   //char *Y = "aaebe\0";
   int m = strlen(Y);
   int n = strlen(X);
   int achou = 0;
   printf("Cadeia X = {%s} de tamanho n = %d\n", X, n);
   printf("Cadeia Y = {%s} de tamanho m = %d\n", Y, m);
   achou = forca_bruta(X, Y, n, m);
   printf("Achou em [%d]\n", achou);
   return EXIT_SUCCESS;
}
