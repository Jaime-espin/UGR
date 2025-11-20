package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
import java.util.Random;

public class Dice {
    private static final int MAX_USES = 5;                  // número máximo de usos de armas y escudos
    private static final float MAX_INTELLIGENCE = (float) 10.0;    // valor máximo para la inteligencia de jugadores y monstruos
    private static final float MAX_STRENGTH = (float) 10.0;        // valor máximo para la fuerza de jugadores y monstruos
    private static final float RESURRECT_PROB = (float) 0.3;       // probabilidad de resurrección por turno
    private static final int WEAPONS_REWARD = 2;            // número máximo de armas recibidas al ganar un combate
    private static final int SHIELDS_REWARD = 3;            // número máximo de escudos recibidos al ganar un combate
    private static final int HEALTH_REWARD = 5;             // número máximo de unidades de salud recibidas al ganar un combate
    private static final int MAX_ATTACK = 3;                // máxima potencia de las armas
    private static int MAX_SHIELD = 2;                // máxima potencia de los escudos
    
    // Atributo de clase para generación de números aleatorios
    private static final Random generator = new Random();
    
    public static int randomPos(int max){
        return generator.nextInt(max);
    }
    
    public static int whoStarts(int nplayers){
        return generator.nextInt(nplayers);
    }
    
    public static float randomIntelligence(){
        return generator.nextFloat(MAX_INTELLIGENCE);
    }
    
    public static float randomStrength(){
        return generator.nextFloat(MAX_STRENGTH);
    }
    
    public static boolean resurrectPlayer(){
        boolean resurrect=false;
        if(generator.nextFloat()<RESURRECT_PROB){
            resurrect = true;
        }
        return resurrect;
    }
    
    public static int weaponsReward(){
        return generator.nextInt(WEAPONS_REWARD+1);
    }
    
    public static int shieldsReward(){
        return generator.nextInt(SHIELDS_REWARD+1);
    }
    
    public static int healthReward(){
        return generator.nextInt(HEALTH_REWARD+1);
    }
    
    public static float weaponPower(){
        return generator.nextInt(MAX_ATTACK);
    }
    
    public static float shieldPower(){
        return generator.nextInt(MAX_SHIELD);
    }
    
    public static int usesLeft(){
        return generator.nextInt(MAX_USES+1);
    }
    
    public static float intensity(float competence){
        return generator.nextFloat(competence);
    }
    
    public static boolean discardElement(int usesLeft){
        if(usesLeft<=0){
            return true;
        }
        if (usesLeft >= MAX_USES) {
            return false;
        }
        
        double probabilityOfDiscard = (double) (MAX_USES - usesLeft) / MAX_USES;

        return generator.nextDouble() < probabilityOfDiscard;
    }
}
