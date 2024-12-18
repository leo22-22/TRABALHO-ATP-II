#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>
#include <locale.h>

struct Livros{
    int id_livro, ano_publi;
    char titulo[100];
    int ativo;
};

struct Autor{
    int id_autor;
    char nome[30], nacionalidade[30];
    int ativo;
};

struct Emprestimo{
    int id_emprestimo, id_livro, id_pessoa;
    int dia, mes, ano;
    char data_emprestimo[11];
    char data_devolucao[11];
    int ativo;
};

struct Pessoa{
    int id_pessoa;
    char nome[30], telefone[14], endereco[40];
    int ativo;
};

struct LivroAutor{
    int id_livro, id_autor;
    int ativo;
};

void CriaArquivos(void) {
    FILE *Ptr;
    
    Ptr = fopen("Livros.dat", "ab");
    fclose(Ptr);
    Ptr = fopen("Autor.dat", "ab");
    fclose(Ptr);
    Ptr = fopen("Emprestimos.dat", "ab");
    fclose(Ptr);
    Ptr = fopen("LivroAutor.dat", "ab");
    fclose(Ptr);
    Ptr = fopen("Pessoas.dat", "ab");
    fclose(Ptr);
}

int BuscaLivro(FILE *Ptr, int ChaveID);
int BuscaAutor(FILE *Ptr, int ChaveID);
int BuscaAutorPorLivro(FILE *Ptr, int id_livro);
int BuscaPessoa(FILE *Ptr, int ChaveID);
int BuscaEmprestimo(FILE *Ptr, int ChaveID);

// Funções de cadastro
void CadastroLivros();
void CadastroAutor();
void CadastroPessoa();
void CadastroLivroAutor();
void RealizarEmprestimo();

// Funções de exclusão
void ExclusaoLogica();
void ExclusaoFisica();

// Funções de alteração
void AlterarDados();

// Funções de consulta
void ConsultarDados();

// Funções de exibição
void ExibirLivros(void);
void ExibirPessoas(void);
void ExibirAutores(void);
void ExibirEmprestimos(void);

// Funções de relatório
void RelatorioAutoresPorLetra(char letra);
void RelatorioLivrosPorPalavra(char *palavra);
void RelatorioEmprestimosPorPessoa(int id_pessoa);
void RelatorioLivrosPorAutor(int id_autor);
void RelatorioEmprestimosSeparadosPorPessoa();
void RelatorioCompleto();
void RelatorioAutoresCompleto();
void RelatorioLivrosCompleto();
void RelatorioPessoasCompleto();
void RelatorioEmprestimosCompleto();

void ExclusaoLogica(void) {
    Livros L;
    Pessoa P;
    Autor A;
    Emprestimo E;

    FILE *PtrLi = fopen("Livros.dat", "rb+");
    FILE *PtrPe = fopen("Pessoas.dat", "rb+");
    FILE *PtrAu = fopen("Autores.dat", "rb+");
    FILE *PtrEm = fopen("Emprestimos.dat", "rb+");

    char opcao;
    int id_excluir, exclusaoRealizada = 0; // Flag para indicar se uma exclusão foi realizada
    printf("Escolha a opção de exclusão lógica:\n");
    printf("A - Excluir Livro\n");
    printf("B - Excluir Pessoa\n");
    printf("C - Excluir Autor\n");
    printf("D - Excluir Empréstimo\n");

    printf("Escolha a opção (A/B/C/D): ");
    opcao = toupper(getchar());
    getchar(); // Consome o '\n' residual após a leitura

    switch (opcao) {
        case 'A': // Excluir Livro
            printf("ID do Livro a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            while (fread(&L, sizeof(Livros), 1, PtrLi) == 1) {
                if (L.id_livro == id_excluir) {
                    L.ativo = 0; // Marca como inativo
                    fseek(PtrLi, -sizeof(Livros), SEEK_CUR); // Volta o ponteiro para reescrever
                    fwrite(&L, sizeof(Livros), 1, PtrLi);
                    exclusaoRealizada = 1;
                }
            }
            break;

        case 'B': // Excluir Pessoa
            printf("ID da Pessoa a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            while (fread(&P, sizeof(Pessoa), 1, PtrPe) == 1) {
                if (P.id_pessoa == id_excluir) {
                    P.ativo = 0; // Marca como inativo
                    fseek(PtrPe, -sizeof(Pessoa), SEEK_CUR); // Volta o ponteiro para reescrever
                    fwrite(&P, sizeof(Pessoa), 1, PtrPe);
                    exclusaoRealizada = 1;
                }
            }
            break;

        case 'C': // Excluir Autor
            printf("ID do Autor a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            while (fread(&A, sizeof(Autor), 1, PtrAu) == 1) {
                if (A.id_autor == id_excluir) {
                    A.ativo = 0; // Marca como inativo
                    fseek(PtrAu, -sizeof(Autor), SEEK_CUR); // Volta o ponteiro para reescrever
                    fwrite(&A, sizeof(Autor), 1, PtrAu);
                    exclusaoRealizada = 1;
                }
            }
            break;

        case 'D': // Excluir Empréstimo
            printf("ID do Empréstimo a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            while (fread(&E, sizeof(Emprestimo), 1, PtrEm) == 1) {
                if (E.id_emprestimo == id_excluir) {
                    E.ativo = 0; // Marca como inativo
                    fseek(PtrEm, -sizeof(Emprestimo), SEEK_CUR); // Volta o ponteiro para reescrever
                    fwrite(&E, sizeof(Emprestimo), 1, PtrEm);
                    exclusaoRealizada = 1;
                }
            }
            break;

        default:
            printf("Opção Inválida!\n");
            break;
    }

    if (exclusaoRealizada) {
        printf("Exclusão lógica realizada com sucesso!\n");
    } else {
        printf("Não foi possível realizar a exclusão!\n");
    }

    // Fecha os arquivos
    fclose(PtrLi);
    fclose(PtrPe);
    fclose(PtrAu);
    fclose(PtrEm);
}

void ExclusaoFisica(void) {
    Livros L;
    Pessoa P;
    Autor A;
    Emprestimo E;
    LivroAutor LA;

    FILE *PtrLi = fopen("Livros.dat", "rb+");
    FILE *PtrPe = fopen("Pessoas.dat", "rb+");
    FILE *PtrAu = fopen("Autores.dat", "rb+");
    FILE *PtrEm = fopen("Emprestimos.dat", "rb+");
    FILE *PtrLa = fopen("LivroAutor.dat", "rb+");

    FILE *PtrTempLi, *PtrTempPe, *PtrTempAu, *PtrTempEm, *PtrTempLa;


    char opcao;
    printf("Escolha a opção de exclusão física:\n");
    printf("A - Excluir Livro\n");
    printf("B - Excluir Pessoa\n");
    printf("C - Excluir Autor\n");
    printf("D - Excluir Empréstimo\n");

    printf("Escolha a opção (A/B/C/D): ");
    opcao = toupper(getchar());
    getchar();  // Consome o '\n' residual após a leitura

    switch (opcao) {
        case 'A': {
            int id_excluir;
            printf("ID do Livro a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            PtrTempLi = fopen("TempLivros.dat", "wb");
            PtrTempLa = fopen("TempLivroAutor.dat", "wb");

            while (fread(&L, sizeof(Livros), 1, PtrLi) == 1) {
                if (L.id_livro != id_excluir) {
                    fwrite(&L, sizeof(Livros), 1, PtrTempLi);
                }
            }

            while (fread(&LA, sizeof(LivroAutor), 1, PtrLa) == 1) {
                if (LA.id_livro != id_excluir) {
                    fwrite(&LA, sizeof(LivroAutor), 1, PtrTempLa);
                }
            }

            printf("Livro excluído fisicamente!\n");

            fclose(PtrLi);
            fclose(PtrTempLi);
            fclose(PtrLa);
            fclose(PtrTempLa);

            remove("Livros.dat");
            rename("TempLivros.dat", "Livros.dat");

            remove("LivroAutor.dat");
            rename("TempLivroAutor.dat", "LivroAutor.dat");
            break;
        }
        case 'B': {
            int id_excluir;
            printf("ID da Pessoa a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            PtrTempPe = fopen("TempPessoas.dat", "wb");

            while (fread(&P, sizeof(Pessoa), 1, PtrPe) == 1) {
                if (P.id_pessoa != id_excluir) {
                    fwrite(&P, sizeof(Pessoa), 1, PtrTempPe);
                }
            }

            printf("Pessoa excluída fisicamente!\n");

            fclose(PtrPe);
            fclose(PtrTempPe);

            remove("Pessoas.dat");
            rename("TempPessoas.dat", "Pessoas.dat");
            break;
        }
        case 'C': {
            int id_excluir;
            printf("ID do Autor a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            PtrTempAu = fopen("TempAutores.dat", "wb");

            while (fread(&A, sizeof(Autor), 1, PtrAu) == 1) {
                if (A.id_autor != id_excluir) {
                    fwrite(&A, sizeof(Autor), 1, PtrTempAu);
                }
            }

            printf("Autor excluído fisicamente!\n");

            fclose(PtrAu);
            fclose(PtrTempAu);

            remove("Autores.dat");
            rename("TempAutores.dat", "Autores.dat");
            break;
        }
        case 'D': {
            int id_excluir;
            printf("ID do Empréstimo a Excluir: ");
            scanf("%d", &id_excluir);
            getchar(); // Consome o '\n' residual

            PtrTempEm = fopen("TempEmprestimos.dat", "wb");

            while (fread(&E, sizeof(Emprestimo), 1, PtrEm) == 1) {
                if (E.id_emprestimo != id_excluir) {
                    fwrite(&E, sizeof(Emprestimo), 1, PtrTempEm);
                }
            }

            printf("Empréstimo excluído fisicamente!\n");

            fclose(PtrEm);
            fclose(PtrTempEm);

            remove("Emprestimos.dat");
            rename("TempEmprestimos.dat", "Emprestimos.dat");
            break;
        }
        default:
            printf("Opção Inválida!\n");
            break;
    }
}


void ExibirLivros(void) {
    Livros L;
    FILE *Ptr = fopen("Livros.dat", "rb");

    // Inicializa a leitura do arquivo
    while (fread(&L, sizeof(Livros), 1, Ptr)) {
        // Exibe os dados de cada livro
        printf("ID: %d\n", L.id_livro);
        printf("Título: %s\n", L.titulo);
        printf("Ano de Publicação: %d\n", L.ano_publi);
        printf("-----------------------------\n");
    }

    fclose(Ptr);
}


void ExibirPessoas(void)
{
    Pessoa P;
    FILE *Ptr = fopen("Pessoas.dat", "rb");
	
    printf("## PESSOAS CADASTRADAS ##\n");
    while (fread(&P, sizeof(Pessoa), 1, Ptr)) {
        printf("ID: %d\n", P.id_pessoa);
        printf("Nome: %s\n", P.nome);
        printf("Telefone: %s\n", P.telefone);
        printf("Endereço: %s\n", P.endereco);
    }

    fclose(Ptr);
}

void ExibirAutores(void)
{
    Autor A;
    FILE *Ptr = fopen("Autor.dat", "rb");

    printf("## AUTORES CADASTRADOS ##\n");
    while (fread(&A, sizeof(Autor), 1, Ptr)) {
        printf("ID: %d\n", A.id_autor);
        printf("Nome: %s\n", A.nome);
        printf("Nacionalidade: %s\n", A.nacionalidade);
    }

    fclose(Ptr);
}

void MenuExibirCadastros(void) {
    int opcao;

    do {
        printf("\n## MENU DE EXIBIÇÃO DE CADASTROS ##\n");
        printf("1. Exibir Livros\n");
        printf("2. Exibir Pessoas\n");
        printf("3. Exibir Autores\n");
        printf("4. Exibir Empréstimos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                ExibirLivros();
                break;
            case 2:
                ExibirPessoas();
                break;
            case 3:
                ExibirAutores();
                break;
            case 4:
                ExibirEmprestimos();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);
}

void ExibirEmprestimos(void) {
    Emprestimo E;
    FILE *Ptr = fopen("Emprestimos.dat", "rb");

    printf("\n## EMPRÉSTIMOS REALIZADOS ##\n");
    while (fread(&E, sizeof(Emprestimo), 1, Ptr)) {
        printf("ID do Empréstimo: %d\n", E.id_emprestimo);
        printf("Pessoa ID: %d\n", E.id_pessoa);
        printf("Livro ID: %d\n", E.id_livro);
        printf("Data de Empréstimo: %s\n", E.data_emprestimo);
        printf("Data de Devolução: %s\n\n", E.data_devolucao);
    }

    fclose(Ptr);
}

int BuscaLivro(FILE *Ptr, int id_livro)
{
    Livros L;
    fseek(Ptr, 0, SEEK_SET);  // Garante que o ponteiro está no início do arquivo
    while (fread(&L, sizeof(Livros), 1, Ptr) == 1)
    {
        if (L.id_livro == id_livro)
            return 1;  // Livro encontrado
    }
    return -1;  // Livro não encontrado
}


int BuscaAutor(FILE *PtrAu, int id_autor) {
    Autor Au;
    fseek(PtrAu, 0, SEEK_SET);  // Iniciar no começo do arquivo
    while (fread(&Au, sizeof(Autor), 1, PtrAu)) {
        if (Au.id_autor == id_autor) {
            return 1; // Autor encontrado
        }
    }
    return -1;  // Autor não encontrado
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
    FILE *Ptr = fopen("Livros.dat", "wb+");  // Abre o arquivo para leitura e escrita

    printf("## CADASTRO DE LIVROS ##\n");
    printf("ID DO LIVRO: ");
    scanf("%d", &L.id_livro);

    while (L.id_livro > 0)
    {
        // Verificar se o livro já está cadastrado no arquivo
        if (BuscaLivro(Ptr, L.id_livro) == 1)
        {
            printf("ID JÁ CADASTRADO! O livro com esse ID já existe no arquivo.\n");
        }
        else
        {
            int titulo_valido = 0;
            while (!titulo_valido)
            {
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
                        printf("TÍTULO INVÁLIDO! Use apenas letras e espaços.\n");
                        break;
                    }
                }
            }

            printf("ANO DE PUBLICAÇÃO (XXXX): ");
            scanf("%d", &L.ano_publi);

            if (L.ano_publi >= 1000 && L.ano_publi <= 2024)
            {
                // Marca o livro como ativo (não excluído)
                L.ativo = 1;

                fseek(Ptr, 0, SEEK_END);  // Move para o final do arquivo antes de adicionar
                fwrite(&L, sizeof(Livros), 1, Ptr);
                printf("LIVRO CADASTRADO!\n");
            }
            else
            {
                printf("ANO DE PUBLICAÇÃO INVÁLIDO! Data limite até 2024.\n");
            }
        }

        printf("ID DO LIVRO: ");
        scanf("%d", &L.id_livro);
    }

    fclose(Ptr);
}


void CadastroPessoa(void)
{
    Pessoa P;
    FILE *Ptr = fopen("Pessoas.dat", "wb+");

    printf("## CADASTRO DE PESSOAS ##\n");
    printf("ID DA PESSOA: ");
    scanf("%d", &P.id_pessoa);

    while (P.id_pessoa > 0)
    {
        if (BuscaPessoa(Ptr, P.id_pessoa) == -1)
        {
            printf("NOME DA PESSOA: ");
            fflush(stdin);
            fgets(P.nome, sizeof(P.nome), stdin);
            P.nome[strcspn(P.nome, "\n")] = '\0';  // Remove o '\n'
            printf("TELEFONE((XX)XXXXX-XXXX): ");
            fflush(stdin);
            gets(P.telefone); fflush(stdin);
            
            if (strlen(P.telefone) == 14)
            {
                if (P.telefone[0] == '(' || P.telefone[3] == ')' || P.telefone[9] == '-')
                {
                    printf("ENDEREÇO: ");
                    fflush(stdin);
                    fgets(P.endereco, sizeof(P.endereco), stdin);
                    P.endereco[strcspn(P.endereco, "\n")] = '\0';  // Remove o '\n'

                    // Marca a pessoa como ativa (não excluída)
                    P.ativo = 1;

                    fseek(Ptr, 0, SEEK_END);  // Move para o final do arquivo antes de adicionar
                    fwrite(&P, sizeof(Pessoa), 1, Ptr);
                    printf("PESSOA CADASTRADA!\n");
                }
                else
                {
                    printf("TELEFONE INVÁLIDO!\n");
                }
            }
            else
            {
                printf("TELEFONE INVÁLIDO!\n");
            }            
        }
        else
        {
            printf("PESSOA JÁ CADASTRADA!\n");
        }

        printf("ID DA PESSOA: ");
        scanf("%d", &P.id_pessoa);
    }

    fclose(Ptr);
}

void CadastroAutor(void)
{
    Autor A;
    FILE *Ptr = fopen("Autor.dat", "wb+");

    printf("## CADASTRO DE AUTORES ##\n");
    printf("ID DO AUTOR: ");
    scanf("%d", &A.id_autor);

    while (A.id_autor > 0)
    {
        if (BuscaAutor(Ptr, A.id_autor) == -1)
        {
            printf("NOME DO AUTOR: ");
            fflush(stdin);
            fgets(A.nome, sizeof(A.nome), stdin);
            A.nome[strcspn(A.nome, "\n")] = '\0';  // Remove o '\n'
            printf("NACIONALIDADE: ");
            fflush(stdin);
            fgets(A.nacionalidade, sizeof(A.nacionalidade), stdin);
            A.nacionalidade[strcspn(A.nacionalidade, "\n")] = '\0';  // Remove o '\n'
            
            A.ativo = 1;

            fseek(Ptr, 0, SEEK_END);  
            fwrite(&A, sizeof(Autor), 1, Ptr);
            printf("AUTOR CADASTRADO!\n");
        }
        else
        {
            printf("AUTOR JÁ CADASTRADO!\n");
        }

        printf("ID DO AUTOR: ");
        scanf("%d", &A.id_autor);
    }

    fclose(Ptr);
}

void CadastroLivroAutor(void)
{
    LivroAutor La;
    Livros Li;
    Autor Au;
    FILE *PtrLa = fopen("LivroAutor.dat", "wb+");
    FILE *PtrLi = fopen("Livros.dat", "rb+");
    FILE *PtrAu = fopen("Autores.dat", "rb+");



    printf("## CADASTRO LIVRO-AUTOR ##\n");

    // Solicitar ID do livro
    printf("ID DO LIVRO: ");
    scanf("%d", &Li.id_livro);

    while (Li.id_livro > 0)
    {
        // Buscar livro manualmente
        fseek(PtrLi, 0, SEEK_SET);  // Começar a leitura do começo do arquivo
        int livroEncontrado = 0;  // Flag para verificar se o livro foi encontrado
        while (fread(&Li, sizeof(Livros), 1, PtrLi)) {
            if (Li.id_livro == Li.id_livro) {  // Comparando o id do livro
                livroEncontrado = 1;
                break;  // Livro encontrado, parar a busca
            }
        }

        if (livroEncontrado) {
            // Solicitar ID do autor
            printf("ID DO AUTOR: ");
            scanf("%d", &Au.id_autor);

            // Buscar autor manualmente
            fseek(PtrAu, 0, SEEK_SET);  // Começar a leitura do começo do arquivo
            int autorEncontrado = 0;  // Flag para verificar se o autor foi encontrado
            while (fread(&Au, sizeof(Autor), 1, PtrAu)) {
                if (Au.id_autor == Au.id_autor) {  // Comparando o id do autor
                    autorEncontrado = 1;
                    break;  // Autor encontrado, parar a busca
                }
            }

            if (autorEncontrado) {
                // Associar livro ao autor
                La.id_livro = Li.id_livro;
                La.id_autor = Au.id_autor;

                // Gravar a associação no arquivo
                fseek(PtrLa, 0, SEEK_END);  
                fwrite(&La, sizeof(LivroAutor), 1, PtrLa);
                printf("ASSOCIAÇÃO LIVRO-AUTOR CADASTRADA!\n");
            } else {
                printf("AUTOR NÃO ENCONTRADO!\n");
            }
        } else {
            printf("LIVRO NÃO ENCONTRADO!\n");
        }

        // Pedir novo ID do livro
        printf("ID DO LIVRO: ");
        scanf("%d", &Li.id_livro);
    }

    fclose(PtrLi);
    fclose(PtrAu);
    fclose(PtrLa);
}






void AlterarDados(void)
{
    LivroAutor LA;
    Livros Li;
    Pessoa P;
    Autor A;
    int pos;
    char op;
    int encontrado;

    FILE *PtrL = fopen("Livros.dat", "rb+");
    FILE *PtrLA = fopen("AutorLivro.dat", "rb+");
    FILE *PtrP = fopen("Pessoas.dat", "rb+");
    FILE *Ptr = fopen("Autor.dat", "rb+");


    printf("## ALTERAR DADOS ##\n");
    printf("Escolha a opção de alteração:\n");
    printf("A - Alterar Autor\n");
    printf("B - Alterar Livro\n");
    printf("C - Alterar Pessoa\n");
    printf("Escolha a opção (A/B/C): ");
    op = toupper(getchar());

    switch (op)
    {
    case 'A':
        printf("\nID DO AUTOR PARA ALTERAR: ");
        scanf("%d", &A.id_autor);
        
        encontrado = 0;
        // Busca manual no arquivo de autores
        while (fread(&A, sizeof(Autor), 1, Ptr) == 1) {
            if (A.id_autor == A.id_autor) {
                printf("## DADOS ENCONTRADOS! ##\n");
                printf("NOME DO AUTOR: %s\n", A.nome);
                printf("NACIONALIDADE: %s\n", A.nacionalidade);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("I.D NÃO ENCONTRADO!\n");
        } else {
            printf("\nDESEJA ALTERAR (S/N)? ");
            getchar();  // Limpar o buffer do teclado
            if (toupper(getchar()) == 'S')
            {
                printf("\nNOVO I.D: ");
                scanf("%d", &A.id_autor);
                printf("NOVO NOME: ");
                fflush(stdin);
                fgets(A.nome, sizeof(A.nome), stdin);
                printf("NOVA NACIONALIDADE: ");
                fflush(stdin);
                fgets(A.nacionalidade, sizeof(A.nacionalidade), stdin);

                // Reposiciona o ponteiro para a posição correta e grava os dados
                fseek(Ptr, -sizeof(Autor), SEEK_CUR);
                fwrite(&A, sizeof(Autor), 1, Ptr);

                // Atualiza o arquivo AutorLivro
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
            }
        }
        break;

    case 'B':
        printf("\nID DO LIVRO PARA ALTERAR: ");
        scanf("%d", &Li.id_livro);

        encontrado = 0;
        // Busca manual no arquivo de livros
        while (fread(&Li, sizeof(Livros), 1, PtrL) == 1) {
            if (Li.id_livro == Li.id_livro) {
                printf("## DADOS ENCONTRADOS! ##\n");
                printf("TÍTULO: %s\n", Li.titulo);
                printf("ANO DE PUBLICAÇÃO: %d\n", Li.ano_publi);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("I.D NÃO ENCONTRADO!\n");
        } else {
            printf("\nDESEJA ALTERAR (S/N)? ");
            getchar();  // Limpar o buffer do teclado
            if (toupper(getchar()) == 'S')
            {
                printf("\nNOVO TÍTULO: ");
                fflush(stdin);
                fgets(Li.titulo, sizeof(Li.titulo), stdin);
                printf("NOVO ANO DE PUBLICAÇÃO: ");
                scanf("%d", &Li.ano_publi);

                // Reposiciona o ponteiro para a posição correta e grava os dados
                fseek(PtrL, -sizeof(Livros), SEEK_CUR);
                fwrite(&Li, sizeof(Livros), 1, PtrL);
                printf("\nDADOS ATUALIZADOS!\n");
            }
        }
        break;

    case 'C':
        printf("\nID DA PESSOA PARA ALTERAR: ");
        scanf("%d", &P.id_pessoa);

        encontrado = 0;
        // Busca manual no arquivo de pessoas
        while (fread(&P, sizeof(Pessoa), 1, PtrP) == 1) {
            if (P.id_pessoa == P.id_pessoa) {
                printf("## DADOS ENCONTRADOS! ##\n");
                printf("NOME: %s\n", P.nome);
                printf("TELEFONE: %s\n", P.telefone);
                printf("ENDEREÇO: %s\n", P.endereco);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("I.D NÃO ENCONTRADO!\n");
        } else {
            printf("\nDESEJA ALTERAR (S/N)? ");
            getchar();  // Limpar o buffer do teclado
            if (toupper(getchar()) == 'S')
            {
                printf("\nNOVO NOME: ");
                fflush(stdin);
                fgets(P.nome, sizeof(P.nome), stdin);
                printf("NOVO TELEFONE: ");
                fflush(stdin);
                fgets(P.telefone, sizeof(P.telefone), stdin);
                printf("NOVO ENDEREÇO: ");
                fflush(stdin);
                fgets(P.endereco, sizeof(P.endereco), stdin);

                // Reposiciona o ponteiro para a posição correta e grava os dados
                fseek(PtrP, -sizeof(Pessoa), SEEK_CUR);
                fwrite(&P, sizeof(Pessoa), 1, PtrP);
                printf("\nDADOS ATUALIZADOS!\n");
            }
        }
        break;

    default:
        printf("Opção inválida.\n");
        break;
    }

    fclose(Ptr);
    fclose(PtrP);
    fclose(PtrLA);
    fclose(PtrL);
}


void RealizarEmprestimo(void) {
    Livros Li;
    Emprestimo Em;
    Pessoa P;

    FILE *PtrLi = fopen("Livros.dat", "rb");
    FILE *PtrEm = fopen("Emprestimos.dat", "ab+");
    FILE *PtrPe = fopen("Pessoas.dat", "rb");

    if (PtrLi == NULL || PtrEm == NULL || PtrPe == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    printf("## EFETUAR EMPRÉSTIMOS ##\n");

    printf("I.D PESSOA: ");
    scanf("%d", &P.id_pessoa);

    // Buscar manualmente a pessoa no arquivo
    int pessoaEncontrada = 0;
    fseek(PtrPe, 0, SEEK_SET);  // Volta ao início do arquivo para a leitura correta

    while (fread(&P, sizeof(Pessoa), 1, PtrPe)) {
        if (P.id_pessoa == P.id_pessoa) {  // Se o ID da pessoa no arquivo for igual ao ID fornecido
            pessoaEncontrada = 1;  // Marca que a pessoa foi encontrada
            break;  // Não precisa continuar a busca depois de encontrar
        }
    }

    if (pessoaEncontrada) {
        printf("## PESSOA ENCONTRADA! ##\n");
        printf("I.D: %d\n", P.id_pessoa);
        printf("NOME: %s\n", P.nome);
        printf("TELEFONE: %s\n", P.telefone);
        printf("ENDEREÇO: %s\n", P.endereco);

        // Pergunta se a pessoa deseja realizar o empréstimo
        printf("REALIZAR EMPRÉSTIMO (S/N)? ");
        if (toupper(getche()) == 'S') {
            printf("I.D DO LIVRO PARA EMPRÉSTIMO: ");
            scanf("%d", &Li.id_livro);

            // Buscar manualmente o livro no arquivo
            int livroEncontrado = 0;
            fseek(PtrLi, 0, SEEK_SET);  // Volta ao início do arquivo para a leitura correta

            while (fread(&Li, sizeof(Livros), 1, PtrLi)) {
                if (Li.id_livro == Li.id_livro) {  // Se o ID do livro no arquivo for igual ao ID fornecido
                    livroEncontrado = 1;  // Marca que o livro foi encontrado
                    break;  // Não precisa continuar a busca depois de encontrar
                }
            }

            if (livroEncontrado) {
                printf("LIVRO ENCONTRADO!\n");
                printf("I.D: %d\n", Li.id_livro);
                printf("TÍTULO: %s\n", Li.titulo);
                printf("ANO DE PUBLICAÇÃO: %d\n", Li.ano_publi);

                // Confirmação do empréstimo
                printf("CONFIRMAR EMPRÉSTIMO DO LIVRO '%s' PARA '%s' (S/N)? ", Li.titulo, P.nome);
                if (toupper(getche()) == 'S') {
                    printf("\nDigite o ID do Empréstimo: ");
                    scanf("%d", &Em.id_emprestimo);

                    // Data do empréstimo
                    printf("QUAL O DIA DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.dia);
                    printf("QUAL O MÊS DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.mes);
                    printf("QUAL O ANO DO EMPRÉSTIMO? ");
                    scanf("%d", &Em.ano);

                    // Validação da data do empréstimo
                    if (Em.mes < 1 || Em.mes > 12) {
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
                            printf("DIA INVÁLIDO! ESTE MÊS POSSUI APENAS %d DIAS.\n", diasNoMes);
                        } else {
                            sprintf(Em.data_emprestimo, "%02d/%02d/%04d", Em.dia, Em.mes, Em.ano);
                            fwrite(&Em, sizeof(Emprestimo), 1, PtrEm);

                            // Data de devolução
                            printf("QUAL O DIA DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                            scanf("%d", &Em.dia);
                            printf("QUAL O MÊS DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                            scanf("%d", &Em.mes);
                            printf("QUAL O ANO DA DEVOLUÇÃO DO EMPRÉSTIMO? ");
                            scanf("%d", &Em.ano);

                            // Validação da data de devolução
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
                                    fwrite(&Em, sizeof(Emprestimo), 1, PtrEm);
                                    printf("Empréstimo realizado com sucesso!\n");
                                }
                            }
                        }
                    }
                }
            } else {
                printf("Livro não encontrado.\n");
            }
        }
    } else {
        printf("Pessoa não encontrada.\n");
    }

    fclose(PtrPe);
    fclose(PtrEm);
    fclose(PtrLi);
}

void ConsultarDados() {
    char opcao;
    Autor A;
    Livros L;
    Pessoa P;
    Emprestimo E;
    int pos;

    system("cls");
    printf("## CONSULTA DE DADOS ##\n");
    printf("Escolha uma opção:\n");
    printf("a) Autor\n");
    printf("b) Livro\n");
    printf("c) Pessoa\n");
    printf("d) Empréstimo\n");
    printf("Opção: ");
    scanf(" %c", &opcao);

    switch(opcao) {
        case 'a': {
            FILE *PtrA = fopen("Autor.dat", "rb");
            if (PtrA == NULL) {
                printf("Erro ao abrir o arquivo de autores.\n");
            } else {
                printf("## CONSULTA DE AUTORES ##\n");
                printf("I.D DO AUTOR: ");
                scanf("%d", &A.id_autor);

                int encontrado = 0;
                // Lê todos os autores e faz a consulta manual
                while (fread(&A, sizeof(Autor), 1, PtrA) == 1) {
                    if (A.id_autor == A.id_autor) {  // Aqui, você precisa comparar com o id do usuário
                        printf("DADOS ENCONTRADOS!\n");
                        printf("I.D AUTOR: %d\n", A.id_autor);
                        printf("NOME DO AUTOR: %s\n", A.nome);
                        printf("NACIONALIDADE: %s\n", A.nacionalidade);
                        encontrado = 1;
                    }
                }

                if (!encontrado) {
                    printf("I.D NÃO ENCONTRADO!\n");
                }

                fclose(PtrA);
            }
        }
        break;

        case 'b': {
            FILE *PtrL = fopen("Livros.dat", "rb");
            if (PtrL == NULL) {
                printf("Erro ao abrir o arquivo de livros.\n");
            } else {
                printf("## CONSULTA DE LIVROS ##\n");
                printf("I.D DO LIVRO: ");
                scanf("%d", &L.id_livro);

                int encontrado = 0;
                // Lê todos os livros e faz a consulta manual
                while (fread(&L, sizeof(Livros), 1, PtrL) == 1) {
                    if (L.id_livro == L.id_livro) {  // Aqui, você precisa comparar com o id do usuário
                        printf("DADOS ENCONTRADOS!\n");
                        printf("I.D LIVRO: %d\n", L.id_livro);
                        printf("TÍTULO: %s\n", L.titulo);
                        printf("ANO DE PUBLICAÇÃO: %d\n", L.ano_publi);
                        encontrado = 1;
                    }
                }

                if (!encontrado) {
                    printf("I.D NÃO ENCONTRADO!\n");
                }

                fclose(PtrL);
            }
        }
        break;

        case 'c': {
            FILE *PtrP = fopen("Pessoas.dat", "rb");
            if (PtrP == NULL) {
                printf("Erro ao abrir o arquivo de pessoas.\n");
            } else {
                printf("## CONSULTA DE PESSOAS ##\n");
                printf("I.D DA PESSOA: ");
                scanf("%d", &P.id_pessoa);

                int encontrado = 0;
                // Lê todas as pessoas e faz a consulta manual
                while (fread(&P, sizeof(Pessoa), 1, PtrP) == 1) {
                    if (P.id_pessoa == P.id_pessoa) {  // Aqui, você precisa comparar com o id do usuário
                        printf("DADOS ENCONTRADOS!\n");
                        printf("I.D PESSOA: %d\n", P.id_pessoa);
                        printf("NOME: %s\n", P.nome);
                        printf("TELEFONE: %s\n", P.telefone);
                        printf("ENDEREÇO: %s\n", P.endereco);
                        encontrado = 1;
                    }
                }

                if (!encontrado) {
                    printf("I.D NÃO ENCONTRADO!\n");
                }

                fclose(PtrP);
            }
        }
        break;

        case 'd': {
            FILE *PtrE = fopen("Emprestimos.dat", "rb");
            if (PtrE == NULL) {
                printf("Erro ao abrir o arquivo de empréstimos.\n");
            } else {
                printf("## CONSULTA DE EMPRÉSTIMOS ##\n");
                printf("I.D DO EMPRÉSTIMO: ");
                scanf("%d", &E.id_emprestimo);

                int encontrado = 0;
                // Lê todos os empréstimos e faz a consulta manual
                while (fread(&E, sizeof(Emprestimo), 1, PtrE) == 1) {
                    if (E.id_emprestimo == E.id_emprestimo) {  // Aqui, você precisa comparar com o id do usuário
                        printf("DADOS ENCONTRADOS!\n");
                        printf("I.D EMPRÉSTIMO: %d\n", E.id_emprestimo);
                        printf("DATA DE EMPRÉSTIMO: %s\n", E.data_emprestimo);
                        printf("DATA DE DEVOLUÇÃO: %s\n", E.data_devolucao);
                        printf("I.D PESSOA: %d\n", E.id_pessoa);
                        printf("I.D LIVRO: %d\n", E.id_livro);
                        encontrado = 1;
                    }
                }

                if (!encontrado) {
                    printf("I.D NÃO ENCONTRADO!\n");
                }

                fclose(PtrE);
            }
        }
        break;

        default:
            printf("Opção inválida!\n");
    }
}



void ExibirLivrosPorAutor(FILE *PtrLivroAutor, FILE *PtrLivros, int id_autor) {
    LivroAutor LA;
    Livros L;
    
    // Verificar se o autor existe
    if (BuscaAutor(PtrLivros, id_autor) == -1) {
        printf("Autor não encontrado!\n");
        return;
    }

    printf("Livros do autor %d:\n", id_autor);
    
    // Buscar todos os livros desse autor
    fseek(PtrLivroAutor, 0, SEEK_SET);  // Voltar ao início do arquivo
    int encontrado = 0;
    while (fread(&LA, sizeof(LivroAutor), 1, PtrLivroAutor) == 1) {
        if (LA.id_autor == id_autor) {
            if (BuscaLivro(PtrLivros, LA.id_livro) == 1) {
                fseek(PtrLivros, LA.id_livro * sizeof(Livros), SEEK_SET);  // Acessar o livro correspondente
                fread(&L, sizeof(Livros), 1, PtrLivros);
                encontrado = 1;
                printf("\nID do Livro: %d\n", L.id_livro);
                printf("Título: %s\n", L.titulo);
                printf("Ano de Publicação: %d\n", L.ano_publi);
                printf("Ativo: %d\n", L.ativo);
            }
        }
    }
    
    if (!encontrado) {
        printf("Nenhum livro encontrado para esse autor.\n");
    }
}

void ExibirAutorPorLetra(char letra);
void ExibirLivroPorPalavra(char *palavra);
void ExibirEmprestimoPorPessoa(int id_pessoa);
void ExibirLivrosPorAutor(int id_autor);
void ExibirEmprestimoPorPessoaDetalhado(void);
void RelatorioCompleto(void);

void relatorios() {
    char opcao;

    // Limpa a tela (uso de sistema operacional moderno)
    system("cls");  // Para Windows
    // system("clear");  // Para sistemas Unix/Linux

    printf("## MENU DE RELATÓRIOS ##\n");
    printf("A. Relatório de autores por letra\n");
    printf("B. Relatório de livros por palavra no título\n");
    printf("C. Relatório de empréstimos por pessoa\n");
    printf("D. Relatório de livros por autor\n");
    printf("E. Relatório de empréstimos separados por pessoa\n");
    printf("F. Relatório Completo\n");
    printf("G. Sair\n");

    printf("Escolha uma opção (A-G): ");
    opcao = getchar();  // Usa getchar() para ler a opção
    opcao = toupper(opcao);  // Converte para maiúsculo
    getchar();  // Captura o Enter

    printf("\n");

    switch (opcao) {
        case 'A': {
            char letra;
            printf("Digite a letra para filtrar os autores: ");
            letra = getchar();  // Lê a letra
            letra = toupper(letra);  // Garante que a letra seja maiúscula
            getchar();  // Captura o Enter
            system("cls");  // Limpa a tela
            ExibirAutorPorLetra(letra);  // Chama a função do relatório
            break;
        }
        case 'B': {
            char palavra[50];
            printf("Digite a palavra para filtrar os livros: ");
            scanf("%s", palavra);
            getchar();  // Captura o Enter após a entrada de string
            system("cls");  // Limpa a tela
            ExibirLivroPorPalavra(palavra);  // Chama a função do relatório
            break;
        }
        case 'C': {
            int id_pessoa;
            printf("Digite o ID da pessoa para visualizar os empréstimos: ");
            scanf("%d", &id_pessoa);
            getchar();  // Captura o Enter após a entrada de número
            system("cls");  // Limpa a tela
            ExibirEmprestimoPorPessoa(id_pessoa);  // Chama a função do relatório
            break;
        }
        case 'D': {
            int id_autor;
            printf("Digite o ID do autor para visualizar os livros: ");
            scanf("%d", &id_autor);
            getchar();  // Captura o Enter após a entrada de número
            system("cls");  // Limpa a tela
            ExibirLivrosPorAutor(id_autor);  // Chama a função do relatório
            break;
        }
        case 'E': {
            system("cls");  // Limpa a tela
            ExibirEmprestimoPorPessoaDetalhado();  // Chama a função do relatório
            break;
        }
        case 'F': {
            system("cls");  // Limpa a tela
            RelatorioCompleto();  // Chama a função do relatório completo
            break;
        }
        case 'G':
            return;  // Sai do menu de relatórios
        default:
            printf("Opção inválida! Tente novamente.\n");
            getchar();  // Espera que o usuário pressione uma tecla
            break;
    }

    printf("\nPressione qualquer tecla para voltar ao menu.");
    getchar();  // Pausa a execução aguardando uma tecla
    relatorios();  // Chama novamente o menu de relatórios
}

// Função para exibir autores que começam com uma determinada letra
void ExibirAutorPorLetra(char letra) {
    // Exemplo de implementação: filtrar autores pelo nome começando com a letra fornecida
    printf("Exibindo autores que começam com a letra '%c'\n", letra);
    // Aqui você adicionaria a lógica para buscar os autores no seu banco de dados
}

// Função para exibir livros que contêm uma palavra no título
void ExibirLivroPorPalavra(char *palavra) {
    printf("Exibindo livros com o título contendo a palavra: %s\n", palavra);
    // Aqui você adicionaria a lógica para buscar os livros no seu banco de dados
}

// Função para exibir os empréstimos de uma pessoa
void ExibirEmprestimoPorPessoa(int id_pessoa) {
    printf("Exibindo empréstimos para a pessoa com ID: %d\n", id_pessoa);
    // Aqui você adicionaria a lógica para buscar os empréstimos da pessoa no seu banco de dados
}

// Função para exibir livros de um autor específico
void ExibirLivrosPorAutor(int id_autor) {
    printf("Exibindo livros do autor com ID: %d\n", id_autor);
    // Aqui você adicionaria a lógica para buscar os livros do autor no seu banco de dados
}

// Função para exibir os empréstimos detalhados por pessoa
void ExibirEmprestimoPorPessoaDetalhado(void) {
    printf("Exibindo empréstimos detalhados por pessoa.\n");
    // Aqui você adicionaria a lógica para mostrar todos os empréstimos detalhados por pessoa
}


void RelatorioCompleto() {
    char opcao;
    
    // Limpa a tela (uso de sistema operacional moderno)
    system("cls");  // Para Windows
    // system("clear");  // Para sistemas Unix/Linux

    printf("## RELATÓRIO COMPLETO ##\n");
    printf("Escolha qual relatório completo deseja gerar:\n");
    printf("1. Relatório de Autores\n");
    printf("2. Relatório de Livros\n");
    printf("3. Relatório de Pessoas\n");
    printf("4. Relatório de Empréstimos\n");
    printf("5. Voltar\n");

    printf("Escolha uma opção (1-5): ");
    opcao = getchar();  // Usa getchar() para ler a opção
    opcao = toupper(opcao);  // Converte para maiúsculo

    printf("\n");

    switch (opcao) {
        case '1':
            system("cls");  // Limpa a tela
            RelatorioAutoresCompleto();  // Chama a função de relatório de autores
            break;
        case '2':
            system("cls");  // Limpa a tela
            RelatorioLivrosCompleto();  // Chama a função de relatório de livros
            break;
        case '3':
            system("cls");  // Limpa a tela
            RelatorioPessoasCompleto();  // Chama a função de relatório de pessoas
            break;
        case '4':
            system("cls");  // Limpa a tela
            RelatorioEmprestimosCompleto();  // Chama a função de relatório de empréstimos
            break;
        case '5':
            return;  // Volta ao menu anterior
        default:
            printf("Opção inválida! Tente novamente.\n");
            getchar();  // Espera o usuário pressionar uma tecla
            RelatorioCompleto();  // Tenta novamente
            break;
    }

    // Espera o usuário pressionar uma tecla para voltar ao menu
    printf("\nPressione qualquer tecla para voltar ao menu.");
    getchar();  // Pausa a execução aguardando uma tecla
}

void ExibirAutoresPorLetra(char letra) {
    FILE *Ptr = fopen("Autor.dat", "rb");  // Abre o arquivo de autores em modo leitura binária
    if (Ptr == NULL) {
        printf("Erro ao abrir o arquivo de autores.\n");
        return;  // Se o arquivo não foi aberto corretamente, retorna
    }

    Autor autores[100];  // Array para armazenar os autores encontrados
    int numAutores = 0;

    // Buscar autores cujo nome começa com a letra fornecida
    fseek(Ptr, 0, SEEK_SET);  // Ir para o início do arquivo
    Autor Au;

    while (fread(&Au, sizeof(Autor), 1, Ptr) == 1) {
        // Verifica se o nome do autor começa com a letra fornecida
        if (Au.nome[0] == letra || Au.nome[0] == letra + 32) {  // Maiúscula ou minúscula
            autores[numAutores++] = Au;  // Armazena o autor no array
        }
    }

    if (numAutores == 0) {
        printf("Nenhum autor encontrado com a letra '%c'.\n", letra);
        fclose(Ptr);  // Fecha o arquivo
        return;
    }

    // Ordenar os autores pela nacionalidade
    for (int i = 0; i < numAutores - 1; i++) {
        for (int j = i + 1; j < numAutores; j++) {
            if (strcmp(autores[i].nacionalidade, autores[j].nacionalidade) > 0) {
                // Troca de posições
                Autor temp = autores[i];
                autores[i] = autores[j];
                autores[j] = temp;
            }
        }
    }

    // Exibir o relatório ordenado
    printf("Autores cujo nome começa com '%c', ordenados por nacionalidade:\n", letra);
    for (int i = 0; i < numAutores; i++) {
        printf("\nID do Autor: %d\n", autores[i].id_autor);
        printf("Nome: %s\n", autores[i].nome);
        printf("Nacionalidade: %s\n", autores[i].nacionalidade);
        printf("Ativo: %d\n", autores[i].ativo);
    }

    fclose(Ptr);  // Fecha o arquivo após o uso
}

void ExibirLivrosPorPalavra(char *palavra) {
    FILE *Ptr = fopen("Livros.dat", "rb");  // Abre o arquivo de livros em modo leitura binária

    if (Ptr == NULL) {
        printf("Erro ao abrir o arquivo de livros.\n");
        return;  // Se o arquivo não foi aberto corretamente, retorna
    }

    Livros livros[100];  // Array para armazenar os livros encontrados
    int numLivros = 0;

    // Buscar livros cujo título contenha a palavra fornecida
    fseek(Ptr, 0, SEEK_SET);  // Ir para o início do arquivo
    Livros L;

    while (fread(&L, sizeof(Livros), 1, Ptr) == 1) {
        // Verifica se o título do livro contém a palavra fornecida
        if (strstr(L.titulo, palavra) != NULL) {
            livros[numLivros++] = L;  // Armazena o livro no array
        }
    }

    if (numLivros == 0) {
        printf("Nenhum livro encontrado com a palavra '%s'.\n", palavra);
        fclose(Ptr);  // Fecha o arquivo antes de retornar
        return;
    }

    // Ordenar os livros pelo ano de publicação (ordem crescente)
    for (int i = 0; i < numLivros - 1; i++) {
        for (int j = i + 1; j < numLivros; j++) {
            if (livros[i].ano_publi > livros[j].ano_publi) {
                // Troca de posições
                Livros temp = livros[i];
                livros[i] = livros[j];
                livros[j] = temp;
            }
        }
    }

    // Exibir o relatório ordenado
    printf("Livros com títulos que contém a palavra '%s', ordenados pelo ano de publicação:\n", palavra);
    for (int i = 0; i < numLivros; i++) {
        printf("\nID do Livro: %d\n", livros[i].id_livro);
        printf("Título: %s\n", livros[i].titulo);
        printf("Ano de Publicação: %d\n", livros[i].ano_publi);
        printf("Ativo: %d\n", livros[i].ativo);
    }

    fclose(Ptr);  // Fecha o arquivo após o uso
}


void ExibirEmprestimosPorPessoaDetalhado(FILE *PtrEmprestimos, FILE *PtrPessoas) {
    Emprestimo E;
    Pessoa P;

    fseek(PtrEmprestimos, 0, SEEK_SET);
    fseek(PtrPessoas, 0, SEEK_SET);
    
    // Loop para percorrer todas as pessoas
    while (fread(&P, sizeof(Pessoa), 1, PtrPessoas) == 1) {
        printf("\nEmpréstimos de %s (ID: %d):\n", P.nome, P.id_pessoa);
        int encontrouEmprestimos = 0;
        
        // Para cada pessoa, busca seus empréstimos
        fseek(PtrEmprestimos, 0, SEEK_SET);
        while (fread(&E, sizeof(Emprestimo), 1, PtrEmprestimos) == 1) {
            if (E.id_pessoa == P.id_pessoa) {
                encontrouEmprestimos = 1;
                printf("\nID do Empréstimo: %d\n", E.id_emprestimo);
                printf("ID do Livro: %d\n", E.id_livro);
                printf("Data de Empréstimo: %s\n", E.data_emprestimo);
                printf("Data de Devolução: %s\n", E.data_devolucao);
                printf("Ativo: %d\n", E.ativo);
            }
        }
        
        if (!encontrouEmprestimos) {
            printf("Nenhum empréstimo encontrado.\n");
        }
    }
}

void ExibirEmprestimosPorPessoa(FILE *PtrEmprestimos, FILE *PtrPessoas, int id_pessoa) {
    Emprestimo E;
    Pessoa P;
    
    // Verificar se a pessoa existe
    if (BuscaPessoa(PtrPessoas, id_pessoa) == -1) {
        printf("Pessoa não encontrada!\n");
        return;
    }

    printf("Empréstimos realizados por %d:\n", id_pessoa);
    
    // Buscar todos os empréstimos dessa pessoa
    fseek(PtrEmprestimos, 0, SEEK_SET);  // Voltar ao início do arquivo
    int encontrado = 0;
    while (fread(&E, sizeof(Emprestimo), 1, PtrEmprestimos) == 1) {
        if (E.id_pessoa == id_pessoa) {
            encontrado = 1;
            printf("\nID do Empréstimo: %d\n", E.id_emprestimo);
            printf("ID do Livro: %d\n", E.id_livro);
            printf("Data de Empréstimo: %s\n", E.data_emprestimo);
            printf("Data de Devolução: %s\n", E.data_devolucao);
            printf("Ativo: %d\n", E.ativo);
        }
    }
    
    if (!encontrado) {
        printf("Nenhum empréstimo encontrado para essa pessoa.\n");
    }
}


// Funções para Relatórios Completos (Autores, Livros, Pessoas, Empréstimos)
void RelatorioAutoresCompleto() {
    Autor A;
    FILE *PtrAutores = fopen("Autor.dat", "rb+");

    if (PtrAutores == NULL) {
        printf("Erro ao abrir arquivo de autores!\n");
    } else {
        printf("## Relatório Completo de Autores ##\n");

        rewind(PtrAutores);
        while (fread(&A, sizeof(struct Autor), 1, PtrAutores) == 1) {
            printf("ID: %d | Nome: %s | Nacionalidade: %s\n", A.id_autor, A.nome, A.nacionalidade);
        }

        fclose(PtrAutores);
    }
}

void RelatorioLivrosCompleto() {
    Livros L;
    FILE *PtrLivros = fopen("Livros.dat", "rb+");

    if (PtrLivros == NULL) {
        printf("Erro ao abrir arquivo de livros!\n");
    } else {
        printf("## Relatório Completo de Livros ##\n");

        rewind(PtrLivros);
        while (fread(&L, sizeof(struct Livros), 1, PtrLivros) == 1) {
            printf("ID: %d | Título: %s | Ano de Publicação: %d\n", L.id_livro, L.titulo, L.ano_publi);
        }

        fclose(PtrLivros);
    }
}

void RelatorioPessoasCompleto() {
    Pessoa P;
    FILE *PtrPessoas = fopen("Pessoas.dat", "rb+");

    if (PtrPessoas == NULL) {
        printf("Erro ao abrir arquivo de pessoas!\n");
    } else {
        printf("## Relatório Completo de Pessoas ##\n");

        rewind(PtrPessoas);
        while (fread(&P, sizeof(struct Pessoa), 1, PtrPessoas) == 1) {
            printf("ID: %d | Nome: %s | Telefone: %s | Endereço: %s\n", P.id_pessoa, P.nome, P.telefone, P.endereco);
        }

        fclose(PtrPessoas);
    }
}

void RelatorioEmprestimosCompleto() {
   	Emprestimo E;
    FILE *PtrEmprestimos = fopen("Emprestimos.dat", "rb+");

    if (PtrEmprestimos == NULL) {
        printf("Erro ao abrir arquivo de empréstimos!\n");
    } else {
        printf("## Relatório Completo de Empréstimos ##\n");
        
        rewind(PtrEmprestimos);
        while (fread(&E, sizeof(struct Emprestimo), 1, PtrEmprestimos) == 1) {
            printf("ID: %d | Livro ID: %d | Pessoa ID: %d | Data de Empréstimo: %s | Data de Devolução: %s\n",
                   E.id_emprestimo, E.id_livro, E.id_pessoa, E.data_emprestimo, E.data_devolucao);
        }

        fclose(PtrEmprestimos);
    }
}

char Menu(void) {
    char op;

    system("cls");  // Limpa a tela (funciona em sistemas Windows)

    // Exibe o título do menu
    printf("## MENU ##\n");

    // Exibe as opções do menu
    printf("[A] CADASTRAR LIVROS\n");
    printf("[B] CADASTRAR AUTOR\n");
    printf("[C] CADASTRAR PESSOA\n");
    printf("[D] CADASTRAR LIVRO-AUTOR\n");
    printf("[E] EXIBIR CADASTROS\n");
    printf("[F] EXCLUSÃO LÓGICA\n");
    printf("[G] EXCLUSÃO FÍSICA\n");
    printf("[H] ALTERAÇÃO POR ID\n");
    printf("[I] CONSULTAR POR ID\n");
    printf("[J] RELATÓRIO\n");
    printf("[K] REALIZAR EMPRÉSTIMO\n");

    printf("[0] PARA SAIR\n");

    // Solicita a escolha do usuário
    printf("Escolha a opção: ");
    op = toupper(getche());  // Captura a opção escolhida (converte para maiúsculo)

    return op;
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");  // Configura a localidade para português
    char op;

    do {
        op = Menu();  // Chama o menu e armazena a escolha

        // Realiza a ação de acordo com a opção escolhida
        switch(op) {
            case 'A': 
                // Chama a função de cadastro de livros
                CadastroLivros();  
                break;
            case 'B': 
                // Chama a função de cadastro de autor
                CadastroAutor();  
                break;
            case 'C': 
                // Chama a função de cadastro de pessoa
                CadastroPessoa();  
                break;
            case 'D': 
                // Chama a função de cadastro livro-autor
                CadastroLivroAutor();  
                break;
            case 'E': 
                // Chama a função para exibir os cadastros
                MenuExibirCadastros();  
                break;
            case 'F': 
                // Chama a função para exclusão lógica
                ExclusaoLogica();  
                break;
            case 'G': 
                // Chama a função para exclusão física
                ExclusaoFisica();  
                break;
            case 'H': 
                // Chama a função para alteração de dados
                AlterarDados();  
                break;
            case 'I': 
                // Chama a função para consultar dados
                ConsultarDados();  
                break;
            case 'J': 
                // Chama a função para relatórios
                relatorios();  
                break;
            case 'K': 
                // Chama a função para realizar empréstimo
                RealizarEmprestimo();  
                break;
            case '0': 
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        // Limpa o buffer de entrada (caso o usuário tenha pressionado enter extra)
        while(getchar() != '\n');

    } while(op != '0');  // Sai quando o usuário digitar '0'

    return 0;
}
