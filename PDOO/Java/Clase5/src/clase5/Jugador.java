/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package clase5;

/**
 *
 * @author Jaime Espín
 */
public class Jugador extends Personaje{
    
    public Jugador(String tipo, String nombre, int vida){
        super(tipo, nombre, vida);
    }

    @Override
    public void atacar() {
        System.out.println("Nombre "+super.nombre+" ataca con espada");
    }

    @Override
    public void defender() {
        System.out.println("Nombre "+super.nombre+" defiende con escudo");
    }
}
