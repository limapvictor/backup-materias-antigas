#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *v;
    int topo, max;
} pilha;
typedef pilha *Pilha;

typedef struct {
    int **tab;
    char **palavras;
    int m, n, p;
} instancia;

typedef struct {
    int lin, col, sentido;
} encaixe;

int max(int a, int b)
{
    if (a < b){
        return (b);
    }
    return (a);
}

int pilhaVazia(Pilha P)
{
    return (P->topo == 0);
}

void empilha(Pilha P, int el)
{
    P->v[P->topo] = el;
    (P->topo)++;
}

void desempilha(Pilha P)
{
    if (pilhaVazia(P)) {
        printf ("Erro");
        return;
    }
    (P->topo)--;
}

int topoDaPilha(Pilha P)
{
    if (pilhaVazia(P)) {
        printf ("Erro");
        return (-1);
    }
    return (P->v[P->topo-1]);
}

int empilhado(Pilha P, int x)
{ /*Função que verifica se um item está empilhado na pilha.*/
    int i, achou = 0;
    for(i = 0; i < P->topo && achou == 0; i++) {
        if (P->v[i] == x) achou = 1;
    }
    return (achou);
}

Pilha criaPilha(int max)
{
    Pilha P = malloc (sizeof (pilha));
    P->v = malloc (max * sizeof (int));
    P->topo = 0;
    P->max = max;
    return (P);
}

void destroiPilha(Pilha P)
{
    free (P);
}

int tamPalavra(char *palavra)
{
    int i;
    for (i = 0; palavra[i] != '\0'; i++);
    return (i);
}

void copiaPalavra(char *origem, char *destino)
{
    int i;
    for (i = 0; origem[i] != '\0'; i++) {
        destino[i] = origem[i];
    }
    destino[i] = '\0';
}

void ordenaPalavras(char **palavras, int n, int t)
{/*Função que utiliza do algoritmo de inserção para ordenar as palavras de acordo com a quantidade de letras.*/
    int b, i;
    char *x;
    x = malloc (t * sizeof (char));
    for (b = 1; b < n; b++) {
        copiaPalavra(palavras[b], x);
        for (i = b - 1; i >= 0 && tamPalavra(palavras[i]) > tamPalavra(x); i--){
            copiaPalavra(palavras[i], palavras[i + 1]);
        }
        copiaPalavra(x, palavras[i + 1]);
    }
}

char **tabuleiroPalavras(instancia *inst)
{ /*Função que recebe o tabuleiro inteiro e faz um espelho dele só que com caracteres.*/
    char **v;
    int i,j;
    v = malloc (inst->m * sizeof (char *));
    for(i = 0; i < inst->m; i++) {
        v[i] = malloc (inst->n * sizeof (char));
        for(j = 0; j < inst->n; j++) {
            if (inst->tab[i][j] == -1) {
                v[i][j] = '*';
            } else {
                v[i][j] = '-';
            }
        }  
    }
    return (v);
}

encaixe *verificaEncaixes(instancia *inst)
{ 
/*Função que retorna um vetor contendo o mapeamento de em que posições do tabuleiro se realizam as inserções de palavra,
 além de indicar se a inserção é horizontal ou vertical. */
    encaixe *v;
    int i, j, l = 0;
    v = malloc (inst->p * (sizeof (encaixe)));
    for (i = 0; i < inst->m; i++) {
        for (j = 0; j < inst->n; j++) {
            if (inst->tab[i][j] != -1) {
                if ((j == 0 || inst->tab[i][j - 1] == -1) && inst->n - j > 1 && inst->tab[i][j + 1] != -1) { 
                    v[l].lin = i; v[l].col = j; v[l].sentido = 1;
                    l++;
                }
                if ((i == 0 || inst->tab[i - 1][j] == -1) && inst->m - i > 1 && inst->tab[i + 1][j] != -1) {
                    v[l].lin = i; v[l].col = j; v[l].sentido = 2;
                    l++;
                }
            }
        }
    }
    return (v);
}

int tamEncaixe(instancia *inst, encaixe pos)
{/*Função que verifica quantos caracteres cabem em cada encaixe.*/
    int i = pos.lin, j = pos.col;
    if (pos.sentido == 1) {
        while (j < inst->n && inst->tab[i][j] != -1) j++;
        return (j - pos.col);
    }
    while (i < inst->m && inst->tab[i][j] != -1) i++;
    return (i - pos.lin);
}

void desencaixa(char **tab, encaixe pos, char *palavra, Pilha P, int fim)
{/*Função que desencaixa os caracteres de uma palavra que está no encaixe errado,
 usando uma pilha que indica quais caracteres daquela palavra podem ser retirados em cada desencaixe.*/
    int k;
    if (pos.sentido == 1) { 
        if (fim == -1) fim = pos.col + tamPalavra(palavra) - 1;
        for (k = fim; k >= pos.col; k--) {
            if (tab[pos.lin][k] == topoDaPilha(P)) {
                tab[pos.lin][k] = '-';
                desempilha(P);
            }
        }
    } else {
        if (fim == -1) fim = pos.lin + tamPalavra(palavra) -1;
        for (k = fim; k >= pos.lin; k--) {
            if (tab[k][pos.col] == topoDaPilha(P)) {
                tab[k][pos.col] = '-';
                desempilha(P);
            }
        }
    }
}

int encaixou(char **tab, encaixe pos, char *palavra, Pilha P)
{/*Função que retorna se uma palavra conseguiu ou não ser encaixada em determinada posição do tabuleiro
 além de fazer o encaixe caso a palavra esteja no encaixe certo até o momento.*/
    int c, i = pos.lin, j = pos.col, ok = 1;
    if (pos.sentido == 1) {
        while(ok == 1 && j - pos.col < tamPalavra(palavra) ){
            if (tab[i][j] != '-') {
                if (tab[i][j] != palavra[j - pos.col]) { 
                    ok = 0;
                    desencaixa(tab, pos, palavra, P, j);
                } else j++;
            } else {
                tab[i][j] = palavra[j - pos.col];
                c =  palavra[j - pos.col]; //correspondencia caractere - inteiro
                empilha(P, c); //encaixo o caractere na pilha para sinalizar que ele pode ser removido caso seja preciso, visto que ocupou uma posição que estava vazia
                j++;
            } 
        }    
    } else {
        while(ok == 1 && i - pos.lin < tamPalavra(palavra) ){
            if (tab[i][j] != '-') {
                if (tab[i][j] != palavra[i - pos.lin]) {
                    ok = 0;
                    desencaixa(tab, pos, palavra, P, i);
                } else i++;
            } else {
                tab[i][j] = palavra[i - pos.lin];
                c =  palavra[i - pos.lin];
                empilha(P, c);
                i++;
            } 
        }    
    }
    return (ok);
}

void verificaInstancia(instancia *inst)
{/*Realiza as operações com as instâncias.*/
    Pilha P, PC;
    encaixe *encaixes;
    char **tabuleiro = tabuleiroPalavras(inst); 
    int i, j = 0, x = 0, sol = 1, sair;
    P = criaPilha(inst->p); //essa pilha guarda os ids das palavras 
    PC = criaPilha(inst->p * max(inst->m, inst->n) / 2); //essa pilha guarda a cada palavra encaixada quais caracteres podem ser removidos se necessário o desencaixe
    encaixes = verificaEncaixes(inst);
    while (sol == 1 && P->topo != P->max) {
        sair = 0;
        for (i = x; i < inst->p && sair == 0; i++) {
            if (!empilhado(P,i)) {  
                if (tamEncaixe(inst, encaixes[j]) == tamPalavra(inst->palavras[i]) && encaixou(tabuleiro, encaixes[j], inst->palavras[i], PC)) {
                    empilha(P, i); 
                    j++; //passo para o próximo encaixe
                    x = 0; sair = 1; //o x é setado em 0 para que possa testar todas palavras não empilhadas novamente
                } else if (tamEncaixe(inst, encaixes[j]) < tamPalavra(inst->palavras[i]) || i == inst->p - 1) {
                    sair = 1;
                    if (!pilhaVazia(P)) {    
                        j--; //volto para o encaixe anterior visto que não consigo encaixar no atual com as palavras restantes
                        x = topoDaPilha(P) + 1; //uso o id da ultima palavra e somo 1 visto que ela me deixou em um encaixe sem solução
                        desencaixa(tabuleiro, encaixes[j], inst->palavras[topoDaPilha(P)], PC, -1);
                        desempilha(P);
                    } else {
                        sol = 0;
                    }
                }
            }        
        }          
    }
    for (i = 0; i < inst->m; i++) {
        for (j = 0; j < inst->n; j++) {
            if (sol == 1) printf ("%c\t", tabuleiro[i][j]);
        }
        if (sol == 1) printf ("\n");
        free (tabuleiro[i]);
    }
    if (sol == 0) printf ("Nao ha solucao \n");
    printf("\n");
    free (tabuleiro); free (encaixes);
    destroiPilha(P); destroiPilha(PC);
}

int main(void)
{
    instancia *inst;
    int **tab;
    char **palavras;
    int m, n, p, i, j, cont = 1, k;
    while (cont > 0) {
        printf ("Digite quantas linhas o tabuleiro possui: "); 
        scanf ("%d", &m);
        printf ("Digite quantas colunas o tabuleiro possui: ");
        scanf ("%d", &n);
        if (m == 0 || n == 0) break;
        tab = malloc (m * sizeof (int *));
        printf("Preencha o tabuleiro com 0 para casas brancas e -1 para casas pretas:\n");
        for (i = 0; i < m; i++) {
            tab[i] = malloc (n * sizeof (int));
            j = 0;
            for (j = 0; j < n; j++) scanf ("%d", &tab[i][j]);
        }
        printf ("Digite quantas palavras voce deseja encaixar no tabuleiro: ");
        scanf ("%d", &p);
        palavras = malloc (p * sizeof (char *));
        for (i = 0; i < p; i++) { 
            palavras[i] = malloc ((max(m, n) + 1) * sizeof (char));  
            scanf ("%s", palavras[i]);
        }
        ordenaPalavras(palavras, p, max(m, n));
        inst = malloc (sizeof (instancia));
        inst->tab = tab;
        inst->palavras = palavras;
        inst->m = m; inst->n = n; inst->p = p;
        printf ("\n\nInstancia %d\n", cont++);
        verificaInstancia(inst);
        for (k = 0; k < m; k++) free (tab[k]);
        for (k = 0; k < p; k++) free (palavras[k]);
        free (inst); free (tab); free (palavras); 
    }
    return (0);
}
