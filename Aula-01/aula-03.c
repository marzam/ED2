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


tpDisciplina acharEmDisco(tpDisciplina *disciplinas, int *status, char *nome_arquivo, int chave, unsigned long tam){
    FILE *bin_in = NULL;
    int achou = 0;
    tpDisciplina disciplina;
    long posicao = 0,
         offset  = sizeof(disciplina.disc_codi) + sizeof(disciplina.disc_nome) + \
                  sizeof(disciplina.disc_area) + sizeof(disciplina.disc_perio);



    bin_in = fopen(nome_arquivo, "rb");
    if (bin_in == NULL){
        fprintf(stderr, "ERROR ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    while ((!feof(bin_in)) && (!achou)){
      size_t ret = fread(&disciplina.cod, sizeof(disciplina.cod), 1, bin_in);
      if (disciplina.cod == chave){
        achou = 1;
        fread(&disciplina.disc_codi, sizeof(disciplina.disc_codi), 1, bin_in);
        fread(&disciplina.disc_nome, sizeof(disciplina.disc_nome), 1, bin_in);
        fread(&disciplina.disc_area, sizeof(disciplina.disc_area), 1, bin_in);
        fread(&disciplina.disc_perio, sizeof(disciplina.disc_perio), 1, bin_in);
      }else if (!feof(bin_in)){
          posicao = ftell(bin_in);
          posicao += offset;
          fseek(bin_in, posicao, SEEK_SET);
          posicao = ftell(bin_in);
          //printf("%lx\n", posicao);
          printf("%ld\n", posicao);
      }//if (disciplina.cod == chave){

    }//while ((!feof(bin_in)) && (!achou)){
    *status = achou;
    return disciplina;
}//tpDisciplina acharEmMemoria(tpDisciplina *disciplinas, int *status, int chave, unsigned long tam){
int main (int ac, char **av){
    tpDisciplina *disciplinas = NULL;
    int chave          = -1;
    int status         = 0;
    long tam           = -1;

    printf("Digite uma chave: ");
    scanf("%d", &chave);

    tpDisciplina d = acharEmDisco(disciplinas, &status, "disciplinas-01.bin", chave, tam);
    if (!status)
      printf("Chave não encontrada\n");
    else{
        printf("%.2d | %s | %d | %s | %s \n", d.cod, d.disc_codi, d.disc_perio, d.disc_area, d.disc_nome);
    }

    free(disciplinas);
    return EXIT_SUCCESS;
}
