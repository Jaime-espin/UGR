/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package clase5;

/**
 *
 * @author Jaime Espín
 */
public class Monstruo extends Personaje{
    
    public Monstruo(String tipo, String nombre, int vida){
        super(tipo, nombre, vida);
    }
    
    @Override
    public void atacar() {
        System.out.println("Nombre "+super.nombre+" ataca con garras");
    }

    @Override
    public void defender() {
        System.out.println("Nombre "+super.nombre+" defiende con escudo de monstruo");
    }
}
