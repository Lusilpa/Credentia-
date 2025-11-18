#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#undef min
#undef max
#include <cstdlib>

// --- Definição da Estrutura ---
// (Tipos de dados devem ser declarados no header)
struct Certificado {
    std::string nome;
    std::string cpf;
    std::string tipo;
    int horas;
};

// --- Declaração de Variável Global ---
// (Usamos 'extern' para dizer ao compilador que esta variável
// será *definida* em um arquivo .cpp)
extern std::vector<Certificado> certificados;

// --- Protótipos das Funções ---
// (Apenas a assinatura da função, a implementação fica no .cpp)

/**
 * @brief Cria um arquivo .txt formatado como um certificado.
 * @param cert O objeto Certificado contendo os dados do participante.
 */
void criarCertificado(const Certificado& cert);

/**
 * @brief Busca e exibe no console os certificados pelo nome do participante.
 * @param nome O nome a ser buscado.
 */
void buscarPorNome(const std::string& nome);

/**
 * @brief Busca e exibe no console os certificados pelo CPF do participante.
 * @param cpf O CPF a ser buscado.
 */
void buscarPorCpf(const std::string& cpf);

int mainCertificados();