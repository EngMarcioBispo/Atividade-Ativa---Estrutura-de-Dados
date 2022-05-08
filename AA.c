#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char cantor[100], musica[100];
    int duracao;
} Artista;

typedef struct no
{
    Artista artista;
    struct no *direita, *esquerda;
} NoArv;

Artista ler_artista()
{
    Artista a;
    printf("\tDigite o nome do cantor: ");
    scanf("%s", a.cantor);
    printf("\tDigite o nome da musica: ");
    scanf("%s", a.musica);
    printf("\tDigite a duracao da musica: ");
    scanf("%d", &a.duracao);
    return a;
}

void imprimir_artista(Artista a)
{
    printf("\t'%s' -> '%s'\n", a.cantor, a.musica);
}

void inserir(NoArv **raiz, Artista a)
{
    NoArv *aux = *raiz;
    while (aux)
    {
        if (a.duracao < aux->artista.duracao)
            raiz = &aux->esquerda;
        else
            raiz = &aux->direita;
        aux = *raiz;
    }
    aux = malloc(sizeof(NoArv));
    aux->artista = a;
    aux->esquerda = NULL;
    aux->direita = NULL;
    *raiz = aux;
}

NoArv *buscar(NoArv *raiz, int duracao)
{
    if (raiz)
    {
        if (duracao == raiz->artista.duracao)
            return raiz;
        else if (duracao < raiz->artista.duracao)
            return buscar(raiz->esquerda, duracao);
        else
            return buscar(raiz->direita, duracao);
    }
    return NULL;
}

NoArv *remover(NoArv *raiz, int chave)
{
    if (raiz == NULL)
    {
        printf("Valor nao encontrado!\n");
        return NULL;
    }
    else
    {
        free(raiz);
        printf("Musica %d removida\n", chave);
        return NULL;
    }
}

void imprimir(NoArv *raiz)
{
    if (raiz)
    {
        imprimir(raiz->esquerda);
        imprimir_artista(raiz->artista);
        imprimir(raiz->direita);
    }
}

int main()
{
    NoArv *busca, *raiz = NULL;
    int opcao, valor;

    do
    {
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Remover\n");
        scanf("%d", &opcao);
        scanf("%c");

        switch (opcao)
        {
        case 1:
            inserir(&raiz, ler_artista());
            break;
        case 2:
            printf("\n\tDigite a duracao da musica a ser procurada: ");
            scanf("%d", &valor);
            busca = buscar(raiz, valor);
            if (busca)
            {
                printf("\n\tValor encontrado:\n");
                imprimir_artista(busca->artista);
            }
            else
                printf("\n\tValor nao encontrado!\n");
            break;
        case 3:
            printf("\t");
            imprimir(raiz);
            printf("\n\tDigite a duracao da musica a ser removida: ");
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        default:
            if (opcao != 0)
                printf("\n\tOpcao invalida!!!\n");
        }
    } while (opcao != 0);
    return 0;
}