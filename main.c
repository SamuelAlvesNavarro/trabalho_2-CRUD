#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>


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



void create(){
    Aluno alunos[MAX];
    int i = 0;
    FILE *arquivo;
    char resp;
    if((arquivo = fopen("dados_alunos.dat", "wb")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }
	printf("\n\t\tMaximo de 100 alunos\n\n");
    do{
        printf("\nNome: ");
        fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
        printf("\nID: ");
        scanf("%d", &alunos[i].id);
        printf("\nIdade: ");
        scanf("%d", &alunos[i].idade);
        printf("\nCR: ");
        scanf("%f", &alunos[i].cr);
        printf("\nCurso: ");
        scanf("%s", alunos[i].curso);
        printf("\nData de Nascimento: ");
        scanf("%d", &alunos[i].data.dia);
        scanf("%d", &alunos[i].data.mes);
        scanf("%d", &alunos[i].data.ano);
		
        fwrite(&alunos[i], sizeof(alunos), 1, arquivo);
        printf("\n Adicionar outro aluno (s/n)?: ");
        i++;
     do{
     	scanf("%c", &resp);
         resp = toupper(resp);
         printf("\n");
     }while(resp != 'S' && resp != 'N');
  }while(resp == 'S');

  fclose(arquivo);
}

void exibir(Aluno *alunos){
    printf("-----------------------------------------------------------------------------\n");
    printf("%-50s %-10s %-8d %-6.1f %02d/%02d/%04d\n", 
            &(*alunos).nome, 
            &(*alunos).curso, 
            (*alunos).id, 
            (*alunos).cr, 
            (*alunos).data.dia, 
            (*alunos).data.mes, 
            (*alunos).data.ano);
}

void read(){
    Aluno alunos[MAX];
    FILE *arquivo;
    int i = 0;
    if((arquivo = fopen("dados_alunos.dat", "rb")) == NULL) {
        printf ("\n Erro de abertura de arquivo\n");
        exit(1);
    }
    printf("\n%-50s %-10s %-8s %-6s %-10s\n", "Nome", "Curso", "ID", "CR", "Data");
    while(fread(&alunos, sizeof(alunos), 1, arquivo) == 1){
        exibir(alunos);
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
    read();
}
