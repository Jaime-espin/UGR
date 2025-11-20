package monstruo;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */

import java.util.ArrayList;
import utils.Utils;

public class Monstruo {
    private static int MAX_MONSTRUOS=10;
    public static ArrayList<Monstruo> listaMonstruos = new ArrayList<Monstruo>();
    
    private String nombre;
    private TipoMonstruo tipo;
    private float vida;
    

    public Monstruo(String nombre, TipoMonstruo tipo, float vida) {
        this.nombre = nombre;
        this.tipo = tipo;
        this.vida = vida;
    }
    
    public String MostrarInfo(){
        return "Nombre="+nombre+"\n Tipo="+tipo+"\n Vida="+vida;
    }
    
    public float ataque(float a){
        vida-=a;
        return vida;
    }
    
    public static Monstruo buscarMonstruo(String m){
        Monstruo monster = null;
        boolean encontrado=false;
        for(int i = 0; i<MAX_MONSTRUOS || encontrado; i++){
            if(listaMonstruos.get(i).nombre==m){
                encontrado = true;
                monster=listaMonstruos.get(i);
            }
        }
        return monster;        
    }
    
    public static void mostrarMonstruo(){
        for(Monstruo m : listaMonstruos ){
            System.out.println(m.MostrarInfo());
        }
    }
    
    private static void addMonstruo(String n, float v, TipoMonstruo tipo){
        if(buscarMonstruo(n)!=null && listaMonstruos.size()<MAX_MONSTRUOS){
            listaMonstruos.add(new Monstruo(n,tipo,v));
        }
    }
    
    public static void addRandomMonstruo(){
        float vida = Utils.vidaAleatoria();
        String nombre = Utils.NombreAleatorio();
        TipoMonstruo ti = Utils.TipoAleatorio();
        
    }
    
}