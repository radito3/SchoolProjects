public class Point
{
    int x;
    int y;

    public Point(int x,int y)
    {
        this.x = x;
        this.y = y;
    }

    public static void ChangeLocation(Point p,int newX, int newY)
    {
        p.x = newX;
        p.y = newY;
        System.out.println("The point's location is set to ("+newX+","+newY+")");
    }

    public static void calcDistanceBetweenPoints (Point firstPoint,Point secondPoint)
    {  double formula1 = (secondPoint.x-firstPoint.x);
    double res1 = Math.pow(formula1,2);
    double formula2 = (secondPoint.y-firstPoint.y);
    double res2 = Math.pow(formula2,2);
    double formula = Math.sqrt(res1 + res2);
       System.out.println("The distance between the points is " + formula);
    }
    public static void calcDistanceToOrigin (Point firstPoint)
    {   double formula1 = (0-firstPoint.x);
        double res1 = Math.pow(formula1,2);
        double formula2 = (0-firstPoint.y);
        double res2 = Math.pow(formula2,2);
        double formula = Math.sqrt(res1 + res2);
        System.out.println("The distance from the origin is " + Math.abs(formula));
    }
}
