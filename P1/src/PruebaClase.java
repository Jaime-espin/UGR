/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class PruebaClase {
    public static void main(String[] args) {
        Monstruo m1 = new Monstruo("Marvin", TipoMonstruo.Orco);
        Monstruo m2 = new Monstruo("Omar", TipoMonstruo.Dragon);
        Monstruo m3 = new Monstruo("Jaime", TipoMonstruo.Esqueleto);

       System.out.println(m1.MostrarInfo());
       System.out.println(m2.MostrarInfo());
       System.out.println(m3.MostrarInfo());
    }
}
