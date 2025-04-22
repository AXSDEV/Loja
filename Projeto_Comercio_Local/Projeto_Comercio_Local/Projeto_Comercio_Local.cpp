// Projeto_Comercio_Local.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <ctime>
using namespace std;


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
	cout << "Escolha uma opcao: ";
	cin >> opcao;
	switch (opcao) {
	case 1:
		// Listar produtos disponíveis
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
	default:
		cout << "Opcao invalida. Tente novamente.\n";
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
