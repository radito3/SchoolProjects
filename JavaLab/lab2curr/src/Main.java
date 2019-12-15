import java.util.Currency;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

            Scanner a = new Scanner(System.in);

            System.out.println(" Please choose a currency!");
            System.out.println("Press 1 for : LEV");
            System.out.println("Press 2 for : GBT");
            System.out.println("Press 3 for : EUR");
            int currencyType = a.nextInt();
            boolean loop = false;

            System.out.println("Please enter value!");
            double value = a.nextInt();

            double LEV = value * 0.56;
            double GBT = value * 1.24;
            double EUR = value * 1.1;

            if (currencyType == 1) {
                System.out.println("LEV to USD: " + LEV);
            }
            if (currencyType == 2) {
                System.out.println("GBT to USD: " + GBT);
            }
            if (currencyType == 3) {
                System.out.println("EUR to USD: " + EUR);
            }

    }
}
