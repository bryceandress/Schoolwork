// oware.Player.java
// CSC 243, Spring 2017
// Dr. Schwesinger's definition for the Player abstract class

package oware;

import oware.Board;
import oware.Board.House;
import oware.Board.Side;

public abstract class Player implements Cloneable {
    public enum Action {
        PLAY,
        QUIT,
				UNDO,
				RESET
    }

    public static class PlayerMove {
        Action action;
        House house;
        PlayerMove(Action action) {
            this.action = action;
        }
        PlayerMove(Action action, House house) {
            this.action = action;
            this.house = house;
        }
    }

    Side player_side;

    public Player(Side player_side) {
        this.player_side = player_side;
    }

    public abstract PlayerMove getMove(Board board);
}
