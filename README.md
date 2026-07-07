# 📚 Acervo de Livros — Sistema de Gestão de Biblioteca em C

Este é um sistema robusto para gerenciamento de bibliotecas desenvolvido inteiramente na linguagem **C**. O objetivo principal do projeto é aplicar conceitos de estruturas de dados e **persistência de dados em arquivos de texto (`.txt`)**, eliminando a necessidade de um banco de dados externo tradicional para manter as informações salvas entre as execuções do programa.

O projeto demonstra forte domínio de conceitos essenciais da programação estruturada, controle de fluxo e manipulação rigorosa de arquivos.

---
## ⚙️ Arquitetura e Engenharia de Dados

O software foi projetado utilizando três entidades principais interligadas (`structs`), cujos dados são mapeados diretamente para arquivos físicos:

1. **Livros (`livros.txt`):** Armazena o código único, título, autor, ano de publicação, género, quantidade total, quantidade disponível no estoque e o histórico total de empréstimos.
2. **Usuários (`usuarios.txt`):** Controla os leitores cadastrados por meio de matrícula, nome, curso e quantidade de empréstimos ativos simultâneos.
3. **Empréstimos (`emprestimos.txt`):** Funciona como a tabela de relacionamento (log de transações), registrando o ID da operação, vínculo do usuário, vínculo do livro, data de retirada, data prevista para devolução, data real da devolução e status atual (ativo/devolvido).

---
## 🛠️ Módulos e Funcionalidades Inteligentes

O sistema é dividido em menus aninhados que segmentam as responsabilidades do negócio:

### 1. Central de Gerenciamento de Livros
* **Cadastro e Geração Automática de ID:** IDs sequenciais e exclusivos para evitar duplicidade.
* **Listagem e Busca Direta:** Leitura otimizada linha por linha para consulta do acervo.
* **Edição e Remoção Segura:** Atualização precisa dos dados direto nos registros e exclusão física das informações utilizando técnicas de arquivos temporários (`temp.txt`).
* **Rastreabilidade de Empréstimos Ativos:** Identifica instantaneamente quais usuários estão em posse de um determinado título.

### 2. Central de Gerenciamento de Usuários
* **Controle de Matrícula:** Cadastro indexado e validação de existência.
* **Integridade Referencial na Remoção:** O sistema possui uma regra inteligente que impede a exclusão de qualquer usuário que possua livros pendentes de devolução.
* **Sincronização de Dados:** Modificações efetuadas na memória (vetores) são imediatamente descarregadas nos arquivos físicos para evitar perda de dados (*Data Loss*).

### 3. Sistema de Transações (Empréstimos e Devoluções)
* **Regras de Negócio e Restrições:** Validação de estoque disponível antes da liberação do livro e imposição automática do limite máximo de 3 empréstimos simultâneos por usuário.
* **Submódulo Completo de Relatórios:** * Histórico individual de transações por matrícula.
  * Estatísticas do acervo disponível em tempo real.
  * Relatório de livros mais buscados (métrica de popularidade baseada no histórico).
  * Controle de usuários com pendências ativas.

---

## 🚀 Como Executar o Projeto

### Pré-requisitos
Certifique-se de ter um compilador C instalado no seu sistema (como o `GCC`).

### Passo a Passo
1. Clone este repositório para a sua máquina:
   ```bash
   git clone https://github.com/Gielsson/Acervo-de-livros.git
   
