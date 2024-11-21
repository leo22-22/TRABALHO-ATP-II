#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

struct Livros{
	int id_livro,ano_publi;
	char titulo[100];
	int ativo;
};

struct Autor{
	int id_autor;
	char nome[30],nacionalidade[30];
	int ativo;
};

struct Emprestimo{
	int id_emprestimo,id_livro,id_pessoa;
	int dia,mes,ano;
	char data_emprestimo[11];
	char data_devolucao[11];
	int ativo;
};

struct Pessoa{
	int id_pessoa;
	char nome[30],telefone[14],endereco[40];
	int ativo;
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

int BuscaLivro(FILE *Ptr, int ChaveID);
int BuscaAutor(FILE *Ptr, int ChaveID);
int BuscaAutorPorLivro(FILE *Ptr, int id_livro);
int BuscaPessoa(FILE *Ptr, int ChaveID);
int BuscaEmprestimo(FILE *Ptr, int ChaveID);

void CadastroLivros();
void CadastroAutor();
void CadastroPessoa();
void RealizarEmprestimo();
void ExclusaoLogica();
void ExclusaoFisica();
void AlterarDados();
void ConsultarDados();

void relatorios();  
void RelatorioCompleto(); 
void RelatorioAutoresCompleto();  
void RelatorioLivrosCompleto();  
void RelatorioPessoasCompleto();  
void RelatorioEmprestimosCompleto();  
void RelatorioAutoresPorLetra(char letra);
void RelatorioLivrosPorPalavra(char palavra[50]);
void RelatorioEmprestimosPorPessoa(int id_pessoa);
void RelatorioLivrosPorAutor(int id_autor);
void RelatorioEmprestimosSeparadosPorPessoa();
void desenharBordas();


void ExclusaoLogica(void) {
    int pos;
    Livros L;
    Pessoa P;
    Autor A;
    Emprestimo E;
    FILE *PtrLi = fopen("Livros.dat", "r+b");
    FILE *PtrPe = fopen("Pessoas.dat", "r+b");
    FILE *PtrAu = fopen("Autores.dat", "r+b");
    FILE *PtrEm = fopen("Emprestimos.dat", "r+b");

    clrscr();
    textcolor(WHITE);
    gotoxy(10, 2);
    printf("### Exclusao Logica (Livro, Pessoa, Autor ou Empréstimo) ###");

    if (PtrLi == NULL || PtrPe == NULL || PtrAu == NULL || PtrEm == NULL) {
        gotoxy(10, 4);
        textcolor(RED);
        printf("Erro de Abertura de Arquivo!\n");
    } else {
        char opcao;
        gotoxy(10, 5);
        textcolor(WHITE);
        printf("Escolha a opção de exclusão logica:\n");
        gotoxy(10, 7);
        printf("A - Excluir Livro");
        gotoxy(10, 8);
        printf("B - Excluir Pessoa");
        gotoxy(10, 9);
        printf("C - Excluir Autor");
        gotoxy(10, 10);
        printf("D - Excluir Empréstimo");

        gotoxy(10, 12);
        printf("Escolha a opção (A/B/C/D): ");
        opcao = toupper(getche());

        switch (opcao) {
        case 'A': 
            gotoxy(10, 14);
            printf("ID do Livro a Excluir: ");
            scanf("%d", &L.id_livro);
            pos = BuscaLivro(PtrLi, L.id_livro);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Livro nao Cadastrado!\n");
            } else {
                fseek(PtrLi, pos, SEEK_SET);
                fread(&L, sizeof(Livros), 1, PtrLi);
                if (L.ativo == 0) {
                    gotoxy(10, 18);
                    printf("Livro ja esta inativo!\n");
                } else {
                    L.ativo = 0;
                    fseek(PtrLi, pos, SEEK_SET);
                    fwrite(&L, sizeof(Livros), 1, PtrLi);
                    gotoxy(10, 18);
                    textcolor(GREEN);
                    printf("Livro excluido logicamente!\n");
                }
            }
            break;

        case 'B': 
            gotoxy(10, 14);
            printf("ID da Pessoa a Excluir: ");
            scanf("%d", &P.id_pessoa);
            pos = BuscaPessoa(PtrPe, P.id_pessoa);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Pessoa nao Cadastrada!\n");
            } else {
                fseek(PtrPe, pos, SEEK_SET);
                fread(&P, sizeof(Pessoa), 1, PtrPe);
                if (P.ativo == 0) {
                    gotoxy(10, 18);
                    printf("Pessoa ja esta inativa!\n");
                } else {
                    P.ativo = 0;
                    fseek(PtrPe, pos, SEEK_SET);
                    fwrite(&P, sizeof(Pessoa), 1, PtrPe);
                    gotoxy(10, 18);
                    textcolor(GREEN);
                    printf("Pessoa excluida logicamente!\n");
                }
            }
            break;

        case 'C': 
            gotoxy(10, 14);
            printf("ID do Autor a Excluir: ");
            scanf("%d", &A.id_autor);
            pos = BuscaAutor(PtrAu, A.id_autor);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Autor nao Cadastrado!\n");
            } else {
                fseek(PtrAu, pos, SEEK_SET);
                fread(&A, sizeof(Autor), 1, PtrAu);
                if (A.ativo == 0) {
                    gotoxy(10, 18);
                    printf("Autor ja esta inativo!\n");
                } else {
                    A.ativo = 0;
                    fseek(PtrAu, pos, SEEK_SET);
                    fwrite(&A, sizeof(Autor), 1, PtrAu);
                    gotoxy(10, 18);
                    textcolor(GREEN);
                    printf("Autor excluido logicamente!\n");
                }
            }
            break;

        case 'D': 
            gotoxy(10, 14);
            printf("ID do Emprestimo a Excluir: ");
            scanf("%d", &E.id_emprestimo);
            pos = BuscaEmprestimo(PtrEm, E.id_emprestimo);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Emprestimo nao Cadastrado!\n");
            } else {
                fseek(PtrEm, pos, SEEK_SET);
                fread(&E, sizeof(Emprestimo), 1, PtrEm);
                if (E.ativo == 0) {
                    gotoxy(10, 18);
                    printf("Emprestimo ja esta inativo!\n");
                } else {
                    E.ativo = 0;
                    fseek(PtrEm, pos, SEEK_SET);
                    fwrite(&E, sizeof(Emprestimo), 1, PtrEm);
                    gotoxy(10, 18);
                    textcolor(GREEN);
                    printf("Emprestimo excluido logicamente!\n");
                }
            }
            break;

        default:
            gotoxy(10, 14);
            textcolor(RED);
            printf("Opcao Invalida!\n");
            break;
        }
    }
    getch();
    fclose(PtrLi);
    fclose(PtrPe);
    fclose(PtrAu);
    fclose(PtrEm);
}


void ExclusaoFisica(void)
{
    int pos;
    Livros L;
    Pessoa P;
    Autor A;
    Emprestimo E;
    FILE *PtrLi = fopen("Livros.dat", "r+b");
    FILE *PtrPe = fopen("Pessoas.dat", "r+b");
    FILE *PtrAu = fopen("Autores.dat", "r+b");
    FILE *PtrEm = fopen("Emprestimos.dat", "r+b");

    clrscr();
    textcolor(WHITE); 
    gotoxy(10, 2); 
    printf("### Exclusao Fisica (Livro, Pessoa, Autor ou Empréstimo) ###");

    if (PtrLi == NULL || PtrPe == NULL || PtrAu == NULL || PtrEm == NULL) {
        gotoxy(10, 4);
        textcolor(RED);
        printf("Erro de Abertura de Arquivo!\n");
    } else {
        char opcao;
        gotoxy(10, 5);
        textcolor(WHITE);
        printf("Escolha a opção de exclusão fisica:\n");
        gotoxy(10, 7);
        printf("A - Excluir Livro");
        gotoxy(10, 8);
        printf("B - Excluir Pessoa");
        gotoxy(10, 9);
        printf("C - Excluir Autor");
        gotoxy(10, 10);
        printf("D - Excluir Empréstimo");

        gotoxy(10, 12);
        printf("Escolha a opção (A/B/C/D): ");
        opcao = toupper(getche());

        switch (opcao) {
        case 'A': // Excluir Livro
            gotoxy(10, 14);
            printf("ID do Livro a Excluir: ");
            scanf("%d", &L.id_livro);
            pos = BuscaLivro(PtrLi, L.id_livro);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Livro nao Cadastrado!\n");
            } else {
                fseek(PtrLi, pos, SEEK_SET);
                fread(&L, sizeof(Livros), 1, PtrLi);
                gotoxy(10, 16);
                printf("Dados do Livro:\n");
                gotoxy(10, 17);
                printf("ID Livro: %d", L.id_livro);
                gotoxy(10, 18);
                printf("Titulo: %s", L.titulo);
                gotoxy(10, 19);
                printf("Ano de Publicacao: %d", L.ano_publi);
                gotoxy(10, 20);
                printf("Confirma Exclusao Fisica de Livro (S/N)? ");
                if (toupper(getche()) == 'S') {
                    rewind(PtrLi); 
                    FILE *PtrTempLi = fopen("TempLivros.dat", "wb");
                    while (fread(&L, sizeof(Livros), 1, PtrLi) == 1) {
                        if (L.id_livro != L.id_livro) // Corrigido para comparação correta
                            fwrite(&L, sizeof(Livros), 1, PtrTempLi);
                    }
                    fclose(PtrLi);
                    fclose(PtrTempLi);
                    remove("Livros.dat");
                    rename("TempLivros.dat", "Livros.dat");
                    gotoxy(10, 22);
                    textcolor(GREEN);
                    printf("Livro excluido fisicamente!\n");
                }
            }
            break;

        case 'B': // Excluir Pessoa
            gotoxy(10, 14);
            printf("ID da Pessoa a Excluir: ");
            scanf("%d", &P.id_pessoa);
            pos = BuscaPessoa(PtrPe, P.id_pessoa);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Pessoa nao Cadastrada!\n");
            } else {
                fseek(PtrPe, pos, SEEK_SET);
                fread(&P, sizeof(Pessoa), 1, PtrPe);
                gotoxy(10, 16);
                printf("Dados da Pessoa:\n");
                gotoxy(10, 17);
                printf("ID Pessoa: %d", P.id_pessoa);
                gotoxy(10, 18);
                printf("Nome: %s", P.nome);
                gotoxy(10, 19);
                printf("Telefone: %s", P.telefone);
                gotoxy(10, 20);
                printf("Endereco: %s", P.endereco);
                gotoxy(10, 21);
                printf("Confirma Exclusao Fisica de Pessoa (S/N)? ");
                if (toupper(getche()) == 'S') {
                    rewind(PtrPe); 
                    FILE *PtrTempPe = fopen("TempPessoas.dat", "wb");
                    while (fread(&P, sizeof(Pessoa), 1, PtrPe) == 1) {
                        if (P.id_pessoa != P.id_pessoa) // Corrigido para comparação correta
                            fwrite(&P, sizeof(Pessoa), 1, PtrTempPe);
                    }
                    fclose(PtrPe);
                    fclose(PtrTempPe);
                    remove("Pessoas.dat");
                    rename("TempPessoas.dat", "Pessoas.dat");
                    gotoxy(10, 23);
                    textcolor(GREEN);
                    printf("Pessoa excluida fisicamente!\n");
                }
            }
            break;

        case 'C': // Excluir Autor
            gotoxy(10, 14);
            printf("ID do Autor a Excluir: ");
            scanf("%d", &A.id_autor);
            pos = BuscaAutor(PtrAu, A.id_autor);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Autor nao Cadastrado!\n");
            } else {
                fseek(PtrAu, pos, SEEK_SET);
                fread(&A, sizeof(Autor), 1, PtrAu);
                gotoxy(10, 16);
                printf("Dados do Autor:\n");
                gotoxy(10, 17);
                printf("ID Autor: %d", A.id_autor);
                gotoxy(10, 18);
                printf("Nome: %s", A.nome);
                gotoxy(10, 19);
                printf("Nacionalidade: %s", A.nacionalidade);
                gotoxy(10, 20);
                printf("Confirma Exclusao Fisica de Autor (S/N)? ");
                if (toupper(getche()) == 'S') {
                    rewind(PtrAu); 
                    FILE *PtrTempAu = fopen("TempAutores.dat", "wb");
                    while (fread(&A, sizeof(Autor), 1, PtrAu) == 1) {
                        if (A.id_autor != A.id_autor) // Corrigido para comparação correta
                            fwrite(&A, sizeof(Autor), 1, PtrTempAu);
                    }
                    fclose(PtrAu);
                    fclose(PtrTempAu);
                    remove("Autores.dat");
                    rename("TempAutores.dat", "Autores.dat");
                    gotoxy(10, 22);
                    textcolor(GREEN);
                    printf("Autor excluido fisicamente!\n");
                }
            }
            break;

        case 'D': // Excluir Emprestimo
            gotoxy(10, 14);
            printf("ID do Emprestimo a Excluir: ");
            scanf("%d", &E.id_emprestimo);
            pos = BuscaEmprestimo(PtrEm, E.id_emprestimo);
            if (pos == -1) {
                gotoxy(10, 16);
                printf("Emprestimo nao Cadastrado!\n");
            } else {
                fseek(PtrEm, pos, SEEK_SET);
                fread(&E, sizeof(Emprestimo), 1, PtrEm);
                gotoxy(10, 16);
                printf("Dados do Emprestimo:\n");
                gotoxy(10, 17);
                printf("ID Emprestimo: %d", E.id_emprestimo);
                gotoxy(10, 18);
                printf("ID Livro: %d", E.id_livro);
                gotoxy(10, 19);
                printf("ID Pessoa: %d", E.id_pessoa);
                gotoxy(10, 20);
                printf("Data de Emprestimo: %s", E.data_emprestimo);
                gotoxy(10, 21);
                printf("Data de Devolucao: %s", E.data_devolucao);
                gotoxy(10, 22);
                printf("Confirma Exclusao Fisica de Emprestimo (S/N)? ");
                if (toupper(getche()) == 'S') {
                    rewind(PtrEm); 
                    FILE *PtrTempEm = fopen("TempEmprestimos.dat", "wb");
                    while (fread(&E, sizeof(Emprestimo), 1, PtrEm) == 1) {
                        if (E.id_emprestimo != E.id_emprestimo) // Corrigido para comparação correta
                            fwrite(&E, sizeof(Emprestimo), 1, PtrTempEm);
                    }
                    fclose(PtrEm);
                    fclose(PtrTempEm);
                    remove("Emprestimos.dat");
                    rename("TempEmprestimos.dat", "Emprestimos.dat");
                    gotoxy(10, 24);
                    textcolor(GREEN);
                    printf("Emprestimo excluido fisicamente!\n");
                }
            }
            break;

        default:
            gotoxy(10, 12);
            printf("Opcao Invalida!\n");
            break;
        }
    }
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
    rewind(Ptr);  
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
    FILE *Ptr = fopen("Livros.dat", "rb+");

    if (Ptr == NULL) {
        printf("Erro ao abrir o arquivo Livros.dat\n");
        gotoxy(5, 15);
        printf("Pressione qualquer tecla para sair...\n");
        getch();
    } else {
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## CADASTRO DE LIVROS ##\n");
        gotoxy(5, 5);
        printf("ID DO LIVRO: ");
        scanf("%d", &L.id_livro);

        while (L.id_livro > 0)
        {
            if (BuscaLivro(Ptr, L.id_livro) == -1)
            {
                int titulo_valido = 0;
                while (!titulo_valido)
                {
                    gotoxy(5, 7);
                    printf("NOME DO LIVRO: ");
                    fflush(stdin);
                    fgets(L.titulo, sizeof(L.titulo), stdin);
                    L.titulo[strcspn(L.titulo, "\n")] = '\0'; // Remove o '\n' gerado pelo fgets

                    titulo_valido = 1;
                    for (int i = 0; L.titulo[i] != '\0'; i++)
                    {
                        if (!((L.titulo[i] >= 'A' && L.titulo[i] <= 'Z') || 
                              (L.titulo[i] >= 'a' && L.titulo[i] <= 'z') || 
                              L.titulo[i] == ' '))  // Verifica caracteres válidos
                        {
                            titulo_valido = 0;
                            gotoxy(5, 9);
                            printf("TÍTULO INVÁLIDO! Use apenas letras e espaços.\n");
                            break;
                        }
                    }
                }

                gotoxy(5, 11);
                printf("ANO DE PUBLICAÇÃO (XXXX): ");
                scanf("%d", &L.ano_publi);

                if (L.ano_publi >= 1000 && L.ano_publi <= 2024)
                {
                    // Marca o livro como ativo (não excluído)
                    L.ativo = 1;
                    
                    fseek(Ptr, 0, SEEK_END);  // Move para o final do arquivo antes de adicionar
                    fwrite(&L, sizeof(Livros), 1, Ptr);
                    gotoxy(5, 13);
                    printf("LIVRO CADASTRADO!\n");
                }
                else
                {
                    gotoxy(5, 13);
                    printf("ANO DE PUBLICAÇÃO INVÁLIDO! Data limite até 2024.\n");
                }
            }
            else
            {
                gotoxy(5, 13);
                printf("ID já cadastrado!\n");
            }

            gotoxy(5, 15);
            printf("ID DO LIVRO: ");
            scanf("%d", &L.id_livro);
        }
    }
    fclose(Ptr);
}

void CadastroPessoa(void)
{
    Pessoa P;
    FILE *Ptr = fopen("Pessoas.dat", "rb+");

    if (Ptr == NULL) {
        printf("Erro ao abrir o arquivo Pessoas.dat\n");
        gotoxy(5, 15);
        printf("Pressione qualquer tecla para sair...\n");
        getch();
    } else {
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## CADASTRO DE PESSOAS ##\n");
        gotoxy(5, 5);
        printf("ID DA PESSOA: ");
        scanf("%d", &P.id_pessoa);

        while (P.id_pessoa > 0)
        {
            if (BuscaPessoa(Ptr, P.id_pessoa) == -1)
            {
                gotoxy(5, 7);
                printf("NOME DA PESSOA: "); fflush(stdin);
                fgets(P.nome, sizeof(P.nome), stdin);
                P.nome[strcspn(P.nome, "\n")] = '\0';  // Remove o '\n'
                gotoxy(5, 9);
                printf("TELEFONE((XX)XXXXX-XXXX): "); fflush(stdin);
                fgets(P.telefone, sizeof(P.telefone), stdin);
                P.telefone[strcspn(P.telefone, "\n")] = '\0';  // Remove o '\n'

                if (strlen(P.telefone) == 14)
                {
                    if (P.telefone[0] == '(' || P.telefone[3] == ')' || P.telefone[9] == '-')
                    {
                        gotoxy(5, 11);
                        printf("ENDEREÇO: "); fflush(stdin);
                        fgets(P.endereco, sizeof(P.endereco), stdin);
                        P.endereco[strcspn(P.endereco, "\n")] = '\0';  // Remove o '\n'

                        // Marca a pessoa como ativa (não excluída)
                        P.ativo = 1;

                        fseek(Ptr, 0, SEEK_END);  // Move para o final do arquivo antes de adicionar
                        fwrite(&P, sizeof(Pessoa), 1, Ptr);
                        gotoxy(5, 13);
                        printf("PESSOA CADASTRADA!\n");
                    }
                    else
                    {
                        gotoxy(5, 13);
                        printf("TELEFONE INVÁLIDO!\n");
                    }
                }
                else
                {
                    gotoxy(5, 13);
                    printf("TELEFONE INVÁLIDO!\n");
                }            
            }
            else
            {
                gotoxy(5, 13);
                printf("PESSOA JÁ CADASTRADA!\n");
            }

            gotoxy(5, 15);
            getch();
            gotoxy(5, 17);
            printf("ID DA PESSOA: ");
            scanf("%d", &P.id_pessoa);
        }
    }

    fclose(Ptr);
}

void CadastroAutor(void)
{
    Autor A;
    FILE *Ptr = fopen("Autor.dat", "rb+");
	clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## CADASTRO DE AUTORES ##\n");
        gotoxy(5, 5);
        printf("ID DO AUTOR: ");
        scanf("%d", &A.id_autor);

        while (A.id_autor > 0)
        {
            if (BuscaAutor(Ptr, A.id_autor) == -1)
            {
                gotoxy(5, 7);
                printf("NOME DO AUTOR: "); fflush(stdin);
                fgets(A.nome, sizeof(A.nome), stdin);
                A.nome[strcspn(A.nome, "\n")] = '\0';  // Remove o '\n'
                gotoxy(5, 9);
                printf("NACIONALIDADE: "); fflush(stdin);
                fgets(A.nacionalidade, sizeof(A.nacionalidade), stdin);
                A.nacionalidade[strcspn(A.nacionalidade, "\n")] = '\0';  // Remove o '\n'
                
                A.ativo = 1;

                fseek(Ptr, 0, SEEK_END);  
                fwrite(&A, sizeof(Autor), 1, Ptr);
                gotoxy(5, 11);
                printf("AUTOR CADASTRADO!\n");
            }
            else
            {
                gotoxy(5, 11);
                printf("AUTOR JÁ CADASTRADO!\n");
            }

            gotoxy(5, 13);
            getch();
            gotoxy(5, 15);
            printf("ID DO AUTOR: ");
            scanf("%d", &A.id_autor);
        }

    fclose(Ptr);
}


void AlterarDados(void)
{
    LivroAutor LA;
    Livros Li;
    Pessoa P;
    Autor A;
    int pos;
    char op;

    FILE *PtrL = fopen("Livros.dat", "rb+");
    FILE *PtrLA = fopen("AutorLivro.dat", "rb+");
    FILE *PtrP = fopen("Pessoas.dat", "rb+");
    FILE *Ptr = fopen("Autor.dat", "rb+");

    if (PtrL == NULL || PtrLA == NULL || PtrP == NULL || Ptr == NULL)
    {
        textbackground(RED);
        textcolor(WHITE);
        gotoxy(5, 5);
        printf("\nErro ao abrir os arquivos!\n");
        getch();
    }
    else
    {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## ALTERAR DADOS ##\n");
        gotoxy(5, 5);
        printf("Escolha a opção de alteração:\n");
        gotoxy(5, 6);
        printf("A - Alterar Autor\n");
        gotoxy(5, 7);
        printf("B - Alterar Livro\n");
        gotoxy(5, 8);
        printf("C - Alterar Pessoa\n");
        gotoxy(5, 9);
        printf("Escolha a opção (A/B/C): ");
        op = toupper(getche());

        switch (op)
        {
        case 'A':
            gotoxy(5, 11);
            printf("\nID DO AUTOR PARA ALTERAR: ");
            scanf("%d", &A.id_autor);

            while (A.id_autor > 0)
            {
                pos = BuscaAutor(Ptr, A.id_autor);
                if (pos == -1)
                {
                    gotoxy(5, 13);
                    printf("I.D NÃO ENCONTRADO!\n");
                }
                else
                {
                    fseek(Ptr, pos, 0);
                    fread(&A, sizeof(Autor), 1, Ptr);
                    gotoxy(5, 13);
                    printf("## DADOS ENCONTRADOS! ##\n");
                    printf("NOME DO AUTOR: %s\n", A.nome);
                    printf("NACIONALIDADE: %s\n", A.nacionalidade);

                    gotoxy(5, 15);
                    printf("\nDESEJA ALTERAR (S/N)? ");
                    if (toupper(getche()) == 'S')
                    {
                        gotoxy(5, 17);
                        printf("\nNOVO I.D: ");
                        scanf("%d", &A.id_autor);
                        gotoxy(5, 18);
                        printf("NOVO NOME: ");
                        fflush(stdin);
                        gets(A.nome);
                        gotoxy(5, 19);
                        printf("NOVA NACIONALIDADE: ");
                        fflush(stdin);
                        gets(A.nacionalidade);

                        fseek(Ptr, pos, 0);
                        fwrite(&A, sizeof(Autor), 1, Ptr);

                        fseek(PtrLA, 0, SEEK_SET);
                        while (fread(&LA, sizeof(LivroAutor), 1, PtrLA) == 1)
                        {
                            if (LA.id_autor == A.id_autor)
                            {
                                fseek(PtrLA, -sizeof(LivroAutor), 1);
                                fwrite(&LA, sizeof(LivroAutor), 1, PtrLA);
                            }
                        }

                        gotoxy(5, 21);
                        printf("\nDADOS ATUALIZADOS!\n");
                    }
                }

                gotoxy(5, 23);
                printf("\nID DO AUTOR PARA ALTERAR: ");
                scanf("%d", &A.id_autor);
            }
            break;

        case 'B':
            gotoxy(5, 11);
            printf("\nID DO LIVRO PARA ALTERAR: ");
            scanf("%d", &Li.id_livro);

            while (Li.id_livro > 0)
            {
                pos = BuscaLivro(PtrL, Li.id_livro);
                if (pos == -1)
                {
                    gotoxy(5, 13);
                    printf("I.D NÃO ENCONTRADO!\n");
                }
                else
                {
                    fseek(PtrL, pos, 0);
                    fread(&Li, sizeof(Livros), 1, PtrL);
                    gotoxy(5, 13);
                    printf("## DADOS ENCONTRADOS! ##\n");
                    printf("TÍTULO DO LIVRO: %s\n", Li.titulo);
                    printf("ANO DE PUBLICAÇÃO: %d\n", Li.ano_publi);

                    gotoxy(5, 15);
                    printf("\nDESEJA ALTERAR (S/N)? ");
                    if (toupper(getche()) == 'S')
                    {
                        gotoxy(5, 17);
                        printf("\nNOVO I.D: ");
                        scanf("%d", &Li.id_livro);
                        gotoxy(5, 18);
                        printf("NOVO TÍTULO: ");
                        fflush(stdin);
                        gets(Li.titulo);
                        gotoxy(5, 19);
                        printf("NOVO ANO DE PUBLICAÇÃO: ");
                        scanf("%d", &Li.ano_publi);

                        fseek(PtrL, pos, 0);
                        fwrite(&Li, sizeof(Livros), 1, PtrL);

                        fseek(PtrLA, 0, 0);
                        while (fread(&LA, sizeof(LivroAutor), 1, PtrLA) == 1)
                        {
                            if (LA.id_livro == Li.id_livro)
                            {
                                fseek(PtrLA, -sizeof(LivroAutor), 1);
                                fwrite(&LA, sizeof(LivroAutor), 1, PtrLA);
                            }
                        }

                        gotoxy(5, 21);
                        printf("\nDADOS ATUALIZADOS!\n");
                    }
                }

                gotoxy(5, 23);
                printf("\nID DO LIVRO PARA ALTERAR: ");
                scanf("%d", &Li.id_livro);
            }
            break;

        case 'C':
            gotoxy(5, 11);
            printf("\nID DA PESSOA PARA ALTERAR: ");
            scanf("%d", &P.id_pessoa);

            while (P.id_pessoa > 0)
            {
                pos = BuscaPessoa(PtrP, P.id_pessoa);
                if (pos == -1)
                {
                    gotoxy(5, 13);
                    printf("I.D NÃO ENCONTRADO!\n");
                }
                else
                {
                    fseek(PtrP, pos, 0);
                    fread(&P, sizeof(Pessoa), 1, PtrP);
                    gotoxy(5, 13);
                    printf("## DADOS ENCONTRADOS! ##\n");
                    printf("I.D: %d\n", P.id_pessoa);
                    printf("NOME: %s\n", P.nome);
                    printf("TELEFONE: %s\n", P.telefone);
                    printf("ENDEREÇO: %s\n", P.endereco);

                    gotoxy(5, 15);
                    printf("\nDESEJA ALTERAR (S/N)? ");
                    if (toupper(getche()) == 'S')
                    {
                        gotoxy(5, 17);
                        printf("\nNOVO I.D: ");
                        scanf("%d", &P.id_pessoa);
                        gotoxy(5, 18);
                        printf("NOVO NOME: ");
                        fflush(stdin);
                        gets(P.nome);
                        gotoxy(5, 19);
                        printf("NOVO TELEFONE: ");
                        fflush(stdin);
                        gets(P.telefone);
                        gotoxy(5, 20);
                        printf("NOVO ENDEREÇO: ");
                        fflush(stdin);
                        gets(P.endereco);

                        fseek(PtrP, pos, 0);
                        fwrite(&P, sizeof(Pessoa), 1, PtrP);

                        gotoxy(5, 22);
                        printf("\nDADOS ATUALIZADOS!\n");
                    }
                }

                gotoxy(5, 23);
                printf("\nID DA PESSOA PARA ALTERAR: ");
                scanf("%d", &P.id_pessoa);
            }
            break;

        default:
            gotoxy(5, 25);
            printf("\nOpção inválida!\n");
            break;
        }

        fclose(PtrL);
        fclose(PtrLA);
        fclose(PtrP);
        fclose(Ptr);
        getch(); 
    }
}



void RealizarEmprestimo(void) {
    Livros Li;
    Emprestimo Em;
    Pessoa P;
    clrscr(); // Limpa a tela

    textbackground(CYAN); 
    textcolor(YELLOW);    
    clrscr(); 

    FILE *PtrLi = fopen("Livros.dat", "rb");
    FILE *PtrEm = fopen("Emprestimos.dat", "ab+");
    FILE *PtrPe = fopen("Pessoas.dat", "rb");

    gotoxy(30, 2);
    cprintf("## EFETUAR EMPRÉSTIMOS ##");

    gotoxy(5, 4); 
    printf("I.D PESSOA: ");
    scanf("%d", &P.id_pessoa);

    if (BuscaPessoa(PtrPe, P.id_pessoa) != 1) {
        gotoxy(5, 6); 
        printf("## PESSOA ENCONTRADA! ##\n");
        gotoxy(5, 7);
        printf("I.D: %d\n", P.id_pessoa);
        gotoxy(5, 8);
        printf("NOME: %s\n", P.nome);
        gotoxy(5, 9);
        printf("TELEFONE: %s\n", P.telefone);
        gotoxy(5, 10);
        printf("ENDEREÇO: %s\n", P.endereco);

        gotoxy(5, 12);
        printf("REALIZAR EMPRÉSTIMO (S/N)? ");

        if (toupper(getche()) == 'S') {
            gotoxy(5, 14);
            printf("\nI.D DO LIVRO PARA EMPRÉSTIMO:\n ");
            scanf("%d", &Li.id_livro);

            if (BuscaLivro(PtrLi, Li.id_livro) != 1) {
                gotoxy(5, 16); 
                printf("LIVRO ENCONTRADO!\n");
                gotoxy(5, 17);
                printf("I.D: %d\n", Li.id_livro);
                gotoxy(5, 18);
                printf("TÍTULO: %s\n", Li.titulo);
                gotoxy(5, 19);
                printf("ANO DE PUBLICAÇÃO: %d\n", Li.ano_publi);

                gotoxy(5, 21);
                printf("CONFIRMAR EMPRÉSTIMO DO LIVRO '%s' PARA '%s' (S/N)? ", Li.titulo, P.nome);

                if (toupper(getche()) == 'S') {
                    gotoxy(5, 23); 
                    printf("\nDigite o ID do Empréstimo: ");
                    scanf("%d", &Em.id_emprestimo);

                    gotoxy(5, 25);
                    printf("QUAL O DIA DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.dia);
                    gotoxy(5, 26); 
                    printf("QUAL O MÊS DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.mes);
                    gotoxy(5, 27); 
                    printf("QUAL O ANO DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.ano);

                    if (Em.mes < 1 || Em.mes > 12) {
                        gotoxy(5, 29); 
                        printf("MÊS INVÁLIDO! O MÊS DEVE SER ENTRE 1 E 12.\n");
                    } else {
                        int diasNoMes;
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
                            gotoxy(5, 31); // Linha 31, coluna 5
                            printf("DIA INVÁLIDO! ESTE MÊS POSSUI APENAS %d DIAS.\n", diasNoMes);
                        } else {
                            sprintf(Em.data_emprestimo, "%02d/%02d/%04d", Em.dia, Em.mes, Em.ano);
                            fwrite(&Em, sizeof(Emprestimo), 1, PtrEm);

                            gotoxy(5, 33); 
                            printf("QUAL O DIA DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                            scanf("%d", &Em.dia);
                            gotoxy(5, 34); 
                            printf("QUAL O MÊS DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                            scanf("%d", &Em.mes);
                            gotoxy(5, 35);
                            printf("QUAL O ANO DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                            scanf("%d", &Em.ano);

                            if (Em.mes < 1 || Em.mes > 12) {
                                gotoxy(5, 37); 
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
                                    gotoxy(5, 39); 
                                    printf("DIA INVÁLIDO! ESTE MÊS POSSUI APENAS %d DIAS.\n", diasNoMes);
                                } else {
                                    sprintf(Em.data_devolucao, "%02d/%02d/%04d", Em.dia, Em.mes, Em.ano);

                                    int emprestimoDia, emprestimoMes, emprestimoAno;
                                    sscanf(Em.data_emprestimo, "%2d/%2d/%4d", &emprestimoDia, &emprestimoMes, &emprestimoAno);

                                    if ((Em.ano < emprestimoAno) ||
                                        (Em.ano == emprestimoAno && Em.mes < emprestimoMes) ||
                                        (Em.ano == emprestimoAno && Em.mes == emprestimoMes && Em.dia < emprestimoDia)) {
                                        gotoxy(5, 41); // Linha 41, coluna 5
                                        printf("A DATA DE DEVOLUÇÃO NÃO PODE SER MENOR DO QUE A DE EMPRÉSTIMO!\n");
                                    } else {
                                        gotoxy(5, 43); 
                                        printf("EMPRÉSTIMO CONCEDIDO! DEVOLUÇÃO AGENDADA PARA: %s\n", Em.data_devolucao);
                                        fwrite(&Em, sizeof(Emprestimo), 1, PtrEm);
                                    }
                                }
                            }
                        }
                    }
                } else {
                    gotoxy(5, 45); 
                    printf("\nEMPRÉSTIMO CANCELADO!\n");
                }
            } else {
                gotoxy(5, 47); 
                printf("\nLIVRO NÃO ENCONTRADO!\n");
            }
        } else {
            gotoxy(5, 49); 
            printf("\nEMPRÉSTIMO NÃO AUTORIZADO!\n");
        }
    } else {
        gotoxy(5, 51); 
        printf("\nPESSOA NÃO ENCONTRADA!\n");
    }

    fclose(PtrLi);
    fclose(PtrPe);
    fclose(PtrEm);
    getch(); // Espera a tecla ser pressionada para sair
}


void ConsultarDados()
{
    char opcao;  // Alterado de int para char
    Autor A;
    Livros L;
    Pessoa P;
    Emprestimo E;
    int pos;

    system("cls");  // Usando system("cls") para limpar a tela no Windows
    desenharBordas();
    printf("## CONSULTA DE DADOS ##\n");
    printf("Escolha uma opção:\n");
    printf("a) Autor\n");
    printf("b) Livro\n");
    printf("c) Pessoa\n");
    printf("d) Empréstimo\n");
    printf("Opção: ");
    scanf(" %c", &opcao);  // Usando um espaço antes de %c para limpar o buffer

    switch(opcao)
    {
        case 'a':
            {
                FILE *PtrA = fopen("Autor.dat", "rb");
                if (PtrA == NULL) {
                    printf("Erro ao abrir o arquivo de autores.\n");
                } else {
                    printf("\n## CONSULTA DE AUTORES ##\n");
                    printf("I.D DO AUTOR: ");
                    scanf("%d", &A.id_autor);

                    while(A.id_autor > 0)
                    {
                        pos = BuscaAutor(PtrA, A.id_autor);
                        if(pos == -1)
                        {
                            printf("I.D NÃO ENCONTRADO!\n");
                        }
                        else
                        {
                            fseek(PtrA, pos, SEEK_SET);
                            if (fread(&A, sizeof(Autor), 1, PtrA) == 1) {  // Verificando se a leitura foi bem-sucedida
                                printf("\nDADOS ENCONTRADOS!\n");
                                printf("I.D AUTOR: %d\n", A.id_autor);
                                printf("NOME DO AUTOR: %s\n", A.nome);
                                printf("NACIONALIDADE: %s\n", A.nacionalidade);
                            } else {
                                printf("Erro ao ler os dados do autor.\n");
                            }
                        }

                        printf("I.D DO AUTOR: ");
                        scanf("%d", &A.id_autor);
                    }

                    fclose(PtrA);
                }
            }
            break;

        case 'b':
            {
                FILE *PtrL = fopen("Livros.dat", "rb");
                if (PtrL == NULL) {
                    printf("Erro ao abrir o arquivo de livros.\n");
                } else {
                    printf("\n## CONSULTA DE LIVROS ##\n");
                    printf("I.D DO LIVRO: ");
                    scanf("%d", &L.id_livro);

                    while(L.id_livro > 0)
                    {
                        pos = BuscaLivro(PtrL, L.id_livro);
                        if(pos == -1)
                        {
                            printf("I.D NÃO ENCONTRADO!\n");
                        }
                        else
                        {
                            fseek(PtrL, pos, SEEK_SET);
                            if (fread(&L, sizeof(Livros), 1, PtrL) == 1) {  // Verificando se a leitura foi bem-sucedida
                                printf("\nDADOS ENCONTRADOS!\n");
                                printf("I.D DO LIVRO: %d\n", L.id_livro);
                                printf("TÍTULO: %s\n", L.titulo);
                                printf("ANO DE PUBLICAÇÃO: %d\n", L.ano_publi);
                            } else {
                                printf("Erro ao ler os dados do livro.\n");
                            }
                        }

                        printf("I.D DO LIVRO: ");
                        scanf("%d", &L.id_livro);
                    }

                    fclose(PtrL);
                }
            }
            break;

        case 'c':
            {
                FILE *PtrP = fopen("Pessoas.dat", "rb");
                if (PtrP == NULL) {
                    printf("Erro ao abrir o arquivo de pessoas.\n");
                } else {
                    printf("\n## CONSULTA DE PESSOAS ##\n");
                    printf("I.D DA PESSOA: ");
                    scanf("%d", &P.id_pessoa);

                    while(P.id_pessoa > 0)
                    {
                        pos = BuscaPessoa(PtrP, P.id_pessoa);
                        if(pos == -1)
                        {
                            printf("I.D NÃO ENCONTRADO!\n");
                        }
                        else
                        {
                            fseek(PtrP, pos, SEEK_SET);
                            if (fread(&P, sizeof(Pessoa), 1, PtrP) == 1) {  // Verificando se a leitura foi bem-sucedida
                                printf("\nDADOS ENCONTRADOS!\n");
                                printf("I.D PESSOA: %d\n", P.id_pessoa);
                                printf("NOME: %s\n", P.nome);
                                printf("TELEFONE: %s\n", P.telefone);
                                printf("ENDEREÇO: %s\n", P.endereco);
                            } else {
                                printf("Erro ao ler os dados da pessoa.\n");
                            }
                        }

                        printf("I.D DA PESSOA: ");
                        scanf("%d", &P.id_pessoa);
                    }

                    fclose(PtrP);
                }
            }
            break;

        case 'd':
            {
                FILE *PtrE = fopen("Emprestimos.dat", "rb");
                if (PtrE == NULL) {
                    printf("Erro ao abrir o arquivo de empréstimos.\n");
                } else {
                    printf("\n## CONSULTA DE EMPRÉSTIMOS ##\n");
                    printf("I.D DO EMPRÉSTIMO: ");
                    scanf("%d", &E.id_emprestimo);

                    pos = BuscaEmprestimo(PtrE, E.id_emprestimo);
                    if(pos == -1)
                    {
                        printf("EMPRÉSTIMO NÃO ENCONTRADO!\n");
                    }
                    else
                    {
                        fseek(PtrE, pos, SEEK_SET);
                        if (fread(&E, sizeof(Emprestimo), 1, PtrE) == 1) {  // Verificando se a leitura foi bem-sucedida
                            printf("\nDADOS ENCONTRADOS!\n");
                            printf("I.D DO EMPRÉSTIMO: %d\n", E.id_emprestimo);
                            printf("ID PESSOA: %d\n", E.id_pessoa);
                            printf("ID LIVRO: %d\n", E.id_livro);
                            printf("DATA DE EMPRÉSTIMO: %s\n", E.data_emprestimo);
                            printf("DATA DE DEVOLUÇÃO: %s\n", E.data_devolucao);
                        } else {
                            printf("Erro ao ler os dados do empréstimo.\n");
                        }
                    }

                    fclose(PtrE);
                }
            }
            break;

        default:
            printf("Opção inválida.\n");
            break;
    }

    getchar();  // Aguardar a tecla pressionada antes de voltar ao menu
}


void relatorios() {
    Livros L;
    Pessoa P;
    LivroAutor LA;
    Emprestimo E;
    Autor A;
    char opcao;
    clrscr();
    textbackground(CYAN);
    textcolor(YELLOW);

    gotoxy(10, 3);
    printf("## MENU DE RELATORIOS ##\n");
    gotoxy(5, 5);
    printf("A. Relatório de autores por letra\n");
    printf("B. Relatório de livros por palavra no título\n");
    printf("C. Relatório de empréstimos por pessoa\n");
    printf("D. Relatório de livros por autor\n");
    printf("E. Relatório de empréstimos separados por pessoa\n");
    printf("F. Relatório Completo\n");
    printf("G. Sair\n");

    gotoxy(5, 7);
    printf("Escolha uma opção (A-G): ");
    opcao = toupper(getch());

    switch (opcao) {
        case 'A': {
            char letra;
            clrscr();
            gotoxy(5, 3);
            printf("Digite a letra para filtrar os autores: ");
            letra = toupper(getch());  // Lê a letra
            RelatorioAutoresPorLetra(letra);
            break;
        }
        case 'B': {
            char palavra[50];
            clrscr();
            gotoxy(5, 3);
            printf("Digite a palavra para filtrar os livros: ");
            scanf("%s", palavra);
            RelatorioLivrosPorPalavra(palavra);
            break;
        }
        case 'C': {
            clrscr();
            gotoxy(5, 3);
            printf("Digite o ID da pessoa para visualizar os empréstimos: ");
            scanf("%d", &P.id_pessoa);
            RelatorioEmprestimosPorPessoa(P.id_pessoa);
            break;
        }
        case 'D': {
            clrscr();
            gotoxy(5, 3);
            printf("Digite o ID do autor para visualizar os livros: ");
            scanf("%d", &A.id_autor);
            RelatorioLivrosPorAutor(A.id_autor);
            break;
        }
        case 'E': {
            clrscr();
            RelatorioEmprestimosSeparadosPorPessoa();
            break;
        }
        case 'F': {
            clrscr();
            RelatorioCompleto();  // Chama a função de relatório completo
            break;
        }
        case 'G':
            return;  // Se a opção for G, sai do programa
        default:
            clrscr();
            gotoxy(5, 5);
            printf("Opção inválida! Tente novamente.\n");
            break;
    }

    gotoxy(5, 10);
    printf("\nPressione qualquer tecla para voltar ao menu.");
    getch();
    relatorios();  // Chama novamente o menu de relatórios
}

// Função para gerar o relatório completo de todas as tabelas
void RelatorioCompleto() {
    char opcao;
    clrscr();
    textbackground(CYAN);
    textcolor(YELLOW);
    gotoxy(10, 3);
    printf("## RELATÓRIO COMPLETO ##\n");
    gotoxy(5, 5);
    printf("Escolha qual relatório completo deseja gerar:\n");
    printf("1. Relatório de Autores\n");
    printf("2. Relatório de Livros\n");
    printf("3. Relatório de Pessoas\n");
    printf("4. Relatório de Empréstimos\n");
    printf("5. Voltar\n");

    gotoxy(5, 7);
    printf("Escolha uma opção (1-5): ");
    opcao = toupper(getch());

    switch (opcao) {
        case '1':
            RelatorioAutoresCompleto();
            break;
        case '2':
            RelatorioLivrosCompleto();
            break;
        case '3':
            RelatorioPessoasCompleto();
            break;
        case '4':
            RelatorioEmprestimosCompleto();
            break;
        case '5':
            return;  // Voltar ao menu de relatórios
        default:
            clrscr();
            gotoxy(5, 5);
            printf("Opção inválida! Tente novamente.\n");
            getch();
            RelatorioCompleto();  // Tenta novamente
            break;
    }

    gotoxy(5, 10);
    printf("\nPressione qualquer tecla para voltar ao menu.");
    getch();
}

// Função para gerar o relatório completo de autores
void RelatorioAutoresCompleto() {
    Autor A;
    FILE *PtrAutores = fopen("Autor.dat", "rb+");

    if (PtrAutores == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de autores!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Autores ##\n");

        rewind(PtrAutores);
        int linha = 7;
        while (fread(&A, sizeof(Autor), 1, PtrAutores) == 1) {
            gotoxy(5, linha++);
            printf("ID: %d | Nome: %s | Nacionalidade: %s\n", A.id_autor, A.nome, A.nacionalidade);
        }

        fclose(PtrAutores);
    }
}

// Função para gerar o relatório completo de livros
void RelatorioLivrosCompleto() {
    Livros L;
    FILE *PtrLivros = fopen("Livros.dat", "rb+");

    if (PtrLivros == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de livros!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Livros ##\n");

        rewind(PtrLivros);
        int linha = 7;
        while (fread(&L, sizeof(Livros), 1, PtrLivros) == 1) {
            gotoxy(5, linha++);
            printf("ID: %d | Título: %s | Ano de Publicação: %d\n", L.id_livro, L.titulo, L.ano_publi);
        }

        fclose(PtrLivros);
    }
}

// Função para gerar o relatório completo de pessoas
void RelatorioPessoasCompleto() {
    Pessoa P;
    FILE *PtrPessoas = fopen("Pessoas.dat", "rb+");

    if (PtrPessoas == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de pessoas!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Pessoas ##\n");

        rewind(PtrPessoas);
        int linha = 7;
        while (fread(&P, sizeof(Pessoa), 1, PtrPessoas) == 1) {
            gotoxy(5, linha++);
            printf("ID: %d | Nome: %s | Endereço: %s\n", P.id_pessoa, P.nome, P.endereco);
        }

        fclose(PtrPessoas);
    }
}

// Função para gerar o relatório completo de empréstimos
void RelatorioEmprestimosCompleto() {
    Emprestimo E;
    FILE *PtrEmprestimos = fopen("Emprestimos.dat", "rb+");

    if (PtrEmprestimos == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de empréstimos!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Empréstimos ##\n");

        rewind(PtrEmprestimos);
        int linha = 7;
        while (fread(&E, sizeof(Emprestimo), 1, PtrEmprestimos) == 1) {
            gotoxy(5, linha++);
            printf("ID: %d | Livro ID: %d | Pessoa ID: %d | Data de Empréstimo: %s | Data de Devolução: %s\n",
                   E.id_emprestimo, E.id_livro, E.id_pessoa, E.data_emprestimo, E.data_devolucao);
        }

        fclose(PtrEmprestimos);
    }
}

void RelatorioAutoresPorLetra(char letra) {
    Autor A;
    FILE *PtrAutores = fopen("Autor.dat", "rb+");

    if (PtrAutores == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de autores!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Autores (Letra %c) ##\n", letra);

        rewind(PtrAutores);
        int linha = 7;
        while (fread(&A, sizeof(Autor), 1, PtrAutores) == 1) {
            if (toupper(A.nome[0]) == toupper(letra)) {  // Verifica a letra inicial do nome
                gotoxy(5, linha++);
                printf("ID: %d | Nome: %s | Nacionalidade: %s\n", A.id_autor, A.nome, A.nacionalidade);
            }
        }

        fclose(PtrAutores);
    }
}

// Função para gerar o relatório de livros filtrados por palavra no título
void RelatorioLivrosPorPalavra(char *palavra) {
    Livros L;
    FILE *PtrLivros = fopen("Livros.dat", "rb+");

    if (PtrLivros == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de livros!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Livros (Palavra: %s) ##\n", palavra);

        rewind(PtrLivros);
        int linha = 7;
        while (fread(&L, sizeof(Livros), 1, PtrLivros) == 1) {
            if (strstr(L.titulo, palavra) != NULL) {  // Verifica se a palavra está no título
                gotoxy(5, linha++);
                printf("ID: %d | Título: %s | Ano de Publicação: %d\n", L.id_livro, L.titulo, L.ano_publi);
            }
        }

        fclose(PtrLivros);
    }
}

// Função para gerar o relatório de empréstimos por pessoa
void RelatorioEmprestimosPorPessoa(int id_pessoa) {
    Emprestimo E;
    FILE *PtrEmprestimos = fopen("Emprestimos.dat", "rb+");

    if (PtrEmprestimos == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de empréstimos!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Empréstimos para Pessoa (ID: %d) ##\n", id_pessoa);

        rewind(PtrEmprestimos);
        int linha = 7;
        while (fread(&E, sizeof(Emprestimo), 1, PtrEmprestimos) == 1) {
            if (E.id_pessoa == id_pessoa) {
                gotoxy(5, linha++);
                printf("ID: %d | Livro ID: %d | Data de Empréstimo: %s | Data de Devolução: %s\n",
                       E.id_emprestimo, E.id_livro, E.data_emprestimo, E.data_devolucao);
            }
        }

        fclose(PtrEmprestimos);
    }
}

// Função para gerar o relatório de livros por autor
void RelatorioLivrosPorAutor(int id_autor) {
    LivroAutor LA;
    Livros L;
    FILE *PtrLivros = fopen("Livros.dat", "rb+");
    FILE *PtrLivroAutor = fopen("LivroAutor.dat", "rb+");

    if (PtrLivros == NULL || PtrLivroAutor == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivos de livros ou livro-autor!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Livros por Autor (ID: %d) ##\n", id_autor);

        rewind(PtrLivroAutor);
        int linha = 7;
        while (fread(&LA, sizeof(LivroAutor), 1, PtrLivroAutor) == 1) {
            if (LA.id_autor == id_autor) {
                rewind(PtrLivros);
                while (fread(&L, sizeof(Livros), 1, PtrLivros) == 1) {
                    if (L.id_livro == LA.id_livro) {
                        gotoxy(5, linha++);
                        printf("ID: %d | Título: %s | Ano de Publicação: %d\n", L.id_livro, L.titulo, L.ano_publi);
                    }
                }
                rewind(PtrLivros);
            }
        }

        fclose(PtrLivros);
        fclose(PtrLivroAutor);
    }
}

// Função para gerar o relatório de empréstimos separados por pessoa
void RelatorioEmprestimosSeparadosPorPessoa() {
    Emprestimo E;
    FILE *PtrEmprestimos = fopen("Emprestimos.dat", "rb+");

    if (PtrEmprestimos == NULL) {
        gotoxy(5, 5);
        printf("Erro ao abrir arquivo de empréstimos!\n");
    } else {
        clrscr();
        textbackground(CYAN);
        textcolor(YELLOW);
        gotoxy(10, 3);
        printf("## Relatório de Empréstimos Separados por Pessoa ##\n");

        rewind(PtrEmprestimos);
        int linha = 7;
        int current_person = -1;
        while (fread(&E, sizeof(Emprestimo), 1, PtrEmprestimos) == 1) {
            if (E.id_pessoa != current_person) {
                current_person = E.id_pessoa;
                gotoxy(5, linha++);
                printf("\nPessoa ID: %d\n", E.id_pessoa);
            }
            gotoxy(5, linha++);
            printf("ID: %d | Livro ID: %d | Data de Empréstimo: %s | Data de Devolução: %s\n",
                   E.id_emprestimo, E.id_livro, E.data_emprestimo, E.data_devolucao);
        }

        fclose(PtrEmprestimos);
    }
}

void desenharBordas() {
    for (int i = 1; i <= 80; i++) {
        gotoxy(i, 1); printf("#");  
        gotoxy(i, 25); printf("#"); 
    }
    for (int i = 1; i <= 25; i++) {
        gotoxy(1, i); printf("#");  
        gotoxy(80, i); printf("#"); 
    }
}

char Menu(void)
{
    char op;

    clrscr(); // Limpa a tela
    
    textcolor(CYAN);
    desenharBordas(); // Chama a função para desenhar as bordas

    gotoxy(30, 2);
    textcolor(WHITE);
    printf("## MENU ##");

    textcolor(LIGHTGREEN);
    gotoxy(5, 4); printf("[A] CADASTRAR LIVROS");
    gotoxy(5, 5); printf("[B] CADASTRAR AUTOR");
    gotoxy(5, 6); printf("[C] CADASTRAR PESSOA");
    gotoxy(5, 7); printf("[D] REALIZAR EMPRESTIMO");
    gotoxy(5, 8); printf("[E] EXCLUSÃO LÓGICA");
    gotoxy(5, 9); printf("[F] EXCLUSÃO FÍSICA");
    gotoxy(5, 10); printf("[G] ALTERAÇÃO POR ID");
    gotoxy(5, 11); printf("[H] CONSULTAR POR ID");
    gotoxy(5, 15); printf("[I] RELATÓRIO");

    gotoxy(5, 24);
    textcolor(LIGHTCYAN);
    printf("[0] PARA SAIR");

    gotoxy(35, 25);
    textcolor(RED);
    printf("Escolha a opção: ");
    op = toupper(getche());

    return op;
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
            case 'E': ExclusaoLogica();
                break;
            case 'F': ExclusaoFisica();
                break;
            case 'G': AlterarDados();
                break;
            case 'H': ConsultarDados();
                break;
            case 'I': relatorios();
                break;  
        }
    } while(op != '0'); // Sai quando o usuário digitar '0'
    
    return 0;
}
