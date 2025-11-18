// Participante.cpp

#include "Participante.hpp"
#include "ValidadorCPF.hpp"
#include <algorithm>
#include <limits>
#include <cctype>
#include <vector>

/*
      Responsável: Igor Kramer
      sistema: Area de Palestrantes
      github: igorswf
*/

using namespace std;

/*
    PARTE 1: GERENCIAMENTO MANUAL DE MEMÓRIA
    =================================================================================================
    Este código C++ detalha a implementação da classe Participante, cujo design é centrado no gerenciamento 
    manual de memória para listas dinâmicas. A classe armazena dados simples (ID, CPF, nome) e três arrays 
    alocados dinamicamente: telefones (strings), cursos_palestras (strings) e ids_instituicao_origem (ints).

    Para gerenciar corretamente essa memória, a classe segue a "Regra dos Três": possui um Destrutor 
    (para liberar memória), um Construtor de Cópia e um Operador de Atribuição (ambos usando copiarDados 
    para fazer "cópias profundas" e evitar que dois objetos apontem para a mesma memória).

    Além disso, a classe utiliza uma estratégia de realocação dinâmica. Métodos como adicionarTelefone 
    verificam se o array está cheio; se estiver, a função realocarTelefones é chamada para dobrar a 
    capacidade do array, copiando os dados antigos antes de adicionar o novo.

	Att. Equipe Credentia+ 
	Código Revisado!
*/

/* Construtor - Inicializa todos os ponteiros como nullptr */
Participante::Participante()
    : id_participante(0),
    telefones(nullptr), cursos_palestras(nullptr), ids_instituicao_origem(nullptr),
    quantidade_telefones(0), quantidade_cursos(0), quantidade_instituicoes(0),
    capacidade_telefones(0), capacidade_cursos(0), capacidade_instituicoes(0) {
}

/* Destrutor - Libera toda a memória alocada dinamicamente */
Participante::~Participante() {
    liberarMemoria();
}

/* Construtor de cópia (Regra dos Três) */
Participante::Participante(const Participante& outro)
    : id_participante(0),
    telefones(nullptr), cursos_palestras(nullptr), ids_instituicao_origem(nullptr),
    quantidade_telefones(0), quantidade_cursos(0), quantidade_instituicoes(0),
    capacidade_telefones(0), capacidade_cursos(0), capacidade_instituicoes(0) {
    copiarDados(outro);
}

/* Operador de atribuição (Regra dos Três) */
Participante& Participante::operator=(const Participante& outro) {
    if (this != &outro) {
        liberarMemoria();
        copiarDados(outro);
    }
    return *this;
}

/* Método para liberar toda a memória alocada */
void Participante::liberarMemoria() {
    delete[] telefones;
    delete[] cursos_palestras;
    delete[] ids_instituicao_origem;

    telefones = nullptr;
    cursos_palestras = nullptr;
    ids_instituicao_origem = nullptr;

    quantidade_telefones = quantidade_cursos = quantidade_instituicoes = 0;
    capacidade_telefones = capacidade_cursos = capacidade_instituicoes = 0;
}

/* Método para copiar dados entre objetos (usado na cópia) */
void Participante::copiarDados(const Participante& outro) {
    id_participante = outro.id_participante;
    cpf = outro.cpf;
    nome_completo = outro.nome_completo;
    email = outro.email;

    // Copiar array de telefones
    quantidade_telefones = outro.quantidade_telefones;
    capacidade_telefones = outro.capacidade_telefones;
    if (capacidade_telefones > 0) {
        telefones = new std::string[capacidade_telefones];
        for (int i = 0; i < quantidade_telefones; i++) {
            telefones[i] = outro.telefones[i];
        }
    }

    // Copiar array de cursos
    quantidade_cursos = outro.quantidade_cursos;
    capacidade_cursos = outro.capacidade_cursos;
    if (capacidade_cursos > 0) {
        cursos_palestras = new std::string[capacidade_cursos];
        for (int i = 0; i < quantidade_cursos; i++) {
            cursos_palestras[i] = outro.cursos_palestras[i];
        }
    }

    // Copiar array de instituições
    quantidade_instituicoes = outro.quantidade_instituicoes;
    capacidade_instituicoes = outro.capacidade_instituicoes;
    if (capacidade_instituicoes > 0) {
        ids_instituicao_origem = new int[capacidade_instituicoes];
        for (int i = 0; i < quantidade_instituicoes; i++) {
            ids_instituicao_origem[i] = outro.ids_instituicao_origem[i];
        }
    }
}

/* Realocar array de telefones quando capacidade insuficiente */
void Participante::realocarTelefones() {
    int nova_capacidade = capacidade_telefones == 0 ? 2 : capacidade_telefones * 2;
    std::string* novo_array = new std::string[nova_capacidade];

    for (int i = 0; i < quantidade_telefones; i++) {
        novo_array[i] = telefones[i];
    }

    delete[] telefones;
    telefones = novo_array;
    capacidade_telefones = nova_capacidade;
}

/* Realocar array de cursos quando capacidade insuficiente */
void Participante::realocarCursos() {
    int nova_capacidade = capacidade_cursos == 0 ? 2 : capacidade_cursos * 2;
    std::string* novo_array = new std::string[nova_capacidade];

    for (int i = 0; i < quantidade_cursos; i++) {
        novo_array[i] = cursos_palestras[i];
    }

    delete[] cursos_palestras;
    cursos_palestras = novo_array;
    capacidade_cursos = nova_capacidade;
}

/* Realocar array de instituições quando capacidade insuficiente */
void Participante::realocarInstituicoes() {
    int nova_capacidade = capacidade_instituicoes == 0 ? 2 : capacidade_instituicoes * 2;
    int* novo_array = new int[nova_capacidade];

    for (int i = 0; i < quantidade_instituicoes; i++) {
        novo_array[i] = ids_instituicao_origem[i];
    }

    delete[] ids_instituicao_origem;
    ids_instituicao_origem = novo_array;
    capacidade_instituicoes = nova_capacidade;
}

/* Adicionar telefone usando alocação dinâmica */
void Participante::adicionarTelefone(const std::string& telefone) {
    if (quantidade_telefones >= capacidade_telefones) {
        realocarTelefones();
    }
    telefones[quantidade_telefones] = telefone;
    quantidade_telefones++;
}

/* Adicionar curso usando alocação dinâmica */
void Participante::adicionarCurso(const std::string& curso) {
    if (quantidade_cursos >= capacidade_cursos) {
        realocarCursos();
    }
    cursos_palestras[quantidade_cursos] = curso;
    quantidade_cursos++;
}

/* Adicionar instituição usando alocação dinâmica */
void Participante::adicionarInstituicao(int id_instituicao) {
    if (quantidade_instituicoes >= capacidade_instituicoes) {
        realocarInstituicoes();
    }
    ids_instituicao_origem[quantidade_instituicoes] = id_instituicao;
    quantidade_instituicoes++;
}

/* Retorna a primeira instituição ou "Nenhuma" */
std::string Participante::getInstituicao() const {
    if (quantidade_instituicoes == 0) {
        return "Nenhuma";
    }
    return "Instituição " + std::to_string(ids_instituicao_origem[0]);
}

/*
    PARTE 2: CADASTRO DE NOVOS PARTICIPANTES
	==========================================================================================
    Este código define o método Participante::cadastrar(), que é uma interface de console para 
    coletar os dados de um novo participante. A função limpa a tela, gera um ID e solicita 
    interativamente o nome, email e CPF. O CPF é validado em um loop até que um valor correto 
    seja inserido. Em seguida, o método pergunta a quantidade de telefones, cursos e IDs de 
    instituição, coletando cada item individualmente e usando os métodos adicionar... (vistos 
    anteriormente) para alocá-los dinamicamente. Por fim, a função salvarEmArquivo() é chamada 
    para anexar (std::ios::app) os dados do novo participante ao arquivo "Participante.txt".

	Att. Igor Kramer
	Código Revisado!
*/

/* Método principal de cadastro com alocação dinâmica */
void Participante::cadastrar() {
    system("cls");
    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl;
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "         CADASTRO DE PARTICIPANTE          " << std::endl;
    std::cout << "===============================================" << std::endl;

    this->id_participante = updGlId_Participante("global_id_participante.txt");
    std::cout << "ID gerado: " << this->id_participante << std::endl;

    std::cout << "Nome completo: ";
    std::getline(std::cin, this->nome_completo);

    system("cls");
    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl;
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "         CADASTRO DE PARTICIPANTE          " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Nome: " << this->nome_completo << std::endl;

    // Validação de CPF
    std::string cpf_temp;
    bool cpf_valido = false;

    do {
        std::cout << "CPF (apenas números): ";
        std::getline(std::cin, cpf_temp);

        // CORREÇÃO: Usando a função trim estática
        cpf_temp = Participante::trim(cpf_temp);

        cpf_valido = ValidadorCPF::validar(cpf_temp);

        if (!cpf_valido) {
            system("cls");
            std::cout << "===============================================" << std::endl;
            std::cout << "                 CREDENTIA+" << std::endl;
            std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
            std::cout << "===============================================" << std::endl;
            std::cout << "         CADASTRO DE PARTICIPANTE          " << std::endl;
            std::cout << "===============================================" << std::endl;
            std::cout << "Nome: " << this->nome_completo << std::endl;
            std::cout << "❌ CPF inválido! Tente novamente." << std::endl;
        }
    } while (!cpf_valido);

    this->cpf = cpf_temp;

    system("cls");
    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl;
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "         CADASTRO DE PARTICIPANTE          " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Nome: " << this->nome_completo << std::endl;
    std::cout << "CPF: " << this->cpf << std::endl;

    std::cout << "Email: ";
    std::getline(std::cin, this->email);

    // Coletar telefones
    int num;
    std::cout << "Quantos telefones? ";

    while (true) {
        if (!(std::cin >> num)) {
            system("cls");
            std::cout << "Entrada inválida! Digite um número: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (num < 1) {
            system("cls");
            std::cout << "Digite um número maior ou igual a 1: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < num; i++) {
        std::string telefone;
        std::cout << "Telefone " << (i + 1) << ": ";
        std::getline(std::cin, telefone);

        if (telefone.empty()) {
            std::cout << "Telefone não pode ser vazio! Digite novamente." << std::endl;
            i--;
            continue;
        }

        adicionarTelefone(telefone);
    }

    // Coletar cursos/palestras
    std::cout << "Quantos cursos/palestras (entre 1 e 4)? ";

    while (true) {
        if (!(std::cin >> num)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (num < 1 || num > 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < num; i++) {
        std::string curso;
        std::cout << "Curso/Palestra " << (i + 1) << ": ";
        std::getline(std::cin, curso);

        if (curso.empty()) {
            std::cout << "Curso não pode ser vazio! Digite novamente." << std::endl;
            i--;
            continue;
        }

        adicionarCurso(curso);
    }

    // Coletar instituições
    std::cout << "Quantos IDs de instituição de origem (0 para nenhum)? ";

    while (true) {
        if (!(std::cin >> num)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (num < 0) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    for (int i = 0; i < num; i++) {
        int id_inst;
        std::cout << "ID Instituição " << (i + 1) << ": ";

        while (!(std::cin >> id_inst) || id_inst < 0) {
            std::cout << "ID inválido! Digite um número positivo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        adicionarInstituicao(id_inst);

        if (i < num - 1) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    salvarEmArquivo();

    system("cls");
    std::cout << "\nPARTICIPANTE CADASTRADO COM SUCESSO!" << std::endl;
    std::cout << "\nPressione Enter para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/* Salvar participante em arquivo com formato específico */
void Participante::salvarEmArquivo() const {
    std::ofstream arquivo("Participante.txt", std::ios::app);

    if (arquivo.is_open()) {
        arquivo << "ID:" << this->id_participante << "\n";
        arquivo << "Nome:" << this->nome_completo << "\n";
        arquivo << "CPF:" << this->cpf << "\n";
        arquivo << "Email:" << this->email << "\n";

        for (int i = 0; i < quantidade_telefones; i++) {
            arquivo << "Telefone" << i + 1 << ":" << telefones[i] << "\n";
        }

        for (int i = 0; i < quantidade_cursos; i++) {
            arquivo << "Curso" << i + 1 << ":" << cursos_palestras[i] << "\n";
        }

        for (int i = 0; i < quantidade_instituicoes; i++) {
            arquivo << "InstituicaoID" << i + 1 << ":" << ids_instituicao_origem[i] << "\n";
        }

        arquivo << "---\n";
        arquivo.close();
    }
}

/*
    PARTE 3: EXIBIR DADOS DO PARTICIPANTE
    ================================================================================
    Este código C++ define os métodos de exibição e manipulação de arquivos para a 
    classe Participante. O método exibir() é responsável por formatar e imprimir 
    no console todos os dados de uma instância, incluindo os itens dos arrays dinâmicos.

    A funcionalidade de busca (buscarPorCpf) não usa os dados do objeto atual; em vez disso, 
    ela lê o arquivo "Participante.txt", procura por um CPF e, se o encontra, carrega todos 
    os dados (incluindo as listas) em vetores std::vector temporários apenas para exibição.

    O método removerPorCpf() implementa a exclusão lendo o "Participante.txt" e escrevendo 
    em um "temp.txt". Ele copia todos os blocos de participantes, exceto aquele que corresponde 
    ao CPF informado. Ao final, o arquivo original é deletado e o temporário é renomeado.

	Att. Equipe Credentia+
	Código Revisado!
*/

/* Exibir dados do participante com arrays dinâmicos */
void Participante::exibir() const {
    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl;
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "           DADOS DO PARTICIPANTE           " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "ID: " << this->id_participante << std::endl;
    std::cout << "Nome: " << this->nome_completo << std::endl;
    std::cout << "CPF: " << this->cpf << std::endl;
    std::cout << "Email: " << this->email << std::endl;

    std::cout << "Telefones (" << quantidade_telefones << "):" << std::endl;
    for (int i = 0; i < quantidade_telefones; i++) {
        std::cout << "  - " << telefones[i] << std::endl;
    }

    std::cout << "Cursos/Palestras (" << quantidade_cursos << "):" << std::endl;
    for (int i = 0; i < quantidade_cursos; i++) {
        std::cout << "  - " << cursos_palestras[i] << std::endl;
    }

    std::cout << "IDs Instituição (" << quantidade_instituicoes << "):" << std::endl;
    if (quantidade_instituicoes > 0) {
        for (int i = 0; i < quantidade_instituicoes; i++) {
            std::cout << "  - " << ids_instituicao_origem[i] << std::endl;
        }
    }
    else {
        std::cout << "  - Nenhuma" << std::endl;
    }
    std::cout << "===============================================" << std::endl;
}

/* Buscar participante por CPF no arquivo (função auxiliar) */
bool Participante::buscarParticipantePorCPF(const std::string& cpf, std::string& nome, std::string& instituicao) {
    std::ifstream arquivo("Participante.txt");
    if (!arquivo) {
        return false;
    }

    std::string linha;
    bool dentroDoParticipante = false;
    bool cpfEncontrado = false;
    instituicao = "Nenhuma";

    // CORREÇÃO: Usando trim estático
    std::string cpfBuscado = Participante::trim(cpf);

    while (getline(arquivo, linha)) {
        std::string linha_limpa = Participante::trim(linha);

        if (linha_limpa.find("ID:") == 0) {
            dentroDoParticipante = true;
            cpfEncontrado = false;
        }
        else if (linha_limpa.find("CPF:") == 0 && dentroDoParticipante) {
            std::string cpfArquivo = Participante::trim(linha_limpa.substr(4));

            if (cpfArquivo == cpfBuscado) {
                cpfEncontrado = true;
            }
        }
        else if (dentroDoParticipante && cpfEncontrado) {
            if (linha_limpa.find("Nome:") == 0) {
                nome = Participante::trim(linha_limpa.substr(5));
            }
            else if (linha_limpa.find("InstituicaoID") == 0) {
                instituicao = Participante::trim(linha_limpa.substr(linha_limpa.find(":") + 1));
            }
        }
        else if (linha_limpa == "---") {
            if (cpfEncontrado) {
                break;
            }
            dentroDoParticipante = false;
        }
    }

    arquivo.close();
    return cpfEncontrado && !nome.empty();
}

/* Buscar participante por CPF (método de instância - interface completa) */
void Participante::buscarPorCpf() {
    std::string cpf_busca;
    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl;
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "        BUSCAR PARTICIPANTE POR CPF        " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "                DIGITE O CPF                   " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    std::getline(std::cin, cpf_busca);

    // CORREÇÃO: Usando trim estático
    cpf_busca = Participante::trim(cpf_busca);

    if (cpf_busca.length() != 11) {
        std::cout << "CPF deve conter 11 dígitos!" << std::endl;
        system("pause");
        system("cls");
        return;
    }

    std::ifstream arquivo("Participante.txt");

    if (!arquivo.is_open()) {
        std::cout << "Arquivo Participante.txt não encontrado!" << std::endl;
        system("pause");
        system("cls");
        return;
    }

    std::string linha;
    bool encontrou = false;
    bool dentroDoParticipante = false;

    std::string id_encontrado, nome_encontrado, cpf_encontrado, email_encontrado;
    std::vector<std::string> instituicoes_encontradas;
    std::vector<std::string> telefones_encontrados;
    std::vector<std::string> cursos_encontrados;

    while (getline(arquivo, linha)) {
        std::string linha_limpa = Participante::trim(linha);

        if (linha_limpa.find("ID:") == 0 && !dentroDoParticipante) {
            id_encontrado = Participante::trim(linha_limpa.substr(3));
            dentroDoParticipante = true;
            encontrou = false;
        }
        else if (linha_limpa.find("CPF:") == 0 && dentroDoParticipante) {
            std::string cpf_arquivo = Participante::trim(linha_limpa.substr(4));

            if (cpf_arquivo == cpf_busca) {
                cpf_encontrado = cpf_arquivo;
                encontrou = true;
            }
            else {
                dentroDoParticipante = false;
                id_encontrado.clear();
            }
        }
        else if (encontrou && dentroDoParticipante) {
            if (linha_limpa.find("Nome:") == 0) {
                nome_encontrado = Participante::trim(linha_limpa.substr(5));
            }
            else if (linha_limpa.find("Email:") == 0) {
                email_encontrado = Participante::trim(linha_limpa.substr(6));
            }
            else if (linha_limpa.find("Telefone") == 0) {
                telefones_encontrados.push_back(Participante::trim(linha_limpa.substr(linha_limpa.find(":") + 1)));
            }
            else if (linha_limpa.find("Curso") == 0) {
                cursos_encontrados.push_back(Participante::trim(linha_limpa.substr(linha_limpa.find(":") + 1)));
            }
            else if (linha_limpa.find("InstituicaoID") == 0) {
                instituicoes_encontradas.push_back(Participante::trim(linha_limpa.substr(linha_limpa.find(":") + 1)));
            }
        }

        if (linha_limpa == "---") {
            if (encontrou && dentroDoParticipante) {
                std::cout << "===============================================" << std::endl;
                std::cout << "                 CREDENTIA+" << std::endl;
                std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
                std::cout << "===============================================" << std::endl;
                std::cout << "           PARTICIPANTE ENCONTRADO         " << std::endl;
                std::cout << "===============================================" << std::endl;
                std::cout << "ID: " << id_encontrado << std::endl;
                std::cout << "Nome: " << nome_encontrado << std::endl;
                std::cout << "CPF: " << cpf_encontrado << std::endl;
                std::cout << "Email: " << email_encontrado << std::endl;

                std::cout << "Telefones (" << telefones_encontrados.size() << "):" << std::endl;
                if (telefones_encontrados.empty()) {
                    std::cout << "  - Nenhuma" << std::endl;
                }
                else {
                    for (const std::string& tel : telefones_encontrados) {
                        std::cout << "  - " << tel << std::endl;
                    }
                }

                std::cout << "Cursos/Palestras (" << cursos_encontrados.size() << "):" << std::endl;
                if (cursos_encontrados.empty()) {
                    std::cout << "  - Nenhuma" << std::endl;
                }
                else {
                    for (const std::string& curso : cursos_encontrados) {
                        std::cout << "  - " << curso << std::endl;
                    }
                }

                std::cout << "IDs Instituição (" << instituicoes_encontradas.size() << "):" << std::endl;
                if (instituicoes_encontradas.empty()) {
                    std::cout << "  - Nenhuma" << std::endl;
                }
                else {
                    for (const std::string& inst_id : instituicoes_encontradas) {
                        std::cout << "  - " << inst_id << std::endl;
                    }
                }
                std::cout << "===============================================" << std::endl;
                break;
            }
            dentroDoParticipante = false;
            encontrou = false;
            id_encontrado.clear();
            nome_encontrado.clear();
            cpf_encontrado.clear();
            email_encontrado.clear();
            instituicoes_encontradas.clear();
            telefones_encontrados.clear();
            cursos_encontrados.clear();
        }
    }

    arquivo.close();

    if (!encontrou) {
        std::cout << "\n>>> Participante com CPF '" << cpf_busca << "' não encontrado. <<<\n";
    }

    system("pause");
    system("cls");
}

/* Remover participante por CPF */
void Participante::removerPorCpf() {
    std::string cpf_remover;
    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl;
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "        REMOVER PARTICIPANTE POR CPF       " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "                DIGITE O CPF                   " << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    std::getline(std::cin, cpf_remover);

    // Usando trim estático
    cpf_remover = Participante::trim(cpf_remover);

    if (cpf_remover.length() != 11) {
        std::cout << "CPF deve conter 11 dígitos!" << std::endl;
        system("pause");
        system("cls");
        return;
    }

    std::ifstream arquivoEntrada("Participante.txt");

    if (!arquivoEntrada.is_open()) {
        std::cout << "Arquivo Participante.txt não encontrado!" << std::endl;
        system("pause");
        system("cls");
        return;
    }

    std::ofstream arquivoSaida("temp.txt");

    if (!arquivoSaida.is_open()) {
        std::cout << "Erro ao criar arquivo temporário!" << std::endl;
        arquivoEntrada.close();
        system("pause");
        system("cls");
        return;
    }

    std::string linha;
    bool encontrou = false;
    std::vector<std::string> bufferParticipante;

    while (getline(arquivoEntrada, linha)) {
        if (linha == "---") {
            bool pularEsteParticipante = false;

            for (const std::string& linhaBuffer : bufferParticipante) {
                if (linhaBuffer.find("CPF:") == 0) {
                    std::string cpf_arquivo = linhaBuffer.substr(4);
                    cpf_arquivo = Participante::trim(cpf_arquivo);

                    if (cpf_arquivo == cpf_remover) {
                        encontrou = true;
                        pularEsteParticipante = true;
                        break;
                    }
                }
            }

            if (!pularEsteParticipante) {
                for (const std::string& linhaBuffer : bufferParticipante) {
                    arquivoSaida << linhaBuffer << "\n";
                }
                arquivoSaida << "---\n";
            }

            bufferParticipante.clear();
        }
        else {
            bufferParticipante.push_back(linha);
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    if (encontrou) {
        remove("Participante.txt");
        rename("temp.txt", "Participante.txt");
        std::cout << "\n>>> Participante removido com sucesso! <<<\n";
    }
    else {
        remove("temp.txt");
        std::cout << "\n>>> Participante não encontrado. <<<\n";
    }

    system("pause");
    system("cls");
}

/*
   PARTE 4: Implementação do SistemaParticipantes
   ===============================================================
   Este trecho de C++ define a classe SistemaParticipantes, que atua 
   como uma controladora (ou fachada) para o gerenciamento de participantes. 
   Os métodos buscar() e remover() não possuem lógica própria; eles 
   simplesmente delegam a chamada para os métodos estáticos Participante::buscarPorCpf() 
   e Participante::removerPorCpf(). Da mesma forma, cadastrar() cria uma instância 
   temporária de Participante apenas para invocar o método cadastrar() dela. A única 
   funcionalidade realmente implementada nesta classe é listar(), que abre o "Participante.txt", 
   lê o arquivo linha por linha e imprime um resumo de todos os cadastrados no console.

   Att. Equipe Credentia+
   Código Revisado!
*/

void SistemaParticipantes::cadastrar() {
    Participante p;
    p.cadastrar();
}

void SistemaParticipantes::listar() const {
    std::ifstream arquivo("Participante.txt");
    Participante part;
    if (!arquivo) {
        std::cout << "Nenhum participante cadastrado." << std::endl;
        return;
    }

    std::cout << "===============================================" << std::endl;
    std::cout << "                 CREDENTIA+" << std::endl;
    std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "        LISTAR TODOS OS PARTICIPANTES        " << std::endl;
    std::cout << "===============================================" << std::endl;
    std::string linha;
    int contador = 0;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            contador++;
            std::cout << "\n-----------------------------------------------" << std::endl;
        }

        if (linha.find("ID:") == 0) {
            std::cout << "ID: " << linha.substr(3) << std::endl;
        }
        else if (linha.find("Nome:") == 0) {
            std::cout << "Nome: " << linha.substr(5) << std::endl;
        }
        else if (linha.find("CPF:") == 0) {
            std::cout << "CPF: " << linha.substr(4) << std::endl;
        }
        else if (linha.find("Email:") == 0) {
            std::cout << "Email: " << linha.substr(6) << std::endl;
        }
        else if (linha.find("InstituicaoID") == 0) {
            std::cout << "ID Instituição: " << part.trim(linha.substr(linha.find(":") + 1)) << std::endl;
        }
    }

    if (contador == 0) {
        std::cout << "Nenhum participante encontrado." << std::endl;
    }
    else {
        std::cout << "\n===============================================" << std::endl;
        std::cout << "TOTAL: " << contador << " PARTICIPANTE(S) ENCONTRADO(S)\n";
        std::cout << "===============================================" << std::endl;
    }

    arquivo.close();
}

void SistemaParticipantes::buscar() const {
    Participante::buscarPorCpf();
}

void SistemaParticipantes::remover() {
    Participante::removerPorCpf();
}

/*
	PARTE 5: A ALMA DA APLICAÇÃO - MENU PARTICIPANTE
    ====================================================
    Este código define a função mainParticipante(), que atua 
    como o menu principal e o loop de interface do usuário 
    para o gerenciamento de participantes. Ele cria um objeto 
    SistemaParticipantes para orquestrar as ações. A função 
    exibe um menu de opções (Cadastrar, Listar, Buscar, Remover, 
    Retornar) dentro de um loop do-while, que se repete até que o 
    usuário digite '0'. Um switch é usado para invocar o método 
    apropriado do objeto sistema (como sistema.cadastrar()) com 
    base na escolha do usuário. A função também inclui validação 
    de entrada para garantir que o usuário digite um número.

	Att. Igor Kramer
	Código Revisado!
*/

int mainParticipante() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    SistemaParticipantes sistema;
    int opcao;

    do {
        std::cout << "===============================================" << std::endl;
        std::cout << "                 CREDENTIA+" << std::endl;
        std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
        std::cout << "===============================================" << std::endl;
        std::cout << "           ÁREA DE PARTICIPANTES           " << std::endl;
        std::cout << "===============================================" << std::endl;
        std::cout << "1. Cadastrar participante" << std::endl;
        std::cout << "2. Listar participantes" << std::endl;
        std::cout << "3. Buscar participante por CPF" << std::endl;
        std::cout << "4. Remover participante por CPF" << std::endl;
        std::cout << "0. Retornar ao menu principal" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "               DIGITE UMA OPÇÃO                " << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;

        while (!(std::cin >> opcao)) {
            std::cout << "Opção inválida! Digite um número: ";
            std::cin.clear();
            limparBuffer();
        }

        system("cls");
        limparBuffer();

        switch (opcao) {
        case 1:
            sistema.cadastrar();
            break;
        case 2:
            sistema.listar();
            break;
        case 3:
            sistema.buscar();
            break;
        case 4:
            sistema.remover();
            break;
        case 0:
            std::cout << "\nRetornando ao menu principal...\n";
            break;
        default:
            std::cout << "\nOpção inválida!\n";
        }

        if (opcao != 0) {
            std::cout << "\nPressione Enter para continuar...";
            std::cin.get();
            system("cls");
        }
    } while (opcao != 0);

    return 0;
}

/*
    PARTE 6: Gerenciador de ID Global em Arquivo
	====================================================
    Este código gerencia um ID global auto-incrementado 
    para participantes, usando um arquivo (ex: "global_id_participante.txt"). 
    A função getGlId_Participante apenas lê o ID atual do arquivo, retornando 
    1 se o arquivo não existir. A função principal é updGlId_Participante, 
    que lê o ID atual (digamos, 'X') e depois reabre o arquivo para sobrescrevê-lo 
    com o valor incrementado ('X+1'). Crucialmente, esta função retorna o ID antigo 
    ('X'), garantindo que ele seja usado para o cadastro atual. O método 
    Participante::proximoId é um atalho que chama updGlId_Participante para obter o 
    próximo ID disponível.

	Att. Sistema Unificado de Arquivos
	Código Revisado!
*/

int getGlId_Participante(std::string nome_arq) {
    std::ifstream arq;
    int gl_id = 1;

    arq.open(nome_arq);
    if (arq.is_open()) {
        arq >> gl_id;
        arq.close();
    }
    else {
        std::cout << "Arquivo de ID global não encontrado.\n";
    }

    return gl_id;
}

int updGlId_Participante(std::string nome_arq) {
    std::fstream arq;
    int gl_id = 1;

    arq.open(nome_arq, std::ios::in);
    if (arq.is_open()) {
        arq >> gl_id;
        arq.close();
    }

    if (gl_id < 1) {
        gl_id = 1;
    }

    int proximoId = gl_id + 1;
    arq.open(nome_arq, std::ios::out);
    if (arq.is_open()) {
        arq << proximoId;
        arq.close();
    }

    return gl_id;
}

int Participante::proximoId() {
    return updGlId_Participante("global_id_participante.txt");
}

/*
    PARTE 7: LIMPEZA DE BUFFER
    ======================================================
    Este código define duas funções com o mesmo nome, limparBuffer, 
    mas em escopos diferentes. Uma é uma função global e a outra é 
    um método da classe Participante. Ambas têm exatamente a mesma 
    funcionalidade: limpar o buffer de entrada padrão (std::cin). 
    Elas usam a expressão idiomática std::cin.ignore(...) para 
    descartar o número máximo de caracteres do buffer até encontrar 
    (e descartar) um caractere de nova linha (\n). Isso é essencial 
    para prevenir erros ao misturar leituras formatadas (com >>) e 
    leituras de linha inteira (com getline).

	Att. Equipe Credentia+
	Código Revisado!
*/

void limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Participante::limparBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}