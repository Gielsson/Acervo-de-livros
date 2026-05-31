#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


struct livro{
    int codigo;
    char titulo[250];
    char autor[250];
    int ano_de_publi;
    char genero[50];
    int qtd_total;
    int quant_disp;
   int total_emprestimos;
};
typedef struct livro livro;
struct usuario{
int matricula;
char nome[250];
char curso[250];
int qtd_emprestimos_ativos;
}; 
typedef struct usuario usuario;

struct emprestimo{
    int id;
     int matricula_usuario;
     int codigo_livro;
     char data_retirada[11];
     char data_prevista[11];
    char data_devolucao[11];
    int devolvido;/// Ex: 0 para não devolvido, 1 para devolvido
}; typedef struct emprestimo emprestimo;

void desenhaBorda(){ 
     printf("📖========================📖 \n");//função que desenha borda

}
void limpaTela(){ // FUNÇÃO QUE LIMPA A TELA
    system ("CLS || clear");// se for linux =cls, se wind = clear
}
void cadastrarLivro(livro lista[], int posicao, int id_automatico) {
    
    // O sistema define automaticamente o código do livro na posição atual
    lista[posicao].codigo = id_automatico;
    printf("--- CADASTRANDO LIVRO (Codigo: %d) ---\n", id_automatico);
    printf("Digite o titulo do livro: \n");
    scanf(" %[^\n]s", lista[posicao].titulo); //%[^\n]s lê até apertar Enter
    printf("Digite o autor do livro: \n");
    scanf(" %[^\n]s", lista[posicao].autor);
    printf("Digite o ano de publicacao do livro: \n");
    scanf("%d", &lista[posicao].ano_de_publi);
    printf("Digite o genero do livro: \n");
    scanf(" %[^\n]s", lista[posicao].genero);
    printf("Digite a quantidade de livros disponiveis: \n");
    scanf("%d", &lista[posicao].quant_disp);
    printf("\nLivro cadastrado com sucesso!\n");
}
void cadastrarUsuario(usuario lista_usuarios[], int *tam_usuarios) {
    // o ponteiro aponta pro total de usuarios que, no caso é a posição do usuario no vetor 
    int posicao = *tam_usuarios; 
    printf("\n=== CADASTRO DE NOVO USUARIO ===\n");
    //gera a matrícula automaticamente com base na posição
    lista_usuarios[posicao].matricula = 202600 + posicao;
    printf("Matricula gerada automaticamente: %d\n", lista_usuarios[posicao].matricula);
    //lê o nome completo
    printf("Digite o nome completo: ");
    scanf(" %[^\n]", lista_usuarios[posicao].nome);
    //lê o curso
    printf("Digite o curso: ");
    scanf(" %[^\n]", lista_usuarios[posicao].curso);
    // inicializa o contador de empréstimos do usuário zerado
    lista_usuarios[posicao].qtd_emprestimos_ativos = 0;
    // soma 1 na variável total_usuarios que esta sendo apontada
    (*tam_usuarios)++;
    printf("Usuario cadastrado com sucesso!\n");
    printf("================================\n");
}
int main(){
setlocale(LC_ALL, "Portuguese");
livro lista_livros[100]; //espaço que guarda ate 100 fichas de livros
int total_livros = 0;    // Cont de livros cadastrados (começa em 0)
int proximo_codigo = 1;  // guarda o  próximo id (começa em 1)
int opcao; // variavel usada para guardar a opção escolhida  pelo usuário do menu
do{
     limpaTela();
    desenhaBorda();
    printf("\n📚     ACERVO DE LIVROS   📚\n");
    desenhaBorda();
printf("\n [1] -📘 Gerenciar Livros ");
printf("\n [2] -👥 Gerenciar Usuários");
printf("\n [3] -🤝 Realizar Empréstimo ");
printf("\n [4] -↩️ Registrar Devolução ");
printf("\n [5] -📊 Relatórios \n");
printf(" [6] -❌ Sair \n");
printf("Escolha uma opção: ");
scanf("%d", &opcao);
//resultado de acordo com a opção escolhida.
switch(opcao){
    case 1:
    if (total_livros < 100) {
       cadastrarLivro(lista_livros, total_livros, proximo_codigo);
     total_livros++;    // Avança para o próxima espaço do armário
    proximo_codigo++;  // Aumenta o número do ID para o próximo livro
   } else {
     printf("Erro: Limite de 100 livros atingido!\n");
}
    break;
    case 2:
    printf("opção 2 foi escolhida\n");
    break;
    case 3:
    printf("opção 3 foi escolhida\n");
    break;
    case 4:
    printf("opção 4 foi escolhida\n");
    break;
    case 5:
    printf("opção 5 foi escolhida\n");
    break;
    case 6:
    printf("opção 6 foi escolhida\n");
    break;
    default:
    printf("opção invalida\n");
    break;
}
}while (opcao != 6); // O programa continua rodando ATÉ o usuário digitar 6

return 0;
}
