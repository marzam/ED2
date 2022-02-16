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

tpDisciplina * loadBin(char *nome, unsigned long *tam_out){
    tpDisciplina *disciplina = NULL; //(tpDisciplina *) malloc(tam * sizeof(tpDisciplina));

    long tamanho_arquivo = 0,
         tam = 0,
         tamanho_registro = sizeof(tpDisciplina);

    FILE *bin_in = NULL;

    bin_in = fopen(nome, "rb");
    if (bin_in == NULL){
        fprintf(stderr, "ERROR ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }
    fseek(bin_in, 0, SEEK_END);
    tamanho_arquivo = ftell(bin_in);
    fseek(bin_in, 0, SEEK_SET);
    tam = tamanho_arquivo / tamanho_registro;
    *tam_out  = tam;

    disciplina = (tpDisciplina *) malloc(tam * sizeof(tpDisciplina));
    if (disciplina == NULL){
        fprintf(stderr, "ERROR na alocação de memória\n");
        exit(EXIT_FAILURE);
    }

    fread(disciplina, sizeof(tpDisciplina), tam, bin_in);


    fclose(bin_in);
    return  disciplina;

}
void printDisciplinas(tpDisciplina *disciplinas, unsigned long tam){
    for (long i = 0; i < tam; i++){
        //printf("%.2d | %s | %s | %s | %d \n", disciplinas[i].cod, disciplinas[i].disc_codi, disciplinas[i].disc_nome, disciplinas[i].disc_area,  disciplinas[i].disc_perio);
        printf("%.2d | %s | %d | %s | %s \n", disciplinas[i].cod, disciplinas[i].disc_codi, disciplinas[i].disc_perio, disciplinas[i].disc_area, disciplinas[i].disc_nome);
    }

}


tpDisciplina acharEmMemoria(tpDisciplina *disciplinas, int *status, int chave, unsigned long tam){
    int achou = 0;
    long indice = 0;
    tpDisciplina disciplina;
    while ((!achou) && (indice < tam)){
      if (disciplinas[indice].cod == chave){
        achou = 1;
        printf("Achou registro com chave %d\n", chave);
      }else{
        indice++;
      }
    }//while ((!achou) && (indice < tam)){
    if (achou)
      disciplina = disciplinas[indice];
    *status = achou;
    return disciplina;
}//tpDisciplina acharEmMemoria(tpDisciplina *disciplinas, int *status, int chave, unsigned long tam){

int main (int ac, char **av){
    tpDisciplina *disciplinas = NULL;
    int chave          = -1;
    int status         = 0;
    long tam           = -1;
    disciplinas =  loadBin("disciplinas-01.bin", &tam);
    printDisciplinas(disciplinas, tam);
    printf("Digite uma chave: ");
    scanf("%d", &chave);

    tpDisciplina d = acharEmMemoria(disciplinas, &status, chave, tam);
    if (!status)
      printf("Chave não encontrada\n");
    else{
        printf("%.2d | %s | %d | %s | %s \n", d.cod, d.disc_codi, d.disc_perio, d.disc_area, d.disc_nome);
    }

    free(disciplinas);
    return EXIT_SUCCESS;
}
