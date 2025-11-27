/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package clase5;

/**
 *
 * @author Jaime Espín
 */
public class Clase5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Jugador j1 = new Jugador(Personaje.TIPO_MONSTRUO, "Jaime el heroe", 10);
        Monstruo m1 = new Monstruo(Personaje.TIPO_MONSTRUO, "Marvin", 5);
        
        j1.atacar();
        m1.defender();
        j1.defender();
        m1.atacar();
    }
    
}
