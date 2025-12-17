/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
import irrgarten.Game;
import irrgarten.Controller.Controller;
import irrgarten.UI.GraphicalUI;

public class main {
    public static void main(String[] args) {
        
        GraphicalUI vista = new GraphicalUI();
        Game game = new Game(2);
        Controller controller = new Controller (game, vista);
        controller.play(); 
    }
}