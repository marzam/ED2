#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
typedef struct stBooks{
  char titulo[255],                     // 255 bytes
       autores[572],                    // 572 bytes
       avalicao_media[16],              // 16 bytes
       isbn[11],                        // 11 bytes
       isbn13[14],                      // 14 bytes
       lingua[14],                      // 14 bytes
       num_pag[5],                      // 5 bytes
       qtde_avaliacoes[8],              // 8 bytes
       qtde_textos_revisados[6],        // 6 bytes
       data_publicacao[11],             // 11 bytes
       editora[62];                     // 62 bytes
} tpBooks;



int main (int ac, char **av){
  FILE *arquivo = fopen(av[1], "rb");
  tpBooks book;
  int registros = 0;
  printf("\nLista de livros: \n");
  assert(arquivo != NULL);
  
  while(fread(&(book), sizeof(tpBooks), 1, arquivo) > 0){
      registros++;
      printf("\t %s \n", book.titulo); 
      
      printf("\t\t %s \n", book.autores); 
      printf("\t\t %s \n", book.avalicao_media); 
      printf("\t\t %s \n", book.isbn); 
      printf("\t\t %s \n", book.isbn13); 
      printf("\t\t %s \n", book.lingua); 
      printf("\t\t %s \n", book.num_pag); 
      printf("\t\t %s \n", book.qtde_avaliacoes); 
      printf("\t\t %s \n", book.qtde_textos_revisados); 
      printf("\t\t %s \n", book.data_publicacao); 
      printf("\t\t %s \n", book.editora); 
      
  }
  printf("Total de registros: %d\n", registros);
  
  fclose(arquivo);
  return EXIT_SUCCESS;
}
