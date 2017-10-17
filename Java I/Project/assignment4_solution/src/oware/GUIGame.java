package oware;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Stack;

import oware.Board.House;
import oware.Board.Side;
import oware.Board;
import oware.OwareException;
import oware.Player.PlayerMove;

public class GUIGame extends Application {
    private Board board;
    private Scanner input;
    private Side currentPlayer;
    private GridPane grid;
    private Text turn_text;

    public GUIGame() {
        board = new Board();
        currentPlayer = Side.SOUTH;
    }

    public void start(Stage stage) {

        // represent the board with a grid pane
        grid = new GridPane();
        grid.setPadding(new Insets(10));
        grid.setAlignment(Pos.CENTER);
        grid.setHgap(5);
        grid.setVgap(5);

        // text for the current player's turn
        turn_text = new Text();
        HBox text = new HBox(10);
        text.setStyle(
                "-fx-alignment: center;" +
                "-fx-background-color: burlywood;"
                );
        text.getChildren().add(turn_text);

        // make the stores
        Button north_store = new Button();
        north_store.setMinWidth(50);
        north_store.setMinHeight(100);
        GridPane.setRowSpan(north_store, 2);
        grid.add(north_store, 0, 0);

        Button south_store = new Button();
        south_store.setMinWidth(50);
        south_store.setMinHeight(100);
        GridPane.setRowSpan(south_store, 2);
        grid.add(south_store, 7, 0);

        // make the houses
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 6; j++) {
                Button b = new Button("");
                b.setMinWidth(50);
                b.setMinHeight(50);
                grid.add(b, j+1, i);
            }
        }

        HBox controls = new HBox(10);
        controls.setStyle(
                "-fx-alignment: center;" +
                "-fx-background-color: burlywood;" +
                "-fx-padding: 10 10 10 10;"
                );

        String button_style = new String(
                "-fx-alignment: center;" +
                "-fx-background-color: papayawhip;" +
                "-fx-effect: dropshadow(three-pass-box, black, 10, 0, 0, 0);"
                );

        Button quitButton = new Button("Quit");
        quitButton.setStyle(button_style);

        Button resetButton = new Button("Reset");
        resetButton.setStyle(button_style);

        Button undoButton = new Button("Undo");
        undoButton.setStyle(button_style);

        controls.getChildren().addAll(quitButton, resetButton, undoButton);

        VBox root = new VBox();
        root.getChildren().add(text);
        root.getChildren().add(grid);
        root.getChildren().add(controls);

        stage.setTitle("Oware");
        stage.setScene(new Scene(root));
        stage.show();
        repaint();
    }

    private void repaint() {
        grid.setStyle("-fx-background-color: burlywood;");
        String house_style = new String(
                    "-fx-background-color: papayawhip;" +
                    "-fx-border-width: 1px;" +
                    "-fx-background-radius: 5em;" +
                    "-fx-alignment: center;" +
                    "-fx-effect: dropshadow(three-pass-box, black, 10, 0, 0, 0);"
                    );
        String score_style = new String(
                "-fx-background-color: papayawhip;" +
                "-fx-alignment: center;" +
                "-fx-background-radius: 2em;"
                );

        int[] north_houses = board.getNorthHousesArray();
        int[] north_houses_reversed = new int[north_houses.length];
        for (int i = 0; i < north_houses.length; i++) {
            north_houses_reversed[(north_houses.length - 1) - i] = north_houses[i];
        }
        for (int i = 0; i < north_houses_reversed.length; i++) {
            Button b = (Button)getNodeFromGridPane(grid, 0, i+1);
            b.setText(Integer.toString(north_houses_reversed[i]));
            b.setStyle(house_style);
        }
        int[] south_houses = board.getSouthHousesArray();
        for (int i = 0; i < south_houses.length; i++) {
            Button b = (Button)getNodeFromGridPane(grid, 1, i+1);
            b.setText(Integer.toString(south_houses[i]));
            b.setStyle(house_style);
        }

        // get the scores
        Map<Side, Integer> score = board.getScore();
        Button north_store = (Button)getNodeFromGridPane(grid, 0, 0);
        north_store.setText(Integer.toString(score.get(Side.NORTH)));
        north_store.setStyle(score_style);

        Button south_store = (Button)getNodeFromGridPane(grid, 0, 7);
        south_store.setText(Integer.toString(score.get(Side.SOUTH)));
        south_store.setStyle(score_style);

        String player = currentPlayer == Side.NORTH ? "NORTH" : "SOUTH";
        turn_text.setText("Turn: " + player);
    }

    private Node getNodeFromGridPane(GridPane grid, int row, int col) {
        Node result = null;
        for (Node n: grid.getChildren()) {
            if (GridPane.getRowIndex(n) == row &&
                GridPane.getColumnIndex(n) == col)
            {
                result = n;
            }
        }
        return result;
    }
}

