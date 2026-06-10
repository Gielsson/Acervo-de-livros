#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
     printf("=========================== \n");//função que desenha borda

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
fscanf(arquivo, "%d\n", &info.qtd_total);
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
    scanf(" %[^\n]", novo.titulo); //%[^\n]s lê até apertar Enter
    printf("Digite o autor do livro: \n");
    scanf(" %[^\n]", novo.autor);
    printf("Digite o ano de publicacao do livro: \n");
    while(scanf("%d", &novo.ano_de_publi)!=1){
        printf("\n ERRO: Ano invalido! Digite apenas numeros.\n");
        while(getchar() !='n'); //limpa buffer (letra que ficou traavdano teclado)
        printf("Digite o ano de publicacao do livro novamente: \n");
    }
    getchar(); 
    int genero_valido;
        do {
            genero_valido =1; // ja cmeça sasumindo que esta correto
    printf("Digite o genero do livro: \n");
    scanf(" %[^\n]", novo.genero);
    // Varre o texto usando a Tabela ASCII para achar números
    
    for (int i = 0; novo.genero[i] != '\0'; i++) {
     if (novo.genero[i] >= '0' && novo.genero[i] <= '9') {
    genero_valido = 0; // Se achou número, invalida
    break;
     }
    } if (genero_valido == 0) {
                printf("\n⚠️ Erro: Genero invalido! Nao use numeros.\n");
            }
        } while (genero_valido == 0); // Só repete se for inválido
        //validando a quantidade total
    printf("Digite a quantidade total de exemplares: \n");
   while (scanf("%d", &novo.qtd_total) !=1 ||novo.qtd_total <0){
printf("\n⚠️ Erro: Quantidade invalida! Digite um numero maior ou igual a 0.\n");
while (getchar() != '\n'); // Limpa o buffer
printf("Digite a quantidade total de exemplares novamente: \n");
   }
getchar();
    novo.quant_disp = novo.qtd_total; // inicializando baseado na quant total
    novo.total_emprestimos = 0;
    //gravando no arquivo
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
    continuar = tolower(continuar);
    
    if(continuar == 's'){
    id_automatico = obterProximoCodigo();
    }
    } while (continuar == 's');
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
fscanf(arquivo, "%[^\n]\n", info.titulo);
fscanf(arquivo, "%[^\n]\n", info.autor);
fscanf(arquivo, "%d\n", &info.ano_de_publi);
fscanf(arquivo, "%[^\n]\n", info.genero);
fscanf(arquivo, "%d\n", &info.qtd_total);
fscanf(arquivo, "%d\n", &info.quant_disp);
fscanf(arquivo, "%d\n", &info.total_emprestimos);

printf("Codigo: %d\n", info.codigo);
  printf("Titulo: %s\n", info.titulo);
 printf("Autor: %s\n", info.autor);
 printf("Quantidade total: %d\n", info.qtd_total);
printf("------------------------------------\n");
encontrou =1;
    
} if (!encontrou){
    printf("O arquivo esta vazio. \n");
}
fclose(arquivo);
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
void realizarEmprestimo(usuario lista_usuarios[], int tam_usuarios, emprestimo lista_emprestimos[], int *tam_emprestimos);
void realizarDevolucao(usuario lista_usuarios[], int tam_usuarios, livro lista_livros[], int tam_livros, emprestimo lista_emprestimos[], int tam_emprestimos);

void realizarEmprestimo(usuario lista_usuarios[], int tam_usuarios, emprestimo lista_emprestimos[], int *tam_emprestimos){
    int mat_busca;
    int cod_busca;
    int index_usuario = -1; // Começa com -1 para indicar que não encontrou

    limpaTela();
    desenhaBorda();
    printf("\n📚 EFETUAR NOVO EMPRÉSTIMO 📚\n");
    desenhaBorda();

    //1. COleta dados de quem está solicitando o empréstimo
    printf("Digite a matricula do usuário: ");
    scanf("%d", &mat_busca);

    //Busca sequencial no vetor de usuários cadastrados 
    for (int i=0; i<tam_usuarios; i++){
        if (lista_usuarios[i]. matricula == mat_busca){
            index_usuario = i; //Guarda a posição exata onde o usuário foi encontrado 
            break; //Encerra a busca, já que encontrou o usuário
        }
    }

//Se o índice continuar -1, o usuário não existe no sistema 
    if (index_usuario == -1){
    printf("\n❌ Erro: Usuario com a matricula %d não está cadastrado!\n", mat_busca);
    printf("Pressione Enter para voltar ao menu.");
    getchar(); getchar(); //Aguarda o usuário pressionar Enter
    return; //Finaliza a função (aborta o empréstimo)
    }

//Aplicação do limite de 3 livros ativos 
    if (lista_usuarios[index_usuario]. qtd_emprestimos_ativos >= 3){
    printf("\n ❌  Erro: o usuario %s já atingiu o limite de 3 emprestimos ativos!\n", lista_usuarios[index_usuario]. nome);
    printf("Não é permitido realizar mais empréstimos até que um livro seja devolvido.");
    printf("Pressione Enter para voltar ao menu.");
    getchar(); getchar(); //Aguarda o usuário pressionar Enter
    return; //(aborta o empréstimo)
    }

    printf("\n Usuario liberado para realizar o empréstimo! \n");


livro l_busca; //Variável temporária para ler os dados do arquivo 
int livro_encontrado = 0; //Flag para indicar se o livro foi encontrado

printf("\nDigite o codigo do livro desejado: ");
scanf("%d", &cod_busca);

//Abre o arquivo de livros em modo de leitura 
FILE *arq_livros = fopen("livros.txt", "r");

if (arq_livros == NULL){
    printf("\n❌ Erro: Não foi possível abrir o arquivo de livros!\n");
    printf("Pressione Enter para voltar.");
    getchar(); getchar(); //Aguarda o usuário pressionar Enter
    return; //Aborta a função
}

//Varre o arquivo linha por linha até o Fim do Arquivo (EOF)
while (fscanf(arq_livros, "%d", &l_busca.codigo) != EOF){
    //Lê os demais campos do livro do atual arquivo
    fscanf(arq_livros, " %[^\n]\n", l_busca.titulo);
    fscanf(arq_livros, " %[^\n]\n", l_busca.autor);
    fscanf(arq_livros, " %d\n", &l_busca.ano_de_publi);
    fscanf(arq_livros, " %[^\n]\n", l_busca.genero); 
    fscanf(arq_livros, " %d\n", &l_busca.qtd_total);
    fscanf(arq_livros, " %d\n", &l_busca.quant_disp);
    fscanf(arq_livros, " %d\n", &l_busca.total_emprestimos);

    //Se o código lido for o mesmo que o usuário digitou

    if (l_busca.codigo == cod_busca){
        livro_encontrado = 1; //Marca que o livro foi encontrado
    
        //Verificar se há exemplares disponíveis para empréstimo
        if (l_busca.quant_disp <= 0){
            printf("\n❌ Erro: O livro '%s' está esgotado no momento!\n", l_busca.titulo);
            printf("Não há exemplares disponíveis para emprestimo.\n");
            fclose(arq_livros); //Fecha o arquivo antes de retornar
            printf("Pressione Enter para voltar.");
            getchar(); getchar();
            return; //Aborta o empréstimo
        }

        break; //Encerra a busca, já que encontrou o livro
    }
}
fclose(arq_livros); //Fecha o arquivo de leitura

//Se a flag continuou 0, o livro não existe no sistema
if (livro_encontrado == 0){
    printf("\n❌ Erro: Código de livro %d não encontrado no sistema!\n", cod_busca);
    printf("Pressione Enter para voltar.");
    getchar(); getchar();
    return; //Aborta o empréstimo
} 

printf("\nLivro '%s' disponível! Pronto para registrar o empréstimo \n", l_busca.titulo);

//Gerar datas automáticas 
time_t t = time(NULL);
struct tm *info_tempo = localtime(&t);

char data_retirada[11];
char data_prevista[11];

//Formata a data atual do sistema para o formato DD/MM/AAAA
strftime(data_retirada, sizeof(data_retirada), "%d/%m/%Y", info_tempo);

//Soma o prazo de 14 dias em segundos (14 dias * 24 horas * 60 minutos * 60 segundos)
t += 14 * 24 * 60 * 60;
info_tempo = localtime(&t); //Atualiza a estrutura de tempo com a nova

//Formata a data prevista para devolução
strftime(data_prevista, sizeof(data_prevista), "%d/%m/%Y", info_tempo); 

FILE *arq_emp = fopen("emprestimos.txt", "a");
if (arq_emp == NULL){
    printf("\n❌ Erro: Não foi possível abrir ou criar o arquivo  'emprestimos.txt'!\n");
    printf("Pressione Enter para voltar.");
    getchar(); getchar();
    return; 
}

// O ID do novo empréstimo será o número total de empréstimos já registrados + 1
int novo_id = *tam_emprestimos + 1;

//Grava no arquivo conforme os campos definidos na struct emprestimo
fprintf(arq_emp, "%d\n", novo_id);
fprintf(arq_emp, "%d\n", mat_busca);
fprintf(arq_emp, "%d\n", cod_busca);
fprintf(arq_emp, "%s\n", data_retirada);
fprintf(arq_emp, "%s\n", data_prevista);
fprintf(arq_emp, "00/00/0000\n"); //Data de devolução real inicialmente vazia
fprintf(arq_emp, "0\n"); //Status de devolução inicialmente 0 (não devolvido)

fclose(arq_emp); //Fecha o arquivo de empréstimos

//Atualizar dados na memoria 
lista_usuarios[index_usuario]. qtd_emprestimos_ativos += 1; //Incrementa a quantidade de empréstimos ativos do usuário
(*tam_emprestimos)++; //Incrementa o total de empréstimos registrados no sistema

//Imprimir recibo de sucesso 
    printf("     🤝 EMPRÉSTIMO CONFIGURADO COM SUCESSO!       \n");
    printf("  🔹 ID da Operação:    %d\n", novo_id);
    printf("  🔹 Usuário Beneficiário: %s (Matrícula: %d)\n", lista_usuarios[index_usuario].nome, mat_busca);
    printf("  🔹 Livro Retirado:    %s\n", l_busca.titulo);
    printf("  🔹 Data de Retirada:  %s\n", data_retirada);
    printf("  🔹 Prazo Máximo:      %s (14 dias)\n", data_prevista);
    printf("==================================================\n");
    
    printf("\nPressione Enter para concluir e retornar ao menu...");
    getchar(); getchar();

} //fecha a função realizarEmprestimo

void realizarDevolucao(usuario lista_usuarios[], int tam_usuarios, livro lista_livros[], int tam_livros, emprestimo lista_emprestimos[], int tam_emprestimos){
    int id_busca;
    int emprestimo_encontrado = 0; //Flag para indicar se o empréstimo foi encontrado
    emprestimo emp_temp; //Variável temporária para ler os dados do arquivo de empréstimos

    limpaTela();
    desenhaBorda();
    printf("\n↩️    REGISTRAR DEVOLUÇÃO DE LIVRO    ↩️\n");
    desenhaBorda();

    printf("Digite o ID do emprestimo (Protocolo): ");
    scanf("%d", &id_busca);

    //Abre o arquivo de empréstimos em modo de leitura para verificar se o empréstimo existe 
    FILE *arq_emp = fopen("emprestimos.txt", "r");
    if (arq_emp == NULL){
        printf("\n❌ Erro: Não há empréstimos registrados no sistema!\n");
        printf("Pressione Enter para voltar.");
        getchar(); getchar();
        return; 
    }

//Criaremos um arquivo temporário para salvar as alterações do arquivo de empréstimos
FILE *arq_temp = fopen("temp_emprestimos.txt", "w");

//Varre o arquivo procurando pelo ID 
while (fscanf(arq_emp, "%d", &emp_temp.id) != EOF){
fscanf(arq_emp," %[^\n]\n", emp_temp.data_retirada);
fscanf(arq_emp," %[^\n]\n", emp_temp.data_prevista);
fscanf(arq_emp," %[^\n]\n", emp_temp.data_devolucao);
fscanf(arq_emp," %d\n", &emp_temp.devolvido);

//Se achou o ID digitado e o livro ainda NÃO foi devolvido
if (emp_temp.id == id_busca && emp_temp.devolvido == 0){
    emprestimo_encontrado = 1; 
    emp_temp.devolvido = 1; //Marca como devolvido

    //Pega a data atual do sistema para registrar a data de devolução real
    time_t t = time(NULL);
    struct tm *info_tempo = localtime(&t);
    strftime(emp_temp.data_devolucao, sizeof(emp_temp.data_devolucao), "%d/%m/%Y", info_tempo);
}

//Grava os dados (alterados ou não) no arquivo temporário
fprintf(arq_temp, "%d\n%d\n%d\n%s\n%s\n%s\n%d\n", 
        emp_temp.id, 
        emp_temp.matricula_usuario, 
        emp_temp.codigo_livro, 
        emp_temp.data_retirada, 
        emp_temp.data_prevista, 
        emp_temp.data_devolucao, 
        emp_temp.devolvido);
}

fclose(arq_emp);
fclose(arq_temp);

//Substitui o arquivo antigo pelo atualizado
remove("emprestimos.txt");
rename("temp_emprestimos.txt", "emprestimos.txt");

//Se a flag continuar 0, o empréstimo não foi encontrado ou já tinha sido devolvido anteriormente
if (emprestimo_encontrado == 0){
    printf("\n❌ Erro: Emprestimo com ID %d não encontrado ou já foi devolvido!\n", id_busca);
    printf("Pressione Enter para voltar.");
    getchar(); getchar();
    return;
}

///Atualização do estoque do livro no arquivo "livros.txt
livro liv_temp; //Variável temporária para ler os dados do arquivo de livros
FILE *arq_livros = fopen("livros.txt", "r");
FILE *arq_livros_temp = fopen("temp_livros.txt", "w");

if (arq_livros != NULL && arq_livros_temp != NULL){
    // Varre o arquivo de livros copiando os dados para o temporário
     while (fscanf(arq_livros, "%d", &liv_temp.codigo) != EOF){
        fscanf(arq_livros, " %[^\n]", liv_temp.titulo);
        fscanf(arq_livros, " %[^\n]", liv_temp.autor);
        fscanf(arq_livros, " %d\n", &liv_temp.ano_de_publi);
        fscanf(arq_livros, " %[^\n]", liv_temp.genero); 
        fscanf(arq_livros, " %d\n", &liv_temp.qtd_total);
        fscanf(arq_livros, " %d\n", &liv_temp.quant_disp);
        fscanf(arq_livros, " %d\n", &liv_temp.total_emprestimos);

//Se o livro for devolvido neste empréstimo, incrementa o estoque disponível 
if (liv_temp.codigo == emp_temp.codigo_livro){
    liv_temp.quant_disp += 1;
}

//Grava o registro no arquivo temporário de livros 
fprintf(arq_livros_temp, "%d\n%s\n%s\n%d\n%s\n%d\n%d\n%d\n", 
        liv_temp.codigo, 
        liv_temp.titulo, 
        liv_temp.autor, 
        liv_temp.ano_de_publi, 
        liv_temp.genero, 
        liv_temp.qtd_total, 
        liv_temp.quant_disp, 
        liv_temp.total_emprestimos);
    }

    fclose(arq_livros);
    fclose(arq_livros_temp);

    //Substitui o arquivo antigo pelo atualizado
    remove("livros.txt");
    rename("temp_livros.txt", "livros.txt");
}

//Atualização do contador do usuário na memória 
for (int i=0; i<tam_usuarios; i++){
    if (lista_usuarios[i].matricula == emp_temp.matricula_usuario){
        if (lista_usuarios[i].qtd_emprestimos_ativos > 0) {
            lista_usuarios[i].qtd_emprestimos_ativos -= 1;
        }
        break; //Encerra o loop após encontrar o usuário
    }
}

//Mensagem de sucesso final e recibo da operação 
    printf("     🤝 DEVOLUÇÃO REGISTRADA COM SUCESSO!       \n");
    printf("  🔹 ID do Empréstimo:   %d\n", emp_temp.id);
    printf("  🔹 Código do Livro:    %d\n", emp_temp.codigo_livro);
    printf("  🔹 Matrícula do Aluno: %d\n", emp_temp.matricula_usuario);
    printf("  🔹 Data de Devolução:  %s\n", emp_temp.data_devolucao);

    printf("\nPressione Enter para concluir e retornar ao menu...");
    getchar(); getchar();

} // fecha a função realizarDevolucao
int main(){
setlocale(LC_ALL, "Portuguese");
usuario vetor_usuarios[1000];
    int total_usuarios = 0;
int opcao, opcao2,opcaoSecundar; // variavel usada para guardar a opção escolhida  pelo usuário do menu
do{
     limpaTela();
    desenhaBorda();
    printf("\n     ACERVO DE LIVROS   \n");
    desenhaBorda();
printf("\n [1] - Gerenciar Livros ");
printf("\n [2] - Gerenciar Usuarios");
printf("\n [3] - Realizar Emprestimo ");
printf("\n [4] - Registrar Devolucao ");
printf("\n [5] - Relatorios \n");
printf(" [6] - Sair \n");
printf("Escolha uma opcao: ");
scanf("%d", &opcao);
//resultado de acordo com a opção escolhida.
switch(opcao){
    case 1:
    do {
                    limpaTela();
                        desenhaBorda();
                    printf("\n  GERENCIAMENTO DE LIVROS   \n");
                         desenhaBorda();
                    printf("\n [1] - Cadastrar livro");
                    printf("\n [2] - Listar livros");
                    printf("\n [3] - Buscar livro");
                    printf("\n [4] - Voltar ao Menu Principal\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &opcaoSecundar);
                    getchar();
                    switch(opcaoSecundar) {
    case 1: {
                            int proximo_codigo = obterProximoCodigo();
                            cadastrarLivro(proximo_codigo);
                            break;
                        }
    case 2:
                            limpaTela();
                            listarLivros();
                            printf("\nPressione Enter para voltar...");
                            getchar(); // Pausa para o usuário ler
                            break;
    case 3:
                            printf("\nFunção de busca blablabla.\n");
                            printf("Pressione Enter para voltar...");
                            getchar();
                            break;
     case 4:
                            break;
                        default:
                            printf("\nOpção inválida!\n");
                            printf("Pressione Enter para tentar novamente...");
                            getchar();
                            break;
                    }
                } while(opcaoSecundar != 4);
                break;

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
           getchar();
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
} while (opcao != 6); // O programa continua rodando ATÉ o usuário digitar 6

return 0;
}
