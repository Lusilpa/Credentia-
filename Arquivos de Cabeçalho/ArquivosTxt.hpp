#pragma once

#include <iostream>        // Jennifer: Biblioteca padrão para entrada e saída de dados
#include <fstream>         // Jennifer: Biblioteca para trabalhar com arquivos (leitura e escrita)
#include <string>          // Jennifer: Biblioteca para manipular strings (texto)
#include <sstream>         // Jennifer: Biblioteca usada para quebrar (dividir) linhas de texto
#include <vector>          // Jennifer: Biblioteca para usar vetores (listas dinâmicas)
#include <Windows.h>
#undef min
#undef max
#include <cstdlib>

/* CLASSE BASE REGISTRO
   ------------------------------------------------------------
   Jennifer: Essa classe é genérica e serve de base para todas
   as entidades do sistema (Participante, Evento, etc).
   Ela tem funções que abrem o arquivo, listam e buscam dados. */
class LB_Registro {
protected:
    std::string nomeArquivo;  // Jennifer: Guarda o nome do arquivo associado a cada entidade

public:
    LB_Registro(std::string arquivo) { nomeArquivo = arquivo; }  // Jennifer: Define o nome do arquivo no construtor

    /* FUNÇÃO: listar()
       ------------------------------------------------------------
       Jennifer: Lê todo o conteúdo do arquivo e mostra na tela.
       Cada linha do arquivo representa um registro completo. */
    void listar() {
        std::ifstream arq(nomeArquivo.c_str());  // Jennifer: Abre o arquivo para leitura
        if (!arq) {                         // Jennifer: Verifica se o arquivo abriu corretamente
            std::cout << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
            return;
        }

        std::string linha;
        std::cout << "\n=== Listagem de " << nomeArquivo << " ===\n";
        while (getline(arq, linha)) {       // Jennifer: Lê cada linha até o final
            std::cout << linha << std::endl;          // Jennifer: Mostra o conteúdo da linha
        }
        arq.close();                        // Jennifer: Fecha o arquivo após terminar
    }

    /* FUNÇÃO: buscar(campo, valorProcurado)
       ------------------------------------------------------------
       Jennifer: Procura um valor específico (ex: nome, ID, etc)
       dentro do arquivo, linha por linha. */
    void buscar(std::string campo, std::string valorProcurado) {
        std::ifstream arq(nomeArquivo.c_str());  // Jennifer: Abre o arquivo para leitura
        if (!arq) {
            std::cout << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
            return;
        }

        std::string linha;
        bool encontrou = false;  // Jennifer: Variável de controle, verifica se achou o registro

        // Jennifer: Leitura de cada linha do arquivo
        while (getline(arq, linha)) {
            std::stringstream ss(linha);  // Jennifer: Transforma a linha em um stream de dados (pra separar os campos)
            std::vector<std::string> campos;   // Jennifer: Vetor que vai armazenar todas as palavras da linha
            std::string temp;

            // Jennifer: Quebra a linha em palavras separadas por espaço e adiciona no vetor
            while (ss >> temp) {
                campos.push_back(temp);
            }

            // Jennifer: Agora, dependendo de quantos campos tiver, pegamos os principais:
            // Exemplo: [ID] [Nome completo] [Ocupacao] [Idade]
            // Mas o nome pode ter mais de uma palavra
            if (campos.size() >= 4) {  // Jennifer: Garante que tem dados suficientes
                std::string id = campos[0];
                std::string idade = campos.back(); // Jennifer: Último elemento (idade)
                std::string ocupacao = campos[campos.size() - 2]; // Jennifer: Penúltimo elemento (ocupação)

                // Jennifer: Monta o nome com as palavras que estão entre ID e Ocupacao
                std::string nome = "";
                for (size_t i = 1; i < campos.size() - 2; i++) {
                    nome += campos[i];
                    if (i < campos.size() - 3) nome += " "; // Jennifer: Adiciona espaço entre nomes
                }

                // Jennifer: Verifica se o campo e o valor batem
                if ((campo == "ID" && id == valorProcurado) ||
                    (campo == "Nome" && nome == valorProcurado) ||
                    (campo == "Ocupacao" && ocupacao == valorProcurado) ||
                    (campo == "Idade" && idade == valorProcurado)) {
                    std::cout << "\n--- Registro encontrado ---\n";
                    std::cout << "ID: " << id << "\n";
                    std::cout << "Nome: " << nome << "\n";
                    std::cout << "Ocupacao: " << ocupacao << "\n";
                    std::cout << "Idade: " << idade << "\n";
                    encontrou = true;
                }
            }
        }

        if (!encontrou)
            std::cout << "Nenhum registro encontrado com " << campo << ": " << valorProcurado << std::endl;

        arq.close();  // Jennifer: Fecha o arquivo no final
    }
};

/*  CLASSES DERIVADAS (ESPECÍFICAS)
   ------------------------------------------------------------
   Jennifer: Cada classe representa uma entidade específica
   do sistema, herdando as funções de "Registro". */

class LB_Participante : public LB_Registro {
public:
    LB_Participante() : LB_Registro("") {}  // Jennifer: Define o arquivo usado
};

class LB_Palestrante : public LB_Registro {
public:
    LB_Palestrante() : LB_Registro("") {}
};

class LB_Evento : public LB_Registro {
public:
    LB_Evento() : LB_Registro("") {}
};

class LB_Atividade : public LB_Registro {
public:
    LB_Atividade() : LB_Registro("") {}
};

class LB_Instituicao : public LB_Registro {
public:
    LB_Instituicao() : LB_Registro("") {}
};

class LB_Certificado : public LB_Registro {
public:
    LB_Certificado() : LB_Registro("") {}
};

/* FUNÇÕES DE INTERFACE
   ------------------------------------------------------------
   Jennifer: Essas funções são as que vai chamar
   diretamente no código principal do sistema. */

   // PARTICIPANTES
void LB_listarParticipantes() {
    LB_Participante p;
    p.listar();
}

void LB_buscarParticipantePorID(std::string id) {
    LB_Participante p;
    p.buscar("ID", id);
}

void LB_buscarParticipantePorNome(std::string nome) {
    LB_Participante p;
    p.buscar("Nome", nome);
}

// PALESTRANTES
void LB_listarPalestrantes() {
    LB_Palestrante p;
    p.listar();
}

void LB_buscarPalestrantePorNome(std::string nome) {
    LB_Palestrante p;
    p.buscar("Nome", nome);
}

// EVENTOS
void LB_listarEventos() {
    LB_Evento e;
    e.listar();
}

void LB_buscarEventoPorNome(std::string nome) {
    LB_Evento e;
    e.buscar("Nome", nome);
}

// ATIVIDADES
void LB_listarAtividades() {
    LB_Atividade a;
    a.listar();
}

void LB_buscarAtividadePorNome(std::string nome) {
    LB_Atividade a;
    a.buscar("Nome", nome);
}

// INSTITUIÇÕES
void LB_listarInstituicoes() {
    LB_Instituicao i;
    i.listar();
}

void LB_buscarInstituicaoPorNome(std::string nome) {
    LB_Instituicao i;
    i.buscar("Nome", nome);
}

// CERTIFICADOS
void LB_listarCertificados() {
    LB_Certificado c;
    c.listar();
}

void LB_buscarCertificadoPorID(std::string id) {
    LB_Certificado c;
    c.buscar("ID", id);
}