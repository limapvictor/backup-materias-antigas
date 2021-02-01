/****************************************************************
    Nome: Victor Pereira Lima
    NUSP: 10737028

    Ao preencher esse cabeçalho com o meu nome e o meu número USP,
    declaro que todas as partes originais desse exercício programa (EP)
    foram desenvolvidas e implementadas por mim e que portanto não 
    constituem desonestidade acadêmica ou plágio.
    Declaro também que sou responsável por todas as cópias desse
    programa e que não distribui ou facilitei a sua distribuição.
    Estou ciente que os casos de plágio e desonestidade acadêmica
    serão tratados segundo os critérios divulgados na página da 
    disciplina.
    Entendo que EPs sem assinatura devem receber nota zero e, ainda
    assim, poderão ser punidos por desonestidade acadêmica.

    Abaixo descreva qualquer ajuda que você recebeu para fazer este
    EP.  Inclua qualquer ajuda recebida por pessoas (inclusive
    monitoras e colegas). Com exceção de material de MAC0323, caso
    você tenha utilizado alguma informação, trecho de código,...
    indique esse fato abaixo para que o seu programa não seja
    considerado plágio ou irregular.

    Exemplo:

        A monitora me explicou que eu devia utilizar a função xyz().

        O meu método xyz() foi baseada na descrição encontrada na 
        página https://www.ime.usp.br/~pf/algoritmos/aulas/enumeracao.html.

    Descrição de ajuda ou indicação de fonte:

    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:

****************************************************************/

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

import java.util.LinkedList;

public class Board 
{
    private int N, man, ham;
    private int[][] tabuleiro;

    public Board(int[][] tiles)
    {
        N = tiles.length;
        tabuleiro = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                tabuleiro[i][j] = tiles[i][j];
            }
            tiles[i] = null;
        }
        tiles = null;
        ham = this.hamming(); man = this.manhattan();
    }

    public String toString()
    {
        String tab = N + "\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                tab += " " + tabuleiro[i][j];
            tab += "\n";
        }
        return (tab);
    }

    public int tileAt(int row, int col)
    {
        if (row < 0 || row >= N || col < 0 || col >= N)
            throw new IllegalArgumentException();
        return (tabuleiro[row][col]);
    }

    public int size()
    {
        return (N);
    }

    public int hamming()
    {
        int errados = 0, i, j;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (tabuleiro[i][j] != 0 && tabuleiro[i][j] != N * i + j + 1)
                    errados++;
            }
        }
        return (errados);
    }

    public int manhattan()
    {
        int distancia = 0, i, j, distVer, distHor;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (tabuleiro[i][j] != 0) {
                    distVer = ((tabuleiro[i][j] - 1) / N) - i;
                    distHor = ((tabuleiro[i][j] - 1) % N) - j;
                    distancia += abs(distVer) + abs(distHor);
                }
            }
        }
        return (distancia); 
    }

    public boolean isGoal()
    {
        return (this.ham == 0);
    }

    public boolean equals(Object y)
    {
        if (y ==null || y.getClass() != this.getClass())
            return (false);
        if (y == this)
            return (true);
        Board comp = (Board) y;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (tabuleiro[i][j] != comp.tileAt(i,j))
                    return (false);
        return (true);
    }

    public Iterable<Board> neighbors()
    {
        LinkedList<Board> vizinhos = new LinkedList<Board>();
        int lin = achaQuadrado()[0], col = achaQuadrado()[1];
        if (lin != 0)
            vizinhos.add(new Board(moveQuadrado(lin, col, lin - 1, col)));
        if (lin != N - 1)
            vizinhos.add(new Board(moveQuadrado(lin, col, lin + 1, col)));
        if (col != 0)
            vizinhos.add(new Board(moveQuadrado(lin, col, lin, col - 1)));
        if (col != N - 1)
            vizinhos.add(new Board(moveQuadrado(lin, col, lin, col + 1)));
        return (vizinhos);
    }

    public boolean isSolvable()
    {
        int inversoes = contaInversoes(), linhaQuad = achaQuadrado()[0];
        boolean soluciona = false;
        if (N % 2 == 1 && inversoes % 2 == 0)
            soluciona = true;
        if (N % 2 == 0 && (inversoes + linhaQuad) % 2 == 1)
            soluciona = true;
        return (soluciona);
    }

    private int abs(int a)
    {
        if (a < 0)
            a = -1 * a;
        return (a);
    }

    private int contaInversoes()
    {
        int cont = 0, i, j, i2, j2, aux;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                for (i2 = i; i2 < N; i2++) {
                    if (i2 == i)
                        aux = j + 1;
                    else    
                        aux = 0;
                    for (j2 = aux; j2 < N; j2++) {
                        if (tabuleiro[i][j] != 0 && tabuleiro[i2][j2] != 0 && tabuleiro[i][j] > tabuleiro[i2][j2])
                            cont += 1;
                    }
                }
            }
        }
        return (cont);
    }

    private int[] achaQuadrado()
    {
        boolean achou = false;
        int[] pos = new int[2];
        for (int i = 0; i < N && !achou; i++) {
            for (int j = 0; j < N && !achou; j++) {
                if (tabuleiro[i][j] == 0) {
                    pos[0] = i; pos[1] = j;
                    achou = true;
                }
            }
        }
        return (pos);
    }

    private int[][] moveQuadrado(int linIni, int colIni, int linFim, int colFim)
    {
        int aux, i, j;
        int[][] copia = new int[N][N];
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                copia[i][j] = tabuleiro[i][j];
            }
        }
        aux = copia[linFim][colFim];
        copia[linFim][colFim] = copia[linIni][colIni];
        copia[linIni][colIni] = aux;
        return (copia);
    }

    public static void main(String args[])
    {
        int n = StdIn.readInt(), i, j;
        int[][] tiles = new int[n][n];
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                tiles[i][j] = StdIn.readInt();
        }
        Board b = new Board(tiles);
        StdOut.print(b.toString());
        StdOut.println("Distancia Hamming = " + b.hamming());
        StdOut.println("Distancia Manhattan = " + b.manhattan());
        StdOut.println("O tabuleiro está organizado? " + b.isGoal());
        StdOut.println("O tabuleiro possui solução? " + b.isSolvable());
        StdOut.println("Vizinhos do tabuleiro:");
        for (Board vizinho : b.neighbors()) {
            StdOut.print(vizinho.toString());
        }
    }
}