// oware.Board.java
// CSC 243, Spring 2017
// Dr. Schwesinger's implementation of the Board class

package oware;

import java.util.Arrays;

/**
 * The Board class is a representation of the board state for a game of Oware
 */
public class Board {

    private static final int HOUSE_COUNT = 12;
    private static final int NORTH_OFFSET = 6;
    private static final int SOUTH_OFFSET = 0;

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
    public int[] getNorthHousesArray() {
        return Arrays.copyOfRange(houses,
                NORTH_OFFSET,
                NORTH_OFFSET + (HOUSE_COUNT/2));
    }

    /**
     * getSouthHousesArray returns an array representing the number of seeds
     * in each house belonging to the South player
     *
     * @return the array representation of the South player's houses
     */
    public int[] getSouthHousesArray() {
        return Arrays.copyOfRange(houses,
                SOUTH_OFFSET,
                SOUTH_OFFSET + (HOUSE_COUNT/2));
    }

    /**
     * getNorthScore returns the number of seeds in the North player's store
     *
     * @return the number of seeds in the North player's store
     */
    public int getNorthScore() {
        return northStore;
    }

    /**
     * getSouthScore returns the number of seeds in the South player's store
     *
     * @return the number of seeds in the South player's store
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
     * sow performs the sow portion of a player's move
     *
     * @param player a character representation of the player
     * @param house a character representation of the house
     * @return an integer representing the index into the houses array of the
     * last seed placed
     */
    private int sow(char player, char house) {
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
     * harvest performs the harvest portion of a player's move
     *
     * @param player a character representation of the player
     * @param houseIndex the index in the houses array indicating where the
     * last seed was placed on the sow part of the turn
     * @return an integer representing the number of seeds harvested
     */
    private int harvest(char player, int houseIndex) {
        int [] houses_copy = Arrays.copyOf(houses, houses.length);
        int store = 0;

        int currentIndex = houseIndex;
        while ( !isOnPlayerSide(player, currentIndex) &&
                (houses[currentIndex] == 2 || houses[currentIndex] == 3)) {
            store += houses[currentIndex];
            houses[currentIndex] = 0;
            currentIndex = getPreviousHouseIndex(currentIndex);
        }

        // handle case if all opponent seeds are captured
        char opponent = (player == 'N') ? 'S' : 'N';
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
    private int getHouseIndex(char player, char house) {
        int result = -1;

        if (player != 'N' && player != 'S') {
            return result; // invalid player
        }

        char c = Character.toLowerCase(house);
        String s = new String("abcdef");
        int index = s.indexOf(c);

        if (index >= 0) {
            result = index + ((player == 'N') ? NORTH_OFFSET : SOUTH_OFFSET);
        }

        return result;
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
    private boolean isOnPlayerSide(char player, int houseIndex) {
        boolean result = false;
        if (player == 'S' &&
                houseIndex >= SOUTH_OFFSET &&
                houseIndex <= (SOUTH_OFFSET + (HOUSE_COUNT/2) -1)) {
            result = true;
        }
        if (player == 'N' &&
                houseIndex >= NORTH_OFFSET &&
                houseIndex <= (NORTH_OFFSET + (HOUSE_COUNT/2) -1)) {
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
    private int getPlayerSeeds(char player) {
        int [] player_houses = null;
        if (player == 'N') {
            player_houses = getNorthHousesArray();
        }
        if (player == 'S') {
            player_houses = getSouthHousesArray();
        }

        int result = 0;
        for (int seeds : player_houses) {
            result += seeds;
        }
        return result;
    }

    /**
     * test and display game state changes
     *
     * @param args command line arguments (not used)
     */
    public static void main(String[] args) {
        Board b = new Board();

        // test the sow action
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
