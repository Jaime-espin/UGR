/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
import irrgarten.Game;
import irrgarten.UI.TextUI;
import irrgarten.Controller.Controller;

public class main {
    public static void main(String[] args) {
        
        TextUI view = new TextUI();

        Game game = new Game(2);

        Controller controller = new Controller(game, view);

        controller.play(); 
    }
}