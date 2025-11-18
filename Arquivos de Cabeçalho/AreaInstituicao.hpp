#pragma once

#include <string>
#include <Windows.h>
#undef min
#undef max
#include <cstdlib>




// =============================================
// STRUCT INSTITUICAO COM ALOCAÇÃO DINÂMICA
// =============================================
struct Instituicao {
    std::string* telefones;           // Array dinâmico de strings
    int quantidade_telefones;
    int capacidade_telefones;
    int id_instituicao;
    std::string nome;
    std::string endereco_reitoria;
    std::string tipo_vinculo_com_evento;
    std::string senha_institucional;
    std::string tratando_bug;

    // Construtor
    Instituicao();

    // Destrutor
    ~Instituicao();

    // Construtor de cópia (Regra dos Três)
    Instituicao(const Instituicao& outro);

    // Operador de atribuição (Regra dos Três)
    Instituicao& operator=(const Instituicao& outro);
};

// =============================================
// FUNÇÕES DE GERENCIAMENTO DE MEMÓRIA
// =============================================
void liberarTelefones(Instituicao& inst);
void realocarTelefones(Instituicao& inst);
void adicionarTelefone(Instituicao& inst, const std::string& telefone);

// =============================================
// FUNÇÕES PRINCIPAIS DO CRUD
// =============================================
void salvarInstituicao(Instituicao& inst);
Instituicao buscarInstituicao(int id);
bool removerInstituicao(int id);
void exibirInstituicao(const Instituicao& inst);
void CadastrarInstituicao();

// =============================================
// FUNÇÕES DE LISTAGEM E BUSCA
// =============================================
void LB_listarInstituicoes();
void LB_buscarInstituicaoPorID(int id);
void LB_buscarInstituicaoPorNome(std::string nomeProcurado);
void LB_buscarInstituicaoPorVinculo(std::string vinculoProcurado);

// =============================================
// FUNÇÕES DE ID GLOBAL
// =============================================
int getGlobalID_instituicao(std::string nomeArq);
int updGlobalid_instituicao(std::string nomeArq);

// =============================================
// MENU PRINCIPAL
// =============================================
int mainInstituicao();