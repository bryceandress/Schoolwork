// oware.Game.java
// CSC 243, Spring 2017
// Author: Dr. Schwesinger

package oware;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;

import oware.Board;

/**
 *  The Game class has the game logic for a text based game of Oware
 */
public class Game {

    /**
     * The Action enum enumerates the possible actions a player can take
     */
    public enum Action {
        PLAY,
        QUIT
    }

    /**
     * PlayerMove is a class that contains a player Action type, but also
     * contains the house position of the move when the Action is of type PLAY
     */
    static class PlayerMove {
        Action action;
        char house;

        PlayerMove(Action action) {
            this.action = action;
        }

        PlayerMove(Action action, char house) {
            this.action = action;
            this.house = house;
        }
    }

    /**
     * drawBoard is a helper method that prints the game board
     *
     * @param board the Board object representing the current state of the game
     */
    private static void drawBoard(Board board) {
        int [] northHouses = board.getNorthHousesArray();
        int [] southHouses = board.getSouthHousesArray();
        int northScore = board.getNorthScore();
        int southScore = board.getSouthScore();

        String header   = "        f    e    d    c    b    a";
        String hLine    = "+----+----+----+----+----+----+----+----+";
        String midLine  = "|    |----+----+----+----+----+----|    |";
        String footer   = "        A    B    C    D    E    F";

        System.out.println(header);
        System.out.println(hLine);

        System.out.print("|  N ");

        // reverse the north houses array for printing
        int [] northHousesReversed = new int[northHouses.length];
        for (int i = 0; i < northHouses.length; i++) {
            northHousesReversed[(northHouses.length - 1) - i] = northHouses[i];
        }
        for (int seeds : northHousesReversed) {
            String cell = (seeds < 10) ? "|  %d " : "| %d ";
            System.out.print(String.format(cell, seeds));
        }
        System.out.println("|  S |");
        System.out.println(midLine);

        String northScoreString = northScore < 10 ? "|  %d " : "| %d ";
        System.out.print(String.format(northScoreString, northScore));

        for (int seeds : southHouses) {
            String cell = (seeds < 10) ? "|  %d " : "| %d ";
            System.out.print(String.format(cell, seeds));
        }

        String southScoreString = (southScore < 10) ? "|  %d |" : "| %d |";
        System.out.println(String.format(southScoreString, southScore));
        System.out.println(hLine);
        System.out.println(footer + "\n");
    }

    /**
     * getPlayerMove gets a player's move using text based I/O
     *
     * Precondition: the Scanner parameter is assumed to be constructed by the
     * caller
     *
     * @param input a Scaner object to parse a player's move
     * @param board a Board object representing the current state of the game
     * @param player a character representation of the current player
     * @return A PlayerMove object representing the player's move
     */
    private static PlayerMove getPlayerMove(Scanner input, Board board, char player) {
        String playerName = player == 'N' ? "North" : "South";

        while (true) {
            System.out.printf("Enter the move for %s or \"quit\"\n", playerName);
            String move = input.nextLine();
            try {
                // split the input into whitespace separated tokens
                String[] splitArray = move.split("\\s+");

                if (splitArray.length == 1) {
                    if (splitArray[0].toLowerCase().equals("quit")) {
                        return new PlayerMove(Action.QUIT);
                    }
                    if (Pattern.matches("[A-F]|[a-f]", splitArray[0])) {
                        return new PlayerMove(Action.PLAY, splitArray[0].charAt(0));
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

    /**
     * Play a text based game of Oware to completion
     *
     * @param args the command line argument array
     */
    public static void main(String[] args) {
        System.out.println("Oware\n");

        // initialize variables
        Board board = new Board();
        char currentPlayer = 'S'; // south goes first
        Scanner input = new Scanner(System.in);

        // the game loop
        while (true) {

            // print the board to the screen
            drawBoard(board);
            int north_score = board.getNorthScore();
            int south_score = board.getSouthScore();

            // get the play move and perform the appropriate action
            PlayerMove pm = getPlayerMove(input, board, currentPlayer);
            switch (pm.action) {
                case QUIT:
                    System.exit(0);
                    break;
                case PLAY:
                    if (!board.playMove(currentPlayer, pm.house)) {
                        System.out.println("Invalid move. Try again");
                        break;
                    }

                    // check if the game is over
                    north_score = board.getNorthScore();
                    south_score = board.getSouthScore();
                    if (north_score + south_score == 48) {
                        drawBoard(board);
                        System.out.println("Game over");
                        System.exit(0);
                    }

                    // switch player
                    currentPlayer = (currentPlayer == 'N') ? 'S' : 'N';
                    break;
                default:
                    System.out.println("Unkown action");
            }
        }
    }
}
