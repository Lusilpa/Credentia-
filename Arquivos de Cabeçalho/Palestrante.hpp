#pragma once

#include <string>
#include <Windows.h>
#undef min
#undef max
#include <cstdlib>

// =============================================
// CLASSE PALESTRANTE
// =============================================

class Palestrante {
private:
    int id_palestrante;
    std::string nome_completo;
    std::string titulo_academico;
    std::string atividade;

public:
    // Construtores
    Palestrante();
    Palestrante(int id, const std::string& nome, const std::string& titulo, const std::string& atv);

    // Métodos de acesso
    int getId() const { return id_palestrante; }
    std::string getNome() const { return nome_completo; }
    std::string getTitulo() const { return titulo_academico; }
    std::string getAtividade() const { return atividade; }

    // Métodos de modificação
    void setId(int id) { id_palestrante = id; }
    void setNome(const std::string& nome) { nome_completo = nome; }
    void setTitulo(const std::string& titulo) { titulo_academico = titulo; }
    void setAtividade(const std::string& atv) { atividade = atv; }

    // Métodos funcionais
    void exibir() const;
    std::string toFileString() const;
};

// =============================================
// FUNÇÕES AUXILIARES
// =============================================

inline std::string trim(const std::string& str);

// =============================================
// FUNÇÕES DE ID GLOBAL
// =============================================

int getGlobalID_palestrante(std::string nomeArq);
int updGlobalID_palestrante(std::string nomeArq);

// =============================================
// FUNÇÕES PRINCIPAIS DO CRUD
// =============================================

void CadastrarPalestrante();
void ListarPalestrantes();
void BuscarPalestrantePorID(int id);
void BuscarPalestrantePorNome(const std::string& nome);
bool RemoverPalestrante(int id);

// =============================================
// FUNÇÕES DE ARQUIVO
// =============================================

void LB_listarPalestrantes();
void LB_buscarPalestrantePorID(int id);
void LB_buscarPalestrantePorNome(std::string nomeProcurado);
bool LB_removerPalestrante(int id);

// =============================================
// MENU PRINCIPAL
// =============================================

int MainPalestrantes();