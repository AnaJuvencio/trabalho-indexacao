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
    preco_kit_index *kit_a = (preco_kit_index *)a;
    preco_kit_index *kit_b = (preco_kit_index *)b;

    // Comparação dos preços
    int cmp = (kit_a->preco > kit_b->preco) - (kit_a->preco < kit_b->preco);
    if (cmp != 0) {
        return cmp;
    }

    // Caso o preço seja igual, compararemos os IDs
    return strcmp(kit_a->id_kit, kit_b->id_kit);
}



/* Função usada na comparação entre as chaves do índice data_idx */
int qsort_data_idx(const void *a, const void *b) {
    data_index *data_a = (data_index *)a;
    data_index *data_b = (data_index *)b;

    // Comparação pela data
    int cmp = strcmp(data_a->inicio, data_b->inicio);
    if (cmp != 0)
        return cmp;

    // Comparação pelo ID da partida (desempate)
    return strcmp(data_a->id_partida, data_b->id_partida);
}


/* Função de comparação entre vitórias, eliminacoes e tempo de sobrevivencia dos jogadores
 * Usada na função recompensar_vencedores_periodo; */
int qsort_info_jogador(const void *a, const void *b) {

    Info_Jogador *jogador_a = (Info_Jogador *)a;
    Info_Jogador *jogador_b = (Info_Jogador *)b;
    // Comparando as vitorias
    if (jogador_a->vitorias > jogador_b->vitorias) {
        return -1;
    } else if (jogador_a->vitorias < jogador_b->vitorias) {
        return 1;
    }
    // Comparando as eliminações
    if (jogador_a->eliminacoes > jogador_b->eliminacoes) {
        return -1;
    } else if (jogador_a->eliminacoes < jogador_b->eliminacoes) {
        return 1;
    }
    // Comparando o tempo de sobrevivência
    int cmp_sobrevivencia = strcmp(jogador_a->sobrevivencia, jogador_b->sobrevivencia);
    if (cmp_sobrevivencia > 0) {
        return -1;
    } else if (cmp_sobrevivencia < 0) {
        return 1;
    }
    // Comparando o Id do jogador
    return strcmp(jogador_a->id_jogador, jogador_b->id_jogador);
}


/* Função de comparação entre chaves do índice secundário de jogador_kits_secundario_idx */
int qsort_jogador_kits_secundario_idx(const void *a, const void *b) {
    jogador_kits_secundario_index *ia = (jogador_kits_secundario_index *)a;
    jogador_kits_secundario_index *ib = (jogador_kits_secundario_index *)b;
    return strcmp(ia->chave_secundaria, ib->chave_secundaria);
}


/* Função de comparação entre chaves do índice secundário de jogador_kits_primario_idx */
int qsort_inverted_list_primary_search(const void *a, const void *b) {
    jogador_kits_primario_index *ia = (jogador_kits_primario_index *)a;
    jogador_kits_primario_index *ib = (jogador_kits_primario_index *)b;
    return strcmp(ia->chave_primaria, ib->chave_primaria);
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

    if (!kits_idx) { // Verificando falha na alocação
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
    // Preenchendo o índice percorrendo os registros no arquivo
    for (unsigned i = 0; i < qtd_registros_kits; ++i) {
        Kit k = recuperar_registro_kit(i); // Recupera o kit do arquivo

        // Preenchendo o índice com os dados do kit
        strncpy(kits_idx[i].id_kit, k.id_kit, TAM_ID_KIT - 1);
        kits_idx[i].id_kit[TAM_ID_KIT - 1] = '\0'; // Garantindo terminação nula
        kits_idx[i].rrn = i;
    }
    // Ordenando o índice pelo campo id_kit
    qsort(kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx);
    printf(INDICE_CRIADO, "kits_idx");
}




void criar_partidas_idx() {
    if (!partidas_idx)
        partidas_idx = malloc(MAX_REGISTROS * sizeof(partidas_index));

    if (!partidas_idx) { // Verifica falha na alocação
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
    // Inicializando o índice percorrendo todos os registros
    for (unsigned i = 0; i < qtd_registros_partidas; ++i) {
        Partida p = recuperar_registro_partida(i); // Recupera o registro de partida pelo RRN
        // Preenchendo o índice
        strncpy(partidas_idx[i].id_partida, p.id_partida, TAM_ID_PARTIDA - 1);
        partidas_idx[i].id_partida[TAM_ID_PARTIDA - 1] = '\0'; // Garante terminação nula
        partidas_idx[i].rrn = i;
    }
    // Ordenando o índice pelo campo id_partida
    qsort(partidas_idx, qtd_registros_partidas, sizeof(partidas_index), qsort_partidas_idx);
    printf(INDICE_CRIADO, "partidas_idx");
}



void criar_resultados_idx() {
    if (!resultados_idx)
        resultados_idx = malloc(MAX_REGISTROS * sizeof(resultados_index));

    if (!resultados_idx) { // Verificando falha na alocação
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
    // Inicializando o índice percorrendo todos os registros
    for (unsigned i = 0; i < qtd_registros_resultados; ++i) {
        Resultado r = recuperar_registro_resultado(i); // Recupera o registro de resultado pelo RRN

        // Preenchendo o índice diretamente
        strncpy(resultados_idx[i].id_jogador, r.id_jogador, TAM_ID_JOGADOR - 1);
        resultados_idx[i].id_jogador[TAM_ID_JOGADOR - 1] = '\0'; // Garante terminação nula

        strncpy(resultados_idx[i].id_partida, r.id_partida, TAM_ID_PARTIDA - 1);
        resultados_idx[i].id_partida[TAM_ID_PARTIDA - 1] = '\0'; // Garante terminação nula

        resultados_idx[i].rrn = i;
    }
    // Ordenando o índice primeiro por id_jogador e depois por id_partida
    qsort(resultados_idx, qtd_registros_resultados, sizeof(resultados_index), qsort_resultados_idx);
    printf(INDICE_CRIADO, "resultados_idx");
}




void criar_preco_kit_idx() {
    if (!preco_kit_idx) // Verificamos se já existe, caso contrário, alocamos
        preco_kit_idx = malloc(MAX_REGISTROS * sizeof(preco_kit_index));

    if (!preco_kit_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }
    // Preenchendo o índice com os dados
    for (unsigned i = 0; i < qtd_registros_kits; ++i) {
        Kit k = recuperar_registro_kit(i); // Recuperando o kit
        strcpy(preco_kit_idx[i].id_kit, k.id_kit);
        preco_kit_idx[i].preco = k.preco; // Armazenando o preço do kit
    }
    // Ordenando o índice pelo id_kit
    qsort(preco_kit_idx, qtd_registros_kits, sizeof(preco_kit_index), qsort_preco_kit_idx);
    printf(INDICE_CRIADO, "preco_kit_idx");
}



void criar_data_idx() {
    if (!data_idx) // Verificando se já existe
        data_idx = malloc(MAX_REGISTROS * sizeof(data_index));

    if (!data_idx) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    // Preenchendo o índice com os dados
    for (unsigned i = 0; i < qtd_registros_partidas; ++i) {
        Partida p = recuperar_registro_partida(i); // Recupera a partida
        strcpy(data_idx[i].id_partida, p.id_partida);
        strcpy(data_idx[i].inicio, p.inicio); // Armazena a data da partida
    }
    // Ordenando o índice pelo Id da partida
    qsort(data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx);
    printf(INDICE_CRIADO, "data_idx");
}

void criar_jogador_kits_idx() {
    // Verificando e alocando memória para os índices primário e secundário
    if ((!jogador_kits_idx.jogador_kits_primario_idx && !(jogador_kits_idx.jogador_kits_primario_idx = malloc(MAX_REGISTROS * sizeof(jogador_kits_primario_index)))) ||
        (!jogador_kits_idx.jogador_kits_secundario_idx && !(jogador_kits_idx.jogador_kits_secundario_idx = malloc(MAX_REGISTROS * 10 * sizeof(jogador_kits_secundario_index))))) {
        printf(ERRO_MEMORIA_INSUFICIENTE);
        exit(1);
    }

    // Percorrendo os registros de jogadores
    for (unsigned i = 0; i < qtd_registros_jogadores; ++i) {
        Jogador jogador = recuperar_registro_jogador(i);
        // Inserindo cada kit válido na lista invertida
        for (unsigned j = 0; j < 10 && jogador.kits[j][0] != '\0'; ++j) {
            char kit_maiusculo[TAM_MAX_NOME_KIT];
            strupr(strcpy(kit_maiusculo, jogador.kits[j]));
            
            // Inserção do kit no índice
            inverted_list_insert(kit_maiusculo, jogador.id_jogador, &jogador_kits_idx);
        }
    }
    // Ordenando o índice secundário
    qsort(jogador_kits_idx.jogador_kits_secundario_idx, jogador_kits_idx.qtd_registros_secundario, sizeof(jogador_kits_secundario_index), jogador_kits_idx.compar);
    // Mensagem de sucesso
    printf(INDICE_CRIADO, "jogador_kits_idx");
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
    char data[TAM_REGISTRO_PARTIDA + 1], *token;
    // Copiando o registro do arquivo com base no RRN
    strncpy(data, ARQUIVO_PARTIDAS + (rrn * TAM_REGISTRO_PARTIDA), TAM_REGISTRO_PARTIDA);
    data[TAM_REGISTRO_PARTIDA] = '\0'; // Garante terminação nula
    // Dividndo os dados do registro da partida usando o delimitador ;
    token = strtok(data, ";");
    strcpy(p.id_partida, token);  
    token = strtok(NULL, ";");
    strcpy(p.inicio, token);  
    token = strtok(NULL, ";");
    strcpy(p.duracao, token);  
    token = strtok(NULL, ";");
    strcpy(p.cenario, token);  
    token = strtok(NULL, ";");
    strcpy(p.id_jogadores, token);  // Ids dos jogadores separados por "|"
    return p;
}



Resultado recuperar_registro_resultado(int rrn) {

    Resultado r;
    char data[TAM_REGISTRO_RESULTADO + 1], *p;
    // Copiando os dados do registro de resultado do arquivo para a variável data
    strncpy(data, ARQUIVO_RESULTADOS + (rrn * TAM_REGISTRO_RESULTADO), TAM_REGISTRO_RESULTADO);
    data[TAM_REGISTRO_RESULTADO] = '\0'; // Garante terminação nula
    // Dividindo os dados do registro do resultado usando o delimitador ;
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



/* Escrevendo em seu arquivo na posição informada RRN */
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
    strcat(data, ";");
    strcat(data, p.inicio);
    strcat(data, ";");
    strcat(data, p.duracao);
    strcat(data, ";");
    strcat(data, p.cenario);
    strcat(data, ";");
    strcat(data, p.id_jogadores);
    strcat(data, ";");
    // Preenchendo o restante com padding até TAM_REGISTRO_PARTIDA
    strpadright(data, '#', TAM_REGISTRO_PARTIDA);
    // Escrevendo no arquivo na posição certa
    strncpy(ARQUIVO_PARTIDAS + rrn * TAM_REGISTRO_PARTIDA, data, TAM_REGISTRO_PARTIDA);
}


void escrever_registro_resultado(Resultado jp, int rrn) {
    char data[TAM_REGISTRO_RESULTADO + 1], number[50];
    data[0] = '\0';
    number[0] = '\0';
    // Concatenando os campos na string data
    strcat(data, jp.id_jogador);
    strcat(data, ";");
    strcat(data, jp.id_partida);
    strcat(data, ";");
    strcat(data, jp.id_kit);
    strcat(data, ";");
    // Formatando a colocação como string de 4 bytes
    sprintf(number, "%04d", jp.colocacao);
    strcat(data, number);
    strcat(data, ";");
    strcat(data, jp.sobrevivencia);
    strcat(data, ";");
    // Formatanso as eliminações como string de 4 bytes
    sprintf(number, "%04d", jp.eliminacoes);
    strcat(data, number);
    strcat(data, ";");
    // Preenchendo o restante com padding até TAM_REGISTRO
    strpadright(data, '#', TAM_REGISTRO_RESULTADO);
    // Escrevendo no arquivo na posição adequada
    strncpy(ARQUIVO_RESULTADOS + rrn * TAM_REGISTRO_RESULTADO, data, TAM_REGISTRO_RESULTADO);
}



/* Exibindo um registro com base no RRN */
bool exibir_jogador(int rrn) {
	if (rrn < 0)
		return false;

	Jogador j = recuperar_registro_jogador(rrn);
	printf ("%s, %s, %s, %s, %.2lf\n", j.id_jogador, j.apelido, j.cadastro, j.premio, j.saldo);
	return true;
}


bool exibir_kit(int rrn) {
    if (rrn < 0)
        return false;
    Kit k = recuperar_registro_kit(rrn);
    printf("%s, %s, %s, %.2lf\n", k.id_kit, k.nome, k.poder, k.preco);
    return true;
}


bool exibir_partida(int rrn) {
    if (rrn < 0)
        return false;
    Partida p = recuperar_registro_partida(rrn);
    printf("%s, %s, %s, %s, %s\n", p.id_partida, p.inicio, p.duracao, p.cenario, p.id_jogadores);
    return true;
}



/* Funções principais */
void cadastrar_jogador_menu(char *id_jogador, char *apelido) {

    // Verificando se o Id está no sistema
    int indice = busca_binaria_com_reps(id_jogador, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0, 0);
    if (indice != -1) {
        printf(ERRO_PK_REPETIDA, id_jogador);
        return;
    }
    // Criando um novo jogador e preenchendo os dados de acorod com o documento do prof
    Jogador novo_jogador;
    strcpy(novo_jogador.id_jogador, id_jogador);
    strcpy(novo_jogador.apelido, apelido);
    current_datetime(novo_jogador.cadastro);
    strcpy(novo_jogador.premio, "000000000000"); // Formatação igual do doc
    novo_jogador.saldo = 0.0;
    for (int i = 0; i < QTD_MAX_KITS; i++) {
        novo_jogador.kits[i][0] = '\0';
    }
    // Escrevendo o novo registro do jogador
    escrever_registro_jogador(novo_jogador, qtd_registros_jogadores);
    // Adicionando o novo jogador no índice e ordenando
    strcpy(jogadores_idx[qtd_registros_jogadores].id_jogador, id_jogador);
    jogadores_idx[qtd_registros_jogadores].rrn = qtd_registros_jogadores;
    qtd_registros_jogadores++;
    qsort(jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx);
    printf(SUCESSO); // Exibindo mensagem de sucesso
}


void remover_jogador_menu(char *id_jogador) {
    // Verificando se o Id está no sistema
    int indice = busca_binaria_com_reps(id_jogador, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0, 0);
    if (indice == -1) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }
    // Recuperando o jogador com o RRN recuperado na busca binária
    Jogador jogador = recuperar_registro_jogador(jogadores_idx[indice].rrn);
    memcpy(jogador.id_jogador, "*|", 2); // Marcando o jogador como removido
    // Escrevendo o registro do jogador
    escrever_registro_jogador(jogador, jogadores_idx[indice].rrn);
    // Marcando o RRN com -1
    jogadores_idx[indice].rrn = -1;
    printf(SUCESSO); // Exibindo mensagem de sucesso
}


void adicionar_saldo_menu(char *id_jogador, double valor) {
	adicionar_saldo(id_jogador, valor, true);
}


void adicionar_saldo(char *id_jogador, double valor, bool flag) {

    // Verificando se o Id está no sistema
    int indice = busca_binaria_com_reps(id_jogador, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0, 0);
    if (indice == -1) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }
    // Verificandi se o valor e valido
    if (valor <= 0) {
        printf(ERRO_VALOR_INVALIDO);
        return;
    }
    // Recuperando o jogador com o RRN recuperado na busca binaria
    Jogador jogador = recuperar_registro_jogador(jogadores_idx[indice].rrn);
    // Adicionando o saldo
    jogador.saldo += valor;
    // Escrevendo o registro do jogador
    escrever_registro_jogador(jogador, jogadores_idx[indice].rrn);
    // Exibindo mensagem de sucesso se a flag for true
    if (flag) {
        printf(SUCESSO);
    }
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
    // Adicionando o novo kit no índice e ordenando
    strcpy(kits_idx[qtd_registros_kits].id_kit, novo_kit.id_kit);
    kits_idx[qtd_registros_kits].rrn = qtd_registros_kits;
    qtd_registros_kits++;
    qsort(kits_idx, qtd_registros_kits, sizeof(kits_index), qsort_kits_idx);
    printf(SUCESSO); // Exibindo a mensagem de sucesso
}


void comprar_kit_menu(char *id_jogador, char *id_kit) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "comprar_kit_menu()");
}


void executar_partida_menu(char *inicio, char *duracao, char *cenario, char *id_jogadores, char *kits_jogadores, char *duracoes_jogadores, char *eliminacoes_jogadores) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "executar_partida_menu()");
}


void recompensar_vencedores_menu(char *data_inicio, char *data_fim, double premio) {

    Info_Jogador info_jogadores[MAX_REGISTROS] = {0};
    int qtd_jogadores = 0;
    // Recuperando o RRN da primeira data que e igual ou maior que a data de início
    int rrn_inicio = busca_binaria_com_reps(data_inicio, data_idx, qtd_registros_partidas, sizeof(data_index), qsort_data_idx, false, 0, 1);
    for (int i = rrn_inicio; i < qtd_registros_partidas; i++) {
        Partida partida = recuperar_registro_partida(partidas_idx[i].rrn);
        // Verificando se a data está dentro do intervalo
        if (strcmp(partida.inicio, data_fim) > 0) {
            break;
        }
        // Recuperando as informações de cada jogador dentro da partida
        char *token = strtok(partida.id_jogadores, "|");
        while (token != NULL) {
            // Recuperando o RRN do resultado
            int rrn_resultado = busca_binaria_com_reps(token, resultados_idx, qtd_registros_resultados, sizeof(resultados_index), qsort_resultados_idx, false, 0, 0);
            Resultado resultado = recuperar_registro_resultado(resultados_idx[rrn_resultado].rrn);
            // Verificando se o jogador ja está na lista
            int j;
            for (j = 0; j < qtd_jogadores; j++) {
                if (strcmp(info_jogadores[j].id_jogador, resultado.id_jogador) == 0) {
                    break;
                }
            }
            if (j == qtd_jogadores) { // Se não estive rna lista
                strcpy(info_jogadores[qtd_jogadores].id_jogador, resultado.id_jogador);
                qtd_jogadores++;
            }
            // Atualizando as infos do jogador
            info_jogadores[j].vitorias += (resultado.colocacao == 1) ? 1 : 0;
            info_jogadores[j].eliminacoes += resultado.eliminacoes;
            // Atualizando o tempo de sobrevivência - string
            int tempo_sobrevivencia = atoi(info_jogadores[j].sobrevivencia) + atoi(resultado.sobrevivencia);
            sprintf(info_jogadores[j].sobrevivencia, "%08d", tempo_sobrevivencia);
            token = strtok(NULL, "|");
        }
    }
    // Ordenando o vetor info_Jogadores
    qsort(info_jogadores, qtd_jogadores, sizeof(Info_Jogador), qsort_info_jogador);
    // Recuperando o jogador pelo Id usando busca binária
    int indice = busca_binaria_com_reps(info_jogadores[0].id_jogador, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, false, 0, 0);
    if (indice == -1 || jogadores_idx[indice].rrn == -1) {
        printf(ERRO_JOGADOR_REMOVIDO, premio, info_jogadores[0].id_jogador, info_jogadores[0].vitorias, info_jogadores[0].eliminacoes);
    } else {
        adicionar_saldo(info_jogadores[0].id_jogador, premio, false);
        Jogador jogador = recuperar_registro_jogador(jogadores_idx[indice].rrn);
        printf(CONCEDER_PREMIO, jogador.apelido, info_jogadores[0].vitorias, info_jogadores[0].eliminacoes, premio);
    }
}


/* Busca */
void buscar_jogador_id_menu(char *id_jogador) {
	jogadores_index index;
	strcpy(index.id_jogador, id_jogador);
	int bb = busca_binaria((void*)&index, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, true, 0);
	if (bb == -1)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_jogador(jogadores_idx[bb].rrn);
}


void buscar_kit_id_menu(char *id_kit) {
    kits_index index;
    strcpy(index.id_kit, id_kit);
    // Busca binária no índice de kits
    int bb = busca_binaria((void*)&index, kits_idx, qtd_registros_kits, sizeof(kits_index),qsort_kits_idx, true, 0);
    // Verificando o resultado da busca
    if (bb == -1)
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    else
        exibir_kit(kits_idx[bb].rrn);  // Exibe o kit encontrado
}



void buscar_partida_id_menu(char *id_partida) {
    partidas_index index;
    strcpy(index.id_partida, id_partida);
    // Busca binária no índice primário de partidas
    int bb = busca_binaria((void*)&index, partidas_idx, qtd_registros_partidas,sizeof(partidas_index),qsort_partidas_idx, true, 0);
    // Verificando se a partida foi encontrada
    if (bb == -1) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);  
    } else {
        exibir_partida(partidas_idx[bb].rrn);  // Exibe os dados da partida encontrada
    }
}



/* Listagem */
void listar_jogadores_id_menu() {
	if (qtd_registros_jogadores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_jogadores; i++)
			exibir_jogador(jogadores_idx[i].rrn);
}

/* Otimizando com lista invertida, a primeira versão foi sem */
void listar_jogadores_kits_menu(char *kit) {
    bool encontrou = false;
    int indice_secundario;
    // Verificando se há registros de jogadores
    if (qtd_registros_jogadores == 0) {
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
        return;
    }
    // Buscando o kit no índice secundário
    bool chave_encontrada = inverted_list_secondary_search(&indice_secundario, false, kit, &jogador_kits_idx);
    if (!chave_encontrada) {
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
        return;
    }
    // Recuperando todos os jogadores que possuem o kit
    int indice_final;
    char result[qtd_registros_jogadores][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX];
    int num_jogadores = inverted_list_primary_search(result, false, indice_secundario, &indice_final, &jogador_kits_idx);
    // Exibindo os jogadores encontrados
    for (int i = 0; i < num_jogadores; i++) {
        for (unsigned int j = 0; j < qtd_registros_jogadores; j++) {
            if (strcmp(jogadores_idx[j].id_jogador, result[i]) == 0) {
                exibir_jogador(jogadores_idx[j].rrn);
                encontrou = true;
                break;
            }
        }
    }
    if (!encontrou) {
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
    }
}


void listar_kits_compra_menu(char *id_jogador) {

    int posicao = -1;
    // Buscando o jogador pelo Id
    jogadores_index index;
    strcpy(index.id_jogador, id_jogador);
    posicao = busca_binaria((void*)&index, jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx, true, 0);
    if (posicao == -1) {
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
        return;
    }
    // Recuperando o registro do jogador
    Jogador jogador = recuperar_registro_jogador(jogadores_idx[posicao].rrn);
    bool encontrou_kit = false;
    // Verificando os kits disponíveis no sistema
    for (int i = 0; i < qtd_registros_kits; i++) {
        Kit kit = recuperar_registro_kit(i);
        // Verificando se o saldo do jogador é suficiente para comprar o kit
        if (jogador.saldo >= kit.preco) {
            if (!encontrou_kit) {
                printf("Kits disponíveis para compra pelo jogador %s:\n", id_jogador);
                encontrou_kit = true;
            }
            printf("- %s (Preço: %.2f)\n", kit.nome, kit.preco);
        }
    }
    // Caso nenhum kit esteja disponível
    if (!encontrou_kit) {
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
    }
}


void listar_partidas_periodo_menu(char *data_inicio, char *data_fim) {

    bool encontrou = false;
    if (qtd_registros_partidas == 0) {
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
        return;
    }
    for (unsigned int i = 0; i < qtd_registros_partidas; i++) {
        // Recuperando a partida pelo RRN
        Partida partida = recuperar_registro_partida(partidas_idx[i].rrn);
        // Verificando se a data esta dentro do intervalo especificado
        if (strcmp(partida.inicio, data_inicio) >= 0 && strcmp(partida.inicio, data_fim) <= 0) {
            exibir_partida(partidas_idx[i].rrn);
            encontrou = true;
        }
    }
    if (!encontrou) {
        printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
    }
}


/* Imprimir arquivos de dados */
void imprimir_arquivo_jogadores_menu() {
	if (qtd_registros_jogadores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_JOGADORES);
}


void imprimir_arquivo_kits_menu() {
    if (qtd_registros_kits == 0) // Verifica se o arquivo de kits está vazio
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
    if (qtd_registros_resultados == 0) // Verifica se o arquivo de resultados está vazio
        printf(ERRO_ARQUIVO_VAZIO);
    else
        printf("%s\n", ARQUIVO_RESULTADOS);
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
    if (kits_idx == NULL || qtd_registros_kits == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned i = 0; i < qtd_registros_kits; ++i)
            printf("%s, %d\n", kits_idx[i].id_kit, kits_idx[i].rrn);
}


void imprimir_partidas_idx_menu() {
    if (partidas_idx == NULL || qtd_registros_partidas == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned i = 0; i < qtd_registros_partidas; ++i)
            printf("%s, %d\n", partidas_idx[i].id_partida, partidas_idx[i].rrn);
}


void imprimir_resultados_idx_menu() {
    if (resultados_idx == NULL || qtd_registros_resultados == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned i = 0; i < qtd_registros_resultados; ++i)
            printf("%s, %s, %d\n", 
                   resultados_idx[i].id_jogador, 
                   resultados_idx[i].id_partida, 
                   resultados_idx[i].rrn);
}


/* Imprimir índices secundários */
void imprimir_preco_kit_idx_menu() {
    if (preco_kit_idx == NULL || qtd_registros_kits == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned i = 0; i < qtd_registros_kits; ++i)
            printf("%s, %.2f\n", preco_kit_idx[i].id_kit, preco_kit_idx[i].preco);
}


void imprimir_data_idx_menu() {
    if (data_idx == NULL || qtd_registros_partidas == 0)
        printf(ERRO_ARQUIVO_VAZIO);
    else
        for (unsigned i = 0; i < qtd_registros_partidas; ++i)
            printf("%s, %s\n", data_idx[i].inicio, data_idx[i].id_partida);
}


void imprimir_jogador_kits_secundario_idx_menu() {
    if (jogador_kits_idx.jogador_kits_secundario_idx == NULL || jogador_kits_idx.qtd_registros_secundario == 0) {
        printf(ERRO_ARQUIVO_VAZIO);
    } else {
        for (unsigned i = 0; i < jogador_kits_idx.qtd_registros_secundario; ++i) {
            printf("%s, %d\n",
                   jogador_kits_idx.jogador_kits_secundario_idx[i].chave_secundaria,
                   jogador_kits_idx.jogador_kits_secundario_idx[i].primeiro_indice);
        }
    }
}

void imprimir_jogador_kits_primario_idx_menu() {
    if (jogador_kits_idx.jogador_kits_primario_idx == NULL || jogador_kits_idx.qtd_registros_primario == 0) {
        printf(ERRO_ARQUIVO_VAZIO);
    } else {
        for (unsigned i = 0; i < jogador_kits_idx.qtd_registros_primario; ++i) {
            printf("%s, %d\n",
                   jogador_kits_idx.jogador_kits_primario_idx[i].chave_primaria,
                   jogador_kits_idx.jogador_kits_primario_idx[i].proximo_indice);
        }
    }
}


/* Liberar espaço */

// A primeira ideia era criar um buffer
// Mas essa função tem um menor uso de memória, pq evita a criação de buffers desnecessários
void liberar_espaco_menu() {
    int rrn_atual = 0; // RRN atualizado para os registros válidos
    for (int i = 0; i < qtd_registros_jogadores; ++i) {
        // Recupera o registro do jogador no índice atual
        Jogador jogador = recuperar_registro_jogador(i);
        // Verifica se o registro é válido
        if (strcmp(jogador.id_jogador, "*") != 0) {
            // Reescreve o registro no arquivo de dados no RRN correspondente
            escrever_registro_jogador(jogador, rrn_atual);
            // Atualiza o índice com o novo RRN
            strcpy(jogadores_idx[rrn_atual].id_jogador, jogador.id_jogador);
            jogadores_idx[rrn_atual].rrn = rrn_atual;
            rrn_atual++; // Incrementa o RRN para a próxima posição válida
        }
    }
    // Atualizando o número de registros para refletir apenas os válidos
    qtd_registros_jogadores = rrn_atual;
    // Marcando o fim do arquivo com \0 após o último registro válido
    ARQUIVO_JOGADORES[rrn_atual * TAM_REGISTRO_JOGADOR] = '\0';
    // Reordenando os índices pelo Id do jogador
    qsort(jogadores_idx, qtd_registros_jogadores, sizeof(jogadores_index), qsort_jogadores_idx);
    // Exibindo a mensagem de sucesso
    printf(SUCESSO);
}


/* Liberar memória e encerrar programa com array, foi oq eu pensei para não ficar uma função muito grande, menos trabalho rs*/
void liberar_memoria_menu() {
    // Array de ponteiros para os índices
    void *indices[] = {jogadores_idx, kits_idx, partidas_idx, resultados_idx, preco_kit_idx, data_idx,
                       jogador_kits_idx.jogador_kits_secundario_idx, jogador_kits_idx.jogador_kits_primario_idx};
    int num_indices = sizeof(indices) / sizeof(indices[0]);
    // Liberando cada índice
    for (int i = 0; i < num_indices; i++) {
        if (indices[i]) {
            free(indices[i]);
            indices[i] = NULL;
        }
    }
    printf("Memória liberada.\n");
    exit(0); // Encerra o programa
}


void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) { int indice_secundario;
    bool chave_encontrada = inverted_list_secondary_search(&indice_secundario, false, chave_secundaria, t);

    if (!chave_encontrada) {
        // Inserindo a chave secundária no índice secundário
        strcpy(t->jogador_kits_secundario_idx[t->qtd_registros_secundario].chave_secundaria, chave_secundaria);
        t->jogador_kits_secundario_idx[t->qtd_registros_secundario].primeiro_indice = t->qtd_registros_primario;
        // Inserindo o jogador no índice primário
        strcpy(t->jogador_kits_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
        t->jogador_kits_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
        // Incrementando as quantidades
        t->qtd_registros_secundario++;
        t->qtd_registros_primario++;
        // Ordenando o índice secundário
        qsort(t->jogador_kits_secundario_idx, t->qtd_registros_secundario, sizeof(jogador_kits_secundario_index), t->compar);
    } else {
        // Recuperando o índice final da lista encadeada
        int indice_final;
        inverted_list_primary_search(NULL, false, indice_secundario, &indice_final, t);
        // Inserindo o novo jogador no índice primário
        strcpy(t->jogador_kits_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
        t->jogador_kits_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
        // Atualizando o próximo índice do último jogador na lista encadeada
        t->jogador_kits_primario_idx[indice_final].proximo_indice = t->qtd_registros_primario;
        // Incrementando a quantidade
        t->qtd_registros_primario++;
    }
}


bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
    int esquerda = 0;
    int direita = t->qtd_registros_secundario - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        int comparacao = t->compar(chave_secundaria, t->jogador_kits_secundario_idx[meio].chave_secundaria);
        
        if (comparacao == 0) {
            *result = t->jogador_kits_secundario_idx[meio].primeiro_indice;
            return true;
        }
        
        if (comparacao < 0) {
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }
    *result = -1; // Usando -1 para indicar que a chave não foi encontrada
    return false;
}



int inverted_list_primary_search(char result[][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
    int num_chaves_encontradas = 0;
    // Exibindo o caminho inicial
    if (exibir_caminho) {
        printf(" %d", indice);
    }
    // Recuperando o primeiro corredor
    if (result != NULL) {
        strcpy(result[num_chaves_encontradas], t->jogador_kits_primario_idx[indice].chave_primaria);
    }
    num_chaves_encontradas++;
    // Atualizando o índice final
    if (indice_final != NULL) {
        *indice_final = indice;
    }
    // Percorrendo a lista encadeada
    while (t->jogador_kits_primario_idx[indice].proximo_indice != -1) {
        indice = t->jogador_kits_primario_idx[indice].proximo_indice;
        // Exibir o caminho
        if (exibir_caminho) {
            printf(" %d", indice);
        }
        // Recuperando o corredor
        if (result != NULL) {
            strcpy(result[num_chaves_encontradas], t->jogador_kits_primario_idx[indice].chave_primaria);
        }
        num_chaves_encontradas++;
        // Atualizando o índice final
        if (indice_final != NULL) {
            *indice_final = indice;
        }
    }
    // Exibindo nova linha
    if (exibir_caminho) {
        printf("\n");
    }
    return num_chaves_encontradas;
}


/* Funções de busca binária */ // poxa, deu trabalho rs
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
    const char *base = (const char *)base0;
    size_t lim = nmemb;
    size_t meio;
    int cmp;
    size_t pos_inicial = 0;

    // Exibindo registros percorridos
    if (exibir_caminho) {
        printf(REGS_PERCORRIDOS + ' '); // Corrigindo o erro de saída
    }
    while (lim > 0) {
        meio = lim >> 1; // Calculando a mediana
        const void *p = base + meio * size;
        cmp = compar(key, p);

        // Exibindo índice atual no caminho
        if (exibir_caminho) {
            printf("%ld", pos_inicial + meio);
            if (cmp == 0 || lim == 1) {
                printf("\n"); // Último valor do caminho
            } else {
                printf(" "); // Espaço entre índices
            }
        }
        if (cmp == 0) {
            int pos = pos_inicial + meio;
            // Tratando as repetições
            if (posicao_caso_repetido < 0) {
                // Localizando a primeira ocorrência
                while (pos > 0 && compar(key, base0 + (pos - 1) * size) == 0) {
                    pos--;
                }
            } else if (posicao_caso_repetido > 0) {
                // Localizando a última ocorrência
                while (pos + 1 < (int)nmemb && compar(key, base0 + (pos + 1) * size) == 0) {
                    pos++;
                }
            }
            return pos;
        }
        if (cmp > 0) { // Movendo para a metade direita
            base += (meio + 1) * size;
            pos_inicial += meio + 1;
            lim -= meio + 1;
        } else { // Movendo para a metade esquerda
            lim = meio;
        }
    }
    if (exibir_caminho) { // Quando a chave não é encontrada
        printf("\n");
    }
    if (retorno_se_nao_encontrado == -1) {
        return (pos_inicial > 0) ? (pos_inicial - 1) : -1; // Retorna o antecessor
    } else if (retorno_se_nao_encontrado == 1) {
        return (pos_inicial < nmemb) ? pos_inicial : -1;  // Retorna o sucessor
    }
    return -1; // Retorno padrão NULL
}

/* Função de busca binária simples */
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
