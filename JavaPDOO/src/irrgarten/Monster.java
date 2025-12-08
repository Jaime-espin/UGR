package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class Monster extends LabyrinthCharacter{
    private static final int INITIAL_HEALTH = 5;

    public Monster(String name, float intelligence, float strength) {
        super(name, intelligence, strength, INITIAL_HEALTH);
    }
    
    @Override
    public float attack(){
        Dice dado = new Dice();
        return dado.intensity(getStrength());
    }
    
    @Override
    public boolean defend(float receivedAttack){
        boolean isDead = this.dead();
        Dice dado = new Dice();
        if(!isDead){
            float defensiveEnergy = dado.intensity(getIntelligence());
            if(defensiveEnergy < receivedAttack){
                this.gotWounded();
                isDead = this.dead();
            }
        }
        return isDead;
    }  
}


















