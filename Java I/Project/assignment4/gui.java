// gui.java
// CSC 243, Spring 2017
// GUI interface for Oware game
// Bryce Andress
// Dr. Schwesinger
// April 21st 2017
// Assignment 4
// Create an implementation of the game Oware

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

// Definition of gui
public class gui extends Application {
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

    // Place nodes in the pane
    Label board = new Label("             f       e      d      c      b      a");
    pane.add(board, 0, 0);
		pane.setColumnSpan(board, 7);
		pane.add(new Label("North "), 0, 1);
    pane.add(new Button("4"), 1, 1);
    pane.add(new Button("4"), 2, 1);
    pane.add(new Button("4"), 3, 1);
    pane.add(new Button("4"), 4, 1);
    pane.add(new Button("4"), 5, 1);
    pane.add(new Button("4"), 6, 1);
		pane.add(new Label("South "), 7, 1);
		pane.add(new Label("  0"), 0, 2);
		pane.add(new Button("4"), 1, 2);
    pane.add(new Button("4"), 2, 2);
    pane.add(new Button("4"), 3, 2);
    pane.add(new Button("4"), 4, 2);
    pane.add(new Button("4"), 5, 2);
    pane.add(new Button("4"), 6, 2);
		pane.add(new Label("  0"), 7, 2);
    board = new Label("Turn:     A      B     C     D     E     F");
		pane.add(board,0, 3);
		pane.setColumnSpan(board, 7);
		pane.add(board = new Label("South"), 0, 4);
		pane.setColumnSpan(board, 2);
		Button butt;
		pane.add(butt = new Button("Reset"), 3, 4);
		pane.setColumnSpan(butt, 2);
		pane.add(butt = new Button("Quit"), 5, 4);
		pane.setColumnSpan(butt, 2);
		pane.add(new Button("Undo"), 7, 4);


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
