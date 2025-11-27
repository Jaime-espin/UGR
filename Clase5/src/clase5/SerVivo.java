/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package clase5;

/**
 *
 * @author Jaime Espín
 */
abstract public class SerVivo {
    protected String nombre;
    protected int vida;

    public SerVivo(String nombre, int vida) {
        this.nombre = nombre;
        this.vida = vida;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public void setVida(int vida) {
        this.vida = vida;
    }
    
    
}
