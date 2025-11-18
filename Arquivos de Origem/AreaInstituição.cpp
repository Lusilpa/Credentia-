#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "AreaInstituicao.hpp"

/*
      Responsável: João Pedro Bandeira
      sistema: Area de Instituição
      github: jotapejx
*/

// =============================================
// CONSTANTES PARA ALOCAÇÃO DINÂMICA
// =============================================
#define CAPACIDADE_INICIAL 2
#define FATOR_CRESCIMENTO 2

/* =============================================
FUNÇÕES AUXILIARES PARA INTERFACE PADRÃO
=============================================
*/

/**
 * @brief Exibe o cabeçalho principal padronizado da aplicação.
 */
void exibirCabecalhoApp() {
    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl; 
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
}

/**
 * @brief Exibe o prompt de "Digite uma opção" padronizado.
 */
void exibirPromptOpcao() {
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "               DIGITE UMA OPÇÃO                " << std::endl; 
    std::cout << "-----------------------------------------------" << std::endl;
}

/* =============================================
    PARTE 1: IMPLEMENTAÇÃO DA CLASSE INSTITUICAO
    =============================================
    Este trecho implementa a "Regra dos Três" (Rule of Three) em C++ para a classe 
    Instituicao, que gerencia manualmente a memória de um array de telefones. 
    O construtor padrão inicia o objeto "vazio", definindo o ponteiro como nullptr. 
    O destrutor (~Instituicao) chama liberarTelefones para usar delete[] e evitar vazamentos de memória. 
    O construtor de cópia e o operator= (operador de atribuição) realizam uma cópia profunda (deep copy):
    eles alocam nova memória para os telefones do novo objeto, garantindo que ele seja independente do original.

    att. Luan Palma
    Código Revisado!
*/

/* Construtor - Inicializa todos os ponteiros como nullptr */
Instituicao::Instituicao()
    : id_instituicao(0), telefones(nullptr),
    quantidade_telefones(0), capacidade_telefones(0) {
}

/* Destrutor - Libera toda a memória alocada */
Instituicao::~Instituicao() {
    liberarTelefones(*this);
}

/* Construtor de cópia (Regra dos Três) */
Instituicao::Instituicao(const Instituicao& outro)
    : id_instituicao(0), telefones(nullptr),
    quantidade_telefones(0), capacidade_telefones(0) {

    // Copia dados básicos
    id_instituicao = outro.id_instituicao;
    nome = outro.nome;
    endereco_reitoria = outro.endereco_reitoria;
    tipo_vinculo_com_evento = outro.tipo_vinculo_com_evento;
    senha_institucional = outro.senha_institucional;

    // Copia array de telefones
    quantidade_telefones = outro.quantidade_telefones;
    capacidade_telefones = outro.capacidade_telefones;

    if (capacidade_telefones > 0 && outro.telefones != nullptr) {
        telefones = new std::string[capacidade_telefones];
        for (int i = 0; i < quantidade_telefones; i++) {
            telefones[i] = outro.telefones[i];
        }
    }
}

/* Operador de atribuição (Regra dos Três) */
Instituicao& Instituicao::operator=(const Instituicao& outro) {
    if (this != &outro) {
        // Libera memória atual
        liberarTelefones(*this);

        // Copia dados básicos
        id_instituicao = outro.id_instituicao;
        nome = outro.nome;
        endereco_reitoria = outro.endereco_reitoria;
        tipo_vinculo_com_evento = outro.tipo_vinculo_com_evento;
        senha_institucional = outro.senha_institucional;

        // Copia array de telefones
        quantidade_telefones = outro.quantidade_telefones;
        capacidade_telefones = outro.capacidade_telefones;

        if (capacidade_telefones > 0 && outro.telefones != nullptr) {
            telefones = new std::string[capacidade_telefones];
            for (int i = 0; i < quantidade_telefones; i++) {
                telefones[i] = outro.telefones[i];
            }
        }
    }
    return *this;
}

/* =============================================
    PARTE 2: FUNÇÕES DE GERENCIAMENTO DE MEMÓRIA
    =============================================
    Este código implementa o gerenciamento de memória para o array dinâmico 
    de telefones da classe Instituicao, simulando a funcionalidade de um std::vector. 
    A função adicionarTelefone é a interface pública: ela primeiro verifica se o array 
    está cheio. Se estiver, ela chama realocarTelefones para alocar um novo array maior, 
    copiar os dados antigos e liberar o array antigo. A função liberarTelefones (usada pelo destrutor) 
    é a contraparte, responsável por usar delete[] para liberar com segurança a memória alocada 
    e zerar os contadores, evitando vazamentos de memória.

    att. Luan Palma
    Código Revisado!
*/

/* Libera memória alocada para o array de telefones */
void liberarTelefones(Instituicao& inst) {
    if (inst.telefones != nullptr) {
        delete[] inst.telefones;
        inst.telefones = nullptr;
        inst.quantidade_telefones = 0;
        inst.capacidade_telefones = 0;
    }
}

/* Realocar array de telefones quando capacidade insuficiente */
void realocarTelefones(Instituicao& inst) {
    int nova_capacidade = inst.capacidade_telefones == 0 ?
        CAPACIDADE_INICIAL : inst.capacidade_telefones * FATOR_CRESCIMENTO;

    std::string* novo_array = new std::string[nova_capacidade];

    // Copia elementos antigos para o novo array
    for (int i = 0; i < inst.quantidade_telefones; i++) {
        novo_array[i] = inst.telefones[i];
    }

    // Libera array antigo e atualiza
    delete[] inst.telefones;
    inst.telefones = novo_array;
    inst.capacidade_telefones = nova_capacidade;
}

/* Adicionar telefone usando alocação dinâmica */
void adicionarTelefone(Instituicao& inst, const std::string& telefone) {
    if (inst.quantidade_telefones >= inst.capacidade_telefones) {
        realocarTelefones(inst);
    }
    inst.telefones[inst.quantidade_telefones] = telefone;
    inst.quantidade_telefones++;
}

/* =============================================
    PARTE 3: FUNÇÕES DE ARQUIVO
    =============================================
    Este código gerencia o CRUD (Criar, Ler, Deletar) de Instituicao diretamente no arquivo 
    "Instituicao.txt". salvarInstituicao (Criar) obtém um ID global e anexa os dados ao final 
    do arquivo. buscarInstituicao (Ler) lê o arquivo, encontra um ID, e reconstrói o objeto 
    em memória, alocando new[] para os telefones. removerInstituicao (Deletar) implementa uma 
    exclusão segura: ela reescreve o arquivo para um "temp.txt", pulando o ID a ser removido, 
    e depois substitui o original. A função exibirInstituicao é um auxiliar simples que apenas 
    imprime um objeto Instituicao já carregado.

    att. Jennifer e Luan
    Código Revisado!

*/

/* Salva instituição no arquivo txt com formatação específica */
void salvarInstituicao(Instituicao& inst) {
    std::ofstream arquivo;
    std::string nomeArquivo = "Instituicao.txt";

    arquivo.open(nomeArquivo, std::ios::app);

    // Cria cópia com ID atualizado usando sistema global
    Instituicao instComId = inst;
    instComId.id_instituicao = updGlobalid_instituicao("global_id_instituicao.txt");

    // Escreve dados formatados no arquivo
    arquivo << "ID:" << instComId.id_instituicao << "\n";
    arquivo << "NOME:" << instComId.nome << "\n";
    arquivo << "ENDERECO:" << instComId.endereco_reitoria << "\n";
    arquivo << "VINCULO:" << instComId.tipo_vinculo_com_evento << "\n";
    arquivo << "SENHA:" << instComId.senha_institucional << "\n";
    arquivo << "TELEFONES_QTD:" << instComId.quantidade_telefones << "\n";

    // Salva cada telefone em linha separada
    for (int i = 0; i < instComId.quantidade_telefones; i++) {
        arquivo << "TEL:" << instComId.telefones[i] << "\n";
    }

    arquivo << "---\n"; // Separador entre instituições
    arquivo.close();

    // Exibe confirmação com todos os dados cadastrados (NOVO PADRÃO)
    system("cls");
    exibirCabecalhoApp();
    std::cout << "===============================================" << std::endl; 
    std::cout << "        INSTITUIÇÃO SALVA COM SUCESSO        " << std::endl; 
    std::cout << "===============================================" << std::endl;
    std::cout << "ID: " << instComId.id_instituicao << std::endl;
    std::cout << "NOME: " << instComId.nome << std::endl;
    std::cout << "ENDEREÇO REITORIA: " << instComId.endereco_reitoria << std::endl;
    std::cout << "VÍNCULO: " << instComId.tipo_vinculo_com_evento << std::endl;
    std::cout << "SENHA: " << instComId.senha_institucional << std::endl;
    std::cout << "TELEFONES (" << instComId.quantidade_telefones << "): ";

    for (int i = 0; i < instComId.quantidade_telefones; i++) {
        std::cout << instComId.telefones[i];
        if (i < instComId.quantidade_telefones - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n===============================================" << std::endl;

    system("pause");
    system("cls");

    // Libera memória APÓS salvar e exibir os dados
    liberarTelefones(inst);
}

/* Busca instituição por ID no arquivo txt - CORRIGIDA */
Instituicao buscarInstituicao(int id) {
    Instituicao inst;
    // Inicializa explicitamente
    inst.id_instituicao = -1;
    inst.quantidade_telefones = 0;
    inst.capacidade_telefones = 0;
    inst.telefones = nullptr;

    std::ifstream arquivo("Instituicao.txt");
    std::string linha;
    bool encontrou = false;
    int instituicaoAtualId = -1;

    if (!arquivo.is_open()) {
        std::cout << "Arquivo de instituições não encontrado!\n";
        return inst;
    }

    // Processa arquivo linha por linha procurando pelo ID
    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            instituicaoAtualId = std::stoi(linha.substr(3));

            if (instituicaoAtualId == id) {
                encontrou = true;
                inst.id_instituicao = instituicaoAtualId;
            }
        }
        else if (encontrou) {
            // Preenche dados da instituição encontrada
            if (linha.find("NOME:") == 0) {
                inst.nome = linha.substr(5);
            }
            else if (linha.find("ENDERECO:") == 0) {
                inst.endereco_reitoria = linha.substr(9);
            }
            else if (linha.find("VINCULO:") == 0) {
                inst.tipo_vinculo_com_evento = linha.substr(8);
            }
            else if (linha.find("SENHA:") == 0) {
                inst.senha_institucional = linha.substr(6);
            }
            else if (linha.find("TELEFONES_QTD:") == 0) {
                int qtd = std::stoi(linha.substr(14));
                inst.quantidade_telefones = 0;
                inst.capacidade_telefones = qtd > 0 ? qtd : 1;

                // Aloca memória para os telefones baseado na quantidade
                if (inst.telefones != nullptr) {
                    liberarTelefones(inst);
                }
                inst.telefones = new std::string[inst.capacidade_telefones];
            }
            else if (linha.find("TEL:") == 0 && inst.telefones != nullptr) {
                if (inst.quantidade_telefones < inst.capacidade_telefones) {
                    inst.telefones[inst.quantidade_telefones] = linha.substr(4);
                    inst.quantidade_telefones++;
                }
            }
            else if (linha == "---") {
                break; // Fim dos dados desta instituição
            }
        }
    }

    arquivo.close();

    if (!encontrou) {
        liberarTelefones(inst);
        inst.id_instituicao = -1;
    }

    return inst;
}

/* Remove instituição por ID usando arquivo temporário */
bool removerInstituicao(int id) {
    std::ifstream arquivoEntrada("Instituicao.txt");
    std::ofstream arquivoSaida("temp.txt");
    std::string linha;
    bool encontrou = false;
    bool dentroDaInstituicao = false;

    if (!arquivoEntrada.is_open()) {
        std::cout << "Arquivo de instituições não encontrado!\n";
        return false;
    }

    if (!arquivoSaida.is_open()) {
        std::cout << "Erro ao criar arquivo temporário!\n";
        return false;
    }

    // Copia todas as instituições exceto a que será removida
    while (getline(arquivoEntrada, linha)) {
        if (linha.find("ID:") == 0) {
            int currentId = std::stoi(linha.substr(3));

            if (currentId == id) {
                encontrou = true;
                dentroDaInstituicao = true;
                continue; // Pula os dados da instituição a ser removida
            }
            else {
                dentroDaInstituicao = false;
            }
        }

        if (linha == "---" && dentroDaInstituicao) {
            dentroDaInstituicao = false;
            continue;
        }

        if (!dentroDaInstituicao) {
            arquivoSaida << linha << "\n";
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    // Substitui arquivo original pelo temporário
    if (encontrou) {
        remove("Instituicao.txt");
        rename("temp.txt", "Instituicao.txt");
    }
    else {
        remove("temp.txt");
    }

    return encontrou;
}

/* Exibe todos os dados de uma instituição na tela (NOVO PADRÃO) */
void exibirInstituicao(const Instituicao& inst) {
    std::cout << "\n===============================================" << std::endl;
    std::cout << "           INSTITUIÇÃO ENCONTRADA            " << std::endl; 
    std::cout << "===============================================" << std::endl;
    std::cout << "ID: " << inst.id_instituicao << "\n"
        << "NOME: " << inst.nome << "\n"
        << "ENDEREÇO: " << inst.endereco_reitoria << "\n"
        << "VÍNCULO: " << inst.tipo_vinculo_com_evento << "\n"
        << "TELEFONES (" << inst.quantidade_telefones << "): ";

    for (int i = 0; i < inst.quantidade_telefones; i++) {
        std::cout << inst.telefones[i];
        if (i < inst.quantidade_telefones - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n===============================================" << std::endl;
}

/*
    =============================================
    PARTE 4: FUNÇÃO DE CADASTRO
    =============================================
    Esta função, CadastrarInstituicao, é um menu interativo 
    para criar um objeto Instituicao e preenchê-lo com dados 
    do usuário, como nome e endereço. Seu recurso principal é 
    um loop do-while que permite ao usuário adicionar múltiplos 
    telefones. Dentro desse loop, ele chama realocarTelefones 
    sempre que o array dinâmico fica cheio, expandindo sua capacidade. 
    Após o usuário terminar de adicionar telefones (digitando 'n') e 
    preencher o resto dos dados (vínculo, senha), a função salvarInstituicao 
    é chamada para escrever o objeto final no arquivo e liberar a memória alocada.

    att. João Pedro
    Código Revisado!
*/

/* Função para cadastrar nova instituição com múltiplos telefones (NOVO PADRÃO) */
void CadastrarInstituicao() {
    Instituicao nova_inst;

    // Tratamento de bug do getline
    std::cout << "Pressione ENTER para iniciar o cadastro...";
    getline(std::cin, nova_inst.tratando_bug);

    system("cls");
    exibirCabecalhoApp();
    std::cout << "===============================================" << std::endl; 
    std::cout << "         ADICIONAR NOVA INSTITUIÇÃO          " << std::endl; 
    std::cout << "===============================================" << std::endl;

    std::cout << "\nNOME DA INSTITUIÇÃO: ";
    getline(std::cin, nova_inst.nome);

    std::cout << "ENDEREÇO DA REITORIA: ";
    getline(std::cin, nova_inst.endereco_reitoria);
    system("cls");

    exibirCabecalhoApp();
    std::cout << "===============================================" << std::endl; 
    std::cout << "           CADASTRO DE TELEFONES             " << std::endl; 
    std::cout << "===============================================" << std::endl;
    char continuar;

    do {
        // Realoca memória se capacidade estiver esgotada
        if (nova_inst.quantidade_telefones >= nova_inst.capacidade_telefones) {
            realocarTelefones(nova_inst);
        }

        std::cout << "\nTELEFONE " << (nova_inst.quantidade_telefones + 1) << ": ";
        std::string telefone;
        std::getline(std::cin, telefone);

        adicionarTelefone(nova_inst, telefone);
        std::cout << "Telefone adicionado com sucesso!\n";

        if (nova_inst.quantidade_telefones < nova_inst.capacidade_telefones) {
            std::cout << "ADICIONAR OUTRO TELEFONE? (s/n): ";
            std::cin >> continuar;
            std::cin.ignore(1000, '\n');
        }
        else {
            std::cout << "Capacidade máxima atingida. Continuando...\n";
            continuar = 'n';
        }

    } while (continuar == 's' || continuar == 'S');

    system("cls");
    exibirCabecalhoApp();
    std::cout << "===============================================" << std::endl; 
    std::cout << "         ADICIONAR NOVA INSTITUIÇÃO          " << std::endl; 
    std::cout << "===============================================" << std::endl;
    std::cout << "\nDADOS ADICIONAIS:\n\n";

    std::cout << "TIPO DE VÍNCULO COM O EVENTO: ";
    std::getline(std::cin, nova_inst.tipo_vinculo_com_evento);

    std::cout << "SENHA INSTITUCIONAL: ";
    std::getline(std::cin, nova_inst.senha_institucional);
    system("cls");

    // Chama função de salvamento (que já exibe a tela de sucesso)
    salvarInstituicao(nova_inst);
}

/*
    =============================================
    PARTE 5: FUNÇÕES DE ID GLOBAL
    =============================================
    Este código implementa um sistema de ID auto-incremento que 
    usa um arquivo de texto para persistir o contador. A função 
    getGlobalID_instituicao apenas lê o ID atual do arquivo, 
    garantindo que ele seja no mínimo 1. A função principal, 
    updGlobalid_instituicao, é usada no cadastro: ela lê o ID atual (ex: 50), 
    calcula o próximo ID (51), e sobrescreve o arquivo com o valor 51. Por fim, 
    ela retorna o ID original (50) para ser usado pelo novo objeto, garantindo 
    que cada instituição receba um ID único e sequencial.

    att. Pedro Henrique
    Código Revisado!

*/

int getGlobalID_instituicao(std::string nomeArq) {
    std::ifstream arq;
    int globalId = 1;

    arq.open(nomeArq);
    if (arq.is_open()) {
        arq >> globalId;
        arq.close();

        if (globalId < 1) {
            globalId = 1;
        }
    }
    else {
        std::cout << "Arquivo de ID global não encontrado.\n";
    }

    return globalId;
}

int updGlobalid_instituicao(std::string nomeArq) {
    std::fstream arq;
    int globalId = 1;

    arq.open(nomeArq, std::ios::in);
    if (arq.is_open()) {
        arq >> globalId;
        arq.close();
    }

    if (globalId < 1) {
        globalId = 1;
    }

    int proximoId = globalId + 1;
    arq.open(nomeArq, std::ios::out);
    if (arq.is_open()) {
        arq << proximoId;
        arq.close();
    }

    return globalId;
}

/*
    =============================================
    PARTE 6: FUNÇÕES DE LISTAGEM E BUSCA
    =============================================
    Este trecho de código define quatro funções que leem (Read) o arquivo 
    "Instituicao.txt" sem carregar os dados para a memória da classe, 
    operando diretamente na exibição. A função LB_listarInstituicoes 
    lê o arquivo e imprime todos os registros, formatando-os para o usuário. 
    As outras três são funções de busca: LB_buscarInstituicaoPorID procura por 
    uma correspondência exata de ID, enquanto LB_buscarInstituicaoPorNome e 
    LB_buscarInstituicaoPorVinculo fazem uma busca parcial (do tipo "contém") 
    e case-insensitive (convertendo tudo para minúsculas) para encontrar e 
    listar múltiplos resultados.

    att. Jennifer
    Código Revisado!
*/

void LB_listarInstituicoes() {
    std::ifstream arquivo("Instituicao.txt");
    if (!arquivo) {
        std::cout << "Nenhuma instituição cadastrada.\n";
        return;
    }

    // NOVO CABEÇALHO
    exibirCabecalhoApp();
    std::cout << "===============================================" << std::endl; 
    std::cout << "        LISTAR TODAS AS INSTITUIÇÕES         " << std::endl; 
    std::cout << "===============================================" << std::endl;
    std::string linha;
    int contador = 0;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            contador++;
            // Separador padronizado
            std::cout << "\n-----------------------------------------------" << std::endl;
        }

        // Labels em MAIÚSCULO
        if (linha.find("ID:") == 0) {
            std::cout << "ID: " << linha.substr(3) << "\n";
        }
        else if (linha.find("NOME:") == 0) {
            std::cout << "NOME: " << linha.substr(5) << "\n";
        }
        else if (linha.find("ENDERECO:") == 0) {
            std::cout << "ENDEREÇO: " << linha.substr(9) << "\n";
        }
        else if (linha.find("VINCULO:") == 0) {
            std::cout << "VÍNCULO: " << linha.substr(8) << "\n";
        }
        else if (linha.find("SENHA:") == 0) {
            std::cout << "SENHA: " << linha.substr(6) << "\n";
        }
        else if (linha.find("TELEFONES_QTD:") == 0) {
            continue;
        }
        else if (linha.find("TEL:") == 0) {
            if (linha.substr(4) != "") {
                std::cout << "TELEFONE: " << linha.substr(4) << "\n";
            }
        }
    }

    if (contador == 0) {
        std::cout << "Nenhuma instituição encontrada.\n";
    }
    else {
        std::cout << "\n===============================================" << std::endl;
        std::cout << "TOTAL: " << contador << " INSTITUIÇÃO(ÕES) ENCONTRADA(S)\n";
        std::cout << "===============================================" << std::endl;
    }

    arquivo.close();
}

void LB_buscarInstituicaoPorID(int id) {
    std::ifstream arquivo("Instituicao.txt");
    if (!arquivo) {
        std::cout << "Arquivo de instituições não encontrado!\n";
        return;
    }

    std::string linha;
    bool encontrou = false;
    bool dentroDaInstituicao = false;
    int instituicaoAtualId = -1;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            instituicaoAtualId = std::stoi(linha.substr(3));
            if (instituicaoAtualId == id) {
                encontrou = true;
                dentroDaInstituicao = true;
                // NOVO CABEÇALHO
                std::cout << "\n===============================================" << std::endl;
                std::cout << "           INSTITUIÇÃO ENCONTRADA            " << std::endl; 
                std::cout << "===============================================" << std::endl;
                std::cout << "ID: " << instituicaoAtualId << "\n";
            }
            else {
                dentroDaInstituicao = false;
            }
        }
        else if (dentroDaInstituicao) {
            // Labels em MAIÚSCULO
            if (linha.find("NOME:") == 0) {
                std::cout << "NOME: " << linha.substr(5) << "\n";
            }
            else if (linha.find("ENDERECO:") == 0) {
                std::cout << "ENDEREÇO: " << linha.substr(9) << "\n";
            }
            else if (linha.find("VINCULO:") == 0) {
                std::cout << "VÍNCULO: " << linha.substr(8) << "\n";
            }
            else if (linha.find("SENHA:") == 0) {
                std::cout << "SENHA: " << linha.substr(6) << "\n";
            }
            else if (linha.find("TELEFONES_QTD:") == 0) {
                int qtd = std::stoi(linha.substr(14));
                std::cout << "QTD. TELEFONES: " << qtd << "\n";
            }
            else if (linha.find("TEL:") == 0) {
                if (linha.substr(4) != "") {
                    std::cout << "TELEFONE: " << linha.substr(4) << "\n";
                }
            }
            else if (linha == "---") {
                std::cout << "===============================================" << std::endl;
                break;
            }
        }
    }

    if (!encontrou) {
        std::cout << "\nInstituição com ID " << id << " não encontrada.\n";
    }

    arquivo.close();
}

void LB_buscarInstituicaoPorNome(std::string nomeProcurado) {
    std::ifstream arquivo("Instituicao.txt");
    if (!arquivo) {
        std::cout << "Arquivo de instituições não encontrado!\n";
        return;
    }

    std::string linha;
    bool encontrou = false;
    bool dentroDaInstituicao = false;
    int instituicaoAtualId = -1;
    std::string nomeAtual = "";

    for (char& c : nomeProcurado) {
        c = std::tolower(c);
    }

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            instituicaoAtualId = std::stoi(linha.substr(3));
            dentroDaInstituicao = true;
            nomeAtual = "";
        }
        else if (linha.find("NOME:") == 0 && dentroDaInstituicao) {
            nomeAtual = linha.substr(5);

            std::string nomeLower = nomeAtual;
            for (char& c : nomeLower) {
                c = std::tolower(c);
            }

            if (nomeLower.find(nomeProcurado) != std::string::npos) {
                encontrou = true;
                // NOVO CABEÇALHO
                std::cout << "\n===============================================" << std::endl;
                std::cout << "           INSTITUIÇÃO ENCONTRADA            " << std::endl; 
                std::cout << "===============================================" << std::endl;
                std::cout << "ID: " << instituicaoAtualId << "\n";
                std::cout << "NOME: " << nomeAtual << "\n";

                while (getline(arquivo, linha) && linha != "---") {
                    // Labels em MAIÚSCULO
                    if (linha.find("ENDERECO:") == 0) {
                        std::cout << "ENDEREÇO: " << linha.substr(9) << "\n";
                    }
                    else if (linha.find("VINCULO:") == 0) {
                        std::cout << "VÍNCULO: " << linha.substr(8) << "\n";
                    }
                    else if (linha.find("SENHA:") == 0) {
                        std::cout << "SENHA: " << linha.substr(6) << "\n";
                    }
                    else if (linha.find("TELEFONES_QTD:") == 0) {
                        int qtd = std::stoi(linha.substr(14));
                        std::cout << "QTD. TELEFONES: " << qtd << "\n";
                    }
                    else if (linha.find("TEL:") == 0 && linha.substr(4) != "") {
                        std::cout << "TELEFONE: " << linha.substr(4) << "\n";
                    }
                }
                std::cout << "===============================================" << std::endl;
            }
            else {
                dentroDaInstituicao = false;
            }
        }
        else if (linha == "---") {
            dentroDaInstituicao = false;
        }
    }

    if (!encontrou) {
        std::cout << "\nNenhuma instituição encontrada com o nome: " << nomeProcurado << "\n";
    }

    arquivo.close();
}

/*
    =============================================
    PARTE 7: MENU PRINCIPAL
    =============================================
    Este trecho de código define quatro funções que leem (Read) o arquivo
    "Instituicao.txt" sem carregar os dados para a memória da classe,
    operando diretamente na exibição. A função LB_listarInstituicoes
    lê o arquivo e imprime todos os registros, formatando-os para o usuário.
    As outras três são funções de busca: LB_buscarInstituicaoPorID procura por
    uma correspondência exata de ID, enquanto LB_buscarInstituicaoPorNome e
    LB_buscarInstituicaoPorVinculo fazem uma busca parcial (do tipo "contém")
    e case-insensitive (convertendo tudo para minúsculas) para encontrar e
    listar múltiplos resultados.

    att. João Pedro
    Código Revisado!
*/
int mainInstituicao() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int opcao;
    do {
        // NOVO MENU PADRONIZADO
        exibirCabecalhoApp();
        std::cout << "===============================================" << std::endl; 
        std::cout << "           ÁREA DE INSTITUIÇÕES              " << std::endl; 
        std::cout << "===============================================" << std::endl;
        std::cout << "1. ADICIONAR NOVA INSTITUIÇÃO" << std::endl;
        std::cout << "2. BUSCAR INSTITUIÇÃO POR ID" << std::endl;
        std::cout << "3. REMOVER INSTITUIÇÃO POR ID" << std::endl;
        std::cout << "4. LISTAR TODAS AS INSTITUIÇÕES" << std::endl;
        std::cout << "5. BUSCAR INSTITUIÇÃO POR NOME" << std::endl;
        std::cout << "0. RETORNAR AO MENU INICIAL" << std::endl;
        exibirPromptOpcao(); // Novo prompt padronizado

        std::cin >> opcao;
        std::cin.ignore(1000, '\n');
        system("cls");

        switch (opcao) {
        case 1: {
            CadastrarInstituicao(); // Já está padronizado
            break;
        }
        case 2: {
            int id_busca;
            // Tela de input padronizada
            exibirCabecalhoApp();
            std::cout << "===============================================" << std::endl; 
            std::cout << "         BUSCAR INSTITUIÇÃO POR ID           " << std::endl; 
            std::cout << "===============================================" << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << "                 DIGITE O ID                   " << std::endl; 
            std::cout << "-----------------------------------------------" << std::endl;
            std::cin >> id_busca;
            std::cin.ignore(1000, '\n');
            system("cls");

            Instituicao inst = buscarInstituicao(id_busca);

            if (inst.id_instituicao != -1) {
                exibirInstituicao(inst); // Já está padronizado
                liberarTelefones(inst);
            }
            else {
                std::cout << "\n>>> Instituição com ID " << id_busca << " não encontrada. <<<\n";
            }
            system("PAUSE");
            system("cls");
            break;
        }
        case 3: {
            int id_remocao;
            // Tela de input padronizada
            exibirCabecalhoApp();
            std::cout << "===============================================" << std::endl; 
            std::cout << "         REMOVER INSTITUIÇÃO POR ID          " << std::endl; 
            std::cout << "===============================================" << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << "                 DIGITE O ID                   " << std::endl; 
            std::cout << "-----------------------------------------------" << std::endl;
            std::cin >> id_remocao;
            std::cin.ignore(1000, '\n');
            system("cls");

            if (removerInstituicao(id_remocao)) {
                std::cout << "\n>>> Instituição com ID " << id_remocao << " removida com sucesso! <<<\n";
            }
            else {
                std::cout << "\n>>> Instituição com ID " << id_remocao << " não encontrada. <<<\n";
            }
            system("PAUSE");
            system("cls");
            break;
        }
        case 4: {
            LB_listarInstituicoes(); // Já está padronizado
            system("PAUSE");
            system("cls");
            break;
        }
        case 5: {
            std::string nome_busca;
            // Tela de input padronizada
            exibirCabecalhoApp();
            std::cout << "===============================================" << std::endl; 
            std::cout << "        BUSCAR INSTITUIÇÃO POR NOME          " << std::endl; 
            std::cout << "===============================================" << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;
            std::cout << "                DIGITE O NOME                  " << std::endl; 
            std::cout << "-----------------------------------------------" << std::endl;
            std::getline(std::cin, nome_busca);
            system("cls");
            
            LB_buscarInstituicaoPorNome(nome_busca); // Já está padronizado
            system("PAUSE");
            system("cls");
            break;
        }
        case 0:
            std::cout << "Voltando a Tela Anterior\n";
            break;
        default:
            std::cout << "Opção inválida! Tente novamente.\n";
            system("PAUSE");
            system("cls");
            break;
        }
    } while (opcao != 0);
    return 0;
}