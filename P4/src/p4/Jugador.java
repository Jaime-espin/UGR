/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package p4;

/**
 *
 * @author Jaime Espín
 */
public class Jugador extends Personaje{
    private int nivel;

    public Jugador(int nivel, String nombre, int salud) {
        super(nombre, salud);
        this.nivel = nivel;
    }
    
    @Override
    public void atacar(){
        super.atacar();
        System.out.println("... con nivel"+ nivel);
    }
    
    public void subirNIvel(){
        this.nivel++;
    }
}
