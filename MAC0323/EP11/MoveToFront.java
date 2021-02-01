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
import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;
import edu.princeton.cs.algs4.StdOut;

public class MoveToFront
{
    public static final int R = 256;

    public static void encode()
    {
        char[] ascii = new char[R];
        for (int i = 0; i < R; i++)
            ascii[i] = (char)i;
        while (!BinaryStdIn.isEmpty()) {
            char c = BinaryStdIn.readChar();
            int pos = findChar(c, ascii);
            BinaryStdOut.write(pos, 8);
            moveCharToFront(pos, ascii);
        }
        BinaryStdOut.close();
    }

    public static void decode()
    {
        char[] ascii = new char[R];
        for (int i = 0; i < R; i++)
            ascii[i] = (char)i;
        while (!BinaryStdIn.isEmpty()) {
            int pos = BinaryStdIn.readInt(8);
            BinaryStdOut.write(ascii[pos]);
            moveCharToFront(pos, ascii);
        }
        BinaryStdOut.close();
    }

    private static int findChar(char c, char[] ascii)
    {
        int i;
        for (i = 0; i < R && ascii[i] != c; i++);
        return (i);
    }

    private static void moveCharToFront(int pos, char[] ascii)
    {
        char c = ascii[pos];
        int i;
        for (i = pos; i > 0; i--)
            ascii[i] = ascii[i - 1];
        ascii[i] = c;
    }

    public static void main(String[] args)
    {
        if (args[0].compareTo("-") == 0)
            encode();
        else if (args[0].compareTo("+") == 0)
            decode();
    }

}