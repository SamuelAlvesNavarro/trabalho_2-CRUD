#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

#define esc 27
#define f1 59
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

int menu(){
	int o=1;
	char t;
	
	do{
		system("cls");

		printf("Escolha o que deseja fazer:\n");
		printf("1. Registrar\n");
		printf("2. Exibir\n");
		printf("3. Atualizar\n");
		printf("4. Excluir logicamente\n");
		printf("5. Excluir fisicamente\n");
		printf("6. Lista dos alunos aprovados\n");
        printf("7. Lista dos alunos reprovados\n");
		printf("\n<F1>  - Ajuda\n<Esc> - Sair\n");
		
		fflush(stdin);
		t = getch();
		//Verifica se a tecla digitada é um caracter especial
		if(t == esc) return esc;

		if(t == f1) return f1;

        if(t > 48 && t < 56) return t-48;
		
	}while(t < 1 || t > 6);
	
	return 0;
}

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
	 //printf("%s %50s %10s %8s %6s %10s\n", "Nome", "Curso", "ID", "CR", "Data", "Idade");
	 //printf("\n%-50s %-10s %-8s %-6s %-10s %-5s\n", "Nome", "Curso", "ID", "CR", "Data", "Idade");
	 //printf("%-50s %-10s %-8d %-6.1f %02d/%02d/%04d %-5d\n"
    if(aluno->excluir == 0){
        printf("%-50s %-10s %-8d %-6.1f %02d/%02d/%04d %4d\n",
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
        fflush(stdin);
        printf("\nNome: ");
        getchar();
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
    char t;

    if((arquivo = fopen("dados_alunos.dat", "rb")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }

    printf("%-50s %-10s %-8s %-6s %-12s %-5s\n", "Nome", "Curso", "ID", "CR", "Data", "Idade");
    
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        exibir(&aluno);
    }

    fclose(arquivo);
    
    printf("\n\nAperte qualquer tecla para voltar...\n");
    
    do{
		t = getch();
	}while(t == NULL);
}

void update() {
    FILE *arquivo;
    Aluno aluno;
    int id, encontrado = 0;
    
    if((arquivo = fopen("dados_alunos.dat", "rb")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }
    
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        exibir(&aluno);
    }
    
    fclose(arquivo);

    printf("\nDigite o ID do aluno a ser atualizado: ");
    scanf("%d", &id);

    if((arquivo = fopen("dados_alunos.dat", "rb+")) == NULL){
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }
    
    while(fread(&aluno, sizeof(Aluno), 1, arquivo) == 1){
        if(aluno.id == id && aluno.excluir == 0) {
            encontrado = 1;
            fflush(stdin);
            printf("\nNovo nome: ");
            getchar();
            fgets(aluno.nome, sizeof(aluno.nome), stdin);
            printf("\nNova idade: ");
            scanf("%d", &aluno.idade);
            printf("\nNovo CR: ");
            scanf("%f", &aluno.cr);
            printf("\nNovo curso: ");
            scanf("%s", aluno.curso);

            fseek(arquivo, sizeof(Aluno), SEEK_CUR);
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
    char t;

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
    
    printf("\n\nAperte qualquer tecla para voltar...\n");
    
    do{
		t = getch();	
	}while(t == NULL);
    
}

void listaReprovados(){
    FILE *arquivo;
    char t;

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
    
    printf("\n\nAperte qualquer tecla para voltar...\n");
    
    do{
		t = getch();	
	}while(t == NULL);
}

void help(){
	FILE *arquivo;
	int n, count, i , j, x, r;
	char frase[100], t;
	
	if ((arquivo = fopen("ajuda.txt", "r")) == NULL) {
        printf("\n Erro de abertura de arquivo\n");
        exit(1);
    }
		
	fgets(frase, 100, arquivo);
		
	for(i=0;i<strlen(frase);i++){
		if(frase[i] != ' ') frase[i] -= 5;
			
		if(frase[i] < 97 && frase[i] != ' '){
			frase[i] += 26;
		}
	}
		
	printf("%s\n\nAperte qualquer tecla para voltar...\n", frase);
	
	do{
		t = getch();	
	}while(t == NULL);
	
}

int main(){
    //João Pedro de Oliveira Santos
    //Leonardo Quederoli Leme
	//Samuel Alves Navarro
	int e;

	do{
		e = menu();

		switch(e){
		case 1:
			system("cls");
			create();

			break;
		
		case 2:
			system("cls");
			read();

			break;

		case 3:
			system("cls");
			update();

			break;

		case 4:
			system("cls");
			excluirLogico();

			break;

		case 5:
			system("cls");
			excluirFisico();

			break;

		case 6:
			system("cls");
			listaAprovados();

			break;

		case 7:
			system("cls");
			listaReprovados();

			break;

        case f1:
        	system("cls");
            help();

            break;

		default:
			printf("Algo deu errado\n");
		}
	}while(e != esc);

	system("cls");

    return 0;
}
