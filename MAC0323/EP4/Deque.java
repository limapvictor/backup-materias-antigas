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

import java.lang.IllegalArgumentException;
import java.lang.UnsupportedOperationException;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item>
{

    private Node inicio, fim;
    private int N;

    private class Node
    {
        Item conteudo;
        Node prox, ant;

        public Node(Item conteudo, Node prox, Node ant)
        {
            this.conteudo = conteudo;
            this.prox = prox; this.ant = ant;
        }
    }

    public Deque()
    {   
        inicio = null; fim = inicio;
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

    public void addFirst(Item item)
    {
        if (item == null)
            throw new IllegalArgumentException();
        else {
            Node novo = new Node(item, inicio, null);
            if (!isEmpty())
                inicio.ant = novo;
            inicio = novo;
            N++;
            if (N == 1) 
                fim = inicio;
        }
    }

    public void addLast(Item item)
    {
        if (item == null)
            throw new IllegalArgumentException();
        else {
            Node novo = new Node(item, null, fim);
            if (!isEmpty())
                fim.prox = novo;
            fim = novo;
            N++;
            if (N == 1) 
                inicio = fim;
        }
    }

    public Item removeFirst()
    {
        if (isEmpty())
            throw new NoSuchElementException();
        else {
            Item item = inicio.conteudo;
            Node lixo = inicio;
            inicio = inicio.prox;
            lixo = null;
            N--;
            if (!isEmpty())
                inicio.ant = null;
            else
                fim = null;
            return (item);
        }
    }
    
    public Item removeLast()
    {
        if (isEmpty())
            throw new NoSuchElementException();
        else {
            Item item = fim.conteudo;
            Node lixo = fim;
            fim = fim.ant; 
            lixo = null;
            N--;
            if (!isEmpty())
                fim.prox = null;
            else
                inicio = null;
            return (item);
        }
    }

    @Override
    public Iterator<Item> iterator()
    {
        Iterator<Item> it = new Iterator<Item>()
        {
            private Node caminho = inicio;

            @Override
            public boolean hasNext()
            {
                return (caminho != null);
            }

            @Override
            public Item next()
            {
                Item item = caminho.conteudo;
                caminho = caminho.prox;
                return (item);
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
        Deque<String> dq = new Deque<String>();
        StdOut.println("Vazio? " + dq.isEmpty() + " Tamanho = " + dq.size());
        dq.addLast("3"); dq.addLast("4"); dq.addFirst("2"); dq.addLast("5"); dq.addFirst("1");
        StdOut.println("Vazio? " + dq.isEmpty() + " Tamanho = " + dq.size());
        
        Iterator<String> it = dq.iterator();
        while (it.hasNext()){
            StdOut.println(it.next());
        }
        StdOut.println("15423 = " + dq.removeFirst() + dq.removeLast() + dq.removeLast() + dq.removeFirst() + dq.removeLast());
        StdOut.println("Vazio? " + dq.isEmpty() + " Tamanho = " + dq.size());
    }
}