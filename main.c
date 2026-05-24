#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


struct livro{
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
    char genero[50];
    int qtd_total[100];
    int qtd_disponivel;
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
    int devolvido;/// ideia: 0 para não devolvido, 1 para devolvido
}; typedef struct emprestimo emprestimo;

void menuPrincipal(){
int opcao; // variavel usada para guardar a opção escolhida  pelo usuário do menu
do{
    printf("\n=====ACERVO DE LIVROS=====\n");
printf("\n 1 - Gerenciar Livros ");
printf("\n 2 - Gerenciar Usuários");
printf("\n 3 - Realizar Empréstimo ");
printf("\n 4 - Registrar Devolução ");
printf("\n 5 - Relatórios \n");
printf("\n 6 - Sair \n");
printf("Escolha uma opção: ");
scanf("%d", &opção);
//resultado de acordo com a opção escolhida.
switch(opção){
    case 1:
    printf("opção 1 foi escolhida\n");
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

}
void cadastrarLivro //função bagunçada
int n, i;
printf("digite a quantidade de exemplare: \n");
scanf("%d", &n);
livro quant[n];
for(i=0; i<n; i++){
    printf("digite o codigo do novo livro: ")
}
int main(){
setlocale(LC_ALL, "Portuguese");



menuPrincipal();

return 0;
}
