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

    O meu método next() foi baseado na forma de se obter a próxima permutação lexográfica
    descrita na página https://www.nayuki.io/page/next-lexicographical-permutation-algorithm

    Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:

****************************************************************/

// excessões pedidas
import java.lang.IllegalArgumentException;
import java.lang.UnsupportedOperationException;
import java.util.NoSuchElementException;

// pode ser útil
import java.util.Arrays; // Arrays.sort(), Arrays.copyOf(), ...

import java.util.Iterator; // passo 0 para criarmos um iterador

import edu.princeton.cs.algs4.StdOut;

public class Arrangements implements Iterable<String>
{

    public int n;
    public String inicial, atual;
    public boolean primeiraVez;

    public void troca(char[] s, int i, int j)
    {
        char aux;
        aux = s[i];
        s[i] = s[j];
        s[j] = aux;
    }

    public String primeiraPermutacao(char[] S)
    {
        int i, j, min;
        for (i = 0; i < n - 1; i++) {
            min = i;
            for (j = i + 1; j < n; j++) {
                if(S[j] < S[min])
                    min = j;
            }
            if (S[i] != S[min])
                troca(S, i, min);
        }
        return (String.valueOf(S));
    }

    public Arrangements(String S)
    {
        if (S != null) {
            n = S.length();
            inicial = primeiraPermutacao(S.toCharArray());
            atual = inicial;
            primeiraVez = true;
        } else 
            throw new IllegalArgumentException();
    }

    @Override
    public Iterator<String> iterator()
    {
        Iterator<String> it = new Iterator<String>()
        {
            @Override
            public boolean hasNext()
            {
                boolean ultima = true;
                for (int i = 0; i < n; i++) {
                    if (inicial.charAt(i) != atual.charAt(n - i - 1))
                        ultima = false;
                }
                return (!ultima);
            }

            @Override
            public String next()
            {
                if (!primeiraVez) {
                    int i = n - 1, j = n - 1;
                    char[] perm = atual.toCharArray();
                    while (i > 0 && perm[i - 1] >= perm[i])
                        i--;
                    while (perm[j] <= perm[i - 1])
                        j--;
                    troca(perm, i - 1, j);
                    j = n - 1;
                    while (i < j) {
                        troca(perm, i, j);
                        i++; j--;
                    }
                    atual = String.valueOf(perm);
                } else {
                    primeiraVez = false;
                }
                return atual;
            }
            
            @Override
            public void remove()
            {
                throw new UnsupportedOperationException();
            }
        };
        return it;
    }
    
    // Unit test
    public static void main(String[] args)
    {
        String s = args[0];
        Arrangements arr = new Arrangements(s);
        
        StdOut.println("Teste 1: imprime no máximo os 10 primeiros arranjos");
        Iterator<String> it = arr.iterator();
        for (int i = 0; it.hasNext() && i < 10; i++) {
            StdOut.println(i + " : " + it.next());
        }
        
        StdOut.println("Teste 2: imprime todos os arranjos");
        int i = 0;
        arr.primeiraVez = true; arr.atual = arr.inicial; //para reiniciar o iterator
        for (String arranjo: arr) {
            StdOut.println(i + " : " + arranjo);
            i++;
        }
    }
}
