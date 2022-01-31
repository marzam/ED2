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

    size_t bytes_lidos = fread(disciplina, sizeof(tpDisciplina), tam, bin_in);
    printf("Bytes lidos: %lu \n", bytes_lidos);

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

    disciplinas =  loadBin("disciplinas-01.bin", 91);
    printDisciplinas(disciplinas, 91);
    printf("\n%lu\n", sizeof(int));
    free(disciplinas);
    return EXIT_SUCCESS;
}
