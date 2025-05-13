#include <iostream>  // biblioteca padrão de entrada e saída
#include <iomanip>   // para usar manipuladores de entrada e saida para controlar a formatação dos dados
#include <string>    // para usar strings
#include <ctime>     // para adicionar horas e datas (talao)
#include <sstream>   // para poder usar setprecision em strings || deixa-me usar manipulador de strings
#include <windows.h> // necessario para usar sleep
#include <algorithm> // necessario para transform
#include <cctype>    // necessario para tolower
#include <conio.h>   // para usar _getch() para esconder a senha no login
// \033 é o escape para iniciar ANSI 27 | [0m é para repor para formatação padrão | [31m é para cor vermelho | [32m é para cor verde
#define RESET "\033[0m"  // Define a cor de texto para padrão
#define RED "\033[31m"   // Define a cor de texto para vermelho
#define GREEN "\033[32m" // Define a cor de texto para verde
// ASCII é um padrão de codificação de caracteres
// ANSI é para códigos especiais que controlam a aparência do texto no terminal.
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
void adicionarCarrinho(string** carrinho);
void adicionarProduto();
void eliminarProduto();
bool sortearVendaGratis();
void processarCheckout(string** carrinho);
void imprimirTalao(string** carrinho, double total, double valorPago, double troco, bool gratis);
void menu(string** carrinho);
void eliminarCarrinho(string** carrinho);
void mostrarCarrinho(string** carrinho);
void modificarPreco(double novoPrecoT, string id);
void printCarrinho(string** carrinho, double total);
void limparCarrinho(string** carrinho);

bool login()
{
    string utilizador, senha, senhaEscondida;
    char caracter;

    cout << "====== LOGIN ADMIN ======";
    cout << "\n Utilizador: ";
    getline(cin, utilizador); // Para caso alguem escreva por exemplo admin arroz nao consiga entrar, sem o getline ele apesar de estar escrito admin arroz o buffer iria apenas ler admin e iria conseguir efeturar login
    cout << "\n Palavra-Passe: ";

    // Ler a senha sem mostrá-la
    while ((caracter = _getch()) != 13) // 13 é o código para ENTER em ASCII ou seja enquanto nao der ENTER repete
    {
        if (caracter == 8 && !senhaEscondida.empty()) // 8 representa BACKSPACE em ASCII
        {
            senhaEscondida.pop_back();
            cout << "\b \b"; // \b faz com que o cursor volte uma posicao para trás o space vai substituir o que esta escrito por um espaço e o outro \b volta a posicao atras tirando o espaço em branco
        }
        else if (caracter != 8)
        {
            senhaEscondida.push_back(caracter); // Adiciona os caracteres digitados na string senhaEscondida
            cout << "*";                        // Mostra * por cada caracter digitado
        }
    }

    senha = senhaEscondida;

    if (utilizador == "admin" && senha == "admin123")
    {
        system("CLS");
        cout << GREEN 
             << "Bem-Vindo!" 
             << RESET;
        Sleep(3000);

        return true;
    }
    cout << RED << endl
         << "\nAs credenciais sao invalidas!\n"
         << RESET;
    return false;
}

void inicializarProdutos()
{
    for (int i = 0; i < maximoProdutos; i++)
    {
        produto[i] = new string[colunas];
    }
    // produto 1
    produto[0][0] = "1";
    produto[0][1] = "Lapis";
    produto[0][2] = "20";
    produto[0][3] = "0.20";

    // produto 2
    produto[1][0] = "2";
    produto[1][1] = "Caneta";
    produto[1][2] = "20";
    produto[1][3] = "0.40";

    // produto 3
    produto[2][0] = "3";
    produto[2][1] = "Caderno";
    produto[2][2] = "20";
    produto[2][3] = "1.50";
}

// Imprime os produtos default
void produtosDisponiveis()
{
    cout << "Produtos Disponiveis " << endl;

    // Cabeçalho
    cout << left << setw(5) << "ID"
         << setw(20) << "Nome"
         << setw(10) << "Qnt"
         << setw(10) << "Preco" << endl;

    // Lista de produtos
    for (int i = 0; i < totalProdutos; i++)
    {
        cout << left << setw(5) << produto[i][0]
             << setw(20) << produto[i][1]
             << setw(10) << produto[i][2]
             << setw(10) << produto[i][3];

        cout << endl;
    }
}

// Inicialização do toLower
string toLower(string nomeProduto)
{
    transform(nomeProduto.begin(), nomeProduto.end(), nomeProduto.begin(), ::tolower); // transforma em lowercase
    return nomeProduto;                                                                // envia o nome em lowercase para nomeProduto
}

// Adiciona Produtos
void adicionarProduto()
{
    int nProdAdicionar;

    cout << "Quantos produtos deseja adicionar? ";
    // Repete até o utilizador inserir um numero acima de 0
    while (!(cin >> nProdAdicionar) || nProdAdicionar < 0)
    {
        /*
          O(!(cin >> nProdAdicionar) || nProdAdicionar <= 0) diz que se cin >> nProdAdicionar nao for um numero ou for maior ou igual a 0 para repetir
          Temos de ter em conta que a variavel nProdAdicionar foi criada em int ou seja tem de ser um numero sem este while ao colocar texto o programa iria crashar.
        */
        cout << endl << RED 
             << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n" 
             << RESET;
        cout << endl 
             << "Quantos produtos deseja adicionar? ";
        cin.clear();            // para conseguir introduzir uma nova entrada || vai limpar o erro
        cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
    }

    if (nProdAdicionar + totalProdutos >= maximoProdutos)
    {
        cout << RED << "Limite maximo de produtos atingido.\n"
             << RESET;
        return;
    }
    for (int i = 0; i < nProdAdicionar; i++)
    {
        int qnt;
        double precoT; // preco Temporario
        string nome;
        bool produtoExiste = false;

        cout << "Nome: ";
        cin.ignore();       // Preciso disto para ele nao ler apenas ate ao espaço em caso de produtos com "2 nomes" como por exemplo "Arroz Doce". com cin >> nome; iria apenas guardar Arroz. E doce iria ficar no buffer e entrar no proximo cin.
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
                    cout << endl << RED 
                         << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n" 
                         << RESET;
                    cout << endl 
                         << "Quantidade: ";
                    cin.clear();            // para conseguir introduzir uma nova entrada || vai limpar o erro
                    cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
                }

                int qntAtual = stoi(produto[j][2]); // Quantidade do produto em stock
                produto[j][2] = to_string(qntAtual + qnt);
                produtoExiste = true;
                cout << "O estoque foi atualizado.";
                Sleep(2000);
                break;
            }
        }

        // Senao existir entao criar um novo
        if (!produtoExiste)
        {
            produto[totalProdutos][0] = to_string(totalProdutos + 1); // to_string converte o inteiro para string e depois torna o id automatico fazendo +1
            produto[totalProdutos][1] = nome;

            cout << "Quantidade: ";
            // Repete até o utilizador inserir um numero acima de 0
            while (!(cin >> qnt) || qnt < 0)
            {
                cout << endl << RED 
                     << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n" 
                     << RESET;
                cout << endl 
                     << "Quantidade: ";
                cin.clear();            // para conseguir introduzir uma nova entrada || vai limpar o erro
                cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
            }
            produto[totalProdutos][2] = to_string(qnt);

            cout << "Preco: ";
            // Repete até o utilizador inserir um numero acima de 0
            while (!(cin >> precoT) || precoT < 0)
            {
                cout << endl << RED 
                     << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n" 
                     << RESET;
                cout << endl 
                     << "Preco: ";
                cin.clear();            // para conseguir introduzir uma nova entrada || vai limpar o erro
                cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
            }

            ostringstream conversao;                         // output string stream é uma variavel de uma string que me deixa formatar dados como numeros e converter para string
            conversao << fixed << setprecision(2) << precoT; // vai formatar o preco para ter 2 casas decimais
            produto[totalProdutos][3] = conversao.str();

            totalProdutos++;
        }
    }
    // Se adicionar apenas 1
    if (nProdAdicionar == 1)
    {
        cout << GREEN << endl
             << "Produto adicionado.\n"
             << RESET;
        Sleep(2000);
    }
    // Se adicionar mais que 1
    if (nProdAdicionar > 1)
    {
        cout << GREEN << endl
             << "Produtos adicionados.\n"
             << RESET;
        Sleep(2000);
    }
    // Imprime autalizacao de estoque
    system("CLS");
    cout << "|=============| ";
    cout << "Atualizacao de estoque "; // para mostrar os produtos adicionados.
    cout << " |==============|\n";
    produtosDisponiveis();
}

// eliminar produto
void eliminarProduto()
{
    int nProdEliminar;
    cout << "Quantos produtos deseja eliminar? ";

    while (!(cin >> nProdEliminar) || nProdEliminar < 0)
    {
        cout << endl << RED 
             << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n" 
             << RESET;
        cout << endl 
             << "Quantos produtos deseja eliminar? ";
        cin.clear();            // para conseguir introduzir uma nova entrada || vai limpar o erro
        cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
    }

    if (nProdEliminar > totalProdutos)
    {
        cout << RED 
             << "Nao existem " << nProdEliminar << " produtos na loja." 
             << RESET;
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
                system("CLS");
                cout << RED
                     << "Produto eliminado. \n"
                     << RESET << endl;
                Sleep(2000);
                encontrado = true;
                break;
            }
        }
    }
    if (!encontrado)
    {
        cout << RED << "Produto nao encontrado.\n"
             << RESET;
    }
    cout << "Atualizacao de estoque : \n"; // para mostrar os produtos restantes e atualizar estoque.
    produtosDisponiveis();
}

bool sortearVendaGratis()
{
    return (rand() % 10) == 0; // 10% de chance
}

void printCarrinho(string** carrinho)
{
    double total = 0.0;

    if (carrinho[0][0] == "")
    {
        cout << "O carrinho esta vazio." << endl
            << endl;
        return;
    }

    cout << "=== Carrinho de Compras ===\n";
    cout << "----------------------------------------------------------------\n";
    cout << "| ID  | Nome           | Qtd | Preco Unit. |  IVA  | Subtotal   |\n";
    cout << "----------------------------------------------------------------\n";

    for (int i = 0; i < linhacarrinho; i++)
    {
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
}

void mostrarCarrinho(string** carrinho)
{
    int opcao;

    do
    {
        system("CLS");
        printCarrinho(carrinho);
        cout << "[1] Adicionar Produto ao carrinho\n";
        cout << "[2] Eliminar Produto do carrinho\n";
        cout << "[3] Checkout\n";
        cout << "[4] Voltar ao Menu Principal\n";
        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            system("CLS");
            adicionarCarrinho(carrinho);
            break;
        case 2:
            system("CLS");
            eliminarCarrinho(carrinho);
            break;
        case 3:
            system("CLS");
            processarCheckout(carrinho);
            break;
        case 4:
            break;
        default:
            // Opcao invalida
            cout << endl
                 << "Opcao invalida. Tente novamente.\n";
            break;
        }
        if (opcao != 4)
        {

            cout << endl
                 << "Pressione ENTER para voltar ao menu do carrinho.";
            cin.ignore();
            cin.get();
        }
    } while (opcao != 4);
}

void eliminarCarrinho(string** carrinho)
{

    int nProdEliminarCarrinho;
    cout << "Quantos produtos deseja eliminar? ";
    cin >> nProdEliminarCarrinho;

    if (nProdEliminarCarrinho > capacidadeCarrinho)
    {
        cout << RED 
             << "Nao existem " << nProdEliminarCarrinho << " produtos na loja." 
             << RESET;
        return;
    }
    for (int n = 0; n < nProdEliminarCarrinho; n++)
    {
        string id;
        printCarrinho(carrinho);
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
                        int qntEliminada = stoi(carrinho[i][2]);                   // quantidade que tinha sido adicionado ao carrinho
                        int qntEstoqueAtual = stoi(produto[p][2]);                 // quantidade no stock
                        produto[p][2] = to_string(qntEstoqueAtual + qntEliminada); // soma dos stock + a quantidade eliminada do carrinho
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
                cout << RED << endl
                     << "Produto eliminado. \n"
                     << RESET;
                encontrado = true;
                break;
            }
        }
        if (!encontrado)
        {
            cout << RED 
                 << "Produto nao encontrado no carrinho.\n"
                 << RESET;
        }
    }
}

void adicionarCarrinho(string** carrinho)
{
    string continuar = "sim";

    do
    {
        system("CLS");
        produtosDisponiveis();
        cout << "ID do produto ou 'SAIR' para retornar ao Menu Principal: ";
        string id;
        cin >> id;
        id = toLower(id);
        if (id == "sair")
            break;

        bool encontrado = false;
        for (int i = 0; i < totalProdutos; i++)
        {
            if (produto[i][0] == id)
            {
                encontrado = true;

                int quantidade;
                int stockAtual = stoi(produto[i][2]);

                cout << endl
                     << "Produto: " << produto[i][1] << endl;
                cout << "Quantidade disponivel: " << produto[i][2] << endl;

                do
                {
                    cout << "Digite quantidade desejada: ";
                    while (!(cin >> quantidade) || quantidade <= 0)
                    {
                        cout << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n";
                        cout << "Digite quantidade desejada: ";
                        cin.clear(); // Limpa o erro
                        cin.ignore(1000, '\n');
                    }
                    if (quantidade > stockAtual)
                    {
                        cout << "Quantidade invalida ou insuficiente no estoque! Tente novamente.\n";
                        continue;
                    }
                } while (quantidade > stockAtual);

                double precoCusto = stod(produto[i][3]);
                double precoVenda = precoCusto * 1.30;
                double iva = precoVenda * 0.23;
                double subtotal = (iva + precoVenda) * quantidade;

                if (linhacarrinho >= capacidadeCarrinho)
                {
                    cout << RED 
                         << "Carrinho cheio! Finalize a compra ou limpe o carrinho.\n"
                         << RESET;
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

                cout << GREEN 
                     << "Produto " << produto[i][0] << " adicionado ao carrinho!\n"
                     << RESET;
                break;
            }
        }
        if (!encontrado)
        {
            cout << RED 
                 << "Produto nao encontrado!\n"
                 << RESET;
        }

        cout << "Deseja adicionar outro produto? (sim/nao): ";
        cin >> continuar;

        continuar = toLower(continuar);

    } while (continuar == "sim");
}

void processarCheckout(string** carrinho)
{
    double total = 0.0;
    if (carrinho[0][0] == "")
    {
        cout << RED 
             << "O carrinho encontra-se vazio.\n"
             << RESET;
        return;
    }
    else
    {
        cout << "\nResumo da Compra:\n";
        cout << "----------------------------------------------------------------\n";
        cout << "| ID  | Nome           | Qtd | Preco Unit. |  IVA  | Subtotal   |\n";
        cout << "----------------------------------------------------------------\n";

        for (int i = 0; i < linhacarrinho; i++)
        {
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
    }

    bool gratis = sortearVendaGratis();
    double valorPago = 0.0;
    double troco = 0.0;

    if (gratis)
    {
        cout << "\nParabens! A sua compra foi gratuita!\n";
        total = 0.0;
    }
    else
    {
        cout << "\nTotal a pagar: " << fixed << setprecision(2) << total << " euros\n";

        do
        {
            cout << "Insira o Valor recebido ou escreva 0 voltar ao Menu, se desejar cancelar a compra escreva -1.\n";
            cout << "Valor recebido: ";
            cin >> valorPago;

            if (valorPago == 0)
                return;
            if (valorPago == -1)
            {
                for (int i = 0; i < linhacarrinho; i++)
                {
                    int qntCarrinho = stoi(carrinho[i][2]);

                    for (int j = 0; j < totalProdutos; j++)
                    {
                        if (produto[j][0] == carrinho[i][0])
                        {
                            int stockAtual = stoi(produto[j][2]);

                            produto[j][2] = to_string(stockAtual + qntCarrinho); // devolver a quantidade do carrinho ao stock
                            break;
                        }
                    }
                }
                limparCarrinho(carrinho);
                system("CLS");
                cout << RED 
                     << "A sua compra foi cancelada.\n"
                     << RESET;
                return;
            }

            if (valorPago < total)
            {
                cout << RED 
                     << "Valor insuficiente!\n"
                     << RESET;
            }
        } while (valorPago < total);

        troco = valorPago - total;
    }

    imprimirTalao(carrinho, total, valorPago, troco, gratis);

    numeroFatura++;
    numeroCliente++;
    // Limpar o carrinho após o checkout
    limparCarrinho(carrinho);
}

void limparCarrinho(string** carrinho)
{ // Limpar o carrinho
    for (int i = 0; i < linhacarrinho; i++)
    {

        for (int j = 0; j < 6; j++)
        {

            carrinho[i][j].clear();
        }
    }

    linhacarrinho = 0;
}

void imprimirTalao(string** carrinho, double total, double valorPago, double troco, bool gratis)
{
    system("CLS");
    cout << "\n\n==================== TALAO DE COMPRA ====================\n";
    time_t agora = time(0);
    tm tempoLocal;
    localtime_s(&tempoLocal, &agora);
    cout << "Data: " << tempoLocal.tm_mday << "/" << tempoLocal.tm_mon + 1 << "/" << tempoLocal.tm_year + 1900 << "\n";
    cout << "Fatura n: " << numeroFatura << " | Cliente n: " << numeroCliente << endl;
    cout << "---------------------------------------------------------\n";
    cout << left << setw(15) << "Produto" << setw(10) << "Qtd" << setw(15) << "Preco S/IVA" << setw(10) << "IVA" << setw(10) << "Total" << endl;
    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < linhacarrinho; i++)
    {
        cout << left << setw(15) << carrinho[i][1]
            << setw(10) << carrinho[i][2]
            << setw(15) << fixed << setprecision(2) << stod(carrinho[i][3])
            << setw(10) << fixed << setprecision(2) << stod(carrinho[i][4])
            << setw(10) << fixed << setprecision(2) << stod(carrinho[i][5]) << endl;
    }
    cout << "---------------------------------------------------------\n";

    if (gratis)
    {
        cout << GREEN 
             << "COMPRA GRATUITA!\n"
             << RESET;
    }
    else
    {
        cout << "Total: " << fixed << setprecision(2) << total << " euros\n";
        cout << "Valor pago: " << fixed << setprecision(2) << valorPago << " euros\n";
        cout << "Troco: " << fixed << setprecision(2) << troco << " euros\n";
    }

    cout << "=========================================================\n";
    cout << "Obrigado pela sua preferencia!\n";
}

void modificarPreco()
{
    double novoPrecoT;
    string id;
    string continuar = "sim";
    bool encontrado = false;

    do
    {
        produtosDisponiveis();
        cout << endl
             << "Insira o ID do produto a qual deseja modificar o preco ou 'SAIR' para retornar ao Menu Principal: ";
        cin >> id;
        id = toLower(id);

        if (id == "sair")
            break;

        for (int i = 0; i < totalProdutos; i++)
        {
            if (id == produto[i][0])
            {
                encontrado = true;
                cout << endl
                    << "Preco atual: " << produto[i][3] << endl;
                cout << endl
                    << "Insira o novo preco do produto: ";

                while (!(cin >> novoPrecoT) || novoPrecoT < 0)
                {
                    cout << "Atencao, apenas pode inserir numeros e tem de ser maior que 0.\n";
                    cout << "Preco: ";
                    cin.clear();            // para conseguir introduzir uma nova entrada || vai limpar o erro
                    cin.ignore(1000, '\n'); // 1000 significa o numero de caracteres que vao ser ignorados. O '\n' é para dizer apenas até o ENTER, ou seja, se eu colocar "abc" e der enter vai dar erro porque nao é numero e ele vai ignorar "abc".
                }

                ostringstream novoFormatado;                             // output string stream é uma variavel de uma string que me deixa formatar dados como numeros e converter para string
                novoFormatado << fixed << setprecision(2) << novoPrecoT; // vai formatar o preco para ter 2 casas decimais
                produto[i][3] = novoFormatado.str();
            }
        }
        if (!encontrado)
        {
            cout << RED 
                 << "Produto nao encontrado.\n"
                 << RESET;
            break;
        }

        cout << endl
             << "Deseja modificar mais algum preco? (sim/nao)\n";
        cin >> continuar;
        system("CLS"); // Limpa a tela
        continuar = toLower(continuar);

    } while (continuar == "sim");

    cout << "|=============| ";
    cout << "Atualizacao de precos "; // para mostrar os novos precos.
    cout << " |==============|\n";
    produtosDisponiveis();
}

void menu(string** carrinho)
{
    int opcao;

    do
    {
        system("CLS"); // Limpa a tela
        cout << endl
             << "|=============| ";
        cout << "Papelaria Note & Book";
        cout << " |==============|\n";
        cout << endl;
        cout << "[1] Produtos Disponiveis\n";
        cout << "[2] Carrinho\n";
        cout << "[3] Checkout\n";
        cout << "[4] Adicionar Produto\n";
        cout << "[5] Eliminar Produto\n";
        cout << "[6] Modificar Preco\n";
        cout << "[7] Sair\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Apenas pode inserir numeros. Por favor tente novamente.\n";
        }

        switch (opcao)
        {
        case 1:
            // Mostrar produtos disponíveis
            system("CLS"); // Limpa a tela
            produtosDisponiveis();
            break;
        case 2:
            // Comprar produto
            system("CLS"); // Limpa a tela
            mostrarCarrinho(carrinho);
            break;
        case 3:
            // carrinho
            system("CLS"); // Limpa a tela
            processarCheckout(carrinho);
            break;
        case 4:
            // Adicionar produto
            system("CLS"); // Limpa a tela
            adicionarProduto();
            break;
        case 5:
            // Eliminar produto
            system("CLS"); // Limpa a tela
            eliminarProduto();
            break;
        case 6:
            // Modificar preço do produto
            system("CLS"); // Limpa a tela
            modificarPreco();
            break;
        case 7:
            cout << RED << endl
                 << "A desligar o programa...\n"
                 << RESET;
            break;
        default:
            // Opcao invalida
            cout << endl
                 << "Opcao invalida. Tente novamente.\n";
            break;
        }
        if (opcao != 7)
        {
            cout << endl
                 << "Pressione Enter para voltar ao menu.";
            cin.ignore();
            cin.get(); // Espera o utilizador pressionar Enter
        }
    } while (opcao != 7); // repete o menu até sair do programa
}

int main()
{
    while (login() == false)
    {
        cout << RED 
             << "Tente novamente.\n"
             << RESET;
    }

    inicializarProdutos();

    string** carrinho = new string * [capacidadeCarrinho];

    for (int i = 0; i < capacidadeCarrinho; i++)
    {
        carrinho[i] = new string[6]; // 6 colunas: ID, Nome, Quantidade, Preço, IVA, Subtotal
    }
    menu(carrinho);
}
