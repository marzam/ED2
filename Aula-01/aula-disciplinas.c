#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct stDisciplina {
    int cod;                //4 bytes
    char disc_codi[6];      //5 bytes
    char disc_nome[100];    //100 bytes
    char disc_area[50];     //50 bytes
    int disc_perio;         //4 bytes
} tpDisciplina;
void saveBin(tpDisciplina * disciplina, char *nome, int tam){
  FILE *bin_out = NULL;

  bin_out = fopen(nome, "wb");

  if (bin_out == NULL){
      fprintf(stderr, "ERROR ao abrir o arquivo\n");
      exit(EXIT_FAILURE);
  }

  fwrite(disciplina, sizeof(tpDisciplina), tam, bin_out);


  fclose(bin_out);

}

tpDisciplina * loadBin(char *nome, int tam){
    tpDisciplina *disciplina = (tpDisciplina *) malloc(tam * sizeof(tpDisciplina));
    FILE *bin_in = NULL;
    if (disciplina == NULL){
        fprintf(stderr, "ERROR na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    bin_in = fopen(nome, "rb");

    if (bin_in == NULL){
        fprintf(stderr, "ERROR ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tam; i++){
        fread(&(disciplina[i]), sizeof(tpDisciplina), 1, bin_in);
    }



    fclose(bin_in);
    return  disciplina;

}

tpDisciplina * loadBin3(char *nome, int tam){
    tpDisciplina *disciplina = (tpDisciplina *) malloc(tam * sizeof(tpDisciplina));
    FILE *bin_in = NULL;
    if (disciplina == NULL){
        fprintf(stderr, "ERROR na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    bin_in = fopen(nome, "rb");

    if (bin_in == NULL){
        fprintf(stderr, "ERROR ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

/*
int cod;                //4 bytes
char disc_codi[6];      //5 bytes
char disc_nome[100];    //100 bytes
char disc_area[50];     //50 bytes
int disc_perio;
*/

    for (int i = 0; i < tam; i++){
      fread(&(disciplina[i].cod), sizeof(int), 1, bin_in);
      fread(&(disciplina[i].disc_codi), sizeof(char), 6, bin_in);
      fread(&(disciplina[i].disc_nome), sizeof(char), 100, bin_in);
      fread(&(disciplina[i].disc_area), sizeof(char), 50, bin_in);
      fread(&(disciplina[i].disc_perio), sizeof(int), 1, bin_in);
    }

    fclose(bin_in);
    return  disciplina;

}

tpDisciplina * loadBin2(char *nome, int tam){
    tpDisciplina *disciplina = (tpDisciplina *) malloc(tam * sizeof(tpDisciplina));
    FILE *bin_in = NULL;
    if (disciplina == NULL){
        fprintf(stderr, "ERROR na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    bin_in = fopen(nome, "rb");

    if (bin_in == NULL){
        fprintf(stderr, "ERROR ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    fread(disciplina, sizeof(tpDisciplina), tam, bin_in);


    fclose(bin_in);
    return  disciplina;

}

void printDisciplinas(tpDisciplina *disciplinas, int tam){
    for (int i = 0; i < tam; i++){
        //printf("%.2d | %s | %s | %s | %d \n", disciplinas[i].cod, disciplinas[i].disc_codi, disciplinas[i].disc_nome, disciplinas[i].disc_area,  disciplinas[i].disc_perio);
        printf("%.2d | %s | %d | %s | %s \n", disciplinas[i].cod, disciplinas[i].disc_codi, disciplinas[i].disc_perio, disciplinas[i].disc_area, disciplinas[i].disc_nome);    }

}

int main (int ac, char **av){
    tpDisciplina *disciplinas = NULL;

    disciplinas =  loadBin3("disciplinas-01.bin", 91);
    printDisciplinas(disciplinas, 91);
    //saveBin(disciplinas, "arquivo_saida.bin", 91);
    printf("\n%lu\n", sizeof(int));
    free(disciplinas);
    return EXIT_SUCCESS;
}
