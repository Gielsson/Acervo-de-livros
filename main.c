#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



int main(){
setlocale(LC_ALL, "Portuguese");
int mnenuPrincipal(){
int opção; // variavel usada para guardar a opção escolhida  pelo usuário do menu
while(opção <1 || opção > 3){
printf("Escolha uma opção: ");
printf("\n 1 - tarara 1");
printf("\n 2 - terere 2");
printf("\n 3 - tiriri 3\n");
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
    default:
    printf("opção invalida\n");
    break;
}
}
  return 0;
}
