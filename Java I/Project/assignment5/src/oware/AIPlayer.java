package oware;

import java.util.List;

import oware.Board;
import oware.Board.House;
import oware.Board.Side;

public class AIPlayer extends Player implements Cloneable {
    AIPlayer(Side player) {
        super(player);
    }

    @Override
    public PlayerMove getMove(Board board) {
        PlayerMove result = null;
        List<House> validMoves = board.getValidMoves(player_side);
        if (validMoves.size() > 0) {
            House h = validMoves.get(0);
            result = new PlayerMove(Action.PLAY, h);
        }
        return result;
    }
}
