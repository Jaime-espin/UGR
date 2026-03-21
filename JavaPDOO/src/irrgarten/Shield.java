package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class Shield extends CombatElement{

    public Shield(float protection, int uses) {
        super(protection, uses);
    }  
    
    public float protect(){
        return produceEffect();
    }

    @Override
    public String toString() {
        return "S[" + getEffect() + ", " + getUses() + ']';
    }
}