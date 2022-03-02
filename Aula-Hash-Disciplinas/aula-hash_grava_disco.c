#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define M 50 //tamanho da table hash - 
#define CONSTANTE_DISPERSAO 7

/*
 * Estrutura da disciplina
 */
typedef struct stDisciplina {
    int cod;                //4 bytes
    char disc_codi[6];      //5 bytes
    char disc_nome[100];    //100 bytes
    char disc_area[50];     //50 bytes
    int disc_perio;         //4 bytes
} tpDisciplina;

/*
 * Estrutura da tabela HASH
 */ 
typedef struct stRegistroHASH {
    char disc_codi[6];      //5 bytes (código da disciplina, indica a relação da chave com a posição do arquivo)
    long pos;               //8 bytes (ponteiro para o arquivo da disciplina em disco)
    void *prox;             //8 bytes (ponteiro para lista, aponta para o próximo elemento da lista)
} tpRegistroHASH;

/*
 * Função HASH para strings. No exemplo, a função é aplicada sobre o código da disciplina
 * Parâmetros:
 *  char *texto string para definir a entrada na tabela HASH
 *  int tamanho_tabela tamanho da tabela (M)
 * 
 */ 

int funcao_hash(char *texto, int tamanho_tabela){
     
    int h = 0;
    for (int i = 0; i < strlen(texto); i++){
        int ascii = (int) texto[i];
        h += (ascii * (i + 1));
        
    }
    h = (CONSTANTE_DISPERSAO * h) % tamanho_tabela;
    
    return h;
}

/*
int funcao_hash(char *texto, int tamanho_tabela){
     
    int h = 0;
    
    for (int i = 0; i < strlen(texto); i++){
        int ascii = (int) texto[i];
        h = (CONSTANTE_DISPERSAO * h + ascii) % tamanho_tabela;
    }
    return h;
}

/*
 * Função que inserire registros na tabela, considerando ainda a possibilidade de colisão 
 * Parâmetros:
 *  tpRegistroHASH **tabela_hash - a tabela HASH
 *  char *disc_cod código da disciplina 
 *  long pos posição do registro no arquivo de dados (NÃO É O ARQUIVO DA TABELA HASH)
 */
void inserir_lista (tpRegistroHASH **tabela_hash, char *disc_cod, long pos){
    tpRegistroHASH *registro = (tpRegistroHASH *) malloc (sizeof(tpRegistroHASH));
    tpRegistroHASH *lista = *tabela_hash;
    
    strcpy(registro->disc_codi, disc_cod);
    registro->pos = pos;
    registro->prox = NULL;
    
    if (lista == NULL){
        *tabela_hash = registro;
        return;
    }
    
    while (lista->prox != NULL)
        lista = (tpRegistroHASH *) lista->prox;
    
    lista->prox = (tpRegistroHASH *) registro;
    return;
    
    
}

/*
 * Função para contar quantos registros estão em colisão em cada entrada da tabela. A função também
 * mostra o fator de carga
 * Parâmetros de entrada: 
 *  tpRegistroHASH **tabela_hash -> é a tabela de listas. 
 *  int tamanho_tabela -> define o tamanho da tabela, mas não das listas (entradas na tabela)
 */ 

void contar_chaves_tabela_hash(tpRegistroHASH **tabela_hash, int tamanho_tabela){
    int N          = 0;
    int qtde_lista = 0;
    for (int i = 0; i < tamanho_tabela; i++){
        qtde_lista = 0;
        tpRegistroHASH *lista = tabela_hash[i];
        while(lista != NULL){
            qtde_lista++;
            lista = (tpRegistroHASH*) lista->prox;
        }//while(lista != NULL){
        printf("Entrada da tabela: %d -> qtde de chaves: %d\n", i, qtde_lista);
        N += qtde_lista;
    }//for (int i = 0; i < tamanho_tabela; i++){
    double alpha = (double) N / M;
    printf("Alpha: %lf \n", alpha);
}

/*
 * A funçao lê registro a registro do arquivo para montar a tabela hash, como o é permitido acesso direito
 *  ao arquivo, cada registro da tabela aponta para uma posição do arquivo de disiciplinas.
 * Observação: O arquivo não é carregado totalmente na memória, apenas 1 registro por vez
 * Parâmetros de entrada: 
 *  tpRegistroHASH **tabela_hash -> é a tabela de listas. 
 *  int tamanho_tabela -> define o tamanho da tabela, mas não das listas (entradas na tabela)
 */
tpRegistroHASH ** ler_arquivo_construir_tabela_hash(char *nome_arquivo, int tamanho_tabela){
    tpRegistroHASH **tabela_hash = NULL;
    FILE           *arquivo  = fopen(nome_arquivo, "rb");
    tpDisciplina   disciplina;
    int            hash;
    assert(arquivo != NULL);
    
    //Alocando memória da tabela
    tabela_hash = (tpRegistroHASH **) malloc (sizeof(tpRegistroHASH *) * tamanho_tabela);
    for (int i = 0; i < tamanho_tabela; i++){
        tabela_hash[i] = (tpRegistroHASH *) malloc(sizeof(tpRegistroHASH));
        tabela_hash[i] = NULL;
    }
     
    
    while (fread(&disciplina, sizeof(tpDisciplina), 1, arquivo) > 0){
         hash = funcao_hash(disciplina.disc_codi, tamanho_tabela);
         long pos = ftell(arquivo) - sizeof (tpDisciplina);
         inserir_lista (&(tabela_hash[hash]), disciplina.disc_codi, pos);
    }
    
    fclose(arquivo);
    
    
    return tabela_hash;
}

/*
 * Função que salva em disco a própria tabela em um arquivo binário
 * observe que não faz sentido gravar o ponteiro das listas que tratam as colisões, porque não temos como 
 * garantir que esses endereços serão o mesmos ao carregar as listas nas tabelas
 * Parâmetros de entrada: 
 *  tpRegistroHASH **tabela_hash -> é uma tabela de listas. 
 *  int tamanho_tabela -> define o tamanho da tabela, mas não das listas (entradas na tabela)
 */
void salvar_tabela_hash(tpRegistroHASH **tabela_hash, int tamanho_tabela){
    FILE *arquivo_hash = fopen("disciplinas_hash.dat", "w+");
    assert(arquivo_hash);
  
  assert(fwrite(&tamanho_tabela, sizeof(int), 1, arquivo_hash) > 0);
  for (int i = 0; i < tamanho_tabela; i++){
        tpRegistroHASH *lista = tabela_hash[i];
        while(lista != NULL){
            assert(fwrite(&lista->disc_codi, sizeof(char), 6, arquivo_hash) > 0);
            assert(fwrite(&lista->pos, sizeof(long), 1, arquivo_hash) > 0);
            lista = (tpRegistroHASH*) lista->prox;
        }//while(lista != NULL){
    }//for (int i = 0; i < tamanho_tabela; i++){
    fclose(arquivo_hash);
}

int main (int ac, char **av){
    printf("Exemplo de uso de tabela HASH\n");
    //Leio do arquivo de disciplinas e constroi a tabela HASH 
    tpRegistroHASH **tabela_hash = ler_arquivo_construir_tabela_hash("disciplinas.dat", M);
    //Conta quantas chaves estão em colisão por entrada na tabela
    //Calcula o fator de carga
    contar_chaves_tabela_hash(tabela_hash, M);
    //exemplo de como salvar a tabela hash em um disco
    //Observação -> a função funcao_hash é determinística. Logo, ao gravar a própria tabela 
    //hash, deve-se observar a função hash utilizada
    salvar_tabela_hash(tabela_hash, M);

    return EXIT_SUCCESS;
}
