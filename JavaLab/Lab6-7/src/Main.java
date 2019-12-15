public class Main {


    public static void main(String[] args)
    {

        Point p1 = new Point(7,2);
        Point p2 = new Point (4,3);
        Point.calcDistanceBetweenPoints(p1,p2);
        Point p3 = new Point (9,14);
        Point.ChangeLocation(p3,6,3);
        Point p4 = new Point(13,5);
        Point.calcDistanceToOrigin(p4);


    }
}
