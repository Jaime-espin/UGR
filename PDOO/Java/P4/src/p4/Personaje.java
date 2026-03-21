/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package p4;

/**
 *
 * @author Jaime Espín
 */
public class Personaje {
    protected String nombre;
    protected int salud;

    public Personaje(String nombre, int salud) {
        this.nombre = nombre;
        this.salud = salud;
    }
    
    public void atacar(){
        System.out.println(nombre + " ataca\n");
    }
    
    public void recibirDato(int dato){
        salud -= dato;
    }
}
