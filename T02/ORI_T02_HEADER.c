/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 02 - Árvore-B
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T02_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */
/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */


/* Compara a chave (key) com cada elemento do índice (elem).
 * Funções auxiliares para o buscar e inserir chaves em Árvores-B.
 * Note que, desta vez, as funções comparam chaves no formato string, e não struct.
 * "key" é a chave do tipo string que está sendo buscada ou inserida. 
 * "elem" é uma chave do tipo string da struct btree_node.
 *
 * Dica: consulte sobre as funções strncmp() e strnlen(). Muito provavelmente, você vai querer utilizá-las no código.
 * */

/* Função de comparação entre chaves do índice jogadores_idx */
int order_jogadores_idx(const void *key, const void *elem) {
	return strncmp(key, elem, TAM_ID_JOGADOR-1);
}

/* Função de comparação entre chaves do índice kits_idx */
int order_kits_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "order_kits_idx()");
	return -1;
}

/* Função de comparação entre chaves do índice partidas_idx */
int order_partidas_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "order_partidas_idx()");
	return -1;
}

/* Função de comparação entre chaves do índice resultados_idx */
int order_resultados_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "order_resultados_idx()");
	return -1;
}

/* Função de comparação entre chaves do índice preco_kit_idx */
int order_preco_kit_idx(const void *key, const void *elem){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "order_preco_kit_idx()");
	return -1;
}

/* Função de comparação entre chaves do índice data_partida_idx */
int order_data_partida_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "order_data_partida_idx()");
	return -1;
}

/* Função de comparação entre chaves do índice jogador_kits_idx */
int order_jogador_kit_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "order_jogador_kit_idx()");
	return -1;
}

/* Função de comparação entre vitórias, eliminacoes e tempo de sobrevivencia dos jogadores
 * Usada na função recompensar_vencedores_periodo; */
int qsort_info_jogador(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "qsort_info_jogador()");
	return -1;
}


/* Cria o índice respectivo */
void criar_jogadores_idx() {
	char str[TAM_CHAVE_JOGADORES_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_jogadores; ++i) {
		Jogador z = recuperar_registro_jogador(i);

		sprintf(str, "%s%04d", z.id_jogador, i);
		btree_insert(str, &jogadores_idx);
	}
	printf(INDICE_CRIADO, "jogadores_idx");
}


void criar_kits_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_kits_idx()");
}


void criar_partidas_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_partidas_idx()");
}


void criar_resultados_idx(){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_resultados_idx()");
}


void criar_preco_kit_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_preco_kit_idx()");
}


void criar_data_partida_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_data_partida_idx()");
}


void criar_jogador_kits_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "criar_jogador_kits_idx()");
}


/* Recupera do arquivo o registro com o RRN informado
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
		memset (j.kits[i], 0, TAM_ID_KIT);
	}

	if (p[0] != '#') {
		p = strtok(p, "|");
		for (int i = 0; p; p = strtok(NULL, "|"), ++i) {
			strncpy(j.kits[i], p, TAM_ID_KIT-1);
		}
	}
	
	return j;
}


Kit recuperar_registro_kit(int rrn) {
	Kit k;
	
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "recuperar_registro_kit()");

	return k;
}


Partida recuperar_registro_partida(int rrn) {
	Partida p;

	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "recuperar_registro_partida()");

	return p;
}


Resultado recuperar_registro_resultado(int rrn) {
	Resultado r;

	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "recuperar_registro_resultado()");

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
	return false;
}

bool exibir_partida(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_partida()");
	return false;
}


/* Exibe um registro com base na chave de um btree_node */
bool exibir_btree_jogadores(char *chave) {
	char num [5];
	memset (num, 0, 5);
	memcpy (num, chave + TAM_ID_JOGADOR-1, 4);

	int rrn = strtol(num, NULL, 10);
    return exibir_jogador(rrn);
}

bool exibir_btree_kits(char *chave) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_btree_kits()");
	return false;
}

bool exibir_btree_partidas(char *chave) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_btree_partidas()");
	return false;
}

bool exibir_btree_preco_kit(char *chave) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_btree_preco_kit()");
	return false;
}

bool exibir_btree_data_partida(char *chave) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "exibir_btree_data_partida()");
	return false;
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


void recompensar_vencedor_menu (char *data_inicio, char *data_fim, double premio) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "recompensar_vencedor_menu()");
}


/* Busca */
void buscar_jogador_id_menu(char *id_jogador) {
	char str[TAM_CHAVE_JOGADORES_IDX];
	memset (str, 0, TAM_CHAVE_JOGADORES_IDX);
	
	printf (REGS_PERCORRIDOS);
    bool found = btree_search(str, true, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
	printf ("\n");
	
    if (!found)
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    else {
		char num[5];
		memset (num, 0, 5);
		memcpy (num, str+TAM_ID_JOGADOR-1, 4);
		
        exibir_jogador(strtol (num, NULL, 10));
	}
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
		btree_print_in_order(NULL, NULL, exibir_btree_jogadores, jogadores_idx.rrn_raiz, &jogadores_idx);
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
	if (jogadores_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_JOGADORES_IDX);
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


void imprimir_data_partida_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_data_partida_idx_menu()");
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

/* Funções de busca binária */

/**
 * Função Genérica de busca binária, que aceita parâmetros genéricos (assinatura baseada na função bsearch da biblioteca C).
 *
 * @param key Chave de busca genérica.
 * @param base0 Base onde ocorrerá a busca, por exemplo, um ponteiro para um vetor.
 * @param nmemb Número de elementos na base.
 * @param size Tamanho do tipo do elemento na base, dica: utilize a função sizeof().
 * @param compar Ponteiro para a função que será utilizada nas comparações.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso. Se true, imprime as posições avaliadas durante a busca, até que todas sejam visitadas ou o elemento seja encontrado (pela 1a vez).
 *                       Caso o número de elementos seja par (p.ex, 10 elementos), então há 2 (duas) possibilidades para a posição da mediana dos elementos (p.ex., 5a ou 6a posição se o total fosse 10).
 *                       Neste caso, SEMPRE escolha a posição mais à direita (p.ex., a posição 6 caso o total for 10).
 * @param posicao_caso_repetido Caso o elemento seja encontrado, se houver mais do que 1 ocorrência, indica qual deve ser retornada. As opções são:
 *                     -1 = primeira : retorna a PRIMEIRA ocorrência (posição mais à esquerda).
 *                      0 = meio : retorna a ocorrência do MEIO (posição central). [modo padrão]
 *                     +1 = ultima : retorna a ÚLTIMA ocorrência (posição mais à direita).
 * @param retorno_se_nao_encontrado Caso o elemento NÃO seja encontrado, indica qual valor deve ser retornado. As opções são:
 *                     -1 = predecessor : retorna o elemento PREDECESSOR (o que apareceria imediatamente antes do elemento procurado, caso fosse encontrado).
 *                      0 = nulo : retorna NULL. [modo padrão]
 *                     +1 = sucessor : retorna o elemento SUCESSOR (o que apareceria imediatamente depois do elemento procurado, caso fosse encontrado).
 * @return Retorna o elemento encontrado ou NULL se não encontrou.
 */
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "busca_binaria_com_reps()");
	return -1;
}


int busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}

/* Funções de manipulação de Lista Invertida */

/* Funções de manipulação de Lista Invertida */
/**
 * Responsável por inserir duas chaves (chave_secundaria e chave_primaria) em uma Lista Invertida (t).<br />
 * Atualiza os parâmetros dos índices primário e secundário conforme necessário.<br />
 * As chaves a serem inseridas devem estar no formato correto e com tamanho t->tam_chave_primario e t->tam_chave_secundario.<br />
 * O funcionamento deve ser genérico para qualquer Lista Invertida, adaptando-se para os diferentes parâmetros presentes em seus structs.<br />
 *
 * @param chave_secundaria Chave a ser buscada (caso exista) ou inserida (caso não exista) no registro secundário da Lista Invertida.
 * @param chave_primaria Chave a ser inserida no registro primário da Lista Invertida.
 * @param t Ponteiro para a Lista Invertida na qual serão inseridas as chaves.
 */
void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_insert()");
}


/**
 * Responsável por buscar uma chave no índice secundário de uma Lista invertida (T). O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e conterá o índice inicial das chaves no registro primário.<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, false, nome, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.<br />
 * ...<br />
 * bool found = inverted_list_secondary_search(NULL, false, nome, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse no caminho feito para encontrar a chave.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, true, nome, &jogador_kits_idx);<br />
 * </code>
 *
 * @param result Ponteiro para ser escrito o índice inicial (primeira ocorrência) das chaves do registro primário. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave_secundaria Chave a ser buscada.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_secondary_search()");
	return false;
}


/**
 * Responsável por percorrer o índice primário de uma Lista invertida (T). O valor de retorno indica a quantidade de chaves encontradas.
 * O ponteiro para o vetor de strings result pode ser fornecido opcionalmente, e será populado com a lista de todas as chaves encontradas.
 * O ponteiro para o inteiro indice_final também pode ser fornecido opcionalmente, e deve conter o índice do último campo da lista encadeada
 * da chave primaria fornecida (isso é útil na inserção de um novo registro).<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. As chaves encontradas deverão ser retornadas e tanto o caminho quanto o indice_final não devem ser informados.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, false, indice, NULL, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse nas chaves encontradas, apenas no indice_final, e o caminho não deve ser informado.<br />
 * ...<br />
 * int indice_final;
 * int qtd = inverted_list_primary_search(NULL, false, indice, &indice_final, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse nas chaves encontradas e no caminho feito.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, true, indice, NULL, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * </code>
 *
 * @param result Ponteiro para serem escritas as chaves encontradas. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param indice Índice do primeiro registro da lista encadeada a ser procurado.
 * @param indice_final Ponteiro para ser escrito o índice do último registro encontrado (cujo campo indice é -1). É ignorado caso NULL.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica a quantidade de chaves encontradas.
 */
int inverted_list_primary_search(char result[][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_secondary_search()");
	return -1;
}


/**
 * Responsável por buscar uma chave (k) dentre os registros secundários de uma Lista Invertida de forma eficiente.<br />
 * O valor de retorno deve indicar se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e conterá o índice no registro secundário da chave encontrada.<br />
 *
 * @param result Ponteiro para ser escrito o índice nos registros secundários da chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Lista Invertida.
 * @param t Ponteiro para o índice da Lista Invertida no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool inverted_list_binary_search(int* result, bool exibir_caminho, char *chave, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "inverted_list_secondary_search()");
	return false;
}


/* Funções de manipulação de Árvores-B */

/**
 * Responsável por inserir uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * A chave a ser inserida deve estar no formato correto e com tamanho t->tam_chave.<br />
 * O funcionamento deve ser genérico para qualquer Árvore-B, considerando que os únicos parâmetros que se alteram entre
 * as árvores é o t->tam_chave.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * ...<br />
 * char jogador_str[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * sprintf(jogador_str, "%s%04d", id_jogador, rrn_jogador);<br />
 * btree_insert(jogador_str, &jogadores_idx);<br />
 * ...<br />
 * </code>
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 */
void btree_insert(char *chave, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_insert()");
}


/**
 * Função auxiliar de inserção de uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * Esta é uma função recursiva. Ela recebe o RRN do nó a ser trabalhado sobre.<br />
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_insert_aux(char *chave, int rrn, btree *t) {
	promovido_aux p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_insert_aux()");
	return p;
}


/**
 * Função auxiliar para dividir um nó de uma Árvore-B (T). Atualiza os parâmetros conforme necessário.<br />
 *
 * @param promo Uma struct do tipo promovido_aux que contém a chave a ser inserida e o RRN do seu filho direito.
 * @param node Ponteiro para nó que deve ser dividido. 
 * @param i O índice da posição onde a chave a ser inserida deve estar.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_divide(promovido_aux promo, btree_node *node, int i, btree *t) {
	promovido_aux p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_divide()");
	return p;
}


/**
 * Responsável por remover uma chave (k) de uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * A chave a ser removida deve estar no formato correto e com tamanho t->tam_chave.<br />
 * O funcionamento deve ser genérico para qualquer Árvore-B, considerando que os únicos parâmetros que se alteram entre
 * as árvores é o t->tam_chave.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * ...<br />
 * char jogador_str[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * sprintf(jogador_str, "%s%04d", id_jogador, rrn_jogador);<br />
 * btree_delete(jogador_str, &jogadores_idx);<br />
 * ...<br />
 * </code>
 *
 * @param chave Chave a ser removida da Árvore-B.
 * @param t Ponteiro para o índice do tipo Árvore-B do qual será removida a chave.
 */
void btree_delete(char *chave, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_delete()");
}


/**
 * Função auxiliar de remoção de uma chave (k) de uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * Esta é uma função recursiva. Ela recebe o RRN do nó a ser trabalhado sobre.<br />
 *
 * @param chave Chave a ser removida da Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B do qual será removida a chave.
 * @return Indica se a remoção deixou o nó que foi processado com menos chaves que o mínimo necessário.
 */
bool btree_delete_aux(char *chave, int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_delete_aux()");
	return false;
}


/**
 * Função auxiliar para redistribuir ou concatenar nós irmãos adjacentes à esquerda e à direita de um nó pai em uma Árvore-B (T). 
 * Atualiza os parâmetros conforme necessário.<br />
 *
 * @param node Ponteiro para nó pai dos nós irmãos adjacentes que deve ser redistribuidos ou concatenados. 
 * @param i O índice da posição no nó pai onde se encontra a chave separadora dos nós irmãos adjacentes.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual serão redistribuídos ou concatenados os nós irmãos adjacentes.
 * @return Indica se a redistribuição ou concatenação deixou o nó pai com menos chaves que o mínimo necessário.
 */
bool btree_borrow_or_merge(btree_node *node, int i, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_borrow_or_merge()");
	return false;
}


/**
 * Responsável por buscar uma chave (k) em uma Árvore-B (T). O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para a string result pode ser fornecido opcionalmente, e conterá o resultado encontrado.<br />
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo fornecido.<br />
 * Comportamento de acordo com as especificações do PDF sobre Árvores-B e suas operações.<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.<br />
 * ...<br />
 * char result[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * bool found = btree_search(result, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.<br />
 * ...<br />
 * bool found = btree_search(NULL, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);<br />
 * ...<br />
 * <br />
* // Exemplo 3. Há interesse no caminho feito para encontrar a chave.<br />
  * ...<br />
 * char result[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * bool found = btree_search(result, true, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);<br />
 * printf("\n");<br />
 * </code>
 *
 * @param result Ponteiro para ser escrita a chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado. É o RRN da raíz da Árvore-B caso seja a primeira chamada.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool btree_search(char *result, bool exibir_caminho, char *chave, int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_search()");
	return false;
}


/**
 * Responsável por buscar uma chave (k) dentro do nó de uma Árvore-B (T) de forma eficiente. O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e indica o índice da chave encontrada (caso tenha sido encontrada) 
 * ou o índice do filho onde esta chave deve estar (caso não tenha sido encontrada).<br />
 *
 * @param result Ponteiro para ser escrito o índice da chave encontrada ou do filho onde ela deve estar. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Árvore-B.
 * @param node Ponteiro para o nó onde a busca deve ser feita.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool btree_binary_search(int *result, bool exibir_caminho, char* chave, btree_node* node, btree* t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_binary_search()");
	return false;
}


/**
 * Função para percorrer uma Árvore-B (T) em ordem e armazenar as chaves, em result, que estiverem dentro do intervalo fornecido.<br />
 * Os parâmetros chave_inicio e chave_fim podem ser fornecidos opcionalmente, e contém o intervalo do percurso.
 * Caso chave_inicio e chave_fim sejam NULL, o índice inteiro é percorrido.
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo de percursão em ordem.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * // Exemplo 1. Intervalo não especificado.
 * ...<br />
 * bool imprimiu = btree_search_in_order(result, NULL, NULL, 0, jogadores_idx.rrn_raiz, &jogadores_idx);
 * ...<br />
 * <br />
 * // Exemplo 2. Imprime as transações contidas no intervalo especificado.
 * ...<br />
 * bool imprimiu = btree_search_in_order(result, data_inicio, data_fim, 0, data_partida_idx.rrn_raiz, &data_partida_idx);
 * ...<br />
 * </code>
 *
 * @param result Vetor de strings onde serão armazenadas as chaves dos registros válidos.
 * @param chave_inicio Começo do intervalo. É ignorado caso NULL.
 * @param chave_fim Fim do intervalo. É ignorado caso NULL.
 * @param qtd Recebe a quantidade atual de chaves válidas (valor usado para retornar a quantidade com a recursão).
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Indica a quantidade de chaves válidas.
 */
int btree_search_in_order(char **result, char *chave_inicio, char *chave_fim, int qtd, int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_search_in_order()");
	return 0;
}


/**
 * Função para percorrer uma Árvore-B (T) em ordem.<br />
 * Os parâmetros chave_inicio e chave_fim podem ser fornecidos opcionalmente, e contém o intervalo do percurso.
 * Caso chave_inicio e chave_fim sejam NULL, o índice inteiro é percorrido.
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo de percursão em ordem.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * // Exemplo 1. Intervalo não especificado.
 * ...<br />
 * bool imprimiu = btree_print_in_order(NULL, NULL, exibir_btree_jogadores, jogadores_idx.rrn_raiz, &jogadores_idx);
 * ...<br />
 * <br />
 * // Exemplo 2. Imprime as transações contidas no intervalo especificado.
 * ...<br />
 * bool imprimiu = btree_print_in_order(data_inicio, data_fim, exibir_btree_data_partida, data_partida_idx.rrn_raiz, &data_partida_idx);
 * ...<br />
 * </code>
 *
 * @param chave_inicio Começo do intervalo. É ignorado caso NULL.
 * @param chave_fim Fim do intervalo. É ignorado caso NULL.
 * @param exibir Função utilizada para imprimir uma chave no índice. É informada a chave para a função.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Indica se alguma chave foi impressa.
 */
bool btree_print_in_order(char *chave_inicio, char *chave_fim, bool (*exibir)(char *chave), int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_print_in_order()");
	return false;
}


/**
 * Função interna para ler um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser lido da Árvore-B.
 * @param t Árvore-B na qual será feita a leitura do nó.
 */
btree_node btree_read(int rrn, btree *t) {
	btree_node no;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_read()");
	return no;
}


/**
 * Função interna para escrever um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser escrito na Árvore-B.
 * @param t Árvore-B na qual será feita a escrita do nó.
 */
void btree_write(btree_node no, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_write()");
}


/**
 * Função interna para alocar o espaço necessário dos campos chaves (vetor de strings) e filhos (vetor de inteiros) da struct btree_node.<br />
 *
 * @param t Árvore-B base para o qual será alocado um struct btree_node.
 */
btree_node btree_node_malloc(btree *t) {
	btree_node no;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "btree_write()");
	return no;
}


/**
 * Função interna para calcular o tamanho em bytes de uma Árvore-B.<br />
 *
 * @param t Árvore-B base para o qual será calculado o tamanho.
 */
int btree_register_size(btree *t) {
	int chaves_ordenadas = (btree_order-1)*t->tam_chave;
	return 3 + chaves_ordenadas + 1 + (btree_order*3);
}


/* Funções Auxiliares */

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