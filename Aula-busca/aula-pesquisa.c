#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
typedef struct stDisciplina {
    int cod;                //4 bytes
    char disc_codi[6];      //5 bytes
    char disc_nome[100];    //100 bytes
    char disc_area[50];     //50 bytes
    int disc_perio;         //4 bytes
} tpDisciplina;             //tamanho total 164


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

    fread(disciplina, sizeof(tpDisciplina), tam, bin_in);


    fclose(bin_in);
    return  disciplina;

}

void printDisciplinas(tpDisciplina *disciplinas, int tam){
    for (int i = 0; i < tam; i++){
        //printf("%.2d | %s | %s | %s | %d \n", disciplinas[i].cod, disciplinas[i].disc_codi, disciplinas[i].disc_nome, disciplinas[i].disc_area,  disciplinas[i].disc_perio);
        printf("%.2d | %s | %d | %s | %s \n", disciplinas[i].cod, disciplinas[i].disc_codi, disciplinas[i].disc_perio, disciplinas[i].disc_area, disciplinas[i].disc_nome);    }

}


void pesquisa_binaria(char *nome_arquivo, char *codigo){
   
    
}


void acesso_direto(char *nome_arquivo, int reg){
    int tam_estrutura      = sizeof(tpDisciplina);
    int tam_arquivo        = 0;
    int total_registros    = 0;
    int posicao_no_arquivo = reg * tam_estrutura;
    tpDisciplina disciplina; 
    
    FILE *arquivo = fopen(nome_arquivo, "rb");
    assert(arquivo != NULL);
    
    fseek(arquivo, 0L, SEEK_END); //posiciona no final do arquivo
    tam_arquivo = ftell(arquivo); //retorna quantos bytes foram "lidos" até o momento
    fseek(arquivo, 0L, SEEK_SET); //reposiciona o ponteiro para a posição desejada, neste caso, inicio do arquivo

    total_registros = tam_arquivo / tam_estrutura;
    printf("\nInfo sobre arquivos:\n");
    printf("\tTamanho da estrutura da disciplina %d bytes\n", tam_estrutura);
    printf("\t   Tamanho da estrutura do arquivo %d bytes\n", tam_arquivo);
    printf("\t               Total de registros: %d\n", total_registros);
    printf("\t   Posição do registro %d -> %d bytes\n", reg,  posicao_no_arquivo);
    printf("======================================================================================\n");
    
    if (posicao_no_arquivo > tam_arquivo){
        printf("ERROR: Endereço do registro maior que o tamanho do arquivo (%d > %d)\n", posicao_no_arquivo, tam_arquivo);
        exit(EXIT_FAILURE);
    }
    fseek(arquivo, posicao_no_arquivo, SEEK_SET);
    assert(fread(&disciplina, sizeof(tpDisciplina), 1, arquivo) > 0);
    printf("%.2d | %s | %d | %s | %s \n", disciplina.cod, disciplina.disc_codi, disciplina.disc_perio, disciplina.disc_area, disciplina.disc_nome);
    
}


void pesquisa_sequencial(char *nome_arquivo, char *codigo){
    FILE *arquivo = fopen(nome_arquivo, "rb");
    int   achou   = 0;
    int   comparacoes = 0;
    
    tpDisciplina disciplina;  
    while((!achou) && (fread(&disciplina, sizeof(tpDisciplina), 1, arquivo) > 0)){
        comparacoes++;
        if (strcmp(codigo, disciplina.disc_codi) == 0)
            achou = 1;
    }
    fclose(arquivo);
    
    if (achou){
         printf("%.2d | %s | %d | %s | %s \n", disciplina.cod, disciplina.disc_codi, disciplina.disc_perio, disciplina.disc_area, disciplina.disc_nome); 
    }else{
        printf("Código %s não localizado \n", codigo);
    }
    
    printf("Comparações %d\n", comparacoes);
    
}

int main (int ac, char **av){
    //pesquisa_sequencial(av[1], av[2]);
    acesso_direto(av[1], atoi(av[2]));
    /*
    tpDisciplina *disciplinas = NULL;

    disciplinas =  loadBin(av[1], 91);
    */
    
    return EXIT_SUCCESS;
}
