#ifndef Menu_e_telas_de_escolha_H_INCLUDED
#define Menu_e_telas_de_escolha_H_INCLUDED

// #include "Processos.h"
// #include "Structs_e_variáveis.h"

#define CLEAR "cls"

void introducao()
{
    limpar_livros();
    limpar_pessoas();
    limpar_emprestimos();
    printf("Quantos livros na biblioteca? ");
    scanf(" %d", &QtdeLivros);
    Livros = calloc(QtdeLivros, sizeof(t_livro));

    printf("Quantas pessoas frequentam a biblioteca? ");
    scanf(" %d", &QtdePessoas);
    Pessoas = calloc(QtdePessoas, sizeof(t_pessoa));
    Emprestimos = calloc(3*QtdePessoas, sizeof(t_emprestimo));
    Devolucoes = calloc(3*QtdePessoas, sizeof(t_devolucoes));
}

void menu()
{
    system(CLEAR);
    int opcao;
    printf(">>MENU<<\n");
    printf("[1] Acrescentar dados\n[2] Consultar dados\n[3] Registrar emprestimo\n[4] Registrar devolucao\n[5] Limpar todos os dados salvos\n[6] Sair\n");
    scanf(" %d", &opcao);
    switch(opcao)
    {
        case 1:
        {
            acrescentar_dados();
            break;
        }
        case 2:
        {
            consultar_dados();
            break;
        }
        case 3:
        {
            registrar_emprestimo();
        }
        case 4:
        {
            registrar_devolucao();
        }
        case 5:
        {
            limpar_livros();
            limpar_pessoas();
            limpar_emprestimos();
            menu();
        }
        case 6:
        {
            exit (0);
        }
    }
}

void acrescentar_dados()
{
    system(CLEAR);
    int opcao;
    printf(">>ACRESCENTAR DADOS<<\n");
    printf("[1] Registrar livro\n[2] Registrar pessoa\n[3] Menu Principal\n");
    fflush(stdin);
    scanf(" %d", &opcao);
    switch(opcao)
    {
        case 1:
        {
            registrar_livro();
            break;
        }
        case 2:
        {
            registrar_pessoa();
            break;
        }
        case 3:
        {
            menu();
            break;
        }
    }
}

void consultar_dados()
{
    system(CLEAR);
    int opcao;
    printf(">>CONSULTAR DADOS<<\n");
    printf("[1] Buscar livros\n[2] Buscar pessoas\n[3] Relatorios\n[4] Menu Principal\n");
    scanf("%d", &opcao);
    switch(opcao)
    {
        case 1:
        {
            buscar_livro();
            break;
        }
        case 2:
        {
            buscar_pessoa();
            break;
        }
        case 3:
        {
            relatorios();
            break;
        }
        case 4:
            menu();
    }
}

#endif // Menu_e_telas_de_escolha_H_INCLUDED
