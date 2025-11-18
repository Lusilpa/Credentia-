#include "Palestrante.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

/*
	 PARTE 1: IMPLEMENTAÇÃO DA CLASSE PALESTRANTE
     =================================================================
     Este código C++ define quatro métodos para a classe Palestrante. 
     Os dois primeiros são construtores: um construtor padrão, que inicializa 
     o objeto com valores vazios (ID 0, strings vazias), e um construtor 
     parametrizado, que recebe e atribui todos os dados (ID, nome, título, 
     atividade) durante a criação. O método exibir() é responsável por 
     imprimir no console todos os dados do palestrante de forma formatada, 
     incluindo um cabeçalho do sistema "CREDENTIA+". Por fim, o método toFileString() 
     converte os dados do objeto em uma única string formatada, pronta para ser salva em um arquivo.

	 att. Equipe Credentia+
	 Código Revisado!
*/

Palestrante::Palestrante()
    : id_palestrante(0), nome_completo(""), titulo_academico(""), atividade("") {
}

Palestrante::Palestrante(int id, const string& nome, const string& titulo, const string& atv)
    : id_palestrante(id), nome_completo(nome), titulo_academico(titulo), atividade(atv) {
}

void Palestrante::exibir() const {
    cout << "===============================================" << endl;
    cout << "                 CREDENTIA+" << endl;
    cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
    cout << "===============================================" << endl;
    cout << "          DADOS DO PALESTRANTE           " << endl;
    cout << "===============================================" << endl;
    cout << "ID: " << id_palestrante << endl;
    cout << "Nome: " << nome_completo << endl;
    cout << "Título Acadêmico: " << titulo_academico << endl;
    cout << "Atividade: " << atividade << endl;
    cout << "===============================================" << endl;
}

string Palestrante::toFileString() const {
    return "ID:" + to_string(id_palestrante) + "\n" +
        "NOME:" + nome_completo + "\n" +
        "TITULO:" + titulo_academico + "\n" +
        "ATIVIDADE:" + atividade + "\n";
}

/*
	 PARTE 2: FUNÇÃO AUXILIAR DE TRIM
     =================================================================
     Esta função trim remove espaços em branco do início e do fim 
     de uma string. Ela utiliza os métodos find_first_not_of e 
     find_last_not_of para localizar os índices dos primeiros e 
     últimos caracteres não brancos, retornando a substring 
     correspondente. Se a string for composta apenas por espaços, 
	 retorna uma string vazia.

	 att. Equipe Credentia+
	 Código Revisado!
*/

string trim(const string& str) {
    const string WHITESPACE = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(WHITESPACE);
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(WHITESPACE);
    return str.substr(start, (end - start + 1));
}

/*
	 PARTE 3: GERENCIAMENTO DE IDs GLOBAIS
     =================================================================
     Estas funções gerenciam o ID global para palestrantes, 
     armazenado em um arquivo de texto. A função getGlobalID_palestrante 
     lê o ID atual do arquivo e o retorna, garantindo que seja 
     pelo menos 1. A função updGlobalID_palestrante incrementa 
     esse ID, atualiza o arquivo com o novo valor e retorna 
	 o ID antigo para uso na criação de um novo palestrante.

	 att. Sistema Unificado de Arquivos
	 Código Revisado!
*/
int getGlobalID_palestrante(string nomeArq) {
    ifstream arq;
    int globalId = 1;

    arq.open(nomeArq);
    if (arq.is_open()) {
        arq >> globalId;
        arq.close();
        if (globalId < 1) globalId = 1;
    }

    return globalId;
}

int updGlobalID_palestrante(string nomeArq) {
    int globalId = getGlobalID_palestrante(nomeArq);
    int proximoId = globalId + 1;

    ofstream arq(nomeArq);
    if (arq.is_open()) {
        arq << proximoId;
        arq.close();
    }

    return globalId;
}

/*
	 PARTE 4: FUNÇÕES PRINCIPAIS DO CRUD
     ====================================================================
     Este código C++ define um sistema CRUD (Criar, Ler, Atualizar, Deletar) 
     completo para Palestrantes, gerenciando os dados diretamente no arquivo 
     "palestrantes.txt". A função CadastrarPalestrante coleta dados do usuário 
     (nome, título, atividade), obtém um ID global (updGlobalID_palestrante) 
     e anexa o novo registro ao arquivo.

     As demais operações (Listar, Buscar, Remover) são "wrappers" que delegam 
     a lógica para funções prefixadas com LB_ (ex: LB_listarPalestrantes). As 
     funções LB_ implementam a leitura do arquivo: LB_listar exibe todos, 
     LB_buscarPorID procura por ID exato, e LB_buscarPorNome faz uma busca 
     case-insensitive por substring. Por fim, LB_removerPalestrante utiliza 
     a técnica de arquivo temporário para reescrever o "palestrantes.txt" 
     sem o registro excluído.

	 att. Equipe Credentia+
	 Código Revisado!
*/

void CadastrarPalestrante() {
    cout << "===============================================" << endl;
    cout << "                 CREDENTIA+" << endl;
    cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
    cout << "===============================================" << endl;
    cout << "         CADASTRAR NOVO PALESTRANTE         " << endl;
    cout << "===============================================" << endl;

    string nome, titulo, atividade;

    cout << "Nome completo: ";
    getline(cin, nome);

    cout << "Título acadêmico: ";
    getline(cin, titulo);

    cout << "Atividade: ";
    getline(cin, atividade);

    system("cls");

    int novoId = updGlobalID_palestrante("global_id_palestrantes.txt");

    ofstream arquivo("palestrantes.txt", ios::app);
    if (arquivo.is_open()) {
        arquivo << "ID:" << novoId << "\n";
        arquivo << "NOME:" << nome << "\n";
        arquivo << "TITULO:" << titulo << "\n";
        arquivo << "ATIVIDADE:" << atividade << "\n";
        arquivo << "---\n";
        arquivo.close();
    }

    cout << "===============================================" << endl;
    cout << "                 CREDENTIA+" << endl;
    cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
    cout << "===============================================" << endl;
    cout << "        PALESTRANTE SALVO COM SUCESSO        " << endl;
    cout << "===============================================" << endl;
    cout << "ID gerado: " << novoId << endl;
    cout << "Nome: " << nome << endl;
    cout << "Título: " << titulo << endl;
    cout << "Atividade: " << atividade << endl;
    cout << "===============================================" << endl;

    system("pause");
    system("cls");
}

void ListarPalestrantes() {
    LB_listarPalestrantes();
}

void BuscarPalestrantePorID(int id) {
    LB_buscarPalestrantePorID(id);
}

void BuscarPalestrantePorNome(const string& nome) {
    LB_buscarPalestrantePorNome(nome);
}

bool RemoverPalestrante(int id) {
    return LB_removerPalestrante(id);
}

void LB_listarPalestrantes() {
    ifstream arquivo("palestrantes.txt");
    if (!arquivo) {
        cout << "Nenhum palestrante cadastrado." << endl;
        return;
    }

    cout << "===============================================" << endl;
    cout << "                 CREDENTIA+" << endl;
    cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
    cout << "===============================================" << endl;
    cout << "       LISTAR TODOS OS PALESTRANTES        " << endl;
    cout << "===============================================" << endl;

    string linha;
    int contador = 0;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            contador++;
            cout << "-----------------------------------------------" << endl;
        }

        if (linha.find("ID:") == 0) {
            cout << "ID: " << trim(linha.substr(3)) << endl;
        }
        else if (linha.find("NOME:") == 0) {
            cout << "Nome: " << trim(linha.substr(5)) << endl;
        }
        else if (linha.find("TITULO:") == 0) {
            cout << "Título: " << trim(linha.substr(7)) << endl;
        }
        else if (linha.find("ATIVIDADE:") == 0) {
            cout << "Atividade: " << trim(linha.substr(10)) << endl;
        }
    }

    if (contador == 0) {
        cout << "Nenhum palestrante encontrado." << endl;
    }
    else {
        cout << "===============================================" << endl;
        cout << "TOTAL: " << contador << " PALESTRANTE(S) ENCONTRADO(S)" << endl;
        cout << "===============================================" << endl;
    }

    arquivo.close();
}

void LB_buscarPalestrantePorID(int id) {
    ifstream arquivo("palestrantes.txt");
    if (!arquivo) {
        cout << "Arquivo de palestrantes não encontrado!" << endl;
        return;
    }

    string linha;
    bool encontrou = false;
    bool dentroDoPalestrante = false;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            int palestranteAtualId = -1;
            try {
                palestranteAtualId = stoi(trim(linha.substr(3)));
            }
            catch (...) {}

            if (palestranteAtualId == id) {
                encontrou = true;
                dentroDoPalestrante = true;
                cout << "===============================================" << endl;
                cout << "                 CREDENTIA+" << endl;
                cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
                cout << "===============================================" << endl;
                cout << "          PALESTRANTE ENCONTRADO           " << endl;
                cout << "===============================================" << endl;
                cout << "ID: " << palestranteAtualId << endl;
            }
            else {
                dentroDoPalestrante = false;
            }
        }
        else if (dentroDoPalestrante) {
            if (linha.find("NOME:") == 0) {
                cout << "Nome: " << trim(linha.substr(5)) << endl;
            }
            else if (linha.find("TITULO:") == 0) {
                cout << "Título: " << trim(linha.substr(7)) << endl;
            }
            else if (linha.find("ATIVIDADE:") == 0) {
                cout << "Atividade: " << trim(linha.substr(10)) << endl;
            }
            else if (linha == "---") {
                cout << "===============================================" << endl;
                if (encontrou) break;
            }
        }
    }

    if (!encontrou) {
        cout << "Palestrante com ID " << id << " não encontrado." << endl;
    }

    arquivo.close();
}

void LB_buscarPalestrantePorNome(string nomeProcurado) {
    ifstream arquivo("palestrantes.txt");
    if (!arquivo) {
        cout << "Arquivo de palestrantes não encontrado!" << endl;
        return;
    }

    string linha;
    bool encontrou = false;
    int contador = 0;
    string idAtual, nomeAtual, tituloAtual, atividadeAtual;

    string nomeProcuradoLower = trim(nomeProcurado);
    transform(nomeProcuradoLower.begin(), nomeProcuradoLower.end(), nomeProcuradoLower.begin(), ::tolower);

    cout << "===============================================" << endl;
    cout << "                 CREDENTIA+" << endl;
    cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
    cout << "===============================================" << endl;
    cout << "        RESULTADOS DA BUSCA POR NOME         " << endl;
    cout << "===============================================" << endl;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            idAtual = trim(linha.substr(3));
            nomeAtual = ""; tituloAtual = ""; atividadeAtual = "";
        }
        else if (linha.find("NOME:") == 0) {
            nomeAtual = trim(linha.substr(5));
        }
        else if (linha.find("TITULO:") == 0) {
            tituloAtual = trim(linha.substr(7));
        }
        else if (linha.find("ATIVIDADE:") == 0) {
            atividadeAtual = trim(linha.substr(10));
        }
        else if (linha == "---") {
            if (!nomeAtual.empty()) {
                string nomeAtualLower = nomeAtual;
                transform(nomeAtualLower.begin(), nomeAtualLower.end(), nomeAtualLower.begin(), ::tolower);

                if (nomeAtualLower.find(nomeProcuradoLower) != string::npos) {
                    encontrou = true;
                    contador++;
                    cout << "-----------------------------------------------" << endl;
                    cout << "ID: " << idAtual << endl;
                    cout << "Nome: " << nomeAtual << endl;
                    cout << "Título: " << tituloAtual << endl;
                    cout << "Atividade: " << atividadeAtual << endl;
                }
            }
        }
    }

    if (!encontrou) {
        cout << "Nenhum palestrante encontrado com o nome: " << nomeProcurado << endl;
    }
    else {
        cout << "===============================================" << endl;
        cout << "TOTAL: " << contador << " PALESTRANTE(S) ENCONTRADO(S)" << endl;
        cout << "===============================================" << endl;
    }

    arquivo.close();
}

bool LB_removerPalestrante(int id) {
    ifstream arquivoEntrada("palestrantes.txt");
    ofstream arquivoSaida("temp.txt");
    string linha;
    bool encontrou = false;
    bool pularBloco = false;

    if (!arquivoEntrada.is_open()) {
        cout << "Arquivo de palestrantes não encontrado!" << endl;
        return false;
    }

    if (!arquivoSaida.is_open()) {
        cout << "Erro ao criar arquivo temporário!" << endl;
        return false;
    }

    while (getline(arquivoEntrada, linha)) {
        if (linha.find("ID:") == 0) {
            pularBloco = false;
            int currentId = -1;
            try {
                currentId = stoi(trim(linha.substr(3)));
            }
            catch (...) {}

            if (currentId == id) {
                encontrou = true;
                pularBloco = true;
            }
        }

        if (linha == "---") {
            if (pularBloco) {
                pularBloco = false;
                continue;
            }
        }

        if (!pularBloco) {
            if (!trim(linha).empty()) {
                arquivoSaida << linha << "\n";
            }
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    if (encontrou) {
        remove("palestrantes.txt");
        rename("temp.txt", "palestrantes.txt");
        cout << "Palestrante removido com sucesso!" << endl;
    }
    else {
        remove("temp.txt");
        cout << "Palestrante não encontrado!" << endl;
    }

    return encontrou;
}

int getInteiroValido(const string& prompt, const string& errorMsg) {
    int valor;

    cout << prompt;

    while (!(cin >> valor)) {
        cout << errorMsg;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return valor;
}

/*
	  PARTE 5: MENU PRINCIPAL DE PALESTRANTES
      ========================================================
      Este código C++ define a função MainPalestrantes(), que serve 
      como a interface principal do menu para o módulo de palestrantes. 
      A função exibe um menu de console com as opções de CRUD: Cadastrar (1), 
      Listar (2), Buscar por ID (3), Buscar por Nome (4) e Remover (5). Ela 
      opera dentro de um loop do-while que se repete até que o usuário digite 
      '0' para retornar. Um switch direciona a escolha do usuário para a função 
      apropriada (ex: CadastrarPalestrante()). O código também inclui validação 
      de entrada e limpa a tela após cada ação.

	  Att. Igor Kramer
	  Código Revisado!
*/

int MainPalestrantes() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int opcao;

    system("cls");

    do {
        cout << "===============================================" << endl;
        cout << "                 CREDENTIA+" << endl;
        cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
        cout << "===============================================" << endl;
        cout << "             ÁREA DE PALESTRANTES            " << endl;
        cout << "===============================================" << endl;
        cout << "1. CADASTRAR PALESTRANTE" << endl;
        cout << "2. LISTAR PALESTRANTES" << endl;
        cout << "3. BUSCAR PALESTRANTE POR ID" << endl;
        cout << "4. BUSCAR PALESTRANTE POR NOME" << endl;
        cout << "5. REMOVER PALESTRANTE" << endl;
        cout << "0. VOLTAR AO MENU PRINCIPAL" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "               DIGITE UMA OPÇÃO                " << endl;
        cout << "-----------------------------------------------" << endl;

        while (!(cin >> opcao)) {
            cout << "Opção inválida! Digite um número: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");

        switch (opcao) {
        case 1:
            CadastrarPalestrante();
            break;
        case 2:
            ListarPalestrantes();
            system("pause");
            system("cls");
            break;
        case 3: {
            cout << "===============================================" << endl;
            cout << "                 CREDENTIA+" << endl;
            cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
            cout << "===============================================" << endl;
            cout << "         BUSCAR PALESTRANTE POR ID         " << endl;
            cout << "===============================================" << endl;
            cout << "-----------------------------------------------" << endl;
            cout << "                 DIGITE O ID                   " << endl;
            cout << "-----------------------------------------------" << endl;

            int id_busca = getInteiroValido("", "ID inválido! Digite um número: ");

            system("cls");
            BuscarPalestrantePorID(id_busca);
            system("pause");
            system("cls");
            break;
        }
        case 4: {
            string nome_busca;
            cout << "===============================================" << endl;
            cout << "                 CREDENTIA+" << endl;
            cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
            cout << "===============================================" << endl;
            cout << "        BUSCAR PALESTRANTE POR NOME        " << endl;
            cout << "===============================================" << endl;
            cout << "-----------------------------------------------" << endl;
            cout << "                DIGITE O NOME                  " << endl;
            cout << "-----------------------------------------------" << endl;

            getline(cin, nome_busca);

            system("cls");
            BuscarPalestrantePorNome(nome_busca);
            system("pause");
            system("cls");
            break;
        }
        case 5: {
            cout << "===============================================" << endl;
            cout << "                 CREDENTIA+" << endl;
            cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
            cout << "===============================================" << endl;
            cout << "        REMOVER PALESTRANTE POR ID         " << endl;
            cout << "===============================================" << endl;
            cout << "-----------------------------------------------" << endl;
            cout << "                 DIGITE O ID                   " << endl;
            cout << "-----------------------------------------------" << endl;

            int id_remover = getInteiroValido("", "ID inválido! Digite um número: ");

            system("cls");
            RemoverPalestrante(id_remover);

            system("pause");
            system("cls");
            break;
        }
        case 0:
            cout << "Retornando ao menu principal..." << endl;
            break;
        default:
            cout << "Opção inválida! Tente novamente." << endl;
            system("pause");
            system("cls");
            break;
        }

    } while (opcao != 0);

    return 0;
}