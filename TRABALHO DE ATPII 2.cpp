#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Livros{
	int id_livro,ano_publi;
	char titulo[100];
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
    FILE *Ptr = fopen("Livros.dat", "ab+");
    printf("## CADASTRO DE LIVROS ##\n");
    printf("ID DO LIVRO: ");
    scanf("%d", &L.id_livro);

    while (L.id_livro > 0)
    {
        if (BuscaLivro(Ptr, L.id_livro) == -1)
        {
            int titulo_valido = 0;
            while (!titulo_valido)
            {
                printf("NOME DO LIVRO: ");
                fflush(stdin);
                gets(L.titulo);

                titulo_valido = 1;
                for (int i = 0; L.titulo[i] != '\0'; i++)
                {
                    if (!((L.titulo[i] >= 'A' && L.titulo[i] <= 'Z') || 
                          (L.titulo[i] >= 'a' && L.titulo[i] <= 'z') || 
                          L.titulo[i] == ' '))
                    {
                        titulo_valido = 0;
                        printf("T�TULO INV�LIDO! Use apenas letras e espa�os.\n");
                        i = strlen(L.titulo);
                    }
                }
            }

            printf("ANO DE PUBLICA��O (XXXX): ");
            scanf("%d", &L.ano_publi);

            if (L.ano_publi >= 1000 && L.ano_publi <= 2024)
            {
                fwrite(&L, sizeof(Livros), 1, Ptr);
                printf("LIVRO CADASTRADO!\n");
            }
            else if (L.ano_publi > 2024 || L.ano_publi <= 9999)
            {
                printf("ANO DE PUBLICA��O INV�LIDO! Data limite at� 2024.\n");
            }
            else if (L.ano_publi < 1000 || L.ano_publi > 9999)
            {
                printf("ANO DE PUBLICA��O INV�LIDO! Deve ter 4 d�gitos.\n");
            }
        }
        else
        {
            printf("ID j� cadastrado!\n");
        }

        getch();
        printf("ID DO LIVRO: ");
        scanf("%d", &L.id_livro);
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
								printf("LIVRO COM ID %d N�O ENCONTRADO!\n",ChaveID);
							}
						}
					}while(ChaveID>0);
				}
			}else{
				printf("AUTOR J� CADASTRADO!\n");
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
						printf("ENDERE�O: "); fflush(stdin);
						gets(P.endereco);				
						fwrite(&P,sizeof(Pessoa),1,Ptr);	
						printf("PESSOA CADASTRADA!\n");
					}else{
						printf("TELEFONE INV�LIDO!\n");
						fclose(Ptr);
					}
				}else{
					printf("TELEFONE INV�LIDO!\n"); 
					fclose(Ptr);
				}			
			}else
				printf("PESSOA J� CADASTRADA!\n");
			
			getch();
			printf("ID DA PESSOA: ");
			scanf("%d",&P.id_pessoa);
		}
	fclose(Ptr);
}

void Alterar(void)
{
	LivroAutor LA;
	Autor A;
	int pos;
	char op;
	clrscr();
    FILE *PtrL = fopen("Livros.dat", "rb");
    FILE *PtrLA = fopen("AutorLivro.dat", "ab+");
	FILE *Ptr = fopen("Autor.dat","ab+");
	printf("## ALTERAR POR I.D ##\n");
	printf("ID DO AUTOR PARA ALTERAR: ");
	scanf("%d",&A.id_autor);
		while(A.id_autor>0)
		{
			pos = BuscaAutor(Ptr,A.id_autor);
			if(BuscaAutor(Ptr,A.id_autor)==-1)
			{
				printf("I.D N�O ENCONTRADO!\n");
			}else{
				fseek(Ptr, pos, SEEK_SET);
        		fread(&A, sizeof(Autor), 1, Ptr);
            	printf("## DADOS FORAM ENCONTRADOS! ##\n");
            	printf("NOME DO AUTOR: %s\n", A.nome);
            	printf("NACIONALIDADE: %s\n", A.nacionalidade);

            	printf("\nDESEJA ALTERAR (S/N)? ");
            	if (toupper(getche()) == 'S')
            	{
                	printf("\nNOVO I.D: ");
                	scanf("%d", &LA.id_autor);
               		printf("NOVO NOME: ");fflush(stdin);
                	gets(A.nome);
                	printf("NOVA NACIONALIDADE: ");
                	fflush(stdin);
                	gets(A.nacionalidade);

                	fseek(Ptr, pos, 0);
                	fwrite(&A, sizeof(Autor), 1, Ptr);

                	fseek(PtrLA, 0, 0);
                	while (fread(&LA, sizeof(LivroAutor), 1, PtrLA) == 1)
               		{
                    	if (LA.id_autor == A.id_autor)
                    	{
                    	    fseek(PtrLA, -sizeof(LivroAutor), 1);
                    	    LA.id_autor = LA.id_autor; 
                    	    fwrite(&LA, sizeof(LivroAutor), 1, PtrLA);
                    	}
                	}

               		printf("\nDADOS FORAM ATUALIZADOS!\n");
                	printf("NOVO I.D: %d\n", LA.id_autor);
                	printf("NOVO NOME: %s\n", A.nome);
                	printf("NOVA NACIONALIDADE: %s\n", A.nacionalidade);
            	}
        	}	

        getch();
        printf("ID DO AUTOR PARA ALTERAR: ");
        scanf("%d", &A.id_autor);
    }

    fclose(Ptr);
    fclose(PtrL);
    fclose(PtrLA);
}

void RealizarEmprestimo(void)
{
	Livros Li;
	Pessoa Pe;
	Emprestimo Em;
	Pessoa Pe;
	FILE *PtrLi = fopen("Livros.dat","rb");
	FILE *PtrEm = fopen("Emprestimos.dat","rb");
	FILE *PtrPe = fopen("Pessoas.dat","ab");
	clrscr();		
	printf("## EFETUAR EMPR�STIMOS ##\n");
	printf("I.D PESSOA: ");
	scanf("%d\n",&Em.id_pessoa);
	if(BuscaPessoa(PtrPe,Em.id_pessoa)!=-1)
	{
		fseek(PtrPe,BuscaPessoa(PtrPe,Em.id_pessoa),0);
		fread(&Pe,sizeof(Pessoa),1, PtrPe);
		printf("## PESSOA ENCONTRADA! ##\n");
		printf("I.D: %d\n",Pe.id_pessoa);
		printf("NOME: %s\n",Pe.nome);
		printf("TELEFONE: %s\n",Pe.telefone);
		printf("ENDERE�O: %s\n",Pe.endereco);
		printf("REALIZAR EMPR�STIMO(S/N)?\n");
		if(toupper(getche())=='S')
		{
			printf("I.D DO LIVRO PARA EMPR�STIMO:\n");
			scanf("%d",&Li.id_livro);
			if(BuscaLivro(PtrLi,Li.id_livro)!=-1){
				fseek(PtrLi,BuscaLivro(PtrLi,Li.id_livro),0);
				fread(&Li,sizeof(Livros),1,PtrLi);
				printf("LIVRO ENCONTRADO!\n");
				printf("I.D: %d\n",Li.id_livro);
				printf("TITULO: %s\n",Li.titulo);
				printf("ANO DE PUBLICA��O: %d\n",Li.ano_publi);
				
				printf("CONFIRMAR EMPR�STIMO DO LIVRO %s PARA %s?(S/N)\n",.Li.titulo,Pe.nome);
				if(toupper(getche())=='S')
				{
					printf("## EMPRÉSTIMO CONCEDIDO! ##\n");
					fwrite(&Em,sizeof(Emprestimo),1,PtrEm);

					printf("I.D: %d\n",Pe.id_pessoa);
					printf("NOME: %s\n",Pe.nome);
					printf("TELEFONE: %s\n",Pe.telefone);
					printf("ENDERE�O: %s\n",Pe.endereco);
					printf("I.D: %d\n",Li.id_livro);
					printf("TITULO: %s\n",Li.titulo);
					printf("ANO DE PUBLICA��O: %d\n",Li.ano_publi);
				}else{
					printf("EMPRÉSTIMO CANCELADO!\n");
				}
			}else{
				printf("LIVRRO NÃO ENCONTRADO!\n");
			}
		}else{
			printf("ERRO NO EMPRÉSTIMO!\n");
		}
	}else{
		printf("PESSOA NÃO ENCONTRADA!\n");
	}
	fclose(PtrLi);
	fclose(PtrPe);
	fclose(PtrEm);
	getch();
}

char Menu(void)
{
	clrscr();
	printf("## MENU ##\n");
	printf("[A]CADASTRAR LIVROS\n");
	printf("[B]CADASTRAR AUTOR\n");
	printf("[C]CADASTRAR PESSOA\n");
	printf("[D]REALIZAR EMPRESTIMO\n");
	printf("[E]EXCLUS�O L�GICA\n");
	printf("[F]EXCLUSA FISICA\n");
	printf("[G]ALTERA��O POR ID\n");
	printf("[H]CONSULTAR LIVRO\n");
	printf("[I]CONSULTAR AUTOR\n");
	printf("[J]CONSULTA PESSOA\n");
	printf("[K]CONSULTAR EMPR�STIMO\n");
	printf("[L]GERAR RELAT�RIO DOS LIVROS\n");
	printf("[M]GERAR RELAT�RIO DOS AUTORES\n");
	printf("[N]GERAR RELAT�RIO DAS PESSOAS\n");
	printf("[O]GERAR RELAT�RIO GERAL\n");
	printf("[P]GERAR RELAT�RIO POR LETRA\n");
	printf("[Q]GERAR RELAT�RIO POR PALAVRA NO T�TULO\n");
	printf("[R]GERAR RELAT�RIO DE EMPR�STIMO FEITO POR UMA PESSOA\n");
	printf("[S]GERAR RELAT�RIO DE TODOS OS LIVROS DE UM AUTOR\n");
	printf("[T]GERAR RELAT�RIO DE TODOS OS EMPR�STIMOS FEITOS POR UMA PESSOA\n");
	printf("[0 PARA SAIR]\n");
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
			case 'G': Alterar();
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

