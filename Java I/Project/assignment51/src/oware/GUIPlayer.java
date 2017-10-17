package oware;

import oware.Board.Side;

public class GUIPlayer extends Player {

    GUIPlayer(Side player) {
        super(player);
    }

    @Override
    public PlayerMove getMove(Board board) {
        return new PlayerMove(Action.QUIT);
    }
}
