#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



int main(){
setlocale(LC_ALL, "Portuguese");
int mnenuPrincipal(){
int opção; // variavel usada para guardar a opção escolhida  pelo usuário do menu
while(opção <1 || opção > 3){
printf("Escolha uma opção: ");
printf("\n 1 - Gerenciar Livros");
printf("\n 2 - Gerenciar Usuários");
printf("\n 3 - Realizar Empréstimo \n");
printf("\n 4 - Registrar Devolução");
printf("\n 5 - Relatórios");
printf("\n 6 - Sair \n");
scanf("%d", &opção);
//resultado de acordo com a opção escolhida.
swuitch(opção){
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
}
  return 0;
}
