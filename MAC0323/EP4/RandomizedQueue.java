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
import java.util.Iterator;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

import java.lang.IllegalArgumentException;
import java.lang.UnsupportedOperationException;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item>
{
    private Item[] queue;
    private int N;

    public RandomizedQueue(int max)
    {
        queue = (Item[]) new Object[max];
        N = 0;
    }

    public boolean isEmpty()
    {
        return (N == 0);
    }

    public int size()
    {
        return (N);
    }

    public void enqueue(Item item)
    {
        if (item == null)
            throw new IllegalArgumentException();
        queue[N++] = item;
    }

    public Item dequeue()
    {
        if (this.isEmpty())
            throw new NoSuchElementException();
        int i = StdRandom.uniform(0, N);
        Item item = queue[i];
        queue[i] = queue[--N];
        queue[N] = null;
        return (item);
    }

    public Item sample()
    {
        if (this.isEmpty())
            throw new NoSuchElementException();
        int i = StdRandom.uniform(0, N);
        return (queue[i]);
    }

    @Override
    public Iterator<Item> iterator()
    {
        Iterator<Item> it = new Iterator<Item>()
        {
            private int i = 0;
            private Item[] rQueue = embaralha(queue);
            
            private Item[] embaralha(Item[] queue)
            {
                Item[] q = (Item[]) new Object[N];
                for (int i = 0; i < N; i++) {
                    q[i] = queue[i];
                }
                StdRandom.shuffle(q);
                return(q);
            }

            @Override
            public boolean hasNext()
            {
                return (i < N);
            }

            @Override
            public Item next()
            {
                if (!hasNext())
                    throw new NoSuchElementException();
                else {
                    Item item = rQueue[i++];
                    return (item);
                }
            }

            @Override
            public void remove()
            {
                throw new UnsupportedOperationException();
            }
        };
        return (it);
    }

    public static void main(String[] args)
    {
        RandomizedQueue<String> q = new RandomizedQueue<String>(5);
        StdOut.println("A fila esta vazia ? " + q.isEmpty() + " Tamanho da fila = " + q.size());
        q.enqueue("esse"); q.enqueue("texto"); q.enqueue("eh"); q.enqueue("aleatorio");
        StdOut.println("A fila esta vazia ? " + q.isEmpty() + " Tamanho da fila = " + q.size());
        StdOut.println(q.sample() + " " + q.sample() + " " + q.sample() + " " + q.sample()); 
        StdOut.println("A fila esta vazia ? " + q.isEmpty() + " Tamanho da fila = " + q.size());

        Iterator<String> it = q.iterator();
        while (it.hasNext()){
            StdOut.println(it.next());
        }
        StdOut.println(q.dequeue() + " " + q.dequeue() + " " + q.dequeue() + " " + q.dequeue());
        StdOut.println("A fila esta vazia ? " + q.isEmpty() + " Tamanho da fila = " + q.size());
    }
}