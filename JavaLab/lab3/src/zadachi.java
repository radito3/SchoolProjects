import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.DayOfWeek;
import java.util.Calendar;
import java.util.Date;
import java.util.Scanner;

public class zadachi {


    public static void main(String[] args) {
        boolean loop = true;
        Calendar currentDay = Calendar.getInstance();
        do {

            System.out.println("1.Use today's date.");
            System.out.println("2.Use other date.");
            System.out.println("3.Exit.");
            Scanner scan = new Scanner(System.in);

            int choice = scan.nextInt();
            int howManyDaysAhead;

            switch (choice) {
                case 1:
                    System.out.println("Please enter for how many days you want to check: ");
                    howManyDaysAhead = scan.nextInt();

                    int todayDay = currentDay.get(Calendar.DAY_OF_WEEK);

                    int futureDay = (todayDay + howManyDaysAhead) % 7;

                    System.out.println("After " + howManyDaysAhead + " days it will be " + DayOfWeek.of(futureDay));
                    break;

                case 2:
                    System.out.println("Please enter a day for a starting point: dd/mm/yyyy");
                    String ChosenDate = scan.next();

                    Date date1 = null;
                    try {
                        date1 = new SimpleDateFormat("dd/mm/yyyy").parse(ChosenDate);
                    } catch (ParseException e) {
                        e.printStackTrace();
                    }

                    currentDay.setTime(date1);

                    //int futureDate = date1.get(Calendar.DAY_OF_WEEK);

                    System.out.println("Enter how many days ahead...");
                    howManyDaysAhead = scan.nextInt();
                    int finalDay = (currentDay.get(Calendar.DAY_OF_WEEK) + howManyDaysAhead) % 7;

                    System.out.println("After " + howManyDaysAhead + " days it will be " + DayOfWeek.of(finalDay));
                    break;

                case 3:
                    loop = false;
                    break;
            }
        }
            while (loop) ;

        }
    }


