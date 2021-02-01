/****************************************************************
    Nome:   Victor Pereira Lima
    NUSP:   10737028

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
// import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Quick3way;

import java.lang.IllegalArgumentException;

public class CircularSuffixArray
{
    private class CircularSuffix implements Comparable<CircularSuffix>
    {
        private String s;
        private int firstChar;

        public CircularSuffix(String s, int i)
        {
            this.s = s;
            this.firstChar = i;
        }

        @Override
        public int compareTo(CircularSuffix that)
        {
            int j = that.getFirstChar(), N = s.length();       
            for (int i = 0; i < N; i++) {
                if (s.charAt((this.firstChar + i) % N) > s.charAt((j + i) % N) )
                    return (1);
                if (s.charAt((this.firstChar + i) % N) < s.charAt((j + i) % N) )
                    return (-1);
            }
            return (0); 
        }

        public int getFirstChar()
        {
            return (this.firstChar);
        }
    }

    private int N;
    private int[] index;

    public CircularSuffixArray(String s)
    {
        if (s == null)
            throw new IllegalArgumentException("constructor argument cannot be null");
        N = s.length();
        index = new int[N];
        CircularSuffix[] suffixes = new CircularSuffix[N];
        for (int i = 0; i < N; i++)
            suffixes[i] = new CircularSuffix(s, i);
        Quick3way.sort(suffixes);
        for (int i = 0; i < N; i++) 
            index[i] = suffixes[i].getFirstChar();
    }

    public int length()
    {
        return (N);
    }

    public int index(int i)
    {
        if (i < 0 || i >= N)
            throw new IllegalArgumentException("i is outside prescribed range");
        return (index[i]);
    }

    public static void main(String[] args)
    {
        String s = "ABRACADABRA!";
        CircularSuffixArray c = new CircularSuffixArray(s);
        int j;
        for (int i = 0; i < c.length(); i++) {
            StdOut.println("index() de i = " + c.index(i));
            for (j = 0; j < c.length(); j++)
                StdOut.print(s.charAt((c.index(i) + j) % c.length()));
            StdOut.println();
        }
    }

}