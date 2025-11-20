/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package utils;

import java.util.Random;
import monstruo.Monstruo;
import monstruo.TipoMonstruo;

/**
 *
 * @author Jaime Espín
 */
 
public class Utils {
    private static final Random RANDOM = new Random();
    
    public static float vidaAleatoria(){
        return 1.0f + RANDOM.nextFloat()* 49.0f;
    }
    
    public static String NombreAleatorio() {
       
        return "Monstruo" + Monstruo.listaMonstruos.size();
    }
    
    public static TipoMonstruo TipoAleatorio() {
        TipoMonstruo[] tipos = TipoMonstruo.values();
        int indiceAleatorio = RANDOM.nextInt(tipos.length);
        return tipos[indiceAleatorio];
    }
}
