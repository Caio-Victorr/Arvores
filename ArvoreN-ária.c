#include <stdio.h>
#include <stdlib.h>

struct no {
	int info;
	struct no* primFilho;
	struct no* proxIrmao;
};

typedef struct no Arv;

Arv* criarNo(int valor) {
	Arv* novoNo = (Arv*)malloc(sizeof(Arv));//aloca um novo no na memoria
	novoNo->info = valor; //seta o valor dentro do no
	novoNo->primFilho = NULL;
	novoNo->proxIrmao = NULL;
	return novoNo;
}



Arv* buscar(Arv* raiz, int valor) {
	if(raiz == NULL) {//verifica se a arvore esta vazia
		return NULL;
	}
	if (raiz->info == valor) {//verifica se o valor buscado é igual a raiz
		return raiz;
	}
	Arv* p = buscar(raiz->primFilho, valor);//percorre todos os primogenitos da raiz em busca do valor
	if(p != NULL) {//caso a função encontre o o valor buscado...
		return p;//retorna o valor encontrado nos primogenitos
	}
	Arv* irmao = buscar(raiz->proxIrmao, valor);//percorre todos os irmão dos primogenitos em busca do valor
	return irmao;//retorna valor encontrado nos irmãos
}

void exibir(Arv* raiz) {
	if(raiz == NULL) {
		printf("\nArvore vazia");
		return NULL;
	}
	printf("%d(", raiz->info);//printa a informação da raiz
	Arv* p = raiz->primFilho;//cria ponteiro recebendo o primogenito da raiz
	if(p == NULL) {//se não houver primogenito
		return NULL;
	}
	while(p != NULL) {//percorre todos os irmaos
		exibir(p);//chama a função de exibir(recursividade)
		p = p->proxIrmao;//pula para o proximo irmão da arvore
	}
	printf("))");
}

Arv* inserir(Arv* raiz, int valorNo, int valorPai) {
	Arv* pai = buscar(raiz, valorPai);//chama a função de buscar para localizar o item na arvore
	if(pai == NULL) {//caso o valor buscado não esteja na arvore(retorno do buscar)
		return NULL;//retorna NULL
	}else{
		Arv* novo = criarNo(valorNo);//seta o valor como um novo nó alocando espaço na memoria
		novo->primFilho = NULL;
		if(pai->primFilho == NULL){//verifica se existe primogenito em pai
			pai->primFilho = novo;//seta novo como primogenito de pai
		}else{
			Arv* aux = pai->primFilho;//cria ponteiro auxiliar setando o primogenito de pai
			while(aux->proxIrmao != NULL){//percorre os irmaos do no primogenito de pai
				aux = aux->proxIrmao;
			}
			aux->proxIrmao = novo;//seta o novo como ultimo irmao do primogenito de 
		}
		return pai;
	}
}

Arv* libera(Arv* raiz){
    if (raiz != NULL) {
		libera(raiz->primFilho);
		libera(raiz->proxIrmao);
        free(raiz);
    }
    return NULL;
}

void vazia (Arv* raiz) {
	if(raiz == NULL) {
		printf("\nArvore vazia");
	}else{
		printf("\nArvore nao esta vazia");
	}
}

int main(int argc, char *argv[]) {

	Arv* a = criarNo(1);
	
	inserir(a, 2, 1);
	inserir(a, 3, 1);
	inserir(a, 4, 1);
	inserir(a, 5, 2);
	inserir(a, 6, 2);
	inserir(a, 7, 3);
	inserir(a, 8, 5);
	inserir(a, 9, 6);
    inserir(a, 10, 6);
    //inserir(a, 11, 7);
    //inserir(a, 12, 7);
    //inserir(a, 13, 7);
	
	Arv* b = buscar(a, 2);
	
	if(b != NULL) {
		printf("\nValor %d encontrado\n", b->info);
	} else {
		printf("\nValor nao encontrado\n");
	}
	exibir(a);
	vazia(a);
	a = libera(a);
	printf("\n================================");
	exibir(a);
	vazia(a);
	
	return 0;
}