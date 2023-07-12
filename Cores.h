#ifndef CORES_H_INCLUDED
#define CORES_H_INCLUDED

//Define as cores a serem usadas ao longo do programa
//Sao utilizadas pela funcao "cor()" (exemplo: "red()" imprime as linhas seguintes na cor vermelha)

red()
{
    printf("\033[0;31m");
}

white()
{
    printf("\033[0;37m");
}

green()
{
    printf("\033[0;32m");
}


#endif // CORES_H_INCLUDED
