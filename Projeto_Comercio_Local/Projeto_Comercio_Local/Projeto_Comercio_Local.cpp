// Projeto_Comercio_Local.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
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
	produto[2][2] = "20";
	produto[2][3] = "1.50";
}

//print matrix
void produtosDisponiveis()
{
	cout << endl << "Produtos Disponiveis " << endl;
	cout << "ID\tNome\tQnt\tPreco" << endl;
	for (int i = 0; i < totalProdutos; i++)
	{
		if (produto[i][0] != "")
		{
			for (int j = 0; j < colunas; j++)
			{
				cout << produto[i][j] << "\t";
			}
			cout << endl;
		}
		
	}
}

//adicionar produto
void adicionarProduto()
{
	int nProdAdicionar;
	cout << "Quantos produtos deseja adicionar? ";
	cin >> nProdAdicionar;

	if (nProdAdicionar + totalProdutos >= maximoProdutos)
	{
		cout << "Limite máximo de produtos atingido.";
		return;
	}
	for (int i = 0; i < nProdAdicionar; i++)
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
		cout << "\nIntroduza o ID do produto a eliminar: ";
		cin >> id;
		for (int i = 0; i < totalProdutos; i++)
		{
			if (produto[i][0] == id)
			{
				for (int j = i; j < totalProdutos - 1; j++)
				{
					for (int k = 0; k < colunas; k++)
					{
						produto[j][k] = produto[j + 1][k];
					}
				}
				totalProdutos--;
				cout << endl << "Produto eliminado. \n";
				encontrado = true;
				break;
			}
		}
	}
	if (!encontrado)
	{
		cout << "Produto não encontrado.\n";
	}
	cout << "\nAtualizacao de estoque: \n"; //para mostrar os produtos restantes e atualizar estoque.
	produtosDisponiveis();
}

//Falta Terminar...
vector<vector<string>> carrinho;		
void adicionarAoCarrinho() 
{
    
int quantidade;
    
    produtosDisponiveis();
    
    bool encontrado = false;
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') 
	{
		cout << "Digite o ID do produto: ";
	   	cin >> id;
		cout << "Digite a quantidade: ";
	        cin >> quantidade;
	    
	    	for (int i = 0; i < totalProdutos; i++) 
		{
	        if (produto[i][0] == id) 
			{
		            int estoqueAtual = stoi(produto[i][2]); // Converte uma string em um número inteiro. Biblioteca <string>
		            if (quantidade <= 0) 
			    {
		                cout << "Quantidade invalida!\n";
		                return;
		            }
		            if (quantidade > estoqueAtual) 
			    {
		                cout << "Quantidade indisponivel!\n";
		                return;
		            }
		double preco = stod(produto[i][3]);
		double subtotal = quantidade * preco;
	
		vector<string> itemCarrinho = 
			{
	                    produtos[i][0],
	                    produtos[i][1],
	                    to_string(quantidade),
	                    produtos[i][3],
	                    to_string(subtotal)
	                };
	
		carrinho.push_back(itemCarrinho);
		cout << "Produto adicionado ao carrinho!\n";
		encontrado = true;
		break;
	            }
	        }
	
	        if (!encontrado) 
		{
	            cout << "Produto não encontrado.\n";
	        }
	
	        cout << "Deseja adicionar outro produto? (s/n): ";
	        cin >> continuar;
	}

   
    cout << "\n==== CARRINHO DE COMPRAS ====\n";
    double total = 0.0;
    for (int i = 0; i < carrinho.size(); i++) 
    {
        cout << "Produto: " << carrinho[i][1]
             << " | Quantidade: " << carrinho[i][2]
             << " | Preço: € " << carrinho[i][3]
             << " | Subtotal: €" << carrinho[i][4] << endl;
        total = total + stod(carrinho[i][4]);
    }
		
	carrinho.push_back(itemCarrinho);
	cout << "Produto adicionado ao carrinho!\n";
	encontrado = true;
	break;

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
