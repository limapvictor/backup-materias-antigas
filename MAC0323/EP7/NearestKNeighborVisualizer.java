/******************************************************************************
 *  Compilation:  javac NearestNeighborVisualizer.java
 *  Execution:    java NearestNeighborVisualizer input.txt
 *  Dependencies: PointST.java KdTreeST.java
 *
 *  Read points from a file (specified as a command-line argument) and
 *  draw to standard draw. Highlight the closest point to the mouse.
 *
 *  The nearest neighbor according to the brute-force algorithm is drawn
 *  in red; the nearest neighbor using the kd-tree algorithm is drawn in blue.
 *
 ******************************************************************************/

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.StdDraw;

public class NearestKNeighborVisualizer {

    public static void main(String[] args) {
        String filename = args[0];
        In in = new In(filename);
        int k = Integer.parseInt(args[1]);

        StdDraw.show(0);

        // initialize the two data structures with point from standard input
        PointST<Integer> brute = new PointST<Integer>();
        KdTreeST<Integer> kdtree = new KdTreeST<Integer>();
        for (int i = 0; !in.isEmpty(); i++) {
            double x = in.readDouble();
            double y = in.readDouble();
            Point2D p = new Point2D(x, y);
            kdtree.put(p, i);
            brute.put(p, i);
        }

        while (true) {

            // the location (x, y) of the mouse
            double x = StdDraw.mouseX();
            double y = StdDraw.mouseY();
            Point2D query = new Point2D(x, y);

            // draw all of the points
            StdDraw.clear();
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.setPenRadius(0.01);
            for (Point2D p : brute.points())
                p.draw();

            // draw in red the nearest neighbor according to the brute-force algorithm
            // StdDraw.setPenRadius(0.03);
            // StdDraw.setPenColor(StdDraw.RED);
            // Iterable<Point2D> kNearest = brute.nearest(query, k);
            // for (Point2D p: kNearest) p.draw();
            // StdDraw.setPenRadius(0.02);

            // draw in blue the nearest neighbor according to the kd-tree algorithm
            StdDraw.setPenColor(StdDraw.BLUE);
            kNearest = kdtree.nearest(query, k);
            for (Point2D p: kNearest) p.draw();
            StdDraw.show(0);
            StdDraw.show(40);
        }
    }
}
