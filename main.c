#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Arquivos

FILE *arquivoDeLivros;
FILE *arquivoDeUsuarios;
FILE *arquivoDeEmprestimos;

// Variaveis/Vetores
int opcao, opc;
int usuariosCadastrados = 1;
char voltar[10];

// Estrutras de dados Structs(Classes)
struct data {
    int dia;
    int mes;
    int ano;
};

struct cadastroDeLivros  {
    int codigoDoLivro;
    char titulo[100];
    char autor[80];
    char editora[60];
    struct data anoDePublicacao;
    int numeroDeExemplaresDisponiveis;
    int status;
};

struct cadastroDeUsuarios {
    int matricula;
    char nomeCompleto[100];
    char curso[50];
    char telefone[50];
    struct data dataDeNacimento;
};

struct sistemaDeEmprestimos{
    int codigoDoEmprestimo;
    int matriculaDoUsuario;
    int codigoDoLivro;
    struct data dataDeEmprestimo;
    struct data dataPrevistaDevolucao;
    int status;
};

// Vetores de Struct
struct cadastroDeLivros Livros[10];
struct cadastroDeUsuarios Usuarios[10];
struct sistemaDeEmprestimos Emprestimos[10];

// Vetores de Struct
struct cadastroDeLivros Livros[10];
struct cadastroDeUsuarios Usuarios[10];
struct sistemaDeEmprestimos Emprestimos[10];

// Declaração de funções
int carregarDadosLivros();
int carregarDadosUsuarios();
int carregarDadosEmprestimos();
int incrementarContadorLivros(int valorAtual);
int incrementarContadorUsuarios(int valorAtual);
int inicializarCadastroDeLivros();
int inicializarCadastroDeUsuarios();
int inicializarRealizarEmprestimos(int numeroLivro);
void realizarDevolucoes();
void pesquisarLivrosRealizarEmprestimos();
void pesquisarUsuariosExistentes();
int listaDeEmprestimosAtivos();
int voltarAoInicio();
void mostrarMenu();

// Carregar dados dos arquivos

int carregarDadosLivros() {
    int c = 1;
    char linha[256];
    int maxLivros = 10;
    int numeroDoLivro;

    arquivoDeLivros = fopen("livros.txt", "a");
    fclose(arquivoDeLivros);

    arquivoDeLivros = fopen("livros.txt", "r");
    if (arquivoDeLivros == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    do {
        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, "Livro %d Salvo", &numeroDoLivro) != 1) {
                printf("Erro ao ler o numero do livro.\n");
            }
        };

        // Linha vazia
        fgets(linha, 256, arquivoDeLivros);

        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, "%*s %d", &Livros[numeroDoLivro].codigoDoLivro) != 1) {
                // Tratamento de erro se o formato estiver errado
                printf("Erro ao ler o Codigo.\n");
            }
        } else {
            fclose(arquivoDeLivros);
            return 0;
        }

        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, "%*s %99[^\n]", Livros[numeroDoLivro].titulo) != 1) {
                printf("Erro ao ler o Titulo.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, "%*s %99[^\n]", Livros[numeroDoLivro].autor) != 1) {
                printf("Erro ao ler o Autor.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, "%*s %99[^\n]", Livros[numeroDoLivro].editora) != 1) {
                printf("Erro ao ler a Editora.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, " Ano de publicacao: %d/%d/%d",
                &Livros[numeroDoLivro].anoDePublicacao.dia,
                &Livros[numeroDoLivro].anoDePublicacao.mes,
                &Livros[numeroDoLivro].anoDePublicacao.ano) != 3) {
                printf("Erro ao ler a Ano.\n");
                }
        }

        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, "%*s %d", &Livros[numeroDoLivro].numeroDeExemplaresDisponiveis) != 1) {
                printf("Erro ao ler Exemplares.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeLivros) != NULL) {
            if (sscanf(linha, "%*s %d", &Livros[numeroDoLivro].status) != 1) {
                printf("Erro ao ler Status.\n");
            }
        }

        // Linha vazia
        fgets(linha, 256, arquivoDeLivros);

        // Linha vazia
        fgets(linha, 256, arquivoDeLivros);

    } while (numeroDoLivro <= maxLivros);

    fclose(arquivoDeLivros);
    return c;
}

int carregarDadosUsuarios() {
    char linha[256];
    int maxUsuarios = 10;
    int numeroDoUsuario;

    arquivoDeUsuarios = fopen("Usuarios.txt", "a");
    fclose(arquivoDeUsuarios);

    arquivoDeUsuarios = fopen("usuarios.txt", "r");
    if (arquivoDeUsuarios == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    do {
        if (fgets(linha, 256, arquivoDeUsuarios) == NULL) {
            return 0;
        }

        if (sscanf(linha, "Usuario %d Salvo", &numeroDoUsuario) != 1) {
            printf("Erro ao ler o formato do cabeçalho de usuário.\n");
            return 0;
        }

        // Linha vazia
        fgets(linha, 256, arquivoDeUsuarios);

        if (fgets(linha, 256, arquivoDeUsuarios) != NULL) {
            if (sscanf(linha, "%*s %99[^\n]", Usuarios[numeroDoUsuario].nomeCompleto) != 1) {
                printf("Erro ao ler o Nome.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeUsuarios) != NULL) {
            if (sscanf(linha, "%*s %d", &Usuarios[numeroDoUsuario].matricula) != 1) {
                printf("Erro ao ler a Matricula.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeUsuarios) != NULL) {
            if (sscanf(linha, "%*s %99[^\n]", Usuarios[numeroDoUsuario].telefone) != 1) {
                printf("Erro ao ler o Telefone.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeUsuarios) != NULL) {
            if (sscanf(linha, "%*s %99[^\n]", Usuarios[numeroDoUsuario].curso) != 1) {
                printf("Erro ao ler o curso.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeUsuarios) != NULL) {
            if (sscanf(linha, "%*s %*s %*s %d/%d/%d",
                &Usuarios[numeroDoUsuario].dataDeNacimento.dia,
                &Usuarios[numeroDoUsuario].dataDeNacimento.mes,
                &Usuarios[numeroDoUsuario].dataDeNacimento.ano) != 3) {
                printf("Erro ao ler a Data de Nacimento.\n");
                }
        }

        // Linha vazia
        fgets(linha, 256, arquivoDeUsuarios);

        // Linha vazia
        fgets(linha, 256, arquivoDeUsuarios);
    } while (numeroDoUsuario <= maxUsuarios);
    fclose(arquivoDeUsuarios);
    return 1;
}

int carregarDadosEmprestimos() {
    char linha[256];
    int maxEmprestimos = 10;
    int numeroDoEmprestimo = 1;

    arquivoDeEmprestimos = fopen("emprestimos.txt", "a");
    fclose(arquivoDeEmprestimos);

    arquivoDeEmprestimos = fopen("emprestimos.txt", "r");
    if (arquivoDeEmprestimos == NULL) {
        perror("Erro ao abrir arquivo de emprestimos!");
    }

    while (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
        if (sscanf(linha, "Codigo do emprestimo: %d", &numeroDoEmprestimo) != 1) {
            printf("Erro ao ler o codigo do emprestimo.\n");
            return 0;
        }
        Emprestimos[numeroDoEmprestimo].codigoDoEmprestimo = numeroDoEmprestimo;

        if (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
            if (sscanf(linha, "Matricula do usuario: %d", &Emprestimos[numeroDoEmprestimo].matriculaDoUsuario) != 1) {
                printf("Erro ao ler o matricula do usuario.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
            if (sscanf(linha, "Codigo do livro: %d", &Emprestimos[numeroDoEmprestimo].codigoDoLivro) != 1) {
                printf("Erro ao ler o codigo do livro.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
            if (sscanf(linha, "Data do emprestimo: %d/%d/%d",
                &Emprestimos[numeroDoEmprestimo ].dataDeEmprestimo.dia,
                &Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes,
                &Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.ano) != 3) {
                printf("Erro ao ler o Data de emprestimo. Linha lida: %s", linha);
                }
        }

        if (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
            if (sscanf(linha, "Data prevista de devolucao: %d/%d/%d",
                &Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.dia,
                &Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.mes,
                &Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.ano) != 3) {
                printf("Erro ao ler data de devolucao.");
                }
        }

        if (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
            if (sscanf(linha, "Status do emprestimo: %d", &Emprestimos[numeroDoEmprestimo].status) != 1) {
                printf("Erro ao ler status.\n");
            }
        }

        if (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
            if (sscanf(linha, "Devolver nova quantidade de livros: %d",
                &Livros[Emprestimos[numeroDoEmprestimo].codigoDoLivro].numeroDeExemplaresDisponiveis) != 1) {
                printf("Erro ao devolver qtd de livros");
                }
        }

        if (fgets(linha, 256, arquivoDeEmprestimos) != NULL) {
            if (sscanf(linha, "Devolver status do livro: %d",
                &Livros[Emprestimos[numeroDoEmprestimo].codigoDoLivro].status) != 1) {
                printf("Erro ao devolver status");
                }
        }

        fgets(linha, 256, arquivoDeEmprestimos);
        fgets(linha, 256, arquivoDeEmprestimos);
    }

    fclose(arquivoDeEmprestimos);
    return 1;
}

// Funcoes

int incrementarContadorLivros(int valorAtual) {
    int cadastros = valorAtual + 1;

    FILE *contadorLivros = fopen("cadastroDeLivros.txt", "w");

    if (contadorLivros == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    fprintf(contadorLivros, "Livros Cadastrados: %i\n", cadastros);
    fclose(contadorLivros);
}

int incrementarContadorUsuarios(int valorAtual) {
    int cadastros = valorAtual + 1;

    FILE *contadorUsuarios = fopen("cadastroDeUsuarios.txt", "w");

    if (contadorUsuarios == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 0;
    }

    fprintf(contadorUsuarios, "Livros Cadastrados: %i\n", cadastros);
    fclose(contadorUsuarios);
}

// Funcoes Modulares

int inicializarCadastroDeLivros() {
    // Cadastro de Livros

    // Ler o arquivo que conta o numero de cadastros
    char linha[256];
    int contador = 0;

    // Caso nao exista o arquivo ele vai criar para fazer a leitura
    FILE *numLivroCadastros = fopen("cadastroDeLivros.txt", "a");
    fclose(numLivroCadastros);

    numLivroCadastros = fopen("cadastroDeLivros.txt", "r");
    if (numLivroCadastros== NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    if (fgets(linha, 256, numLivroCadastros) != NULL) {
        int livrosCadastrados = sscanf(linha, "Livros Cadastrados: %d \n", &contador);

    }

    fclose(numLivroCadastros);
    // Se nao tiver nenhum cadastro no arquivo, inicia o cadastro numero 1
    if (contador == 0) {
        contador = 1;
    }

    // Abrir o arquivo para salvar dados
    arquivoDeLivros = fopen("livros.txt", "a");
    if (arquivoDeLivros == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Inicio do cadastro
    printf("VOCE INICIOU O CADASTRO DE LIVROS! \n");
    printf("\n\n");

    Livros[contador].codigoDoLivro = contador;
    printf("Codigo do livro definido!\n"
           "CODIGO DO LIVRO: %d\n\n", Livros[contador].codigoDoLivro);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("DIGITE O TITULO DO LIVRO:");
    fgets(Livros[contador].titulo, 100, stdin);

    printf("DIGITE O AUTOR DO LIVRO:");
    fgets(Livros[contador].autor, 80, stdin);

    printf("DIGITE A EDITORA DO LIVRO:");
    fgets(Livros[contador].editora, 60, stdin);

    printf("DIGITE O ANO DE PUBLICACAO DO LIVRO (DD MM AAAA):");
    scanf("%d %d %d",
        &Livros[contador].anoDePublicacao.dia,
        &Livros[contador].anoDePublicacao.mes,
        &Livros[contador].anoDePublicacao.ano);

    printf("DIGITE O NUMERO DE EXEMPLARES DISPONIVEIS:");
    scanf("%i", &Livros[contador].numeroDeExemplaresDisponiveis);

    Livros[contador].status = 0;
    printf("\n\n");

    printf("LIVRO CADASTRADO COM SUCESSO! \n\n");
    printf("Codigo do livro: %i\n", Livros[contador].codigoDoLivro);
    printf("Titulo do livro: %s", Livros[contador].titulo);
    printf("Autor do livro: %s", Livros[contador].autor);
    printf("Editora do Livro: %s", Livros[contador].editora);
    printf("Ano de publicacao do livro: %i/%i/%i\n",
        Livros[contador].anoDePublicacao.dia,
        Livros[contador].anoDePublicacao.mes,
        Livros[contador].anoDePublicacao.ano);
    printf("Numero de Exemplares: %i\n", Livros[contador].numeroDeExemplaresDisponiveis);

    // Salvando no arquivo livros.txt
    fprintf(arquivoDeLivros, "Livro %d Salvo\n\n", contador);
    fprintf(arquivoDeLivros, "Codigo: %i\n", Livros[contador].codigoDoLivro);
    fprintf(arquivoDeLivros,  "Titulo: %s", Livros[contador].titulo);
    fprintf(arquivoDeLivros, "Autor: %s", Livros[contador].autor);
    fprintf(arquivoDeLivros, "Editora: %s", Livros[contador].editora);
    fprintf(arquivoDeLivros, "Ano de publicacao: %i/%i/%i\n",
        Livros[contador].anoDePublicacao.dia,
        Livros[contador].anoDePublicacao.mes,
        Livros[contador].anoDePublicacao.ano);
    fprintf(arquivoDeLivros, "Exemplares: %i\n", Livros[contador].numeroDeExemplaresDisponiveis);
    fprintf(arquivoDeLivros, "Status: %i\n", Livros[contador].status);


    // Incrementos
    fprintf(arquivoDeLivros, "----\n\n"); // Separador entre registros
    fclose(arquivoDeLivros);
    incrementarContadorLivros(contador);

    return 0;
};

int inicializarCadastroDeUsuarios() {
    // Cadastro de  Usuarios

    // Ler o arquivo que conta o numero de cadastros
    char linha[256];
    int contador = 0;

    // Caso nao exista o arquivo ele vai criar para fazer a leitura
    FILE *numUsuariosCadastros = fopen("cadastroDeUsuarios.txt", "a");
    fclose(numUsuariosCadastros);

    numUsuariosCadastros = fopen("cadastroDeUsuarios.txt", "r");
    if (numUsuariosCadastros == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    if (fgets(linha, 256, numUsuariosCadastros) != NULL) {
        int livrosCadastrados = sscanf(linha, "Usuarios Cadastrados: %d \n", &contador);
    }
    fclose(numUsuariosCadastros);

    // Se nao tiver nenhum cadastro no arquivo, inicia o cadastro numero 1
    if (contador == 0) {
        contador = 1;
    }

    // Abrir o arquivo para salvar dados
    arquivoDeUsuarios = fopen("usuarios.txt", "a");
    if (arquivoDeUsuarios == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // Inicio do cadastro
    printf("VOCE INICIOU O CADASTRO DE USUARIOS! \n");
    printf("Cadastro numero %i", contador);
    printf("\n\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("DIGITE SEU NOME COMPLETO:");
    fgets(Usuarios[contador].nomeCompleto, 100, stdin);

    printf("DIGITE SEU NUMERO DE MATRICULA:");
    scanf("%i", &Usuarios[contador].matricula);

    // Lê e descarta todos os caracteres, incluindo o '\n', que restaram no buffer
    while ((c = getchar()) != '\n' && c != EOF) {}

    printf("DIGITE SEU NUMERO DE TELEFONE (DDD 123456789):");
    fgets(Usuarios[contador].telefone, 100, stdin);

    printf("DIGITE O NOME DO SEU CURSO(Ex: Engenharia de Software):");
    fgets(Usuarios[contador].curso, 50, stdin);

    printf("DIGITE O SEU ANO DE NASCIMENTO (DD MM AAAA):");
    scanf("%d %d %d",
        &Usuarios[contador].dataDeNacimento.dia,
        &Usuarios[contador].dataDeNacimento.mes,
        &Usuarios[contador].dataDeNacimento.ano
        );

    printf("\n\n");

    printf("USUARIO CADASTRADO COM SUCESSO! \n\n");
    printf("Nome: %s", Usuarios[contador].nomeCompleto);
    printf("Matricula: %i\n", Usuarios[contador].matricula);
    printf("Telefone: %s", Usuarios[contador].telefone);
    printf("Curso: %s", Usuarios[contador].curso);
    printf("Data de nascimento: %i/%i/%i\n",
        Usuarios[contador].dataDeNacimento.dia,
        Usuarios[contador].dataDeNacimento.mes,
        Usuarios[contador].dataDeNacimento.ano);

    // Salvando no arquivo Usuarios.txt

    fprintf(arquivoDeUsuarios, "Usuario %d Salvo\n\n", contador);
    fprintf(arquivoDeUsuarios, "Nome: %s", Usuarios[contador].nomeCompleto);
    fprintf(arquivoDeUsuarios,"Matricula: %i\n", Usuarios[contador].matricula);
    fprintf(arquivoDeUsuarios,"Telefone: %s", Usuarios[contador].telefone);
    fprintf(arquivoDeUsuarios,"Curso: %s", Usuarios[contador].curso);
    fprintf(arquivoDeUsuarios,"Data de nascimento: %d/%d/%d\n",
        Usuarios[contador].dataDeNacimento.dia,
        Usuarios[contador].dataDeNacimento.mes,
        Usuarios[contador].dataDeNacimento.ano);

    // Incrementos
    fprintf(arquivoDeUsuarios, "----\n\n"); // Separador entre registros
    fclose(arquivoDeUsuarios);
    incrementarContadorUsuarios(contador);

    // Lê e descarta todos os caracteres, incluindo o '\n', que restaram no buffer
    while ((c = getchar()) != '\n' && c != EOF) {}
    return 0;
};

int inicializarRealizarEmprestimos(int numeroLivro) {
    char emprestimoSN[10];
    int c = 1;

    printf("\nDeseja emprestar esse livro? (Sim/S para continuar)\n");
    printf("R:");
    scanf("%s", emprestimoSN);

    if (strcasecmp(emprestimoSN, "sim") == 0
        || strcasecmp(emprestimoSN, "s") == 0) {
        int numeroDoEmprestimo;
        printf("INICIAR EMPRESTIMO!\n\n");

        // Verificar o numero do emprestimo
        int i = 1;
        while (i <= 10) {
            if (Emprestimos[i].codigoDoEmprestimo != 0) {
                i = i + 1;
            } else {
                numeroDoEmprestimo = i;
                break;
            }
        }

        Emprestimos[numeroDoEmprestimo].codigoDoLivro = Livros[numeroLivro].codigoDoLivro;
        Emprestimos[numeroDoEmprestimo].codigoDoEmprestimo = numeroDoEmprestimo;

        printf("Livro: %s\n", Livros[numeroLivro].titulo);
        printf("Codigo do livro: %i\n", Livros[numeroLivro].codigoDoLivro);
        printf("Codigo do emprestimo: %d\n", Emprestimos[numeroDoEmprestimo].codigoDoEmprestimo);

        printf("Digite o seu numero de matricula: ");
        scanf("%i", &Emprestimos[numeroDoEmprestimo].matriculaDoUsuario);

        printf("Digite a data atual (DD MM AAAA): ");
        scanf("%i %i %i",
            &Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.dia,
            &Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes,
            &Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.ano);

        // Calculando data de devolucao

        int diaFinalMes;
        if (Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 1 ||
                Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 3 ||
                Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 5 ||
                Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 7 ||
                Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 8 ||
                Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 10 ||
                Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 12)
        {
            diaFinalMes = 31;
        } else if (Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes == 2) {
            diaFinalMes = 28;
        } else {
            diaFinalMes = 30;
        }

        Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.dia = Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.dia + 7;
        if (Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.dia > diaFinalMes) {

            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.dia -= diaFinalMes;

            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.mes = Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes + 1;

            if (Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.mes > 12) {
                Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.mes = 1;
                Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.ano = Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.ano + 1;
            } else {
                Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.ano = Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.ano;
            }
        } else {
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.mes = Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes;
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.ano = Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.ano;
        }

        printf("Voce deve devolver o livro: %s, em ate 7 dias!\n", Livros[numeroLivro].titulo);
        printf("Data de validade do emprestimo: %i/%i/%i\n",
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.dia,
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.mes,
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.ano);

        Emprestimos[numeroDoEmprestimo].status = 1;

        // Verificar se era o ultimo livro
        int devolverStatusDelivro;
        int quantidadeDeLivros = Livros[numeroLivro].numeroDeExemplaresDisponiveis - 1;
        if (quantidadeDeLivros <= 0) {
            devolverStatusDelivro = 1;
        } else {
            devolverStatusDelivro = 0;
        }

        // Salvando dados do emprestimo

        arquivoDeEmprestimos = fopen("emprestimos.txt", "a");
        if (arquivoDeEmprestimos == NULL) {
            perror("Erro ao salvar dados do emprestimo!");
        }

        fprintf(arquivoDeEmprestimos, "Codigo do emprestimo: %d\n", Emprestimos[numeroDoEmprestimo].codigoDoEmprestimo);
        fprintf(arquivoDeEmprestimos, "Matricula do usuario: %d\n", Emprestimos[numeroDoEmprestimo].matriculaDoUsuario);
        fprintf(arquivoDeEmprestimos, "Codigo do livro: %d\n", Emprestimos[numeroDoEmprestimo].codigoDoLivro);
        fprintf(arquivoDeEmprestimos, "Data do emprestimo: %d/%d/%d\n",
            Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.dia,
            Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.mes,
            Emprestimos[numeroDoEmprestimo].dataDeEmprestimo.ano);
        fprintf(arquivoDeEmprestimos, "Data prevista de devolucao: %d/%d/%d\n",
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.dia,
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.mes,
            Emprestimos[numeroDoEmprestimo].dataPrevistaDevolucao.ano);
        fprintf(arquivoDeEmprestimos, "Status do emprestimo: %d\n", Emprestimos[numeroDoEmprestimo].status);
        fprintf(arquivoDeEmprestimos, "Devolver nova quantidade de livros: %d\n" , quantidadeDeLivros);
        fprintf(arquivoDeEmprestimos, "Devolver status do livro: %d\n", devolverStatusDelivro);

        fprintf(arquivoDeEmprestimos, "----\n\n");

        fclose(arquivoDeEmprestimos);
        printf("EMPRESTIMO CONCLUIDO!");

        } else {
            printf("Emprestimo cancelado.\n");
        }
};

void realizarDevolucoes() {
    int codigoDeEmprestimo;
    int numeroDeMatricula;
    char devolucaoSN[10];

    printf("INICIAR DEVOLUCAO!\n");

    printf("Digite o codigo do seu emprestimo: ");
    scanf("%i", &codigoDeEmprestimo);

    printf("Digite o seu numero de matricula: ");
    scanf("%i", &numeroDeMatricula);

    if (codigoDeEmprestimo != Emprestimos[codigoDeEmprestimo].codigoDoEmprestimo || numeroDeMatricula != Emprestimos[codigoDeEmprestimo].matriculaDoUsuario) {
        printf("Erro ao continuar com emprestimo!\n");
        printf("Verifique o codigo e a matricula.");
        realizarDevolucoes();
    } else {
        printf("Codigo encontrado!\n");
        printf("Devolver livro? (Sim/S para continuar)\n");
        printf("R:");
        scanf("%s", devolucaoSN);

        if (strcasecmp(devolucaoSN, "sim") == 0
        || strcasecmp(devolucaoSN, "s") == 0) {
            FILE *arquivoOriginal, *arquivoTemp;
            char linha[1024];
            int codigoAtual;
            int lendoRegistroParaApagar = 0;

            arquivoOriginal = fopen("emprestimos.txt", "r");
            if (arquivoOriginal == NULL) {
                printf("Erro ao abrir o arquivo Original!");
                return;
            }

            arquivoTemp = fopen("temp.txt", "w");
            if (arquivoTemp == NULL) {
                printf("Erro ao abrir o arquivo Temp!");
                return;
            }

            while (fgets(linha, 1024, arquivoOriginal) != NULL) {
                if (sscanf(linha, "Codigo do emprestimo: %d", &codigoAtual) == 1) {
                    if (codigoAtual == codigoDeEmprestimo) {
                        lendoRegistroParaApagar = 1;
                    } else {
                        lendoRegistroParaApagar = 0;
                    }
                }

                if (strstr(linha, "----") != NULL) {
                    if (lendoRegistroParaApagar == 1) {
                        lendoRegistroParaApagar = 0;
                    }
                    continue;
                }
                if (lendoRegistroParaApagar == 0) {
                    fputs(linha, arquivoTemp);
                }
            }

            fclose(arquivoOriginal);
            fclose(arquivoDeEmprestimos);
            fclose(arquivoTemp);

            if (remove("emprestimos.txt") != 0) {
                perror("Erro ao remover arquivo!");
                return;
            }

            if (rename("temp.txt", "emprestimos.txt") != 0) {
                perror("Erro no renomear arquivo!");
            }

            printf("DEVOLUCAO CONCLUIDA!");
        }
    }
}

void pesquisarLivrosRealizarEmprestimos() {
    int metodoDeBusca;
    int codigoLido;

    arquivoDeLivros = fopen("livros.txt", "r");
    if (arquivoDeLivros == NULL) {
        printf("Erro ao abrir o arquivo!");
    }

    printf("INICIAR BUSCA/EMPRESTIMO DE LIVROS\n\n"
           "(BUSQUE UM LIVRO, CASO QUEIRA OU NAO EMPRESTAR...\n"
           "ASSINALE A OPCAO NO FINAL DA BUSCA!\n\n");

    do {
        printf("Escolha uma opcao \n");
        printf(
            "1- Busca por codigo do livro \n"
            "2- Busca por titulo do livro \n"
            "3- Busca por Autor do livro\n"
            "4- Encerrar\n"
            );
        scanf("%i", &metodoDeBusca);

        switch (metodoDeBusca) {
            case 1:
                int codigo_encontrado = 0;
                int codigoPesquisa;
                int c;
                printf("Digite o codigo do Livro: ");
                scanf("%d", &codigoPesquisa);

                for (int c = 0; c <= 10; c++) {
                    if (codigoPesquisa == Livros[c].codigoDoLivro) {
                        printf("LIVRO ENCONTRADO COM SUCESSO!\n");
                        codigo_encontrado = 1;
                        break;
                    }
                }

                if (codigo_encontrado == 1) {
                    printf("Codigo do livro: %i\n", Livros[c].codigoDoLivro);
                    printf("Titulo do livro: %s\n", Livros[c].titulo);
                    printf("Autor do livro: %s\n", Livros[c].autor);
                    printf("Editora do Livro: %s\n", Livros[c].editora);
                    printf("Ano de publicacao do livro: %i/%i/%i\n",
                        Livros[c].anoDePublicacao.dia,
                        Livros[c].anoDePublicacao.mes,
                        Livros[c].anoDePublicacao.ano);
                    printf("Numero de Exemplares: %i\n", Livros[c].numeroDeExemplaresDisponiveis);
                    if (Livros[c].status == 0) {
                        printf("Status: Disponivel\n");
                        inicializarRealizarEmprestimos(c);
                    } else if (Livros[c].status == 1) {
                        printf("Status: Nao Disponivel\n"
                               "NAO E POSSIVEL EMPRESTAR ESTE LIVRO!");
                    }
                } else {
                    printf("LIVRO NAO ENCONTRADO!");
                }
                break;
            case 2:
                int i = 1;
                char tituloPesquisa[100];
                int tituloEncontrado = 0;
                printf("Digite o titulo do Livro: ");

                // Limpa o buffer de entrada (stdin)
                while ((c = getchar()) != '\n' && c != EOF) { }

                fgets(tituloPesquisa, 100, stdin);

                size_t len = strlen(tituloPesquisa);
                if (len > 0 && tituloPesquisa[len - 1] == '\n') {
                    tituloPesquisa[len - 1] = '\0';
                }

                for (i = 0; i <= 10; i++) {
                    if (strcasecmp(tituloPesquisa, Livros[i].titulo) == 0) {
                        printf("LIVRO ENCONTRADO COM SUCESSO!\n");
                        tituloEncontrado = 1;
                        // Código para marcar a busca como bem-sucedida
                        break;
                    }
                }

                if (tituloEncontrado == 1) {
                    printf("Codigo do livro: %i\n", Livros[i].codigoDoLivro);
                    printf("Titulo do livro: %s\n", Livros[i].titulo);
                    printf("Autor do livro: %s\n", Livros[i].autor);
                    printf("Editora do Livro: %s\n", Livros[i].editora);
                    printf("Ano de publicacao do livro: %i/%i/%i\n",
                        Livros[i].anoDePublicacao.dia,
                        Livros[i].anoDePublicacao.mes,
                        Livros[i].anoDePublicacao.ano);
                    printf("Numero de Exemplares: %i\n", Livros[i].numeroDeExemplaresDisponiveis);
                    if (Livros[i].status == 0) {
                        printf("Status: Disponivel\n");
                        inicializarRealizarEmprestimos(i);
                    } else if (Livros[i].status == 1) {
                        printf("Status: Nao Disponivel\n"
                               "NAO E POSSIVEL EMPRESTAR ESTE LIVRO!");
                    }
                } else {
                    printf("LIVRO NAO ENCONTRADO!");
                }

                break;
            case 3:
                int j = 1;
                int autorEncontrado = 0;
                char autorPesquisa[80];
                printf("Digite o autor do Livro: ");

                // Limpa o buffer de entrada (stdin)
                while ((c = getchar()) != '\n' && c != EOF) { }

                fgets(autorPesquisa, 80, stdin);

                size_t len1 = strlen(autorPesquisa);
                if (len1 > 0 && autorPesquisa[len1 - 1] == '\n') {
                    autorPesquisa[len1 - 1] = '\0';
                }

                for (j = 0; j <= 10; j++) {
                    if (strcasecmp(autorPesquisa, Livros[j].autor) == 0) {
                        printf("LIVRO ENCONTRADO COM SUCESSO!\n");
                        autorEncontrado = 1;
                        // Código para marcar a busca como bem-sucedida
                        break;
                    }
                }

                if (autorEncontrado == 1) {
                    printf("Codigo do livro: %i\n", Livros[j].codigoDoLivro);
                    printf("Titulo do livro: %s\n", Livros[j].titulo);
                    printf("Autor do livro: %\s", Livros[j].autor);
                    printf("Editora do Livro: %s\n", Livros[j].editora);
                    printf("Ano de publicacao do livro: %i/%i/%i\n",
                        Livros[j].anoDePublicacao.dia,
                        Livros[j].anoDePublicacao.mes,
                        Livros[j].anoDePublicacao.ano);
                    printf("Numero de Exemplares: %i\n", Livros[j].numeroDeExemplaresDisponiveis);
                    if (Livros[j].status == 0) {
                        printf("Status: Disponivel\n");
                        inicializarRealizarEmprestimos(j);
                    } else if (Livros[j].status == 1) {
                        printf("Status: Nao Disponivel\n"
                               "NAO E POSSIVEL EMPRESTAR ESTE LIVRO!");
                    }
                } else {
                    printf("LIVRO NAO ENCONTRADO!");
                }

                break;
            case 4:
                printf("Encerrando...");
                break;
            default:
                printf("Opcao invalida!");
        }
    } while (metodoDeBusca != 1 && metodoDeBusca != 2 && metodoDeBusca != 3 && metodoDeBusca != 4);

    fclose(arquivoDeLivros);
}

void pesquisarUsuariosExistentes() {
    int metodoDeBusca;

    arquivoDeUsuarios = fopen("usuarios.txt", "r");
    if (arquivoDeUsuarios == NULL) {
        printf("Erro ao abrir o arquivo!");
    }

    printf("INICIAR BUSCA DE USUARIOS\n");

    do {
        printf("Escolha uma opcao\n");
        printf(
            "1- Busca por nome do usuario\n"
            "2- Busca por matricula do usuario\n"
            "3- Encerrar\n"
            );
        scanf("%i", &metodoDeBusca);
        switch (metodoDeBusca) {
            case 1:
                int j = 1;
                int nomeEncontrado = 0;
                char nomePesquisa[80];
                printf("Digite o nome do usuario: ");

                // Limpa o buffer de entrada (stdin)
                int c;
                while ((c = getchar()) != '\n' && c != EOF) { }

                fgets(nomePesquisa, 80, stdin);

                size_t len1 = strlen(nomePesquisa);
                if (len1 > 0 && nomePesquisa[len1 - 1] == '\n') {
                    nomePesquisa[len1 - 1] = '\0';
                }

                for (j = 0; j <= 10; j++) {
                    if (strcasecmp(nomePesquisa, Usuarios[j].nomeCompleto) == 0) {
                        printf("USUARIO ENCONTRADO COM SUCESSO!\n");
                        nomeEncontrado = 1;
                        // Código para marcar a busca como bem-sucedida
                        break;
                    }
                }

                if (nomeEncontrado == 1) {
                    printf("Nome do Usuario: %s\n", Usuarios[j].nomeCompleto);
                    printf("Matricula: %d\n", Usuarios[j].matricula);
                    printf("Telefone: %\s\n", Usuarios[j].telefone);
                    printf("Curso: %s\n", Usuarios[j].curso);
                    printf("Data de nascimento: %i/%i/%i\n",
                        Usuarios[j].dataDeNacimento.dia,
                        Usuarios[j].dataDeNacimento.mes,
                        Usuarios[j].dataDeNacimento.ano);
                } else {
                    printf("USUARIO NAO ENCONTRADO!");
                }
                break;
            case 2:
                int matriculaPesquisa;
                c = 1;
                int matriculaEncontrada = 0;
                printf("Digite a matricula do Usuario : ");
                scanf("%d", &matriculaPesquisa);

                for (c = 0; c <= 10; c++) {
                    if (matriculaPesquisa == Usuarios[c].matricula) {
                        printf("USUARIO ENCONTRADO COM SUCESSO!\n");
                        matriculaEncontrada = 1;
                        break;
                    }
                }

                if (matriculaEncontrada == 1) {
                    printf("Nome do usuario: %s\n", Usuarios[c].nomeCompleto);
                    printf("Matricula: %d\n", Usuarios[c].matricula);
                    printf("Telefone: %\s\n", Usuarios[c].telefone);
                    printf("Curso: %s\n", Usuarios[c].curso);
                    printf("Data de nascimento: %i/%i/%i\n",
                        Usuarios[c].dataDeNacimento.dia,
                        Usuarios[c].dataDeNacimento.mes,
                        Usuarios[c].dataDeNacimento.ano);
                } else {
                    printf("USUARIO NAO ENCONTRADO!");
                }

                break;
            case 3:
                printf("Encerrando...");
                break;
            default:
                printf("Opcao invalida!");
        }
    } while (metodoDeBusca != 1 && metodoDeBusca != 2 && metodoDeBusca != 3);

    fclose(arquivoDeLivros);
}

int listaDeEmprestimosAtivos() {
    for (int c = 1; c <= 10; c++) {
        if (Emprestimos[c].codigoDoEmprestimo != 0) {
            printf("Codigo do emprestimo: %d\n", Emprestimos[c].codigoDoEmprestimo);
            printf("Matricula do usuario: %d\n", Emprestimos[c].matriculaDoUsuario);
            printf("Codigo do livro: %d\n", Emprestimos[c].codigoDoLivro);
            printf("Data do emprestimo: %d/%d/%d\n",
                Emprestimos[c].dataDeEmprestimo.dia,
                Emprestimos[c].dataDeEmprestimo.mes,
                Emprestimos[c].dataDeEmprestimo.ano);
            printf("Data prevista de devolucao: %d/%d/%d\n",
                Emprestimos[c].dataPrevistaDevolucao.dia,
                Emprestimos[c].dataPrevistaDevolucao.mes,
                Emprestimos[c].dataPrevistaDevolucao.ano);
            if (Emprestimos[c].status == 1) {
                printf("Status do emprestimo: Ativo");
            } else {
                printf("Status do emprestimo: Devolvido");
            }
        } else {
            printf("\nLISTA DE EMPRESTIMOS IMPRIMIDA!");
            return 0;
        }
    }
}

int voltarAoInicio () {
    // Voltar ao menu incial

    printf("Voltar ao menu inical? (Sim/Nao)");
    scanf("%s", voltar);

    if (strcmp(voltar, "Sim") == 0
        || strcmp(voltar, "sim") == 0
        || strcmp(voltar, "SIM") == 0) {
        return 1;
    } else {
        return 0;
    }
}

void mostrarMenu() {
    // A TERMINAR
    int volta;

    // Enquanto a opcao escolhida nao for uma das mostradas, o programa fica reiniando infinitamente
    do {
        printf(
        "Escolha uma opcao\n\n"
           "1- Usuario(Registro de Usuario/Pesquisar Usuarios Existentes)\n"
           "2- Emprestimos(Devolver Livros/Lista de Emprestimos Ativos)\n"
           "3- Livros(Pesquisar e Emprestar Livros/Cadastrar Livros)\n"
           "4- Encerrar Servico\n"
           );
        scanf("%i", &opcao);

        switch (opcao) {

            case 1:
                // Enquanto a opcao escolhida nao for uma das mostradas, o programa fica reiniando infinitamente
                do {
                    printf(
                    "Opcao de Usuario \n\n"
                    "1- Registro de Usuario\n"
                    "2- Pesquisar Usuarios Ja Existentes\n"
                    "3- Encerrar Servico\n"
                    );
                    scanf("%i", &opc);

                    switch (opc) {
                        case 1:
                            inicializarCadastroDeUsuarios();
                            volta = voltarAoInicio();
                            if (volta == 1) {
                                mostrarMenu();
                            } else {
                                printf(
                                    "Encerrando... \n"
                                    "Volte Sempre!"
                                    );
                            }
                            break;

                        case 2:
                            pesquisarUsuariosExistentes();
                            volta = voltarAoInicio();
                            if (volta == 1) {
                                mostrarMenu();
                            } else {
                                printf(
                                    "Encerrando... \n"
                                    "Volte Sempre!"
                                    );
                            }
                            break;
                        case 3:
                            printf(
                            "Voce encerrou o servico! \n"
                                "Volte Sempre!"
                           );
                            break;

                        default:
                            printf("Opcao invalida! \n");
                    }
                } while (opc != 1 && opc != 2 && opc != 3);
                break;

            case 2:
                // Enquanto a opcao escolhida nao for uma das mostradas, o programa fica reiniando infinitamente
                do {
                    printf(
                    " Opcao de Emprestimos\n\n"
                    "1- Devolver um Livro\n"
                    "2- Lista de Livros Emprestados\n"
                    "3- Encerrar Servico\n"
                    );
                    scanf("%i", &opc);

                    switch (opc) {
                        case 1:
                            realizarDevolucoes();
                            volta = voltarAoInicio();
                            if (volta == 1) {
                                mostrarMenu();
                            } else {
                                printf(
                                    "Encerrando... \n"
                                    "Volte Sempre!"
                                    );
                            }
                            break;

                        case 2:
                            listaDeEmprestimosAtivos();
                            volta = voltarAoInicio();
                            if (volta == 1) {
                                mostrarMenu();
                            } else {
                                printf(
                                    "Encerrando... \n"
                                    "Volte Sempre!"
                                    );
                            }
                            break;
                        case 3:
                            printf(
                            "Voce encerrou o servico! \n"
                                "Volte Sempre!"
                           );
                            break;

                        default:
                            printf("Opcao invalida! \n");
                    }
                } while (opc != 1 && opc != 2 && opc != 3);
                break;
            case 3:

                // Enquanto a opcao escolhida nao for uma das mostradas, o programa fica reiniando infinitamente
                do {
                    printf(
                    " Opcao de Livros\n\n"
                    "1- Pesquisar/Emprestar Livros\n"
                    "2- Cadastrar Livros\n"
                    "3- Encerrar Servico\n"
                    );
                    scanf("%i", &opc);

                    switch (opc) {
                        case 1:
                            pesquisarLivrosRealizarEmprestimos();
                            volta = voltarAoInicio();
                            if (volta == 1) {
                                mostrarMenu();
                            } else {
                                printf(
                                    "Encerrando... \n"
                                    "Volte Sempre!"
                                    );
                            }
                            break;

                        case 2:
                            inicializarCadastroDeLivros();
                            volta = voltarAoInicio();
                            if (volta == 1) {
                                mostrarMenu();
                            } else {
                                printf(
                                    "Encerrando... \n"
                                    "Volte Sempre!"
                                    );
                            }
                            break;

                        case 3:
                            printf(
                            "Voce encerrou o servico! \n"
                                "Volte Sempre!"
                           );
                            break;

                        default:
                            printf("Opcao invalida! \n");
                    }
                } while (opc != 1 && opc != 2 && opc != 3);
                break;
            case 4:
                    printf(
                    "Voce encerrou o servico! \n"
                        "Volte Sempre!"
                           );
                break;

            default:
                printf("Opcao invalida! \n");
        }
    } while (opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4);
}

// Codigo principal
int main(void) {

    arquivoDeEmprestimos = fopen("emprestimos.txt", "a");
    arquivoDeUsuarios = fopen("usuarios.txt", "a");
    arquivoDeLivros = fopen("livros.txt", "a");

    fclose(arquivoDeEmprestimos);
    fclose(arquivoDeUsuarios);
    fclose(arquivoDeLivros);

    printf("CARREGANDO DADOS...\n");
    carregarDadosLivros();
    carregarDadosUsuarios();
    carregarDadosEmprestimos();
    printf("DADOS CARREGADOS!\n");

    mostrarMenu();

    return 0;
}
