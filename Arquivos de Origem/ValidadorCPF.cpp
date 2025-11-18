#include "ValidadorCPF.hpp"

/*
      Responsável: Luan Palma
      sistema: Area de Atividades
      github: lusilpa
*/

/*
     ===============================================
     Validação de CPF
     ===============================================
     A função pública validar é o método principal, 
     que orquestra toda a validação do CPF. Ela começa 
     chamando a função privada limpar para remover todos
     os caracteres não numéricos, como pontos e traços, 
     da string de entrada. Em seguida, validar checa 
     regras básicas, como o tamanho (11) e se todos os 
     dígitos são idênticos, usando o helper digitosIguais. 
     O cálculo dos dígitos verificadores é feito pela 
     somaRecursiva, que multiplica os dígitos por pesos 
     decrescentes (10, 9, 8... e depois 11, 10, 9...). 
     Por fim, validar compara os dois dígitos calculados 
     com os dois últimos dígitos do CPF limpo para determinar 
     se é um número válido.

     Equipe Credentia+
     Código Revisado!
*/

//Luan: O método público que organiza tudo
bool ValidadorCPF::validar(const std::string& cpf) {
    std::string cpfLimpo = limpar(cpf);

    // Regras básicas
    if (cpfLimpo.length() != 11 || !isdigit(cpfLimpo[0]) || digitosIguais(cpfLimpo)) {
        return false;
    }

    // 1. Pega os 9 primeiros dígitos
    std::string baseD1 = cpfLimpo.substr(0, 9);

    // 2. Calcula o primeiro dígito (D1)
    int soma1 = somaRecursiva(baseD1, 10);
    int resto1 = soma1 % 11;
    int d1 = (resto1 < 2) ? 0 : (11 - resto1);

    // 3. Pega os 10 primeiros dígitos (base + D1 calculado)
    std::string baseD2 = baseD1 + std::to_string(d1);

    // 4. Calcula o segundo dígito (D2)
    int soma2 = somaRecursiva(baseD2, 11);
    int resto2 = soma2 % 11;
    int d2 = (resto2 < 2) ? 0 : (11 - resto2);

    // 5. Compara com o CPF original
    int d1_original = cpfLimpo[9] - '0';
    int d2_original = cpfLimpo[10] - '0';

    return (d1 == d1_original) && (d2 == d2_original);
}

// --- Implementação das funções privadas ---

//Luan: Função recursiva para calcular a soma ponderada
int ValidadorCPF::somaRecursiva(const std::string& str, int peso) {
    // --- CASO BASE ---
    if (str.empty()) {
        return 0;
    }

    // --- PASSO RECURSIVO ---
    int digitoAtual = str[0] - '0';
    std::string restoDaString = str.substr(1);

    return (digitoAtual * peso) + somaRecursiva(restoDaString, peso - 1);
}

//Luan: Função para limpar a string, removendo caracteres não numéricos
std::string ValidadorCPF::limpar(const std::string& str) {
    std::string resultado = "";
    for (char c : str) {
        if (isdigit(c)) {
            resultado += c;
        }
    }
    return resultado;
}

bool ValidadorCPF::digitosIguais(const std::string& str) {
    if (str.empty()) return true;
    char primeiro = str[0];
    return std::all_of(str.begin() + 1, str.end(), [primeiro](char c) {
        return c == primeiro;
        });
}