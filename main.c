#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#define MAX 100

typedef struct {
    int dia, mes, ano;
} Data_nasc;

typedef struct alunos {
    char nome[51];
    Data_nasc data;
    int idade, id;
    float cr;
    char curso[4];
    int excluir; // 0 - nao excluido, 1 - excluido logicamente
} Aluno;

Aluno alunos[MAX];

int verificarID(int id, int qtd_alunos){
	int i;
    for(i = 0; i < qtd_alunos; i++){
        if(alunos[i].id == id && alunos[i].excluir == 0){
            return 1; 
        }
    }
    return 0;
}

void exibir(Aluno *aluno){
    if(aluno->excluir == 0){
        printf("%-50s %-10s %-8d %-6.1f %02d/%02d/%04d %-5d\n", 
            aluno->nome, 
            aluno->curso, 
            aluno->id, 
            aluno->cr, 
            aluno->data.dia, 
            aluno->data.mes, 
            aluno->data.ano,
            aluno->idade);
    }
}

void create(){
    FILE *arquivo;
    int qtd_alunos = 0, id;
    char resp;

    if((arquivo = fopen("dados_alunos.dat", "ab")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    printf("\n\t\tMaximo de 100 alunos\n\n");
    
    do{

        getchar();
        printf("\nNome: ");
        fgets(alunos[qtd_alunos].nome, sizeof(alunos[qtd_alunos].nome), stdin);
        alunos[qtd_alunos].nome[strcspn(alunos[qtd_alunos].nome, "\n")] = '\0';

        do{
            printf("\nID: ");
            scanf("%d", &id);
            if(verificarID(id, qtd_alunos)){
                printf("\nID ja existe. Insira um novo ID.\n");
            }else{
                alunos[qtd_alunos].id = id;
                break;
            }
        }while(1);

        printf("\nIdade: ");
        scanf("%d", &alunos[qtd_alunos].idade);

        printf("\nCR: ");
        scanf("%f", &alunos[qtd_alunos].cr);

        getchar();
        printf("\nCurso: ");
        fgets(alunos[qtd_alunos].curso, sizeof(alunos[qtd_alunos].curso), stdin);
        alunos[qtd_alunos].curso[strcspn(alunos[qtd_alunos].curso, "\n")] = '\0';

        printf("\nData de Nascimento (dia mes ano): ");
        scanf("%d %d %d", &alunos[qtd_alunos].data.dia, &alunos[qtd_alunos].data.mes, &alunos[qtd_alunos].data.ano);

        alunos[qtd_alunos].excluir = 0;

        fwrite(&alunos[qtd_alunos], sizeof(Aluno), 1, arquivo);
        qtd_alunos++;

        printf("\nAdicionar outro aluno (s/n)?: ");
        do{
            scanf("%c", &resp);
            resp = toupper(resp);
        }while (resp != 'S' && resp != 'N');

    }while(resp == 'S' && qtd_alunos < MAX);

    fclose(arquivo);
}

void read(){
    FILE *arquivo;
    Aluno aluno;

    if((arquivo = fopen("dados_alunos.dat", "rb")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    printf("\n%-50s %-10s %-8s %-6s %-10s %-5s\n", "Nome", "Curso", "ID", "CR", "Data", "Idade");
    
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        exibir(&aluno);
    }

    fclose(arquivo);
}

void update() {
    FILE *arquivo;
    int id, encontrado = 0;

    printf("\nDigite o ID do aluno a ser atualizado: ");
    scanf("%d", &id);

    if((arquivo = fopen("dados_alunos.dat", "rb+")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    Aluno aluno;
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        if(aluno.id == id && aluno.excluir == 0) {
            encontrado = 1;
            printf("\nNovo nome: ");
            getchar();
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            printf("\nNova idade: ");
            scanf("%d", &aluno.idade);
            printf("\nNovo CR: ");
            scanf("%f", &aluno.cr);
            printf("\nNovo curso: ");
            scanf("%s", aluno.curso);

            fseek(arquivo, -sizeof(Aluno), SEEK_CUR);
            fwrite(&aluno, sizeof(Aluno), 1, arquivo);
            break;
        }
    }

    if(!encontrado){
        printf("\nAluno com ID %d nao encontrado.\n", id);
    }

    fclose(arquivo);
}

void excluirLogico(){
    FILE *arquivo;
    int id, encontrado = 0;

    printf("\nDigite o ID do aluno a ser excluido: ");
    scanf("%d", &id);

    if((arquivo = fopen("dados_alunos.dat", "rb+")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    Aluno aluno;
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        if(aluno.id == id && aluno.excluir == 0){
            aluno.excluir = 1;
            fseek(arquivo, -sizeof(Aluno), SEEK_CUR);
            fwrite(&aluno, sizeof(Aluno), 1, arquivo);
            encontrado = 1;
            printf("\nAluno excluido logicamente.\n");
            break;
        }
    }

    if(!encontrado){
        printf("\nAluno com ID %d nao encontrado.\n", id);
    }

    fclose(arquivo);
}

void excluirFisico(){
    FILE *arquivo, *temp;
    int encontrado = 0;

    if((arquivo = fopen("dados_alunos.dat", "rb")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    if((temp = fopen("temp.dat", "wb")) == NULL){
        printf("\n Erro de abertura de arquivo temporário\n");
        exit(1);
    }

    Aluno aluno;
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        if(aluno.excluir == 1){
            encontrado++;

        }else{
            fwrite(&aluno, sizeof(Aluno), 1, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("dados_alunos.dat");
    rename("temp.dat", "dados_alunos.dat");

    printf("Total de campos excluidos: %d", encontrado);
}

void listaAprovados(){
    FILE *arquivo;

    if((arquivo = fopen("dados_alunos.dat", "rb")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    Aluno aluno;
    printf("\nLista de alunos aprovados (CR >= 5.0):\n");
    printf("\n%-50s %-10s %-8s %-6s %-10s %-5s\n", "Nome", "Curso", "ID", "CR", "Data", "Idade");
    
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        if(aluno.cr >= 5.0 && aluno.excluir == 0){
            exibir(&aluno);
        }
    }

    fclose(arquivo);
}

void listaReprovados(){
    FILE *arquivo;

    if ((arquivo = fopen("dados_alunos.dat", "rb")) == NULL) {
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    Aluno aluno;
    printf("\nLista de alunos reprovados (CR < 5.0):\n");
    printf("\n%-50s %-10s %-8s %-6s %-10s %-5s\n", "Nome", "Curso", "ID", "CR", "Data", "Idade");

    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        if(aluno.cr < 5.0 && aluno.excluir == 0){
            exibir(&aluno);
        }
    }

    fclose(arquivo);
}

int main(){
    //create();
    read();
    listaAprovados();
    update();
    listaReprovados();
    //excluirLogico();
    //excluirFisico();

    return 0;
}
