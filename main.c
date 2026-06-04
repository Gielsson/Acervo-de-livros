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
int obterProximoCodigo(){ // descobre o ultimo id para gerar o proximo automaticamente
FILE *arquivo = fopen("livros.txt", "r");
if(arquivo == NULL){
    return 1; // SE O ARQ n existir, o primeiro arq sera 1
}
livro info; // variavel para armazenar os valores na struct livro
int ultimo_id=0;
while (fscanf(arquivo, "%d\n", &info.codigo) !=EOF){//// Le  arquivo inteiro linha por linha. O último ID que passar por aqui será guardado.
fscanf(arquivo, "%[^\n]\n", info.titulo);
fscanf(arquivo, "%[^\n]\n", info.autor);
fscanf(arquivo, "%d\n", &info.ano_de_publi);
fscanf(arquivo, "%[^\n]\n", info.genero);
fscanf(arquivo, "%d\n", &info.quant_disp);
fscanf(arquivo, "%d\n", &info.total_emprestimos);
ultimo_id = info.codigo;
}
fclose(arquivo);
return ultimo_id + 1; // oproximo codigo sera o ultimo + 1;
}
void cadastrarLivro(int id_automatico) {
    char continuar;
    do{
    livro novo;
    novo.codigo = id_automatico;
    limpaTela();
    printf("--- CADASTRANDO LIVRO (Codigo: %d) ---\n", id_automatico);
    printf("Digite o titulo do livro: \n");
    scanf(" %[^\n]s", novo.titulo); //%[^\n]s lê até apertar Enter
    printf("Digite o autor do livro: \n");
    scanf(" %[^\n]s", novo.autor);
    printf("Digite o ano de publicacao do livro: \n");
    scanf("%d", &novo.ano_de_publi);
    printf("Digite o genero do livro: \n");
    scanf(" %[^\n]s", novo.genero);
    printf("Digite a quantidade total de exemplares: \n");
    scanf("%d", &novo.qtd_total);

    novo.quant_disp = novo.qtd_total; // inicializando baseado na quant total
    novo.total_emprestimos = 0;
    FILE *arquivo = fopen("livros.txt", "a");// abre o arq em modo "a", o qual adiciona ao final
 if (arquivo == NULL){
    printf("Erro ao abrir o arquivo para salvar!\n");
 }
 fprintf(arquivo, "%d\n", novo.codigo); // gravando todos os campos da struct livro
    fprintf(arquivo, "%s\n", novo.titulo);
    fprintf(arquivo, "%s\n", novo.autor);
    fprintf(arquivo, "%d\n", novo.ano_de_publi);
    fprintf(arquivo, "%s\n", novo.genero);
    fprintf(arquivo, "%d\n", novo.qtd_total);
    fprintf(arquivo, "%d\n", novo.quant_disp);
    fprintf(arquivo, "%d\n", novo.total_emprestimos);
    fclose(arquivo);
    printf("\nLivro cadastrado com sucesso!\n");
    printf("deseja cadastrar outro livro? (S/N)");
    scanf(" %c", &continuar);
    getchar(); //engole a quebra de linha 
    if(continuar == 'S' || continuar == 's'){
    id_automatico = obterProximoCodigo();
    }
    } while (continuar == 'S' || continuar == 's');
}
void listarLivros(){
FILE *arquivo = fopen("livros.txt", "r");
if(arquivo ==NULL){
    printf(" Nenhum livro cadastrado no sistema ainda. \n");
}
livro info;
printf("\n---LIVROS CADASTRADOS NO ACERVO ---\n");
int encontrou= 0;
while (fscanf(arquivo, "%d\n", &info.codigo) !=EOF){
fscanf(arquivo, "%[^\n]s\n", info.autor);
fscanf(arquivo, "%d\n", &info.ano_de_publi);
fscanf(arquivo, "%[^\n]s\n", info.genero);
fscanf(arquivo, "%d\n", &info.qtd_total);
fscanf(arquivo, "%d\n", &info.quant_disp);
fscanf(arquivo, "%d\n", &info.total_emprestimos);
printf("Codigo: %-3d | Titulo:%-30s | Autor: %-20s | Quantidade total: %d\n", info.codigo,info.titulo, info.autor, info.qtd_total);
encontrou =1;
    
} if (!encontrou){
    printf("O arquivo esta vazio. \n");
}
fclose(arquivo);
}
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
    case 1: { //Descobre o próximo ID automaticamente dentro do arquivo e cadastra
    int proximo_codigo = obterProximoCodigo();
    cadastrarLivro(proximo_codigo);
break;
}
    case 2:
    do{
    	   limpaTela();
           desenhaBorda();
		   printf("\n   GERENCIAMENTO DE USUÁRIOS   \n");
		   desenhaBorda();
		   printf("\n [1] - Cadastrar usuários ");
		   printf("\n [2] - Listar Usuários");
		   printf("\n [3] - Buscar usuários ");
		   printf("\n [4] - Atualizar dados");
		   printf("\n [5] - Remover usuários \n");
		   printf(" [6] -❌ Sair \n");
		   printf("Escolha uma opção: ");
		   scanf("%d", &opcao2);
		   //resultado de acordo com a opção escolhida.
		
		   switch (opcao2) {
		    case 1: 
		    if (total_usuarios<1000) {
        
        cadastrarUsuario(vetor_usuarios, &total_usuarios);
        
        }else {
    
        printf("Erro: limite de usuarios atingidos!");
		}
		break;
		case 2:
		printf("opção 2 escolhida");
		break;
		case 3:
		printf("opção 3 escolhida");
		break;
		case 4:
		printf("opção 4 escolhida");
		break;
		case 5:
			  listarLivros();
	  listarLivros();
		break;
		case 6:
		printf("opção 6 escolhida");
		break;
		   }
		}
		while (opcao2 != 6);// enquanto o usuario nao optar por sair do menu secundario ele vai se repetir
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
