package oware;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
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
		private Stack<Board> undoStack;
		/**
     * Play a GUI based game of Oware to completion
     */
    public GUIGame() {
        board = new Board();
        currentPlayer = Side.SOUTH;
				undoStack = new Stack<>();
				undoStack.push((Board)board.clone());
    }
		/**
     * Set up the GUI for the game
     */
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


        Button na = (Button)getNodeFromGridPane(grid, 0, 1);
        Button nb = (Button)getNodeFromGridPane(grid, 0, 2);
        Button nc = (Button)getNodeFromGridPane(grid, 0, 3);
        Button nd = (Button)getNodeFromGridPane(grid, 0, 4);
        Button ne = (Button)getNodeFromGridPane(grid, 0, 5);
        Button nf = (Button)getNodeFromGridPane(grid, 0, 6);
        Button sa = (Button)getNodeFromGridPane(grid, 1, 1);
        Button sb = (Button)getNodeFromGridPane(grid, 1, 2);
        Button sc = (Button)getNodeFromGridPane(grid, 1, 3);
        Button sd = (Button)getNodeFromGridPane(grid, 1, 4);
        Button se = (Button)getNodeFromGridPane(grid, 1, 5);
        Button sf = (Button)getNodeFromGridPane(grid, 1, 6);

				/**
     		* nf-sf.setOnAction(e -> ) defines the event handler for when a button is pressed
     		*/
				nf.setOnAction(e -> {
					try {
						if (currentPlayer == Side.NORTH)
						{
							board.playMove(currentPlayer, House.A);
							currentPlayer = Side.SOUTH;
							undoStack.push((Board)board.clone());
							repaint();
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				ne.setOnAction(e -> {
					try {
						if (currentPlayer == Side.NORTH)
						{
							board.playMove(currentPlayer, House.B);
							currentPlayer = Side.SOUTH;
							undoStack.push((Board)board.clone());
							repaint();
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				nb.setOnAction(e -> {
					try {
						if (currentPlayer == Side.NORTH)
						{
							board.playMove(currentPlayer, House.E);
							currentPlayer = Side.SOUTH;
							undoStack.push((Board)board.clone());
							repaint();
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				nd.setOnAction(e -> {
					try {
						if (currentPlayer == Side.NORTH)
						{
							board.playMove(currentPlayer, House.C);
							currentPlayer = Side.SOUTH;
							undoStack.push((Board)board.clone());
							repaint();
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				nc.setOnAction(e -> {
					try {
						if (currentPlayer == Side.NORTH)
						{
							board.playMove(currentPlayer, House.D);
							currentPlayer = Side.SOUTH;
							undoStack.push((Board)board.clone());
							repaint();
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				na.setOnAction(e -> {
					try {
						if (currentPlayer == Side.NORTH)
						{
							board.playMove(currentPlayer, House.F);
							currentPlayer = Side.SOUTH;
							repaint();
							undoStack.push((Board)board.clone());
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				sa.setOnAction(e -> {
					try {
						if (currentPlayer == Side.SOUTH)
						{
							board.playMove(currentPlayer, House.A);
							currentPlayer = Side.NORTH;
							repaint();
							undoStack.push((Board)board.clone());
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				sb.setOnAction(e -> {
					try {
						if (currentPlayer == Side.SOUTH)
						{
							board.playMove(currentPlayer, House.B);
							currentPlayer = Side.NORTH;
							repaint();
							undoStack.push((Board)board.clone());
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				sc.setOnAction(e -> {
					try {
						if (currentPlayer == Side.SOUTH)
						{
							board.playMove(currentPlayer, House.C);
							currentPlayer = Side.NORTH;
							repaint();
							undoStack.push((Board)board.clone());
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				sd.setOnAction(e -> {
					try {
						if (currentPlayer == Side.SOUTH)
						{
							board.playMove(currentPlayer, House.D);
							currentPlayer = Side.NORTH;
							repaint();
							undoStack.push((Board)board.clone());
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				se.setOnAction(e -> {
					try {
						if (currentPlayer == Side.SOUTH)
						{
							board.playMove(currentPlayer, House.E);
							currentPlayer = Side.NORTH;
							repaint();
							undoStack.push((Board)board.clone());
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});
				sf.setOnAction(e -> {
					try {
						if (currentPlayer == Side.SOUTH)
						{
							board.playMove(currentPlayer, House.F);
							currentPlayer = Side.NORTH;
							repaint();
							undoStack.push((Board)board.clone());
						}
					}
					catch (OwareException ex) {
						System.out.println("House has no seeds");
					}
				});

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

				/**
     		* quitButton.setOnAction(e -> ) defines the event handler for when quit button is pressed
     		*/
				quitButton.setOnAction(e -> {
					System.exit(0);
				});

        Button resetButton = new Button("Reset");
        resetButton.setStyle(button_style);

				/**
				 * resetButton.setOnAction(e->) defines the event handler for when reset is pressed
				*/
				resetButton.setOnAction(e -> {
					board.reset();
					undoStack = new Stack<>();
					undoStack.push((Board)board.clone());
					currentPlayer = Side.SOUTH;
					repaint();
			  });

        Button undoButton = new Button("Undo");
        undoButton.setStyle(button_style);

				/**
				 * undoButton.setOnAction(e -> ) defines the event handler for when undo is pressed
				 */
				undoButton.setOnAction(e -> {
					if (undoStack.size() != 1) {
						System.out.println("we here");
						Side opponent = (currentPlayer == Side.NORTH) ? Side.SOUTH : Side.NORTH;
						undoStack.pop();
						board = (Board)undoStack.peek().clone();
						currentPlayer = (currentPlayer == Side.NORTH) ? Side.SOUTH : Side.NORTH;
						repaint();
					}
				});

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

		/**
		* repaint repaints the board to the update board object
		*/
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

				if ((score.get(Side.SOUTH) + score.get(Side.NORTH)) == 48)
				{
					Alert alert = new Alert(AlertType.INFORMATION);
					alert.setTitle("Game Over");
					if (score.get(Side.SOUTH) > score.get(Side.NORTH))
					{
						alert.setHeaderText("South Player is the winner!");
					}
					else
					{
						alert.setHeaderText("North player is the winner!");
					}
					alert.showAndWait().ifPresent(rs -> {
						if (rs == ButtonType.OK)
						{
							System.out.println("Pressed OK.");
						}
					});
				}
        Button south_store = (Button)getNodeFromGridPane(grid, 0, 7);
        south_store.setText(Integer.toString(score.get(Side.SOUTH)));
        south_store.setStyle(score_style);

        String player = currentPlayer == Side.NORTH ? "NORTH" : "SOUTH";
        turn_text.setText("Turn: " + player);
    }
		/**
		* getNodeFromGridPain gets node from a location on the grid pane
		*/
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

