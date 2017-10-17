// oware.Game.java
// CSC 243, Spring 2017
// Author: Dr. Schwesinger

package oware;

import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import java.util.Map;
import java.util.HashMap;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;

import oware.Board;
import oware.Board.House;
import oware.Board.Side;
import oware.Player.PlayerMove;
import oware.OwareException;

/**
 *  The Game class has the game logic for a text based game of Oware
 */
public class Game {
    private Board board;
    private Scanner input;
    private Map<Side, Player> players;
    private Side currentSide;

    public Game() {
        this(false, false);
    }

    public Game(boolean use_AI_for_north, boolean use_AI_for_south) {
        board = new Board();
        input = new Scanner(System.in);
        players = new HashMap<>();
        if (use_AI_for_north) {
            players.put(Side.NORTH, new AIPlayer(Side.NORTH));
        }
        else {
            players.put(Side.NORTH, new ConsolePlayer(Side.NORTH, input));
        }
        if (use_AI_for_south) {
            players.put(Side.SOUTH, new AIPlayer(Side.SOUTH));
        }
        else {
            players.put(Side.SOUTH, new ConsolePlayer(Side.SOUTH, input));
        }
    }


    /**
     * The run loop for the text based game of Oware
     */
    public void run() {
        System.out.println("Oware\n");

        // initialize variables
        Board board = new Board();
        Side currentPlayer = Side.SOUTH; // south goes first

        Map<Side, Integer> score = board.getScore();

        // the game loop
        while (true) {

            // print the board to the screen
            System.out.print(board.toString());
            int north_score = score.get(Side.NORTH);
            int south_score = score.get(Side.SOUTH);

            // get the play move and perform the appropriate action
            PlayerMove pm = players.get(currentPlayer).getMove(board);
            switch (pm.action) {
                case QUIT:
                    System.exit(0);
                    break;
                case PLAY:
                    try {
                        board.playMove(currentPlayer, pm.house);
                    }
                    catch (OwareException ex) {
                        System.out.println("Invalid move. Try again");
                        break;
                    }

                    // check if the game is over
                    board.getScore();
                    north_score = score.get(Side.NORTH);
                    south_score = score.get(Side.SOUTH);
                    if (north_score + south_score == 48) {
                        System.out.println(board.toString());
                        System.out.println("Game over");
                        System.exit(0);
                    }

                    // switch player
                    currentPlayer = (currentPlayer == Side.NORTH) ? Side.SOUTH : Side.NORTH;
                    break;
                default:
                    System.out.println("Unkown action");
            }
        }
    }

    /**
     * Play a text based game of Oware to completion
     *
     * @param args the command line argument array
     */
    public static void main(String[] args) {
        // Parse the command line arguments
        boolean use_AI_for_north = false;
        boolean use_AI_for_south = false;
        for (String s: args) {
            if (s.equals("-n")) {
                use_AI_for_north = true;
            }
            if (s.equals("-s")) {
                use_AI_for_south = true;
            }
        }

        Game g = new Game(use_AI_for_north, use_AI_for_south);
        g.run();
    }
}
