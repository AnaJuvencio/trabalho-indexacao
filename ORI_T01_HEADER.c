/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 01 - Indexação
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T01_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */
/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */

/* Funções auxiliares para o qsort. */

/* Função de comparação entre chaves do índice jogadores_idx */
int qsort_jogadores_idx(const void *a, const void *b) {
	return strcmp (((jogadores_index*)a)->id_jogador, ((jogadores_index*)b)->id_jogador);
}


/* Função de comparação entre chaves do índice kits_idx */
int qsort_kits_idx(const void *a, const void *b) {
    return strcmp(((kits_index *)a)->id_kit, ((kits_index *)b)->id_kit);
}

/* Função de comparação entre chaves do índice partidas_idx */
int qsort_partidas_idx(const void *a, const void *b) {
    return strcmp(((partidas_index *)a)->id_partida, ((partidas_index *)b)->id_partida);
}


/* Função de comparação entre chaves do índice resultados_idx */
int qsort_resultados_idx(const void *a, const void *b) {
    resultados_index *res_a = (resultados_index *)a;
    resultados_index *res_b = (resultados_index *)b;

    int cmp = strcmp(res_a->id_jogador, res_b->id_jogador);
    if (cmp != 0)
        return cmp;

    return strcmp(res_a->id_partida, res_b->id_partida);
}



int qsort_preco_kit_idx(const void *a, const void *b) {
    return strcmp(((preco_kit_index *)a)->id_kit, ((preco_kit_index *)b)->id_kit);
}



/* Função usada na comparação entre as chaves do índice data_idx */
int qsort_data_idx(const void *a, const void *b) {
    return strcmp(((data_index *)a)->id_partida, ((data_index *)b)->id_partida);
}


/* Função de comparação entre vitórias, eliminacoes e tempo de sobrevivencia dos jogadores
 * Usada na função recompensar_vencedores_periodo; */
int qsort_info_jogador(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "qsort_info_jogador()");
}


/* Função de comparação entre chaves do índice secundário de jogador_kits_secundario_idx */
int qsort_jogador_kits_secundario_idx(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "qsort_jogador_kits_secundario_idx()");
}


/* Função de comparação entre chaves do índice secundário de jogador_kits_primario_idx */
int qsort_inverted_list_primary_search(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "qsort_inverted_list_primary_search()");
}


/* Cria o índice respectivo  (já estava feito --Ana)*/ 
void criar_jogadores_idx() {
	if (!jogadores_idx)
		jogadores_idx = malloc(MAX_REGISTROS * sizeof(jogadores_index));

	if (!jogadores_idx) {
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_jogadores; ++i) {

		Jogador j = recuperar_registro_jogador(i);

		if (strncmp(j.id_jogador, "*|", 2) == 0)
			jogadores_idx[i].rrn = -1;
		else
			jogadores_idx[i].rrn = i;

		strcpy (jogadores_idx[i].id_jogador, j.id_jogador);
	}



	qsort(jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx);
	printf(INDICE_CRIADO, "jogadores_idx");
}


void criar_kits_idx() {
    if (!kits_idx)
        kits_idx = malloc(MAX_REGISTROS * sizeof(kits_index));

    if (!kits_idx) { // Verifica falha na alocação
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    // Inicializa o índice percorrendo os registros no arquivo
    unsigned qtd_registros_validos = 0; // Para contar apenas registros válidos
    for (unsigned i = 0; i < qtd_registros_kits; ++i) {
        Kit k = recuperar_registro_kit(i); // Função para recuperar um kit a partir do RRN

        // Verifica se o registro foi excluído
        if (strncmp(k.id_kit, "*|", 2) == 0) {
            continue; // Pula registros excluídos
        }

        // Preenche o índice com dados válidos
        strncpy(kits_idx[qtd_registros_validos].id_kit, k.id_kit, TAM_ID_KIT - 1);
        kits_idx[qtd_registros_validos].id_kit[TAM_ID_KIT - 1] = '\0'; // Garante terminação nula
        kits_idx[qtd_registros_validos].rrn = i;

        ++qtd_registros_validos;
    }

    // Ordena o índice pelo campo id_kit
    qsort(kits_idx, qtd_registros_validos, sizeof(kits_index), qsort_kits_idx);

    printf(INDICE_CRIADO, "kits_idx");
}



void criar_partidas_idx() {
	if (!partidas_idx)
        partidas_idx = malloc(MAX_REGISTROS * sizeof(partidas_index));

    if (!partidas_idx) { // Verifica falha na alocação
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    // Inicializa o índice percorrendo os registros no arquivo
    unsigned qtd_registros_validos = 0; // Conta apenas registros válidos
    for (unsigned i = 0; i < qtd_registros_partidas; ++i) {
        Partida p = recuperar_registro_partida(i); // Recupera o registro de partida pelo RRN

        // Verifica se o registro foi excluído
        if (strncmp(p.id_partida, "*|", 2) == 0) {
            continue; // Ignora registros excluídos
        }

        // Preenche o índice com dados válidos
        strncpy(partidas_idx[qtd_registros_validos].id_partida, p.id_partida, TAM_ID_PARTIDA - 1);
        partidas_idx[qtd_registros_validos].id_partida[TAM_ID_PARTIDA - 1] = '\0'; // Garante terminação nula
        partidas_idx[qtd_registros_validos].rrn = i;

        ++qtd_registros_validos;
    }

    // Ordena o índice pelo campo id_partida
    qsort(partidas_idx, qtd_registros_validos, sizeof(partidas_index), qsort_partidas_idx);

    printf(INDICE_CRIADO, "partidas_idx");
}


void criar_resultados_idx() {
    if (!resultados_idx)
        resultados_idx = malloc(MAX_REGISTROS * sizeof(resultados_index));

    if (!resultados_idx) { // Verifica falha na alocação
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    // Inicializa o índice percorrendo os registros no arquivo
    unsigned qtd_registros_validos = 0; // Conta apenas registros válidos
    for (unsigned i = 0; i < qtd_registros_resultados; ++i) {
        Resultado r = recuperar_registro_resultado(i); // Recupera o registro de resultado pelo RRN

        // Verifica se o registro foi excluído
        if (strncmp(r.id_jogador, "*|", 2) == 0) {
            continue; // Ignora registros excluídos
        }

        // Preenche o índice com dados válidos
        strncpy(resultados_idx[qtd_registros_validos].id_jogador, r.id_jogador, TAM_ID_JOGADOR - 1);
        resultados_idx[qtd_registros_validos].id_jogador[TAM_ID_JOGADOR - 1] = '\0'; // Garante terminação nula

        strncpy(resultados_idx[qtd_registros_validos].id_partida, r.id_partida, TAM_ID_PARTIDA - 1);
        resultados_idx[qtd_registros_validos].id_partida[TAM_ID_PARTIDA - 1] = '\0'; // Garante terminação nula

        resultados_idx[qtd_registros_validos].rrn = i;

        ++qtd_registros_validos;
    }

    // Ordena o índice primeiro por id_jogador e depois por id_partida
    qsort(resultados_idx, qtd_registros_validos, sizeof(resultados_index), qsort_resultados_idx);

    printf(INDICE_CRIADO, "resultados_idx");
}



void criar_preco_kit_idx() {
    if (!preco_kit_idx) // Verificamos se já existe, caso contrário, alocamos
        preco_kit_idx = malloc(MAX_REGISTROS * sizeof(preco_kit_index));

    if (!preco_kit_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    // Preenche o índice com os dados
    for (unsigned i = 0; i < qtd_registros_kits; ++i) {
        Kit k = recuperar_registro_kit(i); // Recupera o kit
        strcpy(preco_kit_idx[i].id_kit, k.id_kit);
        preco_kit_idx[i].preco = k.preco; // Armazena o preço do kit
    }

    // Ordena o índice pelo id_kit
    qsort(preco_kit_idx, qtd_registros_kits, sizeof(preco_kit_index), qsort_preco_kit_idx);

    printf(INDICE_CRIADO, "preco_kit_idx");
}



void criar_data_idx() {
    if (!data_idx) // Verificamos se já existe, caso contrário, alocamos
        data_idx = malloc(MAX_REGISTROS * sizeof(data_index));

    if (!data_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    // Preenche o índice com os dados
    for (unsigned i = 0; i < qtd_registros_partidas; ++i) {
        Partida p = recuperar_registro_partida(i); // Recupera a partida
        strcpy(data_idx[i].id_partida, p.id_partida);
        strcpy(data_idx[i].inicio, p.inicio); // Armazena a data da partida
    }

    // Ordena o índice pelo id_partida
    qsort(data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx);

    printf(INDICE_CRIADO, "data_idx");
}


void criar_jogador_kits_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_jogador_kits_idx()");
}


/* Recupera do arquivo o registro com o RRN informado (já estava feito) --Ana
 * e retorna os dados nas structs */
Jogador recuperar_registro_jogador(int rrn) {
	Jogador j;
	char data[TAM_REGISTRO_JOGADOR + 1], *p;

	strncpy(data, ARQUIVO_JOGADORES + (rrn * TAM_REGISTRO_JOGADOR), TAM_REGISTRO_JOGADOR);
	data[TAM_REGISTRO_JOGADOR] = '\0';

	p = strtok(data, ";");
	strcpy(j.id_jogador, p);

	p = strtok(NULL, ";");
	strcpy(j.apelido, p);

	p = strtok(NULL, ";");
	strcpy(j.cadastro, p);

	p = strtok(NULL, ";");
	strcpy(j.premio, p);

	p = strtok(NULL, ";");
	j.saldo = atof(p);

	p = strtok(NULL, ";");

	for (int i = 0; i < QTD_MAX_KITS; ++i) {
		j.kits[i][0] = '\0';
	}

	if (p[0] != '#') {
		p = strtok(p, "|");
		for (int i = 0; p; p = strtok(NULL, "|"), ++i) {
			strcpy(j.kits[i], p);
		}
	}

	return j;
}


Kit recuperar_registro_kit(int rrn) {
    Kit k;
    char data[TAM_REGISTRO_KIT + 1], *p;

    // Copia os dados do registro do kit do arquivo para a variável data
    strncpy(data, ARQUIVO_KITS + (rrn * TAM_REGISTRO_KIT), TAM_REGISTRO_KIT);
    data[TAM_REGISTRO_KIT] = '\0'; // Garante terminação nula

    // Divide os dados do registro do kit usando o delimitador ";"
    p = strtok(data, ";");
    strcpy(k.id_kit, p);  

    p = strtok(NULL, ";");
    strcpy(k.nome, p);  

    p = strtok(NULL, ";");
    strcpy(k.poder, p); 

    p = strtok(NULL, ";");
    k.preco = atof(p);  

    return k;
}



Partida recuperar_registro_partida(int rrn) {
    Partida p;
    char data[TAM_REGISTRO_PARTIDA + 1], *token;

    // Copia o registro do arquivo com base no RRN
    strncpy(data, ARQUIVO_PARTIDAS + (rrn * TAM_REGISTRO_PARTIDA), TAM_REGISTRO_PARTIDA);
    data[TAM_REGISTRO_PARTIDA] = '\0'; // Garante terminação nula

    // Divide os dados do registro da partida usando o delimitador ";"
    token = strtok(data, ";");
    strcpy(p.id_partida, token);  

    token = strtok(NULL, ";");
    strcpy(p.inicio, token);  

    token = strtok(NULL, ";");
    strcpy(p.duracao, token);  

    token = strtok(NULL, ";");
    strcpy(p.cenario, token);  

    token = strtok(NULL, ";");
    strcpy(p.id_jogadores, token);  // Ids dos jogadores (separados por "|")

    return p;
}



Resultado recuperar_registro_resultado(int rrn) {
    Resultado r;
    char data[TAM_REGISTRO_RESULTADO + 1], *p;

    // Copia os dados do registro de resultado do arquivo para a variável data
    strncpy(data, ARQUIVO_RESULTADOS + (rrn * TAM_REGISTRO_RESULTADO), TAM_REGISTRO_RESULTADO);
    data[TAM_REGISTRO_RESULTADO] = '\0'; // Garante terminação nula

    // Divide os dados do registro do resultado usando o delimitador ";"
    p = strtok(data, ";");
    strcpy(r.id_jogador, p); 

    p = strtok(NULL, ";");
    strcpy(r.id_partida, p); 

    p = strtok(NULL, ";");
    strcpy(r.id_kit, p); 

    p = strtok(NULL, ";");
    r.colocacao = atoi(p); 

    p = strtok(NULL, ";");
    strcpy(r.sobrevivencia, p); 

    p = strtok(NULL, ";");
    r.eliminacoes = atoi(p); 

    return r;
}



/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_jogador(Jogador j, int rrn) {
	char data[TAM_REGISTRO_JOGADOR + 1], number[100];
	data[0] = '\0'; number[0] = '\0';

	strcat(data, j.id_jogador);
	strcat(data, ";");
	strcat(data, j.apelido);
	strcat(data, ";");
	strcat(data, j.cadastro);
	strcat(data, ";");
	strcat(data, j.premio);
	strcat(data, ";");
	sprintf(number, "%013.2lf", j.saldo);
	strcat (data, number);
	strcat(data, ";");

	for (int i = 0; i < QTD_MAX_KITS; ++i) {
		if (strlen(j.kits[i]) > 0) {
			if (i != 0)
				strcat (data, "|");
			strcat(data, j.kits[i]);
		}
	}
	strcat(data, ";");


	strpadright(data, '#', TAM_REGISTRO_JOGADOR);

	strncpy(ARQUIVO_JOGADORES + rrn*TAM_REGISTRO_JOGADOR, data, TAM_REGISTRO_JOGADOR);
}

void escrever_registro_kit(Kit k, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_kit()");
}


void escrever_registro_partida(Partida p, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_partida()");
}

void escrever_registro_resultado (Resultado jp, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "escrever_registro_resultado()");
}


/* Exibe um registro com base no RRN */
bool exibir_jogador(int rrn) {
	if (rrn < 0)
		return false;

	Jogador j = recuperar_registro_jogador(rrn);

	printf ("%s, %s, %s, %s, %.2lf\n", j.id_jogador, j.apelido, j.cadastro, j.premio, j.saldo);

	return true;
}

bool exibir_kit(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_kit()");
}

bool exibir_partida(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_partida()");
}


/* Funções principais */
void cadastrar_jogador_menu(char *id_jogador, char *apelido) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_jogador_menu()");
}


void remover_jogador_menu(char *id_jogador) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "remover_jogador_menu()");
}


void adicionar_saldo_menu(char *id_jogador, double valor) {
	adicionar_saldo(id_jogador, valor, true);
}


void adicionar_saldo(char *id_jogador, double valor, bool flag){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "adicionar_saldo()");
}


void cadastrar_kit_menu(char *nome, char *poder, double preco) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "cadastrar_kit_menu()");
}


void comprar_kit_menu(char *id_jogador, char *id_kit) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "comprar_kit_menu()");
}


void executar_partida_menu(char *inicio, char *duracao, char *cenario, char *id_jogadores, char *kits_jogadores, char *duracoes_jogadores, char *eliminacoes_jogadores) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "executar_partida_menu()");
}


void recompensar_vencedores_menu (char *data_inicio, char *data_fim, double premio) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "recompensar_vencedores_menu()");
}


/* Busca */
void buscar_jogador_id_menu(char *id_jogador) {
	jogadores_index index;
	strcpy(index.id_jogador, id_jogador);
	int found = busca_binaria((void*)&index, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, true, 0);
	if (found == -1)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_jogador(jogadores_idx[found].rrn);
}


void buscar_kit_id_menu(char *id_kit) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "buscar_kit_id_menu()");
}


void buscar_partida_id_menu(char *id_partida) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "buscar_partida_id_menu()");
}


/* Listagem */
void listar_jogadores_id_menu() {
	if (qtd_registros_jogadores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_jogadores; i++)
			exibir_jogador(jogadores_idx[i].rrn);
}


void listar_jogadores_kits_menu(char *kit){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_jogadores_kits_menu()");
}


void listar_kits_compra_menu(char *id_jogador) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_kits_compra_menu()");
}


void listar_partidas_periodo_menu(char *data_inicio, char *data_fim) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_partidas_periodo_menu()");
}


/* Imprimir arquivos de dados */
void imprimir_arquivo_jogadores_menu() {
	if (qtd_registros_jogadores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_JOGADORES);
}


void imprimir_arquivo_kits_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_arquivo_kits_menu()");
}


void imprimir_arquivo_partidas_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_arquivo_partidas_menu()");
}


void imprimir_arquivo_resultados_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_arquivo_resultados_menu()");
}


/* Imprimir índices primários */
void imprimir_jogadores_idx_menu() {
	if (jogadores_idx == NULL || qtd_registros_jogadores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_jogadores; ++i)
			printf("%s, %d\n", jogadores_idx[i].id_jogador, jogadores_idx[i].rrn);
}


void imprimir_kits_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_kits_idx_menu()");
}


void imprimir_partidas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_partidas_idx_menu()");
}


void imprimir_resultados_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_resultados_idx_menu()");
}


/* Imprimir índices secundários */
void imprimir_preco_kit_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_preco_kit_idx_menu()");
}


void imprimir_data_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_data_idx_menu()");
}


void imprimir_jogador_kits_secundario_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_jogador_kits_secundario_idx_menu()");
}


void imprimir_jogador_kits_primario_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_jogador_kits_primario_idx_menu()");
}


/* Liberar espaço */
void liberar_espaco_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "liberar_espaco_menu()");
}


/* Liberar memória e encerrar programa */
void liberar_memoria_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "liberar_memoria_menu()");
}


/* Funções de manipulação de Lista Invertida */
void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_insert()");
}


bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_secondary_search()");
}



int inverted_list_primary_search(char result[][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_primary_search()");
}


/* Funções de busca binária */
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "busca_binaria_com_reps()");
}


int busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}


char *strpadright(char *str, char pad, unsigned size){
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}

char *strupr(char *str){
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}

char *strlower(char *str){
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}
