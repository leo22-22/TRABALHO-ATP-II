#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Livros{
	int id_livro,ano_publi;
	char titulo[30];
};

struct Autor{
	int id_autor;
	char nome[30],nacionalidade[30];
};

struct Data{
	int dia,mes,ano;
};

struct Emprestimo{
	int id_emprestimo,id_livro,id_pessoa;
	struct Data data_emprestimo;
	struct Data data_devolucao;
};

struct Pessoa{
	int id_pessoa;
	char nome[30],telefone[14],endereco[40];
};

struct LivroAutor{
	int id_livro,id_autor;
};

void CriaArquivos(void)
{
	FILE *Ptr;
	
	Ptr = fopen("Livros.dat","ab");
	fclose(Ptr);
	Ptr = fopen("Autor.dat","ab");
	fclose(Ptr);
	Ptr = fopen("Emprestimos.dat","ab");
	fclose(Ptr);
	Ptr = fopen("AutorLivro.dat","ab");
	fclose(Ptr);
	Ptr = fopen("Pessoas.dat","ab");
	fclose(Ptr);
}

int BuscaLivro(FILE *Ptr, int ChaveID)
{
	Livros L;
	rewind(Ptr);
	fread(&L,sizeof(Livros),1,Ptr);
	while(!feof(Ptr) && ChaveID!=L.id_livro)
		fread(&L,sizeof(Livros),1,Ptr);

	if (ChaveID==L.id_livro)
		return ftell(Ptr)-sizeof(Livros);
	else
		return -1;
	
}

int BuscaAutor(FILE *Ptr, int ChaveID)
{
	Autor A;
	rewind(Ptr);
	fread(&A,sizeof(Autor),1,Ptr);
	while(!feof(Ptr) && ChaveID!=A.id_autor)
		fread(&A,sizeof(Autor),1,Ptr);

	if (ChaveID==A.id_autor)
		return ftell(Ptr)-sizeof(Autor);
	else
		return -1;
	
}

int BuscaPessoa(FILE *Ptr, int ChaveID)
{
	Pessoa P;
	rewind(Ptr);
	fread(&P,sizeof(Pessoa),1,Ptr);
	while(!feof(Ptr) && ChaveID!=P.id_pessoa)
		fread(&P,sizeof(Pessoa),1,Ptr);

	if (ChaveID==P.id_pessoa)
		return ftell(Ptr)-sizeof(Pessoa);
	else
		return -1;
	
}

void CadastroLivros(void)
{
	Livros L;
	clrscr();
	FILE *Ptr = fopen("Livros.dat","ab+");
	printf("## CADASTRO DE LIVROS ##\n");
	printf("ID DO LIVRO: ");
	scanf("%d",&L.id_livro);
		while(L.id_livro>0)
		{
			if(BuscaLivro(Ptr,L.id_livro)==-1)
			{
				printf("NOME DO LIVRO: "); fflush(stdin);
				gets(L.titulo);
				printf("ANO DE PUBLICAÇÃO: "); fflush(stdin);
				scanf("%d",&L.ano_publi);
				fwrite(&L,sizeof(Livros),1,Ptr);
			
				printf("LIVRO CADASTRADO!\n");
			}else
				printf("ID já cadastrado!\n");
			
			getch();
			printf("ID DO LIVRO: ");
			scanf("%d",&L.id_livro);
		}
	fclose(Ptr);
}

void CadastroAutor(void)
{
	LivroAutor LA;
	Autor A;
	int ChaveID;
	char op;
	clrscr();
    FILE *PtrL = fopen("Livros.dat", "rb");
    FILE *PtrLA = fopen("AutorLivro.dat", "ab+");
	FILE *Ptr = fopen("Autor.dat","ab+");
	printf("## CADASTRO DE AUTORES ##\n");
	printf("ID DO AUTOR: ");
	scanf("%d",&A.id_autor);
		while(A.id_autor>0)
		{
			if(BuscaAutor(Ptr,A.id_autor)==-1)
			{
				printf("NOME DO AUTOR: "); fflush(stdin);
				gets(A.nome);
				printf("NACIONALIDADE: "); fflush(stdin);
				gets(A.nacionalidade);				
				fwrite(&A,sizeof(Autor),1,Ptr);
			
				printf("AUTOR CADASTRADO!\n");
				
				printf("AUTOR POSSUI LIVROS(S/N): ");
				op=toupper(getche());
				
				if(op=='S')
				{
					do{
						printf("INFORME OS IDs:\n");
						scanf("%d",&ChaveID);
						if(ChaveID>0)
						{
							if(BuscaLivro(PtrL,ChaveID)!=-1)
							{
								LA.id_autor=A.id_autor;
								LA.id_livro=ChaveID;
								fwrite(&LA,sizeof(LivroAutor),1,PtrLA);
								printf("LIVRO ASSOCIADO COM O AUTOR COM SUCESSO!\n");
							}else{
								printf("LIVRO COM ID %d NÃO ENCONTRADO!\n",ChaveID);
							}
						}
					}while(ChaveID>0);
				}
			}else{
				printf("AUTOR JÁ CADASTRADO!\n");
			}
			getch();
			printf("ID DO AUTOR: ");
			scanf("%d",&A.id_autor);
		}
	fclose(Ptr);
	fclose(PtrL);
	fclose(PtrLA);
}

void CadastroPessoa(void)
{
	Pessoa P;
	clrscr();
	FILE *Ptr = fopen("Pessoas.dat","ab+");
	printf("## CADASTRO DE PESSOAS ##\n");
	printf("ID DA PESSOA: ");
	scanf("%d",&P.id_pessoa);
		while(P.id_pessoa>0)
		{
			if(BuscaPessoa(Ptr,P.id_pessoa)==-1)
			{
				printf("NOME DA PESSOA: "); fflush(stdin);
				gets(P.nome);
				printf("TELEFONE((XX)XXXXX-XXXX): "); fflush(stdin);
				gets(P.telefone);
				if(strlen(P.telefone)==14)
				{
					if(P.telefone[0] == '(' || P.telefone[3] == ')' || P.telefone[9] == '-')
					{
						printf("ENDEREÇO: "); fflush(stdin);
						gets(P.endereco);				
						fwrite(&P,sizeof(Pessoa),1,Ptr);	
						printf("PESSOA CADASTRADA!\n");
					}else{
						printf("TELEFONE INVÁLIDO!\n");
						fclose(Ptr);
					}
				}else{
					printf("TELEFONE INVÁLIDO!\n"); 
					fclose(Ptr);
				}			
			}else
				printf("PESSOA JÁ CADASTRADA!\n");
			
			getch();
			printf("ID DA PESSOA: ");
			scanf("%d",&P.id_pessoa);
		}
	fclose(Ptr);
}



char Menu(void)
{
	clrscr();
	printf("## MENU ##\n");
	printf("[A]CADASTRAR LIVROS\n");
	printf("[B]CADASTRAR AUTOR\n");
	printf("[C]CADASTRAR PESSOA\n");
	printf("[D]REALIZAR EMPRESTIMO\n");
	printf("[E]EXCLUSÃO LÓGICA\n");
	printf("[F]EXCLUSA FISICA\n");
	printf("[G]ALTERAÇÃO POR ID\n");
	printf("[H]CONSULTAR LIVRO\n");
	printf("[I]CONSULTAR AUTOR\n");
	printf("[J]CONSULTA PESSOA\n");
	printf("[K]CONSULTAR EMPRÉSTIMO\n");
	printf("[L]GERAR RELATÓRIO DOS LIVROS\n");
	printf("[M]GERAR RELATÓRIO DOS AUTORES\n");
	printf("[N]GERAR RELATÓRIO DAS PESSOAS\n");
	printf("[O]GERAR RELATÓRIO GERAL\n");
	printf("[P]GERAR RELATÓRIO POR LETRA\n");
	printf("[Q]GERAR RELATÓRIO POR PALAVRA NO TÍTULO\n");
	printf("[R]GERAR RELATÓRIO DE EMPRÉSTIMO FEITO POR UMA PESSOA\n");
	printf("[S]GERAR RELATÓRIO DE TODOS OS LIVROS DE UM AUTOR\n");
	printf("[T]GERAR RELATÓRIO DE TODOS OS EMPRÉSTIMOS FEITOS POR UMA PESSOA\n");
	printf("CADASTRAR LIVROS\n");
	return toupper(getche());
}

int main(void)
{
	char op;
	do
	{
		op = Menu();
		switch(op)
		{
			case 'A': CadastroLivros();
				break;
			case 'B': CadastroAutor();
				break;
			case 'C': CadastroPessoa();
				break;
			case 'D':
				break;
			case 'E':
				break;
			case 'F':
				break;
			case 'G':
				break;
			case 'H':
				break;
			case 'I':
				break;
			case 'J':
				break;
			case 'K':
				break;
			case 'L':
				break;
			case 'M':
				break;
			case 'N':
				break;
			case 'O':
				break;
			case 'P':
				break;
			case 'Q':
				break;
			case 'R':
				break;
			case 'S':
				break;
			case 'T':
				break;
		}
	}while(op!=27);
	
	return 0;
}

