/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class Monstruo {
    private String nombre;
    private TipoMonstruo tipo;

    public Monstruo(String nombre, TipoMonstruo tipo) {
        this.nombre = nombre;
        this.tipo = tipo;
    }
    
    public String MostrarInfo(){
        return "Nombre="+nombre+"\n Tipo="+tipo;
    }
}




