#include <stdio.h>

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO ArvoreBin;

//ArvoreBin *raiz;//criando o meu nó raiz(primeira forma)

ArvoreBin* create(){

    ArvoreBin* raiz = (ArvoreBin*)malloc(sizeof(ArvoreBin));//(segunda forma)
    
    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}

int vazia(ArvoreBin *raiz){

    if(raiz == NULL){//verifica se a raiz está vazia
        printf("\n\nArvore Vazia");
        return 1; 
    }else{//caso não seja...
        printf("\n\nArvore nao esta vazia");
        return 0;
    }
}

void imprimir(ArvoreBin* raiz){
    if(raiz == NULL){//verifica se arvore esta vazia
        //printf("ARVORE VAZIA");
    }else{
        printf("\n%d ", raiz->info);//printa informação da raiz
        imprimir(raiz->dir);//por recursividade chama a funçao imprimir e seta o valor a direita
        imprimir(raiz->esq);//por recursividade chama a funçao imprimir e seta o valor a esquerda
    }
}

ArvoreBin* inserir(ArvoreBin* raiz, int info){

    if(raiz == NULL){//verifica se raiz esta vazia(se verdadeira o valor será setado na raiz primaria)
        raiz = (ArvoreBin*)malloc(sizeof(ArvoreBin));//aloca raiz na memoria
        raiz->info = info;//seta o info de raiz
        raiz->dir = NULL;//define o ponteiro esq como NULL
        raiz->esq = NULL;//""             "" dir ""    ""
    }else{
        if(info < raiz->info){//verifica se a nova informação a ser inserida é menor do que a informação da raiz
            raiz->esq = inserir(raiz->esq, info); //seta para a raiz a esquerda com o valor de info(recursividade)
        }else if(info > raiz->info){//verifica se a nova informação a ser inserida é maior do que a informação da raiz
            raiz->dir = inserir(raiz->dir, info);//seta para a raiz a esquerda com o valor de info(recursividade)
        }
    }
    return raiz;//retorna a raiz
}

ArvoreBin* remover(ArvoreBin *raiz, int chave) {
    if(raiz == NULL) {//verifica se existe algum valor dentro da raiz
        printf("\nValor nao encontrado!\n");
        return NULL;
    } else {
        if(raiz->info == chave) {//se o conteudo da raiz for igual a chave procurada...
            // remove nós folhas (sem filhos)
            if(raiz->esq == NULL && raiz->dir == NULL) {//verifica se raiz não tem nenhum filho(esq e dir)
                free(raiz);//remove a raiz da memoria
                return NULL;
            }else{
                // remover nós que possuem apenas 1 filho
                if(raiz->esq == NULL || raiz->dir == NULL){//verifica se a raiz tem pelo menos um filho(na esq ou na dir)
                    ArvoreBin *aux;//variavel auaxiliar para salvar o filho(da esq ou da dir)
                    if(raiz->esq != NULL){//se o filho estiver na esquerda...
                        aux = raiz->esq;//variavel auxiliar recebe o filho esq
                    }else{
                        aux = raiz->dir;//variavel auxiliar recebe o filho esq
                    }
                    free(raiz);//remove a raiz
                    return aux;//retorna o endereço do filho(esq ou dir)
                }else{//caso haja dois filhos(esq e dir)    
                    ArvoreBin *aux = raiz->esq;//recebe sub arvore a esquerda
                    while(aux->dir != NULL){//percorre a sub arvore a esquerda do nó a ser removido até chegar no ultimo nó a direita
                        aux = aux->dir;
                    }
                    raiz->info = aux->info;//informação de raiz recebe a informação que está contida em aux
                    aux->info = chave;//informação de raiz recebe a chave que está sendo removida
                    raiz->esq = remover(raiz->esq, chave);//chamada recursiva
                    return raiz;
                }
            }
        } else {
            if(chave < raiz->info){//se a chave que deseja-se remover foor menor que o conteudo da raiz...
                raiz->esq = remover(raiz->esq, chave);//chamada recursiva setando sub arvore esquerda. raiz->esq recebe valor do retorno
            }else{
                raiz->dir = remover(raiz->dir, chave);//chamada recursiva setando sub arvore a direita. raiz->dir recebe valor do retorno
            }
            return raiz;//retorna a raiz
        }
    }
}

ArvoreBin* liberar(ArvoreBin* raiz){
    if (raiz != NULL) {//caso a raiz não esteja vazia
        liberar(raiz->esq);//libera ponteiro a esquerda(recursividade)
        liberar(raiz->dir);//libera ponteiro a direita(recursividade)
        free(raiz);//apaga raiz da memoria
    }
    return NULL;//retona NULL
}

ArvoreBin* buscar (ArvoreBin* raiz, int chave) {
    while (raiz != NULL){//verifica se a raiz não esta vazia
        if(raiz->info == chave){//verifica se o valor em raiz é igual a chave buscada
            printf("\n\nValor encontrado: %d", raiz->info);
            return raiz;
        }else{
            if(raiz->info > chave){//verifica se o valor em raiz é maior que a chave buscada
                raiz = raiz->esq;//seta a raiz como raiz que está a esquerda
            }else{
                raiz = raiz->dir;//seta raiz como raiz que está a esquerda
            }
        }
        if(raiz == NULL){//verifica se a raiz está vazia e retorna para o usuario
            printf("\n\nValor nao encontrado");
            return NULL;
        }
    }
}

int main(int argc, char const *argv[]){
   
    ArvoreBin* exemplo;
	exemplo = create();
    vazia(exemplo);
    exemplo = inserir(exemplo, 1001);
    exemplo = inserir(exemplo, 1002);
    exemplo = inserir(exemplo, 1003);
    exemplo = inserir(exemplo, 1004);
    printf("\n---------------------------------------------------");
    buscar(exemplo, 1005);
    buscar(exemplo, 1001);
    buscar(exemplo, 1002);
    buscar(exemplo, 1003);
    printf("\n---------------------------------------------------");
    imprimir(exemplo);
    printf("\n---------------------------------------------------");
    exemplo = remover(exemplo, 1004);
    imprimir(exemplo);
    exemplo = remover(exemplo, 1001);
    printf("\n---------------------------------------------------");
    imprimir(exemplo);
    printf("\n---------------------------------------------------");
    buscar(exemplo, 1004);
    buscar(exemplo, 1001);
    buscar(exemplo, 1002);
    buscar(exemplo, 1003);

    vazia(exemplo);
    liberar(exemplo);
    vazia(exemplo);

    //ArvoreBin* b = buscar(exemplo, 1004);
    //if(!b == NULL){
    //    printf("\nValor encontrado: %d", b);
    //}
    //printf("\nValor nao encontrado");
    


}
