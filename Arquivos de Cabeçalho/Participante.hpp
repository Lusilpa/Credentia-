#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>
#include <Windows.h>
#undef min
#undef max
#include <cstdlib>

class Participante {
private:
    int id_participante;
    std::string cpf;
    std::string nome_completo;
    std::string email;

    // Arrays dinâmicos - mantendo alocação manual
    std::string* telefones;
    std::string* cursos_palestras;
    int* ids_instituicao_origem;

    int quantidade_telefones;
    int quantidade_cursos;
    int quantidade_instituicoes;

    int capacidade_telefones;
    int capacidade_cursos;
    int capacidade_instituicoes;

    // Métodos privados de gerenciamento de memória
    void realocarTelefones();
    void realocarCursos();
    void realocarInstituicoes();
    void liberarMemoria();
    void copiarDados(const Participante& outro);

public:

    static std::string trim(const std::string& str) {
        const std::string WHITESPACE = " \t\n\r\f\v";
        size_t start = str.find_first_not_of(WHITESPACE);
        if (start == std::string::npos) return "";
        size_t end = str.find_last_not_of(WHITESPACE);
        return str.substr(start, (end - start + 1));
    }

    // Construtores e destrutores
    Participante();
    ~Participante();

    // Regra dos Três
    Participante(const Participante& outro);
    Participante& operator=(const Participante& outro);

    // Métodos principais
    void cadastrar();
    void exibir() const;
    void salvarEmArquivo() const;

    // Métodos estáticos para operações baseadas em CPF
    static void buscarPorCpf();
    static void removerPorCpf();
    static bool buscarParticipantePorCPF(const std::string& cpf, std::string& nome, std::string& instituicao);

    // Getters
    int getId() const { return id_participante; }
    std::string getCpf() const { return cpf; }
    std::string getNome() const { return nome_completo; }
    std::string getEmail() const { return email; }
    std::string getInstituicao() const;

    // Métodos para adicionar elementos aos arrays
    void adicionarTelefone(const std::string& telefone);
    void adicionarCurso(const std::string& curso);
    void adicionarInstituicao(int id_instituicao);

    // Métodos utilitários estáticos
    static int proximoId();
    static void limparBuffer();
};

class SistemaParticipantes {
private:
    std::string nomeArquivo;

public:
    SistemaParticipantes() : nomeArquivo("Participante.txt") {}

    void cadastrar();
    void listar() const;
    void buscar() const;
    void remover();
};

// Funções de ID global
int getGlId_Participante(std::string nome_arq);
int updGlId_Participante(std::string nome_arq);
void limparBuffer();

// Função principal do módulo
int mainParticipante();