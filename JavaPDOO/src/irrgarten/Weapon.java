package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class Weapon extends CombatElement{
    private float power;
    private int uses;

    public Weapon(float power, int uses) {
        super(power, uses);
    }
    
    public float attack(){
        return produceEffect();
    }
    
    @Override
    public String toString(){
        return "W[" + power + "," + uses + "]";
    }
}
