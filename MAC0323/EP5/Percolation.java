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
     A ideia de um representante na UnionFind para o 'topo' e 'fundo' foi discutida em conjunto
    com o aluno João Gabriel Lembo.


    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:

****************************************************************/

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

import java.lang.IllegalArgumentException;

public class Percolation
{
    private boolean[][] grid;
    private int N, topo, fundo, abertos;
    private WeightedQuickUnionUF UF;
    
    public Percolation(int n)
    {
        if (n <= 0)
            throw new IllegalArgumentException();
        grid = new boolean[n][n];
        N = n;
        topo = N * N; fundo = topo + 1; abertos = 0;
        UF = new WeightedQuickUnionUF(fundo + 1);
    }

    public void open(int row, int col)
    {
        if (row < 0 || col < 0 || row >= N || col >= N)
            throw new IllegalArgumentException();
        if (grid[row][col] == false) {
            grid[row][col] = true;
            abertos++;
            if (row == 0 && !UF.connected(N * row + col, topo))    
                UF.union(N * row + col, topo);
            if (row == N - 1 && !UF.connected(N * row + col, fundo))    
                UF.union(N * row + col, fundo);
            if (col + 1 < N && grid[row][col + 1] == true && !UF.connected(N * row + col, N * row + col + 1))
                UF.union(N * row + col, N * row + col + 1);
            if (col - 1 >= 0 && grid[row][col - 1] == true && !UF.connected(N * row + col, N * row + col - 1))
                UF.union(N * row + col, N * row + col - 1);
            if (row + 1 < N && grid[row + 1][col] == true && !UF.connected(N * row + col, N * (row + 1) + col))
                UF.union(N * row + col, N * (row + 1) + col);
            if (row - 1  >= 0 && grid[row - 1][col] == true && !UF.connected(N * row + col, N * (row - 1) + col))
                UF.union(N * row + col, N * (row - 1) + col);
        }
    }

    public boolean isOpen(int row, int col)
    {
        if (row < 0 || col < 0 || row >= N || col >= N)
            throw new IllegalArgumentException();
        return (grid[row][col] == true);
    }

    public boolean isFull(int row, int col)
    {
        if (row < 0 || col < 0 || row >= N || col >= N)
            throw new IllegalArgumentException();
        return (UF.connected(N * row + col, topo));
    }

    public int numberOfOpenSites()
    {
        return (abertos);
    }

    public boolean percolates()
    {
        return (UF.connected(topo, fundo));
    }

    public static void main(String[] args)
    {
        Percolation p = new Percolation(3);
        StdOut.println("Site[0,1] aberto? " + p.isOpen(0, 1) + ". N de sites abertos: " +p.numberOfOpenSites());
        p.open(0, 1); p.open(1, 1); p.open(1, 2);  
        StdOut.println("Site[0,1] aberto? " + p.isOpen(0, 1) + ". N de sites abertos: " +p.numberOfOpenSites());
        StdOut.println("Site[1,0] eh full? "+ p.isFull(1, 0) + ". E o Site[1,2]? " + p.isFull(1, 2));
        StdOut.println("O sistema percola?" + p.percolates());
        p.open(2, 2); 
        StdOut.println("O sistema percola?" + p.percolates());
    }
}