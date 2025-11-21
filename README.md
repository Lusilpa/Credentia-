# 🎓 Credentia+

**Sistema Unificado de Credenciamento e Gestão Para Eventos Acadêmicos e Científicos**

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-orange.svg)]()

> Solução offline especializada para gestão de eventos acadêmicos de grande porte

## 📋 Sobre o Projeto

O **Credentia+** é um sistema desenvolvido em C++ para resolver os desafios de gestão de eventos acadêmicos na região Norte do Brasil, onde a infraestrutura de internet é limitada. Criado inicialmente para atender o **ENCOENG da FUCAPI**, o sistema oferece uma alternativa robusta e offline aos sistemas comerciais dependentes de conectividade constante.

### 🎯 Problema Solucionado

- **Dependência de internet** em regiões com infraestrutura limitada
- **Custos proibitivos** de sistemas comerciais para instituições educacionais
- **Gestão manual ineficiente** para eventos com centenas de participantes
- **Falta de adequação** específica para eventos acadêmicos

## ✨ Funcionalidades

### 🏗️ Módulos Principais

| Módulo | Descrição | Funcionalidades |
|--------|-----------|-----------------|
| **📅 Eventos** | Gestão completa de eventos | CRUD, credenciamento autônomo, controle de participantes |
| **👥 Participantes** | Cadastro de participantes | Validação de CPF, múltiplos telefones/cursos, instituições vinculadas |
| **🎤 Palestrantes** | Gestão de palestrantes | Cadastro simplificado, vínculo com atividades, títulos acadêmicos |
| **📚 Atividades** | Gestão de atividades paralelas | Check-in inteligente, lista de espera, controle de lotação |
| **🏫 Instituições** | Cadastro institucional | Autenticação por ID/senha, múltiplos telefones |
| **📜 Certificados** | Emissão de certificados | Geração automática por tipo de participação |

### 🔧 Funcionalidades Técnicas

- **✅ Validação de CPF** com algoritmo recursivo oficial
- **💾 Persistência em arquivos** texto (operacionalidade offline)
- **🧠 Alocação dinâmica** de memória com arrays dinâmicos
- **📊 Structs e Classes** para modelagem de entidades do domínio
- **🔄 Sistema de check-in** dual (inscrição direta + lista de espera)
- **🎫 Credenciamento autônomo** por CPF para eventos

## 🛠️ Tecnologias e Conceitos

### 🚀 Tecnologias Utilizadas

- **Linguagem**: C++ (padrão C++17)
- **Persistência**: Arquivos texto com formatação estruturada
- **Compilação**: Compatível com GCC, Clang, MSVC

### 📚 Conceitos Aplicados

| Conceito | Aplicação no Projeto |
|----------|---------------------|
| **Ponteiros e Alocação Dinâmica** | Arrays dinâmicos para telefones, cursos, instituições |
| **Structs e Classes** | Modelagem de entidades (Participante, Evento, Atividade) |
| **Funções Recursivas** | Validação de CPF com algoritmo recursivo |
| **Persistência em Arquivos** | Sistema de banco de dados manual em texto |
| **Regra dos Três** | Gestão robusta de memória em classes com recursos dinâmicos |
| **CRUD** | Operações completas de Create, Read, Update, Delete |
| **Separação de Interface/Implementação** | Arquivos .hpp e .cpp para cada módulo |

## 🚀 Como Usar

### Pré-requisitos

- Compilador C++ compatível com C++17 (GCC, Clang, ou MSVC)
- Sistema operacional: Windows, Linux ou macOS
- Make (opcional, para usar o Makefile)

### Compilação e Execução

#### Opção 1: Compilação Manual
```bash
# Compilar todos os arquivos
g++ -std=c++17 -I include -o credentia src/*.cpp

# Executar o sistema
./credentia

Estratégia de Persistência
Formato: Campos com prefixos e delimitadores "---"

IDs: Sistema global auto-incrementado por arquivo

Operações: Leitura/escrita sequencial com arquivos temporários para updates

Separação de Cabeçalhos e Implementação
Headers (.hpp): Declarações de classes, structs, protótipos de funções, includes guards

Implementação (.cpp): Definições de métodos, lógica de negócio

Inclusões: Sistema organizado com -I include para includes limpos

🐛 Solução de Problemas
Erros Comuns de Compilação
Problema: Error: undefined reference to...
Solução: Certifique-se de que todos os arquivos .cpp estão sendo compilados

Problema: Error: file not found
Solução: Verifique o caminho dos includes use -I include

Problema: Erros de linker
Solução: Compile todos os arquivos .cpp juntos ou crie um Makefile

Problema: Multiple definition
Solução: Verifique se há includes guards (#ifndef #define #endif) em todos os headers

🤝 Contribuição
Contribuições são bem-vindas! Para contribuir:

Fork o projeto

Crie uma branch para sua feature (git checkout -b feature/AmazingFeature)

Commit suas mudanças (git commit -m 'Add some AmazingFeature')

Push para a branch (git push origin feature/AmazingFeature)

Abra um Pull Request

Diretrizes de Código
Use .hpp para headers e .cpp para implementações

Mantenha includes guards em todos os headers

Siga o estilo de código existente

Adicione comentários para novas funcionalidades complexas

Teste as mudanças antes de submeter

📄 Licença
Este projeto está sob a licença MIT. Veja o arquivo LICENSE para detalhes.

👥 Autores
Equipe Credentia+ - Desenvolvimento e Documentação

🙏 Agradecimentos
FUCAPI - Pelo contexto real de aplicação

ENCOENG - Pelos desafios práticos de gestão de eventos

Comunidade C++ - Pelas referências e boas práticas
