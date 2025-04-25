// Projeto_Comercio_Local.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip> // para usar manipuladores de entrada e saida para controlar a formatação dos dados
#include <string> // para usar strings
#include <ctime> // para adicionar horas e datas (talao)
#include <sstream> // para poder usar setprecision em strings || deixa-me usar manipulador de strings
#include <vector>

using namespace std;

int totalProdutos = 3;
int colunas = 4; // ID, Nome, Quantidade, Preco 
int maximoProdutos = 100;
string** produto = new string* [maximoProdutos];

void inicializarProdutos()
{
	for (int i = 0; i < maximoProdutos; i++)
	{
		produto[i] = new string[colunas];
	}
	//produto 1
	produto[0][0] = "1";
	produto[0][1] = "Lapis";
	produto[0][2] = "20";
	produto[0][3] = "0.20";
	
	//produto 2
	produto[1][0] = "2";
	produto[1][1] = "Caneta";
	produto[1][2] = "20";
	produto[1][3] = "0.40";
	
	//produto 3
	produto[2][0] = "3";
	produto[2][1] = "Caderno";
	produto[2][2] = "20";
	produto[2][3] = "1.50";
}

//Imprime os produtos default
void produtosDisponiveis()
{
	cout << endl << "Produtos Disponiveis " << endl;
	//Larguras fixas
	int wID = 5;
	int wNome = 20;
	int wQnt = 10;
	int wPreco = 10;

	//Cabeçalho alinhado 
	cout << left << setw(wID) << "ID"
		<< setw(wNome) << "Nome"
		<< setw(wQnt) << "Qnt"
		<< setw(wPreco) << "Preco" << endl;

	//Lista de produtos
	for (int i = 0; i < totalProdutos; i++)
	{
		if (produto[i][0] != "")
		{
			
				cout << left << setw(wID) << produto[i][0] 
					<< setw(wNome) << produto[i][1]
					<< setw(wQnt) << produto[i][2]
					<< setw(wPreco) << produto[i][3];
			
			
		}
		cout << endl;
	}
}
// Adiciona Produtos
void adicionarProduto()
{
	int nProdAdicionar;

	cout << "Quantos produtos deseja adicionar? ";
	// Repete até o utilizador inserir um numero acima de 0
	while (!(cin >> nProdAdicionar) || nProdAdicionar < 0) 
	/*
	  O(!(cin >> nProdAdicionar) || nProdAdicionar <= 0) diz que se cin >> nProdAdicionar nao for um numero ou for maior ou igual a 0 para repetir
	  Temos de ter em conta que a variavel nProdAdicionar foi criada em int ou seja tem de ser um numero sem este while ao colocar texto o programa iria crashar.
	*/ 
	{
		cout << "Atencao, apenas pode inserir números e tem de ser maior que 0.\n";
		cout << "Quantos produtos deseja adicionar? ";
		cin.clear(); // para conseguir introduzir uma nova entrada || vai limpar o erro
		cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
	}
	if (nProdAdicionar + totalProdutos >= maximoProdutos)
	{
		cout << "Limite maximo de produtos atingido.\n";
		return;
	}
	for (int i = 0; i < nProdAdicionar; i++)
	{
		int qnt;
		double precoT; // preco Temporario
		string nome;
		bool produtoExiste = false;

		cout << "Nome: ";
		cin.ignore(); // Preciso disto para ele nao ler apenas ate ao espaço em caso de produtos com "2 nomes" como por exemplo "Arroz Doce". com cin >> nome; iria apenas guardar Arroz. E doce iria ficar no buffer e entrar no proximo cin.
		getline(cin, nome); // Com isto a string nome vai ser "Arroz Doce", vai obrigar a ler até o enter.

		for (int j = 0; j < totalProdutos; j++)
		{
			// Verificar se o produto ja existe, como existe apenas adiciona quantidade
			if (produto[j][1] == nome)
			{
				cout << "Produto ja existe. Que quantidade deseja adicionar?\n";
				// Repete até o utilizador inserir um numero acima de 0
				while (!(cin >> qnt) || qnt < 0)
				{
					cout << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n";
					cout << "Quantidade: ";
					cin.clear(); // para conseguir introduzir uma nova entrada || vai limpar o erro
					cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
				}

				int qntAtual = stoi(produto[j][2]); // Quantidade do produto em stock
				produto[j][2] = to_string(qntAtual + qnt);
				produtoExiste = true;
				cout << "O estoque foi atualizado.";
				break;
			}
		}

		// Senao existir entao criar um novo
		if (!produtoExiste)
		{
			produto[totalProdutos][0] = to_string(totalProdutos + 1); //to_string converte o inteiro para string e depois torna o id automatico fazendo +1
			produto[totalProdutos][1] = nome;

			cout << "Quantidade: ";
			// Repete até o utilizador inserir um numero acima de 0
			while (!(cin >> qnt) || qnt < 0)
			{
				cout << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n";
				cout << "Quantidade: ";
				cin.clear(); // para conseguir introduzir uma nova entrada || vai limpar o erro
				cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
			}
			produto[totalProdutos][2] = to_string(qnt);

			cout << "Preco: ";
			// Repete até o utilizador inserir um numero acima de 0
			while (!(cin >> precoT) || precoT < 0)
			{
				cout << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n";
				cout << "Preco: ";
				cin.clear(); // para conseguir introduzir uma nova entrada || vai limpar o erro
				cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
			}

			ostringstream conversao; // output string stream é uma variavel de uma string que me deixa formatar dados como numeros e converter para string
			conversao << fixed << setprecision(2) << precoT; // vai formatar o preco para ter 2 casas decimais
			produto[totalProdutos][3] = conversao.str();

			totalProdutos++;
		}
	}
	// Se adicionar apenas 1
	if (nProdAdicionar == 1)
	{
		cout << endl <<  "Produto adicionado.\n";
	}
	// Se adicionar mais que 1
	if (nProdAdicionar > 1)
	{
		cout << endl << "Produtos adicionados.\n";
	}
	// Imprime autalizacao de estoque
	cout << "\nAtualizacao de estoque: \n"; //para mostrar os produtos adicionados.
	produtosDisponiveis();
}

//eliminar produto
void eliminarProduto()
{
	int nProdEliminar;
	cout << "Quantos produtos deseja eliminar? ";
	cin >> nProdEliminar;

	if (nProdEliminar > totalProdutos)
	{
		cout << "Nao existem " << nProdEliminar << " produtos na loja.";
		return eliminarProduto();
	}

	bool encontrado = false;

	for (int n = 0; n < nProdEliminar; n++)
	{
		string id;
		cout << "\nDigite o ID do produto a eliminar: ";
		cin >> id;

		for (int i = 0; i < totalProdutos; i++)
		{
			if (produto[i][0] == id)
			{
				for (int j = i; j < totalProdutos - 1; j++)
				{
					for (int k = 0; k < colunas; k++)
					{
						produto[j][k] = produto[j + 1][k]; // vai colocar a linha vazia em ultimo
					}
				}
				totalProdutos--; // Elimina a ultima linha que se encontra vazia
				cout << endl << "Produto eliminado. \n";
				encontrado = true;
				break;
			}
		}
	}
	if (!encontrado)
	{
		cout << "Produto nao encontrado.\n";
	}
	cout << "\nAtualizacao de estoque: \n"; //para mostrar os produtos restantes e atualizar estoque.
	produtosDisponiveis();
}

//adicionar ao carrinho de compra
void efetuarVenda() {
    vector<vector<string>> carrinho;

    cout << "\n=== NOVA VENDA ===\n";

    do {
        listarProdutos();

        string id;
        cout << "ID do produto ou VOLTAR para voltar ao Menu Anterior: ";
        cin >> id;

        if (id == "VOLTAR") break;

        bool encontrado = false;
        for (int i = 0; i < totalProdutos; i++) 
        {
            if (produto[i][0] == id) 
            {
                encontrado = true;
                int quantidade;
                cout << "Quantidade: ";
                cin >> quantidade;

                while (quantidade <= 0)
                   {
                        cout << "Quantidade inválida\n";
                        cout << "Quantos produtos deseja comprar? ";
                        cin.clear(); // para conseguir introduzir uma nova entrada || vai limpar o erro
                        cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
                    }

                double preco = stod(produto[i][2]);
                int iva = stoi(produto[i][3]);
                double precoComIva = preco * (1 + iva / 100.0);

                carrinho.push_back({
                    produto[i][0], produto[i][1],
                    to_string(quantidade),
                    to_string(preco),
                    to_string(iva),
                    to_string(precoComIva),
                    to_string(quantidade * precoComIva)
                    });

                cout << produto[i][1] << " adicionado.\n";
                break;
            }
        }

        if (!encontrado) {
            cout << "Produto não encontrado!\n";
        }

    } while (true);

    if (!carrinho.empty()) {
        processarCheckout(carrinho);
    }
}


int main()
{
	inicializarProdutos();

	int opcao;

	do {
		system("CLS");
		cout << endl << "|=============| ";
		cout << "Papelaria Note & Book";
		cout << " |==============|\n";
		cout << endl;
		cout << "[1] Produtos Disponiveis\n";
		cout << "[2] Comprar Produto\n";
		cout << "[3] Checkout\n";
		cout << "[4] Adicionar Produto\n";
		cout << "[5] Eliminar Produto\n";
		cout << "[6] Sair\n";
		cout << "Escolha uma opcao: ";
		cin >> opcao;
		switch (opcao)
		{
		case 1:
			// Mostrar produtos disponíveis
			produtosDisponiveis();
			break;
		case 2:
			// Comprar produto
			break;
		case 3:
			// Carrinho
			break;
		case 4:
			// Adicionar produto
			adicionarProduto();
			break;
		case 5:
			// Eliminar produto
			eliminarProduto();
			break;
		case 6:
			cout << endl << "A desligar o progama...\n";
			break;
		default:
			// Opcao invalida
			cout << endl << "Opcao invalida. Tente novamente.\n";
			break;
		}
		if (opcao != 6)
		{
			cout << endl << "Pressione enter para voltar ao menu.";
			cin.ignore();
			cin.get();
		}
	} while (opcao != 6); // repete o menu até sair do programa
	
}





























// Isto poderá ser a talão mas depois vemos melhor,
// 
// 
//cout << "|======================================|";
//cout << "|            Lojinha do Joao           |";
//cout << "| Data                                 |";
//cout << "| Numero da fatura                     |";
//cout << "| Numero do cliente                    |";
//cout << "| Prd  |  Qnt  |  Preco s/IVA  |  IVA  |";
//cout << "| Total c/IVA                          |";
//cout << "| Valor Entregue                       |";
//cout << "| Troco                                |";
//cout << "|======================================|";


//Usado inicialmente mas foi exilado xD
// adicionar produto
//void adicionarProduto()
//{
//	int nProdAdicionar;
//	int preco;
//	int qnt;
//	cout << "Quantos produtos deseja adicionar? ";
//	cin >> nProdAdicionar;
//
//	if (nProdAdicionar + totalProdutos >= maximoProdutos)
//	{
//		cout << "Limite máximo de produtos atingido.";
//		return;
//	}
//	for (int i = 0; i < nProdAdicionar; i++)
//	{
//		produto[totalProdutos][0] = to_string(totalProdutos + 1); //to_string converte o inteiro para string e depois torna o id automatico fazendo +1
//		cout << "Nome: ";
//		cin >> produto[totalProdutos][1];
//		cout << "Quantidade: ";
//		cin >> qnt;
////cin >> produto[totalProdutos][2];
//		produto[totalProdutos][2] = to_string(qnt);
//		cout << "Preco: ";
//		cin >> preco;
//		produto[totalProdutos][3] = to_string(preco);
////cin >> produto[totalProdutos][3];
//		totalProdutos++;
//	}
//}
