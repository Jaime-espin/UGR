
package irrgarten.UI;

import irrgarten.Directions;
import irrgarten.GameState;
import java.util.Scanner;


public class TextUI {
    
    private static Scanner in = new Scanner(System.in);
    
    private char readChar() {
        String s = in.nextLine();     
        return s.charAt(0);
    }
    

    public Directions nextMove() {
        System.out.print("Where? ");
        
        Directions direction = Directions.DOWN;
        boolean gotInput = false;
        
        while (!gotInput) {
            char c = readChar();
            switch(c) {
                case 'w':
                    System.out.print(" UP\n");
                    direction = Directions.UP;
                    gotInput = true;
                    break;
                case 's':
                    System.out.print(" DOWN\n");
                    direction = Directions.DOWN;
                    gotInput = true;
                    break;
                case 'd':
                    System.out.print("RIGHT\n");
                    direction = Directions.RIGHT;
                    gotInput = true;
                    break;
                case 'a':
                    System.out.print(" LEFT\n");
                    direction = Directions.LEFT;
                    gotInput = true;    
                    break;
            }
        }    
        return direction;
    }
    
    public void showGame(GameState gameState) {
        // Limpiar la consola (puede no funcionar en todos los IDEs)
        System.out.print("\033[H\033[2J");
        System.out.flush();

        // Muestra el laberinto
        System.out.println("--- LABERINTO ---");
        System.out.println(gameState.getLabyrinth());
        System.out.println();

        // Muestra estado de jugadores y monstruos
        System.out.println("--- JUGADORES ---");
        System.out.println(gameState.getPlayers());
        System.out.println("--- MONSTRUOS ---");
        System.out.println(gameState.getMonsters());
        System.out.println("-------------------");

        // Muestra el jugador actual y si hay ganador
        System.out.println("Turno del jugador: " + gameState.getCurrentPlayer());
        if (gameState.isWinner()) {
            System.out.println("¡¡¡ EL JUGADOR " + gameState.getCurrentPlayer() + " HA GANADO !!!");
        }
        System.out.println();

        // Muestra el log de eventos
        System.out.println("--- LOG ---");
        System.out.println(gameState.getLog());
        System.out.println("-----------");
    }
    
}
