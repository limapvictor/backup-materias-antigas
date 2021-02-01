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
 O método da permutação foi baseado na "inspiração para o EP2" mandado na página do exercicio.


 Se for o caso, descreva a seguir 'bugs' e limitações do seu programa:
 ****************************************************************/

import edu.princeton.cs.algs4.StdOut;

/******************************************************************************
 *  Compilation:  javac-algs4 STPerms.java
 *  Execution:    java STPerms n s t opcao
 *
 *  Enumera todas as (s,t)-permutações das n primeiras letras do alfabeto.
 *  As permutações devem ser exibidas em ordem lexicográfica.
 *  Sobre o papel da opcao, leia o enunciado do EP.
 *
 *  % java STPerms 4 2 2 0
 *  badc
 *  bdac
 *  cadb
 *  cdab
 *  % java STPerms 4 2 2 1
 *  4
 *  % java STPerms 4 2 2 2
 *  badc
 *  bdac
 *  cadb
 *  cdab
 *  4
 *
 ******************************************************************************/

public class STPerms {

    public static int permutar(String prefixo, String aux, int s, int t, int[] cresc, int[] decresc, boolean printar) {
        if (aux.equals("")) {
            if (printar)
                StdOut.println(prefixo);
            return 1;
        } else {
            int nPerm = 0;
            for (int i = 0; i < aux.length(); i++) {
                char atual = aux.charAt(i);
                int tam = prefixo.length();
                int maxCresc = 0, maxDecresc = 0;
                cresc[tam] = 0;
                decresc[tam] = 0;
                for (int j = 0; j < tam; j++) {
                    if (atual < prefixo.charAt(j) && cresc[tam] < cresc[j])
                        cresc[tam] = cresc[j];
                    if (atual > prefixo.charAt(j) && decresc[tam] < decresc[j])
                        decresc[tam] = decresc[j];
                    if (cresc[j] > maxCresc)
                        maxCresc = cresc[j];
                    if (decresc[j] > maxDecresc)
                        maxDecresc = decresc[j];
                }
                cresc[tam]++;
                decresc[tam]++;
                if (cresc[tam] > maxCresc)
                    maxCresc = cresc[tam];
                if (decresc[tam] > maxDecresc)
                    maxDecresc = decresc[tam];
                if (maxCresc <= t && maxDecresc <= s)
                    nPerm = nPerm + permutar(prefixo + atual, aux.substring(0, i) + aux.substring(i + 1, aux.length()), s, t, cresc, decresc, printar);
            }
            return nPerm;
        }
    }

    public static void main(String[] args) {
        if (args.length != 4) {
            StdOut.print("Os argumentos não foram passados corretamente!");
            return;
        }
        int n = Integer.parseInt(args[0]);
        int s = Integer.parseInt(args[1]), t = Integer.parseInt(args[2]);
        int opcao = Integer.parseInt(args[3]);
        int p;
        String subSeq = "abcdefghijklmnopqrstuvwxyz".substring(0, n);
        int[] cresc = new int[n], decresc = new int[n];
        if (opcao != 1) {
            p = permutar("", subSeq, s, t, cresc, decresc, true);
            if (opcao != 0)
                StdOut.println(p);
        } else {
            p = permutar("", subSeq, s, t, cresc, decresc, false);
            StdOut.println(p);
        }
    }
}
