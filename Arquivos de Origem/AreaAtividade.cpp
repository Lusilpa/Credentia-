#include "AreaAtividade.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>

using namespace std;
AreaAtividades gestor;

/*
      Responsável: Luan Palma
      sistema: Area de Atividades
      github: lusilpa
*/


/*
    MAIN ATIVIDADE - CREDENTIA+
    ==================================================
    A função mainAtividade exibe um menu principal em loop,
    permitindo ao usuário escolher entre CRUD de atividades
    (Cadastrar, Listar, Buscar, Excluir) ou entrar na "Gestão
    de Pessoas". As escolhas do usuário são passadas para a
    função tratamentodeentradas, que usa um switch para rotear
    a opção, chamando funções auxiliares ou métodos de um objeto gestor.

    Att. Equipe Credentia+
    Código Corrigido!
*/

int mainAtividade() {

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int opcao;

    do {
        system("cls");
        cout << "===============================================" << endl;
        cout << "             CREDENTIA+" << endl;
        cout << "CREDENCIAMENTO E GESTÃO PARA EVENTOS ACADÊMICOS" << endl;
        cout << "===============================================" << endl;
        cout << "           GESTÃO DE ATIVIDADES" << endl;
        cout << "===============================================" << endl;
        cout << "1. CADASTRAR ATIVIDADE" << endl;
        cout << "2. LISTAR ATIVIDADES" << endl;
        cout << "3. BUSCAR ATIVIDADE" << endl;
        cout << "4. EXCLUIR ATIVIDADE" << endl;
        cout << "5. GESTÃO DE PESSOAS" << endl;
        cout << "0. RETORNAR AO MENU INICIAL" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "               DIGITE UMA OPÇÃO" << endl;
        cout << "-----------------------------------------------" << endl;

        while (!(cin >> opcao)) {
            cout << "Opcao invalida! Digite um numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // CORREÇÃO 3: Passamos o 'gestor' para o handler
        tratamentodeentradas(opcao);

    } while (opcao != 0);

    return 0;
}

/*
    GESTÃO DE PESSOAS - CREDENTIA+
    ==================================================
    A opção "Gestão de Pessoas" (5) chama o sub-menu MainParticipantes,
    que lida com check-in, cancelamento de inscrição e listagem de
    participantes/lista de espera. As funções ExcluirAtividade e ListarInscritos
    são procedimentos auxiliares que solicitam um ID ao usuário e, em seguida,
    executam a ação correspondente usando o objeto gestor.

    Att. Equipe Credentia+
    Código Corrigido!
*/

int MainParticipantes() {
    int opcao;

    do {
        system("cls");
        cout << "===============================================" << endl;
        cout << "             CREDENTIA+" << endl;
        cout << "           GESTÃO DE PESSOAS (SUB-MENU)" << endl;
        cout << "===============================================" << endl;

        // CORREÇÃO 4: Menu renumerado para 1-4 (mais limpo)
        cout << "1. REALIZAR CHECK-IN (Inscrever)" << endl;
        cout << "2. LISTAR LISTA DE ESPERA" << endl;
        cout << "3. LISTAR INSCRITOS POR ATIVIDADE" << endl;
        cout << "4. CANCELAR INSCRIÇÃO" << endl;
        cout << "0. RETORNAR AO MENU PRINCIPAL" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "               DIGITE UMA OPÇÃO" << endl;
        cout << "-----------------------------------------------" << endl;

        while (!(cin >> opcao)) {
            cout << "Opcao invalida! Digite um numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");

        // CORREÇÃO 5: Switch agora usa os casos 1-4
        switch (opcao) {
        case 1: { // Era caso 1 no seu código, mas opção 5 no menu
            string cpf_participante;
            int id_atividade;

            cout << "===============================================" << endl;
            cout << "           REALIZAR CHECK-IN" << endl;
            cout << "===============================================" << endl;

            cout << "Digite o CPF do participante (apenas números): ";
            cin >> cpf_participante;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Digite o ID da atividade: ";
            while (!(cin >> id_atividade)) {
                cout << "ID invalido! Digite um numero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            gestor.fazerCheckin(cpf_participante, id_atividade); // Usa o 'gestor' passado
            system("pause");
            break;
        }
        case 2: // Era caso 2, mas opção 6
            gestor.listarListaEspera(); // Usa o 'gestor' passado
            break;

        case 3: { // Era caso 3, mas opção 7
            ListarInscritos(); // Chama a função auxiliar
            break;
        }
        case 4: // Era caso 4, mas opção 8
            gestor.cancelarInscricao(); // Usa o 'gestor' passado
            break;

        case 0:
            cout << "Retornando ao menu principal..." << endl;
            break;

        default:
            cout << "Opção inválida. Tente novamente." << endl;
            system("PAUSE");
            break;
        }

    } while (opcao != 0);

    return 0;
}

// === Procedimentos Auxiliares ===

void ExcluirAtividade() {
    int id_remover;
    cout << "===============================================" << endl;
    cout << "           EXCLUIR ATIVIDADE" << endl;
    cout << "===============================================" << endl;
    cout << "Digite o ID da atividade a ser excluída: ";

    while (!(cin >> id_remover)) {
        cout << "ID invalido! Digite um numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (gestor.ExcluirAtividade(id_remover)) { // Usa o 'gestor' passado
        cout << "✅ ATIVIDADE EXCLUÍDA COM SUCESSO!" << endl;
    }
    else {
        cout << "❌ ATIVIDADE NÃO ENCONTRADA!" << endl;
    }
    system("PAUSE");
}

void ListarInscritos() {
    // CORREÇÃO 6: REMOVIDO o 'AreaAtividades gestor;' local

    int id_atividade;
    cout << "===============================================" << endl;
    cout << "       LISTAR INSCRITOS POR ATIVIDADE" << endl;
    cout << "===============================================" << endl;
    cout << "Digite o ID da atividade: ";

    while (!(cin >> id_atividade)) {
        cout << "ID invalido! Digite um numero: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    gestor.listarParticipantesPorAtividade(id_atividade); // Usa o 'gestor' passado
}

void tratamentodeentradas(int opcao) {

    system("cls");

    switch (opcao) {
    case 1:
        gestor.CadastrarAtividade(); // Usa o 'gestor' passado
        break;
    case 2:
        gestor.ListarAtividade(); // Usa o 'gestor' passado
        break;
    case 3:
        gestor.BuscarAtividade(); // Usa o 'gestor' passado
        break;
    case 4:
        ExcluirAtividade(); // Passa o 'gestor' para a função auxiliar
        break;
    case 5:
        MainParticipantes(); // Passa o 'gestor' para o sub-menu
        break;

    case 0:
        cout << "Retornando ao menu inicial..." << endl;
        break;
    default:
        cout << "Opção inválida. Tente novamente." << endl;
        system("PAUSE");
        break;
    }
}

/*
   ===================================
   PARTE 1: CONSTRUTOR E DESTRUTOR
   ===================================
   O construtor AreaAtividades::AreaAtividades() 
   aloca memória dinamicamente para os arrays atividades, 
   lista_espera e inscricoes. Em seguida, ele chama três 
   funções (carregar...Arquivo()) para preencher esses 
   arrays com dados de arquivos. O destrutor 
   AreaAtividades::~AreaAtividades() faz a operação inversa, 
   liberando a memória alocada. Ele usa delete[] em cada um 
   dos três arrays. Essas funções garantem o gerenciamento 
   correto da memória (alocação e liberação) para os dados de atividades.

   att. Luan Palma
   Código Revisado!
*/
AreaAtividades::AreaAtividades() {
    atividades = new DadosAtividades[capacidade_atividades];
    lista_espera = new InscricaoListaEspera[capacidade_lista_espera];
    inscricoes = new Inscricao[capacidade_inscricoes];

    carregarAtividadesArquivo();
    carregarListaEsperaArquivo();
    carregarInscricoesArquivo();
}

AreaAtividades::~AreaAtividades() {
    delete[] atividades;
    delete[] lista_espera;
    delete[] inscricoes;
}

// === CARREGAR DADOS DOS ARQUIVOS ===

/*
    =============================================
    PARTE 2: DADOS DE ARQUIVOS
    =============================================
    O código implementa três funções para carregar 
    dados de arquivos texto: uma para atividades, 
    outra para lista de espera e uma para inscrições. 
    Cada função abre seu respectivo arquivo, processa 
    as linhas identificando campos específicos através 
    de prefixos como "ID:", "NOME:" ou "PARTICIPANTE:". 
    Os registros são separados por delimitadores "---" e 
    os dados são armazenados em estruturas temporárias. 
    Quando um registro completo é identificado, ele é 
    adicionado ao array correspondente, com realocação 
    automática se necessário. Finalmente, os arquivos são 
    fechados após todo o processamento, garantindo o 
    carregamento completo dos dados persistidos.

    Att. Equipe Credentia+
    Código Revisado!
*/
void AreaAtividades::carregarAtividadesArquivo() {
    ifstream arquivo("atividades.txt");
    if (!arquivo) return;

    string linha;
    DadosAtividades temp{};
    bool lendoAtividade = false;

    while (getline(arquivo, linha)) {
        if (linha == "---") {
            if (lendoAtividade) {
                if (quantidade_atividades >= capacidade_atividades) realocarAtividades();
                atividades[quantidade_atividades] = temp;
                quantidade_atividades++;
                lendoAtividade = false;
                temp = DadosAtividades{};
            }
        }
        else if (linha.find("ID:") == 0) {
            temp.IDAtividade = stoi(linha.substr(3));
            lendoAtividade = true;
        }
        else if (linha.find("NOME:") == 0) temp.nomeAtividade = linha.substr(5);
        else if (linha.find("TIPO:") == 0) temp.TipoDeAtividade = linha.substr(5);
        else if (linha.find("TEMA:") == 0) temp.TemaAtividade = linha.substr(5);
        else if (linha.find("INSTRUTOR:") == 0) temp.InstrutorAtividade = linha.substr(10);
        else if (linha.find("LOCAL:") == 0) temp.LocalAtividade = linha.substr(6);
        else if (linha.find("DATA:") == 0) temp.dataAtividade = linha.substr(5);
        else if (linha.find("HORA:") == 0) temp.HoraAtividade = linha.substr(5);
        else if (linha.find("VAGAS_TOTAIS:") == 0) {
            try { temp.vagas_totais = stoi(linha.substr(13)); }
            catch (...) { temp.vagas_totais = 0; }
        }
        else if (linha.find("VAGAS_OCUPADAS:") == 0) {
            try { temp.vagas_ocupadas = stoi(linha.substr(15)); }
            catch (...) { temp.vagas_ocupadas = 0; }
        }
        else if (linha.find("CARGA_HORARIA:") == 0) {
            try { temp.CargaHoraria = stoi(linha.substr(14)); }
            catch (...) { temp.CargaHoraria = 0; }
        }
        else if (linha.find("STATUS:") == 0) temp.status = linha.substr(7);
    }

    if (lendoAtividade) {
        if (quantidade_atividades >= capacidade_atividades) realocarAtividades();
        atividades[quantidade_atividades] = temp;
        quantidade_atividades++;
    }
    arquivo.close();
}

void AreaAtividades::carregarListaEsperaArquivo() {
    ifstream arquivo("lista_espera.txt");
    if (!arquivo) return;

    string linha;
    InscricaoListaEspera temp{};
    bool lendoInscricao = false;

    while (getline(arquivo, linha)) {
        if (linha == "---") {
            if (lendoInscricao) {
                if (quantidade_lista_espera >= capacidade_lista_espera) realocarListaEspera();
                lista_espera[quantidade_lista_espera] = temp;
                quantidade_lista_espera++;
                lendoInscricao = false;
                temp = InscricaoListaEspera{};
            }
        }
        else if (linha.find("ATIVIDADE:") == 0) {
            try { temp.id_atividade = stoi(linha.substr(10)); }
            catch (...) { temp.id_atividade = 0; }
            lendoInscricao = true;
        }
        else if (linha.find("PARTICIPANTE:") == 0) {
            try { temp.id_participante = stoi(linha.substr(13)); }
            catch (...) { temp.id_participante = 0; }
        }
        else if (linha.find("TELEFONE:") == 0) temp.telefone = linha.substr(9);
        else if (linha.find("POSICAO:") == 0) {
            try { temp.posicao_fila = stoi(linha.substr(8)); }
            catch (...) { temp.posicao_fila = 0; }
        }
        else if (linha.find("DATA:") == 0) temp.data_entrada = linha.substr(5);
    }

    if (lendoInscricao) {
        if (quantidade_lista_espera >= capacidade_lista_espera) realocarListaEspera();
        lista_espera[quantidade_lista_espera] = temp;
        quantidade_lista_espera++;
    }
    arquivo.close();
}

void AreaAtividades::carregarInscricoesArquivo() {
    ifstream arquivo("inscricoes.txt");
    if (!arquivo) return;

    string linha;
    Inscricao temp{};
    bool lendoInscricao = false;

    while (getline(arquivo, linha)) {
        if (linha == "---") {
            if (lendoInscricao) {
                if (quantidade_inscricoes >= capacidade_inscricoes) realocarInscricoes();
                inscricoes[quantidade_inscricoes] = temp;
                quantidade_inscricoes++;
                lendoInscricao = false;
                temp = Inscricao{};
            }
        }
        else if (linha.find("ATIVIDADE:") == 0) {
            try { temp.id_atividade = stoi(linha.substr(10)); }
            catch (...) { temp.id_atividade = 0; }
            lendoInscricao = true;
        }
        else if (linha.find("PARTICIPANTE:") == 0) {
            try { temp.id_participante = stoi(linha.substr(13)); }
            catch (...) { temp.id_participante = 0; }
        }
    }

    if (lendoInscricao) {
        if (quantidade_inscricoes >= capacidade_inscricoes) realocarInscricoes();
        inscricoes[quantidade_inscricoes] = temp;
        quantidade_inscricoes++;
    }
    arquivo.close();
}

/*
    ====================================
    PARTE 3: REALOCAÇÕES DE MEMÓRIA
    ====================================
    Estas funções implementam uma estratégia de realocação 
    dinâmica para três arrays distintos: atividades, lista 
    de espera e inscrições. Cada função duplica a capacidade 
    atual do array quando necessário, criando um novo espaço 
    de memória com o dobro do tamanho. Todos os elementos 
    existentes são copiados para o novo array antes da liberação 
    da memória antiga. Por fim, os ponteiros são atualizados para 
    apontar para a nova localização e a capacidade é ajustada, 
    garantindo o crescimento eficiente das estruturas de dados 
    conforme novos elementos são adicionados.

    Att. Luan Palma
    Código Revisado!
*/
void AreaAtividades::realocarAtividades() {
    int nova_capacidade = capacidade_atividades * 2;
    DadosAtividades* novo_array = new DadosAtividades[nova_capacidade];
    for (int i = 0; i < quantidade_atividades; i++) novo_array[i] = atividades[i];
    delete[] atividades;
    atividades = novo_array;
    capacidade_atividades = nova_capacidade;
}

void AreaAtividades::realocarListaEspera() {
    int nova_capacidade = capacidade_lista_espera * 2;
    InscricaoListaEspera* novo_array = new InscricaoListaEspera[nova_capacidade];
    for (int i = 0; i < quantidade_lista_espera; i++) novo_array[i] = lista_espera[i];
    delete[] lista_espera;
    lista_espera = novo_array;
    capacidade_lista_espera = nova_capacidade;
}

void AreaAtividades::realocarInscricoes() {
    int nova_capacidade = capacidade_inscricoes * 2;
    Inscricao* novo_array = new Inscricao[nova_capacidade];
    for (int i = 0; i < quantidade_inscricoes; i++) novo_array[i] = inscricoes[i];
    delete[] inscricoes;
    inscricoes = novo_array;
    capacidade_inscricoes = nova_capacidade;
}

/*
   ==================================
   PARTE 4: CRUD
   =================================
   Estas funções gerenciam o ciclo de vida completo das atividades 
   no sistema, desde o cadastro até a exclusão. A função de cadastro 
   coleta todos os dados necessários incluindo nome, tipo, local, 
   data e horário, além de validar entradas numéricas como vagas e 
   carga horária. A listagem exibe todas as atividades cadastradas 
   de forma organizada, mostrando o status completo de cada uma. A 
   busca permite localizar atividades específicas por ID, enquanto a 
   exclusão remove registros do array e atualiza o arquivo correspondente, 
   garantindo a integridade dos dados em todas as operações realizadas.

   Att. Sistema de Arquivos - Equipe Credentia+
   Código Revisado!
*/
void AreaAtividades::CadastrarAtividade() {
    system("cls");
    cout << "===============================================" << endl;
    cout << "           CADASTRAR NOVA ATIVIDADE" << endl;
    cout << "===============================================" << endl;

    if (quantidade_atividades >= capacidade_atividades) realocarAtividades();

    DadosAtividades nova;
    nova.IDAtividade = gerarNovoID();

    cin.ignore();
    cout << "Nome da atividade: "; getline(cin, nova.nomeAtividade);
    cout << "Tipo de atividade: "; getline(cin, nova.TipoDeAtividade);
    cout << "Tema da atividade: "; getline(cin, nova.TemaAtividade);
    cout << "Nome do instrutor: "; getline(cin, nova.InstrutorAtividade);
    cout << "Local: "; getline(cin, nova.LocalAtividade);
    cout << "Data (DD/MM/AAAA): "; getline(cin, nova.dataAtividade);
    cout << "Hora: "; getline(cin, nova.HoraAtividade);

    cout << "Vagas totais: ";
    while (!(cin >> nova.vagas_totais) || nova.vagas_totais <= 0) {
        cout << "Número inválido! Digite um número positivo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Carga horária (horas): ";
    while (!(cin >> nova.CargaHoraria) || nova.CargaHoraria <= 0) {
        cout << "Número inválido! Digite um número positivo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    nova.vagas_ocupadas = 0;
    nova.status = "ativa";

    atividades[quantidade_atividades] = nova;
    quantidade_atividades++;
    salvarAtividadeArquivo(nova);

    cout << "\nATIVIDADE CADASTRADA COM SUCESSO! ID: " << nova.IDAtividade << endl;
    system("pause");
}

void AreaAtividades::ListarAtividade() {
    system("cls");
    cout << "===============================================" << endl;
    cout << "            LISTA DE ATIVIDADES" << endl;
    cout << "===============================================" << endl;

    if (quantidade_atividades == 0) {
        cout << "Nenhuma atividade cadastrada." << endl;
        system("pause");
        return;
    }

    for (int i = 0; i < quantidade_atividades; i++) {
        cout << "\n--- Atividade " << (i + 1) << " ---" << endl;
        cout << "ID: " << atividades[i].IDAtividade << endl;
        cout << "Nome: " << atividades[i].nomeAtividade << endl;
        cout << "Tipo: " << atividades[i].TipoDeAtividade << endl;
        cout << "Tema: " << atividades[i].TemaAtividade << endl;
        cout << "Instrutor: " << atividades[i].InstrutorAtividade << endl;
        cout << "Local: " << atividades[i].LocalAtividade << endl;
        cout << "Data: " << atividades[i].dataAtividade << " às " << atividades[i].HoraAtividade << endl;
        cout << "Vagas: " << atividades[i].vagas_ocupadas << "/" << atividades[i].vagas_totais;
        cout << " (" << getVagasDisponiveis(atividades[i].IDAtividade) << " disponíveis)" << endl;
        cout << "Carga Horária: " << atividades[i].CargaHoraria << " horas" << endl;
        cout << "Status: " << atividades[i].status << endl;
    }
    system("pause");
}

void AreaAtividades::BuscarAtividade() {
    system("cls");
    cout << "===============================================" << endl;
    cout << "             BUSCAR ATIVIDADE" << endl;
    cout << "===============================================" << endl;

    int id_busca;
    cout << "Digite o ID da atividade: ";
    while (!(cin >> id_busca)) {
        cout << "ID inválido! Digite um número: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    DadosAtividades* atividade = buscarAtividade(id_busca);
    if (atividade) {
        cout << "\n=== ATIVIDADE ENCONTRADA ===" << endl;
        cout << "ID: " << atividade->IDAtividade << endl;
        cout << "Nome: " << atividade->nomeAtividade << endl;
        cout << "Tipo: " << atividade->TipoDeAtividade << endl;
        cout << "Tema: " << atividade->TemaAtividade << endl;
        cout << "Instrutor: " << atividade->InstrutorAtividade << endl;
        cout << "Local: " << atividade->LocalAtividade << endl;
        cout << "Data: " << atividade->dataAtividade << " às " << atividade->HoraAtividade << endl;
        cout << "Vagas: " << atividade->vagas_ocupadas << "/" << atividade->vagas_totais << endl;
        cout << "Carga Horária: " << atividade->CargaHoraria << " horas" << endl;
        cout << "Status: " << atividade->status << endl;
    }
    else {
        cout << "Atividade não encontrada!" << endl;
    }
    system("pause");
}

bool AreaAtividades::ExcluirAtividade(int id) {
    for (int i = 0; i < quantidade_atividades; i++) {
        if (atividades[i].IDAtividade == id) {
            for (int j = i; j < quantidade_atividades - 1; j++) atividades[j] = atividades[j + 1];
            quantidade_atividades--;
            reescreverAtividadesArquivo();
            return true;
        }
    }
    return false;
}

/*
    =========================================
    PARTE 5: GESTÃO DE PRESENÇA
    =========================================
    Esta função gerencia o processo completo de check-in de participantes em atividades, 
    desde a validação inicial até a inscrição em lista de espera quando necessário.
    O sistema primeiro verifica a existência do participante via CPF e confirma a 
    disponibilidade da atividade desejada. Se o participante já estiver inscrito, o 
    processo é interrompido, mas se a atividade estiver lotada, é oferecida a opção de 
    entrar na lista de espera, capturando os dados de contato. Para vagas disponíveis, 
    a inscrição é realizada normalmente, atualizando os contadores de vagas ocupadas e 
    gerando confirmação com detalhes da atividade e participante, garantindo um fluxo 
    completo de gerenciamento de inscrições.

    Att. Luan Palma
    Código Revisado!
*/
bool AreaAtividades::fazerCheckin(std::string cpf_participante, int id_atividade) {
    string nome, instituicao;
    int id_participante_numerico;

    if (!buscarParticipantePorCPF(cpf_participante, id_participante_numerico, nome, instituicao)) {
        cout << "PARTICIPANTE NÃO ENCONTRADO!" << endl;
        return false;
    }

    DadosAtividades* atividade = buscarAtividade(id_atividade);
    if (!atividade) {
        cout << "ATIVIDADE NÃO ENCONTRADA!" << endl;
        return false;
    }

    if (verificarInscricaoExistente(id_participante_numerico, id_atividade)) {
        cout << "PARTICIPANTE JÁ INSCRITO NESTA ATIVIDADE!" << endl;
        return false;
    }

    if (atividade->vagas_ocupadas >= atividade->vagas_totais) {
        cout << "ATIVIDADE LOTADA!" << endl;
        string telefone = buscarTelefoneParticipante(id_participante_numerico);
        cout << "Telefone para contato: " << telefone << endl;
        cout << "Deseja entrar na lista de espera? (S/N): ";

        char opcao;
        cin >> opcao;
        cin.ignore();

        if (opcao == 'S' || opcao == 's') {
            if (quantidade_lista_espera >= capacidade_lista_espera) realocarListaEspera();

            InscricaoListaEspera nova;
            nova.id_participante = id_participante_numerico;
            nova.id_atividade = id_atividade;
            nova.telefone = telefone;
            nova.data_entrada = "";
            nova.posicao_fila = quantidade_lista_espera + 1;

            lista_espera[quantidade_lista_espera] = nova;
            quantidade_lista_espera++;
            salvarListaEsperaArquivo(nova);

            cout << "ADICIONADO À LISTA DE ESPERA! Posição: " << nova.posicao_fila << endl;
            return true;
        }
        return false;
    }

    // Fazer inscrição normal
    if (quantidade_inscricoes >= capacidade_inscricoes) realocarInscricoes();

    Inscricao novaInscricao;
    novaInscricao.id_atividade = id_atividade;
    novaInscricao.id_participante = id_participante_numerico;

    inscricoes[quantidade_inscricoes] = novaInscricao;
    quantidade_inscricoes++;
    salvarInscricaoArquivo(novaInscricao);

    atividade->vagas_ocupadas++;
    reescreverAtividadesArquivo();

    cout << "-- CHECK-IN REALIZADO COM SUCESSO! --" << endl;
    cout << "Participante: " << nome << endl;
    cout << "Atividade: " << atividade->nomeAtividade << endl;
    cout << "Vagas restantes: " << getVagasDisponiveis(id_atividade) << endl;
    return true;
}

void AreaAtividades::listarListaEspera(int id_atividade) {
    system("cls");
    cout << "===============================================" << endl;
    cout << "             LISTA DE ESPERA" << endl;
    cout << "===============================================" << endl;

    if (quantidade_lista_espera == 0) {
        cout << "Nenhuma pessoa na lista de espera." << endl;
        system("pause");
        return;
    }

    bool encontrou = false;
    for (int i = 0; i < quantidade_lista_espera; i++) {
        if (id_atividade == -1 || lista_espera[i].id_atividade == id_atividade) {
            encontrou = true;
            cout << "\n--- Posição " << lista_espera[i].posicao_fila << " ---" << endl;
            cout << "Atividade ID: " << lista_espera[i].id_atividade << endl;
            cout << "Participante ID: " << lista_espera[i].id_participante << endl;
            cout << "Telefone: " << lista_espera[i].telefone << endl;
        }
    }

    if (!encontrou && id_atividade != -1) {
        cout << "Nenhuma pessoa na lista de espera para esta atividade." << endl;
    }
    system("pause");
}

/*
    =====================================
    PARTE 6: FUNÇÕES DE GESTÃO
    =====================================
    Estas funções completam o gerenciamento de participantes nas atividades, 
    permitindo visualizar inscrições e realizar cancelamentos. A listagem de 
    participantes exibe detalhes completos de todos os inscritos em uma atividade 
    específica, incluindo nome e instituição de origem, com contagem precisa do total. 
    Já o cancelamento de inscrição remove participantes através da busca por IDs de 
    atividade e participante, atualizando tanto o array de inscrições quanto o 
    contador de vagas ocupadas, e reescrevendo os arquivos para manter a persistência 
    dos dados, garantindo a integridade do sistema de gestão.

    Att. Luan Palma
    Código Revisado!
*/
void AreaAtividades::listarParticipantesPorAtividade(int id_atividade) {
    DadosAtividades* atividade = buscarAtividade(id_atividade);
    if (!atividade) {
        cout << "Atividade com ID " << id_atividade << " não encontrada." << endl;
        system("pause");
        return;
    }

    system("cls");
    cout << "===============================================" << endl;
    cout << "   LISTA DE INSCRITOS NA ATIVIDADE" << endl;
    cout << "===============================================" << endl;
    cout << "ATIVIDADE: " << atividade->nomeAtividade << " (ID: " << id_atividade << ")" << endl;
    cout << "Vagas: " << atividade->vagas_ocupadas << "/" << atividade->vagas_totais << endl;
    cout << "-----------------------------------------------" << endl;

    bool encontrou = false;
    int contador = 0;

    for (int i = 0; i < quantidade_inscricoes; i++) {
        if (inscricoes[i].id_atividade == id_atividade) {
            int id_part = inscricoes[i].id_participante;
            string nome_part, instituicao_part;

            if (buscarDetalhesParticipantePorID(id_part, nome_part, instituicao_part)) {
                cout << "\n  Participante " << (contador + 1);
                cout << "\n  ID: " << id_part;
                cout << "\n  Nome: " << nome_part;
                cout << "\n  Instituicao: " << instituicao_part << endl;
            }
            else {
                cout << "\n  Participante " << (contador + 1);
                cout << "\n  ID: " << id_part << " (Detalhes não encontrados)" << endl;
            }

            encontrou = true;
            contador++;
        }
    }

    if (!encontrou) {
        cout << "\nNenhum participante inscrito nesta atividade." << endl;
    }
    else {
        cout << "\n-----------------------------------------------" << endl;
        cout << "Total de inscritos: " << contador << endl;
    }

    cout << "===============================================" << endl;
    system("pause");
}

void AreaAtividades::cancelarInscricao() {
    int id_atividade, id_participante;

    cout << "===============================================" << endl;
    cout << "           CANCELAR INSCRIÇÃO" << endl;
    cout << "===============================================" << endl;

    cout << "Digite o ID da Atividade: ";
    while (!(cin >> id_atividade)) {
        cout << "ID inválido! Digite um número: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Digite o ID do Participante a remover: ";
    while (!(cin >> id_participante)) {
        cout << "ID inválido! Digite um número: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    int indice_remover = -1;
    for (int i = 0; i < quantidade_inscricoes; i++) {
        if (inscricoes[i].id_atividade == id_atividade &&
            inscricoes[i].id_participante == id_participante) {
            indice_remover = i;
            break;
        }
    }

    if (indice_remover == -1) {
        cout << "INSCRIÇÃO NÃO ENCONTRADA!" << endl;
        system("pause");
        return;
    }

    for (int i = indice_remover; i < quantidade_inscricoes - 1; i++) {
        inscricoes[i] = inscricoes[i + 1];
    }
    quantidade_inscricoes--;
    reescreverInscricoesArquivo();

    DadosAtividades* atividade = buscarAtividade(id_atividade);
    if (atividade) {
        atividade->vagas_ocupadas--;
        reescreverAtividadesArquivo();
    }

    cout << "Inscrição cancelada com sucesso!" << endl;
    system("pause");
}

/*
    =================================================
    PARTE 7: FUNÇÕES AUXILIARES
    =================================================
    Estas funções fornecem utilitários essenciais para o sistema 
    de gestão de atividades, incluindo geração de IDs sequenciais, 
    verificação de lotação e consulta de vagas disponíveis. A busca 
    por atividades e verificação de inscrições existentes garantem 
    a integridade das operações, enquanto a função de detalhes do 
    participante consulta o arquivo externo para recuperar informações 
    completas. Juntas, estas operações suportam as funcionalidades 
    principais do sistema, assegurando validações adequadas e mantendo 
    a consistência dos dados em todas as operações realizadas.

    Att. Equipe Credentia+
    Código Revisado!
*/
string AreaAtividades::obterDataAtual() { return ""; }

int AreaAtividades::gerarNovoID() {
    int max_id = 0;
    for (int i = 0; i < quantidade_atividades; i++) {
        if (atividades[i].IDAtividade > max_id) max_id = atividades[i].IDAtividade;
    }
    return max_id + 1;
}

bool AreaAtividades::verificarLotacao(int id_atividade) {
    DadosAtividades* atividade = buscarAtividade(id_atividade);
    return atividade && (atividade->vagas_ocupadas >= atividade->vagas_totais);
}

int AreaAtividades::getVagasDisponiveis(int id_atividade) {
    DadosAtividades* atividade = buscarAtividade(id_atividade);
    return atividade ? (atividade->vagas_totais - atividade->vagas_ocupadas) : 0;
}

DadosAtividades* AreaAtividades::buscarAtividade(int id_atividade) {
    for (int i = 0; i < quantidade_atividades; i++) {
        if (atividades[i].IDAtividade == id_atividade) return &atividades[i];
    }
    return nullptr;
}

bool AreaAtividades::verificarInscricaoExistente(int id_participante, int id_atividade) {
    for (int i = 0; i < quantidade_inscricoes; i++) {
        if (inscricoes[i].id_participante == id_participante &&
            inscricoes[i].id_atividade == id_atividade) return true;
    }
    return false;
}

bool AreaAtividades::buscarDetalhesParticipantePorID(int id_participante, string& nome, string& instituicao) {
    ifstream arquivo("Participante.txt");
    if (!arquivo) return false;

    string linha;
    int temp_id = -1;
    string temp_nome = "", temp_instituicao = "Nenhuma";
    bool encontrado = false;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) {
            try { temp_id = stoi(linha.substr(3)); }
            catch (...) { temp_id = -1; }
        }
        else if (linha.find("Nome:") == 0) temp_nome = linha.substr(5);
        else if (linha.find("Instituicao:") == 0) temp_instituicao = linha.substr(12);
        else if (linha == "---") {
            if (temp_id == id_participante) {
                nome = temp_nome;
                instituicao = temp_instituicao;
                encontrado = true;
                break;
            }
            temp_id = -1; temp_nome = ""; temp_instituicao = "Nenhuma";
        }
    }

    if (!encontrado && temp_id == id_participante) {
        nome = temp_nome;
        instituicao = temp_instituicao;
        encontrado = true;
    }

    arquivo.close();
    return encontrado;
}

/*
    =========================================
    PARTE 8: FUNÇÕES DE ARQUIVOS
    =========================================
    Estas funções gerenciam a persistência de dados em arquivos texto, 
    implementando duas estratégias distintas: acréscimo para novos 
    registros e reescrita completa para atualizações. As operações de 
    salvar adicionam informações ao final dos arquivos mantendo os dados 
    existentes, enquanto as reescritas regeneram os arquivos do zero para 
    refletir alterações nos arrays. O sistema utiliza formato estruturado 
    com prefixos identificadores e delimitadores "---" para separar registros, 
    garantindo a consistência na leitura e escrita de atividades, inscrições 
    e lista de espera, assegurando a integridade dos dados entre execuções do programa.

    Att. Equipe Credentia+
    Código Revisado!
*/
void AreaAtividades::salvarAtividadeArquivo(const DadosAtividades& atividade) {
    ofstream arquivo("atividades.txt", ios::app);
    if (arquivo) {
        arquivo << "ID:" << atividade.IDAtividade << "\n";
        arquivo << "NOME:" << atividade.nomeAtividade << "\n";
        arquivo << "TIPO:" << atividade.TipoDeAtividade << "\n";
        arquivo << "TEMA:" << atividade.TemaAtividade << "\n";
        arquivo << "INSTRUTOR:" << atividade.InstrutorAtividade << "\n";
        arquivo << "LOCAL:" << atividade.LocalAtividade << "\n";
        arquivo << "DATA:" << atividade.dataAtividade << "\n";
        arquivo << "HORA:" << atividade.HoraAtividade << "\n";
        arquivo << "VAGAS_TOTAIS:" << atividade.vagas_totais << "\n";
        arquivo << "VAGAS_OCUPADAS:" << atividade.vagas_ocupadas << "\n";
        arquivo << "CARGA_HORARIA:" << atividade.CargaHoraria << "\n";
        arquivo << "STATUS:" << atividade.status << "\n";
        arquivo << "---\n";
        arquivo.close();
    }
}

void AreaAtividades::reescreverAtividadesArquivo() {
    ofstream arquivo("atividades.txt");
    if (!arquivo) return;

    for (int i = 0; i < quantidade_atividades; i++) {
        arquivo << "ID:" << atividades[i].IDAtividade << "\n";
        arquivo << "NOME:" << atividades[i].nomeAtividade << "\n";
        arquivo << "TIPO:" << atividades[i].TipoDeAtividade << "\n";
        arquivo << "TEMA:" << atividades[i].TemaAtividade << "\n";
        arquivo << "INSTRUTOR:" << atividades[i].InstrutorAtividade << "\n";
        arquivo << "LOCAL:" << atividades[i].LocalAtividade << "\n";
        arquivo << "DATA:" << atividades[i].dataAtividade << "\n";
        arquivo << "HORA:" << atividades[i].HoraAtividade << "\n";
        arquivo << "VAGAS_TOTAIS:" << atividades[i].vagas_totais << "\n";
        arquivo << "VAGAS_OCUPADAS:" << atividades[i].vagas_ocupadas << "\n";
        arquivo << "CARGA_HORARIA:" << atividades[i].CargaHoraria << "\n";
        arquivo << "STATUS:" << atividades[i].status << "\n";
        arquivo << "---\n";
    }
    arquivo.close();
}

void AreaAtividades::salvarListaEsperaArquivo(const InscricaoListaEspera& inscricao) {
    ofstream arquivo("lista_espera.txt", ios::app);
    if (arquivo) {
        arquivo << "ATIVIDADE:" << inscricao.id_atividade << "\n";
        arquivo << "PARTICIPANTE:" << inscricao.id_participante << "\n";
        arquivo << "TELEFONE:" << inscricao.telefone << "\n";
        arquivo << "POSICAO:" << inscricao.posicao_fila << "\n";
        arquivo << "DATA:" << inscricao.data_entrada << "\n";
        arquivo << "---\n";
        arquivo.close();
    }
}

void AreaAtividades::salvarInscricaoArquivo(const Inscricao& inscricao) {
    ofstream arquivo("inscricoes.txt", ios::app);
    if (arquivo) {
        arquivo << "ATIVIDADE:" << inscricao.id_atividade << "\n";
        arquivo << "PARTICIPANTE:" << inscricao.id_participante << "\n";
        arquivo << "---\n";
        arquivo.close();
    }
}

void AreaAtividades::reescreverInscricoesArquivo() {
    ofstream arquivo("inscricoes.txt");
    if (!arquivo) return;

    for (int i = 0; i < quantidade_inscricoes; i++) {
        arquivo << "ATIVIDADE:" << inscricoes[i].id_atividade << "\n";
        arquivo << "PARTICIPANTE:" << inscricoes[i].id_participante << "\n";
        arquivo << "---\n";
    }
    arquivo.close();
}

/*
    =============================================
    PARTE 9: BUSCA DE DADOS EXTERNOS
    =============================================
    Estas funções realizam consultas específicas ao 
    arquivo de participantes para recuperar informações 
    essenciais durante o processo de check-in. A busca 
    por CPF localiza participantes no sistema e retorna 
    seus dados completos incluindo ID, nome e instituição, 
    validando a existência do cadastro. Já a função de 
    telefone recupera o contato do participante para casos 
    de lista de espera, garantindo meios de comunicação. 
    Ambas utilizam processamento linha por linha com identificação 
    por prefixos e delimitadores, assegurando que as informações 
    críticas para o gerenciamento de inscrições estejam sempre 
    disponíveis quando necessárias.

    Att. Equipe Credentia+
    Código Revisado!

*/
string AreaAtividades::buscarTelefoneParticipante(int id_participante) {
    ifstream arquivo("Participante.txt");
    if (!arquivo) return "Não cadastrado";

    string linha, telefone = "Não informado";
    int temp_id = -1;
    bool encontrado = false;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) temp_id = stoi(linha.substr(3));
        else if (linha.find("Telefone1:") == 0) telefone = linha.substr(10);
        else if (linha == "---") {
            if (temp_id == id_participante) {
                encontrado = true;
                break;
            }
            temp_id = -1; telefone = "Não informado";
        }
    }

    if (!encontrado && temp_id == id_participante) encontrado = true;
    arquivo.close();
    return encontrado ? telefone : "Não informado";
}

bool AreaAtividades::buscarParticipantePorCPF(const string& cpf, int& id_participante, string& nome, string& instituicao) {
    ifstream arquivo("Participante.txt");
    if (!arquivo) return false;

    string linha;
    int temp_id = -1;
    string temp_nome = "", temp_cpf = "", temp_instituicao = "Nenhuma";
    bool cpfEncontrado = false;

    while (getline(arquivo, linha)) {
        if (linha.find("ID:") == 0) temp_id = stoi(linha.substr(3));
        else if (linha.find("Nome:") == 0) temp_nome = linha.substr(5);
        else if (linha.find("Instituicao:") == 0) temp_instituicao = linha.substr(12);
        else if (linha.find("CPF:") == 0) {
            temp_cpf = linha.substr(4);
            temp_cpf.erase(0, temp_cpf.find_first_not_of(" \t"));
            temp_cpf.erase(temp_cpf.find_last_not_of(" \t") + 1);
        }
        else if (linha == "---") {
            if (temp_cpf == cpf && !temp_nome.empty()) {
                cpfEncontrado = true;
                nome = temp_nome;
                instituicao = temp_instituicao;
                id_participante = temp_id;
                break;
            }
            temp_id = -1; temp_nome = ""; temp_cpf = ""; temp_instituicao = "Nenhuma";
        }
    }

    if (!cpfEncontrado && temp_cpf == cpf && !temp_nome.empty()) {
        cpfEncontrado = true;
        nome = temp_nome;
        instituicao = temp_instituicao;
        id_participante = temp_id;
    }

    arquivo.close();
    return cpfEncontrado;
}