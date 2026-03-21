/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package clase5;

/**
 *
 * @author Jaime Espín
 */
abstract public class Personaje extends SerVivo{
    public final static String TIPO_MONSTRUO = "Monstruo";
    public final static String TIPO_JUGADOR = "Jugador";
    protected String tipo;

    public Personaje(String tipo, String nombre, int vida) {
        super(nombre, vida);
        this.tipo = tipo;
    }
    
    abstract public void atacar();
    
    abstract public void defender();
    
    
    
}
