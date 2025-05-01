// Projeto_Comercio_Local.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip> // para usar manipuladores de entrada e saida para controlar a formatação dos dados
#include <string> // para usar strings
#include <ctime> // para adicionar horas e datas (talao)
#include <sstream> // para poder usar setprecision em strings || deixa-me usar manipulador de strings
#include <vector>
#include <algorithm>  // necessario para transform
#include <cctype>     // necessario para tolower

using namespace std;

int totalProdutos = 3;
int colunas = 4; // ID, Nome, Quantidade, Preco 
int maximoProdutos = 100;
string** produto = new string * [maximoProdutos];
int numeroFatura = 1;
int numeroCliente = 1;
int capacidadeCarrinho = 50;
int linhacarrinho = 0;

// Funções
void inicializarProdutos();
void produtosDisponiveis();
//void menuPrincipal();
void adicionarCarrinho(string** carrinho);
void adicionarProduto();
void eliminarProduto();
bool sortearVendaGratis();
//void listarProdutos();
void processarCheckout(string** carrinho);
void imprimirTalao(string** carrinho, double total, double valorPago, double troco, bool gratis);
void menu(string** carrinho);
void eliminarCarrinho(string** carrinho);
void mostrarCarrinho(string** carrinho);

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
string toLower(string nomeProduto)
{
	transform(nomeProduto.begin(), nomeProduto.end(), nomeProduto.begin(), ::tolower); // transforma em lowercase
	return nomeProduto; // envia o nome em lowercase para nomeProduto
}

void adicionarProduto()
{
	int nProdAdicionar;

	cout << "Quantos produtos deseja adicionar? ";
	// Repete até o utilizador inserir um numero acima de 0
	while (!(cin >> nProdAdicionar) || nProdAdicionar <= 0)
	{
		/*
		  O(!(cin >> nProdAdicionar) || nProdAdicionar <= 0) diz que se cin >> nProdAdicionar nao for um numero ou for maior ou igual a 0 para repetir
		  Temos de ter em conta que a variavel nProdAdicionar foi criada em int ou seja tem de ser um numero sem este while ao colocar texto o programa iria crashar.
		*/
		cout << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n";
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

		string nomeInserido = toLower(nome); // cria nomeInserido para colocar nome em lowercase para comparação

		for (int j = 0; j < totalProdutos; j++)
		{
			string nomeExistente = toLower(produto[j][1]); // cria nomeExistente para colocar todos os nomes de produtos na array em lowercase para comparação

			// Verificar se o produto ja existe, como existe apenas adiciona quantidade
			if (nomeExistente == nomeInserido) // se forem iguais então já existe
			{
				cout << "Produto ja existe. Que quantidade deseja adicionar?\n";
				// Repete até o utilizador inserir um numero acima de 0
				while (!(cin >> qnt) || qnt <= 0)
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
		cout << endl << "Produto adicionado.\n";
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
		return;
	}

	bool encontrado = false;

	for (int n = 0; n < nProdEliminar; n++)
	{
		string id;
		produtosDisponiveis();
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

bool sortearVendaGratis() {
	return (rand() % 10) == 0; // 10% de chance
}

void mostrarCarrinho(string** carrinho) {
	int opcao;
	double total = 0.0;
	system("CLS");
	cout << "\n=== Carrinho de Compras ===\n";
	cout << "----------------------------------------------------------------\n";
	cout << "| ID  | Nome           | Qtd | Preco Unit. |  IVA  | Subtotal   |\n";
	cout << "----------------------------------------------------------------\n";

	for (int i = 0; i < linhacarrinho; i++) {
		string id = carrinho[i][0];
		string nome = carrinho[i][1];
		int quantidade = stoi(carrinho[i][2]);
		double precoVenda = stod(carrinho[i][3]);
		double iva = stod(carrinho[i][4]);
		double subtotal = stod(carrinho[i][5]);

		total += subtotal;

		cout << "| " << setw(3) << left << id << " | "
			<< setw(14) << left << nome << " | "
			<< setw(3) << right << quantidade << " | "
			<< setw(11) << fixed << setprecision(2) << precoVenda << " | "
			<< setw(5) << fixed << setprecision(2) << iva << " | "
			<< setw(10) << fixed << setprecision(2) << subtotal << " |\n";
	}

	cout << "-----------------------------------------------------------------\n";
	cout << "| TOTAL A PAGAR: " << setw(46) << right << fixed << setprecision(2)
		<< total << " |\n";
	cout << "-----------------------------------------------------------------\n";

	cout << endl << "Pressione enter para ver o menu do carrinho.";
	cin.ignore();
	cin.get();

	do
	{
		system("CLS");
		cout << "[1] Adicionar Produto ao carrinho\n";
		cout << "[2] Eliminar Produto do carrinho\n";
		cout << "[3] Voltar ao Menu Principal.\n";
		cout << "\nEscolha uma opcao: ";
		cin >> opcao;

	switch (opcao)
	{
	case 1: 
		adicionarCarrinho(carrinho);
		break;
	case 2: 
		eliminarCarrinho(carrinho);
		break;
	case 3: 
		menu(carrinho);
		break;
	default:
		// Opcao invalida
		cout << endl << "Opcao invalida. Tente novamente.\n";
		break;
	}
	} while (opcao !=6);
	if (opcao != 6)
	{
		cout << endl << "Pressione enter para voltar ao menu.";
		cin.ignore();
		cin.get();
	}
}

void eliminarCarrinho(string** carrinho) {
	
	int nProdEliminarCarrinho;
	cout << "Quantos produtos deseja eliminar? ";
	cin >> nProdEliminarCarrinho;

	if (nProdEliminarCarrinho > capacidadeCarrinho)
	{
		cout << "Nao existem " << nProdEliminarCarrinho << " produtos na loja.";
		return;
	}
	for (int n = 0; n < nProdEliminarCarrinho; n++)
	{
		string id;
		cout << "\nDigite o ID do produto a eliminar: ";
		cin >> id;

		bool encontrado = false;

		for (int i = 0; i < linhacarrinho; i++)
		{
			if (carrinho[i][0] == id)
			{
				for (int p = 0; p < totalProdutos; p++)
				{
					if (produto[p][0] == id)
					{
						int qntEliminada = stoi(carrinho[i][2]); // quantidade que tinha sido adicionado ao carrinho
						int qntEstoqueAtual = stoi(produto[p][2]); // quantidade no stock 
						produto[p][2] = to_string(qntEstoqueAtual + qntEliminada); // soma dos sotck + a quantidade eliminada do carrinho 
						break;
					}
				}
				for (int j = i; j < linhacarrinho - 1; j++)
				{
					for (int k = 0; k < 6; k++)
					{
						carrinho[j][k] = carrinho[j + 1][k]; // vai colocar a linha vazia em ultimo
					}
				}
				for (int n = 0; n < 6; n++)
				{
					carrinho[linhacarrinho - 1][n].clear(); // .clear é usado para limpar o conteudo de uma string tornado-a em ""
				}

				linhacarrinho--; // Elimina a ultima linha que se encontra vazia
				cout << endl << "Produto eliminado. \n";
				encontrado = true;
				break;
			}
		}
		if (!encontrado)
		{
			cout << "Produto nao encontrado no carrinho.\n";
		}
	}
}

void adicionarCarrinho(string** carrinho) {
	string continuar = "sim";

	do {
		produtosDisponiveis();
		cout << "ID do produto ou 'SAIR' para retornar ao Menu Principal: ";
		string id;
		cin >> id;
		id = toLower(id);
		if (id == "sair") break;

		bool encontrado = false;
		for (int i = 0; i < totalProdutos; i++) {
			if (produto[i][0] == id) {
				encontrado = true;

				int quantidade;
				int stockAtual = stoi(produto[i][2]);

				cout << "Produto: " << produto[i][1] << endl;
				cout << "Quantidade disponivel: " << produto[i][2] << endl;

				do {
					cout << "Digite quantidade desejada: ";
					cin >> quantidade;

					if (quantidade <= 0 || quantidade > stockAtual) {
						cout << "Quantidade invalida ou insuficiente no estoque! Tente novamente.\n";
						return;
					}
				} while (quantidade <= 0 || quantidade > stockAtual);

				double precoCusto = stod(produto[i][3]);
				double precoVenda = precoCusto * 1.30;
				double iva = precoVenda * 0.23;
				double subtotal = (iva + precoVenda) * quantidade;
				
				if (linhacarrinho >= capacidadeCarrinho) {
					cout << "Carrinho cheio! Finalize a compra ou limpe o carrinho.\n";
					break;
				}

				carrinho[linhacarrinho][0] = produto[i][0];
				carrinho[linhacarrinho][1] = produto[i][1];
				carrinho[linhacarrinho][2] = to_string(quantidade);
				carrinho[linhacarrinho][3] = to_string(precoVenda);
				carrinho[linhacarrinho][4] = to_string(iva);
				carrinho[linhacarrinho][5] = to_string(subtotal);

				linhacarrinho++;

				produto[i][2] = to_string(stockAtual - quantidade);

				cout << "Produto " << produto[i][0] << " adicionado ao carrinho!\n";
				break;
			}
		}
		if (!encontrado) {
			cout << "Produto nao encontrado!\n";
		}

		cout << "Deseja adicionar outro produto? (sim/nao): ";
		cin >> continuar;

		continuar = toLower(continuar);

	} while (continuar == "sim");
}



void processarCheckout(string** carrinho) {
	double total = 0.0;
	cout << "\nResumo da Compra:\n";
	cout << "----------------------------------------------------------------\n";
	cout << "| ID  | Nome           | Qtd | Preco Unit. |  IVA  | Subtotal   |\n";
	cout << "----------------------------------------------------------------\n";

	for (int i = 0; i < linhacarrinho; i++) {
		string id = carrinho[i][0];
		string nome = carrinho[i][1];
		int quantidade = stoi(carrinho[i][2]);
		double precoVenda = stod(carrinho[i][3]);
		double iva = stod(carrinho[i][4]);
		double subtotal = stod(carrinho[i][5]);

		total += subtotal;

		cout << "| " << setw(3) << left << id << " | "
			<< setw(14) << left << nome << " | "
			<< setw(3) << right << quantidade << " | "
			<< setw(11) << fixed << setprecision(2) << precoVenda << " | "
			<< setw(5) << fixed << setprecision(2) << iva << " | "
			<< setw(10) << fixed << setprecision(2) << subtotal << " |\n";
	}

	cout << "-----------------------------------------------------------------\n";
	cout << "| TOTAL A PAGAR: " << setw(46) << right << fixed << setprecision(2)
		<< total << " |\n";
	cout << "-----------------------------------------------------------------\n";

	bool gratis = sortearVendaGratis();
	double valorPago = 0.0;
	double troco = 0.0;

	if (gratis) {
		cout << "\nParabens! A sua compra foi gratuita!\n";
		total = 0.0;
	}
	else {
		cout << "\nTotal a pagar: " << fixed << setprecision(2) << total << " euros\n";

		do {
			cout << "Valor recebido: ";
			cin >> valorPago;
			if (valorPago < total) {
				cout << "Valor insuficiente!\n";
			}
		} while (valorPago < total);

		troco = valorPago - total;
	}

	imprimirTalao(carrinho, total, valorPago, troco, gratis);

	numeroFatura++;
	numeroCliente++;

	// Limpar o carrinho após o checkout

	for (int i = 0; i < linhacarrinho; i++) {

		for (int j = 0; j < 6; j++) {

			carrinho[i][j].clear();

		}

	}

	linhacarrinho = 0;

}


void imprimirTalao(string** carrinho, double total, double valorPago, double troco, bool gratis) {
	cout << "\n\n==================== TALAO DE COMPRA ====================\n";
	time_t agora = time(0);
	tm tempoLocal;
	localtime_s(&tempoLocal, &agora);
	cout << "Data: " << tempoLocal.tm_mday << "/" << tempoLocal.tm_mon + 1 << "/" << tempoLocal.tm_year + 1900 << "\n";
	cout << "Fatura n: " << numeroFatura << " | Cliente n: " << numeroCliente << endl;
	cout << "---------------------------------------------------------\n";
	cout << left << setw(15) << "Produto" << setw(10) << "Qtd" << setw(15) << "Preco S/IVA" << setw(10) << "IVA" << setw(10) << "Total" << endl;
	cout << "---------------------------------------------------------\n";

	for (int i = 0; i < linhacarrinho; i++) {
		cout << left << setw(15) << carrinho[i][1]
			<< setw(10) << carrinho[i][2]
			<< setw(15) << fixed << setprecision(2) << stod(carrinho[i][3])
			<< setw(10) << fixed << setprecision(2) << stod(carrinho[i][4])
			<< setw(10) << fixed << setprecision(2) << stod(carrinho[i][5]) << endl;
	}
	cout << "---------------------------------------------------------\n";

	if (gratis) {
		cout << "COMPRA GRATUITA!\n";
	}
	else {
		cout << "Total: " << fixed << setprecision(2) << total << " euros\n";
		cout << "Valor pago: " << fixed << setprecision(2) << valorPago << " euros\n";
		cout << "Troco: " << fixed << setprecision(2) << troco << " euros\n";
	}

	cout << "=========================================================\n";
	cout << "Obrigado pela sua preferencia!\n";
}

void menu(string** carrinho) {
	int opcao;

	do {
		system("CLS");
		cout << endl << "|=============| ";
		cout << "Papelaria Note & Book";
		cout << " |==============|\n";
		cout << endl;
		cout << "[1] Produtos Disponiveis\n";
		cout << "[2] Carrinho\n";
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
			mostrarCarrinho(carrinho);
			break;
		case 3:
			// carrinho
			processarCheckout(carrinho);

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

int main()
{
	inicializarProdutos();
	

	string** carrinho = new string * [capacidadeCarrinho];

	for (int i = 0; i < capacidadeCarrinho; i++) {
		carrinho[i] = new string[6];  // 6 colunas: ID, Nome, Quantidade, Preço, IVA, Subtotal
	}
	menu(carrinho);
}












//
//if (linhacarrinho > 0) {
//	processarCheckout();
//	// Resetar o carrinho após o checkout
//	for (int i = 0; i < linhacarrinho; i++) {
//		delete[] carrinho[i];
//	}
//	linhacarrinho = 0;
//}
//else {
//	cout << "Carrinho vazio. Adicione produtos antes de fazer checkout.\n";
//}














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
