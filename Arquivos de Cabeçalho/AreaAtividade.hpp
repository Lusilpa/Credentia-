#pragma once

#include <string>
#include <Windows.h>
#undef min
#undef max

#include <cstdlib>

// Estrutura para armazenar os dados de uma atividade
struct DadosAtividades {
    int IDAtividade;
    std::string nomeAtividade;
    std::string TipoDeAtividade;
    std::string TemaAtividade;
    std::string InstrutorAtividade;
    std::string LocalAtividade;
    std::string dataAtividade;
    std::string HoraAtividade;
    int vagas_totais;
    int vagas_ocupadas;
    int CargaHoraria;
    std::string status;
};

// Estrutura para armazenar inscrições na lista de espera
struct InscricaoListaEspera {
    int id_atividade;
    int id_participante;
    std::string telefone;
    int posicao_fila;
    std::string data_entrada;
};

// Estrutura para ligar Participante <-> Atividade (Inscritos confirmados)
struct Inscricao {
    int id_atividade;
    int id_participante;
};

class AreaAtividades {
public:
    // === CONSTRUTOR E DESTRUTOR ===
    AreaAtividades();
    ~AreaAtividades();

    // === CRUD ATIVIDADES ===
    void CadastrarAtividade();
    void ListarAtividade();
    void BuscarAtividade();
    bool ExcluirAtividade(int id);

    // === GESTÃO DE PRESENÇA E INSCRIÇÕES ===
    bool fazerCheckin(std::string cpf_participante, int id_atividade);
    void listarListaEspera(int id_atividade = -1);
    void listarParticipantesPorAtividade(int id_atividade);
    void cancelarInscricao();

    // === FUNÇÕES AUXILIARES PÚBLICAS ===
    bool verificarLotacao(int id_atividade);
    int getVagasDisponiveis(int id_atividade);

private:
    // === MEMBROS PRIVADOS (DADOS) ===
    DadosAtividades* atividades;
    int quantidade_atividades = 0;
    int capacidade_atividades = 10;

    InscricaoListaEspera* lista_espera;
    int quantidade_lista_espera = 0;
    int capacidade_lista_espera = 10;

    Inscricao* inscricoes;
    int quantidade_inscricoes = 0;
    int capacidade_inscricoes = 10;

    // === FUNÇÕES DE ARQUIVO ===
    void carregarAtividadesArquivo();
    void carregarListaEsperaArquivo();
    void carregarInscricoesArquivo();
    void salvarAtividadeArquivo(const DadosAtividades& atividade);
    void reescreverAtividadesArquivo();
    void salvarListaEsperaArquivo(const InscricaoListaEspera& inscricao);
    void salvarInscricaoArquivo(const Inscricao& inscricao);
    void reescreverInscricoesArquivo();

    // === FUNÇÕES DE REALOCAÇÃO ===
    void realocarAtividades();
    void realocarListaEspera();
    void realocarInscricoes();

    // === FUNÇÕES AUXILIARES INTERNAS ===
    std::string obterDataAtual();
    int gerarNovoID();
    DadosAtividades* buscarAtividade(int id_atividade);
    bool verificarInscricaoExistente(int id_participante, int id_atividade);
    bool buscarDetalhesParticipantePorID(int id_participante, std::string& nome, std::string& instituicao);

    // === BUSCA DE DADOS EXTERNOS ===
    std::string buscarTelefoneParticipante(int id_participante);
    bool buscarParticipantePorCPF(const std::string& cpf, int& id_participante, std::string& nome, std::string& instituicao);

    // === REGRA DOS TRÊS ===
    AreaAtividades(const AreaAtividades&);
    AreaAtividades& operator=(const AreaAtividades&);
};

int MainParticipantes();
int mainAtividade();
void ListarInscritos();
void tratamentodeentradas(int opcao);