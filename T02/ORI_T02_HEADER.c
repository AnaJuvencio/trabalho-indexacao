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
    char str[TAM_CHAVE_KITS_IDX + 1];
    for (unsigned i = 0; i < qtd_registros_kits; ++i) {
        Kit k = recuperar_registro_kit(i);

        sprintf(str, "%s%04d", k.id_kit, i);
        btree_insert(str, &kits_idx);
    }
    printf(INDICE_CRIADO, "kits_idx");
}


void criar_partidas_idx() {
    char str[TAM_CHAVE_PARTIDAS_IDX + 1];
    for (unsigned i = 0; i < qtd_registros_partidas; ++i) {
        Partida p = recuperar_registro_partida(i);

        sprintf(str, "%s%04d", p.id_partida, i);
        btree_insert(str, &partidas_idx);
    }
    printf(INDICE_CRIADO, "partidas_idx");
}


void criar_resultados_idx() {
    char str[TAM_CHAVE_RESULTADOS_IDX + 1];
    for (unsigned i = 0; i < qtd_registros_resultados; ++i) {
        Resultado r = recuperar_registro_resultado(i);

        sprintf(str, "%s%s%04d", r.id_jogador, r.id_partida, i);
        btree_insert(str, &resultados_idx);
    }
    printf(INDICE_CRIADO, "resultados_idx");
}

void criar_preco_kit_idx() {
    char str[TAM_CHAVE_PRECO_KIT_IDX + 1];
    for (unsigned i = 0; i < qtd_registros_kits; ++i) {
        Kit k = recuperar_registro_kit(i);

        sprintf(str, "%013.2f%s", k.preco, k.id_kit);
        btree_insert(str, &preco_kit_idx);
    }
    printf(INDICE_CRIADO, "preco_kit_idx");
}


void criar_data_partida_idx() {
    char str[TAM_CHAVE_DATA_PARTIDA_IDX + 1];
    for (unsigned i = 0; i < qtd_registros_partidas; ++i) {
        Partida p = recuperar_registro_partida(i);

        sprintf(str, "%s%s", p.inicio, p.id_partida);
        btree_insert(str, &data_partida_idx);
    }
    printf(INDICE_CRIADO, "data_partida_idx");
}


void criar_jogador_kits_idx() {
    char str[TAM_MAX_NOME_KIT];
    for (unsigned i = 0; i < qtd_registros_jogadores; ++i) {
        Jogador j = recuperar_registro_jogador(i);

        for (unsigned k = 0; k < QTD_MAX_KITS; ++k) {
            if (j.kits[k][0] != '\0') { // Verifica se o kit existe
                // Aqui assumimos que existe uma função para buscar o RRN do kit pelo ID do kit
                int rrn_kit = busca_binaria(j.kits[k], ARQUIVO_KITS_IDX, qtd_registros_kits, TAM_CHAVE_KITS_IDX, order_kits_idx, false, -1);
                if (rrn_kit != -1) {
                    Kit kit = recuperar_registro_kit(rrn_kit);

                    strncpy(str, kit.nome, TAM_MAX_NOME_KIT - 1);
                    str[TAM_MAX_NOME_KIT - 1] = '\0';

                    // Preenche com '#' até TAM_MAX_NOME_KIT - 1
                    for (unsigned l = strlen(str); l < TAM_MAX_NOME_KIT - 1; ++l) {
                        str[l] = '#';
                    }
                    str[TAM_MAX_NOME_KIT - 1] = '\0';

                    // Converte para maiúsculas
                    for (unsigned l = 0; l < TAM_MAX_NOME_KIT - 1; ++l) {
                        str[l] = toupper(str[l]);
                    }

                    inverted_list_insert(str, j.id_jogador, &jogador_kits_idx);
                }
            }
        }
    }
    printf(INDICE_CRIADO, "jogador_kits_idx");
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
    char data[TAM_REGISTRO_KIT + 1], *p;
    // Copiando os dados do registro do kit do arquivo para a variável data
    strncpy(data, ARQUIVO_KITS + (rrn * TAM_REGISTRO_KIT), TAM_REGISTRO_KIT);
    data[TAM_REGISTRO_KIT] = '\0'; // Garante terminação nula
    // Dividindo os dados do registro do kit usando o delimitador ";"
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
    char data[TAM_REGISTRO_PARTIDA + 1];
    // Copiando o registro do arquivo com base no RRN
    strncpy(data, ARQUIVO_PARTIDAS + (rrn * TAM_REGISTRO_PARTIDA), TAM_REGISTRO_PARTIDA);
    data[TAM_REGISTRO_PARTIDA] = '\0'; // Garante terminação nula
    // Dividndo os dados do registro da partida usando o delimitador ;

    // id_partida (8 bytes ), inicio (12 bytes ), duracao (6 bytes ), cenario (4 bytes ) e id_jogadores (132 bytes, correspondendo a 12 ID de jogadores ×11 bytes cada)

    strncpy(p.id_partida, data, 8);
    p.id_partida[8] = '\0';
    strncpy(p.inicio, data+8, 12);
    p.inicio[12] = '\0';
    strncpy(p.duracao, data+20, 6);
    p.duracao[6] = '\0';
    strncpy(p.cenario, data+26, 4);
    p.cenario[4] = '\0';
    strncpy(p.id_jogadores, data+30, 132);
    p.id_jogadores[132] = '\0';


    // token = strtok(data, ";");
    // strcpy(p.id_partida, token);  
    // token = strtok(NULL, ";");
    // strcpy(p.inicio, token);  
    // token = strtok(NULL, ";");
    // strcpy(p.duracao, token);  
    // token = strtok(NULL, ";");
    // strcpy(p.cenario, token);  
    // token = strtok(NULL, ";");
    // strcpy(p.id_jogadores, token);  // Ids dos jogadores separados por "|"
    return p;
}



Resultado recuperar_registro_resultado(int rrn) {

    Resultado r;
    char data[TAM_REGISTRO_RESULTADO + 1];
    // Copiando os dados do registro de resultado do arquivo para a variável data
    strncpy(data, ARQUIVO_RESULTADOS + (rrn * TAM_REGISTRO_RESULTADO), TAM_REGISTRO_RESULTADO);
    data[TAM_REGISTRO_RESULTADO] = '\0'; // Garante terminação nula
    // Dividindo os dados do registro do resultado usando o delimitador ;

    // id_jogador (11 bytes ), id_partida (8 bytes ), id_kit (3 bytes ), colocacao (4 bytes ),  (6 bytes ) e eliminacoes (4 bytes )]

    strncpy(r.id_jogador, data, 11);
    r.id_jogador[11] = '\0';
    strncpy(r.id_partida, data+11, 8);
    r.id_partida[8] = '\0';
    strncpy(r.id_kit, data+19, 3);
    r.id_kit[3] = '\0';

    char number[TAM_INT_NUMBER];
    strncpy(number, data+22, TAM_INT_NUMBER-1);
    number[TAM_INT_NUMBER] = '\0';

    r.colocacao = atoi(number);

    strncpy(r.sobrevivencia, data+26, 6);
    r.sobrevivencia[6] = '\0';
    
    r.eliminacoes = atoi(data+32);


    // p = strtok(data, ";");
    // strcpy(r.id_jogador, p); 
    // p = strtok(NULL, ";");
    // strcpy(r.id_partida, p); 
    // p = strtok(NULL, ";");
    // strcpy(r.id_kit, p); 
    // p = strtok(NULL, ";");
    // r.colocacao = atoi(p); 
    // p = strtok(NULL, ";");
    // strcpy(r.sobrevivencia, p); 
    // p = strtok(NULL, ";");
    // r.eliminacoes = atoi(p); 
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

    char data[TAM_REGISTRO_KIT + 1], number[100];
    data[0] = '\0'; 
    number[0] = '\0';
    // Concatenando os campos na string data
    strcat(data, k.id_kit);
    strcat(data, ";");
    strcat(data, k.nome);
    strcat(data, ";");
    strcat(data, k.poder);
    strcat(data, ";");
    // Formatando o preço como string
    sprintf(number, "%013.2lf", k.preco);
    strcat(data, number);
    strcat(data, ";");
    // Preenchendo o restante com padding até TAM_REGISTRO
    strpadright(data, '#', TAM_REGISTRO_KIT);
    // Escrevendo no arquivo na posição certa
    strncpy(ARQUIVO_KITS + rrn * TAM_REGISTRO_KIT, data, TAM_REGISTRO_KIT);
}



void escrever_registro_partida(Partida p, int rrn) {
    char data[TAM_REGISTRO_PARTIDA + 1];
    data[0] = '\0';
    // Concatenando os campos na string data
    strcat(data, p.id_partida);
    strcat(data, p.inicio);
    strcat(data, p.duracao);
    strcat(data, p.cenario);
    strcat(data, p.id_jogadores);
    // Escrevendo no arquivo na posição certa
    strncpy(ARQUIVO_PARTIDAS + rrn * TAM_REGISTRO_PARTIDA, data, TAM_REGISTRO_PARTIDA);
}


void escrever_registro_resultado(Resultado jp, int rrn) {
    char data[TAM_REGISTRO_RESULTADO + 1], number[TAM_INT_NUMBER];
    data[0] = '\0';
    number[0] = '\0';
    // Concatenando os campos na string data
    strcat(data, jp.id_jogador);
    strcat(data, jp.id_partida);
    strcat(data, jp.id_kit);
    // Formatando a colocação como string de 4 bytes
    sprintf(number, "%04d", jp.colocacao);
    strcat(data, number);
    strcat(data, jp.sobrevivencia);
    // Formatanso as eliminações como string de 4 bytes
    sprintf(number, "%04d", jp.eliminacoes);
    strcat(data, number);
    
    // Escrevendo no arquivo na posição adequada
    strncpy(ARQUIVO_RESULTADOS + rrn * TAM_REGISTRO_RESULTADO, data, TAM_REGISTRO_RESULTADO);
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



void cadastrar_jogador_menu(char *id_jogador, char *apelido) {
    char result[TAM_CHAVE_JOGADORES_IDX + 1];

    // Verificando se o jogador já foi inserido na árvore
    if (btree_search(result, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx)) {
        printf(ERRO_PK_REPETIDA, id_jogador);
        return;
    }

    // Cadastrando todos os dados do jogador
    Jogador novo_jogador;
    strncpy(novo_jogador.id_jogador, id_jogador, TAM_ID_JOGADOR - 1);
    novo_jogador.id_jogador[TAM_ID_JOGADOR - 1] = '\0';
    strncpy(novo_jogador.apelido, apelido, TAM_MAX_APELIDO - 1);
    novo_jogador.apelido[TAM_MAX_APELIDO - 1] = '\0';
    current_datetime(novo_jogador.cadastro);
    current_datetime(novo_jogador.premio);
    novo_jogador.saldo = 0.0;
    memset(novo_jogador.kits, 0, sizeof(novo_jogador.kits));

    // Inserindo o novo jogador na árvore 
    char str[TAM_CHAVE_JOGADORES_IDX + 1];
    sprintf(str, "%s%04d", novo_jogador.id_jogador, qtd_registros_jogadores);
    btree_insert(str, &jogadores_idx);

    // Escrevendo o novo jogador no arquivo de dados
    escrever_registro_jogador(novo_jogador, qtd_registros_jogadores);

    // Incrementando o contador de registros de jogadores
    qtd_registros_jogadores++;
    printf(SUCESSO);
}

// Até que foi tranquilo fazer, precisa testar :(
void remover_jogador_menu(char *id_jogador) {
    // Verifica se o jogador se encontra no sistema
    char chave_jogador[TAM_CHAVE_JOGADORES_IDX + 1];
    sprintf(chave_jogador, "%s", id_jogador);
    bool jogador_encontrado = btree_search(chave_jogador, false, chave_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
    if (!jogador_encontrado) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Recupera o jogador no arquivo
    int rrn_jogador = atoi(chave_jogador + TAM_ID_JOGADOR - 1);
    Jogador jogador = recuperar_registro_jogador(rrn_jogador);

    // Marca o jogador como excluído e escreve no arquivo
    jogador.id_jogador[0] = '*';
    escrever_registro_jogador(jogador, rrn_jogador);

    // Remove do índice de jogadores
    btree_delete(chave_jogador, &jogadores_idx);

    printf(SUCESSO);
}


void adicionar_saldo_menu(char *id_jogador, double valor) {
	adicionar_saldo(id_jogador, valor, true);
}


void adicionar_saldo(char *id_jogador, double valor, bool flag) {
    char result[TAM_CHAVE_JOGADORES_IDX + 1];

    // Verifica se o jogador está na árvore de jogadores
    if (!btree_search(result, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx)) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Verifica se o valor a ser inserido é menor ou igual a zero
    if (valor <= 0) {
        printf(ERRO_VALOR_INVALIDO);
        return;
    }

    // Recupera o jogador
    int rrn = atoi(result + TAM_ID_JOGADOR);
    Jogador j = recuperar_registro_jogador(rrn);

    // Atualiza o saldo
    j.saldo += valor;

    // Escreve o registro atualizado
    escrever_registro_jogador(j, rrn);

    printf(SUCESSO);
}

void cadastrar_kit_menu(char *nome, char *poder, double preco) {
    // Criando um novo kit e preenchendo os dados
    Kit novo_kit;
    sprintf(novo_kit.id_kit, "%03d", qtd_registros_kits);
    strcpy(novo_kit.nome, nome);
    strcpy(novo_kit.poder, poder);
    novo_kit.preco = preco;

    // Escrevendo o novo registro do kit
    escrever_registro_kit(novo_kit, qtd_registros_kits);

    // Criando as chaves para os índices
    char chave_kits_idx[7]; // id_kit (3 bytes) + rrn (4 bytes)
    sprintf(chave_kits_idx, "%s%04d", novo_kit.id_kit, qtd_registros_kits);

    char chave_preco_kit_idx[16]; // preco (13 bytes) + id_kit (3 bytes)
    sprintf(chave_preco_kit_idx, "%013.2f%s", novo_kit.preco, novo_kit.id_kit);

    // Inserindo nos índices
    btree_insert(chave_kits_idx, &kits_idx);
    btree_insert(chave_preco_kit_idx, &preco_kit_idx);

    // Incrementando a quantidade de registros de kits
    qtd_registros_kits++;

    // Exibindo a mensagem de sucesso
    printf(SUCESSO);
}


void comprar_kit_menu(char *id_jogador, char *id_kit) {
    // Cria duas chaves para recuperar 'jogador' e 'kit' durante a busca
    char chave_jogador[TAM_CHAVE_JOGADORES_IDX + 1];
    char chave_kit[TAM_CHAVE_KITS_IDX + 1];
    sprintf(chave_jogador, "%s", id_jogador);
    sprintf(chave_kit, "%s", id_kit);

    // Verifica se o jogador já existe
    int indice_jogador;
    bool jogador_encontrado = btree_search(chave_jogador, false, chave_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
    if (!jogador_encontrado) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Verifica se o kit existe
    int indice_kit;
    bool kit_encontrado = btree_search(chave_kit, false, chave_kit, kits_idx.rrn_raiz, &kits_idx);
    if (!kit_encontrado) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }

    // Cria dois inteiros para recuperar o rrn
    int rrn_jogador = atoi(chave_jogador + TAM_ID_JOGADOR - 1);
    int rrn_kit = atoi(chave_kit + TAM_ID_KIT - 1);

    // Recupera os registros usando o rrn
    Jogador jogador = recuperar_registro_jogador(rrn_jogador);
    Kit kit = recuperar_registro_kit(rrn_kit);

    // Checa se o valor do kit é maior que o saldo do jogador
    if (jogador.saldo < kit.preco) {
        printf(ERRO_SALDO_NAO_SUFICIENTE);
        return;
    }

    // Verifica se o jogador já possui o kit
    for (int i = 0; i < QTD_MAX_KITS; i++) {
        if (strcmp(jogador.kits[i], id_kit) == 0) {
            printf(ERRO_KIT_REPETIDO, jogador.id_jogador, kit.nome);
            return;
        }
    }

    // Atribui o novo kit ao jogador
    for (int i = 0; i < QTD_MAX_KITS; i++) {
        if (jogador.kits[i][0] == '\0') {
            strcpy(jogador.kits[i], id_kit);
            break;
        }
    }
    jogador.saldo -= kit.preco; // Atualiza o saldo do jogador

    // Escreve o registro do jogador
    escrever_registro_jogador(jogador, rrn_jogador);

    // Atualiza a lista invertida
    char kit_maiusculo[TAM_MAX_NOME_KIT];
    strupr(strcpy(kit_maiusculo, kit.nome));
    inverted_list_insert(kit_maiusculo, jogador.id_jogador, &jogador_kits_idx);

    printf(SUCESSO);
}


void executar_partida_menu(char *inicio, char *duracao, char *cenario, char *id_jogadores, char *kits_jogadores, char *duracoes_jogadores, char *eliminacoes_jogadores) {
    // Verificando se todos os jogadores existem e possuem os kits
    for (int i = 0; i < QTD_MAX_JOGADORES; i++) {
        char id_jogador[TAM_ID_JOGADOR];
        char id_kit[TAM_ID_KIT];
        strncpy(id_jogador, id_jogadores + i * (TAM_ID_JOGADOR - 1), TAM_ID_JOGADOR - 1);
        id_jogador[TAM_ID_JOGADOR - 1] = '\0';
        strncpy(id_kit, kits_jogadores + i * (TAM_ID_KIT - 1), TAM_ID_KIT - 1);
        id_kit[TAM_ID_KIT - 1] = '\0'; // Garantindo terminação nula

        // Verificando se o jogador existe
        char chave_jogador[TAM_CHAVE_JOGADORES_IDX + 1];
        sprintf(chave_jogador, "%s", id_jogador);
        bool jogador_encontrado = btree_search(chave_jogador, false, chave_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
        if (!jogador_encontrado) {
            printf(ERRO_REGISTRO_NAO_ENCONTRADO);
            return;
        }
        int rrn_jogador = atoi(chave_jogador + TAM_ID_JOGADOR - 1);
        Jogador jogador = recuperar_registro_jogador(rrn_jogador); // Recuperando o jogador

        // Verificar se o jogador possui o kit
        bool possui_kit = false;
        for (int j = 0; j < QTD_MAX_KITS; j++) {
            if (strcmp(jogador.kits[j], id_kit) == 0) {
                possui_kit = true;
                break;
            }
        }
        if (!possui_kit) {
            char chave_kit[TAM_CHAVE_KITS_IDX + 1];
            sprintf(chave_kit, "%s", id_kit);
            bool kit_encontrado = btree_search(chave_kit, false, chave_kit, kits_idx.rrn_raiz, &kits_idx);
            if (!kit_encontrado) {
                printf(ERRO_REGISTRO_NAO_ENCONTRADO);
                return;
            }
            int rrn_kit = atoi(chave_kit + TAM_ID_KIT - 1);
            Kit k = recuperar_registro_kit(rrn_kit);
            printf(ERRO_JOGADOR_KIT, id_jogador, k.nome);
            return;
        }
    }

    // Guardando os resultados individuais
    for (int i = 0; i < QTD_MAX_JOGADORES; i++) {
        char id_jogador[TAM_ID_JOGADOR];
        char id_kit[TAM_ID_KIT];
        strncpy(id_jogador, id_jogadores + i * (TAM_ID_JOGADOR - 1), TAM_ID_JOGADOR - 1);
        id_jogador[TAM_ID_JOGADOR - 1] = '\0';
        strncpy(id_kit, kits_jogadores + i * (TAM_ID_KIT - 1), TAM_ID_KIT - 1);
        id_kit[TAM_ID_KIT - 1] = '\0'; // Garantindo terminação nula

        // Criando um novo resultado e preenchendo as variáveis
        Resultado resultado;
        strcpy(resultado.id_jogador, id_jogador);
        sprintf(resultado.id_partida, "%08d", qtd_registros_partidas);
        strcpy(resultado.id_kit, id_kit);
        resultado.colocacao = i + 1;
        strncpy(resultado.sobrevivencia, duracoes_jogadores + i * (TAM_TIME - 1), TAM_TIME - 1);
        resultado.sobrevivencia[TAM_TIME - 1] = '\0';
        char aux[TAM_INT_NUMBER];
        strncpy(aux, eliminacoes_jogadores + i * (TAM_INT_NUMBER - 1), TAM_INT_NUMBER - 1);
        aux[TAM_INT_NUMBER - 1] = '\0';
        resultado.eliminacoes = atoi(aux);

        // Escrevendo o resultado e atualizando o índice
        escrever_registro_resultado(resultado, qtd_registros_resultados);

        // Criando a chave para o índice de resultados
        char chave_resultado[TAM_CHAVE_RESULTADOS_IDX + 1];
        sprintf(chave_resultado, "%s%s", resultado.id_jogador, resultado.id_partida);
        btree_insert(chave_resultado, &resultados_idx);

        qtd_registros_resultados++;
    }

    // Preenchendo uma nova partida
    Partida partida;
    sprintf(partida.id_partida, "%08d", qtd_registros_partidas);
    strcpy(partida.inicio, inicio);
    strcpy(partida.duracao, duracao);
    strcpy(partida.cenario, cenario);
    strncpy(partida.id_jogadores, id_jogadores, TAM_ID_JOGADORES);
    partida.id_jogadores[TAM_ID_JOGADORES] = '\0';

    // Escrevendo a partida
    escrever_registro_partida(partida, qtd_registros_partidas);

    // Atualizando o índice de partidas
    char chave_partida[TAM_CHAVE_PARTIDAS_IDX + 1];
    sprintf(chave_partida, "%s", partida.id_partida);
    btree_insert(chave_partida, &partidas_idx);

    // Atualizando o índice de datas
    char chave_data[TAM_CHAVE_DATA_PARTIDA_IDX + 1];
    sprintf(chave_data, "%s%s", partida.inicio, partida.id_partida);
    btree_insert(chave_data, &data_partida_idx);

    qtd_registros_partidas++;

    printf(SUCESSO);
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
    if (qtd_registros_kits == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_KITS);
}


void imprimir_arquivo_partidas_menu() {
    if (qtd_registros_partidas == 0) // Verifica se o arquivo de partidas está vazio
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_PARTIDAS);
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
    if (kits_idx.qtd_nos == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_KITS_IDX);
}


void imprimir_partidas_idx_menu() {
    if (partidas_idx.qtd_nos == 0) { // Verifica se o índice de partidas está vazio
        printf(ERRO_ARQUIVO_VAZIO);
    } else {
        // Itera sobre os nós da árvore B e imprime as chaves
        for (unsigned i = 0; i < partidas_idx.qtd_nos; ++i) {
            btree_node node = btree_read(i, &partidas_idx);
            for (int j = 0; j < node.qtd_chaves; ++j) {
                printf("%s\n", node.chaves[j]);
            }
            btree_node_free(node);
        }
    }
}


void imprimir_resultados_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "imprimir_resultados_idx_menu()");
}


/* Imprimir índices secundários */
void imprimir_preco_kit_idx_menu() {
    if (preco_kit_idx.qtd_nos == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_PRECO_KIT_IDX);
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

// Utilizando  a lógica do trabalho anterior como base
/* Liberar espaço */
void liberar_espaco_menu() {
    int rrn_atual = 0; // RRN atualizado para os registros válidos

    // Redefine a raiz do índice e a quantidade de nós
    jogadores_idx.rrn_raiz = -1;
    jogadores_idx.qtd_nos = 0;

    for (int i = 0; i < qtd_registros_jogadores; ++i) {
        // Recuperando o registro do jogador no índice atual
        Jogador jogador = recuperar_registro_jogador(i);

        // Verificando se o registro é válido
        if (strncmp(jogador.id_jogador, "*", 1) != 0) {
            // Reescreve o registro no arquivo de dados no RRN correspondente
            escrever_registro_jogador(jogador, rrn_atual);

            // Criando a chave (id + rrn) e insere o jogador na árvore
            char chave_jogador[TAM_CHAVE_JOGADORES_IDX + 1];
            sprintf(chave_jogador, "%s%04d", jogador.id_jogador, rrn_atual);
            btree_insert(chave_jogador, &jogadores_idx);

            rrn_atual++; // Incrementando o RRN para a próxima posição válida
        }
    }

    // Atualizando o número de registros para refletir apenas os válidos
    qtd_registros_jogadores = rrn_atual;

    // Marcando o fim do arquivo com \0 após o último registro válido
    ARQUIVO_JOGADORES[rrn_atual * TAM_REGISTRO_JOGADOR] = '\0';
    printf(SUCESSO);
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
    int indice_secundario;
    bool chave_encontrada = inverted_list_secondary_search(&indice_secundario, false, chave_secundaria, t);

    if (!chave_encontrada) {
        // Inserindo a chave secundária no índice secundário
        fseek(t->arquivo_secundario, t->qtd_registros_secundario * (t->tam_chave_secundaria + sizeof(int)), SEEK_SET);
        fprintf(t->arquivo_secundario, "%-*s%04d", t->tam_chave_secundaria, chave_secundaria, t->qtd_registros_primario);
        // Incrementando a quantidade de registros secundários
        t->qtd_registros_secundario++;
        // Inserindo o jogador no índice primário
        fseek(t->arquivo_primario, t->qtd_registros_primario * (t->tam_chave_primaria + sizeof(int)), SEEK_SET);
        fprintf(t->arquivo_primario, "%-*s%04d", t->tam_chave_primaria, chave_primaria, -1);
        // Incrementando a quantidade de registros primários
        t->qtd_registros_primario++;
        // Ordenando o índice secundário
        qsort(t->arquivo_secundario, t->qtd_registros_secundario, t->tam_chave_secundaria + sizeof(int), t->compar);
    } else {
        // Recuperando o índice final da lista encadeada
        int indice_final;
        inverted_list_primary_search(NULL, false, indice_secundario, &indice_final, t);
        // Inserindo o novo jogador no índice primário
        fseek(t->arquivo_primario, t->qtd_registros_primario * (t->tam_chave_primaria + sizeof(int)), SEEK_SET);
        fprintf(t->arquivo_primario, "%-*s%04d", t->tam_chave_primaria, chave_primaria, -1);
        // Atualizando o próximo índice do último jogador na lista encadeada
        fseek(t->arquivo_primario, indice_final * (t->tam_chave_primaria + sizeof(int)) + t->tam_chave_primaria, SEEK_SET);
        fprintf(t->arquivo_primario, "%04d", t->qtd_registros_primario);
        // Incrementando a quantidade de registros primários
        t->qtd_registros_primario++;
    }
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
    return inverted_list_binary_search(result, exibir_caminho, chave_secundaria, t);
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
    int indice_atual = indice;
    int count = 0;
    char chave_primaria[TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX + 1];
    int proximo_indice;

    while (indice_atual != -1) {
        // Calcula o offset no arquivo primário
        long offset = indice_atual * (t->tam_chave_primaria + sizeof(int));

        // Move o ponteiro do arquivo para o offset calculado
        fseek(t->arquivo_primario, offset, SEEK_SET);

        // Lê a chave primária e o próximo índice
        fread(chave_primaria, sizeof(char), t->tam_chave_primaria, t->arquivo_primario);
        chave_primaria[t->tam_chave_primaria] = '\0';
        fread(&proximo_indice, sizeof(int), 1, t->arquivo_primario);

        if (exibir_caminho) {
            printf("%d ", indice_atual);
        }

        if (result != NULL) {
            strcpy(result[count], chave_primaria);
            count++;
        }

        if (proximo_indice == -1) {
            *indice_final = indice_atual;
            return count;
        }

        indice_atual = proximo_indice;
    }

    return count;
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
    const char *base = t->arquivo_secundario;
    size_t lim = t->qtd_registros_secundario;
    size_t size = (TAM_MAX_NOME_KIT - 1) + TAM_RRN_REGISTRO;
    size_t meio;
    int cmp;
    size_t pos_inicial = 0;
    bool chave_encontrada = false;

    // Exibindo registros percorridos
    if (exibir_caminho) {
        printf("(");
    }

    while (lim > 0) {
        meio = lim >> 1; // Calculando a mediana
        const void *p = base + meio * size;
        char chave_atual[TAM_MAX_NOME_KIT];
        strncpy(chave_atual, p, TAM_MAX_NOME_KIT - 1);
        chave_atual[TAM_MAX_NOME_KIT - 1] = '\0';

        cmp = t->compar(chave, chave_atual);

        // Exibindo índice atual no caminho
        if (exibir_caminho) {
            printf("%ld", pos_inicial + meio);
            if (cmp == 0) {
                printf(")\n"); // Último valor do caminho
            } else if (lim > 1) {
                printf(" "); // Espaço entre índices
            }
        }

        if (cmp == 0) {
            chave_encontrada = true;
            if (result != NULL) {
                char rrn_str[TAM_RRN_REGISTRO + 1];
                strncpy(rrn_str, p + (TAM_MAX_NOME_KIT - 1), TAM_RRN_REGISTRO);
                rrn_str[TAM_RRN_REGISTRO] = '\0';
                *result = atoi(rrn_str);
            }
            break;
        }

        if (cmp > 0) { // Movendo para a metade direita
            base += (meio + 1) * size;
            pos_inicial += meio + 1;
            lim -= meio + 1;
        } else { // Movendo para a metade esquerda
            lim = meio;
        }
    }

    if (exibir_caminho && !chave_encontrada) { // Quando a chave não é encontrada
        printf(")\n");
    }

    if (chave_encontrada) {
        return true;
    } else {
        *result = pos_inicial;
        return false;
    }
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
    if (t->rrn_raiz == -1) {
        // Criando uma nova raiz se a árvore estiver vazia
        btree_node nova_raiz = btree_node_malloc(t);
        nova_raiz.this_rrn = t->qtd_nos++;
        nova_raiz.qtd_chaves = 1;
        nova_raiz.folha = true;
        nova_raiz.chaves[0] = strdup(chave);
        for (int i = 1; i < btree_order - 1; i++) {
            nova_raiz.chaves[i] = strdup("#");
        }
        nova_raiz.filhos[0] = -1;
        nova_raiz.filhos[1] = -1;
        t->rrn_raiz = nova_raiz.this_rrn;
        btree_write(nova_raiz, t);
        btree_node_free(nova_raiz);
        return;
    }

    promovido_aux promovido = btree_insert_aux(chave, t->rrn_raiz, t);

    if (promovido.chave_promovida[0] != '\0') {
        // Inserindo uma nova raiz se a chave promovida não estiver vazia
        btree_node nova_raiz = btree_node_malloc(t);
        nova_raiz.this_rrn = t->qtd_nos++;
        nova_raiz.qtd_chaves = 1;
        nova_raiz.folha = (promovido.filho_direito == -1);
        nova_raiz.chaves[0] = strdup(promovido.chave_promovida);
        for (int i = 1; i < btree_order - 1; i++) {
            nova_raiz.chaves[i] = strdup("#");
        }
        nova_raiz.filhos[0] = t->rrn_raiz;
        nova_raiz.filhos[1] = promovido.filho_direito;
        t->rrn_raiz = nova_raiz.this_rrn;
        btree_write(nova_raiz, t);
        btree_node_free(nova_raiz);
    }
}

promovido_aux btree_insert_aux(char *chave, int rrn_atual, btree *t) {
    promovido_aux promovido;
    strcpy(promovido.chave_promovida, "");
    promovido.filho_direito = -1;

    if (rrn_atual == -1) {
        // Chegou na folha e não achou a chave; vai inserir na árvore
        strcpy(promovido.chave_promovida, chave);
        promovido.filho_direito = -1;
        return promovido;
    }

    // Carrega a página atual em um btree_node
    btree_node no_atual = btree_read(rrn_atual, t);

    // Verifica se a página atual contém a chave da busca
    int indice;
    bool chave_encontrada = btree_binary_search(&indice, false, chave, &no_atual, t);

    if (indice < (btree_order - 1) && chave_encontrada) {
        // Chave já existe na árvore
        printf(ERRO_PK_REPETIDA, chave);
        btree_node_free(no_atual);
        return promovido;
    }

    // Insere recursivamente
    promovido_aux promovido_filho = btree_insert_aux(chave, no_atual.filhos[indice], t);

    if (promovido_filho.chave_promovida[0] != '\0') {
        // Verifica se houve overflow na página
        if (no_atual.qtd_chaves < btree_order - 1) {
            // Não houve overflow
            if (indice < no_atual.qtd_chaves) {
                // Move todas as chaves e seus filhos para a direita
                for (int i = no_atual.qtd_chaves; i > indice; i--) {
                    no_atual.chaves[i] = no_atual.chaves[i - 1];
                    no_atual.filhos[i + 1] = no_atual.filhos[i];
                }
            }
            // Insere na posição do índice
            no_atual.chaves[indice] = strdup(promovido_filho.chave_promovida);
            no_atual.filhos[indice + 1] = promovido_filho.filho_direito;
            no_atual.qtd_chaves++;
            // Escreve a chave
            btree_write(no_atual, t);
            btree_node_free(no_atual);
        } else {
            // Houve overflow, retorna a chave promovida na divisão
            promovido = btree_divide(promovido_filho, &no_atual, indice, t);
            btree_write(no_atual, t);
            btree_node_free(no_atual);
        }
    }

    return promovido;
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
    btree_node novo_no = btree_node_malloc(t);
    novo_no.this_rrn = t->qtd_nos++;
    novo_no.qtd_chaves = 0;
    novo_no.folha = node->folha;

    int meio = btree_order / 2;

    // Durante a divisão, a nova chave pode ser inserida na página antiga ou na nova página
    if (i <= meio) {
        // Inserção na página antiga
        for (int j = meio; j < btree_order - 1; j++) {
            novo_no.chaves[novo_no.qtd_chaves] = node->chaves[j];
            novo_no.filhos[novo_no.qtd_chaves + 1] = node->filhos[j + 1];
            novo_no.qtd_chaves++;
            node->chaves[j] = strdup("#");
            node->filhos[j + 1] = -1;
        }

        for (int j = novo_no.qtd_chaves; j < btree_order - 1; j++) {
            novo_no.chaves[j] = strdup("#");
            novo_no.filhos[j + 1] = -1;
        }

        for (int j = btree_order - 2; j > i; j--) {
            node->chaves[j] = node->chaves[j - 1];
            node->filhos[j + 1] = node->filhos[j];
        }

        node->chaves[i] = strdup(promo.chave_promovida);
        node->filhos[i + 1] = promo.filho_direito;
        node->qtd_chaves++;
    } else {
        // Inserção na página nova
        for (int j = meio + 1; j < btree_order - 1; j++) {
            novo_no.chaves[novo_no.qtd_chaves] = node->chaves[j];
            novo_no.filhos[novo_no.qtd_chaves + 1] = node->filhos[j + 1];
            novo_no.qtd_chaves++;
            node->chaves[j] = strdup("#");
            node->filhos[j + 1] = -1;
        }

        for (int j = novo_no.qtd_chaves; j < btree_order - 1; j++) {
            novo_no.chaves[j] = strdup("#");
            novo_no.filhos[j + 1] = -1;
        }

        for (int j = novo_no.qtd_chaves; j > i - meio - 1; j--) {
            novo_no.chaves[j] = novo_no.chaves[j - 1];
            novo_no.filhos[j + 1] = novo_no.filhos[j];
        }

        novo_no.chaves[i - meio - 1] = strdup(promo.chave_promovida);
        novo_no.filhos[i - meio] = promo.filho_direito;
        novo_no.qtd_chaves++;
    }

    // Cria um promovido_aux para promover uma chave para ser pai desses dois nós
    strcpy(p.chave_promovida, node->chaves[meio]);
    p.filho_direito = novo_no.this_rrn;

    novo_no.filhos[0] = node->filhos[meio + 1];
    node->chaves[meio] = strdup("#");
    node->filhos[meio + 1] = -1;
    node->qtd_chaves--;

    novo_no.folha = (novo_no.filhos[0] == -1);

    btree_write(novo_no, t);
    btree_node_free(novo_no);

    btree_write(*node, t);
    btree_node_free(*node);

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


bool btree_delete_aux(char *chave, int rrn, btree *t) { // Triste essa função
    if (rrn == -1) {
        return false; // Nó inválido
    }
    // Criando um nó para ler a página atual
    btree_node no = btree_read(rrn, t);
    // Verificando se a chave está na página atual
    int result;
    bool found = btree_binary_search(&result, false, chave, &no, t);
    if (found && strcmp(no.chaves[result], chave) == 0) {
        // A chave está na página
        if (!no.folha) {
            // Não é uma folha
            btree_node filho_esquerdo = btree_read(no.filhos[result], t);
            // Copia a última chave do filho esquerdo para a página atual
            strcpy(no.chaves[result], filho_esquerdo.chaves[filho_esquerdo.qtd_chaves - 1]);
            btree_write(no, t);

            // Verificando se houve underflow no filho esquerdo
            bool underflow = btree_delete_aux(filho_esquerdo.chaves[filho_esquerdo.qtd_chaves - 1], no.filhos[result], t);
            btree_node_free(filho_esquerdo);
            if (underflow) {
                btree_node_free(no);
                return btree_borrow_or_merge(&no, result, t);
            }
        } else {
            // É uma folha:
            if (result < no.qtd_chaves - 1) {
                // Move todas as chaves a partir do índice para a esquerda
                for (int i = result; i < no.qtd_chaves - 1; i++) {
                    strcpy(no.chaves[i], no.chaves[i + 1]);
                }
            }
            // Preenchendo a última posição com uma string vazia com #
            memset(no.chaves[no.qtd_chaves - 1], '#', t->tam_chave);
            no.qtd_chaves--;
            btree_write(no, t);

            // Verificando se houve underflow na página atual
            bool underflow = no.qtd_chaves < (btree_order - 1) / 2;
            btree_node_free(no);
            return underflow;
        }
    } else {
        // A Chave não foi encontrada na página atual
        bool underflow = btree_delete_aux(chave, no.filhos[result], t);
        btree_node_free(no);
        if (underflow) {
            return btree_borrow_or_merge(&no, result, t);
        }
    }
    return false; // Não houve underflo
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

// Por favor, funcione de primeira, amém!
bool btree_borrow_or_merge(btree_node *no, int i, btree *t) {
    int min_chaves = (btree_order - 1) / 2;

    // Verificando se é possível ter um irmão à direita
    if (i + 1 < no->qtd_chaves + 1) {
        int rrn_irmao_direito = no->filhos[i + 1];
        if (rrn_irmao_direito != -1) {
            btree_node irmao_direito = btree_read(rrn_irmao_direito, t);
            if (irmao_direito.qtd_chaves > min_chaves) {
                // Empresta do irmão à direita
                // Desce a chave do pai e sobe a chave do irmão
                strcpy(no->chaves[i], irmao_direito.chaves[0]);
                for (int j = 0; j < irmao_direito.qtd_chaves - 1; j++) {
                    strcpy(irmao_direito.chaves[j], irmao_direito.chaves[j + 1]);
                }
                memset(irmao_direito.chaves[irmao_direito.qtd_chaves - 1], '#', t->tam_chave);
                irmao_direito.qtd_chaves--;

                btree_write(*no, t);
                btree_write(irmao_direito, t);
                btree_node_free(irmao_direito);
                return false; // Não houve underflow
            }
            btree_node_free(irmao_direito);
        }
    }

    // Verificando se é possível ter um irmão à esquerda
    if (i - 1 >= 0) {
        int rrn_irmao_esquerdo = no->filhos[i - 1];
        if (rrn_irmao_esquerdo != -1) {
            btree_node irmao_esquerdo = btree_read(rrn_irmao_esquerdo, t);
            if (irmao_esquerdo.qtd_chaves > min_chaves) {
                // Empresta do irmão à esquerda
                // Desce a chave do pai e sobe a chave do irmão
                for (int j = no->qtd_chaves; j > 0; j--) {
                    strcpy(no->chaves[j], no->chaves[j - 1]);
                }
                strcpy(no->chaves[0], irmao_esquerdo.chaves[irmao_esquerdo.qtd_chaves - 1]);
                memset(irmao_esquerdo.chaves[irmao_esquerdo.qtd_chaves - 1], '#', t->tam_chave);
                irmao_esquerdo.qtd_chaves--;

                btree_write(*no, t);
                btree_write(irmao_esquerdo, t);
                btree_node_free(irmao_esquerdo);
                return false; // Não houve underflow
            }
            btree_node_free(irmao_esquerdo);
        }
    }

    // Verificando se é possível ter um irmão à direita (não foi possível emprestar)
    if (i + 1 < no->qtd_chaves + 1) {
        int rrn_irmao_direito = no->filhos[i + 1];
        if (rrn_irmao_direito != -1) {
            btree_node irmao_direito = btree_read(rrn_irmao_direito, t);
            if (irmao_direito.qtd_chaves <= min_chaves) {
                // Realiza fusão com o irmão à direita
                strcpy(no->chaves[no->qtd_chaves], irmao_direito.chaves[0]);
                for (int j = 1; j < irmao_direito.qtd_chaves; j++) {
                    strcpy(no->chaves[no->qtd_chaves + j], irmao_direito.chaves[j]);
                }
                no->qtd_chaves += irmao_direito.qtd_chaves;

                btree_write(*no, t);
                btree_node_free(irmao_direito);
                return true; // Houve underflow
            }
            btree_node_free(irmao_direito);
        }
    }

    // Verificando se é possível ter um irmão à esquerda (não foi possível emprestar)
    if (i - 1 >= 0) {
        int rrn_irmao_esquerdo = no->filhos[i - 1];
        if (rrn_irmao_esquerdo != -1) {
            btree_node irmao_esquerdo = btree_read(rrn_irmao_esquerdo, t);
            if (irmao_esquerdo.qtd_chaves <= min_chaves) {
                // Realiza fusão com o irmão à esquerda
                for (int j = 0; j < no->qtd_chaves; j++) {
                    strcpy(irmao_esquerdo.chaves[irmao_esquerdo.qtd_chaves + j], no->chaves[j]);
                }
                irmao_esquerdo.qtd_chaves += no->qtd_chaves;

                btree_write(irmao_esquerdo, t);
                btree_node_free(irmao_esquerdo);
                return true; // Houve underflow
            }
            btree_node_free(irmao_esquerdo);
        }
    }

    return false; // Não houve underflow
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
    // Se chegou ao fim da árvore (chegou em uma folha)
    if (rrn == -1) {
        if (exibir_caminho) {
            printf("\n");
        }
        return false; // Chave não encontrada
    }

    // Se exibir_caminho (caminhando pela árvore)
    if (exibir_caminho) {
        printf(" %d", rrn);
    }

    // Cria um nó e lê a página (btree_read())
    btree_node no = btree_read(rrn, t);

    // Faz uma busca binária no nó para procurar a chave ('btree_binary_search()')
    int indice;
    bool chave_encontrada = btree_binary_search(&indice, exibir_caminho, chave, &no, t);

    // Se a chave for encontrada (busca binária retorna 'true')
    if (chave_encontrada) {
        if (result != NULL) {
            strcpy(result, no.chaves[indice]); // Copia a chave usando o índice recuperado na busca binária
        }
        if (exibir_caminho) {
            printf("\n");
        }
        btree_node_free(no); // Desaloca o nó da memória
        return true; // Chave encontrada
    } else {
        // Retorna btree_search() (recursão)
        bool f = btree_search(result, exibir_caminho, chave, no.filhos[indice], t);
        btree_node_free(no); // Desaloca o nó da memória
        return f;
    }
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
    int esq = 0, dir = node->qtd_chaves - 1, meio;
    bool chave_encontrada = false;

    if (exibir_caminho) {
        printf("(");
    }

    while (esq <= dir) {
        meio = (esq + dir) / 2;
        int cmp = t->compar(chave, node->chaves[meio]);

        if (exibir_caminho) {
            printf(" %d", meio);
        }

        if (cmp == 0) {
            *result = meio;
            chave_encontrada = true;
            break;
        } else if (cmp < 0) {
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }

    if (exibir_caminho) {
        printf(" )\n");
    }

    if (chave_encontrada) {
        return true;
    } else {
        *result = esq;
        return false;
    }
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
    if (rrn == -1) return false; // Se chegou no fim de um ramo

    btree_node no = btree_read(rrn, t); // Lê a página
    bool found = false;

    // Chama recursivamente btree_print_in_order() no filho [0] do nó
    if (!no.folha) {
        found |= btree_print_in_order(chave_inicio, chave_fim, exibir, no.filhos[0], t);
    }

    // Loop para imprimir todas as chaves da página atual
    for (int i = 0; i < no.qtd_chaves; ++i) {
        // Verifica se 'chave_inicio' e 'chave_fim' são 'NULL'
        if ((chave_inicio == NULL || t->compar(no.chaves[i], chave_inicio) >= 0) &&
            (chave_fim == NULL || t->compar(no.chaves[i], chave_fim) <= 0)) {
            found |= exibir(no.chaves[i]); // Usa 'exibir()' para mostrar a chave
        }

        // Chama recursivamente btree_print_in_order() no filho da direita (i+1)
        if (!no.folha) {
            found |= btree_print_in_order(chave_inicio, chave_fim, exibir, no.filhos[i + 1], t);
        }
    }

    btree_node_free(no); // Desaloca o nó da memória

    return found; // Retorna true se ao menos uma chave foi impressa
}


/**
 * Função interna para ler um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser lido da Árvore-B.
 * @param t Árvore-B na qual será feita a leitura do nó.
 */
btree_node btree_read(int rrn, btree *t) {
    // Calcula o tamanho do registro
    int tamanho_registro = btree_register_size(t);

    // Aloca espaço para um vetor temporário
    char temp[tamanho_registro + 1];

    // Calcula o offset no arquivo de índice
    long offset = rrn * tamanho_registro;

    // Move o ponteiro do arquivo para o offset calculado
    fseek(t->arquivo, offset, SEEK_SET);

    // Lê os dados do arquivo para o vetor temporário
    fread(temp, sizeof(char), tamanho_registro, t->arquivo);
    temp[tamanho_registro] = '\0'; // Fecha a string com '\0'

    // Aloca espaço para um novo nó
    btree_node no = btree_node_malloc(t);
    no.this_rrn = rrn;

    // Atualiza os dados do nó
    // 'qtd_chaves' está nos 3 primeiros caracteres do vetor temporário
    char qtd_chaves_str[4];
    strncpy(qtd_chaves_str, temp, 3);
    qtd_chaves_str[3] = '\0';
    no.qtd_chaves = atoi(qtd_chaves_str);

    // Recupera as chaves
    int indice = 3;
    for (int i = 0; i < btree_order - 1; i++) {
        no.chaves[i] = malloc(t->tam_chave + 1);
        strncpy(no.chaves[i], temp + indice, t->tam_chave);
        no.chaves[i][t->tam_chave] = '\0'; // Adiciona o terminador nulo
        indice += t->tam_chave;
    }

    // Verifica se é folha
    no.folha = (temp[indice] == '1');
    indice++;

    // Recupera todos os filhos das chaves
    for (int i = 0; i < btree_order; i++) {
        if (temp[indice] == '*') {
            no.filhos[i] = -1;
        } else {
            char filho_str[4];
            strncpy(filho_str, temp + indice, 3);
            filho_str[3] = '\0';
            no.filhos[i] = atoi(filho_str);
        }
        indice += 3;
    }

    return no;
}



/**
 * Função interna para escrever um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser escrito na Árvore-B.
 * @param t Árvore-B na qual será feita a escrita do nó.
 */
void btree_write(btree_node no, btree *t) {
    // Calcula o tamanho do registro
    int tamanho_registro = btree_register_size(t);

    // Cria um vetor temporário para armazenar o registro
    char temp[tamanho_registro + 1];
    int indice = 0;

    // Copia a quantidade de chaves (int, 3 bytes)
    sprintf(temp + indice, "%03d", no.qtd_chaves);
    indice += 3;

    // Loop para recuperar as chaves (0 a 'btree_order-1')
    for (int i = 0; i < btree_order - 1; i++) {
        strncpy(temp + indice, no.chaves[i], t->tam_chave);
        indice += t->tam_chave;
    }

    // Indica se a página (nó) é uma folha
    temp[indice] = no.folha ? 'T' : 'F';
    indice++;

    // Loop para recuperar os filhos
    for (int i = 0; i < btree_order; i++) {
        if (no.filhos[i] == -1) {
            strncpy(temp + indice, "***", 3);
        } else {
            sprintf(temp + indice, "%03d", no.filhos[i]);
        }
        indice += 3;
    }

    // Copia o registro no arquivo da árvore
    long offset = no.this_rrn * tamanho_registro;
    fseek(t->arquivo, offset, SEEK_SET);
    fwrite(temp, sizeof(char), tamanho_registro, t->arquivo);
}


/**
 * Função interna para alocar o espaço necessário dos campos chaves (vetor de strings) e filhos (vetor de inteiros) da struct btree_node.<br />
 *
 * @param t Árvore-B base para o qual será alocado um struct btree_node.
 */
btree_node btree_node_malloc(btree *t) {
	btree_node no;

	no.this_rrn = t->qtd_nos;

	no.qtd_chaves = 0;

	char *aux = malloc (sizeof (char) * (btree_order-1) * (t->tam_chave)); //vetor contíguo para permitir uso de algumas funções da stdlib
	memset (aux, 0, (btree_order-1) * (t->tam_chave));
	no.chaves = malloc (sizeof (void*) * (btree_order-1));
	for (int i = 0; i < btree_order-1; i++) {
		no.chaves[i] = (aux + i * (t->tam_chave));
	}

	no.folha = true;
	no.filhos = malloc (sizeof(int) * btree_order);
	memset (no.filhos, -1, sizeof(int) * btree_order);

	return no;
}


/**
 * Função interna para liberar o espaço alocado pelo btree_node_malloc.<br />
 *
 * @param no Nó para o qual o espaço alocado deverá ser librerado;
 */
void btree_node_free (btree_node no) {
	if (*no.chaves)
		free (*no.chaves);
	if (no.chaves)
		free (no.chaves);
	if (no.filhos)
		free (no.filhos);
}


/**
 * Função interna para calcular o tamanho em bytes de uma Árvore-B.<br />
 *
 * @param t Árvore-B base para o qual será calculado o tamanho.
 */
int btree_register_size(btree *t) {
    int chaves_ordenadas = (btree_order - 1) * t->tam_chave;
    return 3 + chaves_ordenadas + 1 + (btree_order * 3);
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
