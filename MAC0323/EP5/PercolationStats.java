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

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.Stopwatch;
import java.lang.Math;

import java.lang.IllegalArgumentException;

public class PercolationStats
{
    private int N, T;
    private double[] experimentos;
    private Percolation P;

    public PercolationStats(int n, int trials)
    {
        if (n <= 0 || trials <= 0)
            throw new IllegalArgumentException();
        N = n; T = trials;
        experimentos = new double[T];
        double quad = N * N;
        for (int i = 0; i < T; i++) {
            P = new Percolation(N);
            while (!P.percolates()) {
                P.open(StdRandom.uniform(N), StdRandom.uniform(N));
            }
            experimentos[i] = P.numberOfOpenSites() / quad;
        }
    }

    public double mean()
    {
        double soma = 0;
        for (int i = 0; i < T; i++)
            soma += experimentos[i];
        return (soma / T);
    }

    public double stddev()
    {
        double media = mean(), soma = 0, xt;
        for (int i = 0; i < T; i++) {
            xt = Math.pow(experimentos[i] - media, 2);
            soma += xt;
        }
        return (Math.sqrt(soma / T));
    }

    public double confidenceLow()
    {
        return (mean() - ((1.96 * stddev()) / Math.sqrt(T)));
    }

    public double confidenceHigh()
    {
        return (mean() + ((1.96 * stddev()) / Math.sqrt(T)));
    }

    public static void main(String args[])
    {
        int n = Integer.parseInt(args[0]), t = Integer.parseInt(args[1]);
        Stopwatch timer = new Stopwatch();
        PercolationStats ps = new PercolationStats(n, t);
        StdOut.println("mean()            = " + ps.mean());
        StdOut.println("stddev()          = " + ps.stddev());
        StdOut.println("confidenceLow()   = " + ps.confidenceLow());
        StdOut.println("confidenceHigh()  = " + ps.confidenceHigh());
        StdOut.println("elapsed time      = " + timer.elapsedTime());
    }
}