#pragma once

#include <string>
#include <locale.h>
#include <cstdlib>
#include <Windows.h>
#undef min
#undef max


// Estrutura para dados do evento
struct DadosEventos {
    int ID_Evento;
    std::string nomeEvento;
    std::string TemaEvento;
    std::string DataInicial;
    std::string DataFim;
    std::string Local;
    std::string Hora;
    std::string Instituicao_Promovedora;
    std::string Nome_Representante;
    std::string CPF_Representante;
};

// Estrutura para entrada do usuário
struct Entrada_evento {
    std::string usuario;
    std::string tratando_bug; // Para limpeza de buffer
};

// Estrutura para inscrições em eventos
struct InscricaoEvento {
    int id_evento;
    int id_participante;
};

class Evento {
private:
    // Array dinâmico para inscrições
    InscricaoEvento* inscricoes_evento;
    int quantidade_inscricoes_evento;
    int capacidade_inscricoes_evento;

    // Funções de gerenciamento de memória
    void carregarInscricoesEventoArquivo();
    void realocarInscricoesEvento();
    void salvarInscricaoEvento(int id_evento, int id_participante);
    bool verificarInscricaoEventoExistente(int id_evento, int id_participante);

    // Funções auxiliares
    std::string trim(const std::string& str);
    bool buscarDetalhesParticipantePorID(int id_participante, std::string& nome, std::string& instituicao);
    std::string buscarNomeEventoPorID(int id_evento);

public:
    // Construtor e Destrutor
    Evento();
    ~Evento();

    // CRUD de Eventos
    void CadastrarEvento();
    void ListarEventos();
    void BuscarEventoPorID(int id);
    void BuscarEventoPorNome(const std::string& nome);
    void BuscarEventoPorInstituicao(const std::string& instituicao);
    bool RemoverEvento(int id);
    void DadosEvento();

    // Credenciamento
    void CredenciamentoAutonomo();
    bool buscarParticipantePorCPF(const std::string& cpf, int& idParticipante, std::string& nomeParticipante, std::string& instituicaoParticipante);
    bool verificarFormatoArquivoParticipantes();

    // Listagem de participantes
    void ListarParticipantesDoEvento(int id);

    // Funções de arquivo
    int getGlobalID_evento(std::string nomeArq);
    int updGlobalid_evento(std::string nomeArq);

    // Funções LB (Low-level)
    void LB_listarEventos();
    void LB_buscarEventoPorID(int id);
    void LB_buscarEventoPorNome(std::string nomeProcurado);
    void LB_buscarEventoPorInstituicao(std::string instituicaoProcurada);
    bool LB_removerEvento(int id);
    void LB_listarParticipantesPorEvento(int id_evento);
};

// Declaração da função main
int MainEvento();
