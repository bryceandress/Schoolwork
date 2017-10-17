import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

public class Guess{
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    // Make sure user enters an arg
    if (args.length == 0)
    {
 	System.out.println("Invalid Usage: Guess <int>");
	System.exit(0);
    }
    // Put arg in guess
    int guess = Integer.parseInt(args[0]);
    // Make sure guess is valid. If not make the user enter one.
    if (guess > 100 || guess < 0){
    	System.out.println("Incorrect input. Please enter a number between 0 and 100.");
        guess = sc.nextInt();
    }

    // Get random number
    int answer = ThreadLocalRandom.current().nextInt(0, 101);
    while(guess != answer)
    {
	//Make sure guess is valid
	if (guess > 100 || guess < 0)
        {
	  System.out.println("Incorrect input. Please enter a number between 0 and 100");
        }
	else if (guess > answer)
        {
	  System.out.println("Your guess was higher than the number. Try again!");
        }

	else
	{
	  System.out.println("Your guess was lower than the answer. Try again!");
	}

	System.out.println("Please enter a number between 0-100");
        guess = sc.nextInt();
    }

    System.out.println("Congratulations! You guessed " + answer + ". You won!");
  }
}
