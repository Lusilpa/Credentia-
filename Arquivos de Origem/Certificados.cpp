#include "Certificados.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/*
      Responsável: Gabrielle Oliveira
      sistema: Area de Eventos
      github: bielleoliveira 
*/

/*
   ========================================================
   Gestão de Certificados
   ========================================================

   Este código define o módulo de "Certificados", controlado 
   por um menu principal (mainCertificados) que opera em um 
   loop do-while. A função principal, criarCertificado, é 
   responsável por gerar um arquivo .txt individual para cada 
   certificado, com um nome de arquivo único 
   (ex: Ana_certificado_palestrante.txt). O texto dentro do 
   arquivo é personalizado com base no tipo de certificado 
   (palestrante, minicurso, ou participação). O mainCertificados 
   (opção 1) faz duas coisas: chama criarCertificado para salvar 
   o arquivo no disco e também armazena o objeto Certificado em 
   um vetor global na memória. As funções de busca (buscarPorNome 
   e buscarPorCpf) operam apenas neste vetor global, iterando sobre 
   ele para encontrar correspondências. O programa não lê os arquivos 
   .txt que cria; ele confia inteiramente no vetor em memória para as buscas.

   att. Gabrielle
   Código Revisado
*/

std::vector<Certificado> certificados;

void criarCertificado(const Certificado& cert) {
    std::string nomeArquivo = cert.nome + "_certificado_" + cert.tipo + ".txt";
    std::ofstream arquivo(nomeArquivo);

    if (!arquivo) {
        std::cout << "Erro ao criar o arquivo de certificado." << std::endl;
        return;
    }

    arquivo << "--- Certificado do Evento ---\n";
    arquivo << "Nome: " << cert.nome << "\n";
    arquivo << "CPF: " << cert.cpf << "\n\n";

    if (cert.tipo == "palestrante") {
        arquivo << "Este certificado reconhece que " << cert.nome << ", portador do CPF " << cert.cpf << ", foi palestrante no evento.\n";
    }
    else if (cert.tipo == "minicurso") {
        arquivo << "Este certificado reconhece que " << cert.nome << ", portador do CPF " << cert.cpf << ", participou como ministrante de minicurso no evento.\n";
    }
    else if (cert.tipo == "participacao") {
        arquivo << "Este certificado reconhece que " << cert.nome << ", portador do CPF " << cert.cpf << ", participou do evento.\n";
    }
    else {
        arquivo << "Tipo de certificado inválido.\n";
        arquivo.close();
        std::cout << "Tipo de certificado inválido." << std::endl;
        return;
    }

    arquivo << "Horas complementares atribuídas: " << cert.horas << " horas.\n";
    arquivo << "Agradecemos sua participação!\n";
    arquivo << "-----------------------------\n";

    arquivo.close();
    std::cout << "Certificado de " << cert.tipo << " criado para " << cert.nome << "." << std::endl;
}

void buscarPorNome(const std::string& nome) {
    bool encontrado = false;
    for (const auto& cert : certificados) {
        if (cert.nome == nome) {
            std::cout << "\nCertificado encontrado:\n";
            std::cout << "Nome: " << cert.nome << "\nCPF: " << cert.cpf << "\nTipo: " << cert.tipo << "\nHoras: " << cert.horas << "\n";
            encontrado = true;
            system("PAUSE");
            system("cls");
        }
    }
    if (!encontrado) {
        std::cout << "Nenhum certificado encontrado para o nome: " << nome << std::endl;
        system("PAUSE");
        system("cls");
    }
}

void buscarPorCpf(const std::string& cpf) {
    bool encontrado = false;
    for (const auto& cert : certificados) {
        if (cert.cpf == cpf) {
            std::cout << "\nCertificado encontrado:\n";
            std::cout << "Nome: " << cert.nome << "\nCPF: " << cert.cpf << "\nTipo: " << cert.tipo << "\nHoras: " << cert.horas << "\n";
            encontrado = true;
            system("PAUSE");
            system("cls");
        }
    }
    if (!encontrado) {
        std::cout << "Nenhum certificado encontrado para o CPF: " << cpf << std::endl;
        system("PAUSE");
        system("cls");
    }
}

int mainCertificados() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int opcao;
    do {
        std::cout << "\n============ CERTIFICADOS ===============\n";
        std::cout << "1 - Criar certificado\n";
        std::cout << "2 - Buscar certificado por nome\n";
        std::cout << "3 - Buscar certificado por CPF\n";
        std::cout << "0 - Sair\n";
        std::cout << "========================================";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;
        std::cin.ignore(); // limpar buffer do cin
        system("cls");

        if (opcao == 1) {
            Certificado cert;
            std::cout << "Digite o nome completo: ";
            getline(std::cin, cert.nome);
            std::cout << "Digite o CPF: ";
            getline(std::cin, cert.cpf);
            std::cout << "Digite o tipo de certificado (palestrante, minicurso, participacao): ";
            getline(std::cin, cert.tipo);
            std::cout << "Digite o número de horas complementares: ";
            std::cin >> cert.horas;
            std::cin.ignore();
            system("cls");

            certificados.push_back(cert);
            criarCertificado(cert);
        }
        else if (opcao == 2) {
            std::string nomeBusca;
            std::cout << "Digite o nome para busca: ";
            getline(std::cin, nomeBusca);
            
            system("cls");

            buscarPorNome(nomeBusca);
        }
        else if (opcao == 3) {
            std::string cpfBusca;
            std::cout << "Digite o CPF para busca: ";
            getline(std::cin, cpfBusca);
            
            system("cls");

            buscarPorCpf(cpfBusca);
        }
        else if (opcao == 0) {
            std::cout << "SAINDO DA ÁREA DE CERTIFICADOS\n";
        }
        else {
            std::cout << "Opção inválida.\n";
        }
    } while (opcao != 0);

    return 0;
}