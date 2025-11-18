#include "MainInterno.hpp"
#include "AreaInstituicao.hpp"
#include "Eventos.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

/*
     -----------------------------
     ****Sistemas Universal de Arquivos****
     -----------------------------
     -> Responsáveis:
     Pedro Macedo
     Jennifer Kalyne

     -> Github:
     ph-macedo
     Jennifer-limaa
*/

/*
      PROJETO CREDENTIA+ -  MAIN PRINCIPAL

      Esta função main configura o console para
      UTF-8 e exibe o menu principal do "CREDENTIA+"
      em um loop contínuo. Ela captura a escolha do
      usuário e o direciona para as funções de autenticação
      (1), cadastro (2) ou encerra o programa (0).

      Att. Equipe Credentia+
      Código Revisado!
*/

void AutenticacaoInstituicao();

int main() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int entrada_usuario_main;
    Evento ev;

    //Luan: Tela inicial

    do {
        cout << "===============================================" << endl;
        cout << "                 CREDENTIA+" << endl;
        cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
        cout << "===============================================" << endl;
        cout << "                MENU PRINCIPAL                 " << endl;
        cout << "===============================================" << endl;
        cout << "1. Acessar Área Institucional" << endl; // CORREÇÃO: "Instuticional" -> "Institucional"
        cout << "2. Cadastrar Nova Instituição" << endl;
        cout << "3. Credenciamento de Participante" << endl; // CORREÇÃO: Adicionada opção 3 que estava no código
        cout << "0. Sair" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "               DIGITE UMA OPÇÃO                " << endl;
        cout << "-----------------------------------------------" << endl;

        // CORREÇÃO: Validação de entrada
        if (!(cin >> entrada_usuario_main)) {
            cin.clear();
            cin.ignore(1000, '\n');
            system("cls");
            cout << "Opção inválida! Digite um número." << endl;
            continue;
        }

        system("cls"); // Luan: limpar tela do console

        switch (entrada_usuario_main) { // CORREÇÃO: Usando switch para melhor organização
        case 1:
            // Luan: Acessar área institucional com id da instituição
            AutenticacaoInstituicao();
            break;
        case 2:
            // Luan: Código para cadastrar nova instituição
            CadastrarInstituicao();
            break;
        case 3:
            // Luan: Credenciamento dos participantes
            ev.CredenciamentoAutonomo();
            break;
        case 0:
            system("cls");
            cout << "===============================================" << endl;
            cout << "              CREDENTIA+" << endl;
            cout << "OBRIGADO POR UTILIZAR O NOSSO SISTEMA" << endl;
            cout << "===============================================" << endl;
            return 0; // CORREÇÃO: Usando return em vez de exit()
        default:
            // Luan: Caso a entrada do usuário seja inválida
            cout << "Opção Inválida!" << endl;
            break;
        }

    } while (true);

    return 0;
}

/*
     Autenticação de Entrada

     Esta função implementa um loop de login que solicita
     um ID e senha institucionais, permitindo ao usuário digitar
     "0" para retornar ao menu anterior. Ela valida as credenciais
     chamando buscarInstituicao e comparando a senha; se o acesso
     for concedido, ela exibe os dados da instituição e chama o
     MainInterno, caso contrário, exibe uma mensagem de erro específica
     (ID não encontrado ou senha incorreta) e permite uma nova tentativa.

     Att. Equipe Credentia+
     Código Revisado!
*/

void AutenticacaoInstituicao() {
    int id_busca;
    string senha;

    do {
        cout << "===============================================" << endl;
        cout << "             ACESSO INSTITUCIONAL            " << endl;
        cout << " DIGITE 0 PARA VOLTAR AO MENU ANTERIOR" << endl;
        cout << "===============================================" << endl;
        cout << "DIGITE O ID DA SUA INSTITUIÇÃO:" << endl;

        // CORREÇÃO: Validação de entrada mais robusta
        if (!(cin >> id_busca)) {
            cin.clear(); // Limpa o estado de erro
            // Limpa o buffer de entrada inteiro
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "ID inválido! Digite um número." << endl;
            system("pause"); // Pausa para o usuário ver o erro
            system("cls");
            continue;
        }

        // CORREÇÃO: Limpa o '\n' deixado pelo 'cin >>'
        // Isso é crucial antes de um 'getline'
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (id_busca == 0) {
            system("cls");
            cout << "Retornando ao menu principal..." << endl;
            break;
        }

        // Solicitar senha
        cout << "DIGITE A SENHA DA INSTITUIÇÃO:" << endl;
        getline(cin, senha);

        system("cls");

        if (senha.empty()) {
            cout << "===============================================" << endl;
            cout << "             ERRO DE AUTENTICAÇÃO            " << endl;
            cout << "===============================================" << endl;
            cout << "Senha não pode estar vazia." << endl;
            cout << "===============================================" << endl;
            system("pause");
            system("cls");
            continue;
        }

        // Busca a instituição
        Instituicao inst = buscarInstituicao(id_busca);

        // Verifica se a instituição foi encontrada E se a senha está correta
        if (inst.id_instituicao != -1 && inst.senha_institucional == senha) {
            cout << "===============================================" << endl;
            cout << "                  CREDENTIA+" << endl;
            cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
            cout << "===============================================" << endl;
            cout << "        ACESSO CONCEDIDO - BEM-VINDO(A)!       " << endl;
            cout << "===============================================" << endl;

            exibirInstituicao(inst); // A função de exibir ainda é útil

            cout << "\nPressione Enter para acessar o menu institucional...";

            system("pause");

            system("cls");
            MainInterno();
            break; // Sai do loop de autenticação

        }
        else {
            cout << "===============================================" << endl;
            cout << "             FALHA NA AUTENTICAÇÃO            " << endl;
            cout << "===============================================" << endl;

            if (inst.id_instituicao == -1) {
                cout << "Instituição com ID " << id_busca << " não encontrada." << endl;
            }
            else {
                cout << "Senha incorreta para a instituição." << endl;
            }

            // A memória de 'inst' (mesmo se falhar) será liberada 
            // automaticamente pelo destrutor no final do loop.
            // Nenhuma chamada manual é necessária.

            cout << "\nVerifique suas credenciais e tente novamente." << endl;
            cout << "===============================================" << endl;
            system("pause");
            system("cls");
        }

    } while (true);

    // Quando o loop quebra (pelo 'break' ou 'return' da main),
    // 'inst' sai de escopo, e seu destrutor ~Instituicao() é chamado,
    // o qual chama liberarTelefones(inst) uma única vez.
}