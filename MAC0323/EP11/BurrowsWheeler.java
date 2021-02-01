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

    A resolução da inverseTransform() foi realizada basicamente em cima da ideia da KeyIndexed Sorting vista em 
    https://www.youtube.com/watch?v=S3HjlVv6x7Y&list=PLeipq3NgyTAl20PEUKBXMsoOCE6Q_vkp1&index=80

    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:
    A transform() demora bastante(em torno de 5min no meu PC) em textos grandes como o dickens.txt.

****************************************************************/
import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;
import edu.princeton.cs.algs4.StdOut;

public class BurrowsWheeler
{
    public static final int R = 256;

    public static void transform()
    {
        String s = BinaryStdIn.readString();
        CircularSuffixArray suffixes = new CircularSuffixArray(s);
        int i, N = suffixes.length();
        for (i = 0; suffixes.index(i) != 0; i++);
        BinaryStdOut.write(i);
        for (i = 0; i < N; i++)
            BinaryStdOut.write(s.charAt((suffixes.index(i) + N - 1) % N));
        BinaryStdOut.close();
    }
    
    public static void inverseTransform()
    {
        int first = BinaryStdIn.readInt();
        String t = BinaryStdIn.readString();
        int N = t.length();
        int[] count = new int[R + 1]; int[] next = new int[N]; 
        for (int i = 0; i < N; i++)
            count[t.charAt(i) + 1]++;
        for (int r = 0; r < R; r++)
            count[r + 1] += count[r];
        for (int i = 0; i < N; i++)
            next[count[t.charAt(i)]++] = i;
        for (int i = 0; i < N; i++) {
            BinaryStdOut.write(t.charAt(next[first]));
            first = next[first];
        }
        BinaryStdOut.close();
    }
    public static void main(String[] args)
    {
        if (args[0].compareTo("-") == 0)
            transform();
        else if (args[0].compareTo("+") == 0)
            inverseTransform();
    }

}