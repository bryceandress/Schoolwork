// oware.Board.java
// CSC 243, Spring 2017
// Dr. Schwesinger's implementation of the Board class
// Editted and appeneded to by Bryce Andress
// CSC 243 Assignment 2
// Create a Board class that throws exceptions when invalid moves are played instead of
// needing checks.

package oware;

import java.util.Arrays;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * The Board class is a representation of the board state for a game of Oware
 */
public class Board {

    private static final int HOUSE_COUNT = 12;

    public enum House {
        A(0), B(1), C(2), D(3), E(4), F(5);
        public final int index;
        House(int index) {
            this.index = index;
        }
    }

    public enum Side {
        NORTH(6), SOUTH(0);
        public final int offset;
        Side(int offset) {
            this.offset = offset;
        }
    }

    private int [] houses;
    private int northStore;
    private int southStore;

    /**
     * The Board constructor initializes the board state to the starting
     * configuration of the game
     */
    public Board() {
        houses = new int[HOUSE_COUNT];
        for (int i = 0; i < HOUSE_COUNT; i++) {
            houses[i] = 4;
        }
        northStore = 0;
        southStore = 0;
    }

    /**
     * getNorthHousesArray returns an array representing the number of seeds
     * in each house belonging to the North player
     *
     * @return the array representation of the North player's houses
     */
    private int[] getNorthHousesArray() {
        return Arrays.copyOfRange(houses,
                Side.NORTH.offset,
                Side.NORTH.offset + (HOUSE_COUNT/2));
    }

    /**
     * getSouthHousesArray returns an array representing the number of seeds
     * in each house belonging to the South player
     *
     * @return the array representation of the South player's houses
     */
    private int[] getSouthHousesArray() {
        return Arrays.copyOfRange(houses,
                Side.SOUTH.offset,
                Side.SOUTH.offset + (HOUSE_COUNT/2));
    }

		/**
		 * getScore returns the number of seeds in the player's store
		 *
		 * @return a Map that maps sides to players scores
		 */
    public Map<Side, Integer> getScore() {
        // DONE complete this method
        // getScore returns a mapping from player sides to player scores
				Map <Side, Integer> score = new HashMap<>();
				score.put(Side.NORTH, northStore);
				score.put(Side.SOUTH, southStore);
				return score;
    }

		/**
		 * playMove attempts to play the move indicated by the player and house
		 * parameters. If the move is incalid, then an exception is thrown
		 *
		 * @param player a character representation of the player
		 * @param house a character representation of the house
		 * @throws OwareException if an invalid move occurs
		 */
    public void playMove(Side player, House house) throws OwareException {
        // DONE complete this method
        // This is similar to the previous assignment, but instead of returning
        // a boolean, an exception should be thrown if the move is not valid
			 boolean result = false;

		   try
			 {
				 validateMove(player, house);
			 }
			 catch (OwareException ex)
			 {
					return;
			 }

       int endIndex = sow(player, house);
			 int harvestedSeeds = harvest(player, endIndex);

			 // update the score
			 if (player == Side.NORTH) {
             northStore += harvestedSeeds;
       }
			 if (player == Side.SOUTH) {
            southStore += harvestedSeeds;
       }

      // check if the oppenent can make a valid move if this side is empty
			boolean opponent_has_valid_move = true;
			Side opponent = (player == Side.NORTH) ? Side.SOUTH : Side.NORTH;
			if (getPlayerSeeds(player) == 0)
			{
						House [] house_labels = {House.A, House.B,House.C, House.D, House.E, House.F};
						for ( House label : house_labels)
						{
							try
							{
								validateMove(opponent, label);
								opponent_has_valid_move = true;
							}
					 		catch(OwareException ex)
					 		{
								opponent_has_valid_move = false;
					 		}
					 	}
			}

		  if (!opponent_has_valid_move) {
               int score = 0;
							 for (int i = 0; i < HOUSE_COUNT; i++) {
                   score += houses[i];
                   houses[i] = 0;
							 }
               if (opponent == Side.NORTH) {
                   northStore += score;
							 }
               if (opponent == Side.SOUTH) {
                  southStore += score;
							}
        }
    }
		/**
		 * validateMove determines if the move indicated by the palyer and house
		 * parameters is valid, if the move is not it throws an exception
		 *
		 * @param player a character representation of the player
		 * @param house a character representation of the house
		 * @throws OwareException if an invalid move occurs
		 */
    private void validateMove(Side player, House house) throws OwareException {
        // DONE complete this method
        // validateMove works like isValidMove from the previous assignment,
        // but instead of returning a boolean, an exception should be thrown
        boolean result = false;

				// make a deep copy of the houses
        int [] houses_copy = Arrays.copyOf(houses, houses.length);

        // we cannot make a move if the house is empty
        int houseIndex = getHouseIndex(player, house);
        if (houseIndex < 0 || houses[houseIndex] == 0) {
            throw new OwareException("House is Empty");
        }

        // perform the sow and harvest portions of the move
        int endIndex = sow(player, house);
        int harvestedSeeds = harvest(player, endIndex);

        // we cannot leave the opponent without any seeds
        Side opponent = (player == Side.NORTH) ? Side.SOUTH : Side.NORTH;
        if (getPlayerSeeds(opponent) == 0) {
					houses = houses_copy;
					throw new OwareException("Opponent would have no seeds");
        }

        // restore the board state
        houses = houses_copy;
    }

		/**
		 * sow performs the sow portion of a player's move
		 *
		 * @param player a character representation of the player
		 * @param house a character representation of the house
		 * @return an integer representing the index into the houses array of the
		 * last seed placed
		 */
    private int sow(Side player, House house) {
        // DONE complete this method
        // The type signature has changed from the previous version
				int currentIndex = getHouseIndex(player, house);

        int startingIndex = currentIndex;
        int seeds = houses[currentIndex];
        houses[currentIndex] = 0;
        while (seeds > 0) {
            currentIndex = getNextHouseIndex(currentIndex);
            if (currentIndex == startingIndex) {
                currentIndex = getNextHouseIndex(currentIndex);
            }
            houses[currentIndex] += 1;
            seeds -= 1;
        }

        return currentIndex;

    }

		/**
		 *  harvest performs the harvest portion of a player's move
		 *
		 *  @param player a character representation of the player
		 *  @param houseIndex the index in the houses array indicating where hte
		 *  last seed was placed on the sow part of the turn
		 *  @return an integer representing the number of seeds harvested
		 */
    private int harvest(Side player, int houseIndex) {
        // DONE complete this method
        // The type signature has changed from the previous version
				int [] houses_copy = Arrays.copyOf(houses, houses.length);
        int store = 0;

        int currentIndex = houseIndex;
        while ( !isOnPlayerSide(player, currentIndex) &&
                (houses[currentIndex] == 2 || houses[currentIndex] == 3)) {
            store += houses[currentIndex];
            houses[currentIndex] = 0;
						//System.out.println("Store: " + store + "   Seeds in House: " + houses[currentIndex]);
            currentIndex = getPreviousHouseIndex(currentIndex);
						//System.out.println("Previous Index: " + currentIndex);
        }

        // handle case if all opponent seeds are captured
        Side opponent = (player == Side.NORTH) ? Side.SOUTH : Side.NORTH;
        if (getPlayerSeeds(opponent) == 0) {
            houses = houses_copy;
            store = 0;
        }

        return store;
    }

    /**
     * getHouseIndex maps character representations of the player and house
     * to an index in the houses array
     *
     * @param player a character representation of the player
     * @param house a character representation of the house
     * @return the index of the house in the houses array or -1 if the
     * parameters do not indicate a valid index
     */
    private int getHouseIndex(Side player, House house) {
        return house.index + player.offset;
    }

    /**
     * getNextHouseIndex returns the next house in the houses array
     *
     * @param index the current house index in the houses array
     * @return the next house index in the houses array
     */
    private int getNextHouseIndex(int index) {
        return (index + 1) % HOUSE_COUNT;
    }

    /**
     * getPreviousHouseIndex returns the previous house in the houses array
     *
     * @param index the current house index in the houses array
     * @return the previous house index in the houses array
     */
    private int getPreviousHouseIndex(int index) {
        return ((((index - 1) % HOUSE_COUNT) + HOUSE_COUNT) % HOUSE_COUNT);
    }

		/**
		 * isOnPlayerSide determines if the index passed in is on the side of
		 * the player passed in
		 *
		 * @param player a character representation of the player
		 * @param houseIndex the house index into the houses array
		 * @return true if the index is on the indicated player's side, otherwise
		 * false
		 */
    private boolean isOnPlayerSide(Side player, int houseIndex) {
        // DONE complete this method
        // The type signature has changed from the previous version
				 boolean result = false;
				 if (player == Side.SOUTH &&
				         houseIndex >= 0 &&
				         houseIndex <= 5) {
				     result = true;
				 }
				if (player == Side.NORTH &&
				       houseIndex >= 6 &&
					     houseIndex <= 11){
					  result = true;
			  }
			  return result;
    }

		/**
		 * getPlayerSeeds returns the number of seeds on the indicated player's
		 * side of the board
		 *
		 * @param player a character representation of the player
		 * @return the number of seeds on the indicated player's side of the board
		 */
    private int getPlayerSeeds(Side player) {
        // DONE complete this method
        // The type signature has changed from the previous version
				int [] player_houses = null;
				if (player == Side.NORTH) {
					player_houses = getNorthHousesArray();
				}
				if (player == Side.SOUTH) {
					player_houses = getSouthHousesArray();
				}
				int result = 0;
				for (int seeds : player_houses) {
					result += seeds;
				}
				return result;
    }

		/**
		 * getValidMoves creates a list of valid moves that the AI will be able to choose
		 * from and not break the game
		 *
		 * @param player is a character representation of the player
		 * @return a List is returned with all valid moves
		 */
    public List<House> getValidMoves(Side player) {
        // DONE complete this method
        // getValidMoves returns a list of valid moves for the given player
        // The helper method validateMove should be useful for implementing
        // this method

				List<House> validMoves = new ArrayList<House>();
			  try
				{
					validateMove(player, House.A);
					validMoves.add(House.A);
				}
				catch (OwareException ex)
				{
				}
				try
				{
					validateMove(player, House.B);
					validMoves.add(House.B);
				}
				catch (OwareException ex)
				{
				}
				try
				{
					validateMove(player, House.C);
					validMoves.add(House.C);
				}
				catch (OwareException ex)
				{
				}
				try
				{
					validateMove(player, House.D);
					validMoves.add(House.D);
				}
				catch (OwareException ex)
				{
				}
				try
				{
					validateMove(player, House.E);
					validMoves.add(House.E);
				}
				catch (OwareException ex)
				{
				}
				try
				{
					validateMove(player, House.F);
					validMoves.add(House.F);
				}
				catch (OwareException ex)
				{
				}
			return validMoves;
    }

		/**
		 * toString overrides Java's toString function and outputs the board
		 *
		 * @return a String object that is the board
		 */
    @Override
    public String toString() {
        // DONE complete this method
        // the toString method should return a String object containing the
        // string that got output from the Game.drawBoard method of the
        // previous assignment
				int [] northHouses = getNorthHousesArray();
			  int [] southHouses = getSouthHousesArray();
			  Map score = getScore();

			  String header   = "        f    e    d    c    b    a\n";
			  String hLine    = "+----+----+----+----+----+----+----+----+\n";
			  String midLine  = "|    |----+----+----+----+----+----|    |\n";
			  String footer   = "        A    B    C    D    E    F\n";
				String output = "";

				output += header;
				output += hLine;
				output += "|  N ";

        // reverse the north houses array for printing
        int [] northHousesReversed = new int[northHouses.length];
        for (int i = 0; i < northHouses.length; i++) {
					  northHousesReversed[(northHouses.length - 1) - i] = northHouses[i];
			  }
			  for (int seeds : northHousesReversed) {
			      String cell = (seeds < 10) ? "|  %d " : "| %d ";
						output += String.format(cell, seeds);
		    }
		    output += "|  S |\n";
		    output += midLine;
				output += "|  ";
			  output += score.get(Side.NORTH);
				if ((int)score.get(Side.NORTH) >= 10)
			  {		output += "";}
				else
				{   output += " ";}

		    for (int seeds : southHouses) {
		        String cell = (seeds < 10) ? "|  %d " : "| %d ";
		        output += String.format(cell, seeds);
		    }

				if ((int)score.get(Side.SOUTH) >= 10)
				{   output += "| ";}
				else
				{   output += "|  ";}
		    output += score.get(Side.SOUTH) + " |\n";
			  output += hLine;
			  output += footer;
				return output;
    }

    /**
     * test and display game state changes
     *
     * @param args command line arguments (not used)
     */
    public static void main(String[] args) {
        Board b = new Board();
        try{

            // test the sow action
            int[] sowState = {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            b.houses = sowState;
            System.out.println(b.toString());
            b.playMove(Side.SOUTH, House.A);
            System.out.println(b.toString());

            System.out.println("---");

            // test the harvest action
            int[] harvestState = {0, 0, 0, 0, 0, 5, 1, 2, 1, 2, 1, 3};
            b.houses = harvestState;
            b.northStore = 0;
            b.southStore = 0;
            System.out.println(b.toString());
            b.playMove(Side.SOUTH, House.F);
            System.out.println(b.toString());

            System.out.println("---");

            // test the special case harvest rule
            int[] specialHarvestState = {0, 0, 0, 0, 1, 6, 1, 2, 1, 2, 1, 1};
            b.houses = specialHarvestState;
            b.northStore = 0;
            b.southStore = 0;
            System.out.println(b.toString());
            b.playMove(Side.SOUTH, House.F);
            System.out.println(b.toString());

            System.out.println("---");

            // test the case where there are no valid moves left
            int[] noMovesState = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3};
            b.houses = noMovesState;
            b.northStore = 0;
            b.southStore = 0;
            System.out.println(b.toString());
            b.playMove(Side.NORTH, House.F);
            System.out.println(b.toString());

        }
        catch (OwareException ex) {
            ex.printStackTrace();
        }
    }
}
