#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>


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

// Lê um livro inteiro do arquivo e retorna a struct livro preencida.
livro lerLivro(FILE *arq) {
    livro dado;
    fscanf(arq, "%d\n", &dado.codigo);
    fscanf(arq, "%[^\n]\n", dado.titulo);
    fscanf(arq, "%[^\n]\n", dado.autor);
    fscanf(arq, "%d\n", &dado.ano_de_publi);
    fscanf(arq, "%[^\n]\n", dado.genero);
    fscanf(arq, "%d\n", &dado.qtd_total);
    fscanf(arq, "%d\n", &dado.quant_disp);
    fscanf(arq, "%d\n", &dado.total_emprestimos);
    return dado;
}
//função para ler os 
void lerEmprestimos(emprestimo vetor[], int *total) {
    FILE *arquivo = fopen("emprestimos.txt", "r");
    if (arquivo == NULL) return;

    while (fscanf(arquivo, "%d\n", &vetor[*total].id) != EOF) {
        fscanf(arquivo, "%d\n", &vetor[*total].matricula_usuario);
        fscanf(arquivo, "%d\n", &vetor[*total].codigo_livro);
        fscanf(arquivo, "%[^\n]\n", vetor[*total].data_retirada);
        fscanf(arquivo, "%[^\n]\n", vetor[*total].data_prevista);
        fscanf(arquivo, "%[^\n]\n", vetor[*total].data_devolucao);
        fscanf(arquivo, "%d\n", &vetor[*total].devolvido);
        (*total)++;
    }
    fclose(arquivo);
}
void gravarLivro(FILE *arq, livro dado){ // grava um livro no arquivo
    fprintf(arq, "%d\n", dado.codigo);
    fprintf(arq, "%s\n", dado.titulo);
    fprintf(arq, "%s\n", dado.autor);
    fprintf(arq, "%d\n", dado.ano_de_publi);
    fprintf(arq, "%s\n", dado.genero);
    fprintf(arq, "%d\n", dado.qtd_total);
    fprintf(arq, "%d\n", dado.quant_disp);
    fprintf(arq, "%d\n", dado.total_emprestimos);
}
// Percorre o arquivo inteiro para descobrir qual foi o último código gravado.
int obterProximoCodigo(){ // descobre o ultimo id para gerar o proximo automaticamente
FILE *arquivo = fopen("livros.txt", "r");
if(arquivo == NULL){
    return 1; // SE O ARQ n existir, o primeiro arq sera 1
}
livro aux; // variavel para armazenar os valores na struct livro
int ultimo_id=0;
// Lê livro por livro até o fim do arquivo, guardando sempre o último código visto
while (fscanf(arquivo, "%d\n", &aux.codigo) != EOF){
        fscanf(arquivo, "%[^\n]\n", aux.titulo);
        fscanf(arquivo, "%[^\n]\n", aux.autor);
        fscanf(arquivo, "%d\n", &aux.ano_de_publi);
        fscanf(arquivo, "%[^\n]\n", aux.genero);
        fscanf(arquivo, "%d\n", &aux.qtd_total);
        fscanf(arquivo, "%d\n", &aux.quant_disp);
        fscanf(arquivo, "%d\n", &aux.total_emprestimos);
     
        ultimo_id = aux.codigo;  // vai guardando o último
    }
    fclose(arquivo);
    return ultimo_id + 1;
}

void cadastrarLivro(int ultimo_id) { // ultimo id lido por obterProximoCodigo(); incrementado a cada novo cadastro
    char continuar;
    do {
        livro novo;
        novo.codigo = ultimo_id;
        limpaTela();
        printf("--- CADASTRANDO LIVRO (Codigo: %d) ---\n", ultimo_id);
    printf("Digite o titulo do livro: \n");
    scanf(" %[^\n]", novo.titulo); //%[^\n]s lê até apertar Enter
    printf("Digite o autor do livro: \n");
    scanf(" %[^\n]", novo.autor);
    printf("Digite o ano de publicacao do livro: \n");
    while(scanf("%d", &novo.ano_de_publi)!=1){
        printf("\n ERRO: Ano invalido! Digite apenas numeros.\n");
        while(getchar() !='\n'); //limpa buffer (letra que ficou traavdano teclado)
        printf("Digite o ano de publicacao do livro novamente: \n");
    }
    getchar(); 
    int genero_valido;
        do {
            genero_valido =1; // ja começa sasumindo que esta correto
    printf("Digite o genero do livro: \n");
    scanf(" %[^\n]", novo.genero);
    // Varre o texto usando a Tabela ASCII para achar números
    
    for (int i = 0; novo.genero[i] != '\0'; i++) {
     if (novo.genero[i] >= '0' && novo.genero[i] <= '9') {
    genero_valido = 0; // Se achou número, invalida
    break;
     }
    } 
    if (genero_valido == 0) {
                printf("\n Erro: Genero invalido! Nao use numeros.\n");
            }
        } while (genero_valido == 0); // Só repete se for inválido
        //validando a quantidade total
    printf("Digite a quantidade total de exemplares: \n");
   while (scanf("%d", &novo.qtd_total) !=1 ||novo.qtd_total <0){
printf("\n Erro: Quantidade invalida! Digite um numero maior ou igual a 0.\n");
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
    return;
 }
  gravarLivro(arquivo, novo);
  fclose(arquivo);
  
  printf("\nLivro cadastrado com sucesso!\n");
        printf("Deseja cadastrar outro livro? (S/N): ");
        scanf(" %c", &continuar);
        getchar();
        continuar = tolower(continuar);
    
    if(continuar == 's'){
            ultimo_id = obterProximoCodigo();
        }
    } while (continuar == 's');
}

    void listarLivros(){
FILE *arquivo = fopen("livros.txt", "r");
if(arquivo ==NULL){
    printf(" Nenhum livro cadastrado no sistema ainda. \n");
return;
}
livro info;
int encontrou= 0;
printf("\n---LIVROS CADASTRADOS NO ACERVO ---\n");


while (fscanf(arquivo, "%d\n", &info.codigo) !=EOF){
 // lê os demais campos manualmente pois o codigo já foi lido  
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
  printf("Disponiveis: %d\n",    info.quant_disp);
printf("------------------------------------\n");
encontrou =1;
    
} if (!encontrou){
    printf("O arquivo esta vazio. \n");

} fclose(arquivo);
    }
void buscarLivro() {
    FILE *arquivo = fopen("livros.txt", "r");
    if (arquivo == NULL) {
        printf("\n Nenhum livro cadastrado no sistema ainda.\n");
        return;
    }

    limpaTela();
    desenhaBorda();
    printf("\n BUSCAR LIVRO NO ACERVO \n");
    desenhaBorda();

    int tipo_busca;
    printf("[1] Buscar por Codigo\n");
    printf("[2] Buscar por Titulo\n");
    printf("Escolha o tipo de busca: ");
    scanf("%d", &tipo_busca);
    getchar(); // Limpa o buffer

    int cod_busca = -1; // começa com -1 pois ainda nao foi digitado nenhum codigo
    char termo_busca[250] = "";

    if (tipo_busca == 1) {
        printf("Digite o codigo do livro: ");
        scanf("%d", &cod_busca);
        getchar();
    } else if (tipo_busca == 2) {
        printf("Digite o titulo (ou parte dele): ");
        scanf(" %[^\n]", termo_busca);
        getchar();
        
        // Coloca tudo em letra minuscula para a busca nao diferenciar maiuscula de minuscula
        for(int i = 0; termo_busca[i]; i++) {
            termo_busca[i] = tolower(termo_busca[i]);
        }
    } else {
        printf("\n Opcao invalida!\n");
        fclose(arquivo);
        return;
    }

    livro info;
    int encontrou = 0; // controla se achou algum livro ou nao

     // Fica lendo livro por livro do arquivo ate chegar no final
    while (fscanf(arquivo, "%d\n", &info.codigo) != EOF) {
        fscanf(arquivo, "%[^\n]\n", info.titulo);
        fscanf(arquivo, "%[^\n]\n", info.autor);
        fscanf(arquivo, "%d\n", &info.ano_de_publi);
        fscanf(arquivo, "%[^\n]\n", info.genero);
        fscanf(arquivo, "%d\n", &info.qtd_total);
        fscanf(arquivo, "%d\n", &info.quant_disp);
        fscanf(arquivo, "%d\n", &info.total_emprestimos);

        int corresponde = 0;  // verfica se esse livro bate com o que o usuario procurou

        if (tipo_busca == 1 && info.codigo == cod_busca) {
           
             corresponde = 1; //código bate exatamente
        } else if (tipo_busca == 2) {
           // coloca o titulo do livro em minusculo tambem para n alterar o original
            char titulo_minusculo[250];
            strcpy(titulo_minusculo, info.titulo);

            for(int i = 0; titulo_minusculo[i]; i++) {
                titulo_minusculo[i] = tolower(titulo_minusculo[i]);
            }
            // strstr verifica se o que o usuario digitou esta dentro do titulo e retorna NULL se não encontrar o termo dentro do título
            if (strstr(titulo_minusculo, termo_busca) != NULL) {
                corresponde = 1;
            }
        }

        if (corresponde) {
            if (!encontrou) {
                printf("\n --- LIVRO(S) ENCONTRADO(S) ---\n");
            }
            // mostra os dados do livro encontrado
            printf("Codigo: %d\n", info.codigo);
            printf("Titulo: %s\n", info.titulo);
            printf("Autor: %s\n", info.autor);
            printf("Genero: %s\n", info.genero);
            printf("Ano: %d\n", info.ano_de_publi);
            printf("Disponivel: %d/%d\n", info.quant_disp, info.qtd_total);
           
            printf("------------------------------------\n");
           
            encontrou = 1;
            // se achou pelo codigo nao precisa continuar procurando
            if (tipo_busca == 1) break; // Se buscou por ID único, pode parar o loop
        }
    }

    if (!encontrou) {
        printf("\n Nenhum livro correspondente foi encontrado.\n");
    }

    fclose(arquivo);
}
void editarLivro(){ // Permite alterar título, autor, gênero, ano e quantidade de um livro já cadastrado
    limpaTela();
    desenhaBorda();
    printf("\nEDITAR LIVRO\n");
    desenhaBorda();
 
    int cod_busca;
    printf("Digite o codigo do livro que deseja editar: ");
    scanf("%d", &cod_busca);
    getchar();
 
    FILE *arq_orig = fopen("livros.txt", "r");
    if(arq_orig == NULL){
        printf("\nNenhum livro cadastrado no sistema.\n");
        return;
    }
 //lê o original e grava tudo no arquivo temp
    // Arquivo temporario recebe todos os livros, com o escolhido já alterado
    FILE *arq_temp = fopen("temp_livros.txt", "w");
    if(arq_temp == NULL){
        printf("\nErro ao criar arquivo temporario!\n");
      fclose(arq_orig);
        return;
    }
   livro aux;
    int encontrou = 0;
 
    while(fscanf(arq_orig, "%d\n", &aux.codigo) != EOF){
        fscanf(arq_orig, "%[^\n]\n", aux.titulo);
        fscanf(arq_orig, "%[^\n]\n", aux.autor);
        fscanf(arq_orig, "%d\n", &aux.ano_de_publi);
        fscanf(arq_orig, "%[^\n]\n", aux.genero);
        fscanf(arq_orig, "%d\n", &aux.qtd_total);
        fscanf(arq_orig, "%d\n", &aux.quant_disp);
        fscanf(arq_orig, "%d\n", &aux.total_emprestimos);
 
        // Só edita o livro q o código bate com o digitado
        if(aux.codigo == cod_busca){
            encontrou = 1;
            printf("\nLivro encontrado: %s\n", aux.titulo);
            printf("Deixe o campo em branco e pressione Enter para manter o valor atual.\n\n");
 
            char entrada[256];
 printf("Titulo atual [%s]: ", aux.titulo);
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0'; // strcspn descobre a posição, se n achar, ele devolve o tamanho total da string
             // remove o '\n' que fgets captura
            if(strlen(entrada) > 0) strcpy(aux.titulo, entrada);
 
            printf("Autor atual [%s]: ", aux.autor);
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0'; // strcspn indica posição, em inteiro,  do primeiro espaço na string
            if(strlen(entrada) > 0) strcpy(aux.autor, entrada); // se tamanho >  0, usuario digitou algo.
// Para cada espaço de informação, lê a nova entrada; se vazia, mantém o atual

printf("Genero atual [%s]: ", aux.genero);
            fgets(entrada, sizeof(entrada), stdin);
            entrada[strcspn(entrada, "\n")] = '\0';
            if(strlen(entrada) > 0){
                // faz uma revalidação, pois gênero não pode conter números
                int genero_valido = 1;
                for(int i = 0; entrada[i] != '\0'; i++){
                    if(entrada[i] >= '0' && entrada[i] <= '9'){
                        genero_valido = 0;
                        break;
                    }
                }
                if(genero_valido) strcpy(aux.genero, entrada);
                else printf("Genero invalido, mantendo o anterior.\n");


            }
 
            // se 0, não alterar
            printf("Ano atual [%d] (0 para manter): ", aux.ano_de_publi);
            int novo_ano;
            scanf("%d", &novo_ano);
            getchar();
            if(novo_ano != 0) aux.ano_de_publi = novo_ano;
 
            printf("Quantidade total atual [%d] (0 para manter): ", aux.qtd_total);
            int nova_qtd;
            scanf("%d", &nova_qtd);
            getchar();
            if(nova_qtd > 0){
                // Calcula quantos exemplares estão fora (emprestados) para manter a conta certa
                int em_uso  = aux.qtd_total - aux.quant_disp;
                aux.qtd_total = nova_qtd;
                aux.quant_disp  = nova_qtd - em_uso;
                if(aux.quant_disp < 0) aux.quant_disp = 0; // n deixa que tenha valor negativo
            } // Grava o livro, mesmi q seja alterado ou não no arquivo temporário
        }
        gravarLivro(arq_temp, aux);
    }
         fclose(arq_orig);
    fclose(arq_temp);// Substitui o arquivo original pelo temporário, que tem os dados atualizados
                //função pra ler os usuarios

    remove("livros.txt");
    rename("temp_livros.txt", "livros.txt");
 
    if(encontrou) {
        printf("\nLivro atualizado com sucesso!\n");
    }
    else {
 printf("\nCodigo %d nao encontrado.\n", cod_busca);
 }
}

void removerLivro(){ // Remove um livro do acervo pelo código
    limpaTela();
    desenhaBorda();
    printf("\nREMOVER LIVRO\n");
    desenhaBorda();
 
    int cod_busca;
    printf("Digite o codigo do livro que deseja remover: ");
    scanf("%d", &cod_busca);
    getchar();
 
    FILE *arq_orig = fopen("livros.txt", "r");
    if(arq_orig == NULL){
        printf("\nNenhum livro cadastrado no sistema.\n");
        return;
    }
 
    FILE *arq_temp = fopen("temp_livros.txt", "w");
    if(arq_temp == NULL){
        printf("\nErro ao criar arquivo temporario!\n");
        fclose(arq_orig);
        return;
    }
 livro aux;
    int encontrou = 0;
 
 while(fscanf(arq_orig, "%d\n", &aux.codigo) != EOF){
        fscanf(arq_orig, "%[^\n]\n", aux.titulo);
        fscanf(arq_orig, "%[^\n]\n", aux.autor);
        fscanf(arq_orig, "%d\n", &aux.ano_de_publi);
        fscanf(arq_orig, "%[^\n]\n", aux.genero);
        fscanf(arq_orig, "%d\n", &aux.qtd_total);
        fscanf(arq_orig, "%d\n", &aux.quant_disp);
        fscanf(arq_orig, "%d\n", &aux.total_emprestimos);
 
        if(aux.codigo == cod_busca){
            encontrou = 1;
 // não permite remover se houver exemplares emprestados

            if(aux.quant_disp < aux.qtd_total){//significa que alguém está com o livro.
                printf("\nNao e possivel remover: ha exemplares emprestados no momento.\n");
                fclose(arq_orig);
                fclose(arq_temp);
                remove("temp_livros.txt"); // descarta o temp incompleto
                return;
            }
             printf("\nLivro '%s' removido.\n", aux.titulo);
        } else {
            // Todos os outros livros são copiados normalmente para o temp
            gravarLivro(arq_temp, aux);
        }
    }
 
    fclose(arq_orig);
    fclose(arq_temp);
 
    remove("livros.txt");
    rename("temp_livros.txt", "livros.txt");
 
    if(!encontrou) printf("\nCodigo %d nao encontrado.\n", cod_busca);
}

// Exibe todos os usuários que estão com um exemplar de um livro específico no momento.
//e recebe o vetor de usuários para conseguir mostrar o nome junto à matrícula.
void informarEmprestimosDoLivro(usuario lista_usuarios[], int tam_usuarios){
    limpaTela();
    desenhaBorda();
    printf("\n  EMPRESTIMOS ATIVOS \n");
    desenhaBorda();

    int cod_busca;
    printf("Digite o codigo do livro: ");
    scanf("%d", &cod_busca);
    getchar();

    // Abre o acervo para confirmar que o código existe antes de procurar empréstimos
    FILE *arq_livros = fopen("livros.txt", "r");
    if(arq_livros == NULL){
        printf("\nNenhum livro cadastrado no sistema.\n");
        return;
    }

    livro aux;
    int livro_encontrado = 0;
    char titulo_livro[250] = ""; // guarda o título para usar nas mensagens

    while(fscanf(arq_livros, "%d\n", &aux.codigo) != EOF){
        fscanf(arq_livros, "%[^\n]\n", aux.titulo);
        fscanf(arq_livros, "%[^\n]\n", aux.autor);
        fscanf(arq_livros, "%d\n", &aux.ano_de_publi);
        fscanf(arq_livros, "%[^\n]\n", aux.genero);
        fscanf(arq_livros, "%d\n", &aux.qtd_total);
        fscanf(arq_livros, "%d\n", &aux.quant_disp);
        fscanf(arq_livros, "%d\n", &aux.total_emprestimos);

        if(aux.codigo == cod_busca){
            livro_encontrado = 1;
            strcpy(titulo_livro, aux.titulo); // salva o título para exibir depois
            break; // achou o livro, não precisa continuar lendo o arquivo
        }
    }
    fclose(arq_livros);

    // Se o código não existir no acervo, não faz sentido procurar empréstimos
    if(!livro_encontrado){
        printf("\nCodigo %d nao encontrado no acervo.\n", cod_busca);
        return;
    }

    // Abre o arquivo de empréstimos para procurar registros desse livro
    FILE *arq_emp = fopen("emprestimos.txt", "r");
    if(arq_emp == NULL){
        // Arquivo não existe ainda, ou seja, nenhum empréstimo foi feito no sistema
        printf("\nO livro '%s' nao possui emprestimos ativos.\n", titulo_livro);
        return;
    }

    emprestimo emp;
    int achou_emprestimo = 0; //se continuar 0 no final, nenhum empréstimo ativo foi achado

    while(fscanf(arq_emp, "%d\n", &emp.id) != EOF){
        fscanf(arq_emp, "%d\n", &emp.matricula_usuario);
        fscanf(arq_emp, "%d\n", &emp.codigo_livro);
        fscanf(arq_emp, "%[^\n]\n", emp.data_retirada);
        fscanf(arq_emp, "%[^\n]\n", emp.data_prevista);
        fscanf(arq_emp, "%[^\n]\n", emp.data_devolucao);
        fscanf(arq_emp, "%d\n", &emp.devolvido);

        // so interessa o livro certo e que ainda não foi devolvido, se devolvido == 0
        if(emp.codigo_livro == cod_busca && emp.devolvido == 0){

            // Imprime o cabeçalho só uma vez, na primeira vez encontrada
            if(!achou_emprestimo){
                printf("\nLivro: %s (Codigo: %d)\n", titulo_livro, cod_busca);
                printf("--- EMPRESTIMOS ATIVOS ---\n");
            }
            achou_emprestimo = 1;

            // Busca o nome do usuário no vetor em memória usando a matrícula como chave
            char nome_usuario[250] = "Usuario nao encontrado"; // valor padrão caso não ache
            for(int k = 0; k < tam_usuarios; k++){
                if(lista_usuarios[k].matricula == emp.matricula_usuario){
                    strcpy(nome_usuario, lista_usuarios[k].nome);
                    break; // achou o usuário, encerra a busca no vetor
                }
            }

            printf("ID Emprestimo: %d\n",  emp.id);
            printf("Usuario: %s\n", nome_usuario);
            printf("Matricula: %d\n",  emp.matricula_usuario);
            printf("Retirada: %s\n", emp.data_retirada);
            printf("Prazo devolucao: %s\n", emp.data_prevista);
            printf("----------------------------\n");
        }
    }
    fclose(arq_emp);

    // Se continuou 0, o livro existe mas não tem nenhum exemplar fora no momento
    if(!achou_emprestimo){
        printf("\nO livro '%s' nao possui emprestimos ativos no momento.\n", titulo_livro);
    }
}
//carrega todos os usuários do arquivo "usuarios.txt" para a memória
void LerUsuarios(usuario lista_usuarios[], int *tam_usuarios){
    FILE *arquivo = fopen("usuarios.txt", "r");

    if(arquivo == NULL){
        return;
    }
 // le um usuario por vez ate chegar no fim do arquivo
    while(fscanf(arquivo, "%d\n", &lista_usuarios[*tam_usuarios].matricula) != EOF){
        fscanf(arquivo, "%[^\n]\n", lista_usuarios[*tam_usuarios].nome);
        fscanf(arquivo, "%[^\n]\n", lista_usuarios[*tam_usuarios].curso);
        fscanf(arquivo, "%d\n", &lista_usuarios[*tam_usuarios].qtd_emprestimos_ativos);
    (*tam_usuarios)++; // avanca para a proxima posicao livre do vetor
    }

    fclose(arquivo);

}
 //descobre qual deve ser a matrícula do PRÓXIMO usuário
int obterProximaMatricula(){
    FILE *arquivo = fopen("usuarios.txt", "r");
// se o arquivo ainda não existe, significa que nenhum usuário foi cadastrado
	
    if(arquivo == NULL){
        return 202600;//então o primeiro usuario vai ter essa matricula
    }

    usuario info;
    int ultimaMatricula = 202599; // valor base: uma abaixo de 202600, isso garante que, se o arquivo existir mas estiver vazio,


    while(fscanf(arquivo, "%d\n", &info.matricula) != EOF){
        fscanf(arquivo, "%[^\n]\n", info.nome);
        fscanf(arquivo, "%[^\n]\n", info.curso);
        fscanf(arquivo, "%d\n", &info.qtd_emprestimos_ativos);

    //quando o laço terminar, ela vai conter a matrícula do ÚLTIMO usuário cadastrado
        ultimaMatricula = info.matricula;
    }

    fclose(arquivo);

    return ultimaMatricula + 1; //returna a matricula do usuario que esta sendo cadastrado
}
// registra um ou mais novos usuários no sistema
void cadastrarUsuario(usuario lista_usuarios[], int *tam_usuarios) {
    char continuar;// guarda a resposta (S/N) se o usuário quer cadastrar outro
//usamos do while pra cadastrar pelo menos 1 usuario antes de perguntar se quer continuar
    do {
        // impede cadastro se o vetor ja estiver cheio
        if (*tam_usuarios >= 1000) {
            printf("\n Erro: Limite de 1000 usuarios atingido!\n");
            return;
        }
 
        int posicao = *tam_usuarios; // proxima posicao livre no vetor
        printf("\n=== CADASTRO DE NOVO USUARIO ===\n");
 
        // gera a matricula automaticamente; o usuario nao precisa digitar
        lista_usuarios[posicao].matricula = obterProximaMatricula();
        printf("Matricula gerada: %d\n", lista_usuarios[posicao].matricula);
 
        printf("Digite o nome completo: ");
        scanf(" %[^\n]", lista_usuarios[posicao].nome);
        getchar();
 
        printf("Digite o curso: ");
        scanf(" %[^\n]", lista_usuarios[posicao].curso);
        getchar();
 
        lista_usuarios[posicao].qtd_emprestimos_ativos = 0; // novo usuario comeca sem emprestimos

         // abre o arquivo em modo "a" para adicionar ao final sem apagar os existentes
        FILE *arquivo = fopen("usuarios.txt", "a");
        if (arquivo == NULL) {
            printf("Erro ao abrir arquivo!\n");
            return;
        }

        fprintf(arquivo, "%d\n", lista_usuarios[posicao].matricula);
        fprintf(arquivo, "%s\n", lista_usuarios[posicao].nome);
        fprintf(arquivo, "%s\n", lista_usuarios[posicao].curso);
        fprintf(arquivo, "%d\n", lista_usuarios[posicao].qtd_emprestimos_ativos);
        fclose(arquivo);

        printf("Usuario cadastrado com sucesso!\n");
        printf("================================\n");
        
        // atualiza o contador geral da main e so incrementa depois de gravar com sucesso
        (*tam_usuarios)++;

        printf("\nDeseja continuar cadastrando? (S/N): ");
        scanf(" %c", &continuar);
        getchar();
        continuar = tolower(continuar);//transgorma o caractere lido em minusculo para fazer uma comparação mais precisa

    } while(continuar == 's'); 
}
//lista os usuarios cadastrados no sistema. Ela lê diretamente do vetor na memoria (lista_usuarios), e não do
// arquivo. Isso é mais rápido, já que os dados já foram carregados no início
// do programa pela função LerUsuarios.
void ListarUsuarios(usuario lista_usuarios[], int tam_usuarios){

    limpaTela();
     // avisa se ainda nao ha nenhum usuario no sistema
    if (tam_usuarios == 0) {
        printf("Nenhum usuario cadastrado ainda.\n");
        return;
    }
//printa todos os usuarios do vetor 
    for(int i=0;i < tam_usuarios;i++){
        printf("Nome: %s\n", lista_usuarios[i].nome);
        printf("Curso: %s\n", lista_usuarios[i].curso);
        printf("Matricula: %d\n", lista_usuarios[i].matricula);
        printf("Emprestimos ativos: %d\n", lista_usuarios[i].qtd_emprestimos_ativos);
desenhaBorda();
    }    
}
//função de busca de usuario por matricula ou nome
void buscarUsuario(usuario lista_usuarios[], int tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n BUSCAR USUARIO NO SISTEMA \n");
    desenhaBorda();
 // nao busca se ainda não há nenhum usuário no sistema
    if (tam_usuarios == 0) {
        printf("\n Nenhum usuario cadastrado no sistema ate o momento.\n");
        return;
    }

    int tipo_busca;
    printf("[1] Buscar por Matricula\n");
    printf("[2] Buscar por Nome\n");
    printf("Escolha o tipo de busca: ");
    scanf("%d", &tipo_busca);
    getchar(); // limpa o buffer

    int mat_busca = -1;           // -1 indica que nenhuma matricula foi digitada ainda
    char termo_busca[250] = "";
	
    if (tipo_busca == 1) {
        printf("Digite a matricula do usuario: ");
        scanf("%d", &mat_busca);
        getchar();
    } else if (tipo_busca == 2) {
        printf("Digite o nome (ou parte dele): ");
        scanf(" %[^\n]", termo_busca);
        getchar();
        
        // transforma o termo digitado para minúsculo, caractere por caractere.
        for(int i = 0; termo_busca[i]; i++) {
            termo_busca[i] = tolower(termo_busca[i]);
        }
    } else {
		 //se o usuário digitou uma opção diferente de 1 ou 2, avisa e sai
        printf("\n Opcao invalida!\n");
        return;
    }

    int encontrou = 0; // controla se já achamos pelo menos um usuário

    // percorre o vetor que já está na memória
    for (int i = 0; i < tam_usuarios; i++) {
        int corresponde = 0; //indica se esse usuário específico bate com a busca

        if (tipo_busca == 1 && lista_usuarios[i].matricula == mat_busca) {
            corresponde = 1;
        } else if (tipo_busca == 2) {
            // cria cópia em minúsculo do nome cadastrado para comparar sem alterar a string original 
            char nome_minusculo[250];
            strcpy(nome_minusculo, lista_usuarios[i].nome);
            for(int j = 0; nome_minusculo[j]; j++) {
                nome_minusculo[j] = tolower(nome_minusculo[j]);
            }
            // strstr retorna NULL se nao encontrar o termo dentro do nome, e um endereço
            // válido se encontrar, por isso comparamos com NULL.
            if (strstr(nome_minusculo, termo_busca) != NULL) {
                corresponde = 1;
            }
        }
// imprime o cabeçalho só na primeira vez que algo é encontrado
        if (corresponde) {
            if (!encontrou) {
                printf("\n --- USUARIO(S) ENCONTRADO(S) ---\n");
            }
            printf("Matricula: %d\n", lista_usuarios[i].matricula);
            printf("Nome: %s\n", lista_usuarios[i].nome);
            printf("Curso: %s\n", lista_usuarios[i].curso);
            printf("Emprestimos Ativos: %d\n", lista_usuarios[i].qtd_emprestimos_ativos);
            printf("------------------------------------\n");
            encontrou = 1;

            if (tipo_busca == 1) break; // se achou por matrícula, pode parar o loop
        }
    }
//nesse caso, se não achou o usuario, corresponde=0 e o if anterior não executou
	//então, o valor de encontrou tambem não muda e sinaliza que nenhum usuario foi encontrado
    if (!encontrou) {
        printf("\n Nenhum usuario correspondente foi encontrado.\n");
    }
}
//listar todos os livros que estão atualmente emprestados (pendentes) para um usuario
void informarLivrosEmprestadosDoUsuario(usuario lista_usuarios[], int tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n  LIVROS EMPRESTADOS AO USUARIO \n");
    desenhaBorda();

    int mat_busca;
    printf("Digite a matricula do usuario: ");
    scanf("%d", &mat_busca);
    getchar();

    // primeiro confirma se a matricula existe no vetor 
    int usuario_encontrado = 0;
    char nome_usuario[250] = "";
 
    for (int i = 0; i < tam_usuarios; i++) {
        if (lista_usuarios[i].matricula == mat_busca) {
            usuario_encontrado = 1; //sinaliza que encontoru 
            strcpy(nome_usuario, lista_usuarios[i].nome); // guarda o nome para exibir
            break;
        }
    }
    if (!usuario_encontrado) {
        printf("\n Matricula %d nao encontrada no sistema.\n", mat_busca);
        return;
    }

    // abre o arquivo de empréstimos
    FILE *arq_emp = fopen("emprestimos.txt", "r");
    if (arq_emp == NULL) {
		//se o arquivo não existir ou não puder ser aberto, assume-se que não há empréstimos no sistema
        printf("\nO usuario %s nao possui livros emprestados no momento.\n", nome_usuario);
        return;
    }

    emprestimo emp;
    int achou_emprestimo = 0;

    while (fscanf(arq_emp, "%d\n", &emp.id) != EOF) {
        fscanf(arq_emp, "%d\n", &emp.matricula_usuario);
        fscanf(arq_emp, "%d\n", &emp.codigo_livro);
        fscanf(arq_emp, "%[^\n]\n", emp.data_retirada);
        fscanf(arq_emp, "%[^\n]\n", emp.data_prevista);
        fscanf(arq_emp, "%[^\n]\n", emp.data_devolucao);
        fscanf(arq_emp, "%d\n", &emp.devolvido);

        // confere se o empréstimo for deste usuário e ainda não foi devolvido
        if (emp.matricula_usuario == mat_busca && emp.devolvido == 0) {
            if (!achou_emprestimo) {
                printf("\nUsuario: %s (Matricula: %d)\n", nome_usuario, mat_busca);
                printf("--- LIVROS EMPRESTADOS ATUALMENTE ---\n");
            }
            achou_emprestimo = 1;

            // abre o arquivo "livros.txt" 
            // e varre ele procurando o título do livro correspondente
            char titulo_livro[250] = "Livro nao encontrado no acervo";
            FILE *arq_livros = fopen("livros.txt", "r");
            
            if (arq_livros != NULL) {
                livro aux_livro;
                // lendo o arquivo de livros
                while (fscanf(arq_livros, "%d\n", &aux_livro.codigo) != EOF) {
                    fscanf(arq_livros, "%[^\n]\n", aux_livro.titulo);
                    fscanf(arq_livros, "%[^\n]\n", aux_livro.autor);
                    fscanf(arq_livros, "%d\n", &aux_livro.ano_de_publi);
                    fscanf(arq_livros, "%[^\n]\n", aux_livro.genero);
                    fscanf(arq_livros, "%d\n", &aux_livro.qtd_total);
                    fscanf(arq_livros, "%d\n", &aux_livro.quant_disp);
                    fscanf(arq_livros, "%d\n", &aux_livro.total_emprestimos);

                    if (aux_livro.codigo == emp.codigo_livro) {
                        strcpy(titulo_livro, aux_livro.titulo);
                        break; // achou o livro, pode parar de ler o arquivo de livros
                    }
                }
                fclose(arq_livros); // fecha o arquivo de livros para liberar a memória
            }

            // printa os dados combinados na tela
            printf("ID Emprestimo: %d\n", emp.id);
            printf("Livro: %s (Codigo: %d)\n", titulo_livro, emp.codigo_livro);
            printf("Data de Retirada: %s\n", emp.data_retirada);
            printf("Prazo de Devolucao: %s\n", emp.data_prevista);
            printf("------------------------------------\n");
        }
    }
    fclose(arq_emp); // fecha o arquivo de empréstimos
//para esse if ser executado o valor da variavel não pode ser 1. Ele so seria 1 se o if anterior fosse verdade, o que indica que
	//o usuario não possui emprestimmos no momento 
    if (!achou_emprestimo) {
        printf("\nO usuario %s nao possui livros emprestados no momento.\n", nome_usuario);
    }
}
// grava o arquivo "usuarios.txt" do ZERO, usando os dados
// que estão no vetor em memória. É chamada sempre que algum usuário é
// ATUALIZADO ou REMOVIDO
void SalvarUsuarios(usuario lista_usuarios[], int tam_usuarios) {
    FILE *arquivo = fopen("usuarios.txt", "w"); // modo "w" apaga e recria o arquivo
    if (arquivo == NULL) {
        printf("\n Erro ao abrir o arquivo para salvar as atualizacoes!\n");
        return;
    }
// grava todos os usuarios do vetor no arquivo, um por um
    for (int i = 0; i < tam_usuarios; i++) {
        fprintf(arquivo, "%d\n", lista_usuarios[i].matricula);
        fprintf(arquivo, "%s\n", lista_usuarios[i].nome);
        fprintf(arquivo, "%s\n", lista_usuarios[i].curso);
        fprintf(arquivo, "%d\n", lista_usuarios[i].qtd_emprestimos_ativos);
    }
    fclose(arquivo);
}
//  permite alterar o nome e o curso de um usuário
void atualizarUsuario(usuario lista_usuarios[], int tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n ATUALIZAR DADOS DO USUARIO \n");
    desenhaBorda();

    if (tam_usuarios == 0) {
        printf("\n Nenhum usuario na memoria RAM. Certifique-se de que o arquivo nao esta corrompido.\n");
        return;
    }

    int mat_busca;
    printf("Digite a matricula do usuario que deseja atualizar: ");
    scanf("%d", &mat_busca);
    getchar(); 

    int indice = -1; // -1 indica que o usuario ainda nao foi encontrado
 
    // busca sequencial no vetor para achar a posicao do usuario
    for (int i = 0; i < tam_usuarios; i++) {
        if (lista_usuarios[i].matricula == mat_busca) {
            indice = i;
            break; // achou, não precisa continuar procurando (matrícula é única)
        }
    }
 // se o índice continuar -1, percorremos o vetor inteiro e não achamos
    if (indice == -1) {
        printf("\n Matricula %d nao encontrada.\n", mat_busca);
        return;
    }
 
    // exibe os dados atuais antes de perguntar os novos
    printf("\n--- Dados Atuais ---\n");
    printf("Nome: %s\n",  lista_usuarios[indice].nome);
    printf("Curso: %s\n", lista_usuarios[indice].curso);
    printf("--------------------\n");

    printf("\nDigite os novos dados:\n");
    printf("Novo Nome: ");
    scanf(" %[^\n]", lista_usuarios[indice].nome); // sobrescreve direto no vetor
    getchar();

    printf("Novo Curso: ");
    scanf(" %[^\n]", lista_usuarios[indice].curso);
    getchar();

   // atualiza o arquivo com o vetor modificado
    SalvarUsuarios(lista_usuarios, tam_usuarios);

    printf("\n Dados atualizados com sucesso!\n");
}
// remove um usuário do sistema, tanto da memória quanto
// do arquivo, mas so se ele não tiver empréstimos em aberto
void removerUsuario(usuario lista_usuarios[], int *tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n REMOVER USUARIO DO SISTEMA \n");
    desenhaBorda();

    if (*tam_usuarios == 0) {
        printf("\n Nenhum usuario cadastrado no sistema ate o momento.\n");
        return;
    }
    int mat_busca;
    printf("Digite a matricula do usuario que deseja remover: ");
    scanf("%d", &mat_busca);
    getchar(); // limpa o buffer
    int indice = -1;
    //procura o usuário no vetor na memória
    for (int i = 0; i < *tam_usuarios; i++) {
        if (lista_usuarios[i].matricula == mat_busca) {
            indice = i;
            break;
        }
    }
    // se não encontrou, avisa e sai
    if (indice == -1) {
        printf("\n Usuario com a matricula %d nao foi encontrado.\n", mat_busca);
        return;
    }
    // não remove se tiver empréstimos ativos
    if (lista_usuarios[indice].qtd_emprestimos_ativos > 0) {
        printf("\n Nao e possivel remover o usuario '%s'!\n", lista_usuarios[indice].nome);
        printf("Motivo: Ele possui %d emprestimo(s) ativo(s) pendente(s).\n", lista_usuarios[indice].qtd_emprestimos_ativos);
        return;
    }
    // confirma se deseja remover o usuario
    char confirmar;
    printf("\nTem certeza que deseja remover o usuario '%s'? (S/N): ", lista_usuarios[indice].nome);
    scanf(" %c", &confirmar);
    getchar();
    confirmar = tolower(confirmar);
    if (confirmar != 's') {
        printf("\nOperacao cancelada.\n");
        return;
    }
    //  "puxa" todos os elementos seguintes uma posição para trás sobrescrevendo a posição do usuario que removi
    for (int i = indice; i < (*tam_usuarios) - 1; i++) {
        lista_usuarios[i] = lista_usuarios[i + 1];
    }
    // reduz a quantidade total de usuários na memória RAM
    (*tam_usuarios)--;
    //atualiza o arquivo txt reescrevendo o vetor atualizado sem o usuário removido
    SalvarUsuarios(lista_usuarios, *tam_usuarios);
    printf("\n Usuario removido com sucesso tanto da memoria quanto do arquivo!\n");
}
// os prototipos estao aqui pois as funções são chamadas antes de serem definidas no código. 
void aguardarEnter();
void atualizarEstoqueLivro(int codigo, int delta);
void realizarEmprestimo(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int *total_emprestimos);
void realizarDevolucao(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int *total_emprestimos);
void listarEmprestimosEmAtraso(emprestimo vetor_emprestimos[], int total_emprestimos, usuario vetor_usuarios[], int total_usuarios);
void menuEmprestimos(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int *total_emprestimos);
// Funcoes Auxiliares 
// Evita repetir o bloco while/getchar por todo o código
void aguardarEnter() {
    printf("\nPressione Enter para voltar ao menu...");
    while (getchar() != '\n'); //limpa o buffer de entrada, consumindo todos os caracteres restantes até encontrar a quebra de linha ('\n')
    getchar(); //captura o 'Enter' final, pausando a tela de forma eficaz antes de retornar ao menu
}
// Abre livros.txt, aplica delta (+1 ou -1) na quantidade disponível do livro
// indicado por 'codigo' e regrava o arquivo via arquivo temporário
void atualizarEstoqueLivro(int codigo, int delta) {
    FILE *arq  = fopen("livros.txt", "r"); //abre o arquivo original de livros em modo de leitura 
    FILE *temp = fopen("temp.txt",   "w"); //abre o arquivo temporario em modo de escrita para salvar a base atualizada  

	//validacao de seguranca: se um ou os dois arquivos falharem ao abrir, encerra a funcao para evitar falha de segmentacao
    if (arq == NULL || temp == NULL) {
        printf("\n Erro ao abrir arquivo de livros!\n");
        if (arq)  fclose(arq);
        if (temp) fclose(temp);
        return;
    }
	//le o arquivo registro por registro ate atingir o fim do arquivo 
    livro l;
	 while (fscanf(arq, "%d\n", &l.codigo) != EOF) {
    fscanf(arq, "%[^\n]\n", l.titulo);
    fscanf(arq, "%[^\n]\n", l.autor);  
    fscanf(arq, "%d\n", &l.ano_de_publi);
    fscanf(arq, "%[^\n]\n", l.genero);
    fscanf(arq, "%d\n", &l.qtd_total);
    fscanf(arq, "%d\n", &l.quant_disp);
    fscanf(arq, "%d\n", &l.total_emprestimos);
		 
		//verifica se o livro lido no momento eh o livro alvo para ser modificado
        if (l.codigo == codigo) {
            l.quant_disp =  l.quant_disp + delta;//atualiza a quantidade disponivel somando o delta (+1 se for devolucao, -1 se for emprestimo)
            if (delta < 0) l.total_emprestimos++; //se o delta for negativo (emprestimo), incrementa o historico do total de emprestimos que esse livro ja teve 
        }

       gravarLivro(temp, l); // usando a função declarada em gerenciamento de livros, a qual da fprintf nos dados do livro
    }

	//fecha ambos os aquivos para garantir que todos os dados salvos no buffer sejam gravados no disco 
    fclose(arq);
    fclose(temp);
    remove("livros.txt"); //exclui a versao antiga e desatualizada do arquivo de livros 
    rename("temp.txt", "livros.txt"); //renomeia o arquivo temporario e consolida as alteracoes 
}

// Funcao realizarEmprestimo
void realizarEmprestimo(usuario vetor_usuarios[], int total_usuarios,
                        emprestimo vetor_emprestimos[], int *total_emprestimos) {
    (void)vetor_emprestimos; //casting para void: silencia os avisos do compilador caso a variavel ainda nao esteja sendo usada nesta parte do codigo 

    int mat_busca, cod_busca;
    int index_usuario = -1; //inicia com -1 indicando que o usuario ainda nao foi encontrado no sistema 

    limpaTela();
    desenhaBorda();
    printf("\n    EFETUAR NOVO EMPRESTIMO  \n");
    desenhaBorda();

    //  Verifica usuário
    printf("Digite a matricula do usuario: ");
    scanf("%d", &mat_busca);

	//percorre o vetor de usuarios cadastrados um por um 
    for (int i = 0; i < total_usuarios; i++) {
        if (vetor_usuarios[i].matricula == mat_busca) { //compara a matricula do usuario na posicao 'i'
            index_usuario = i; //salva o indice onde o usuario foi encontrado no vetor
            break;
        }
    }
	//se o indice continuou -1 apos o loop, significa que a matricula digitada nao existe no sistema 
    if (index_usuario == -1) {
        printf("\n Erro: Usuario com matricula %d nao cadastrado!\n", mat_busca);
        aguardarEnter();
        return;
    }
	//impede o emprestimo se o usuario ja tiver 3 livros pendentes
    if (vetor_usuarios[index_usuario].qtd_emprestimos_ativos >= 3) {
        printf("\n Erro: %s ja atingiu o limite de 3 emprestimos ativos!\n",
               vetor_usuarios[index_usuario].nome);
        aguardarEnter();
        return;
    }

    printf("\n Usuario %s liberado!\n", vetor_usuarios[index_usuario].nome);

    // Verifica livro
    printf("\nDigite o codigo do livro desejado: ");
    scanf("%d", &cod_busca);

    livro l_temp;
    int achou = 0; //variavel de controle: 0 para livro nao encontrado e 1 para encontrado 

    FILE *arq_livros = fopen("livros.txt", "r"); //abre a base de dados de livros em modo de leitura 
    if (arq_livros == NULL) { //tratamento de erro caso o arquivo de livros nao exista ou nao possa ser lido 
        printf("\n Erro ao abrir arquivo de livros!\n");
        aguardarEnter();
        return;
    }
	//loop de busca, le os dados de cada livro sequencialmente do arquivo 
    while (fscanf(arq_livros, "%d\n", &l_temp.codigo) != EOF) {
        fscanf(arq_livros, "%[^\n]\n", l_temp.titulo);
        fscanf(arq_livros, "%[^\n]\n", l_temp.autor);
        fscanf(arq_livros, "%d\n", &l_temp.ano_de_publi);
        fscanf(arq_livros, "%[^\n]\n", l_temp.genero);
        fscanf(arq_livros, "%d\n", &l_temp.qtd_total);
        fscanf(arq_livros, "%d\n", &l_temp.quant_disp);
        fscanf(arq_livros, "%d\n", &l_temp.total_emprestimos);
        if (l_temp.codigo == cod_busca) { //verifica se o codigo lido do arquivo eh igual ao codigo que o usuario digitou
            achou = 1; //atualiza a flag indicando que o livro foi localizado com sucesso 
            break; //para a leitura do arquivo imediatamente 
            }
    }
    fclose(arq_livros); //fecha o arquivo de livros 
 
    if (!achou) {
        printf("\n Erro: Codigo %d nao encontrado!\n", cod_busca);
        aguardarEnter();
        return; //se a flag continuar 0, significa que o codigo do livro nao existe no arquivo 
    }
 	//verifica se o livro foi encontrado, mas nao ha exemplares disponiveis
    if (l_temp.quant_disp <= 0) {
        printf("\n Erro: '%s' esta esgotado!\n", l_temp.titulo);
        aguardarEnter();
        return;
    }

    printf("\n Livro '%s' disponivel! Registrando...\n", l_temp.titulo);

    // Gera datas
	//captura o horario atual do sistema em segundos e armazena na variavel 't'
    time_t t = time(NULL); 
    struct tm *tm_atual = localtime(&t); //converte os segundos de 't' para uma estrutura que divide o tempo em dia, mes, ano, ajustada ao fuso horario local
    char data_retirada[11], data_prevista[11]; //declara as strings de tamanho 11 para armazenar as datas no formato "DD/MM/AAAA" (10 caracteres + '\0')

	//formata a estrutura de tempo atual em formato de texto "Dia/Mes/Ano" e guarda na string 'data_retirada'
    strftime(data_retirada, sizeof(data_retirada), "%d/%m/%Y", tm_atual);
    t += 14 * 24 * 60 * 60; //avanca o tempo em 14 dias: adiciona a 't' equivalente a 14 dias convertendo em segundos (14 dias * 24 horas * 60 minutos * 60 segundos)
	tm_atual = localtime(&t); //recalcula  a estrutura de tempo baseada no novo valor de 't' (que agora esta projetado para daqui a 14 dias)
    strftime(data_prevista, sizeof(data_prevista), "%d/%m/%Y", tm_atual); //formata essa nova data calculada em texto e armazena na string 'data_prevista'

    //  Grava empréstimo
    FILE *arq_emp = fopen("emprestimos.txt", "a"); //abre o arquivo de emprestimos em modo Append que adiciona novos dados sempre ao final do arquivo sem apagar o que ja existe 
    if (arq_emp == NULL) {
        printf("\n Erro ao abrir emprestimos.txt!\n");
        aguardarEnter();
        return;
    }
	//define o id do novo emprestimo somando 1 ao total acumulado de emprestimos no sistema 
    int novo_id = *total_emprestimos + 1;
    fprintf(arq_emp, "%d\n%d\n%d\n%s\n%s\n00/00/0000\n0\n",
            novo_id, mat_busca, cod_busca, data_retirada, data_prevista); //grava os dados do emprestimo formatados no arquivo e incializa os campos de devolucao zerados 
    fclose(arq_emp);

    // Atualiza estoque (-1 disponível)
    atualizarEstoqueLivro(cod_busca, -1); 

    // Atualiza contadores em memória
    vetor_usuarios[index_usuario].qtd_emprestimos_ativos++;
    (*total_emprestimos)++;
 SalvarUsuarios(vetor_usuarios, total_usuarios);//salva usuarios.txt após incrementar qtd_emprestimos_ativos
    //  Recibo
    desenhaBorda();
    printf("   EMPRESTIMO REGISTRADO COM SUCESSO!\n");
    desenhaBorda();
    printf("   ID da Operacao:     %d\n",   novo_id);
    printf("   Usuario:            %s (Matricula: %d)\n",
           vetor_usuarios[index_usuario].nome, mat_busca);
    printf("   Livro:              %s (Codigo: %d)\n", l_temp.titulo, cod_busca);
    printf("   Data de Retirada:   %s\n",   data_retirada);
    printf("   Prazo Maximo:       %s (14 dias)\n", data_prevista);
    printf("   Emprestimos ativos: %d/3\n",
           vetor_usuarios[index_usuario].qtd_emprestimos_ativos);
    desenhaBorda();

    aguardarEnter();
}

// Funcao realizarDevolucao 
void realizarDevolucao(usuario vetor_usuarios[], int total_usuarios,
                       emprestimo vetor_emprestimos[], int *total_emprestimos) {
    int id_busca; //armazena o numero do protocolo (id do emprestimo) que o usuario deseja devolver 
    int encontrado = 0; //flag: 0 para emprestimo nao localizado ou ja devolvido, 1 para ativo e encontrado 
    emprestimo emp_temp; //estrutura temporaria para armazenar os dados de cada emprestimo lido no arquivo durante a busca 

    limpaTela();
    desenhaBorda();
    printf("\n    REGISTRAR DEVOLUCAO DE LIVRO   \n");
    desenhaBorda();

    printf("Digite o ID do emprestimo (Protocolo): ");
    scanf("%d", &id_busca);

    //Reescreve emprestimos.txt marcando o registro como devolvido
    FILE *arq_emp  = fopen("emprestimos.txt", "r"); //abre o arquivo original de emprestimos em modo de leitura 
    FILE *arq_temp = fopen("temp_emprestimos.txt", "w");

	//validacao de seguranca 
    if (arq_emp == NULL || arq_temp == NULL) {
        printf("\n Erro ao abrir arquivos de emprestimos!\n");
        if (arq_emp)  fclose(arq_emp);
        if (arq_temp) fclose(arq_temp);
        aguardarEnter();
        return;
    }
	// loop de leitura, processa o arquivo registro por registro, garantindo que todos os 7 campos de cada emprestimo foram lidos corretamente
    while (fscanf(arq_emp, "%d\n%d\n%d\n%10[^\n]\n%10[^\n]\n%10[^\n]\n%d\n",
                  &emp_temp.id,
                  &emp_temp.matricula_usuario,
                  &emp_temp.codigo_livro,
                  emp_temp.data_retirada,
                  emp_temp.data_prevista,
                  emp_temp.data_devolucao,
                  &emp_temp.devolvido) == 7) {
		
		//verifica se o ID do registro atual coincide com o buscado e se o campo 'devoldido' eh 0 (se o emprestimo ainda esta ativo)
        if (emp_temp.id == id_busca && emp_temp.devolvido == 0) {
            encontrado = 1; //sinaliza que o emprestimo foi localizado com sucesso 
            emp_temp.devolvido = 1; //altera o status do emprestimo, muda a flag para 1, indicando que foi devolvido 

			//captura a data exata do sistema neste momento e grava no campo 'data_devolucao', registrando o dia real em que o livro foi entregue 
            time_t t = time(NULL); 
            strftime(emp_temp.data_devolucao, sizeof(emp_temp.data_devolucao),
                     "%d/%m/%Y", localtime(&t));
        }
		//grava o registro lido no arquivo temporario e atualiza o status devolvido 
        fprintf(arq_temp, "%d\n%d\n%d\n%s\n%s\n%s\n%d\n",
                emp_temp.id, emp_temp.matricula_usuario, emp_temp.codigo_livro,
                emp_temp.data_retirada, emp_temp.data_prevista,
                emp_temp.data_devolucao, emp_temp.devolvido);
    }

	//fecha o arquivo para liberar a memoria e garantir a gravacao no disco 
    fclose(arq_emp);
    fclose(arq_temp);
    remove("emprestimos.txt"); //deleta a base de emprestimos antiga 
    rename("temp_emprestimos.txt", "emprestimos.txt"); //renomeia o arquivo temporario atualizado

	//	verifica se a variavel 'encontrado' continuou sendo 0 (falso) apos a varredura do arquivo 
    if (!encontrado) {
        printf("\n ID %d nao encontrado ou ja devolvido!\n", id_busca);
        aguardarEnter();
        return;
    }

    //  Atualiza vetor de empréstimos em memória
    for (int i = 0; i < *total_emprestimos; i++) {
        if (vetor_emprestimos[i].id == id_busca) {
            vetor_emprestimos[i].devolvido = 1;
            strcpy(vetor_emprestimos[i].data_devolucao, emp_temp.data_devolucao);
            break;
        }
    }

    //Atualiza estoque (+1 disponível)
    atualizarEstoqueLivro(emp_temp.codigo_livro, +1);

    // percorre o vetor de usuarios carregado na memoria para encontrar o aluno que fez a devolucao 
    for (int i = 0; i < total_usuarios; i++) {
        if (vetor_usuarios[i].matricula == emp_temp.matricula_usuario) {
            if (vetor_usuarios[i].qtd_emprestimos_ativos > 0) //garante que o contador de emprestimos nao fique negativo 
                vetor_usuarios[i].qtd_emprestimos_ativos--; //decrementa 1 da quantidade de emprestimos ativos liberando espaco para o usuario pegar novos livros 
            break;
        }
    }

    FILE *arq_usuarios = fopen("usuarios.txt", "w"); //abre o arquivo de usuarios em modo de escrita para reescrever a lista atualizada 
    if (arq_usuarios != NULL) {
        for (int i = 0; i < total_usuarios; i++) { //percorre todo o vetor de usuarios da memoria e grava linha por linha no arquivo limpo
             fprintf(arq_usuarios, "%d\n", vetor_usuarios[i].matricula);
            fprintf(arq_usuarios, "%s\n", vetor_usuarios[i].nome);
            fprintf(arq_usuarios, "%s\n", vetor_usuarios[i].curso);
            fprintf(arq_usuarios, "%d\n", vetor_usuarios[i].qtd_emprestimos_ativos);
        }
        fclose(arq_usuarios); //fecha o arquivo 
    }

    //  Recibo
    desenhaBorda();
    printf("    DEVOLUCAO REGISTRADA COM SUCESSO!\n");
    desenhaBorda();
    printf("   ID do Emprestimo:  %d\n",  emp_temp.id);
    printf("   Codigo do Livro:   %d\n",  emp_temp.codigo_livro);
    printf("   Matricula:         %d\n",  emp_temp.matricula_usuario);
    printf("   Retirada em:       %s\n",  emp_temp.data_retirada);
    printf("   Prazo era:         %s\n",  emp_temp.data_prevista);
    printf("   Devolvido em:      %s\n",  emp_temp.data_devolucao);
    desenhaBorda();

    aguardarEnter();
}

// FUncao listarEmprestimosEmAtraso 
void listarEmprestimosEmAtraso(emprestimo vetor_emprestimos[], int total_emprestimos,
                                usuario vetor_usuarios[], int total_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n    EMPRESTIMOS EM ATRASO  \n");
    desenhaBorda();

    // Data de hoje no formato ordenável AAAAMMDD
    time_t t = time(NULL); //captura o numero exato de segundos no momento em que a funcao roda 
    char data_hoje[11], hoje_ord[9]; //declara arrays para armazenar as datas em formato de texto, reservando o espaco para o caractere nulo '\0' no final 
    strftime(data_hoje, sizeof(data_hoje), "%d/%m/%Y", localtime(&t)); //converte o tempo 't' em segundos para o formato DD/MM/AAAA e guarda na variavel 'data_hoje' 
    printf("Data de hoje: %s\n\n", data_hoje);

    // Monta AAAAMMDD a partir de DD/MM/AAAA usando sscanf
    int d, m, a; //variaveis inteiras para extrair dia, mes e ano separadamente 
    sscanf(data_hoje, "%d/%d/%d", &d, &m, &a); //o 'sscanf' funciona como um scanner, le a string "DD/MM/AAAA" ignora as barras e guarda os numeros nas variaveis d, m e a 
    snprintf(hoje_ord, sizeof(hoje_ord), "%04d%02d%02d", a, m, d); //remonta os numeros extraidos em uma nova string no padrao AAAAMMDD

    // Abre livros.txt uma única vez antes do loop
    FILE *arq_livros = fopen("livros.txt", "r");

    int qtd_atraso = 0; //inicializa o contador global de livros atrasados com 0 

    for (int i = 0; i < total_emprestimos; i++) { //inicia a varredura linear percorrendo todos os emprestimos registrados 
        if (vetor_emprestimos[i].devolvido == 1) continue; //se o emprestimo ja foi devolvido, interrompe a iteracao atual e pula para o proximo emprestimo 

        // Converte data_prevista para AAAAMMDD
        char *dp = vetor_emprestimos[i].data_prevista; //cria um ponteiro local 'dp' que aponta diretamente para a data prevista dentro do vetor, facilitando a leitura nas proximas linhas sem precisar copiar o dado 
        char prev_ord[9]; //string de 9 posicoes para armazenar a data formatada 
        sscanf(dp, "%d/%d/%d", &d, &m, &a); //extrai o dia, mes e ano separadamente da datam prevista 
        snprintf(prev_ord, sizeof(prev_ord), "%04d%02d%02d", a, m, d); //remonta a dara no formato numerico comum 

        if (strcmp(prev_ord, hoje_ord) >= 0) continue; // compara cronologicamente a data prevista com a data de hoje. Se a previsao foi maior ou igual a hoje, o livro esta no prazo, entao pula para o proximo 

        // Busca nome do usuário
        char *nome_usuario = "Desconhecido"; //define um nome generico inicial para evitar falhas ou exibicao de 'lixo' na memoria caso o sistema nao encontre a matricula do aluno 
        for (int j = 0; j < total_usuarios; j++) {
            if (vetor_usuarios[j].matricula == vetor_emprestimos[i].matricula_usuario) {
                nome_usuario = vetor_usuarios[j].nome;
                break;
            }
        }

        // Busca título do livro (arquivo já aberto antes do loop)
        char titulo_livro[250] = "Desconhecido";
        if (arq_livros != NULL) {
            rewind(arq_livros); // volta ao início para cada busca
            livro l;
           while (fscanf(arq_livros, "%d\n", &l.codigo) != EOF) {
                fscanf(arq_livros, "%[^\n]\n", l.titulo);
                fscanf(arq_livros, "%[^\n]\n", l.autor);
                fscanf(arq_livros, "%d\n", &l.ano_de_publi);
                fscanf(arq_livros, "%[^\n]\n", l.genero);
                fscanf(arq_livros, "%d\n", &l.qtd_total);
                fscanf(arq_livros, "%d\n", &l.quant_disp);
                fscanf(arq_livros, "%d\n", &l.total_emprestimos);
                if (l.codigo == vetor_emprestimos[i].codigo_livro) {
                    strcpy(titulo_livro, l.titulo);
                    break;
                }
            }
        }

        printf("   ID: %-4d | Matricula: %-6d | Usuario: %s\n",
               vetor_emprestimos[i].id,
               vetor_emprestimos[i].matricula_usuario,
               nome_usuario);
        printf("         Livro: %s (Cod. %d)\n",
               titulo_livro, vetor_emprestimos[i].codigo_livro);
        printf("         Retirada: %s | Prazo era: %s\n",
               vetor_emprestimos[i].data_retirada,
               vetor_emprestimos[i].data_prevista);
        printf("  --------------------------------------------------\n");

        qtd_atraso++;
    }

    if (arq_livros != NULL) fclose(arq_livros);

    if (qtd_atraso == 0)
        printf("   Nenhum emprestimo em atraso.\n");
    else
        printf("\n  Total em atraso: %d\n", qtd_atraso);

    desenhaBorda();
    aguardarEnter();
}

// Funcao  menuEmprestimos 
void menuEmprestimos(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int *total_emprestimos) {
    int opcao;

    do {
        limpaTela();
        desenhaBorda();
        printf("\n   GERENCIAR EMPRESTIMOS\n");
        desenhaBorda();
        printf("  1. Realizar emprestimo\n");
        printf("  2. Listar emprestimos em atraso\n");
        printf("  0. Voltar ao menu principal\n");
        desenhaBorda();
        printf("  Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                realizarEmprestimo(vetor_usuarios, total_usuarios,
                                   vetor_emprestimos, total_emprestimos);
                break;
            case 2:
                listarEmprestimosEmAtraso(vetor_emprestimos, *total_emprestimos,
                                          vetor_usuarios, total_usuarios);
                break;
            case 0:
                break;
            default:
                limpaTela();
                desenhaBorda();
                printf("\n   Opcao invalida! Digite 0, 1 ou 2.\n");
                desenhaBorda();
                aguardarEnter();
                break;
        }
    } while (opcao != 0);
} //fecha menuEmprestimos
int buscarTituloLivro(int codigo, char *titulo_saida) {
    FILE *arq = fopen("livros.txt", "r");
    if (arq == NULL) {
        strcpy(titulo_saida, "Livro nao encontrado");
        return 0;
    }
 
    livro aux;
    int encontrou = 0;
 
    while (fscanf(arq, "%d\n", &aux.codigo) != EOF) {
        fscanf(arq, "%[^\n]\n", aux.titulo);
        fscanf(arq, "%[^\n]\n", aux.autor);
        fscanf(arq, "%d\n",    &aux.ano_de_publi);
        fscanf(arq, "%[^\n]\n", aux.genero);
        fscanf(arq, "%d\n",    &aux.qtd_total);
        fscanf(arq, "%d\n",    &aux.quant_disp);
        fscanf(arq, "%d\n",    &aux.total_emprestimos);
 
        if (aux.codigo == codigo) { // Busca o titulo de um livro pelo codigo em livros.txt.
            strcpy(titulo_saida, aux.titulo);
            encontrou = 1; //Retorna 1 se encontrou, 0 se nao. Sempre preenche titulo_saida
            break;
        }
    }
 
    fclose(arq);
    if (!encontrou) strcpy(titulo_saida, "Livro nao encontrado");
    return encontrou;
}
void converterDataParaOrdenavel(const char *data_ddmmaaaa, char *saida_aaaammdd) {
    // indices do formato DD/MM/AAAA
    //   D=0,1  /=2  M=3,4  /=5  A=6,7,8,9
    saida_aaaammdd[0] = data_ddmmaaaa[6];  // A
    saida_aaaammdd[1] = data_ddmmaaaa[7];  // A
    saida_aaaammdd[2] = data_ddmmaaaa[8];  // A
    saida_aaaammdd[3] = data_ddmmaaaa[9];  // A
    saida_aaaammdd[4] = data_ddmmaaaa[3];  // M
    saida_aaaammdd[5] = data_ddmmaaaa[4];  // M
    saida_aaaammdd[6] = data_ddmmaaaa[0];  // D
    saida_aaaammdd[7] = data_ddmmaaaa[1];  // D
    saida_aaaammdd[8] = '\0';
}
void obterDataHoje(char *buffer) {
    time_t t = time(NULL);
    struct tm *info = localtime(&t);
    strftime(buffer, 11, "%d/%m/%Y", info);
}
int estaEmAtraso(const emprestimo *emp, const char *hoje_ord) {
    if (emp->devolvido == 1) return 0; // ja devolvido, sem atraso
 
    char prazo_ord[9];
    converterDataParaOrdenavel(emp->data_prevista, prazo_ord);
 
    // strcmp < 0: prazo_ord veio "antes" de hoje_ord, ou seja, ja venceu
    return strcmp(prazo_ord, hoje_ord) < 0;
}
    // Le livros.txt e preenche o vetor. Retorna a quantidade de livros lidos.
// Usado pelo relatorio de mais emprestados, que precisa ordenar em memoria.
int carregarTodosLivros(livro lista[], int capacidade) {
    FILE *arq = fopen("livros.txt", "r");
    if (arq == NULL) return 0;
 
    int tam = 0;
    while (tam < capacidade && fscanf(arq, "%d\n", &lista[tam].codigo) != EOF) {
        fscanf(arq, "%[^\n]\n", lista[tam].titulo);
        fscanf(arq, "%[^\n]\n", lista[tam].autor);
        fscanf(arq, "%d\n",    &lista[tam].ano_de_publi);
        fscanf(arq, "%[^\n]\n", lista[tam].genero);
        fscanf(arq, "%d\n",    &lista[tam].qtd_total);
        fscanf(arq, "%d\n",    &lista[tam].quant_disp);
        fscanf(arq, "%d\n",    &lista[tam].total_emprestimos);
        tam++;
    }
 
    fclose(arq);
    return tam;
}
void relatorioLivrosMaisEmprestados() {
    limpaTela();
    desenhaBorda();
    printf("\n");
    printf("  LIVROS MAIS EMPRESTADOS\n");
    desenhaBorda();

    livro lista[1000];
    int tam = carregarTodosLivros(lista, 1000);

    if (tam == 0) {
        printf("\n");
        printf("Nenhum livro cadastrado no sistema.\n");
        return;
    }

    // Bubble sort decrescente por total_emprestimos
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - 1 - i; j++) {
            if (lista[j].total_emprestimos < lista[j+1].total_emprestimos) {
                livro temp = lista[j];
                lista[j]   = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    // Exibe na tela
    printf("\n");
    for (int i = 0; i < tam; i++) {
        printf("Posicao: %d\n",          i + 1);
        printf("Titulo: %s\n",           lista[i].titulo);
        printf("Autor: %s\n",            lista[i].autor);
        printf("Total emprestimos: %d\n", lista[i].total_emprestimos);
        desenhaBorda();
    }

    // Salva em arquivo .txt
    FILE *arq_rel = fopen("relatorio_mais_emprestados.txt", "w");
    if (arq_rel == NULL) {
        printf("\n");
        printf("Erro ao criar o arquivo de relatorio!\n");
        return;
    }

    fprintf(arq_rel, "RELATORIO - LIVROS MAIS EMPRESTADOS\n");
    fprintf(arq_rel, "====================================\n");
    fprintf(arq_rel, "\n");
    for (int i = 0; i < tam; i++) {
        fprintf(arq_rel, "Posicao: %d\n",           i + 1);
        fprintf(arq_rel, "Titulo: %s\n",            lista[i].titulo);
        fprintf(arq_rel, "Autor: %s\n",             lista[i].autor);
        fprintf(arq_rel, "Total emprestimos: %d\n", lista[i].total_emprestimos);
        fprintf(arq_rel, "------------------------------------\n");
    }

    fclose(arq_rel);
    printf("\n");
    printf("Relatorio salvo em 'relatorio_mais_emprestados.txt'\n");
}
void relatorioUsuariosEmAtraso(usuario lista_usuarios[], int tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n");
    printf("  USUARIOS COM EMPRESTIMOS EM ATRASO\n");
    desenhaBorda();

    // Pega a data de hoje já no formato ordenável (AAAAMMDD) para comparar
    char hoje[11];
    obterDataHoje(hoje);
    char hoje_ord[9];
    converterDataParaOrdenavel(hoje, hoje_ord);

    printf("\n");
    printf("Data de hoje: %s\n", hoje);
    printf("\n");

    FILE *arq_emp = fopen("emprestimos.txt", "r");
    if (arq_emp == NULL) {
        printf("Nenhum emprestimo registrado no sistema.\n");
        return;
    }

    FILE *arq_rel = fopen("relatorio_atrasos.txt", "w");
    if (arq_rel == NULL) {
        printf("Erro ao criar o arquivo de relatorio!\n");
        fclose(arq_emp);
        return;
    }

    fprintf(arq_rel, "RELATORIO - USUARIOS COM EMPRESTIMOS EM ATRASO\n");
    fprintf(arq_rel, "===============================================\n");
    fprintf(arq_rel, "Data de hoje: %s\n", hoje);
    fprintf(arq_rel, "\n");

    emprestimo emp;
    int achou = 0;

    while (fscanf(arq_emp, "%d\n", &emp.id) != EOF) {
        fscanf(arq_emp, "%d\n", &emp.matricula_usuario);
        fscanf(arq_emp, "%d\n", &emp.codigo_livro);
        fscanf(arq_emp, "%[^\n]\n", emp.data_retirada);
        fscanf(arq_emp, "%[^\n]\n", emp.data_prevista);
        fscanf(arq_emp, "%[^\n]\n", emp.data_devolucao);
        fscanf(arq_emp, "%d\n", &emp.devolvido);

        // Verifica se está em atraso usando a função já existente no código
        if (estaEmAtraso(&emp, hoje_ord)) {
            achou = 1;

            // Busca o nome do usuário no vetor em memória
            char nome[250] = "Nao encontrado";
            for (int i = 0; i < tam_usuarios; i++) {
                if (lista_usuarios[i].matricula == emp.matricula_usuario) {
                    strcpy(nome, lista_usuarios[i].nome);
                    break;
                }
            }

            // Busca o título do livro no arquivo
            char titulo[250];
            buscarTituloLivro(emp.codigo_livro, titulo);

            // Exibe na tela
            printf("ID Emprestimo: %d\n",  emp.id);
            printf("Usuario: %s\n",        nome);
            printf("Matricula: %d\n",      emp.matricula_usuario);
            printf("Livro: %s\n",          titulo);
            printf("Prazo vencido em: %s\n", emp.data_prevista);
            desenhaBorda();

            // Salva no arquivo
            fprintf(arq_rel, "ID Emprestimo: %d\n",    emp.id);
            fprintf(arq_rel, "Usuario: %s\n",           nome);
            fprintf(arq_rel, "Matricula: %d\n",         emp.matricula_usuario);
            fprintf(arq_rel, "Livro: %s\n",             titulo);
            fprintf(arq_rel, "Prazo vencido em: %s\n",  emp.data_prevista);
            fprintf(arq_rel, "------------------------------------\n");
        }
    }

    fclose(arq_emp);
    fclose(arq_rel);

    if (!achou) {
        printf("Nenhum emprestimo em atraso encontrado.\n");
    } else {
        printf("\n");
        printf("Relatorio salvo em 'relatorio_atrasos.txt'\n");
    }
}
void relatorioAcervoDisponivel() {
    limpaTela();
    desenhaBorda();
    printf("\n");
    printf("  ACERVO DISPONIVEL\n");
    desenhaBorda();

    FILE *arq = fopen("livros.txt", "r");
    if (arq == NULL) {
        printf("\n");
        printf("Nenhum livro cadastrado no sistema.\n");
        return;
    }

    FILE *arq_rel = fopen("relatorio_acervo_disponivel.txt", "w");
    if (arq_rel == NULL) {
        printf("Erro ao criar o arquivo de relatorio!\n");
        fclose(arq);
        return;
    }

    fprintf(arq_rel, "RELATORIO - ACERVO DISPONIVEL\n");
    fprintf(arq_rel, "==============================\n");
    fprintf(arq_rel, "\n");

    livro aux;
    int achou = 0;

    while (fscanf(arq, "%d\n", &aux.codigo) != EOF) {
        fscanf(arq, "%[^\n]\n", aux.titulo);
        fscanf(arq, "%[^\n]\n", aux.autor);
        fscanf(arq, "%d\n",     &aux.ano_de_publi);
        fscanf(arq, "%[^\n]\n", aux.genero);
        fscanf(arq, "%d\n",     &aux.qtd_total);
        fscanf(arq, "%d\n",     &aux.quant_disp);
        fscanf(arq, "%d\n",     &aux.total_emprestimos);

        // Só exibe livros que tenham ao menos 1 exemplar disponível
        if (aux.quant_disp > 0) {
            achou = 1;

            // Exibe na tela
            printf("\n");
            printf("Codigo: %d\n",       aux.codigo);
            printf("Titulo: %s\n",       aux.titulo);
            printf("Autor: %s\n",        aux.autor);
            printf("Genero: %s\n",       aux.genero);
            printf("Ano: %d\n",          aux.ano_de_publi);
            printf("Disponiveis: %d\n",  aux.quant_disp);
            printf("Total: %d\n",        aux.qtd_total);
            desenhaBorda();

            // Salva no arquivo
            fprintf(arq_rel, "Codigo: %d\n",      aux.codigo);
            fprintf(arq_rel, "Titulo: %s\n",      aux.titulo);
            fprintf(arq_rel, "Autor: %s\n",       aux.autor);
            fprintf(arq_rel, "Genero: %s\n",      aux.genero);
            fprintf(arq_rel, "Ano: %d\n",         aux.ano_de_publi);
            fprintf(arq_rel, "Disponiveis: %d\n", aux.quant_disp);
            fprintf(arq_rel, "Total: %d\n",       aux.qtd_total);
            fprintf(arq_rel, "------------------------------------\n");
        }
    }

    fclose(arq);
    fclose(arq_rel);

    if (!achou) {
        printf("\n");
        printf("Nenhum livro disponivel no momento.\n");
    } else {
        printf("\n");
        printf("Relatorio salvo em 'relatorio_acervo_disponivel.txt'\n");
    }
}
void relatorioHistoricoUsuario(usuario lista_usuarios[], int tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n");
    printf("  HISTORICO COMPLETO DE EMPRESTIMOS DO USUARIO\n");
    desenhaBorda();

    int mat_busca;
    printf("\n");
    printf("Digite a matricula do usuario: ");
    scanf("%d", &mat_busca);
    getchar();

    // Verifica se o usuário existe no vetor em memória
    char nome_usuario[250] = "";
    int encontrou_usuario = 0;
    for (int i = 0; i < tam_usuarios; i++) {
        if (lista_usuarios[i].matricula == mat_busca) {
            strcpy(nome_usuario, lista_usuarios[i].nome);
            encontrou_usuario = 1;
            break;
        }
    }

    if (!encontrou_usuario) {
        printf("\n");
        printf("Matricula %d nao encontrada no sistema.\n", mat_busca);
        return;
    }

    FILE *arq_emp = fopen("emprestimos.txt", "r");
    if (arq_emp == NULL) {
        printf("\n");
        printf("Nenhum emprestimo registrado no sistema.\n");
        return;
    }

    FILE *arq_rel = fopen("relatorio_historico_usuario.txt", "w");
    if (arq_rel == NULL) {
        printf("Erro ao criar o arquivo de relatorio!\n");
        fclose(arq_emp);
        return;
    }

    fprintf(arq_rel, "RELATORIO - HISTORICO COMPLETO DE EMPRESTIMOS\n");
    fprintf(arq_rel, "==============================================\n");
    fprintf(arq_rel, "Usuario: %s\n", nome_usuario);
    fprintf(arq_rel, "Matricula: %d\n", mat_busca);
    fprintf(arq_rel, "\n");

    emprestimo emp;
    int achou = 0;

    while (fscanf(arq_emp, "%d\n", &emp.id) != EOF) {
        fscanf(arq_emp, "%d\n", &emp.matricula_usuario);
        fscanf(arq_emp, "%d\n", &emp.codigo_livro);
        fscanf(arq_emp, "%[^\n]\n", emp.data_retirada);
        fscanf(arq_emp, "%[^\n]\n", emp.data_prevista);
        fscanf(arq_emp, "%[^\n]\n", emp.data_devolucao);
        fscanf(arq_emp, "%d\n", &emp.devolvido);

        if (emp.matricula_usuario == mat_busca) {
            if (!achou) {
                printf("\n");
                printf("Usuario: %s\n", nome_usuario);
                printf("Matricula: %d\n", mat_busca);
                desenhaBorda();
            }
            achou = 1;

            // Busca o título do livro pelo código
            char titulo[250];
            buscarTituloLivro(emp.codigo_livro, titulo);

            // Exibe na tela
            printf("\n");
            printf("ID Emprestimo: %d\n",   emp.id);
            printf("Livro: %s\n",           titulo);
            printf("Codigo do livro: %d\n", emp.codigo_livro);
            printf("Data de retirada: %s\n", emp.data_retirada);
            printf("Prazo de devolucao: %s\n", emp.data_prevista);

            // Mostra status e data de devolução real conforme situação
            if (emp.devolvido == 1) {
                printf("Data de devolucao: %s\n", emp.data_devolucao);
                printf("Status: DEVOLVIDO\n");
            } else {
                printf("Data de devolucao: Pendente\n");
                printf("Status: EM ABERTO\n");
            }
            desenhaBorda();

            // Salva no arquivo
            fprintf(arq_rel, "ID Emprestimo: %d\n",      emp.id);
            fprintf(arq_rel, "Livro: %s\n",               titulo);
            fprintf(arq_rel, "Codigo do livro: %d\n",     emp.codigo_livro);
            fprintf(arq_rel, "Data de retirada: %s\n",    emp.data_retirada);
            fprintf(arq_rel, "Prazo de devolucao: %s\n",  emp.data_prevista);
            if (emp.devolvido == 1) {
                fprintf(arq_rel, "Data de devolucao: %s\n", emp.data_devolucao);
                fprintf(arq_rel, "Status: DEVOLVIDO\n");
            } else {
                fprintf(arq_rel, "Data de devolucao: Pendente\n");
                fprintf(arq_rel, "Status: EM ABERTO\n");
            }
            fprintf(arq_rel, "------------------------------------\n");
        }
    }

    fclose(arq_emp);
    fclose(arq_rel);

    if (!achou) {
        printf("\n");
        printf("Nenhum emprestimo encontrado para este usuario.\n");
    } else {
        printf("\n");
        printf("Relatorio salvo em 'relatorio_historico_usuario.txt'\n");
    }
}
int main(){
setlocale(LC_ALL, "Portuguese");

    usuario vetor_usuarios[1000];
    int total_usuarios = 0;
	LerUsuarios(vetor_usuarios, &total_usuarios);

     emprestimo vetor_emprestimos[5000];// Vetor de empréstimos (usado para controlar o próximo ID)
     int total_emprestimos = 0;

	 lerEmprestimos(vetor_emprestimos, &total_emprestimos);

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
                     printf("\n [4] - Editar livro");
                    printf("\n [5] - Remover livro");
                    printf("\n [6] - Ver emprestimos ativos");
                    printf("\n [7] - Voltar ao Menu Principal\n");
                    
                    printf("Escolha uma opcao: ");
                    scanf("%d", &opcaoSecundar);
                    getchar();
 
                    switch(opcaoSecundar){
    case 1: {
         // Calcula o próximo ID e passa para a função de cadastro
         cadastrarLivro(obterProximoCodigo());
          break;
                        }
    case 2:
     limpaTela();
     listarLivros();
 printf("\nPressione enter para voltar");
 getchar(); // Pausa para o usuário ler
    break;
    case 3:
    limpaTela();
    buscarLivro();
    printf("\nPressione enter para voltar\n");
    getchar();
    break;
     case 4:
    editarLivro();
    printf("\nPressione enter para voltar\n");
    getchar();
        break;

    case 5:
        removerLivro();
        printf("\nPressione enter para voltar\n");
        getchar();
        break;

        case 6:
         
                     // passa o vetor de usuários para a função conseguir exibir os nomes
        informarEmprestimosDoLivro(vetor_usuarios, total_usuarios);
        printf("\nPressione enter para voltar\n");
         getchar();
            break;
         
         
         case 7:
         
                  break; // sai do mneu secundario de livros
                        default:
                            printf("\nOpcao invalida!\n");
                            printf("Pressione Enter para tentar novamente");
                            getchar();
                            break;
                    }
                } while(opcaoSecundar != 7);
                break;
      case 2:
    do{
    	   limpaTela();
           desenhaBorda();
		   printf("\n   GERENCIAMENTO DE USUARIOS   \n");
		   desenhaBorda();
		   printf("\n [1] - Cadastrar usuarios ");
		   printf("\n [2] - Listar usuarios");
		   printf("\n [3] - Buscar usuarios ");
           printf("\n [4] - Informar os livros emprestados para um usuario");
		   printf("\n [5] - Atualizar dados");
		   printf("\n [6] - Remover usuarios \n");
		   printf(" [7] - Voltar ao Menu Principal\n");
		   printf("Escolha uma opcao: ");
		   scanf("%d", &opcao2);
           getchar();
		   //resultado de acordo com a opção escolhida.
		
		   switch (opcao2) {
		    case 1: 
				limpaTela();
		    if (total_usuarios<1000) {
        
        cadastrarUsuario(vetor_usuarios, &total_usuarios);
        
        }else {
    
        printf("Erro: limite de usuarios atingidos!");
		}
		break;
		case 2:
			limpaTela();
		ListarUsuarios(vetor_usuarios, total_usuarios);
			printf("Digite enter pra voltar.");
			getchar();
		break;
		case 3:
        limpaTela();
		buscarUsuario(vetor_usuarios, total_usuarios);
        printf("\nDigite enter para voltar.");
            getchar();
		break;
		case 4:
		limpaTela();
            informarLivrosEmprestadosDoUsuario(vetor_usuarios, total_usuarios);
            printf("\nDigite enter para voltar.");
            getchar();
		break;
		case 5:
		  limpaTela();
                atualizarUsuario(vetor_usuarios, total_usuarios);
                printf("\nDigite enter pra voltar.");
                getchar();
		break;
		case 6:
limpaTela();
                removerUsuario(vetor_usuarios, &total_usuarios); //passa o & porque o total vai diminuir!
                printf("\nDigite enter pra voltar.");
                getchar();
		break;
		   }
		}
		while (opcao2 != 7);// enquanto o usuario nao optar por sair do menu secundario ele vai se repetir
    break;
    case 3:
    		menuEmprestimos(vetor_usuarios, 
							total_usuarios,
							vetor_emprestimos, 
							&total_emprestimos);
    break;
    case 4:
   			realizarDevolucao(vetor_usuarios, 
							  total_usuarios,
							  vetor_emprestimos,
							   &total_emprestimos);
    break;
    case 5: {
    int opcaoRel;
    do {
        limpaTela();
        desenhaBorda();
        printf("\n  RELATORIOS \n");
        desenhaBorda();
        printf("\n [1] - Livros mais emprestados");
        printf("\n [2] - Usuarios com emprestimos em atraso");
        printf("\n [3] - Acervo disponivel");
        printf("\n [4] - Historico de emprestimos de um usuario");
        printf("\n [5] - Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoRel);
        getchar();

        switch (opcaoRel) {
            case 1:
                relatorioLivrosMaisEmprestados();
                printf("\nPressione Enter para voltar.");
                getchar();
                break;
            case 2:
                relatorioUsuariosEmAtraso(vetor_usuarios, total_usuarios);
                printf("\nPressione Enter para voltar.");
                getchar();
                break;
            case 3:
                relatorioAcervoDisponivel();
                printf("\nPressione Enter para voltar.");
                getchar();
                break;
            case 4:
                relatorioHistoricoUsuario(vetor_usuarios, total_usuarios);
                printf("\nPressione Enter para voltar.");
                getchar();
                break;
            case 5:
                break;
            default:
                printf("\nOpcao invalida!\n");
                getchar();
                break;
        }
    } while (opcaoRel != 5);
    break;
}
    case 6:
    limpaTela();
    break;
    default:
}
} while (opcao != 6); // O programa continua rodando ATÉ o usuário digitar 6

return 0;
}
