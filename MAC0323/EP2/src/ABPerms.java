import edu.princeton.cs.algs4.StdOut;

/******************************************************************************
 *
 * MAC0110 - Introdução à Computação
 * Aluno: Lucas Civile Nagamine
 * Numero USP: 7083142
 * Tarefa: Ex. 9 ((a, b)-permutações)
 * Data: 06/06/2017
 *
 * DECLARO QUE SOU O ÚNICO AUTOR E RESPONSaVEL POR ESTE PROGRAMA.  TODAS AS
 * PARTES DO PROGRAMA, EXCETO AS QUE SÃO BASEADAS EM MATERIAL FORNECIDO
 * PELO PROFESSOR OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK & WAYNE,
 * FORAM DESENVOLVIDAS POR MIM.  DECLARO TAMBÉM QUE SOU RESPONSaVEL POR TODAS
 * AS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUi NEM FACILITEI A DISTRIBUIÇÃO
 * DE CÓPIAS DESTE PROGRAMA.
 *
 ******************************************************************************/
public class ABPerms {
    public static int perm(String permutado, String a_permutar, int[] decr, int[] crec, int a, int b, int m) {
        if (a_permutar.equals("")) {
            if (m == 0 || m == 2) StdOut.println(permutado);
            return 1;
        } else {
            int s = 0;

            for (int i = 0; i < a_permutar.length(); i++) {
                char l = a_permutar.charAt(i);
                int ii = permutado.length();

                decr[ii] = 0;
                crec[ii] = 0;

                int max_crec = 0;
                int max_decr = 0;

                for (int j = 0; j < permutado.length(); j++) {
                    if (l > permutado.charAt(j) && decr[ii] < decr[j])
                        decr[ii] = decr[j];
                    if (l < permutado.charAt(j) && crec[ii] < crec[j])
                        crec[ii] = crec[j];

                    if (max_decr < decr[j])
                        max_decr = decr[j];
                    if (max_crec < crec[j])
                        max_crec = crec[j];
                }

                decr[ii]++;
                crec[ii]++;

                if (max_decr < decr[ii]) // AQUI


                    max_decr = decr[ii]; // AQUI
                if (max_crec < crec[ii]) // AQUI
                    max_crec = crec[ii]; // AQUI

                if (max_decr <= a && max_crec <= b)
                    s = s + perm(permutado + l, a_permutar.substring(0, i) + a_permutar.substring(i + 1, a_permutar.length()), decr, crec, a, b, m);
            }

            return s;
        }
    }


    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        int a = Integer.parseInt(args[1]);
        int b = Integer.parseInt(args[2]);
        int m = Integer.parseInt(args[3]);

        String alpha = "abcdefghijklmnopqrstuvwxyz".substring(0, n);

        int[] crec = new int[n];
        int[] decr = new int[n];

        if (m == 0) perm("", alpha, decr, crec, a, b, m);
        else if (m == 1) StdOut.println(perm("", alpha, decr, crec, a, b, m));
        else if (m == 2) StdOut.println(perm("", alpha, decr, crec, a, b, m));
    }
}
