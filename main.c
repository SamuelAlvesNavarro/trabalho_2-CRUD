#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>


#define MAX 100
typedef struct
{
    int dia, mes, ano;
} Data_nasc;

typedef struct alunos
{
    char nome[50];
    Data_nasc data;
    int idade, id;
    float cr;
    char curso[4];
    int excluir;
} Aluno;



void create(int totalAlunos){
    Aluno alunos[MAX];
    FILE *arquivo;
    char resp;
    if((arquivo = fopen("dados_alunos.dat", "wb")) == NULL) {
        printf ("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    do{
     fwrite(&alunos, sizeof(alunos), 1, arquivo);
     printf("\n Adicionar outro aluno (s/n)?: ");
     do{
         resp = toupper(getch());
     }while(resp != 'S' && resp != 'N');
  }while(resp == 'S');

  fclose(arquivo);
}

void exibir(Aluno *alunos, int i){
    printf("\n%-20s %-6s %-10s %-4s %-10s\n", "Nome", "Curso", "ID", "CR", "Data");
    printf("---------------------------------------------------------------\n");
    printf("%-20s %-6s %-10d %-4.1f %02d/%02d/%04d\n", 
            alunos[i].nome, 
            alunos[i].curso, 
            alunos[i].id, 
            alunos[i].cr, 
            alunos[i].data.dia, 
            alunos[i].data.mes, 
            alunos[i].data.ano);
}

void read(){
    Aluno alunos[MAX];
    FILE *arquivo;
    int i = 0;
    if((arquivo = fopen("dados_alunos.dat", "rb")) == NULL) {
        printf ("\n Erro de abertura de arquivo\n");
        exit(1);
    }
    while(fread(&alunos, sizeof(alunos), 1, arquivo) == 1){
        exibir(alunos, i);
        i++;
    }

    fclose(arquivo);
}

void update(){
    Aluno alunos[MAX];
    FILE *arquivo;
    if((arquivo = fopen("dados_alunos.dat", "ab")) == NULL) {
        printf ("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    fclose(arquivo);
}

void excluirLogico(){
    FILE *arquivo;
    if((arquivo = fopen("dados_alunos.dat", "ab")) == NULL) {
        printf ("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    fclose(arquivo);
}

void excluirFisico(){
    FILE *arquivo;
    if((arquivo = fopen("dados_alunos.dat", "ab")) == NULL) {
        printf ("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    fclose(arquivo);
}

int main(){
    Aluno alunos[2] = {
        {"Joao Silva", "CS", 123, 8.5, 21, {15, 3, 2002}},
        {"Maria Lima", "ENG", 456, 9.2, 22, {10, 6, 2001}}
    };
    for(int i = 0; i < 2; i++)
        read(alunos, i);
    
    system("pause");
    char c[10];
    scanf("%s", c);
}