// Projeto_Comercio_Local.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

int totalProdutos = 3;
int colunas = 4; // ID, Nome, Quantidade, Preco 
string** produto = new string * [totalProdutos];

void inicializarProdutos()
{
	for (int i = 0; i < totalProdutos; i++)
	{
		produto[i] = new string[colunas];
	}
	//produto 1
	produto[0][0] = "1";
	produto[0][1] = "Pao";
	produto[0][2] = "20";
	produto[0][3] = "0.45";
	
	//produto 2
	produto[1][0] = "2";
	produto[1][1] = "Leite";
	produto[1][2] = "20";
	produto[1][3] = "0.80";
	
	//produto 3
	produto[2][0] = "3";
	produto[2][1] = "Queijo";
	produto[2][2] = "";
	produto[2][3] = "1.50";
}

//print matrix
void produtosDisponiveis()
{
	cout << endl << "Produtos Disponiveis " << endl;
	cout << "ID\tNome\tQnt\tPreco" << endl;
	for (int i = 0; i < totalProdutos; i++)
	{
		for (int j = 0; j < colunas; j++)
		{
			cout << produto[i][j] << "\t";
		}
		cout << endl;
	}
}

//adicionar produto
void adicionarProduto()
{
	produto[totalProdutos][0] = to_string(totalProdutos + 1); //to_string converte o inteiro para string e depois torna o id automatico fazendo +1
	cout << "Nome: ";
	cin >> produto[totalProdutos][1];
	cout << "Quantidade: ";
	cin >> produto[totalProdutos][2];
	cout << "Preco: ";
	cin >> produto[totalProdutos][3];
	totalProdutos++;
}

//eliminar produto
void eliminarProduto()	
{
string id;
cout<< "\nDigite o ID do produto a eliminar: ";
cin>> id;
bool encontrado = false;
for (int i = 0; i < totalProdutos; i++)
	{
		if(produto[i][0]==id)
		{
		produto[i][0] = "";
		produto[i][1] = "";
		produto[i][2] = "";
		produto[i][3] = "";
		cout<<" Produto eliminado. \n";
		encontrado=true;
		break;
		}
	}
if(!encontrado)
{
cout<<"Produto não encontrado.\n";
}
cout<<"\nAtualização de estoque: \n"; //para mostrar os produtos restantes e atualizar estoque.
for (int i = 0; i < totalProdutos; i++)
	{
		if(produto[i][0]!="")
		{
		cout<< "ID\tNome\tQnt\tPreco" << endl;
		for (int i = 0; i < totalProdutos; i++)
		{
		for (int j = 0; j < 4; j++)
		{
			cout << produto[i][j] << "\t";
		}
		cout << endl;
		}
		}
	}
}





int main()
{
	inicializarProdutos();

	int opcao;
	do {
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
			// Checkout
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
			cout << "A desligar o progama...\n";
			break;
		default:
			// Opcao invalida
			cout << "Opcao invalida. Tente novamente.\n";
			break;
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

