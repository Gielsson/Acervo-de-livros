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
while (fscanf(arquivo, "%d\n", &aux.codigo) !=EOF){
 aux = lerLivro(arquivo); // lê os campos restantes

        ultimo_id = aux.codigo;  // vai guardando o último
    }
    fclose(arquivo);
    return ultimo_id + 1;
}

void cadastrarLivro(int id_automatico) { // id inicial calculado por obterProximoCodigo(); pode ser atualizado a cada novo cadastro
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
    id_automatico = obterProximoCodigo();
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
int obterProximaMatricula(){
    FILE *arquivo = fopen("usuarios.txt", "r");

    if(arquivo == NULL){
        return 202600;
    }

    usuario info;
    int ultimaMatricula = 202599; // valor base: uma abaixo de 202600


    while(fscanf(arquivo, "%d\n", &info.matricula) != EOF){
        fscanf(arquivo, "%[^\n]\n", info.nome);
        fscanf(arquivo, "%[^\n]\n", info.curso);
        fscanf(arquivo, "%d\n", &info.qtd_emprestimos_ativos);

        ultimaMatricula = info.matricula;
    }

    fclose(arquivo);

    return ultimaMatricula + 1;
}
// insere novo perfil
void cadastrarUsuario(usuario lista_usuarios[], int *tam_usuarios) {
    char continuar;

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
        continuar = tolower(continuar);

    } while(continuar == 's'); 
}
void ListarUsuarios(usuario lista_usuarios[], int tam_usuarios){

    limpaTela();
     // avisa se ainda nao ha nenhum usuario no sistema
    if (tam_usuarios == 0) {
        printf("Nenhum usuario cadastrado ainda.\n");
        return;
    }

    for(int i=0;i < tam_usuarios;i++){
        printf("Nome: %s\n", lista_usuarios[i].nome);
        printf("Curso: %s\n", lista_usuarios[i].curso);
        printf("Matricula: %d\n", lista_usuarios[i].matricula);
        printf("Emprestimos ativos: %d\n", lista_usuarios[i].qtd_emprestimos_ativos);
desenhaBorda();
    }    
}
void buscarUsuario(usuario lista_usuarios[], int tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n BUSCAR USUARIO NO SISTEMA \n");
    desenhaBorda();

    if (tam_usuarios == 0) {
        printf("\n❌ Nenhum usuario cadastrado no sistema ate o momento.\n");
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
        
        // coloca o termo buscado em minúsculo para busca insensível a maiúsculas
        for(int i = 0; termo_busca[i]; i++) {
            termo_busca[i] = tolower(termo_busca[i]);
        }
    } else {
        printf("\n❌ Opcao invalida!\n");
        return;
    }

    int encontrou = 0;

    // percorre o vetor que já está na memória RAM
    for (int i = 0; i < tam_usuarios; i++) {
        int corresponde = 0;

        if (tipo_busca == 1 && lista_usuarios[i].matricula == mat_busca) {
            corresponde = 1;
        } else if (tipo_busca == 2) {
            // cria cópia em minúsculo do nome cadastrado para comparar
            char nome_minusculo[250];
            strcpy(nome_minusculo, lista_usuarios[i].nome);
            for(int j = 0; nome_minusculo[j]; j++) {
                nome_minusculo[j] = tolower(nome_minusculo[j]);
            }
            // strstr retorna NULL se nao encontrar o termo dentro do nome
            if (strstr(nome_minusculo, termo_busca) != NULL) {
                corresponde = 1;
            }
        }

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

    if (!encontrou) {
        printf("\n Nenhum usuario correspondente foi encontrado.\n");
    }
}
void informarLivrosEmprestadosDoUsuario(usuario lista_usuarios[], int tam_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n  LIVROS EMPRESTADOS AO USUARIO \n");
    desenhaBorda();

    int mat_busca;
    printf("Digite a matricula do usuario: ");
    scanf("%d", &mat_busca);
    getchar();

    // primeiro confirma se a matricula existe no vetor em RAM
    int usuario_encontrado = 0;
    char nome_usuario[250] = "";
 
    for (int i = 0; i < tam_usuarios; i++) {
        if (lista_usuarios[i].matricula == mat_busca) {
            usuario_encontrado = 1;
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

        // se o empréstimo for deste usuário e ainda não foi devolvido
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
                // lendo o arquivo de livros no mesmo padrão estruturado do seu grupo
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

    if (!achou_emprestimo) {
        printf("\nO usuario %s nao possui livros emprestados no momento.\n", nome_usuario);
    }
}
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
            break;
        }
    }
 
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


void realizarEmprestimo(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int *total_emprestimos);

void realizarDevolucao(usuario vetor_usuarios[], int total_usuarios,  emprestimo vetor_emprestimos[], int total_emprestimos);

void listarEmprestimosEmAtraso(emprestimo vetor_emprestimos[], int total_emprestimos, usuario vetor_usuarios[], int total_usuarios);

void menuEmprestimos(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int *total_emprestimos);

//Funcao realizarEmprestimo
void realizarEmprestimo(usuario vetor_usuarios[], int total_usuarios,emprestimo vetor_emprestimos[], int *total_emprestimos) {
    (void)vetor_emprestimos;

    int mat_busca;
    int cod_busca;
    int index_usuario = -1; //Começa com -1 para indicar que não encontrou
    int index_livro   = -1; //O mesmo para o livro

    limpaTela();
    desenhaBorda();
    printf("\n  📚  EFETUAR NOVO EMPRESTIMO  📚\n");
    desenhaBorda();

    //ETAPA 1 — Verificar se o usuário existe e está habilitado
    printf("Digite a matricula do usuario: ");
    scanf("%d", &mat_busca);

    //Busca sequencial no vetor de usuarios cadastrados.
    for (int i = 0; i < total_usuarios; i++) {
        if (vetor_usuarios[i].matricula == mat_busca) {
            index_usuario = i; // Guarda a posicao exata onde o usuario foi encontrado 
            break;             //Encerra a busca assim que encontrar 
        }
    }

    // Se o índice continuar -1, o usuario nao existe no sistema
    if (index_usuario == -1) {
        printf("\n❌ Erro: Usuario com a matricula %d nao esta cadastrado!\n", mat_busca);
        printf("Pressione Enter para voltar ao menu.");
        // Limpa o '\n' deixado pelo scanf antes de aguardar o Enter 
        while (getchar() != '\n');
        getchar();
        return; // Finaliza a funcao (aborta o emprestimo)
    }

    //Aplicacao do limite de 3 livros ativos por usuario 
    if (vetor_usuarios[index_usuario].qtd_emprestimos_ativos >= 3) {
        printf("\n❌ Erro: o usuario %s ja atingiu o limite de 3 emprestimos ativos!\n",
               vetor_usuarios[index_usuario].nome);
        printf("Nao e permitido realizar mais emprestimos ate que um livro seja devolvido.\n");
        printf("Pressione Enter para voltar ao menu.");
        while (getchar() != '\n');
        getchar();
        return; // Aborta o emprestimo 
    }

    printf("\n✅ Usuario %s liberado para realizar o emprestimo!\n",
           vetor_usuarios[index_usuario].nome);

    //ETAPA 2 — Verificar se o livro existe e tem exemplar disponivel
    printf("\nDigite o codigo do livro desejado: ");
    scanf("%d", &cod_busca);

    livro l_temp;
    int achou = 0;

    FILE *arq_livros = fopen("livros.txt", "r");
    if (arq_livros == NULL) {
    printf("\n❌ Erro ao abrir arquivo de livros!\n");
    return;
    }

    // busca no arquivo
    while (fscanf(arq_livros,
              "%d\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%d\n%d\n%d\n",
              &l_temp.codigo,
              l_temp.titulo,
              l_temp.autor,
              &l_temp.ano_de_publi,
              l_temp.genero,
              &l_temp.qtd_total,
              &l_temp.quant_disp,
              &l_temp.total_emprestimos) == 8) {

        if (l_temp.codigo == cod_busca) {
        achou = 1;
        break;
        }
    }

    fclose(arq_livros);

    // Livro nao encontrado
    if (!achou) {
    printf("\n❌ Erro: Codigo de livro %d nao encontrado no sistema!\n", cod_busca);
    printf("Pressione Enter para voltar.");
    while (getchar() != '\n');
    getchar();
    return;
    }

    // Verifica estoque
    if (l_temp.quant_disp <= 0) {
    printf("\n❌ Erro: O livro '%s' esta esgotado no momento!\n", l_temp.titulo);
    printf("Nao ha exemplares disponiveis para emprestimo.\n");
    printf("Pressione Enter para voltar.");
    while (getchar() != '\n');
    getchar();
    return;
    }

    printf("\n✅ Livro '%s' disponivel! Registrando emprestimo...\n", l_temp.titulo);

    //ETAPA 3 — Gerar datas automaticas (retirada e prazo de 14 dias)
    time_t t = time(NULL);
    struct tm *info_tempo = localtime(&t);

    char data_retirada[11];
    char data_prevista[11];

    //Formata a data atual do sistema no formato DD/MM/AAAA 
    strftime(data_retirada, sizeof(data_retirada), "%d/%m/%Y", info_tempo);

    // Soma 14 dias em segundos (14 * 24h * 60min * 60seg) e recalcula 
    t += 14 * 24 * 60 * 60;
    info_tempo = localtime(&t);

    // Formata a data prevista de devolucao 
    strftime(data_prevista, sizeof(data_prevista), "%d/%m/%Y", info_tempo);

    //ETAPA 4 — Gravar o novo emprestimo no arquivo emprestimos.txt
    FILE *arq_emp = fopen("emprestimos.txt", "a");
    if (arq_emp == NULL) {
        printf("\n❌ Erro: Nao foi possivel abrir ou criar 'emprestimos.txt'!\n");
        printf("Pressione Enter para voltar.");
        while (getchar() != '\n');
        getchar();
        return;
    }

    // O ID do novo emprestimo e o total atual + 1 
    int novo_id = *total_emprestimos + 1;

    //Grava os campos na ordem definida pela struct emprestimo
    fprintf(arq_emp, "%d\n",  novo_id);
    fprintf(arq_emp, "%d\n",  mat_busca);
    fprintf(arq_emp, "%d\n",  cod_busca);
    fprintf(arq_emp, "%s\n",  data_retirada);
    fprintf(arq_emp, "%s\n",  data_prevista);
    fprintf(arq_emp, "00/00/0000\n"); // Data de devolucao real: vazia inicialmente
    fprintf(arq_emp, "0\n");          //Status devolvido: 0 = nao devolvido

    fclose(arq_emp); //Fecha o arquivo de emprestimos

    //ETAPA 5 — Atualizar o estoque do livro
    FILE *arq = fopen("livros.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (arq == NULL || temp == NULL) {
    printf("\n❌ Erro ao abrir arquivos de livros!\n");
    return;
    }

    livro l;

    while (fscanf(arq,
              "%d\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%d\n%d\n%d\n",
              &l.codigo,
              l.titulo,
              l.autor,
              &l.ano_de_publi,
              l.genero,
              &l.qtd_total,
              &l.quant_disp,
              &l.total_emprestimos) == 8) {

        if (l.codigo == cod_busca) {
        l.quant_disp--;
        l.total_emprestimos++;
        }

        fprintf(temp,
            "%d\n%s\n%s\n%d\n%s\n%d\n%d\n%d\n",
            l.codigo,
            l.titulo,
            l.autor,
            l.ano_de_publi,
            l.genero,
            l.qtd_total,
            l.quant_disp,
            l.total_emprestimos);
    }

    fclose(arq);
    fclose(temp);

    remove("livros.txt");
    rename("temp.txt", "livros.txt");

    // 6 — Atualizar o contador do usuario em memoria
    vetor_usuarios[index_usuario].qtd_emprestimos_ativos++; //+1 emprestimo ativo 
    (*total_emprestimos)++;                                    // +1 no total do sistema

    // ETAPA 7 — Exibir recibo de confirmacao
    desenhaBorda();
    printf("  🤝  EMPRESTIMO REGISTRADO COM SUCESSO!\n");
    desenhaBorda();
    printf("  🔹 ID da Operacao:       %d\n",   novo_id);
    printf("  🔹 Usuario:              %s (Matricula: %d)\n",
           vetor_usuarios[index_usuario].nome, mat_busca);
    printf("  🔹 Livro Retirado:       %s (Codigo: %d)\n",
           l_temp.titulo, cod_busca);
    printf("  🔹 Data de Retirada:     %s\n",   data_retirada);
    printf("  🔹 Prazo Maximo:         %s (14 dias)\n", data_prevista);
    printf("  🔹 Emprestimos ativos:   %d/3\n",
           vetor_usuarios[index_usuario].qtd_emprestimos_ativos);
    desenhaBorda();

    printf("\nPressione Enter para concluir e retornar ao menu...");
    while (getchar() != '\n');
    getchar();

} //fecha realizarEmprestimo 


//Funcao realizarDevolucao
void realizarDevolucao(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int total_emprestimos) {

    int id_busca;
    int emprestimo_encontrado = 0; //Flag: 0 = nao encontrou, 1 = encontrou 
    emprestimo emp_temp;           //Variavel temporaria para leitura do arquivo

    limpaTela();
    desenhaBorda();
    printf("\n  ↩️   REGISTRAR DEVOLUCAO DE LIVRO   ↩️\n");
    desenhaBorda();

    printf("Digite o ID do emprestimo (Protocolo): ");
    scanf("%d", &id_busca);

    //ETAPA 1 — Abrir o arquivo de emprestimos para leitura e criar um arquivo temporario para reescrita
    FILE *arq_emp = fopen("emprestimos.txt", "r");
    if (arq_emp == NULL) {
        printf("\n❌ Erro: Nao ha emprestimos registrados no sistema!\n");
        printf("Pressione Enter para voltar.");
        while (getchar() != '\n');
        getchar();
        return;
    }

    //Arquivo temporario onde os dados atualizados serao gravados 
    FILE *arq_temp = fopen("temp_emprestimos.txt", "w");
    if (arq_temp == NULL) {
        printf("\n❌ Erro: Nao foi possivel criar arquivo temporario!\n");
        fclose(arq_emp);
        printf("Pressione Enter para voltar.");
        while (getchar() != '\n');
        getchar();
        return;
    }

    //ETAPA 2 — Varrer o arquivo procurando pelo ID informado
    while (fscanf(arq_emp, "%d\n", &emp_temp.id) == 1) {

        fscanf(arq_emp, "%d\n",      &emp_temp.matricula_usuario);
        fscanf(arq_emp, "%d\n",      &emp_temp.codigo_livro);
        fscanf(arq_emp, "%10[^\n]\n", emp_temp.data_retirada);
        fscanf(arq_emp, "%10[^\n]\n", emp_temp.data_prevista);
        fscanf(arq_emp, "%10[^\n]\n", emp_temp.data_devolucao);
        fscanf(arq_emp, "%d\n",      &emp_temp.devolvido);

        // Se achou o ID e o livro ainda NAO foi devolvido
        if (emp_temp.id == id_busca && emp_temp.devolvido == 0) {
            emprestimo_encontrado = 1;

            emp_temp.devolvido = 1; //Marca como devolvido

            //Registra a data real de devolucao com a data atual do sistema
            time_t t = time(NULL);
            struct tm *info_tempo = localtime(&t);
            strftime(emp_temp.data_devolucao,
                     sizeof(emp_temp.data_devolucao),
                     "%d/%m/%Y", info_tempo);
        }

        //Grava o registro (alterado ou nao) no arquivo temporario 
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

    //Substitui o arquivo original pelo temporario atualizado
    remove("emprestimos.txt");
    rename("temp_emprestimos.txt", "emprestimos.txt");

    //ETAPA 3 — Verificar se o emprestimo realmente existia
    if (emprestimo_encontrado == 0) {
        printf("\n❌ Erro: Emprestimo com ID %d nao encontrado ou ja foi devolvido!\n",
               id_busca);
        printf("Pressione Enter para voltar.");
        while (getchar() != '\n');
        getchar();
        return;
    }

    // 4 — Atualizar o vetor de emprestimos em memoria
    for (int i = 0; i < total_emprestimos; i++) {
        if (vetor_emprestimos[i].id == id_busca) {
            vetor_emprestimos[i].devolvido = 1;
            strcpy(vetor_emprestimos[i].data_devolucao, emp_temp.data_devolucao);
            break;
        }
    }

    //ETAPA 5 — Atualizar o estoque do livro
    FILE *arq = fopen("livros.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (arq == NULL || temp == NULL) {
    printf("\n❌ Erro ao abrir arquivo de livros!\n");
    return;
    }

    livro l;

    while (fscanf(arq,
              "%d\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%d\n%d\n%d\n",
              &l.codigo,
              l.titulo,
              l.autor,
              &l.ano_de_publi,
              l.genero,
              &l.qtd_total,
              &l.quant_disp,
              &l.total_emprestimos) == 8) {

    if (l.codigo == emp_temp.codigo_livro) {
        l.quant_disp++; // devolve exemplar
    }

    fprintf(temp,
            "%d\n%s\n%s\n%d\n%s\n%d\n%d\n%d\n",
            l.codigo,
            l.titulo,
            l.autor,
            l.ano_de_publi,
            l.genero,
            l.qtd_total,
            l.quant_disp,
            l.total_emprestimos);
    }

    fclose(arq);
    fclose(temp);

    remove("livros.txt");
    rename("temp.txt", "livros.txt");

    //ETAPA 6 — Atualizar o contador de emprestimos do usuario na memoria (e regravar usuarios.txt)
    for (int i = 0; i < total_usuarios; i++) {
        if (vetor_usuarios[i].matricula == emp_temp.matricula_usuario) {
            if (vetor_usuarios[i].qtd_emprestimos_ativos > 0) {
                vetor_usuarios[i].qtd_emprestimos_ativos--; // -1 emprestimo ativo
            }
            break; //Encerra o loop apos encontrar o usuario
        }
    }

    //Regrava usuarios.txt com o contador atualizado
    FILE *arq_usuarios = fopen("usuarios.txt", "w");
    if (arq_usuarios != NULL) {
        for (int i = 0; i < total_usuarios; i++) {
            fprintf(arq_usuarios, "%d\n%s\n%s\n%d\n",
                    vetor_usuarios[i].matricula,
                    vetor_usuarios[i].nome,
                    vetor_usuarios[i].curso,
                    vetor_usuarios[i].qtd_emprestimos_ativos);
        }
        fclose(arq_usuarios);
    }

    //ETAPA 7 — Exibir recibo de confirmacao
    desenhaBorda();
    printf("  🤝  DEVOLUCAO REGISTRADA COM SUCESSO!\n");
    desenhaBorda();
    printf("  🔹 ID do Emprestimo:    %d\n",  emp_temp.id);
    printf("  🔹 Codigo do Livro:     %d\n",  emp_temp.codigo_livro);
    printf("  🔹 Matricula do Aluno:  %d\n",  emp_temp.matricula_usuario);
    printf("  🔹 Data de Retirada:    %s\n",  emp_temp.data_retirada);
    printf("  🔹 Prazo era:           %s\n",  emp_temp.data_prevista);
    printf("  🔹 Data de Devolucao:   %s\n",  emp_temp.data_devolucao);
    desenhaBorda();

    printf("\nPressione Enter para concluir e retornar ao menu...");
    while (getchar() != '\n');
    getchar();

} //fecha realizarDevolucao


//Funcao listarEmprestimosEmAtraso

void listarEmprestimosEmAtraso(emprestimo vetor_emprestimos[], int total_emprestimos, usuario vetor_usuarios[], int total_usuarios) {
    limpaTela();
    desenhaBorda();
    printf("\n  ⏰  EMPRESTIMOS EM ATRASO  ⏰\n");
    desenhaBorda();

    //Obtém a data atual do sistema no formato DD/MM/AAAA
    char data_hoje[11];
    time_t t = time(NULL);
    struct tm *info_tempo = localtime(&t);
    strftime(data_hoje, sizeof(data_hoje), "%d/%m/%Y", info_tempo);

    printf("Data de hoje: %s\n\n", data_hoje);

    // Converte a data de hoje para o formato AAAAMMDD para comparacao.
    char hoje_ord[9]; 
    hoje_ord[0] = data_hoje[6]; hoje_ord[1] = data_hoje[7];
    hoje_ord[2] = data_hoje[8]; hoje_ord[3] = data_hoje[9]; //ano
    hoje_ord[4] = data_hoje[3]; hoje_ord[5] = data_hoje[4]; //mes
    hoje_ord[6] = data_hoje[0]; hoje_ord[7] = data_hoje[1]; //dia
    hoje_ord[8] = '\0';

    int qtd_atraso = 0; //Contador de emprestimos em atraso encontrados

    //Percorre todos os emprestimos registrados
    for (int i = 0; i < total_emprestimos; i++) {

        //Ignora emprestimos ja devolvidos
        if (vetor_emprestimos[i].devolvido == 1) {
            continue;
        }

        //Converte a data_prevista do emprestimo para o formato AAAAMMDD
        char *dp = vetor_emprestimos[i].data_prevista; //alias para facilitar leitura 
        char prev_ord[9];
        prev_ord[0] = dp[6]; prev_ord[1] = dp[7];
        prev_ord[2] = dp[8]; prev_ord[3] = dp[9]; //ano 
        prev_ord[4] = dp[3]; prev_ord[5] = dp[4]; //mes 
        prev_ord[6] = dp[0]; prev_ord[7] = dp[1]; //dia 
        prev_ord[8] = '\0';

        // Compara: se a data prevista for ANTERIOR a hoje, esta em atraso. 
        if (strcmp(prev_ord, hoje_ord) < 0) {

            //Busca o nome do usuario pelo numero de matricula
            char *nome_usuario = "Desconhecido";
            for (int j = 0; j < total_usuarios; j++) {
                if (vetor_usuarios[j].matricula == vetor_emprestimos[i].matricula_usuario) {
                    nome_usuario = vetor_usuarios[j].nome;
                    break;
                }
            }

            //Busca o titulo do livro pelo codigo
            char titulo_livro[250] = "Desconhecido";

            FILE *arq_livros = fopen("livros.txt", "r");
            if (arq_livros != NULL) {

                livro l;

                while (fscanf(arq_livros,
                             "%d\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n%d\n%d\n%d\n",
                            &l.codigo,
                            l.titulo,
                            l.autor,
                            &l.ano_de_publi,
                            l.genero,
                            &l.qtd_total,
                            &l.quant_disp,
                            &l.total_emprestimos) == 8) {

                    if (l.codigo == vetor_emprestimos[i].codigo_livro) {
                        strcpy(titulo_livro, l.titulo);
                        break;
                    }
                }

            fclose(arq_livros);
}

            //Exibe as informacoes do emprestimo em atraso 
            printf("  🔴 ID: %-4d | Matricula: %-6d | Usuario: %s\n",
                   vetor_emprestimos[i].id,
                   vetor_emprestimos[i].matricula_usuario,
                   nome_usuario);
            printf("         Livro: %s (Cod. %d)\n",
                   titulo_livro,
                   vetor_emprestimos[i].codigo_livro);
            printf("         Retirada: %s | Prazo era: %s\n",
                   vetor_emprestimos[i].data_retirada,
                   vetor_emprestimos[i].data_prevista);
            printf("  --------------------------------------------------\n");

            qtd_atraso++;
        }
    }

    //Mensagem final com o total encontrado 
    if (qtd_atraso == 0) {
        printf("  ✅ Nenhum emprestimo em atraso no momento.\n");
    } else {
        printf("\n  Total de emprestimos em atraso: %d\n", qtd_atraso);
    }

    desenhaBorda();
    printf("\nPressione Enter para voltar ao menu...");
    while (getchar() != '\n');
    getchar();

} // fecha listarEmprestimosEmAtraso


//Funcao menuEMprestimos 
void menuEmprestimos(usuario vetor_usuarios[], int total_usuarios, emprestimo vetor_emprestimos[], int *total_emprestimos) {
    int opcao;

    do {
        limpaTela();
        desenhaBorda();
        printf("\n  📋  GERENCIAR EMPRESTIMOS \n");
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
                                   lista_livros,   tam_livros,
                                   vetor_emprestimos, total_emprestimos);
                break;

            case 2:
                listarEmprestimosEmAtraso(vetor_emprestimos, *total_emprestimos,
                                          vetor_usuarios,    total_usuarios,
                                          lista_livros,      tam_livros);
                break;

            case 0:
                //Volta ao menu principal automaticamente
                break;

            default:
                limpaTela();
                desenhaBorda();
                printf("\n  ❌ Opcao invalida! Digite um numero entre 0 e 2.\n");
                desenhaBorda();
                printf("\nPressione Enter para tentar novamente...");
                while (getchar() != '\n');
                getchar();
                break;
        }

    } while (opcao != 0); //Repete ate o usuario escolher sair

} //fecha menuEmprestimos

int main(){
setlocale(LC_ALL, "Portuguese");

    usuario vetor_usuarios[1000];
    int total_usuarios = 0;
	LerUsuarios(vetor_usuarios, &total_usuarios);

     emprestimo vetor_emprestimos[5000];// Vetor de empréstimos (usado para controlar o próximo ID)
     int total_emprestimos = 0;

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
		printf("opção 6 escolhida");
		break;
		   }
		}
		while (opcao2 != 7);// enquanto o usuario nao optar por sair do menu secundario ele vai se repetir
    break;
    case 3:
    		menuEmprestimos(vetor_usuarios, total_usuarios,
							vetor_emprestimos, total_emprestimos;
    break;
    case 4:
   			realizarDevolucao(vetor_usuarios, total_usuarios,
							  vetor_emprestimos, total_emprestimos);
    break;
    case 5:
    printf("opção 5 foi escolhida\n");
    break;
    case 6:
    limpaTela();
    break;
    default:
    printf("opcao 6 foi escolhida\n");
    break;
}
} while (opcao != 6); // O programa continua rodando ATÉ o usuário digitar 6

return 0;
}
