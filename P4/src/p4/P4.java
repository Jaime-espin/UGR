/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package p4;

import java.util.ArrayList;

/**
 *
 * @author Jaime Espín
 */
public class P4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Personaje p = new Personaje("Jaime", 10);     
        Jugador j = new Jugador(3, "Jugador", 10);    
        Mago m = new Mago("Abracadabra", 10, "boldemore", 10);
        
        ArrayList<Personaje> personajes = new ArrayList();
        
        personajes.add(p);
        personajes.add(j);
        personajes.add(m);
        
        for(Personaje i: personajes){
            i.atacar();
        }
        
    }
    
}
