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
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.MaxPQ;

import java.lang.IllegalArgumentException;

public class KdTreeST<Value> 
{
    private class Node implements Comparable<Node>
    {
        private Point2D p;      
        private Value val;
        private RectHV rect; 
        private Node leftBottom, rightTop;
        private boolean orientacao; //caso true orientação pela Key x, caso false orientação pela Key y
        private double dist;

        public Node(Point2D p, Value val, RectHV rect, boolean orientacao)
        {
            this.p = p;
            this.val = val;
            this.rect = rect;
            this.orientacao = orientacao;
            dist = 1;
        }

        public void distanciaAoPonto(Point2D q)
        {
            this.dist = this.p.distanceSquaredTo(q);
        }

        @Override
        public int compareTo(Node x)
        {
            if (this.dist > x.dist)
                return (1);
            return (-1);
        }

    }
    private static final boolean HORIZONTAL = true; private static final boolean VERTICAL = false;
    private Node raiz;
    private int N, contProx;

    public KdTreeST()
    {
        raiz = null;
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

    public void put(Point2D p, Value val)
    {
        if (p == null || val == null)
            throw new IllegalArgumentException();
        raiz = put(raiz, p, val, HORIZONTAL, 0, 0, 1, 1);
    }

    public Value get(Point2D p)
    {
        if (p == null)
            throw new IllegalArgumentException();
        Node x = get(raiz, p);
        if (x == null)
            return (null);
        return (x.val);
    }

    public boolean contains(Point2D p)
    {
        if (p == null)
            throw new IllegalArgumentException();
        return (this.get(p) != null);
    }

    public Iterable<Point2D> points()
    {
        if (raiz == null)
            return (null);
        Node aux;
        Queue<Node> nos = new Queue<Node>(); 
        Queue<Point2D> pontos = new Queue<Point2D>();
        nos.enqueue(raiz); pontos.enqueue(raiz.p);
        while(!nos.isEmpty()) {
            aux = nos.dequeue();
            if (aux.leftBottom != null) {
                nos.enqueue(aux.leftBottom);
                pontos.enqueue(aux.leftBottom.p);
            }
            if (aux.rightTop != null) {
                nos.enqueue(aux.rightTop);
                pontos.enqueue(aux.rightTop.p);
            }
        }
        return (pontos);
    }

    public Iterable<Point2D> range(RectHV rect)
    {
        if (rect == null)
            throw new IllegalArgumentException();
        if (raiz == null)
            return (null);
        Queue<Point2D> pontos = new Queue<Point2D>();
        range(raiz, rect, pontos);
        return (pontos);
    }

    public Iterable<Point2D> nearest(Point2D p, int k)
    {
        if (p == null || k <= 0)
            throw new IllegalArgumentException();
        if (raiz == null)
            return (null);
        contProx = 0;
        MaxPQ<Node> nos = new MaxPQ<Node>();
        Queue<Point2D> pontos = new Queue<Point2D>();
        nearest(raiz, p, k,  nos);
        for (Node x: nos)
            pontos.enqueue(x.p);
        return (pontos);
    }

    private Node put(Node x, Point2D p, Value val, boolean orientacao, double xmin, double ymin, double xmax, double ymax)
    {
        if (x == null) {
            N++;
            return (new Node(p, val, new RectHV(xmin, ymin, xmax, ymax), orientacao));
        }
        int cmp = compara(p, x.p, x.orientacao);
        if (cmp < 0) {
                if (orientacao == HORIZONTAL)
                    x.leftBottom = put(x.leftBottom, p, val, !x.orientacao, xmin, ymin, x.p.x(), ymax);
                else 
                    x.leftBottom = put(x.leftBottom, p, val, !x.orientacao, xmin, ymin, xmax, x.p.y());
        } else if (cmp > 0) { 
            if (orientacao == HORIZONTAL)
                x.rightTop = put(x.rightTop, p, val, !x.orientacao, x.p.x(), ymin, xmax, ymax);
            else
                x.rightTop = put(x.rightTop, p, val, !x.orientacao, xmin, x.p.y(), xmax, ymax);
        }
        x.val = val;
        return (x);
        
    }

    private Node get(Node x, Point2D p)
    {
        if (x == null)
            return (null);
        int cmp = compara(p, x.p, x.orientacao);
        if (cmp < 0)
            return (get(x.leftBottom, p));
        else if (cmp > 0)
            return (get(x.rightTop, p));
        return (x);
    }

    private void range(Node x, RectHV rect, Queue<Point2D> pontos)
    {
            if (rect.contains(x.p))
                pontos.enqueue(x.p);
            if (x.leftBottom != null && rect.intersects(x.leftBottom.rect))
                range(x.leftBottom, rect, pontos);
            if (x.rightTop != null && rect.intersects(x.rightTop.rect))
                range(x.rightTop, rect, pontos);
    }
    
    private void nearest(Node x, Point2D p, int k, MaxPQ<Node> nos)
    {
        if (contProx < k || x.p.distanceSquaredTo(p) < nos.max().p.distanceSquaredTo(p)) {
            if (contProx == k) {
                nos.delMax();
                contProx--;
            }
            contProx++;
            x.distanciaAoPonto(p);
            nos.insert(x);
        }
        if (contProx < k || (x.leftBottom != null && x.leftBottom.rect.distanceSquaredTo(p) < nos.max().p.distanceSquaredTo(p)))
            nearest(x.leftBottom, p, k, nos);
        if (contProx < k || (x.rightTop != null && x.rightTop.rect.distanceSquaredTo(p) < nos.max().p.distanceSquaredTo(p)))
            nearest(x.rightTop, p, k, nos);
    }
    
    private int compara(Point2D p, Point2D q, boolean orientacao)
    {
        if (orientacao == HORIZONTAL) {
            if (p.x() < q.x())
                return (-1);
            else if (p.x() > q.x())
                return (1);
            return (0);
        } else {
            if (p.y() < q.y())
                return (-1);
            else if (p.y() > q.y())
                return (1);
            return (0);
        }
    }

    public static void main(String[] args)
    {
        In arquivo = new In(args[0]);
        KdTreeST<Integer> arv = new KdTreeST<Integer>();
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
        StdOut.println("Todos os pontos inseridos por nível:");
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