#ifndef PROCESSOS_H_INCLUDED
#define PROCESSOS_H_INCLUDED

#define CLEAR "cls"

// ao longo do codigo, as funcoes red(), white(), e green() sao usadas para mudar a cor das mensagens mostradas pelo programa

// Registra emprestimos
void registrar_emprestimo()
{
  system(CLEAR); // limpa a tela

	int checa, erro, parada, j; // variaveis locais auxiliares e de loop
	char temp; // variavel temporaria
	int opc; // variavel de opcao do usuario no menu
	int novaQtde; // utilizada caso o usuario deseje acrescentar mais exemplares de um livro

	parada = 1;
	erro = 1; // inicializa as variaveis com 1

	if (LivrosRegistrados == 0 && PessoasRegistradas == 0)  // garante que a aba de emprestimos nao pode ser acessada caso nao existam livros e pessoas registradas
	{			
		red();
	        printf("Nao ha livros nem usuarios registrados no sistema, um emprestimo nao pode ser realizado!\n");
	        white();
	        getchar();
	        temp = getchar();
	        menu();
	}

	if (LivrosRegistrados == 0)
	{
	        red();
	        printf("Nao ha livros registrados no sistema, um emprestimo nao pode ser realizado!\n");
	        white();
	        getchar();
	        temp = getchar();
	        menu();
	}

	if (PessoasRegistradas == 0)
	{
	        red();
	        printf("Nao ha usuarios registrados no sistema, um emprestimo nao pode ser realizado!\n");
	        white();
	        getchar();
	        temp = getchar();
	        menu();
	}

	printf(">>REGISTRAR EMPRESTIMO<<\n");
	getchar(); // evita problemas com o buffer de teclado
	while (parada == 1)
	{
    		printf("Codigo do Livro emprestado: ");
		fflush(stdin);
		scanf(" %d", &checa); // le o codigo procurado pelo usuario
		for (j = 0; j <= LivrosRegistrados; j++) // verifica se o codigo existe/se o emprestimo e possivel
		{
			if (Livros[j].codigo == checa && Livros[j].qtdeDisp > 0) // emprestimo possivel (livro existe e ha exemplares disponiveis)
			{
				Emprestimos[numEmp].livro = checa;
				parada = 0;
				erro = 0;
				Livros[j].qtdeDisp--;
				break; // sai do loop
			}
			if (Livros[j].codigo == checa && Livros[j].qtdeDisp == 0) // emprestimo impossivel por falta de exemplares
			{
				system(CLEAR);
				red();
				printf("Livro sem unidades disponiveis, deseja incluir mais exemplares? \n\n");
				white();
				printf("[1] Sim\n[2] Nao\n");
				scanf("%d", &opc); // le a opcao do usuario
				if (opc == 1)
				{
					printf("Insira a nova quantidade de exemplares: ");
					scanf("%d", &novaQtde); // le a nova quantidade total de exemplares
					Livros[j].qtdeDisp = Livros[j].qtdeDisp + novaQtde; // atualiza a quantidade de exemplares disponiveis do livro com o codigo informado
					Emprestimos[numEmp].livro = checa;
					erro = 0;
					parada = 0;
					green();
					printf("\nLivros adicionados com sucesso");
					white();
					getchar();
					temp = getchar();
					Livros[j].qtdeDisp--;
					system(CLEAR);
				}
				if (opc == 2)
				{
					red();
					printf("\nNao foi possivel realizar o emprestimo, tente novamente!\n"); // caso o usuario nao acrescente mais exemplares, o emprestimo e impossivel
					white();
					getchar();
					temp = getchar(); // sai da pagina com um "enter"
					menu();
				}
			}
		}
		if (erro == 1)
		{
           		red();
			printf("\nLivro nao existente nos registros, tente novamente\n\n");
			white();
		}
	}

	parada = 1;
	erro = 1; // muda os valores das variaveis para iniciar novo loop

	while (parada == 1)
	{
   		printf("Codigo do Usuario: ");
		fflush(stdin);
		scanf(" %d", &checa); // le o codigo do usuario que deseja emprestar o livro
		for (j = 0; j <= PessoasRegistradas; j++)
		{
			if (Pessoas[j].codigo == checa) // pessoa existe no sistema
			{
                		Emprestimos[numEmp].pessoa = checa;
				parada = 0;
				erro = 0;
				break; // sai do loop
			}
		}
		if (erro == 1) // pessoa nao existe no sistema
		{
			red();
			printf("\nUsuario inexistente, tente novamente\n\n");
			white();
		}
	}

	printf("Data de emprestimo: ");
	fflush(stdin);
	scanf(" %d%d", &Emprestimos[numEmp].dataEmp_dia, &Emprestimos[numEmp].dataEmp_mes); // le dia e mes do emprestimo
    	Emprestimos[numEmp].dataDev_dia = Emprestimos[numEmp].dataDev_mes = 0;

	green();
	printf("\nEmprestimo salvo com sucesso!");
	white();
	getchar();
	temp = getchar(); // sai da pagina com um "enter"

	ArqEmprestimos = fopen("Emprestimos.txt", "a+"); // abre um arquivo txt

	if (ArqEmprestimos == NULL) // avisa caso o arquivo nao tenha possa ser aberto
	{
	   	red();
		printf("Erro ao salvar em disco!\n");
		white();
		getchar();
		temp = getchar();
		menu();
	}

	// salva em um arquivo txt os dados
	fprintf(ArqEmprestimos, "Dados do emprestimo %d\n", numEmp + 1);
	fprintf(ArqEmprestimos, "Código do livro emprestado: %d\n", Emprestimos[numEmp].livro);
	fprintf(ArqEmprestimos, "Codigo do aluno: %d\n", Emprestimos[numEmp].pessoa);
	fprintf(ArqEmprestimos, "Data do emprestimo: %d/%d\n\n", Emprestimos[numEmp].dataEmp_dia, Emprestimos[numEmp].dataEmp_mes);

	fclose(ArqEmprestimos); // fecha o arquivo

	numEmp++; // aumenta o numero de emprestimos registrados
	menu();
}

// Registra devoluções
void registrar_devolucao()
{
    system(CLEAR); //Limpa a tela

    int i;                          //variavel para contagem
    int checa_pessoa, checa_livro;  //variaveis locais auxiliares
    int erro, parada;               //variaveis de loop
    char temp;                      //variavel temporaraia para pausa no sistema
    erro = parada = 1;              //inicializacao dos loops com valor 1

    if (numEmp == 0) { // garante que a aba de emprestimos nao pode ser acessada caso nao existam emprestimos registrados
        red();
        printf("Nao ha emprestimos registrados no sistema, uma devolucao nao pode ser realizada!\n");
        white();
        getchar();
        temp = getchar();
        menu();
    }

    printf(">>Registrar devolucao<<\n");
    while (parada == 1) {           //loop usado para garantir que a devolucao esta associada a um emprestimo existente
        fflush(stdin);
        printf("Codigo do usuario: ");
        scanf("%d", &checa_pessoa); //atribui um codigo a uma variavel auxiliar
        fflush(stdin);
        printf("Codigo do livro: ");
        scanf("%d", &checa_livro); //atribui um codigo a uma variavel auxiliar
        for (i=0; i<numEmp; i++) {
            if (Emprestimos[i].pessoa == checa_pessoa && Emprestimos[i].livro == checa_livro) { //checa a existencia do emprestimo (compara com os valores atribuidos durante o emprestimo)
                Devolucoes[numDev].pessoa = checa_pessoa;
                Devolucoes[numDev].livro = checa_livro;
                erro = 0;
                parada = 0;
                Livros[i].qtdeDisp++; //devolve uma copia ao livro associado ao emprestimo
                break;
            }
        }
        if (erro == 1){  // caso o emprestimo nao exista, retorna uma mensagem de erro
            red();
            printf("\nNao existe um emprestimo com os codigos escolhidos, tente novamente!\n\n");
            white();
            getchar();
            temp = getchar(); // sai da pagina com um "enter"
            parada = 1;
        }
    }

    printf("Data da devolucao: ");
    fflush(stdin);
    scanf("%d%d", &Emprestimos[numDev].dataDev_dia, &Emprestimos[numDev].dataDev_mes); // define a data da devolucao
    green();
    printf("\nDevolucao registrada!");
    white();
    getchar();
    temp = getchar(); // sai da pagina com um "enter"

    ArqDevolucoes = fopen("Devolucoes.txt", "a+"); // abre o arquivo txt para escrita dos dados

    if (ArqDevolucoes == NULL) // avisa caso o arquivo nao tenha possa ser aberto
	{
	      	red();
		printf("Erro ao salvar em disco!\n");
		white();
		getchar();
		temp = getchar();
		menu();
	}

    // registra os dados no arquivo
    fprintf(ArqDevolucoes, "Dados da devolucao %d\n", numDev+1);
    fprintf(ArqDevolucoes, "Usuario: %d\n", Devolucoes[numDev].pessoa);
    fprintf(ArqDevolucoes, "Livro: %d\n", Devolucoes[numDev].livro);
    fprintf(ArqDevolucoes, "Data: %d/%d\n", Emprestimos[numDev].dataDev_dia, Emprestimos[numDev].dataDev_mes);

    fclose(ArqDevolucoes); // fecha o arquivo
    numDev++; // aumenta o numero de devolucoes realizadas
    menu();
}

// Registra livros
void registrar_livro()
{
	system(CLEAR); // limpa a tela

	char temp; // variavel temporaria
	int checa, parada, erro, i; // variaveis locais auxiliares e de loop
	parada = 1;
	erro = 1; // inicializa os valores das variaveis

	if (LivrosRegistrados == QtdeLivros - 1)
	{
		checar_livro(); // caso seja o ultimo registro possivel, chama a funcao
	}

	printf(">>REGISTRAR LIVRO<<\n");
	getchar(); // evita problemas com o buffer de teclado
	printf("Titulo: ");
	fflush(stdin);
	fgets(Livros[LivrosRegistrados].titulo, 50, stdin); // le o titulo do livro registrado

	printf("Autor: ");
	fflush(stdin);
	fgets(Livros[LivrosRegistrados].autor, 50, stdin); // le o autor do livro registrado

	while (parada == 1)
	{
        	printf("Codigo: ");
		fflush(stdin);
		scanf("%d", &checa); // le o codigo do livro registrado
		for (i = 0; i < LivrosRegistrados; i++) // verifica se o codigo inserido e valido
		{
			if (Livros[i].codigo == checa) // codigo valido, nao usado anteriormente
			{
				erro = 0;
				break;
			}
			else if (Livros[i].codigo != checa) // codigo invalido, usado anteriormente
			{
				erro = 1;
			}
		}
		if (erro == 0)
		{
			red();
			printf("\nCodigo de livro ja utilizado, escolha outro e tente novamente\n\n");
			white();
		}
		if (erro == 1)
		{
			Livros[LivrosRegistrados].codigo = checa; // armazena o codigo lido no vetor
			parada = 0; // sai do loop
		}
	}

	printf("Quantidade de exemplares: ");
	fflush(stdin);
	scanf("%d", &Livros[LivrosRegistrados].qtdeDisp); // le a quantidade de exemplares disponiveis
	Livros[LivrosRegistrados].qtdeInicial = Livros[LivrosRegistrados].qtdeDisp; // a quantidade disponivel de livros inicialmente e a quantidade inicial
	green();
	printf("\nLivro registrado com sucesso!");
	white();
	getchar();
	temp = getchar(); // sai da pagina com "enter"

	ArqLivros = fopen("Livros.txt", "a+"); // abre arquivo txt

	if (ArqLivros == NULL) // informa caso nao seja possivek abrir o arquivo
	{
	    	red();
		printf("Erro ao salvar em disco!\n");
		white();
		getchar();
		temp = getchar(); // sai da pagina com "enter"
		menu();
	}

	// salva dados em disco
	fprintf(ArqLivros, "Dados do livro %d:\n", LivrosRegistrados + 1);
	fprintf(ArqLivros, "Titulo: %s", Livros[LivrosRegistrados].titulo);
	fprintf(ArqLivros, "Autor: %s", Livros[LivrosRegistrados].autor);
	fprintf(ArqLivros, "Codigo: %d\n", Livros[LivrosRegistrados].codigo);
	fprintf(ArqLivros, "Exemplares: %d\n\n", Livros[LivrosRegistrados].qtdeDisp);
	fprintf(ArqLivros, "\n");

	fclose(ArqLivros); // fecha arquivo

	LivrosRegistrados++; // aumenta a quantidade registrada de livros
	menu();
}

// Registra pessoas
void registrar_pessoa()
{
	system(CLEAR); // limpa a tela

	char temp; // variavel temporaria
	int checa, parada, erro, i; // variaveis locais auxiliares e de loop
	parada = 1;
	erro = 1; // inicializa as variaveis com valores adequados

	if (PessoasRegistradas == QtdePessoas - 1)
	{
		checar_pessoa(); // caso seja o ultimo registro possivel, chama a funcao
	}

	printf(">>REGISTRAR PESSOA<<\n");
	getchar(); // evita problemas com o buffer de teclado
	printf("Nome: ");
	fflush(stdin);
	fgets(Pessoas[PessoasRegistradas].nome, 50, stdin); // le o nome da pessoa

	while (parada == 1)
	{
        	printf("Codigo: ");
		fflush(stdin);
		scanf("%d", &checa); // le o codigo da pessoa
		for (i = 0; i < PessoasRegistradas; i++) // verifica se o codigo e valido
		{
			if (Pessoas[i].codigo == checa) // codigo valido, nao usado anteriormente
			{
				erro = 0;
				break;
			}
			else if (Pessoas[i].codigo != checa) // codigo invalido, usado anteriormente
			{
				erro = 1;
			}
		}
		if (erro == 0)
		{
			red();
			printf("\nCodigo de usuario ja utilizado, escolha outro e tente novamente\n\n");
			white();
		}
		if (erro == 1)
		{
			Pessoas[PessoasRegistradas].codigo = checa; // atribui o codigo ao usuario
			parada = 0; // sai do loop
		}
	}

	green();
	printf("\nUsuario registrado com sucesso!");
	white();
	getchar();
	temp = getchar(); // sai da pagina com enter

	ArqPessoas = fopen("Pessoas.txt", "a+"); // abre arquivo txt

	if (ArqPessoas == NULL) // informa se houve erro ao salvar em disco
	{
	    	red();
		printf("Erro ao salvar em disco!\n");
		white();
		getchar();
		temp = getchar();
		menu();
	}

	// salva os dados em um arquivo txt
	fprintf(ArqPessoas, "Dados do Usuário %d:\n", PessoasRegistradas + 1);
	fprintf(ArqPessoas, "Nome: %s", Pessoas[PessoasRegistradas].nome);
	fprintf(ArqPessoas, "Codigo: %d\n", Pessoas[PessoasRegistradas].codigo);
	fprintf(ArqPessoas, "\n");

	fclose(ArqPessoas); // fecha o arquivo

	PessoasRegistradas++; // aumenta o numero de pessoas registradas
	menu();
}

// Busca livro por codigo
void buscar_livro()
{
	system(CLEAR); // limpa a tela

	int codigoBuscado; // variavel com o codigo procurado
	int i, erro;	   // variaveis auxiliares e de loop
	char temp;	   // variavel temporaria

	erro = 1; // atribui valor para a variavel

	printf(">>BUSCAR DADOS<<\n");
	printf("Insira o codigo do livro: ");
	scanf("%d", &codigoBuscado);	         // le o codigo procurado
	for (i = 0; i <= LivrosRegistrados; i++) // verifica se o codigo existe no sistema
	{
		if (Livros[i].codigo == codigoBuscado) // codigo encontrado, mostra dados do livro
		{
			green();
			printf("\nLivro encontrado!\n\n");
			white();
			printf("Titulo: %s", Livros[i].titulo);
			printf("Autor: %s", Livros[i].autor);
			printf("Codigo: %d\n", Livros[i].codigo);
			printf("Quantidade disponivel: %d\n", Livros[i].qtdeDisp);
			erro = 0;
			getchar();
			temp = getchar(); // sai da pagina com enter
		}
	}
	if (erro == 1) // codigo nao encontrado
	{ 	
		red();
		printf("\nLivro nao encontrado!\n");
		white();
		getchar();
        	temp = getchar();
	}
	menu();
}

// Busca pessoa por codigo
void buscar_pessoa()
{
	system(CLEAR); // limpa a tela

	int codigoBuscado; // armazena o codigo buscado
	int i, erro;	   // variaveis auxiliares e de loop
	char temp;	   // variavel temporria

	erro = 1;

	printf(">>BUSCAR DADOS<<\n");
	printf("Insira o codigo do usuario: ");
	scanf("%d", &codigoBuscado);		  // le o codigo procurado
	for (i = 0; i <= PessoasRegistradas; i++) // busca o codigo no sistema
	{
		if (Pessoas[i].codigo == codigoBuscado) // encontrou o codigo, mostra dados
		{
			green();
			printf("\nUsuario encontrado!\n\n");
			white();
			printf("Nome: %s", Pessoas[i].nome);
			printf("Codigo: %d\n", Pessoas[i].codigo);
			erro = 0;
			getchar();
			temp = getchar();
		}
	}
	if (erro == 1) // nao encontrou o codigo, mostra mensagem de erro
	{ 
		red();
		printf("Usuario nao encontrado");
		white();
		getchar();
        	temp = getchar();
	}

	menu();
}

// Realoca memoria para registrar novos usuarios
void checar_pessoa()
{
	system(CLEAR); // limpa a tela

	int opc, j;		       // variaveis auxiliares e de loop
	int novaQtdePessoas;	       // armazena a nova quantidade de pessoas escolhida pelo usuario
	t_pessoa *tempPessoa;	       // vetor para armazenar temporariamente dados de pessoas
	t_emprestimo *tempEmprestimo;  // vetor para armazenar temporariamente dados de emprestimos
	t_devolucoes *tempDevolucao;   // vetor para armazenar temporariamente dados de devolucoes

	if (PessoasRegistradas == QtdePessoas - 1)
	{
		red();
		printf(">>ATENCAO!<< ");
		white();
		printf("Este e o ultimo registro de pessoa disponivel, deseja acrescentar mais usuarios?\n");
		printf("[1] Sim\n[2] Nao\n");
		scanf("%d", &opc); // le a opcao escolhida pelo usuario
		if (opc == 1)	   // caso o usuario deseje acrescentar mais pessoas
		{
			printf("Quantas pessoas frequentam a biblioteca?");
			scanf("%d", &novaQtdePessoas); // le a nova quantidade de pessoas escolhida pelo usuario
			tempPessoa = (t_pessoa *)calloc(novaQtdePessoas, sizeof(t_pessoa));
			tempEmprestimo = (t_emprestimo *)calloc(3*novaQtdePessoas, sizeof(t_emprestimo));
			tempDevolucao  = (t_devolucoes *)calloc(3*novaQtdePessoas, sizeof(t_devolucoes)); // cria um vetor temporario
			for (j = 0; j < QtdePessoas; j++)
			{
				tempPessoa[j] = Pessoas[j]; // armazena os dados do vetor anterior no vetor temporario
			}
			for (j = 0; j < 3*QtdePessoas; j++)
			{
				tempEmprestimo[j] = Emprestimos[j];
				tempDevolucao[j] = Devolucoes[j]; // armazena os dados do vetor anterior no vetor temporario
			}
			free(Pessoas); // libera o vetor inicial de pessoas
			Pessoas = (t_pessoa *)calloc(novaQtdePessoas, sizeof(t_pessoa)); // aloca memoria no vetor original
			for (j = 0; j < QtdePessoas; j++)
			{
				Pessoas[j] = tempPessoa[j]; // armazena os dados do vetor temporario no vetor original
			}

			free(Emprestimos); // libera o vetor inicial de emprestimos
			free(Devolucoes); // libera o vetor inicial de devolucoes

			Emprestimos = (t_emprestimo *)calloc(3*novaQtdePessoas, sizeof(t_emprestimo));
			Devolucoes = (t_devolucoes *)calloc(3*novaQtdePessoas, sizeof(t_devolucoes)); // aloca memoria no vetor original
			for (j = 0; j < 3*QtdePessoas; j++)
			{
				Emprestimos[j] = tempEmprestimo[j];
				Devolucoes[j] = tempDevolucao[j]; // armazena os dados do vetor temporario no vetor original
			}
			QtdePessoas = novaQtdePessoas;

			free(tempPessoa);
			free(tempEmprestimo);
			free(tempDevolucao); // libera os vetores temporarios
		}
		else // caso o usuario nao deseje acrescentar mais pessoas
		{
			printf("\n");
		}
	}

	system(CLEAR); //limpa a tela
}

// Realoca memoria para registrar novos livros
void checar_livro()
{
	system(CLEAR); // limpa a tela

	int opc, j;	    // variaveis auxiliares e de loop
	int novaQtdeLivros; // armazena a nova quantidade de livros escolhida pelo usuario
	t_livro *tempLivro; // vetor temporario

	red();
	printf(">>ATENCAO!<< ");
	white();
	printf("Este e o ultimo registro de livro disponivel, deseja acrescentar mais livros?\n");
	printf("[1] Sim\n[2] Nao\n");
	scanf("%d", &opc); // le a opcao do usuario
	if (opc == 1)	   // caso o usuario deseje acrescentar mais livros
	{
		printf("Quantos livros na biblioteca?");
		scanf("%d", &novaQtdeLivros); // le a nova quantidade de livros
		tempLivro = (t_livro *)calloc(novaQtdeLivros, sizeof(t_livro)); // aloca memoria em vetor temporario
		for (j = 0; j < QtdeLivros; j++)
		{
			tempLivro[j] = Livros[j]; // preenche o vetor temporario com os dados do original
		}
		free(Livros); // libera o vetor original
		Livros = (t_livro *)calloc(novaQtdeLivros, sizeof(t_livro)); // aloca memoria no vetor original
		for (j = 0; j < QtdeLivros; j++)
		{
			Livros[j] = tempLivro[j]; // preenche o vetor original com os dados do temporario
		}
		QtdeLivros = novaQtdeLivros; // atualiza a quantidade de livros
		free(tempLivro); // libera o vetor temporario
	}
	else // caso o usuario nao deseje acrescentar mais livros
	{
		printf("\n");
	}

	system(CLEAR); //limpa a tela
}

// Limpa dados de livros
void limpar_livros()
{
	system(CLEAR); // limpa a tela

	ArqLivros = fopen("Livros.txt", "w"); // abre arquivo em branco
	fclose(ArqLivros);
	free(Livros); // libera o vetor de livros
	LivrosRegistrados = 0;
}

// Limpa dados de pessoas
void limpar_pessoas()
{
	system(CLEAR); // limpa a tela

	ArqPessoas = fopen("Pessoas.txt", "w");
	fclose(ArqPessoas);
	free(Pessoas); // libera o vetor de pessoas
	PessoasRegistradas = 0;
}

// Limpa dados de emprestimos
void limpar_emprestimos()
{
	system(CLEAR); // limpa a tela

	ArqEmprestimos = fopen("Emprestimos.txt", "w");
	fclose(ArqEmprestimos);
	free(Emprestimos); // libera vetor de emprestimos
	numEmp = 0;

	ArqDevolucoes = fopen("Devolucoes.txt", "w");
	fclose(ArqDevolucoes);
	free(Devolucoes);
	numDev = 0;
}

// Mostra relatorios de livros, pessoas e emprestimos registrados
void relatorios()
{
	system(CLEAR); // limpa a tela

	int i;	   // variavel de loop
	char temp; // variavel temporaria

	// mostra dados de usuarios
	printf(">>RELATORIOS<<\n\n");
	printf("--Relatorio de usuarios--\n");
	for (i = 0; i < PessoasRegistradas; i++)
	{
		printf("Dados do Usuario %d:\n", i + 1);
		printf("Nome: %s", Pessoas[i].nome);
		printf("Codigo: %d\n\n", Pessoas[i].codigo);
		printf("\n");
	}

	// mostra dados de livros
	printf("--Relatorio de livros--\n");
	for (i = 0; i < LivrosRegistrados; i++)
	{
		printf("Dados do livro %d:\n", i + 1);
		printf("Titulo: %s", Livros[i].titulo);
		printf("Autor: %s", Livros[i].autor);
		printf("Codigo: %d\n", Livros[i].codigo);
		printf("Exemplares: %d\n\n", Livros[i].qtdeDisp);
		printf("\n");
	}

	// mostra dados de emprestimos
	printf("--Relatorio de emprestimos--\n");
	for (i = 0; i < numEmp; i++)
	{
		printf("Dados do emprestimo %d\n", i + 1);
		printf("Codigo do livro emprestado: %d\n", Emprestimos[i].livro);
		printf("Codigo do usuario: %d\n", Emprestimos[i].pessoa);
		printf("Data do emprestimo: %d/%d\n", Emprestimos[i].dataEmp_dia, Emprestimos[i].dataEmp_mes);
		if (Emprestimos[i].dataDev_dia != 0 && Emprestimos[i].dataDev_mes != 0){  // a data de devolucao so e printada caso seja adicionada durante a devolucao
           	printf("Data da devolucao: %d/%d\n\n", Emprestimos[i].dataDev_dia, Emprestimos[i].dataDev_mes);
		}
	}

	getchar();
	temp = getchar(); // sai da pagina com enter
	menu();
}

#endif // PROCESSOS_H_INCLUDED
