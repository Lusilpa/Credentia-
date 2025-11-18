#pragma once



#include <string>
#include <algorithm>
#include <Windows.h>
#undef min
#undef max
#include <cstdlib>

class ValidadorCPF {
private:
    static int somaRecursiva(const std::string& str, int peso);
    static std::string limpar(const std::string& str);
    static bool digitosIguais(const std::string& str);

public:
    static bool validar(const std::string& cpf);
};