// MAC0328 (2019) Algoritmos em Grafos
// Aluno:      João Gabriel Lembo & Victor Pereira Lima
// Número USP: 10737178 & 10737028
// Tarefa:     TarefaG
// Data:       2019-29-09
//
// Solução baseada em ... <se for o caso> ...
//
// DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE PROGRAMA. TODAS
// AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO PROFESSOR
// OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSÁVEL POR
// TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// FACILITEI A DISTRIBUIÇÃO DE CÓPIAS.
//
////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "GRAPHlists.h"

bool
UGRAPHcoloracaoEhValida( UGraph G, int *color) 
{
    for (vertex v = 0; v < G->V; v++) {
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (color[v] == color[a->w])
                return (false);
        } 
    }
    return (true);
}

int UGRAPHseqColoringI( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) color[v] = -1;
   for (vertex v = 0; v < G->V; ++v) {
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) color[v] = i;
      else color[v] = k++;
   }
   return k;
}

// A função inverte as cores dos vértices no subgrafo que tem os vértices
// com cores components[0] e components[1]. Além disso, verifica se algum
// dos vértices aponta para a origem com a mesma cor que a que será atribuida
// a ela, devolvendo false, isto é, indicando que a troca de cores não pode ser
// feita.
bool
changeComponents( UGraph G, vertex v, int* color, int components[], int this, vertex origem, int* visited) {
   visited[v] = 1;
   color[v] = components[1-this];
   for (link a = G->adj[v]; a!= NULL; a = a->next) {
      if (color[a->w] == components[1-this] && visited[a->w] == -1) {
         if (changeComponents( G, a->w, color, components, 1-this, origem, visited) == false) 
            return false;
      }
      else if (a->w == origem && color[v] == components[0]) return false;
   }
   return true;
}

// A função realiza o processo da troca de cores de componentes
// bicoloridas, como explicitado no enunciado.
int 
trocaDeComponentes( UGraph G, vertex w, int* color, int chosen, vertex v, int k) {
   int* components = mallocc( 2 * sizeof (int));
   components[0] = chosen;
   int* visited = malloc( G->V * sizeof (int));
   int i;
   for (i = 0; i < k; i++) {
      if (i == chosen) i++;
      if (i == k) {
         color[v] = k++;
         break;
      }
      components[1] = i;
      for (int j = 0; j < G->V; j++) visited[j] = -1;
      if (changeComponents( G, w, color, components, 0, v, visited) == false) {
         for (int j = 0; j < G->V; j++) visited[j] = -1;
         changeComponents( G, w, color, components, 1, v, visited);
      }
      else {
         color[v] = chosen;
         i = 0;
         break;
      }
   }
   free( components);
   if (i == k) color[v] = k++;
   return k;
}

// Função de coloração sequencial com adição da troca de componentes
// bicoloridas.
int UGRAPHseqColoringII( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) color[v] = -1;
   for (vertex v = 0; v < G->V; ++v) {
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) 
         disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) 
            disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) 
         color[v] = i;
      else {
         int* count = mallocc( k * sizeof (int));
         for (link a = G->adj[v]; a!= NULL; a = a->next)
            count[color[a->w]]++;
         int chosen = -1;
         for (i = 0; i < k; i++)
            if (count[i] == 1) 
               chosen = i;
         if (chosen == -1) 
            color[v] = k++;
         else {
            vertex w;
            for (link a = G->adj[v]; a!= NULL; a = a->next)
               if (color[a->w] == chosen)
                  w = a->w;
            k = trocaDeComponentes( G, w, color, chosen, v, k);
         }
      }
   }
   return k;
}


// Função de coloração sequencial com a troca de componentes
// bicoloridas e a heurística criada pela dupla (explicada no
// relatorio).
int UGRAPHseqColoringIII( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) 
      color[v] = -1;
   for (vertex v = 0; v < G->V; ++v) {
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) 
         disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) 
            disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) color[v] = i;
      else {
         int* count = mallocc( k * sizeof(int));
         for (link a = G->adj[v]; a!= NULL; a = a->next)
            if (color[a->w] != -1)
               count[color[a->w]]++;
         int chosen = -1;
         for (i = 0; i < k; i++)
            if (count[i] == 1) 
               chosen = i;
         if (chosen == -1) 
            color[v] = k++;
         else {
            vertex w;
            for (link a = G->adj[v]; a!= NULL; a = a->next)
               if(color[a->w] == chosen)
                  w = a->w;
            for (i = 0; i < k; ++i) 
               disponivel[i] = true;
            disponivel[color[w]] = false;
            for (link a = G->adj[w]; a != NULL; a = a->next) {
               i = color[a->w];
               if (i != -1) 
                  disponivel[i] = false;
            }
            for (i = k-1; i >= 0; i--)
               if (disponivel[i]) break;
            if (i >= 0) {
               color[w] = i;
               color[v] = chosen;
            }
            else {
               k = trocaDeComponentes( G, w, color, chosen, v, k);
            }
         }
      }
   }
   return k;
}


// Conta o número de cores utilizadas ao redor do
// vértice v.
int
VERTEXcoresAoRedor( UGraph G, vertex v, int *color)
{
    int cont = 0;
    int *coresUsadas = mallocc( GRAPHoutdeg( G, v) * sizeof (int));
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        if (color[a->w] != -1) {
            bool usada = false;
            for (int i = 0; i < cont; i++) {
                if (color[a->w] == coresUsadas[i])
                    usada = true;
            }
            if (!usada)
                coresUsadas[cont++] = color[a->w];
        }
    }
    free( coresUsadas);
    return (cont);
}


// Função de coloração sequencial com a heurística
// de Brelaz.
int
UGRAPHseqColoringIV( UGraph G, int *color)
{
    int k = 0;
    for (vertex v = 0; v < G->V; v++)
        color[v] = -1;
    for (vertex v = 0; v < G->V; v++) {
        vertex escolhido = v;
        while (color[escolhido] != -1)
            escolhido = (escolhido + 1) % G->V;
        int coresEscolhido = VERTEXcoresAoRedor( G, escolhido, color);
        for (vertex w = 0; w < G->V; w++) {
            if (color[w] == -1) {
                int coresW = VERTEXcoresAoRedor( G, w, color);
                if (coresW > coresEscolhido || (coresW == coresEscolhido && GRAPHoutdeg(G, w) > GRAPHoutdeg(G, escolhido))) {
                    escolhido = w;
                    coresEscolhido = coresW;
                }
            }
        }
        bool *disponivel = mallocc( GRAPHoutdeg( G, escolhido) * sizeof (bool));
        for (int i = 0; i < k; i++)
            disponivel[i] = true;
        for (link a = G->adj[escolhido]; a != NULL; a = a->next) {
                if (color[a->w] != -1)
                    disponivel[color[a->w]] = false;
        }
        int i;
        for (i = 0; i < k; ++i)
            if (disponivel[i]) break;
        if (i < k)
            color[escolhido] = i;
        else
            color[escolhido] = k++;
        free( disponivel);
    }
    return k;
}


// Função de coloração sequencial com aleatorização na
// escolha dos vértices e na seleção entre as cores
// disponíveis.
int
UGRAPHseqColoringV( UGraph G, int *color)
{
    int k = 0;
    for (vertex v = 0; v < G->V; ++v) color[v] = -1;
    for (int j = 0; j < G->V; ++j) {
        vertex v = randInteger( 0, G->V - 1);
        while (color[v] != -1)
            v = randInteger( 0, G->V - 1);
        bool *disponivel = mallocc( GRAPHoutdeg( G, v) * sizeof (bool));
        int i;
        for (i = 0; i < k; ++i)
            disponivel[i] = true;
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            i = color[a->w];
            if (i != -1)
                disponivel[i] = false;
        }
        for (i = 0; i < k; ++i)
            if (disponivel[i]) break;
        if (i < k) {
            int r = randInteger( 0, k);
            while (disponivel[r] == false)
                r = randInteger( 0, k);
            color[v] = r;
        } else
            color[v] = k++;
    }
    return k;
}


// Função de coloração sequencial com a troca de componentes
// bicoloridas e a heurística de Brelaz.
int UGRAPHseqColoringVI( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; v++)
      color[v] = -1;
   for (vertex v = 0; v < G->V; v++) {
      vertex escolhido = v;
      while (color[escolhido] != -1)
         escolhido = (escolhido + 1) % G->V;
      int coresEscolhido = VERTEXcoresAoRedor( G, escolhido, color);
      for (vertex w = 0; w < G->V; w++) {
         if (color[w] == -1) {
            int coresW = VERTEXcoresAoRedor( G, w, color);
            if (coresW > coresEscolhido ||(coresW == coresEscolhido &&
                                          GRAPHoutdeg(G, w) > GRAPHoutdeg(G, escolhido))) {
               escolhido = w;
               coresEscolhido = coresW;
            }
         }
      }
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) 
            disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) 
         color[v] = i;
      else {
         int* count = mallocc( k * sizeof(int));
         for (link a = G->adj[v]; a!= NULL; a = a->next)
            count[color[a->w]]++;
         int chosen = -1;
         for (i = 0; i < k; i++)
            if (count[i] == 1) 
               chosen = i;
         if (chosen == -1) 
            color[v] = k++;
         else {
            vertex w;
            for (link a = G->adj[v]; a!= NULL; a = a->next)
               if (color[a->w] == chosen)
                  w = a->w;
            k = trocaDeComponentes( G, w, color, chosen, v, k);
         }
      }
   }
   return k;
}


// Função de coloração sequencial com a heurística de Brelaz,
// a troca de componentes bicoloridas e a heurística criada
// pela dupla (explicada no relatorio).
int UGRAPHseqColoringVII( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; v++)
      color[v] = -1;
   for (vertex v = 0; v < G->V; v++) {
      vertex escolhido = v;
      while (color[escolhido] != -1)
         escolhido = (escolhido + 1) % G->V;
      int coresEscolhido = VERTEXcoresAoRedor( G, escolhido, color);
      for (vertex w = 0; w < G->V; w++) {
         if (color[w] == -1) {
            int coresW = VERTEXcoresAoRedor( G, w, color);
            if (coresW > coresEscolhido ||(coresW == coresEscolhido &&
                                          GRAPHoutdeg(G, w) > GRAPHoutdeg(G, escolhido))) {
               escolhido = w;
               coresEscolhido = coresW;
            }
         }
      }
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) 
            disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) 
         color[v] = i;
      else {
         int* count = mallocc( k * sizeof(int));
         for (link a = G->adj[v]; a!= NULL; a = a->next)
            if (color[a->w] != -1)
               count[color[a->w]]++;
         int chosen = -1;
         for (i = 0; i < k; i++)
            if (count[i] == 1) 
               chosen = i;
         if (chosen == -1) color[v] = k++;
         else {
            vertex w;
            for (link a = G->adj[v]; a!= NULL; a = a->next)
               if (color[a->w] == chosen)
                  w = a->w;
            for (i = 0; i < k; ++i) 
               disponivel[i] = true;
            disponivel[color[w]] = false;
            for (link a = G->adj[w]; a != NULL; a = a->next) {
               i = color[a->w];
               if (i != -1) 
                  disponivel[i] = false;
            }
            for (i = k-1; i >= 0; i--)
               if (disponivel[i]) break;
            if (i >= 0) {
               color[w] = i;
               color[v] = chosen;
            } else {
               k = trocaDeComponentes( G, w, color, chosen, v, k);
            }
         }
      }
   }
   return k;
}


// Função de coloração sequencial com aleatorização na escolha
// dos vértices e na seleção das cores disponíveis e com a troca
// de componentes bicoloridas.
int UGRAPHseqColoringVIII( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) 
      color[v] = -1;
   for (int j = 0; j < G->V; ++j) {
      vertex v = randInteger( 0, G->V - 1);
      while (color[v] != -1)
         v = randInteger( 0, G->V - 1);
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) 
         disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) 
            disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) {
         int r = randInteger( 0, k);
         while (disponivel[r] == false)
            r = randInteger( 0, k);
         color[v] = r;
      } else {
         int* count = mallocc( k * sizeof(int));
         for (link a = G->adj[v]; a!= NULL; a = a->next)
            count[color[a->w]]++;
         int chosen = -1;
         for (i = 0; i < k; i++)
            if (count[i] == 1) chosen = i;
         if (chosen == -1) 
            color[v] = k++;
         else {
            vertex w;
            for (link a = G->adj[v]; a!= NULL; a = a->next)
               if (color[a->w] == chosen)
                  w = a->w;
            k = trocaDeComponentes( G, w, color, chosen, v, k);
         }
      }
   }
   return k;
}


// Função de coloração sequencial com a aleatorização na escolha
// dos vértices e na seleção das cores disponíveis, a troca de
// componentes bicoloridas e a heurística criada pela dupla
// (explicada no relatório).
int UGRAPHseqColoringIX( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) 
      color[v] = -1;
   for (int j = 0; j < G->V; ++j) {
      vertex v = randInteger( 0, G->V - 1);
      while (color[v] != -1)
         v = randInteger( 0, G->V - 1);
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) 
         disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) 
            disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) {
         int r = randInteger( 0, k);
         while (disponivel[r] == false)
            r = randInteger( 0, k);
         color[v] = r;
      } else {
         int* count = mallocc( k * sizeof(int));
         for (link a = G->adj[v]; a!= NULL; a = a->next) {
            if (color[a->w] != -1)
               count[color[a->w]]++;
         }
         int chosen = -1;
         for (i = 0; i < k; i++) {
            if(count[i] == 1) 
               chosen = i;
         }
         if (chosen == -1) 
            color[v] = k++;
         else {
            vertex w;
            for (link a = G->adj[v]; a!= NULL; a = a->next)
               if (color[a->w] == chosen)
                  w = a->w;
            for (i = 0; i < k; ++i) 
               disponivel[i] = true;
            disponivel[color[w]] = false;
            for (link a = G->adj[w]; a != NULL; a = a->next) {
               i = color[a->w];
               if (i != -1) 
                  disponivel[i] = false;
            }
            for (i = 0; i < k; ++i)
               if (disponivel[i]) break;
            if (i < k) {
               int r = randInteger( 0, k);
               while (disponivel[r] == false)
                  r = randInteger( 0, k);
               color[w] = r;
               color[v] = chosen;
            } else {
               k = trocaDeComponentes( G, w, color, chosen, v, k);
            }
         }
      }
   }
   return k;
}

int UGRAPHseqColoringX( UGraph G, int *color)
{
   int k = 0;
   for (vertex v = 0; v < G->V; ++v) 
      color[v] = -1;
   for (vertex v = 0; v < G->V; ++v) {
      bool disponivel[100];
      int i;
      for (i = 0; i < k; ++i) 
         disponivel[i] = true;
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         i = color[a->w];
         if (i != -1) 
            disponivel[i] = false;
      } // A
      for (i = 0; i < k; ++i)
         if (disponivel[i]) break;
      if (i < k) 
         color[v] = i;
      else {
         int* count = mallocc( k * sizeof(int));
         for (link a = G->adj[v]; a!= NULL; a = a->next) {
            if (color[a->w] != -1)
               count[color[a->w]]++;
         }
         int chosen = -1;
         for (i = 0; i < k; i++) {
            if(count[i] == 1) 
               chosen = i;
         }
         if (chosen == -1) 
            color[v] = k++;
         else {
            vertex w;
            for (link a = G->adj[v]; a!= NULL; a = a->next)
               if (color[a->w] == chosen)
                  w = a->w;
            for (i = 0; i < k; ++i) 
               disponivel[i] = true;
            disponivel[color[w]] = false;
            for (link a = G->adj[w]; a != NULL; a = a->next) {
               i = color[a->w];
               if (i != -1) 
                  disponivel[i] = false;
            }
            for (i = k-1; i >= 0; i--)
               if (disponivel[i]) break;
            if (i >= 0) {
               color[w] = i;
               color[v] = chosen;
            } else 
               color[v] = k++;
         }
      }
   }
   return k;
}

void
aplicaColoracao( int (* seqColoring)( UGraph, int *), UGraph G, int * color, int i)
{
   int k;
   double inicio, final;
   printf( "\nTestando a coloração com o algoritmo de coloração %d.\n", i);
   inicio = (double) clock () / CLOCKS_PER_SEC;
   k = seqColoring( G, color);
   final = (double) clock () / CLOCKS_PER_SEC;
   printf( "O algoritmo usou %d cores e demorou %lfs\n", k, final - inicio);
}

int
main( int argc, char *argv[])
{
   if (argc != 4) {
      printf( "Os argumentos foram passados de forma incorreta!\n");
      return (EXIT_FAILURE);
   }
   int V = strtol( argv[1], NULL, 10), E = strtol( argv[2], NULL, 10);
   int s = strtol( argv[3], NULL, 10); srand( s);
   UGraph G = UGRAPHrand1( V, E);
   int *color = mallocc( G->V * sizeof( int));
   int (*funcoes[10])( UGraph, int *) = {
      UGRAPHseqColoringI, UGRAPHseqColoringII, UGRAPHseqColoringIII,
      UGRAPHseqColoringIV, UGRAPHseqColoringV, UGRAPHseqColoringVI,
      UGRAPHseqColoringVII, UGRAPHseqColoringVIII, UGRAPHseqColoringIX,
      UGRAPHseqColoringX 
      };
   for (int i = 0; i < 10; i++) {
      aplicaColoracao( funcoes[i], G, color, i + 1);
   }
   printf("\n");
   return (EXIT_SUCCESS);
}


// RELATÓRIO

// Primeiramente, pudemos perceber com poucos testes que tanto a
// heurística de Brelaz quanto a troca de cores em componentes
// bicoloridas, no geral, de fato auxiliam a colorir o grafo com
// menos cores. Além disso, por mais que levem um tempo maior que
// o guloso, este tempo a mais não é grande, o que faz com que usar
// essas duas técnicas seja algo bom.

// Além dessas duas, também existe uma heurística criada pela dupla,
// baseada tanto no algoritmo guloso quanto no de troca de cores em
// componentes bicoloridas. A ideia é a seguinte: ao encontrar um
// vértice que esteja cercado por todas as cores de 0 a k-1,
// procuramos um vizinho w desse vértice que possua uma cor i tal que
// w seja o único com aquela cor (assim como na troca de cores). Em
// seguida, ao invés de executarmos a troca de cores, primeiro
// tentamos outro método: percorremos os vizinhos de w para encontrar
// uma cor diferente de color[w] que esteja disponível para w (parecido
// com a coloração sequencial). Caso encontremos, fazemos
// color[v] = color[w] e trocamos color[w] para a nova cor encontrada.
// As cores disponíveis são percorridas de trás pra frente, isso é,
// de k-1 a 0, e isto se baseia no seguinte fato: já que na coloração
// sequencial gulosa nós selecionamos a primeira cor disponível da
// esquerda para a direita (0 a k-1), existe uma maior chance de que 
// existam mais elementos com as cores "mais à esquerda". Assim, existe 
// uma chance maior de que os vizinhos de w não possuam as cores "mais
// à direita", de forma que podemos trocar a cor de w para uma dessas
// ao invés de trocar as cores de todos os vértices da componente
// bicolorida.
// Devido a esse fato, no caso em que combinamos essa heurística com a
// aleatorização, ao invés de percorrermos o vetor da direita para a
// esquerda, nós o percorremos de forma aleatória também, pois já que as
// cores disponíveis são escolhidas aleatoriamente, não podemos fazer a
// suposição de que há mais vértices com cores "mais à esquerda", já que
// as cores são escolhidas de modo aleatorio.
// Assim, temos um passo intermediário um pouco mais simples antes de
// tentar executar a troca de cores de componentes bicoloridas, já que
// nosso método troca a cor de apenas um vértice e não de toda a componente.

// Em seguida, combinamos as técnicas entre si para ir gerando novas funções
// de coloração. É claro que a heurística de Brelaz e a aleatorização não
// foram combinadas, pois ambas se baseiam em como escolher o próximo vértice
// da iteração, e, portanto, combinar as duas não faria sentido pois haveria
// duas formas conflitantes de se escolher o próximo vértice.

// Por fim, fizemos diversos testes que nos deram uma ideia de como os
// algoritmos funcionam.
// Primeiro, o teste (V = 10, E = 20, s = 2):
// Testando a coloração com o algoritmo de coloração 1.
// O algoritmo usou 4 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 2.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 3.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 4.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 5.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 6.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 7.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 8.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 9.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 10.
// O algoritmo usou 4 cores e demorou 0.000000s

// Por esse teste, podemos ver que todas as estratégias (com exceção da nossa
// heurística sozinha, foram o suficiente para conseguir reduzir em pelo menos
// uma unidade a coloração do grafo. Isso já é um leve indicativo de que elas
// são uma opção melhor que o guloso.

// O teste (V = 10, E = 10, s = 7):
// Testando a coloração com o algoritmo de coloração 1.
// O algoritmo usou 3 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 2.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 3.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 4.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 5.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 6.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 7.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 8.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 9.
// O algoritmo usou 2 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 10.
// O algoritmo usou 2 cores e demorou 0.000000s


// nos mostra que a nossa heurística pode sim ter pelo menos alguma vantagem
// o que pode ser visto pois ela também reduz o número de cores em relação
// ao guloso.

// Entretanto, nem sempre os métodos conseguem resolver o problema de forma
// mais eficiente. No teste (V = 1000, E = 4000, s = 1530):
// Testando a coloração com o algoritmo de coloração 1.
// O algoritmo usou 7 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 2.
// O algoritmo usou 6 cores e demorou 0.015625s

// Testando a coloração com o algoritmo de coloração 3.
// O algoritmo usou 6 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 4.
// O algoritmo usou 5 cores e demorou 0.156250s

// Testando a coloração com o algoritmo de coloração 5.
// O algoritmo usou 9 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 6.
// O algoritmo usou 6 cores e demorou 0.156250s

// Testando a coloração com o algoritmo de coloração 7.
// O algoritmo usou 6 cores e demorou 0.171875s

// Testando a coloração com o algoritmo de coloração 8.
// O algoritmo usou 6 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 9.
// O algoritmo usou 6 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 10.
// O algoritmo usou 7 cores e demorou 0.000000s

// podemos ver que a aleatorização fez com que a coloração final possuísse
// 2 cores a mais do que a coloração encontrada pelo guloso.

// O método de Brelaz nem sempre é tão eficaz quanto os outros, como podemos
// ver com o teste (V = 100, E = 4000, s = 1530):
// Testando a coloração com o algoritmo de coloração 1.
// O algoritmo usou 36 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 2.
// O algoritmo usou 28 cores e demorou 0.015625s

// Testando a coloração com o algoritmo de coloração 3.
// O algoritmo usou 29 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 4.
// O algoritmo usou 34 cores e demorou 0.015625s

// Testando a coloração com o algoritmo de coloração 5.
// O algoritmo usou 39 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 6.
// O algoritmo usou 28 cores e demorou 0.015625s

// Testando a coloração com o algoritmo de coloração 7.
// O algoritmo usou 29 cores e demorou 0.046875s

// Testando a coloração com o algoritmo de coloração 8.
// O algoritmo usou 29 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 9.
// O algoritmo usou 29 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 10.
// O algoritmo usou 36 cores e demorou 0.000000s

// em que a heurística de Brelaz sozinha reduz a coloração em apenas duas cores,
// enquanto todos os algoritmos que envolvem troca de cores em componentes
// bicoloridas reduzem em 7 ou 8. É interessante notar que a aleatorização
// novamente produz resultados maiores que o guloso, e também que a nossa
// heurística, nesse caso, acaba piorando levemente a troca de cores de
// componentes bicoloridas, deixando com uma cor a mais do que a função com
// a troca de cores apenas.

// Por fim, temos o teste (V = 200, E = 15000, s = 1530):
// Testando a coloração com o algoritmo de coloração 1.
// O algoritmo usou 59 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 2.
// O algoritmo usou 48 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 3.
// O algoritmo usou 46 cores e demorou 0.015625s

// Testando a coloração com o algoritmo de coloração 4.
// O algoritmo usou 53 cores e demorou 0.296875s

// Testando a coloração com o algoritmo de coloração 5.
// O algoritmo usou 61 cores e demorou 0.000000s

// Testando a coloração com o algoritmo de coloração 6.
// O algoritmo usou 48 cores e demorou 0.328125s

// Testando a coloração com o algoritmo de coloração 7.
// O algoritmo usou 46 cores e demorou 0.390625s

// Testando a coloração com o algoritmo de coloração 8.
// O algoritmo usou 46 cores e demorou 0.015625s

// Testando a coloração com o algoritmo de coloração 9.
// O algoritmo usou 46 cores e demorou 0.015625s

// Testando a coloração com o algoritmo de coloração 10.
// O algoritmo usou 57 cores e demorou 0.000000s

// Esse teste é muito interessante pois nos mostra diversas diferenças entre
// os algoritmos. O guloso pinta o grafo com 59 cores, enquanto a aleatorização
// aumenta esse valor para 61. Já a nossa heurística consegue reduzir em duas
// cores a coloração, enquanto Brelaz consegue fazer com 53. Então, temos em
// seguida, com 48 cores, a troca de cores de componentes bicoloridas, tanto
// sozinha quanto com a heurística de brelaz. Por fim, a troca de cores, com
// a nossa heurística, a aleatorização, ou ainda os dois, é capaz de colorir
// o grafo com 46 cores. Assim, temos uma diferença de 13 cores entre ele e
// o guloso, e ainda podemos ver que os algoritmos de fato se comportam de forma
// diferente podendo gerar diversos valores.

// Além disso, quanto ao tempo, é interessante concluir que todos os algoritmos
// são rápidos, mesmo que alguns sejam mais que outros. Assim, para grafos que
// não sejam gigantescos no número de vértices e/ou arestas, usar algoritmos que
// não sejam o guloso é algo muito válido e que pode gerar ótimos resultados.
// Esse tempo rápido provavelmente se deve ao fato de que, mesmo com diversas
// diferenças entre os códigos e cada vez mais adições, todas as funções continuam
// com complexidade O(V + E), isso é, dependentes do número de vértices e arestas
// (edges).



