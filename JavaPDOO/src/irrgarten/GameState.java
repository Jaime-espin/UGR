package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class GameState {
    private String labyrinth;
    private String players;
    private String monster;
    private int currentPlayer;
    private boolean winner;
    private String log;

    public GameState(String labyinth, String players, String monster, int currentPlayer, boolean winner, String log) {
        this.labyrinth = labyinth;
        this.players = players;
        this.monster = monster;
        this.currentPlayer = currentPlayer;
        this.winner = winner;
        this.log = log;
    }

    public String getLabyrinth() {
        return labyrinth;
    }

    public String getPlayers() {
        return players;
    }

    public String getMonsters() {
        return monster;
    }

    public int getCurrentPlayer() {
        return currentPlayer;
    }

    public boolean isWinner() {
        return winner;
    }

    public String getLog() {
        return log;
    }
}