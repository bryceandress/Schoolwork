// AIPlayer.
// CSC 243, Fall 2016
// Bryce Andress
// Dr. Schweisinger
// Create a class that places oware by itself with no human intervention

package oware;

import java.util.List;
import java.util.Scanner;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;

import oware.Board;
import oware.Board.Side;
import oware.Board.House;

/**
 * AIPlayer uses predetermined rules to make moves
 */
public class AIPlayer extends Player {

    /**
     * The constructor for AIPlayer
     * @param side the player's side
     */
    public AIPlayer(Side side) {
        super(side);
    }

    /**
     * getMove gets a player's move via the text console
     * @param board the Board object representing the current state of the game
     * @return a PlayerMove object indicating the player's move
     */
    public PlayerMove getMove(Board board) {
        while (true) {
            try {
							List<House> validMoves = board.getValidMoves(player_side);
                if (validMoves.size() < 1) {
										System.out.println("No valid moves");
                    return new PlayerMove(Action.QUIT);
							  }
								else{
								    House house = validMoves.get(0);
                    return new PlayerMove(Action.PLAY, house);
                }
            }
            catch (PatternSyntaxException ex) {
                // do nothing
            }
        }
    }
}
