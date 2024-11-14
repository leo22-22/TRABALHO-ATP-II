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
	char nome[30],telefone[20],endereco[40];
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

void CadastroLivros(void)
{
	Livros L;
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
	Autor A;
	FILE *Ptr = fopen("Autor.dat","ab+");
	printf("## CADASTRO DE AUTORES ##\n");
	printf("ID DO AUTOR: ");
	scanf("%d",&A.id_autor);
		while(id_autor>0)
		{
			if(BuscaAutor(Ptr,A.id_autor)==-1)
			{
				printf("NOME DO AUTOR: "); fflush(stdin);
				gets(A.nome);
				printf("NACIONALIDADE: "); fflush(stdin);
				gets(A.nacionalidade);				
				fwrite(&A,sizeof(Autor),1,Ptr);
			
				printf("AUTOR CADASTRADO!\n");
			}else
				printf("AUTOR JÁ CADASTRADO!\n");
			
			getch();
			printf("ID DO AUTOR: ");
			scanf("%d",&A.id_autor);
		}
	fclose(Ptr);
}


