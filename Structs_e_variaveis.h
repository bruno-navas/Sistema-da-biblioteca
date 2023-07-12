#ifndef STRUCTS_E_VARIAVEIS_H_INCLUDED
#define STRUCTS_E_VARIAVEIS_H_INCLUDED

//Cria um tipo de variavel para livros
typedef struct
{
    char titulo[50];
    char autor[50];
    int codigo;
    int qtdeDisp;
    int qtdeInicial;
} t_livro;

//Declara um ponteiro para um vetor que armazena livros
t_livro *Livros;

//Cria um tipo de variavel para pessoas
typedef struct
{
    char nome[50];
    int codigo;
} t_pessoa;

//Declara um ponteiro para um vetor que armazena pessoas
t_pessoa *Pessoas;

//Cria um tipo de variavel para emprestimos
typedef struct
{
    int livro;
    int pessoa;
    int dataEmp_dia;
    int dataEmp_mes;
    int dataDev_dia;
    int dataDev_mes;
} t_emprestimo;

//Declara um ponteiro para um vetor que armazena emprestimos
t_emprestimo *Emprestimos;

//Declara um tipo de variavel para devolucoes
typedef struct
{
    int livro;
    int pessoa;
} t_devolucoes;

//Ddeclara um ponteiro para um vetor que armazena devolucoes
t_devolucoes *Devolucoes;

//Declaracao de variaveis e ponteiros globais
int QtdeLivros; //quantidade total de livros
int QtdePessoas; //quantidade total de pessoas
FILE *ArqLivros; //arquivo que salva livros
FILE *ArqPessoas; //arquivo que salva pessoas
FILE *ArqEmprestimos; //arquivo que salva emprestimos
FILE *ArqDevolucoes;
int PessoasRegistradas, LivrosRegistrados, numEmp, numDev; //quantidade de pessoas, livros, emprestimos e devolucoes registradas ate o momento
//embora variaveis globais sejam inicializadas com valor 0, nos certificamos disso atualizando manualmente seus valores
PessoasRegistradas = 0;
LivrosRegistrados = 0;
numEmp = 0;
numDev = 0;

#endif // STRUCTS_E_VARIAVEIS_H_INCLUDED
