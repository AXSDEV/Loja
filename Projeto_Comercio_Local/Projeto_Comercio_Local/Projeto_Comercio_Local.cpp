// Projeto_Comercio_Local.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;


void produtosDisponiveis()
{

	int totalProdutos = 1;
	int colunas = 3; // ID, Nome, Preco 

	string** produtos = new string * [totalProdutos];
	for (int i = 0; i < totalProdutos; i++)
	{
		produtos[i] = new string[colunas];
	}
	produtos[0][0] = "1";
	produtos[0][1] = "Pao";
	produtos[0][2] = "0.45";


	//print matrix
	cout << endl << "Produtos Disponiveis " << endl;
	cout << "ID\tNome\tPreco" << endl;
	for (int i = 0; i < totalProdutos; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			cout << produtos[i][j] << "\t";
		}
		cout << endl;
	}
}


int main()
{
	int opcao;
	cout << "|=============| ";
	cout << "Nome da Loja a Decidir";
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
	switch (opcao) {
	case 1:
		// Mostrar produtos disponíveis
		return void(produtosDisponiveis());
		break;
	case 2:
		// Comprar produto
		break;
	case 3:
		// Checkout
		break;
	case 4:
		// Adicionar produto
		break;
	case 5:
		// Eliminar produto
		break;
	case 6:
		cout << "A desligar o progama...\n";
		return 0;
		break;
	default:
		// Opcao invalida
		cout << "Opcao invalida. Tente novamente.\n";
		return main();
		break;
	}


	
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
