#include "MainInterno.hpp"
#include "ValidadorCPF.hpp"
#include "Eventos.hpp"
#include "Palestrante.hpp"
#include "AreaInstituicao.hpp"
#include "Participante.hpp"
#include "Certificados.hpp"
#include "AreaAtividade.hpp"

/*
    MAIN INTERNO
    =================================================================
    Esta função (MainInterno) é o menu principal do sistema acessado 
    após a autenticação da instituição, configurando o console para 
    UTF-8. Ela exibe um menu de 7 opções (Área de Eventos, Participante, 
    Palestrante, Atividade, Instituição, Credenciamento e Certificados) 
    mais a opção '0' para sair. Em um loop do-while contínuo, a função 
    lê a escolha do usuário (Entrada_usuario) e usa uma estrutura if-else 
    if para chamar a função específica de cada módulo. Se a opção for '0', 
    o loop é interrompido (break), retornando ao menu anterior; opções 
    inválidas exibem uma mensagem de erro e o menu é recarregado.

    Att. Equipe Credentia+
    Código Revisado!
*/

int MainInterno() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Evento ev;

    int Entrada_usuario;

    do {
        std::cout << "===============================================" << std::endl;
        std::cout << "                 CREDENTIA+" << std::endl;
        std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
        std::cout << "===============================================" << std::endl;
        std::cout << "              Bem vindo(a)  " << std::endl; // Adicionar nome do usuário
        std::cout << "===============================================" << std::endl;
        std::cout << "1. Área de Eventos" << std::endl;
        std::cout << "2. Área Participante" << std::endl;
        std::cout << "3. Área Palestrante" << std::endl;
        std::cout << "4. Área Atividade" << std::endl;
        std::cout << "5. Área Instituição" << std::endl;
        std::cout << "6. Credenciamento Autônomo" << std::endl;
        std::cout << "7. Gestão de Certificados" << std::endl;
        std::cout << "0. Sair" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "               DIGITE UMA OPÇÃO                " << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;

        std::cin >> Entrada_usuario;

        system("cls");

        if (Entrada_usuario == 1) {
            MainEvento();
        }
        else if (Entrada_usuario == 2) {
            mainParticipante();
        }
        else if (Entrada_usuario == 3) {
            MainPalestrantes();
        }
        else if (Entrada_usuario == 4) {
            mainAtividade();
        }
        else if (Entrada_usuario == 5) {
            mainInstituicao();
        }
        else if (Entrada_usuario == 6) {
            ev.CredenciamentoAutonomo();
        }
        else if (Entrada_usuario == 7) {
            mainCertificados();
        }
        else if (Entrada_usuario == 0) {
            break;
        }
        else {
            std::cout << std::endl << "Opção Inválida! Tente Novamente" << std::endl;
            system("PAUSE");
            system("cls");
        }

    } while (true);

    return 0;
}
