/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package monstruo;

/**
 *
 * @author Jaime Espín
 */
public class main {
    public static void main(String[] args) {
        Monstruo m1 = new Monstruo("Marvin", TipoMonstruo.Orco, 5);
        Monstruo m2 = new Monstruo("Omar", TipoMonstruo.Dragon, 5);
        Monstruo m3 = new Monstruo("Jaime", TipoMonstruo.Esqueleto, 5);

       /*System.out.println(m1.MostrarInfo());
       System.out.println(m2.MostrarInfo());
       System.out.println(m3.MostrarInfo());*/
       
       
       Monstruo.addRandomMonstruo();
       Monstruo.addRandomMonstruo();
       Monstruo.addRandomMonstruo();
       Monstruo.addRandomMonstruo();
       
      
       Monstruo.mostrarMonstruo();
               
         
    }
}
