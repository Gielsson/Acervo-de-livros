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
        printf("\n❌ Nenhum livro cadastrado no sistema ainda.\n");
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
        printf("\n❌ Opcao invalida!\n");
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
        printf("\n❌ Nenhum livro correspondente foi encontrado.\n");
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

    while(fscanf(arquivo, "%d\n",
           &lista_usuarios[*tam_usuarios].matricula) != EOF){

        fscanf(arquivo, "%[^\n]\n",
               lista_usuarios[*tam_usuarios].nome);

        fscanf(arquivo, "%[^\n]\n",
               lista_usuarios[*tam_usuarios].curso);

        fscanf(arquivo, "%d\n",
               &lista_usuarios[*tam_usuarios].qtd_emprestimos_ativos);

        (*tam_usuarios)++;
    }

    fclose(arquivo);
}
int obterProximaMatricula(){
    FILE *arquivo = fopen("usuarios.txt", "r");

    if(arquivo == NULL){
        return 202600;
    }

    usuario info;
    int ultimaMatricula = 202599;

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
    // o ponteiro aponta pro total de usuarios que, no caso é a posição do usuario no vetor 
    int posicao = *tam_usuarios; 
    printf("\n=== CADASTRO DE NOVO USUARIO ===\n");
    //gera a matrícula automaticamente com base na posição
    lista_usuarios[posicao].matricula = obterProximaMatricula();
    printf("Matricula gerada: %d\n", lista_usuarios[posicao].matricula);
    //lê o nome completo
    printf("Digite o nome completo: ");
    scanf(" %[^\n]", lista_usuarios[posicao].nome);
    //lê o curso
    printf("Digite o curso: ");
    scanf(" %[^\n]", lista_usuarios[posicao].curso);
    // inicializa o contador de empréstimos do usuário zerado
    lista_usuarios[posicao].qtd_emprestimos_ativos = 0;
    // soma 1 na variável total_usuarios que esta sendo apontada
   

    FILE *arquivo = fopen("usuarios.txt", "a");

if(arquivo == NULL){
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
     (*tam_usuarios)++;
}
void ListarUsuarios(usuario lista_usuarios[], int tam_usuarios){

    limpaTela();
    printf("\n=== USUARIOS CADASTRADO ===\n");

    for(int i=0;i < tam_usuarios;i++){
        printf("Nome: %s\n", lista_usuarios[i].nome);
        printf("Curso: %s\n", lista_usuarios[i].curso);
        printf("Matricula: %d\n", lista_usuarios[i].matricula);
        printf("Emprestimos ativos: %d\n", lista_usuarios[i].qtd_emprestimos_ativos);
desenhaBorda();
    }

    
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
		   printf("\n [4] - Atualizar dados");
		   printf("\n [5] - Remover usuarios \n");
		   printf(" [6] - Sair \n");
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
    limpaTela();
    break;
    default:
    printf("opcao 6 foi escolhida\n");
    break;
}
} while (opcao != 6); // O programa continua rodando ATÉ o usuário digitar 6

return 0;
}
