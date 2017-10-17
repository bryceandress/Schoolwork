// reversi.ConsolePlayer.java
// CSC 243, Fall 2016
// Dr. Schwesinger's code for an extension of the Player class that gets text
// input from the console

package oware;

import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;

import oware.Board;
import oware.Board.Side;
import oware.Board.House;

/**
 * ConsolePlayer uses the console to get moves from a player
 */
public class ConsolePlayer extends Player implements Cloneable {
    private Scanner input;

    /**
     * The constructor for ConsolePlayer requires a Scanner object
     * @param side the player's side
     * @param input a Scanner object created by the caller
     */
    public ConsolePlayer(Side side, Scanner input) {
        super(side);
        this.input = input;
    }

    /**
     * getMove gets a player's move via the text console
     * @param board the Board object representing the current state of the game
     * @return a PlayerMove object indicating the player's move
     */
    public PlayerMove getMove(Board board) {
        String sideName = player_side == Side.SOUTH ? "South" : "North";
        while (true) {
            System.out.printf("Enter the move for %s or \"quit\"\n", sideName);
            String move = input.nextLine();
            try {
                // split the input into whitespace separated tokens
                String[] splitArray = move.split("\\s+");

                if (splitArray.length == 1) {
                    if (splitArray[0].toLowerCase().equals("quit")) {
                        return new PlayerMove(Action.QUIT);
                    }
										if (splitArray[0].toLowerCase().equals("undo")) {
											  return new PlayerMove(Action.UNDO);
										}
										if (splitArray[0].toLowerCase().equals("reset")) {
											  return new PlayerMove(Action.RESET);
										}
                    if (Pattern.matches("[A-F]|[a-f]", splitArray[0])) {
                        char c = Character.toLowerCase(splitArray[0].charAt(0));
                        House house = null;
                        if (c == 'a') house = House.A;
                        if (c == 'b') house = House.B;
                        if (c == 'c') house = House.C;
                        if (c == 'd') house = House.D;
                        if (c == 'e') house = House.E;
                        if (c == 'f') house = House.F;
                        return new PlayerMove(Action.PLAY, house);
                    }
                    System.out.println("Invalid move. Try again.");
                }
                else {
                    System.out.println("Invalid move. Try again.");
                }
            }
            catch (PatternSyntaxException ex) {
                // do nothing
            }
        }
    }
}
