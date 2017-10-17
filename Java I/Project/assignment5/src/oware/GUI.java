// gui.java
// CSC 243, Spring 2017
// GUI interface for Oware game
// Bryce Andress
// Dr. Schwesinger
// April 21st 2017
// Assignment 4
// Create an implementation of the game Oware

package oware;

import javafx.application.Application;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.event.EventHandler;
import javafx.event.ActionEvent;

import java.util.Map;
import java.util.HashMap;

import oware.Board;
import oware.Board.House;
import oware.Board.Side;
import oware.Player.PlayerMove;
import oware.OwareException;

// Definition of gui
public class GUI extends Application {
	@Override // Override the start method in the Application class
		// start(0
		// Param Stage - Used to put scenes on
		// Place scene with layout for GUI
		public void start(Stage primaryStage) {
			// Create a pane and set its properties
			GridPane pane = new GridPane();
			pane.setPadding(new Insets(11.5, 12.5, 13.5, 14.5));
			pane.setHgap(5.5);
			pane.setVgap(5.5);
			Board board = new Board();
			Side currentPlayer = Side.SOUTH; // south goes first

			// Place nodes in the pane
			Label boardlabel = new Label("             f       e      d      c      b      a");
			pane.add(boardlabel, 0, 0);
			pane.setColumnSpan(boardlabel, 7);
			pane.add(new Label("North "), 0, 1);
			Button na, nb, nc, nd, ne, nf, sa, sb, sc, sd, se, sf;
			pane.add(nf = new Button("4"), 1, 1);
			pane.add(ne = new Button("4"), 2, 1);
			pane.add(nd = new Button("4"), 3, 1);
			pane.add(nc = new Button("4"), 4, 1);
			pane.add(nb = new Button("4"), 5, 1);
			pane.add(na = new Button("4"), 6, 1);
			pane.add(new Label("South "), 7, 1);
			Label southscore;
			Label northscore;
			pane.add(northscore = new Label("  0"), 0, 2);
			pane.add(sa = new Button("4"), 1, 2);
			pane.add(sb = new Button("4"), 2, 2);
			pane.add(sc = new Button("4"), 3, 2);
			pane.add(sd = new Button("4"), 4, 2);
			pane.add(se = new Button("4"), 5, 2);
			pane.add(sf = new Button("4"), 6, 2);
			pane.add(southscore = new Label("  0"), 7, 2);
			boardlabel = new Label("Turn:     A      B     C     D     E     F");
			pane.add(boardlabel,0, 3);
			pane.setColumnSpan(boardlabel, 7);
			pane.add(boardlabel = new Label(String.valueOf(currentPlayer)), 0, 4);
			pane.setColumnSpan(boardlabel, 2);
			Button reset;
			pane.add(reset = new Button("Reset"), 3, 4);
			pane.setColumnSpan(reset, 2);
			Button quit;
			pane.add(quit = new Button("Quit"), 5, 4);
			pane.setColumnSpan(quit, 2);
			Button undo;
			pane.add(undo = new Button("Undo"), 7, 4);

			quit.setOnAction(e -> {
					System.exit(0);
					});

			undo.setOnAction(e -> {
					});

			reset.setOnAction(e -> {

					});

			nf.setOnAction(new EventHandler<ActionEvent>() {
				public void handle(ActionEvent e) {
					try
					{
						Board copy = (Board)board.clone();
						//moves.push(copy);
					}
					catch (CloneNotSupportedException ex)
					{
						//e.printStackTrace();
					}
					try {
						board.playMove(currentPlayer, Board.House.F);
					}
					catch (OwareException ex) {
						System.out.println("Invalid move. Try again");
					}

					// check if the game is over
      		Map<Side, Integer> score = board.getScore();
					northscore.setText(String.valueOf(score.get(Side.NORTH)));
					southscore.setText(String.valueOf(score.get(Side.SOUTH)));
					if (Integer.parseInt(northscore.getText()) + Integer.parseInt(southscore.getText()) == 48) {
						System.exit(0);
					}
				}
			});


			// Create a scene and place it in the stage
			Scene scene = new Scene(pane);
			primaryStage.setTitle("ShowGridPane"); // Set the stage title
			primaryStage.setScene(scene); // Place the scene in the stage
			primaryStage.show(); // Display the stage
		}

	/**
	 * The main method is only needed for the IDE with limited
	 * JavaFX support. Not needed for running from the command line.
	 */
	// Launch the scene
	public static void main(String[] args) {
		launch(args);
	}
}
