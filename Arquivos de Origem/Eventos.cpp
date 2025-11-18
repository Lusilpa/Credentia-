#include "Eventos.hpp"
#include "ValidadorCPF.hpp"
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

/*
	 Responsável: Luan Palma
	 sistema: Área de Eventos
	 github: lusilpa
*/

DadosEventos Dat_ev;
Entrada_evento entrada_ev;

using namespace std;

/*
     ========================================================
     CONSTRUTOR E DESTRUTOR
     ========================================================
     O construtor (Evento::Evento()) é executado quando um objeto 
     Evento é criado. Ele inicializa o array inscricoes_evento na 
     memória (heap) com uma capacidade inicial de 10 elementos e 
     define a quantidade atual como 0. Logo em seguida, ele chama 
     a função carregarInscricoesEventoArquivo() para preencher este 
     array com dados persistidos em disco.

     O destrutor (~Evento()) é chamado automaticamente quando o objeto 
     Evento é destruído. Sua única responsabilidade é liberar a memória 
     que foi alocada para o array inscricoes_evento usando delete[], 
     evitando vazamentos de memória.

     Att. Luan Palma
	 Código Revisado!
*/

Evento::Evento() {
    capacidade_inscricoes_evento = 10;
    quantidade_inscricoes_evento = 0;
    inscricoes_evento = new InscricaoEvento[capacidade_inscricoes_evento];
    carregarInscricoesEventoArquivo();
}

Evento::~Evento() {
    delete[] inscricoes_evento;
}

/*
     ========================================================
     FUNÇÕES AUXILIARES
     ========================================================
     Este código C++ define três métodos auxiliares para a classe 
     Evento. O primeiro é trim, uma função utilitária que remove 
     espaços em branco do início e do fim de uma string. O segundo, 
     buscarDetalhesParticipantePorID, abre o arquivo "Participante.txt", 
     procura por um id_participante específico e, se o encontrar, 
     preenche as variáveis de referência nome e instituicao com os 
     dados lidos do arquivo. O terceiro método, buscarNomeEventoPorID, 
     funciona de forma semelhante, mas lê o "Evento.txt" para encontrar 
     um id_evento e retornar o nome do evento como uma string.

	 Att. Equipe Credentia+
	 Código Revisado!
*/

string Evento::trim(const string& str) {
    const string WHITESPACE = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(WHITESPACE);
    if (start == string::npos) return "";
    size_t end = str.find_last_not_of(WHITESPACE);
    return str.substr(start, (end - start + 1));
}

bool Evento::buscarDetalhesParticipantePorID(int id_participante, string& nome, string& instituicao) {
    ifstream arquivo("Participante.txt");
    if (!arquivo) return false;

    string linha;
    bool dentroDoParticipante = false;
    int idAtual = -1;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            try {
                idAtual = stoi(trim(linha.substr(3)));
            }
            catch (...) {
                idAtual = -1;
            }

            if (idAtual == id_participante) {
                dentroDoParticipante = true;
            }
            else {
                dentroDoParticipante = false;
            }
        }
        else if (dentroDoParticipante) {
            if (linha.find("Nome:") == 0) {
                nome = trim(linha.substr(5));
            }
            else if (linha.find("Instituicao:") == 0) {
                instituicao = trim(linha.substr(12));
            }
        }
        else if (linha == "---") {
            if (dentroDoParticipante && idAtual == id_participante) {
                break;
            }
        }
    }

    arquivo.close();
    return !nome.empty();
}

string Evento::buscarNomeEventoPorID(int id_evento) {
    ifstream arquivo("Evento.txt");
    if (!arquivo) return "Evento Desconhecido";

    string linha;
    bool dentroDoEvento = false;
    string nomeEvento = "Evento Desconhecido";

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            int idAtual = -1;
            try {
                idAtual = stoi(trim(linha.substr(3)));
            }
            catch (...) {
                idAtual = -1;
            }

            if (idAtual == id_evento) {
                dentroDoEvento = true;
            }
            else {
                dentroDoEvento = false;
            }
        }
        else if (dentroDoEvento && linha.find("NOME:") == 0) {
            nomeEvento = trim(linha.substr(5));
            break;
        }
        else if (linha == "---" && dentroDoEvento) {
            break;
        }
    }

    arquivo.close();
    return nomeEvento;
}

/*
     ========================================================
     GERENCIAMENTO DE INSCRIÇÕES
     ========================================================
     Este código C++ gerencia o armazenamento de inscrições 
     (a ligação entre um id_evento e um id_participante). A 
     função carregarInscricoesEventoArquivo é usada para ler 
     o arquivo "InscricoesEvento.txt" e popular um array dinâmico 
     (inscricoes_evento) na memória RAM. Se este array em memória 
     ficar cheio, a função realocarInscricoesEvento é chamada para 
     dobrar sua capacidade, copiando os dados antigos. Para salvar 
     uma nova inscrição, salvarInscricaoEvento anexa (ios::app) o 
     novo par de IDs ao arquivo. Por fim, verificarInscricaoEventoExistente 
     varre o array em memória para checar se um participante já está inscrito.

     Att. Luan Palma
	 Código Revisado!
*/

void Evento::carregarInscricoesEventoArquivo() {
    ifstream arquivo("InscricoesEvento.txt");
    if (!arquivo) return;

    string linha;
    int id_evento = -1;
    int id_participante = -1;

    while (getline(arquivo, linha)) {
        if (linha.find("EVENTO:") == 0) {
            try {
                id_evento = stoi(trim(linha.substr(7)));
            }
            catch (...) {
                id_evento = -1;
            }
        }
        else if (linha.find("PARTICIPANTE:") == 0) {
            try {
                id_participante = stoi(trim(linha.substr(13)));
            }
            catch (...) {
                id_participante = -1;
            }
        }
        else if (linha == "---") {
            if (id_evento != -1 && id_participante != -1) {
                if (quantidade_inscricoes_evento >= capacidade_inscricoes_evento) {
                    realocarInscricoesEvento();
                }
                inscricoes_evento[quantidade_inscricoes_evento].id_evento = id_evento;
                inscricoes_evento[quantidade_inscricoes_evento].id_participante = id_participante;
                quantidade_inscricoes_evento++;
            }
            id_evento = -1;
            id_participante = -1;
        }
    }

    arquivo.close();
}

void Evento::realocarInscricoesEvento() {
    int novaCapacidade = capacidade_inscricoes_evento * 2;
    InscricaoEvento* novoArray = new InscricaoEvento[novaCapacidade];

    for (int i = 0; i < quantidade_inscricoes_evento; i++) {
        novoArray[i] = inscricoes_evento[i];
    }

    delete[] inscricoes_evento;
    inscricoes_evento = novoArray;
    capacidade_inscricoes_evento = novaCapacidade;
}

bool Evento::verificarInscricaoEventoExistente(int id_evento, int id_participante) {
    for (int i = 0; i < quantidade_inscricoes_evento; i++) {
        if (inscricoes_evento[i].id_evento == id_evento &&
            inscricoes_evento[i].id_participante == id_participante) {
            return true;
        }
    }
    return false;
}

void Evento::salvarInscricaoEvento(int id_evento, int id_participante) {
    ofstream arquivo("InscricoesEvento.txt", ios::app);
    if (arquivo) {
        arquivo << "EVENTO:" << id_evento << "\n";
        arquivo << "PARTICIPANTE:" << id_participante << "\n";
        arquivo << "---\n";
        arquivo.close();
    }
}

/*
     ========================================================
     CRUD DE EVENTOS
     ========================================================
     Este código C++ define o método Evento::CadastrarEvento, 
     uma função de console para registrar novos eventos. O 
     método coleta interativamente todos os dados (nome, tema, 
     datas, local, representante) e os armazena na variável de 
     membro Dat_ev. A função inclui um loop do-while que utiliza 
     ValidadorCPF::validar para garantir que o CPF do representante 
     seja válido antes de prosseguir. Após obter um ID único 
     (updGlobalid_evento), os dados são formatados e anexados 
     (ios::app) ao arquivo "Evento.txt", separados por "---". 
     As demais funções são "wrappers" que repassam chamadas para 
     suas implementações de lógica de negócios (LB_...).

	 Att. Sistema Universal de Arquivos
	 Código Revisado!
*/

void Evento::CadastrarEvento() {
    ofstream arquivo;
    string nomeArquivo = "Evento.txt";

    std::cout << "===============================================" << std::endl;
    std::cout << "               ADICIONAR NOVO EVENTO           " << std::endl;
    std::cout << "===============================================" << std::endl;

    std::cout << "Digite o nome do evento: ";
    getline(std::cin, Dat_ev.nomeEvento);
    system("cls");

    std::cout << "Digite o tema do evento: ";
    getline(std::cin, Dat_ev.TemaEvento);
    system("cls");

    std::cout << "Digite a data do inicio do evento (DD/MM/AAAA): ";
    getline(std::cin, Dat_ev.DataInicial);
    system("cls");

    std::cout << "Digite a data do final do evento (DD/MM/AAAA): ";
    getline(std::cin, Dat_ev.DataFim);
    system("cls");

    std::cout << "Digite o local do evento: ";
    getline(std::cin, Dat_ev.Local);
    system("cls");

    std::cout << "Digite a hora do evento (HH:MM): ";
    getline(std::cin, Dat_ev.Hora);
    system("cls");

    std::cout << "Digite a Instituição que está promovendo: ";
    getline(std::cin, Dat_ev.Instituicao_Promovedora);
    system("cls");

    std::cout << "Digite o nome do representante do evento: ";
    getline(std::cin, Dat_ev.Nome_Representante);
    system("cls");

    do {
        cout << "Digite o CPF do representante do evento: ";
        getline(cin, Dat_ev.CPF_Representante);

        string cpf_validar = trim(Dat_ev.CPF_Representante);

        if (ValidadorCPF::validar(cpf_validar)) {
            Dat_ev.CPF_Representante = cpf_validar;
            break;
        }
        else {
            cout << "CPF inválido. Tente novamente." << endl;
        }
    } while (true);

    system("cls");

    arquivo.open(nomeArquivo, ios::app);
    Dat_ev.ID_Evento = updGlobalid_evento("global_id_evento.txt");

    arquivo << "ID:" << Dat_ev.ID_Evento << "\n";
    arquivo << "NOME:" << Dat_ev.nomeEvento << "\n";
    arquivo << "TEMA:" << Dat_ev.TemaEvento << "\n";
    arquivo << "DATA_INICIO:" << Dat_ev.DataInicial << "\n";
    arquivo << "DATA_FIM:" << Dat_ev.DataFim << "\n";
    arquivo << "LOCAL:" << Dat_ev.Local << "\n";
    arquivo << "HORA:" << Dat_ev.Hora << "\n";
    arquivo << "INSTITUICAO:" << Dat_ev.Instituicao_Promovedora << "\n";
    arquivo << "REPRESENTANTE:" << Dat_ev.Nome_Representante << "\n";
    arquivo << "CPF_REPRESENTANTE:" << Dat_ev.CPF_Representante << "\n";
    arquivo << "---\n";
    arquivo.close();

    std::cout << "Evento cadastrado com os seguintes dados:" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "ID do Evento: " << Dat_ev.ID_Evento << std::endl;
    std::cout << "Nome do Evento: " << Dat_ev.nomeEvento << std::endl;
    std::cout << "Tema do Evento: " << Dat_ev.TemaEvento << std::endl;
    std::cout << "Data do inicio do Evento: " << Dat_ev.DataInicial << std::endl;
    std::cout << "Data final do Evento: " << Dat_ev.DataFim << std::endl;
    std::cout << "Local do Evento: " << Dat_ev.Local << std::endl;
    std::cout << "Hora do Evento: " << Dat_ev.Hora << std::endl;
    std::cout << "Instituição Promovedora: " << Dat_ev.Instituicao_Promovedora << std::endl;
    std::cout << "Nome do Representante: " << Dat_ev.Nome_Representante << std::endl;
    std::cout << "CPF do Representante: " << Dat_ev.CPF_Representante << std::endl;

    system("pause");
    system("cls");
    std::cout << "Novo evento adicionado com sucesso!" << std::endl;
}

void Evento::DadosEvento() {
    int id_busca;
    std::cout << "===============================================" << std::endl;
    std::cout << "               BUSCAR EVENTO POR ID" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Digite o ID do evento: ";
    std::cin >> id_busca;

    system("cls");
    BuscarEventoPorID(id_busca);
    system("pause");
    system("cls");
}

void Evento::ListarEventos() {
    LB_listarEventos();
}

void Evento::BuscarEventoPorID(int id) {
    LB_buscarEventoPorID(id);
}

void Evento::BuscarEventoPorNome(const string& nome) {
    LB_buscarEventoPorNome(nome);
}

void Evento::BuscarEventoPorInstituicao(const string& instituicao) {
    LB_buscarEventoPorInstituicao(instituicao);
}

bool Evento::RemoverEvento(int id) {
    return LB_removerEvento(id);
}

/*
     ========================================================
     LISTAGEM DE PARTICIPANTES
     ========================================================
     Este código C++ define os métodos da classe Evento para 
     listar todos os participantes inscritos em um evento específico. 
     A função principal, LB_listarParticipantesPorEvento, recebe um 
     id_evento e primeiro busca o nome desse evento para exibi-lo. 
     Em seguida, ela itera por um array em memória chamado inscricoes_evento 
     (que armazena todas as inscrições). Para cada inscrição que corresponde 
     ao ID do evento, a função usa o id_participante dessa inscrição para 
     buscar (buscarDetalhesParticipantePorID) o nome e a instituição do 
     participante em outro local (provavelmente o "Participante.txt"). 
     Por fim, os detalhes de cada participante encontrado são impressos no console.

     Att. Equipe Credentia+
	 Código Revisado!
*/

void Evento::ListarParticipantesDoEvento(int id) {
    LB_listarParticipantesPorEvento(id);
}

void Evento::LB_listarParticipantesPorEvento(int id_evento) {
    cout << "===============================================" << endl;
    cout << "      PARTICIPANTES DO EVENTO ID: " << id_evento << endl;
    cout << "===============================================" << endl;

    string nomeEvento = buscarNomeEventoPorID(id_evento);
    cout << "Evento: " << nomeEvento << endl << endl;

    int contador = 0;

    for (int i = 0; i < quantidade_inscricoes_evento; i++) {
        if (inscricoes_evento[i].id_evento == id_evento) {
            string nomeParticipante, instituicaoParticipante;
            if (buscarDetalhesParticipantePorID(inscricoes_evento[i].id_participante,
                nomeParticipante,
                instituicaoParticipante)) {
                contador++;
                cout << "Participante " << contador << ":" << endl;
                cout << "  ID: " << inscricoes_evento[i].id_participante << endl;
                cout << "  Nome: " << nomeParticipante << endl;
                cout << "  Instituição: " << instituicaoParticipante << endl;
                cout << "  -------------------------" << endl;
            }
        }
    }

    if (contador == 0) {
        cout << "Nenhum participante inscrito neste evento." << endl;
    }
    else {
        cout << "Total de participantes: " << contador << endl;
    }
    cout << "===============================================" << endl;
}

/*
     ========================================================
     A ESPINHA DORSAL DO CÓDIGO DE EVENTO - MENU PRINCIPAL
     ========================================================
	 O código a seguir define a função MainEvento(), que atua como o menu principal.

     Att. Luan Palma
	 Código Revisado!
     
*/

int MainEvento() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    Evento ev;
    int opcao;

    system("cls");

    do {
        std::cout << "===============================================" << std::endl;
        std::cout << "              CREDENTIA+" << std::endl;
        std::cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << std::endl;
        std::cout << "===============================================" << std::endl;
        std::cout << "              ÁREA DE EVENTOS                  " << std::endl;
        std::cout << "===============================================" << std::endl;
        std::cout << "1. CREDENCIAMENTO AUTÔNOMO" << std::endl;
        std::cout << "2. ADICIONAR NOVO EVENTO" << std::endl;
        std::cout << "3. BUSCAR EVENTO POR ID" << std::endl;
        std::cout << "4. LISTAR TODOS OS EVENTOS" << std::endl;
        std::cout << "5. BUSCAR EVENTO POR NOME" << std::endl;
        std::cout << "6. BUSCAR EVENTO POR INSTITUIÇÃO" << std::endl;
        std::cout << "7. REMOVER EVENTO" << std::endl;
        std::cout << "8. LISTAR PARTICIPANTES DO EVENTO" << std::endl;
        std::cout << "0. RETORNAR AO MENU INICIAL" << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;
        std::cout << "               DIGITE UMA OPÇÃO                " << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;

        while (!(cin >> opcao)) {
            cout << "Opcao invalida! Digite um numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");

        switch (opcao) {
        case 1:
            ev.CredenciamentoAutonomo();
            break;
        case 2:
            ev.CadastrarEvento();
            break;
        case 3: {
            int id_busca;
            std::cout << "Digite o ID do evento: ";
            while (!(std::cin >> id_busca)) {
                std::cout << "ID invalido! Digite um numero: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ev.BuscarEventoPorID(id_busca);
            system("pause");
            system("cls");
            break;
        }
        case 4:
            ev.ListarEventos();
            system("pause");
            system("cls");
            break;
        case 5: {
            std::string nome_busca;
            std::cout << "Digite o nome do evento: ";
            getline(std::cin, nome_busca);
            ev.BuscarEventoPorNome(nome_busca);
            system("pause");
            system("cls");
            break;
        }
        case 6: {
            std::string instituicao_busca;
            std::cout << "Digite o nome da instituição: ";
            getline(std::cin, instituicao_busca);
            ev.BuscarEventoPorInstituicao(instituicao_busca);
            system("pause");
            system("cls");
            break;
        }
        case 7: {
            int id_remover;
            std::cout << "Digite o ID do evento a ser removido: ";
            while (!(std::cin >> id_remover)) {
                std::cout << "ID invalido! Digite um numero: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (ev.RemoverEvento(id_remover)) {
                std::cout << "Evento removido com sucesso!" << std::endl;
            }
            else {
                std::cout << "Evento não encontrado!" << std::endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 8: {
            int id_evento;
            cout << "===============================================" << endl;
            cout << "      LISTAR PARTICIPANTES POR EVENTO" << endl;
            cout << "===============================================" << endl;
            cout << "Digite o ID do evento: ";
            while (!(cin >> id_evento)) {
                cout << "ID invalido! Digite um numero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            ev.ListarParticipantesDoEvento(id_evento);
            system("pause");
            system("cls");
            break;
        }
        case 0:
            cout << "Retornando ao menu inicial..." << endl;
            break;
        default:
            cout << "Opção inválida. Tente novamente." << endl;
            system("pause");
            system("cls");
            break;
        }

    } while (opcao != 0);

    return 0;
}

/*
     ========================================================
     CREDENCIAMENTO AUTÔNOMO
     ========================================================
	 Código está direcionado para permitir o credenciamento 
	 no evento através do CPF do participante.

     Att. Luan Palma
	 Código Revisado!
*/

bool Evento::buscarParticipantePorCPF(const string& cpf, int& idParticipante, string& nomeParticipante, string& instituicaoParticipante) {
    ifstream arquivo("Participante.txt");
    if (!arquivo) {
        cout << "Erro: Arquivo Participante.txt não encontrado!" << endl;
        return false;
    }

    string linha;
    bool dentroDoParticipante = false;
    bool cpfEncontrado = false;
    string cpfBuscado = trim(cpf);

    idParticipante = -1;
    nomeParticipante = "";
    instituicaoParticipante = "";
    int temp_id = -1;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            try {
                temp_id = stoi(trim(linha.substr(3)));
            }
            catch (...) {
                temp_id = -1;
            }
        }
        else if (linha.find("CPF:") == 0) {
            std::string cpfArquivo = trim(linha.substr(4));

            if (cpfArquivo == cpfBuscado) {
                cpfEncontrado = true;
                dentroDoParticipante = true;
                idParticipante = temp_id;
            }
            else {
                dentroDoParticipante = false;
            }
        }
        else if (dentroDoParticipante && cpfEncontrado) {
            if (linha.find("Nome:") == 0) {
                nomeParticipante = trim(linha.substr(5));
            }
            else if (linha.find("Instituicao:") == 0) {
                instituicaoParticipante = trim(linha.substr(12));
            }
        }
        else if (linha == "---") {
            if (cpfEncontrado) break;
            dentroDoParticipante = false;
            temp_id = -1;
        }
    }
    arquivo.close();

    return cpfEncontrado;
}

bool Evento::verificarFormatoArquivoParticipantes() {
    ifstream arquivo("Participante.txt");
    if (!arquivo) return false;

    string linha;
    bool temFormatoCorreto = false;

    while (getline(arquivo, linha)) {
        string linhaLimpa = trim(linha);
        if (linhaLimpa.find("CPF:") == 0 || linhaLimpa.find("Nome:") == 0 || linhaLimpa.find("Instituicao:") == 0) {
            temFormatoCorreto = true;
            break;
        }
    }

    arquivo.close();
    return temFormatoCorreto;
}

void Evento::CredenciamentoAutonomo() {
    Entrada_evento temp_entrada;

    std::cout << std::endl << "====================================================" << std::endl;
    std::cout << "                      Credentia+" << std::endl;
    std::cout << "     Credenciamento e Gestão para Eventos Acadêmicos" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "Bem Vindo ao Credenciamento Autônomo. Leia as regras." << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "/ PARA ENCERRAR DIGITE O CPF DO RESPONSÁVEL PELO EVENTO;" << std::endl;
    std::cout << "/ Mantenha este terminal aberto durante todo o evento;" << std::endl;
    std::cout << "/ Auxilie os participantes no credenciamento;" << std::endl;
    std::cout << "/ Se o participante não for encontrado, realize o cadastro manualmente;" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "1 - PARA INICIAR O CREDENCIAMENTO;" << std::endl;
    std::cout << "2 - PARA RETORNAR AO MENU DE EVENTOS;" << std::endl;
    std::cout << "=====================================================" << std::endl;

    do {
        std::string entrada;
        std::getline(std::cin, entrada);
        temp_entrada.usuario = trim(entrada);

        if (temp_entrada.usuario == "2") {
            system("cls");
            return;
        }
        if (temp_entrada.usuario != "1")
            cout << "Tente novamente ou digite 2 para retornar ao menu." << endl;
    } while (temp_entrada.usuario != "1");

    system("cls");

    if (!verificarFormatoArquivoParticipantes()) {
        cout << "AVISO: Arquivo de participantes não encontrado ou formato incompatível." << endl;
        cout << "O credenciamento funcionará, mas pode não encontrar participantes." << endl;
        system("pause");
    }

    std::cout << "=== EVENTOS DISPONÍVEIS PARA CREDENCIAMENTO ===" << std::endl;
    LB_listarEventos();

    ifstream arqEventosCheck("Evento.txt");
    if (!arqEventosCheck || arqEventosCheck.peek() == ifstream::traits_type::eof()) {
        cout << "\nNenhum evento cadastrado. Retornando ao menu..." << endl;
        arqEventosCheck.close();
        system("pause");
        system("cls");
        return;
    }
    arqEventosCheck.close();

    int id_evento = 0;
    std::cout << "\nDigite o ID do evento: ";
    while (!(std::cin >> id_evento) || id_evento <= 0) {
        std::cout << "ID invalido! Digite um numero positivo: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    system("cls");
    std::cout << "Iniciando o credenciamento para o evento ID: " << id_evento << std::endl;

    ifstream arquivo("Evento.txt");
    string linha;
    bool eventoEncontrado = false;
    string cpfRepresentante = "";
    string nomeEvento = "";

    if (arquivo.is_open()) {
        while (getline(arquivo, linha)) {
            if (linha.find("ID:") == 0) {
                int idArquivo = 0;
                try {
                    idArquivo = stoi(trim(linha.substr(3)));
                }
                catch (...) {
                    idArquivo = -1;
                }

                if (idArquivo == id_evento) {
                    eventoEncontrado = true;
                }
                else {
                    eventoEncontrado = false;
                }
            }
            else if (eventoEncontrado) {
                if (linha.find("CPF_REPRESENTANTE:") == 0) {
                    cpfRepresentante = trim(linha.substr(18));
                }
                else if (linha.find("NOME:") == 0) {
                    nomeEvento = trim(linha.substr(5));
                }
                else if (linha == "---") {
                    if (eventoEncontrado) break;
                }
            }
        }
        arquivo.close();
    }

    if (!eventoEncontrado || cpfRepresentante.empty()) {
        cout << "Evento não encontrado ou CPF do representante não cadastrado para este evento." << endl;
        system("pause");
        system("cls");
        return;
    }

    std::cout << "Evento: " << nomeEvento << std::endl;
    std::cout << "Para encerrar, digite o CPF do representante." << std::endl;
    std::cout << "\nPressione qualquer tecla para iniciar..." << std::endl;
    system("pause");
    system("cls");

    int participantesCredenciados = 0;

    do {
        std::cout << "====================================================" << std::endl;
        std::cout << "           CREDENCIAMENTO - EVENTO: " << nomeEvento << std::endl;
        std::cout << "====================================================" << std::endl;
        std::cout << "Participantes credenciados: " << participantesCredenciados << std::endl;
        std::cout << "Digite o CPF do participante (ou do representante para sair): ";

        std::string cpfInput;
        std::getline(std::cin, cpfInput);
        std::string cpfLimpo = trim(cpfInput);

        if (cpfLimpo == cpfRepresentante) {
            cout << "\nCPF do representante detectado. Encerrando credenciamento..." << endl;
            break;
        }

        string nomeParticipante, instituicaoParticipante;
        int idParticipante;

        if (buscarParticipantePorCPF(cpfLimpo, idParticipante, nomeParticipante, instituicaoParticipante)) {
            if (verificarInscricaoEventoExistente(id_evento, idParticipante)) {
                cout << "\nATENÇÃO: PARTICIPANTE JÁ CREDENCIADO!" << endl;
                cout << "Nome: " << (nomeParticipante.empty() ? "(Nao informado)" : nomeParticipante) << endl;
                cout << "Instituição: " << (instituicaoParticipante.empty() ? "(Nao informada)" : instituicaoParticipante) << endl;
            }
            else {
                if (quantidade_inscricoes_evento >= capacidade_inscricoes_evento) {
                    realocarInscricoesEvento();
                }
                inscricoes_evento[quantidade_inscricoes_evento].id_evento = id_evento;
                inscricoes_evento[quantidade_inscricoes_evento].id_participante = idParticipante;
                quantidade_inscricoes_evento++;

                salvarInscricaoEvento(id_evento, idParticipante);

                participantesCredenciados++;
                cout << "\nCREDENCIAMENTO REALIZADO COM SUCESSO!" << endl;
                cout << "Nome: " << (nomeParticipante.empty() ? "(Nao informado)" : nomeParticipante) << endl;
                cout << "Instituição: " << (instituicaoParticipante.empty() ? "(Nao informada)" : instituicaoParticipante) << endl;
                cout << "Evento: " << nomeEvento << endl;
            }
        }
        else {
            cout << "\nPARTICIPANTE NÃO ENCONTRADO!" << endl;
            cout << "CPF " << cpfLimpo << " não está cadastrado no sistema." << endl;
            cout << "Oriente o participante a se cadastrar na área de participantes." << endl;
        }

        cout << "\nPressione qualquer tecla para continuar..." << endl;
        system("pause");
        system("cls");
    } while (true);

    std::cout << "\n====================================================" << std::endl;
    std::cout << "           CREDENCIAMENTO ENCERRADO" << std::endl;
    std::cout << "====================================================" << std::endl;
    std::cout << "Evento: " << nomeEvento << std::endl;
    std::cout << "Total de participantes credenciados: " << participantesCredenciados << std::endl;
    std::cout << "====================================================" << std::endl;

    system("pause");
    system("cls");
}

/*
     ========================================================
     FUNÇÕES DE ARQUIVO
     ========================================================
     Este código define dois métodos na classe Evento para 
     gerenciar um ID global persistente em um arquivo. A função 
     getGlobalID_evento atua como um leitor: ela abre o arquivo 
     especificado (ex: "global_id_evento.txt") e retorna o ID 
     numérico que está armazenado lá, ou 0 se o arquivo não for encontrado.

     A função updGlobalid_evento é a atualizadora. Ela primeiro chama 
     getGlobalID_evento para obter o valor atual, incrementa esse valor 
     (globalId++), e então reabre o arquivo em modo de escrita (ofstream), 
     o que apaga o conteúdo antigo e salva o novo ID incrementado. Por fim, 
     a função retorna este novo ID já atualizado.

	 Att. Sistema Universal de Arquivos - SUA
	 Código Revisado!
*/

int Evento::getGlobalID_evento(std::string nomeArq) {
    std::ifstream arq;
    int globalId = 0;

    arq.open(nomeArq);
    if (arq.is_open()) {
        arq >> globalId;
        arq.close();
    }

    return globalId;
}

int Evento::updGlobalid_evento(std::string nomeArq) {
    int globalId = getGlobalID_evento(nomeArq);
    globalId++;

    ofstream arq(nomeArq);
    if (arq.is_open()) {
        arq << globalId;
        arq.close();
    }
    else {
        cout << "Erro: Nao foi possivel atualizar o arquivo de ID global.";
    }

    return globalId;
}

/*
     ========================================================
     FUNÇÕES LB
     ========================================================
     Este código define os métodos de lógica de negócios (LB) 
     para a classe Evento, focados na manipulação direta do arquivo 
     "Evento.txt". A função LB_listarEventos lê e exibe um resumo de 
     todos os registros do arquivo. As funções de busca (LB_buscarEventoPorID, 
     LB_buscarEventoPorNome, LB_buscarEventoPorInstituicao) implementam a 
     leitura do arquivo para encontrar e exibir eventos que correspondam a 
     um ID exato ou a substrings (sem diferenciar maiúsculas/minúsculas) de 
     nome ou instituição. Por fim, LB_removerEvento implementa a exclusão de 
     um evento por ID, utilizando a estratégia de "arquivo temporário": ela 
     copia todos os outros eventos para "temp.txt" e depois substitui o "Evento.txt" original.

	 Att. Sistema Universal de Arquivos - SUA
     Código Revisado!
*/

void Evento::LB_listarEventos() {
    std::ifstream arquivo("Evento.txt");
    if (!arquivo) {
        cout << "Nenhum evento cadastrado.\n";
        return;
    }

    std::cout << "\n=== LISTA DE EVENTOS CADASTRADOS ===\n";
    std::string linha;
    int contador = 0;

    while (getline(arquivo, linha)) {
        if (trim(linha).empty()) continue;

        if (linha.find("ID:") == 0) {
            contador++;
            std::cout << "\n--- Evento " << contador << " ---";
            std::cout << "\nID: " << trim(linha.substr(3)) << "\n";
        }
        else if (linha.find("NOME:") == 0) {
            cout << "Nome: " << trim(linha.substr(5)) << "\n";
        }
        else if (linha.find("TEMA:") == 0) {
            cout << "Tema: " << trim(linha.substr(5)) << "\n";
        }
        else if (linha.find("DATA_INICIO:") == 0) {
            cout << "Data Início: " << trim(linha.substr(12)) << "\n";
        }
        else if (linha.find("DATA_FIM:") == 0) {
            cout << "Data Fim: " << trim(linha.substr(9)) << "\n";
        }
        else if (linha.find("LOCAL:") == 0) {
            cout << "Local: " << trim(linha.substr(6)) << "\n";
        }
        else if (linha.find("HORA:") == 0) {
            cout << "Hora: " << trim(linha.substr(5)) << "\n";
        }
        else if (linha.find("INSTITUICAO:") == 0) {
            cout << "Instituição: " << trim(linha.substr(12)) << "\n";
        }
        else if (linha.find("REPRESENTANTE:") == 0) {
            cout << "Representante: " << trim(linha.substr(14)) << "\n";
        }
        else if (linha.find("CPF_REPRESENTANTE:") == 0) {
            cout << "CPF Representante: " << trim(linha.substr(18)) << "\n";
        }
    }

    if (contador == 0) {
        std::cout << "Nenhum evento encontrado.\n";
    }
    else {
        std::cout << "\nTotal: " << contador << " evento(s)\n";
    }

    arquivo.close();
}

void Evento::LB_buscarEventoPorID(int id) {
    ifstream arquivo("Evento.txt");
    if (!arquivo) {
        cout << "Arquivo de eventos não encontrado!\n";
        return;
    }

    string linha;
    bool encontrou = false;
    bool dentroDoEvento = false;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            int eventoAtualId = -1;
            try {
                eventoAtualId = std::stoi(trim(linha.substr(3)));
            }
            catch (...) {}

            if (eventoAtualId == id) {
                encontrou = true;
                dentroDoEvento = true;
                std::cout << "\n=== EVENTO ENCONTRADO ===\n";
                std::cout << "ID: " << eventoAtualId << "\n";
            }
            else {
                dentroDoEvento = false;
            }
        }
        else if (dentroDoEvento) {
            if (linha.find("NOME:") == 0) {
                cout << "Nome: " << trim(linha.substr(5)) << "\n";
            }
            else if (linha.find("TEMA:") == 0) {
                cout << "Tema: " << trim(linha.substr(5)) << "\n";
            }
            else if (linha.find("DATA_INICIO:") == 0) {
                cout << "Data Início: " << trim(linha.substr(12)) << "\n";
            }
            else if (linha.find("DATA_FIM:") == 0) {
                cout << "Data Fim: " << trim(linha.substr(9)) << "\n";
            }
            else if (linha.find("LOCAL:") == 0) {
                cout << "Local: " << trim(linha.substr(6)) << "\n";
            }
            else if (linha.find("HORA:") == 0) {
                cout << "Hora: " << trim(linha.substr(5)) << "\n";
            }
            else if (linha.find("INSTITUICAO:") == 0) {
                cout << "Instituição: " << trim(linha.substr(12)) << "\n";
            }
            else if (linha.find("REPRESENTANTE:") == 0) {
                cout << "Representante: " << trim(linha.substr(14)) << "\n";
            }
            else if (linha.find("CPF_REPRESENTANTE:") == 0) {
                cout << "CPF Representante: " << trim(linha.substr(18)) << "\n";
            }
            else if (linha == "---") {
                std::cout << "===============================================" << std::endl;
                if (encontrou) break;
            }
        }
    }

    if (!encontrou) {
        std::cout << "\nEvento com ID " << id << " não encontrado.\n";
    }

    arquivo.close();
}

void Evento::LB_buscarEventoPorNome(string nomeProcurado) {
    ifstream arquivo("Evento.txt");
    if (!arquivo) {
        cout << "Arquivo de eventos não encontrado!\n";
        return;
    }

    string linha;
    bool encontrou = false;

    std::string idAtual, nomeAtual, temaAtual, dataInicioAtual, dataFimAtual, localAtual, horaAtual, instituicaoAtual;

    string nomeProcuradoLower = trim(nomeProcurado);
    transform(nomeProcuradoLower.begin(), nomeProcuradoLower.end(), nomeProcuradoLower.begin(), ::tolower);

    std::cout << "===============================================" << std::endl;
    std::cout << "        RESULTADOS DA BUSCA POR NOME         " << std::endl;
    std::cout << "===============================================" << std::endl;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            idAtual = trim(linha.substr(3));
            nomeAtual = ""; temaAtual = ""; dataInicioAtual = ""; dataFimAtual = ""; localAtual = ""; horaAtual = ""; instituicaoAtual = "";
        }
        else if (linha.find("NOME:") == 0) {
            nomeAtual = trim(linha.substr(5));
        }
        else if (linha.find("TEMA:") == 0) {
            temaAtual = trim(linha.substr(5));
        }
        else if (linha.find("DATA_INICIO:") == 0) {
            dataInicioAtual = trim(linha.substr(12));
        }
        else if (linha.find("DATA_FIM:") == 0) {
            dataFimAtual = trim(linha.substr(9));
        }
        else if (linha.find("LOCAL:") == 0) {
            localAtual = trim(linha.substr(6));
        }
        else if (linha.find("HORA:") == 0) {
            horaAtual = trim(linha.substr(5));
        }
        else if (linha.find("INSTITUICAO:") == 0) {
            instituicaoAtual = trim(linha.substr(12));
        }
        else if (linha == "---") {
            if (!nomeAtual.empty()) {
                string nomeAtualLower = nomeAtual;
                transform(nomeAtualLower.begin(), nomeAtualLower.end(), nomeAtualLower.begin(), ::tolower);

                if (nomeAtualLower.find(nomeProcuradoLower) != std::string::npos) {
                    encontrou = true;
                    std::cout << "\n=== EVENTO ENCONTRADO ===\n";
                    std::cout << "ID: " << idAtual << "\n";
                    std::cout << "Nome: " << nomeAtual << "\n";
                    std::cout << "Tema: " << temaAtual << "\n";
                    std::cout << "Data Início: " << dataInicioAtual << "\n";
                    std::cout << "Data Fim: " << dataFimAtual << "\n";
                    std::cout << "Local: " << localAtual << "\n";
                    std::cout << "Hora: " << horaAtual << "\n";
                    std::cout << "Instituição: " << instituicaoAtual << "\n";
                    std::cout << "---------------------------\n";
                }
            }
        }
    }

    if (!encontrou) {
        std::cout << "\nNenhum evento encontrado com o nome: " << nomeProcurado << "\n";
    }

    arquivo.close();
}

void Evento::LB_buscarEventoPorInstituicao(string instituicaoProcurada) {
    ifstream arquivo("Evento.txt");
    if (!arquivo) {
        cout << "Arquivo de eventos não encontrado!\n";
        return;
    }

    string linha;
    bool encontrou = false;
    int contador = 0;
    string idAtual, nomeAtual, temaAtual, dataInicioAtual, instituicaoAtual;

    string instituicaoProcuradaLower = trim(instituicaoProcurada);
    transform(instituicaoProcuradaLower.begin(), instituicaoProcuradaLower.end(), instituicaoProcuradaLower.begin(), ::tolower);

    std::cout << "\n=== EVENTOS DA INSTITUIÇÃO: " << instituicaoProcurada << " ===\n";

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            idAtual = trim(linha.substr(3));
            nomeAtual = ""; temaAtual = ""; dataInicioAtual = ""; instituicaoAtual = "";
        }
        else if (linha.find("NOME:") == 0) {
            nomeAtual = trim(linha.substr(5));
        }
        else if (linha.find("TEMA:") == 0) {
            temaAtual = trim(linha.substr(5));
        }
        else if (linha.find("DATA_INICIO:") == 0) {
            dataInicioAtual = trim(linha.substr(12));
        }
        else if (linha.find("INSTITUICAO:") == 0) {
            instituicaoAtual = trim(linha.substr(12));
        }
        else if (linha == "---") {
            if (!instituicaoAtual.empty()) {
                string instituicaoAtualLower = instituicaoAtual;
                transform(instituicaoAtualLower.begin(), instituicaoAtualLower.end(), instituicaoAtualLower.begin(), ::tolower);

                if (instituicaoAtualLower.find(instituicaoProcuradaLower) != std::string::npos) {
                    encontrou = true;
                    contador++;
                    std::cout << "\n--- Evento " << contador << " ---";
                    std::cout << "\nID: " << idAtual << "\n";
                    std::cout << "Nome: " << nomeAtual << "\n";
                    std::cout << "Tema: " << temaAtual << "\n";
                    std::cout << "Data Início: " << dataInicioAtual << "\n";
                    std::cout << "Instituição: " << instituicaoAtual << "\n";
                }
            }
        }
    }

    if (!encontrou) {
        std::cout << "Nenhum evento encontrado da instituição: " << instituicaoProcurada << "\n";
    }
    else {
        std::cout << "\nTotal encontrado: " << contador << " evento(s)\n";
    }

    arquivo.close();
}

bool Evento::LB_removerEvento(int id) {
    ifstream arquivoEntrada("Evento.txt");
    ofstream arquivoSaida("temp.txt");
    string linha;
    bool encontrou = false;
    bool pularBloco = false;

    if (!arquivoEntrada.is_open()) {
        cout << "Arquivo de eventos não encontrado!\n";
        return false;
    }

    if (!arquivoSaida.is_open()) {
        cout << "Erro ao criar arquivo temporário!\n";
        return false;
    }

    while (getline(arquivoEntrada, linha)) {
        if (linha.find("ID:") == 0) {
            pularBloco = false;
            int currentId = -1;
            try {
                currentId = std::stoi(trim(linha.substr(3)));
            }
            catch (...) {}

            if (currentId == id) {
                encontrou = true;
                pularBloco = true;
            }
        }

        if (linha == "---") {
            if (pularBloco) {
                pularBloco = false;
                continue;
            }
        }

        if (!pularBloco) {
            if (!trim(linha).empty()) {
                arquivoSaida << linha << "\n";
            }
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();

    if (encontrou) {
        remove("Evento.txt");
        rename("temp.txt", "Evento.txt");
    }
    else {
        remove("temp.txt");
    }

    return encontrou;
}