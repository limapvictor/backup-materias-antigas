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
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.Stack;

import java.lang.IllegalArgumentException;


public class Solver
{
    private class SearchNode implements Comparable<SearchNode>
    {
        Board tab;
        SearchNode anterior;
        int movimentos, prioridade;

        public SearchNode(Board atual, SearchNode ant, int mov) 
        {
            tab = atual;
            anterior = ant;
            movimentos = mov; 
            prioridade = tab.manhattan() + movimentos;
        }

        @Override
        public int compareTo(SearchNode j)
        {
            if (this.prioridade > j.prioridade)
                return (1);
            return (-1);
        }
    }

    SearchNode inicio, min;
    MinPQ<SearchNode> filaPr;

    public Solver(Board initial)
    {
        if (initial == null || !initial.isSolvable())
            throw new IllegalArgumentException("Unsolvable puzzle");
        inicio = new SearchNode(initial, null, 0); min = inicio;
        filaPr = new MinPQ<>();
        filaPr.insert(inicio);
        while (!min.tab.isGoal()) {
            min = filaPr.delMin();
            for (Board vizinho : min.tab.neighbors()) {
                filaPr.insert(new SearchNode(vizinho, min, min.movimentos + 1));
            }
        }
    }

    public int moves()
    {
        return (min.movimentos);
    }

    public Iterable<Board> solution()
    {
        Stack<Board> solucao = new Stack<Board>();
        SearchNode p = min;
        while (p != null) { 
            solucao.push(p.tab);
            p = p.anterior;
        }
        return (solucao);
    }
    
    public static void main(String[] args)
    {
        int n = StdIn.readInt(), i, j;
        int[][] tiles = new int[n][n];
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++)
                tiles[i][j] = StdIn.readInt();
        }
        Board b = new Board(tiles);
        Solver s = new Solver(b);
        StdOut.println("Minimum number of moves = " + s.moves());
        for (Board t: s.solution())
            StdOut.println(t.toString());
    }
}