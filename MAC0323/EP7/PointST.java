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
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.RedBlackBST;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.MaxPQ;

import java.lang.IllegalArgumentException;

public class PointST<Value>
{
    private class Node implements Comparable<Node>
    {
        Point2D p;
        double distancia;
        
        public Node(Point2D p, double dist)
        {
            this.p = p;
            distancia = dist;
        }

        @Override
        public int compareTo(Node x)
        {
            if (this.distancia > x.distancia)
                return (1);
            return (-1);
        }
    }
    private RedBlackBST<Point2D, Value> arvore;

    public PointST()
    {
        arvore = new RedBlackBST<Point2D, Value>();
    }

    public boolean isEmpty()
    {
        return (arvore.isEmpty());
    }

    public int size()
    {
        return (arvore.size());
    }

    public void put(Point2D p, Value val)
    {
        if (p == null || val == null)
            throw new IllegalArgumentException();
        arvore.put(p, val);
    }

    public Value get(Point2D p)
    {
        if (p == null)
            throw new IllegalArgumentException();
        return (arvore.get(p));
    }

    public boolean contains(Point2D p)
    {
        if (p == null)
            throw new IllegalArgumentException();
        return (arvore.contains(p));
    }

    public Iterable<Point2D> points()
    {
        return (arvore.keys());
    }

    public Iterable<Point2D> range(RectHV rect)
    {
        if (rect == null)
            throw new IllegalArgumentException();
        Queue<Point2D> pontos = new Queue<Point2D>();
        for (Point2D ponto: this.points()) {
            if (rect.contains(ponto))
                pontos.enqueue(ponto);
        }
        return (pontos);
    }

    public Iterable<Point2D> nearest(Point2D p, int k)
    {
        if (p == null || k <= 0)
            throw new IllegalArgumentException();
        if (this.isEmpty())
            return (null);
        MaxPQ<Node> nos = new MaxPQ<Node>();
        Queue<Point2D> pontos = new Queue<Point2D>();
        int cont = 0;
        for (Point2D ponto: this.points()) {
            if (cont < k || ponto.distanceSquaredTo(p) < nos.max().p.distanceSquaredTo(p)){
                if (cont == k) {
                    nos.delMax();
                    cont--;
                }
                cont++;
                nos.insert(new Node(ponto, ponto.distanceSquaredTo(p)));    
            }
        }
        for (Node x: nos)
            pontos.enqueue(x.p);
        return (pontos);
    }
    // public Point2D nearest(Point2D p, int k)
    // {
    //     if (p == null)
    //         throw new IllegalArgumentException();
    //     if (this.isEmpty())
    //         return (null);
    //     Point2D proximo = null;
    //     for (Point2D ponto: this.points()) {
    //         if (ponto.compareTo(p) != 0) {
    //             if (proximo == null || p.distanceSquaredTo(ponto) < p.distanceSquaredTo(proximo))
    //                 proximo = ponto;
    //         }
    //     }
    //     return (proximo);
    // }
    
    public static void main(String[] args)
    {
        In arquivo = new In(args[0]);
        PointST<Integer> arv = new PointST<Integer>();
        double x, y;
        Point2D p = null;
        StdOut.println("Pontos na árvore = " + arv.size() + " -> A árvore está vazia? " + arv.isEmpty());
        for (int i = 0; !arquivo.isEmpty(); i++) {
            x = arquivo.readDouble(); y = arquivo.readDouble();
            p = new Point2D(x, y);
            arv.put(p, i);
        }
        StdOut.println("Pontos na árvore = " + arv.size() + " -> A árvore está vazia? " + arv.isEmpty());
        StdOut.println("Valor associado ao último ponto inserido = " + arv.get(p));
        StdOut.print("A árvore contém o ponto " + p.toString() + " ? "  + arv.contains(p));
        StdOut.println(".E o ponto (0,0) ? " + arv.contains(new Point2D(0,0)));
        StdOut.println("Todos os pontos inseridos:");
        for (Point2D ponto: arv.points())
            StdOut.println(ponto.toString());
        RectHV ret = new RectHV(0, 0, 0.5, 0.5);
        StdOut.println("Pontos contidos no retângulo:");
        for (Point2D ponto: arv.range(ret))
            StdOut.println(ponto.toString());
        StdOut.println("Os 5 pontos mais próximos de " + p.toString() + " são os pontos: ");
        for(Point2D ponto: arv.nearest(p, 5))
            StdOut.println(ponto.toString());
    }
}
