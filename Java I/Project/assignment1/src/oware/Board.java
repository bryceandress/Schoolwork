// oware.Board.java
// CSC 243, Spring 2017
// Dr. Schwesinger's implementation of the Board class

// Bryce Andress
// Dr. Schwesinger
// Feb 27 2017
// Assignment 1
// Create an implementation of the game Oware

package oware;

import java.util.Arrays;

 /**
 *  The Board class has the logic for a text based game of Oware such as how to sow, harvest,
 *  or determine who is up.
 */

public class Board {

    private static final int HOUSE_COUNT = 12;
    private static final int NORTH_OFFSET = 6;
    private static final int SOUTH_OFFSET = 0;

    private int [] houses;
    private int northStore;
    private int southStore;

		/**
     * Board constructs the playing board for oware
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
     * getNorthHousesArray gets a deep copy of the North player's houses
     * @return an int array of the North players houses
     */
    public int[] getNorthHousesArray() {
        // DONE return a deep copy of the North player's half of the houses
        // array
				int[] northHouses = new int[6];
				for (int i = 0; i <=5; i++)
				{
					northHouses[i] = houses[i+6];
				}
        return northHouses;
    }
		/**
     * getSouthHousesArray creates a deep copy of the South player's houses
     * @return an int array of the South players houses
     */
    public int[] getSouthHousesArray() {
        // DONE return a deep copy of the South player's half of the houses
        int[] southHouses = new int[6];
				for (int i = 0; i < 6; i++)
				{
					southHouses[i] = houses[i];
				}

        return southHouses;
    }
		/**
		 * getNorthScore get the number in northStore
		 * @return an int of seeds for the North player
		 */
    public int getNorthScore() {
        return northStore;
    }
		/**
		 * getNorthScore get the number in southStore
		 * @return an int of seeds for the South player
		 */
    public int getSouthScore() {
        return southStore;
    }

    /**
     * playMove attempts to play the move indicated by the player and house
     * parameters. If the move is invalid, then a result of false is returned.
     *
     * @param player a character representation of the player
     * @param house a character representation of the house
     * @return a boolean indicating whether the move was successful
     */
    public boolean playMove(char player, char house) {
        boolean result = false;
        if (isValidMove(player, house)) {
            int endIndex = sow(player, house);
            int harvestedSeeds = harvest(player, endIndex);

            // update the score
            if (player == 'N') {
                northStore += harvestedSeeds;
            }
            if (player == 'S') {
                southStore += harvestedSeeds;
            }

            // check if the oppenent can make a valid move if this side is empty
            if (getPlayerSeeds(player) == 0) {
                char opponent = (player == 'N') ? 'S' : 'N';
                boolean opponent_has_valid_move = false;
                char [] house_labels = {'a', 'b', 'c', 'd', 'e', 'f'};
                for (char label : house_labels) {
                    if (isValidMove(opponent, label)) {
                        opponent_has_valid_move = true;
                    }
                }

                // if the opponent cannot make a move then they collect all of
                // the seeds on their side of the board
                if (!opponent_has_valid_move) {
                    int score = 0;
                    for (int i = 0; i < HOUSE_COUNT; i++) {
                        score += houses[i];
                        houses[i] = 0;
                    }
                    if (opponent == 'N') {
                        northStore += score;
                    }
                    if (opponent == 'S') {
                        southStore += score;
                    }
                }
            }
            result = true;
        }
        return result;
    }

    /**
     * isValidMove determines if the move indicated by the player and house
     * parameters is valid
     *
     * @param player a character representation of the player
     * @param house a character representation of the house
     * @return a boolean indicating whether the move is valid
     */
    private boolean isValidMove(char player, char house) {
        boolean result = false;
        // make a deep copy of the houses
        int [] houses_copy = Arrays.copyOf(houses, houses.length);
        // we cannot make a move if the house is empty
        int houseIndex = getHouseIndex(player, house);
        if (houseIndex < 0 || houses[houseIndex] == 0) {
            return result;
        }

        // perform the sow and harvest portions of the move
        int endIndex = sow(player, house);
        int harvestedSeeds = harvest(player, endIndex);

				// we cannot leave the opponent without any seeds
        char opponent = (player == 'N') ? 'S' : 'N';
        if (getPlayerSeeds(opponent) != 0) {
            result = true;
        }
// restore the board state
        houses = houses_copy;
        return result;
    }
		/**
     * sow move the seeds around the board in correspondence with the rules
     * @param player a character representation of the player
     * @param house a character representation of the house
     * @return an index of what house the play ended in
     */
    private int sow(char player, char house) {
        // DONE implement the sow part of a player's move
        // the player parameter is a character representation of the player
        // the house parameter is  a character representation of the house
        // the return value is an integer representing the index into the
        // houses array of the last seed placed
				int housesIdx = getHouseIndex(player, house);
				int tempSeeds = houses[housesIdx];
				houses[housesIdx] = 0;
				boolean isKroo = false;
				if (tempSeeds == 12)
					isKroo = true;
				while (tempSeeds > 0)
				{
					housesIdx = getNextHouseIndex(housesIdx);
					houses[housesIdx] += 1;
					tempSeeds--;
				}
				if (isKroo)
				{
					houses[housesIdx] = 0;
					houses[getNextHouseIndex(housesIdx)] += 1;
				}
				return housesIdx;
    }
		/**
     * harvest if opponents house count is 2 or 3 capture seeds
     * @param player a character representation of the player
     * @param houseIndex an int of what house we are in
     * @return an int of the number of seeds harvested
     */
    private int harvest(char player, int houseIndex) {
        // DONE implement the harvest part of a player's move
        // the player parameter is a character representation of the player
        // the houseIndex parameter is the index in the houses array indicating where the
        // last seed was placed on the sow part of the turn
        // the return value is the number of seeds harvested
        int [] houses_copy = Arrays.copyOf(houses, houses.length);
				int harvested = 0;
				while (houses[houseIndex] == 2 || houses[houseIndex] == 3)
				{
					 if (!isOnPlayerSide(player, houseIndex))
					 {
				   		harvested += (houses[houseIndex]);
							houses[houseIndex] = 0;
							houseIndex = getPreviousHouseIndex(houseIndex);
					 }
					 else
						 break;
				}
				char tempPlayer;
				if (player == 'S')
				{
					tempPlayer = 'N';
				}
				else
					tempPlayer = 'S';

				int seeds = getPlayerSeeds(tempPlayer);
				if (seeds == 0)
				{
					houses = houses_copy;
					return 0;
				}
				return harvested;
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
    private int getHouseIndex(char player, char house) {
        int result = -1;

				char c = Character.toLowerCase(house);
				String s = new String("abcdef");
				int index = s.indexOf(c);

				if (index >= 0) {
					result = index + ((player =='N') ? NORTH_OFFSET : SOUTH_OFFSET);
				}
				return result;
    }

		/**
     * isOnPlayerSide determine if index passed in is on players side
     * @param player a character representation of the player
     * @param houseIndex an int index of where we are in the houses array
     * @return a bool if we are on the correct side
     */
    private boolean isOnPlayerSide(char player, int houseIndex) {
        // DONE implement this method:
        // this method determines if the index passed in is on the side of
        // the player passed in
				if (player == 'N' && houseIndex >= 6)
				{
					return true;
				}
				if (player == 'S' && houseIndex < 6)
					return true;
        return false;
    }

		/**
     * getPlayerSeeds get the number of seeds on the players side
     * @param player a character representation of the player
     * @return an int of the number of seeds a player has
     */
    private int getPlayerSeeds(char player) {
        // DONE implement this method:
        // this method counts the number of seeds on the indicated player's
        // side of the board
				int seeds = 0;
				if (player == 'N')
				{
					for(int idx = 6; idx <= 11; idx++)
					{
						seeds += houses[idx];
					}
					return seeds;
				}
				else
				{
					for(int idx = 0; idx < 6; idx++)
					{
						seeds += houses[idx];
					}
        	return seeds;
				}
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
    public static void main(String[] args) {
        Board b = new Board();

        //test the sow action
        int[] sowState = {12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        b.houses = sowState;
        System.out.println(Arrays.toString(b.houses));
        b.playMove('S', 'A');
        System.out.println(Arrays.toString(b.houses));
        System.out.println("S: " + b.southStore + ", N: " + b.northStore);

        System.out.println("---");

        // test the harvest action
        int[] harvestState = {0, 0, 0, 0, 0, 5, 1, 2, 1, 2, 1, 3};
        b.houses = harvestState;
        b.northStore = 0;
        b.southStore = 0;
        System.out.println(Arrays.toString(b.houses));
        b.playMove('S', 'F');
        System.out.println(Arrays.toString(b.houses));
        System.out.println("S: " + b.southStore + ", N: " + b.northStore);

        System.out.println("---");
        // test the special case harvest rule
        int[] specialHarvestState = {0, 0, 0, 0, 1, 6, 1, 2, 1, 2, 1, 1};
        b.houses = specialHarvestState;
        b.northStore = 0;
        b.southStore = 0;
        System.out.println(Arrays.toString(b.houses));
        b.playMove('S', 'F');
        System.out.println(Arrays.toString(b.houses));
        System.out.println("S: " + b.southStore + ", N: " + b.northStore);

        System.out.println("---");

        // test the case where there are no valid moves left
        int[] noMovesState = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3};
        b.houses = noMovesState;
        b.northStore = 0;
        b.southStore = 0;
        System.out.println(Arrays.toString(b.houses));
        b.playMove('N', 'F');
        System.out.println(Arrays.toString(b.houses));
        System.out.println("S: " + b.southStore + ", N: " + b.northStore);
    }
	}
