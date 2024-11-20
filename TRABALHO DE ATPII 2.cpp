#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

struct Livros{
	int id_livro,ano_publi;
	char titulo[100];
};

struct Autor{
	int id_autor;
	char nome[30],nacionalidade[30];
};

struct Emprestimo{
	int id_emprestimo,id_livro,id_pessoa;
	int dia,mes,ano;
	char data_emprestimo[11];
	char data_devolucao[11];
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

int BuscaLivro(FILE *Ptr, int ChaveID) {
    Livros L;
    rewind(Ptr);  
    while (fread(&L, sizeof(Livros), 1, Ptr) == 1) {  
        if (ChaveID == L.id_livro) {
            return ftell(Ptr) - sizeof(Livros);  
        }
    }
    return -1;  
}

int BuscaAutor(FILE *Ptr, int ChaveID) {
    Autor A;
    rewind(Ptr); 
    while (fread(&A, sizeof(Autor), 1, Ptr) == 1) {  
        if (ChaveID == A.id_autor) {
            return ftell(Ptr) - sizeof(Autor);  
        }
    }
    return -1;  
}

int BuscaAutorPorLivro(FILE *Ptr, int id_livro) {
    LivroAutor LA;
    rewind(Ptr); 
    while (fread(&LA, sizeof(LivroAutor), 1, Ptr) == 1) {  
        if (LA.id_livro == id_livro) {
            return ftell(Ptr) - sizeof(LivroAutor);  
        }
    }
    return -1; 
}

int BuscaPessoa(FILE *Ptr, int ChaveID) {
    Pessoa P;
    rewind(Ptr);  // Volta para o início do arquivo
    while (fread(&P, sizeof(Pessoa), 1, Ptr) == 1) {  
        if (ChaveID == P.id_pessoa) {
            return ftell(Ptr) - sizeof(Pessoa);  
        }
    }
    return -1;  
}

int BuscaEmprestimo(FILE *Ptr, int ChaveID) {
    Emprestimo E;
    rewind(Ptr);  
    while (fread(&E, sizeof(Emprestimo), 1, Ptr) == 1) {  
        if (ChaveID == E.id_emprestimo) {
            return ftell(Ptr) - sizeof(Emprestimo); 
        }
    }
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
                        printf("T?TULO INVÁLIDO! Use apenas letras e espaços.\n");
                        i = strlen(L.titulo);
                    }
                }
            }

            printf("ANO DE PUBLICAÇÃO (XXXX): ");
            scanf("%d", &L.ano_publi);

            if (L.ano_publi >= 1000 && L.ano_publi <= 2024)
            {
                fwrite(&L, sizeof(Livros), 1, Ptr);
                printf("LIVRO CADASTRADO!\n");
            }
            else
            {
                printf("ANO DE PUBLICAÇÃO INVÁLIDO! Data limite até 2024.\n");
            }
        }
        else
        {
            printf("ID já cadastrado!\n");
        }

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
								printf("LIVRO COM ID %d N?O ENCONTRADO!\n",ChaveID);
							}
						}
					}while(ChaveID>0);
				}
			}else{
				printf("AUTOR J? CADASTRADO!\n");
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
						printf("ENDERE?O: "); fflush(stdin);
						gets(P.endereco);				
						fwrite(&P,sizeof(Pessoa),1,Ptr);	
						printf("PESSOA CADASTRADA!\n");
					}else{
						printf("TELEFONE INV?LIDO!\n");
						fclose(Ptr);
					}
				}else{
					printf("TELEFONE INV?LIDO!\n"); 
					fclose(Ptr);
				}			
			}else
				printf("PESSOA J? CADASTRADA!\n");
			
			getch();
			printf("ID DA PESSOA: ");
			scanf("%d",&P.id_pessoa);
		}
	fclose(Ptr);
}

void AlterarAutor(void)
{
    LivroAutor LA;
    Autor A;
    int pos;
    FILE *PtrL = fopen("Livros.dat", "rb+");
    FILE *PtrLA = fopen("AutorLivro.dat", "rb+");
    FILE *Ptr = fopen("Autor.dat", "rb+");
    
    printf("## ALTERAR POR I.D ##\n");
    printf("ID DO AUTOR PARA ALTERAR: ");
    scanf("%d", &A.id_autor);
    
    while (A.id_autor > 0)
    {
        pos = BuscaAutor(Ptr, A.id_autor);
        if (pos == -1)
        {
            printf("I.D NÃO ENCONTRADO!\n");
        }
        else
        {
            fseek(Ptr, pos, SEEK_SET);
            fread(&A, sizeof(Autor), 1, Ptr);
            printf("## DADOS ENCONTRADOS! ##\n");
            printf("NOME DO AUTOR: %s\n", A.nome);
            printf("NACIONALIDADE: %s\n", A.nacionalidade);

            printf("\nDESEJA ALTERAR (S/N)? ");
            if (toupper(getchar()) == 'S')
            {
                printf("\nNOVO I.D: ");
                scanf("%d", &A.id_autor);
                printf("NOVO NOME: ");
                fflush(stdin);
                gets(A.nome);
    
                printf("NOVA NACIONALIDADE: ");
                fflush(stdin);
                gets(A.nacionalidade);
                
                fseek(Ptr, pos, SEEK_SET);
                fwrite(&A, sizeof(Autor), 1, Ptr);

                fseek(PtrLA, 0, SEEK_SET);
                while (fread(&LA, sizeof(LivroAutor), 1, PtrLA) == 1)
                {
                    if (LA.id_autor == A.id_autor)
                    {
                        fseek(PtrLA, -sizeof(LivroAutor), SEEK_CUR);
                        fwrite(&LA, sizeof(LivroAutor), 1, PtrLA);
                    }
                }

                printf("\nDADOS ATUALIZADOS!\n");
                printf("NOVO I.D: %d\n", A.id_autor);
                printf("NOVO NOME: %s\n", A.nome);
                printf("NOVA NACIONALIDADE: %s\n", A.nacionalidade);
            }
        }

        printf("ID DO AUTOR PARA ALTERAR: ");
        scanf("%d", &A.id_autor);
    }

    fclose(Ptr);
    fclose(PtrL);
    fclose(PtrLA);
}


void AlterarLivro(void)
{
	LivroAutor LA;
	Livros Li;
	int pos;
	char op;
	clrscr();
    FILE *PtrL = fopen("Livros.dat", "ab+");
    FILE *PtrLA = fopen("AutorLivro.dat", "ab+");
	printf("## ALTERAR POR I.D ##\n");
	printf("ID DO LIVRO PARA ALTERAR: ");
	scanf("%d",&Li.id_livro);
		while(Li.id_livro > 0)
		{
			pos = BuscaLivro(PtrL,Li.id_livro);
			if(BuscaLivro(PtrL,Li.id_livro)==-1)
			{
				printf("I.D NÃO ENCONTRADO!\n");
			}else{
				fseek(PtrL, pos, 0);
        		fread(&Li, sizeof(Livros), 1, PtrL);
            	printf("## DADOS FORAM ENCONTRADOS! ##\n");
            	printf("NOME DO LIVRO: %s\n", Li.titulo);
            	printf("ANO DE PUBLICAÇÂO: %d\n", Li.ano_publi);

            	printf("\nDESEJA ALTERAR (S/N)? ");
            	if (toupper(getche()) == 'S')
            	{
                	printf("\nNOVO I.D: ");
                	scanf("%d", &Li.id_livro);
               		printf("NOVO TÍTULO: ");fflush(stdin);
                	gets(Li.titulo);
                	printf("NOVO ANO DE PUBLICAÇÃO: ");
                	scanf("%d",&Li.ano_publi);

                	fseek(PtrL, pos, 0);
                	fwrite(&Li, sizeof(Livros), 1, PtrL);

                	fseek(PtrLA, 0, 0);
                	while (fread(&LA, sizeof(LivroAutor), 1, PtrLA) == 1)
               		{
                    	if (LA.id_livro == Li.id_livro)
                    	{
                    	    fseek(PtrLA, -sizeof(LivroAutor), 1);
                    	    LA.id_livro = LA.id_livro; 
                    	    fwrite(&LA, sizeof(LivroAutor), 1, PtrLA);
                    	}
                	}

               		printf("\nDADOS FORAM ATUALIZADOS!\n");
                	printf("NOVO I.D: %d\n", Li.id_livro);
                	printf("NOVO TÍTULO: %s\n", Li.titulo);
                	printf("NOVO ANO DE PUBLICAÇÃO: %s\n", Li.ano_publi);
            	}
        	}	

        getch();
        printf("ID DO LIVRO PARA ALTERAR: ");
        scanf("%d", &Li.id_livro);
    }
    fclose(PtrL);
    fclose(PtrLA);
}

void AlterarPessoa(void)
{
	Pessoa P;
	int pos;
	char op;
	clrscr();
    FILE *PtrP = fopen("Pessoas.dat", "ab+");
	printf("## ALTERAR POR I.D ##\n");
	printf("ID DA PESSOA PARA ALTERAR: ");
	scanf("%d",&P.id_pessoa);
		while(P.id_pessoa > 0)
		{
			pos = BuscaPessoa(PtrP,P.id_pessoa);
			if(BuscaPessoa(PtrP,P.id_pessoa)==-1)
			{
				printf("I.D NÃO ENCONTRADO!\n");
			}else{
				fseek(PtrP, pos, 0);
				fread(&P,sizeof(Pessoa),1,PtrP);
        		printf("\nDADOS FORAM ENCONTRADOS!\n");
                printf("I.D: %d\n", P.id_pessoa);
               	printf("NOME: %s\n", P.nome);
              	printf("TELEFONE: %s\n", P.telefone);
               	printf("ENDEREÇO: %s\n", P.endereco);
            	
            	printf("\nDESEJA ALTERAR (S/N)? ");
            	if (toupper(getche()) == 'S')
            	{
                	printf("\nNOVO I.D: ");
                	scanf("%d", &P.id_pessoa);
                	printf("NOVO NOME: "); fflush(stdin);
                	gets(P.nome);
               		printf("NOVO TELEFONE: ");fflush(stdin);
                	gets(P.telefone);
                	printf("NOVO ENDEREÇO: "); fflush(stdin);
                	gets(P.endereco);

                	fseek(PtrP, pos, 0);
                	fwrite(&P, sizeof(Pessoa), 1, PtrP);

               		printf("\nDADOS FORAM ATUALIZADOS!\n");
                	printf("NOVO I.D: %d\n", P.id_pessoa);
                	printf("NOVO NOME: %s\n", P.nome);
                	printf("NOVO TELEFONE: %s\n", P.telefone);
                	printf("NOVO ENDEREÇO: %s\n", P.endereco);
            	}
        	}	

        getch();
        printf("ID DA PESSOA PARA ALTERAR: ");
        scanf("%d", &P.id_pessoa);
    }
    fclose(PtrP);
}

void RealizarEmprestimo(void) {
    Livros Li;
    Emprestimo Em;
    Pessoa P;
    clrscr();

    FILE *PtrLi = fopen("Livros.dat", "rb");
    FILE *PtrEm = fopen("Emprestimos.dat", "ab+");
    FILE *PtrPe = fopen("Pessoas.dat", "rb");

    printf("## EFETUAR EMPRÉSTIMOS ##\n");
    printf("I.D PESSOA: \n");
    scanf("%d", &P.id_pessoa);

    if (BuscaPessoa(PtrPe, P.id_pessoa) != 1) {
        printf("## PESSOA ENCONTRADA! ##\n");
        printf("I.D: %d\n", P.id_pessoa);
        printf("NOME: %s\n", P.nome);
        printf("TELEFONE: %s\n", P.telefone);
        printf("ENDEREÇO: %s\n", P.endereco);
        printf("REALIZAR EMPRÉSTIMO (S/N)? ");
        
        if (toupper(getche()) == 'S') {
            printf("\nI.D DO LIVRO PARA EMPRÉSTIMO:\n ");
            scanf("%d", &Li.id_livro);

            if (BuscaLivro(PtrLi, Li.id_livro) != 1) {
                printf("LIVRO ENCONTRADO!\n");
                printf("I.D: %d\n", Li.id_livro);
                printf("TÍTULO: %s\n", Li.titulo);
                printf("ANO DE PUBLICAÇÃO: %d\n", Li.ano_publi);

                printf("CONFIRMAR EMPRÉSTIMO DO LIVRO '%s' PARA '%s' (S/N)? ", Li.titulo, P.nome);

                if (toupper(getche()) == 'S') {

                    printf("\nDigite o ID do Empréstimo: ");
                    scanf("%d", &Em.id_emprestimo);

                    printf("\nI.D: %d\n", P.id_pessoa);
                    printf("NOME: %s\n", P.nome);
                    printf("TELEFONE: %s\n", P.telefone);
                    printf("ENDEREÇO: %s\n", P.endereco);
                    printf("I.D: %d\n", Li.id_livro);
                    printf("TÍTULO: %s\n", Li.titulo);
                    printf("ANO DE PUBLICAÇÃO: %d\n", Li.ano_publi);

                    printf("QUAL O DIA DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.dia);
                    printf("QUAL O MÊS DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.mes);
                    printf("QUAL O ANO DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.ano);

                    int diasNoMes;
                    if (Em.mes < 1 || Em.mes > 12) {
                        printf("MÊS INVÁLIDO! O MÊS DEVE SER ENTRE 1 E 12.\n");
                    } else {
                        if (Em.mes == 1 || Em.mes == 3 || Em.mes == 5 || Em.mes == 7 || Em.mes == 8 || Em.mes == 10 || Em.mes == 12) {
                            diasNoMes = 31;
                        } else if (Em.mes == 4 || Em.mes == 6 || Em.mes == 9 || Em.mes == 11) {
                            diasNoMes = 30;
                        } else {
                            if ((Em.ano % 4 == 0 && Em.ano % 100 != 0) || (Em.ano % 400 == 0)) {
                                diasNoMes = 29;
                            } else {
                                diasNoMes = 28;
                            }
                        }

                        if (Em.dia < 1 || Em.dia > diasNoMes) {
                            printf("DIA INVÁLIDO! ESTE MÊS POSSUI APENAS %d DIAS.\n", diasNoMes);
                        } else {
                            // Transforma número para string
                            sprintf(Em.data_emprestimo, "%02d/%02d/%04d", Em.dia, Em.mes, Em.ano);

                            fwrite(&Em, sizeof(Emprestimo), 1, PtrEm);

                            printf("I.D: %d\n", P.id_pessoa);
                            printf("NOME: %s\n", P.nome);
                            printf("TELEFONE: %s\n", P.telefone);
                            printf("ENDEREÇO: %s\n", P.endereco);
                            printf("I.D: %d\n", Li.id_livro);
                            printf("TÍTULO: %s\n", Li.titulo);
                            printf("ANO DE PUBLICAÇÃO: %d\n", Li.ano_publi);
                            printf("EMPRÉSTIMO REGISTRADO PARA: %s\n", Em.data_emprestimo);
                        }
                    }

                    printf("\nQUAL O DIA DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.dia);
                    printf("QUAL O MÊS DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.mes);
                    printf("QUAL O ANO DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.ano);

                    if (Em.mes < 1 || Em.mes > 12) {
                        printf("MÊS INVÁLIDO! O MÊS DEVE SER ENTRE 1 E 12.\n");
                    } else {
                        if (Em.mes == 1 || Em.mes == 3 || Em.mes == 5 || Em.mes == 7 || Em.mes == 8 || Em.mes == 10 || Em.mes == 12) {
                            diasNoMes = 31;
                        } else if (Em.mes == 4 || Em.mes == 6 || Em.mes == 9 || Em.mes == 11) {
                            diasNoMes = 30;
                        } else {
                            if ((Em.ano % 4 == 0 && Em.ano % 100 != 0) || (Em.ano % 400 == 0)) {
                                diasNoMes = 29;
                            } else {
                                diasNoMes = 28;
                            }
                        }

                        if (Em.dia < 1 || Em.dia > diasNoMes) {
                            printf("DIA INVÁLIDO! ESTE MÊS POSSUI APENAS %d DIAS.\n", diasNoMes);
                        } else {
                            sprintf(Em.data_devolucao, "%02d/%02d/%04d", Em.dia, Em.mes, Em.ano);

                            printf("EMPRÉSTIMO CONCEDIDO! DEVOLUÇÃO AGENDADA PARA: %s\n", Em.data_devolucao);
                            fwrite(&Em, sizeof(Emprestimo), 1, PtrEm);
                        }
                    }
                } else {
                    printf("\nEMPRÉSTIMO CANCELADO!\n");
                }
            } else {
                printf("\nLIVRO NÃO ENCONTRADO!\n");
            }
        } else {
            printf("\nEMPRÉSTIMO NÃO AUTORIZADO!\n");
        }
    } else {
        printf("\nPESSOA NÃO ENCONTRADA!\n");
    }

    fclose(PtrLi);
    fclose(PtrPe);
    fclose(PtrEm);
    getch();
}


void ConsultaAutor()
{
	Autor A;
	int pos;
	FILE *PtrA = fopen("Autor.dat","rb");
	clrscr();
	printf("\n## CONSULTA DE AUTORES ##\n");
	printf("I.D DO AUTOR: ");
	scanf("%d",&A.id_autor);
	while(A.id_autor > 0)
	{
		pos = BuscaAutor(PtrA, A.id_autor);
		if(pos==-1)
		{
			printf("I.D NÃO ENCONTRADO!\n");
		}else{
			fseek(PtrA,pos,0);
			fread(&A,sizeof(Autor),1,PtrA);
			printf("\nDADOS ENCONTRADOS!\n");
			printf("I.D AUTOR: %d \n",A.id_autor);
			printf("NOME DO AUTOR : %s \n",A.nome);
			printf("NACIONALIDADE: %s \n",A.nacionalidade);
			fwrite(&A,sizeof(Autor),1,PtrA);
		}
		printf("I.D DO AUTOR: ");
		scanf("%d",&A.id_autor);	
	}
	getch();
	fclose(PtrA);
}


void ConsultaLivro()
{
    Livros L;
    int pos;
    FILE *PtrL = fopen("Livros.dat", "rb");
    clrscr();
    printf("\n## CONSULTA DE LIVROS ##\n");
    printf("I.D DO LIVRO: ");
    scanf("%d", &L.id_livro);
    
    while (L.id_livro > 0) {
        pos = BuscaLivro(PtrL, L.id_livro);
        if (pos == -1) {
            printf("I.D NÃO ENCONTRADO!\n");
        } else {
            fseek(PtrL, pos, 0);
            fread(&L, sizeof(Livros), 1, PtrL);
            printf("\nDADOS ENCONTRADOS!\n");
            printf("I.D DO LIVRO: %d\n", L.id_livro);
            printf("TÍTULO: %s\n", L.titulo);
            printf("ANO DE PUBLICAÇÃO: %d\n", L.ano_publi);
        }
    	printf("I.D DO LIVRO: ");
    	scanf("%d", &L.id_livro);
    }
    getch();
    fclose(PtrL);
}


void ConsultaPessoa()
{
    Pessoa P;
    int pos;
    FILE *PtrP = fopen("Pessoas.dat", "rb");
    clrscr();
    printf("\n## CONSULTA DE PESSOAS ##\n");
    printf("I.D DA PESSOA: ");
    scanf("%d", &P.id_pessoa);
    
    while (P.id_pessoa > 0) {
        pos = BuscaPessoa(PtrP, P.id_pessoa);
        if (pos == -1) {
            printf("I.D NÃO ENCONTRADO!\n");
        } else {
            fseek(PtrP, pos, 0);
            fread(&P, sizeof(Pessoa), 1, PtrP);
            printf("\nDADOS ENCONTRADOS!\n");
            printf("I.D PESSOA: %d\n", P.id_pessoa);
            printf("NOME: %s\n", P.nome);
            printf("TELEFONE: %s\n", P.telefone);
            printf("ENDEREÇO: %s\n", P.endereco);
        }
    	printf("I.D DA PESSOA: ");
    	scanf("%d", &P.id_pessoa);
    }
    getch();
    fclose(PtrP);
}

void ConsultaEmprestimo() {
    Emprestimo E;
    int pos;
    FILE *PtrE = fopen("Emprestimos.dat", "rb+");

    clrscr();
    printf("\n## CONSULTA DE EMPRÉSTIMOS ##\n");
    printf("I.D DO EMPRÉSTIMO: ");
    scanf("%d", &E.id_emprestimo);

    pos = BuscaEmprestimo(PtrE, E.id_emprestimo);
    if (pos == -1) {
        printf("EMPRÉSTIMO NÃO ENCONTRADO!\n");
    } else {
        fseek(PtrE, pos, 0);  
        fread(&E, sizeof(Emprestimo), 1, PtrE);  

        printf("\nDADOS ENCONTRADOS!\n");
        printf("I.D DO EMPRÉSTIMO: %d\n", E.id_emprestimo);
        printf("ID PESSOA: %d\n", E.id_pessoa);
        printf("ID LIVRO: %d\n", E.id_livro);
        printf("DATA DE EMPRÉSTIMO: %s\n", E.data_emprestimo);
        printf("DATA DE DEVOLUÇÃO: %s\n", E.data_devolucao);
    }

    fclose(PtrE);
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
	printf("[E]EXCLUS?O LÓGICA\n");
	printf("[F]EXCLUSA FISICA\n");
	printf("[G]ALTERAÇÃO DO AUTOR POR ID\n");
	printf("[H]ALTERAÇÃO DO LIVRO POR ID\n");
	printf("[I]ALTERAÇÃO DA PESSOA POR ID\n");
	printf("[J]CONSULTAR LIVRO\n");
	printf("[K]CONSULTAR AUTOR\n");
	printf("[L]CONSULTA PESSOA\n");
	printf("[M]CONSULTAR EMPR?STIMO\n");
	printf("[N]GERAR RELAT?RIO DOS LIVROS\n");
	printf("[O]GERAR RELAT?RIO DOS AUTORES\n");
	printf("[P]GERAR RELAT?RIO DAS PESSOAS\n");
	printf("[Q]GERAR RELAT?RIO GERAL\n");
	printf("[R]GERAR RELAT?RIO POR LETRA\n");
	printf("[S]GERAR RELAT?RIO POR PALAVRA NO T?TULO\n");
	printf("[T]GERAR RELAT?RIO DE EMPR?STIMO FEITO POR UMA PESSOA\n");
	printf("[U]GERAR RELAT?RIO DE TODOS OS LIVROS DE UM AUTOR\n");
	printf("[V]GERAR RELAT?RIO DE TODOS OS EMPR?STIMOS FEITOS POR UMA PESSOA\n");
	printf("[0] PARA SAIR]\n");
	return toupper(getche());
}

int main(void)
{
	setlocale(LC_ALL,"Portuguese");
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
			case 'D': RealizarEmprestimo();
				break;
			case 'E':
				break;
			case 'F':
				break;
			case 'G': AlterarAutor();
				break;
			case 'H': AlterarLivro();
				break;
			case 'I': AlterarPessoa();
				break;
			case 'J': ConsultaLivro();
				break;
			case 'K': ConsultaAutor();
				break;
			case 'L': ConsultaPessoa();
				break;
			case 'M': ConsultaEmprestimo();
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
			case 'U':
				break;
			case 'V':
				break;				
		}
	}while(op!=27);
	
	return 0;
}
