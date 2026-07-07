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
