/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package p4;

/**
 *
 * @author Jaime Espín
 */
public class Mago extends Jugador{
    private String hechizo;

    public Mago(String hechizo, int nivel, String nombre, int salud) {
        super(nivel, nombre, salud);
        this.hechizo = hechizo;
    }

    
    @Override
    public void atacar(){
        super.atacar();
        System.out.println("... con el hechizo "+ hechizo);
    }
    
}
