#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define alfabeto (26)
#define tam_maior_palavra 200
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct noTrie {
	struct noTrie *filho[alfabeto];
	unsigned int wdCount;
};

struct rank {
	unsigned int count;
	char value[tam_maior_palavra] ;
};

int findNext(struct rank *r, int ini, int fim) {
	int i, intAux;
	char *aux;
	for (i = ini; i < fim; i++) {
		if (r[i].count > 0) return i;
	}
	return -1;
}

void sanitize(struct rank *r, int n) {
	int i, iAux;
	for (i = 0; i < n; i++) {
		if (r[i].count == 0) {
			iAux = findNext(r, i, n);
			if (iAux == -1) return;
			strcpy(r[i].value, r[iAux].value);
			r[i].count = r[iAux].count;
			strcpy(r[iAux].value, "---");
			r[iAux].count = 0;
		}
	}
}

void compare(char* str, int c, struct rank r[], int num) {
	int i, j, intAux;
	char *aux;
	for (i = 0; i < num; i++) {
		if (r[i].count == 0) {
			strcpy(r[i].value, str);
			r[i].count = c;
			return;
		}
		if (c > r[i].count) {
			if (strcmp(r[i].value, str) == 0) {
				r[i].count = c;
				return;
			} else {
				for (j = 7; j > i; j--) {
					if (strcmp(str, r[j - 1].value) != 0) {
						strcpy(r[j].value, r[j - 1].value);
						r[j].count = r[j - 1].count;
						strcpy(r[j - 1].value, "---");
						r[j - 1].count = 0;
					}
				}
				strcpy(r[i].value, str);
				r[i].count = c;
				return;
			}
		}
	}
}

void printRank(struct rank r[], int num) {
	int i;
	for (i = 0; i < num; i++) {
		printf("# %d - quantidade %d - palavra: %s\n", i, r[i].count, r[i].value);
	}
}

struct noTrie *getNo(void){
	struct noTrie *pNo = NULL;
	pNo = (struct noTrie *)malloc(sizeof(struct noTrie));
	if (pNo){
		int i;
		pNo -> wdCount = 0;;

		for (i = 0; i < alfabeto; i++){
			pNo -> filho[i] = NULL;
		}
	}
	return pNo;
}

void inserir(struct noTrie *raiz, char *key, struct rank *r, int op, int num){
	int altura;
	int comprimento = strlen(key);
	int index;
	struct noTrie *pNoCaminhar = raiz;
	for (altura = 0; altura < comprimento; altura++){
		index = CHAR_TO_INDEX(key[altura]);
		if (!pNoCaminhar -> filho[index]){
			pNoCaminhar -> filho[index] = getNo();
		}
		pNoCaminhar = pNoCaminhar -> filho[index];
	}
	pNoCaminhar -> wdCount += 1;
	if (op == 1) compare(key, pNoCaminhar->wdCount, r, num);
}

bool procurar(struct  noTrie *raiz, const char *key){
	int altura;
	int comprimento = strlen(key);
	int index;
	struct noTrie *pNoCaminhar = raiz;
	for (altura = 0; altura < comprimento; altura++){
		index = CHAR_TO_INDEX(key[altura]);
		if (!pNoCaminhar -> filho[index]){
			return false;
		}
		pNoCaminhar = pNoCaminhar -> filho[index];		
	}
	printf("Ocorrencias da palavra: %d\n", pNoCaminhar->wdCount);
	return ((pNoCaminhar != NULL) && (pNoCaminhar -> wdCount > 0));
}

char* limparString (char* palavra){
	for(char *p = palavra; *p ; ++p){
	 	*p = (*p > 0x40) && (*p < 0x5b) ? *p | 0x60 : *p;	// Confere se a palavra é maiscula
	}														// se for retorna minuscula
	for(char *p = palavra; *p; ++p){						// Confere se a palavra só tem letras
		*p = (*p > 0x60) && (*p < 0x7b) ? *p : '\0';		// remove pontos, aspas, parenteses
	}
	return palavra;
}

int main (int argc, char *argv[]){
	int opcao = 1; //valores default caso nao sejam passados parametros 
	int rankNum = 5;	//valores default caso nao sejam passados parametros
	char nomeEntrada[30];
	//int rankNum;
	char* palavrita = (char *)malloc(sizeof(char) * tam_maior_palavra);
	strcpy(nomeEntrada, "entradaTexto.txt"); //valor default caso nao seja passado um arquivo
	if (argc > 1 ) {
		if (strcmp(argv[1], "--freq") == 0) { //opçao 1 --freq N arquivo
			rankNum = atoi(argv[2]);
			strcpy(nomeEntrada, argv[3]);
		} else if (strcmp(argv[1], "--freq-word") == 0) {
			opcao = 2;
			strcpy(palavrita, argv[2]);
			strcpy(nomeEntrada, argv[3]);
		} else if (strcmp(argv[1], "--search") == 0) {
			opcao = 3;
			printf("funcao nao implementada ainda\n");

			//TODO fazer a busca maluca por expressao entre arquivos

		}
	}
	int i;

	struct rank *r = (struct rank *)malloc(sizeof(struct rank ) * rankNum * 10);
	
	for (i = 0; i < rankNum; i++) {
		strcpy(r[i].value, "---");
		r[i].count = 0;
	}
	char* palavra = (char *)malloc(sizeof(char) * tam_maior_palavra);
    FILE *arq;
    arq = fopen(nomeEntrada, "r");

    if (arq == NULL){
    	printf("Arquivo não encontrado...");
    	return 0;
    }

    struct noTrie *raiz = getNo();

    while(!feof(arq)){
		fscanf(arq, "%s", palavra); 		// Leitura String
		palavra = limparString(palavra);    // Limpando (Sinais e tudo minusculo)
		//printf("Inserindo na arvore... %s\n", palavra );		// mostra palavra lida

		int i = 1;

		while (palavra[i] != '\0'){
			inserir(raiz, palavra, r, opcao, rankNum);
			i++;
		}
	}
	fclose(arq);

	printf("\naeeeeee\n");
	if (opcao == 1) {
		sanitize(r, rankNum);
		printRank(r, rankNum);
	} else if (opcao == 2) {
		char *palavraLimpa = limparString(palavrita);
		//strcpy(palavraBuscada,(limparString(palavraBuscada)));
		char output[][60] = {"Não encontrei a palavra", "Encontrei sua palabra"};
		printf("%s --- %s\n", palavraLimpa, output[procurar(raiz, palavraLimpa)]);
		free(palavraLimpa);
	} else if (opcao == 3) {
		printf("funcao nao implementada ainda...\n");
	} else {
		printf("no\n");
	}
	free(r);
}