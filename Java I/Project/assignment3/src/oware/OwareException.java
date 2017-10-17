// reversi.Game.java
// CSC 243, Fall 2016
// Dr. Schwesinger's definition for a custom exception for the reversi package

package oware;

public class OwareException extends Exception implements Cloneable {
  public OwareException(String message) {
    super(message);
  }
}
