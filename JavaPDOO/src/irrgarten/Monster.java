package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class Monster {
    private static final int INITIAL_HEALTH = 5;

    private String name;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;

    public Monster(String name, float intelligence, float strength) {
        this.name = name;
        this.intelligence = intelligence;
        this.strength = strength;
        this.health = INITIAL_HEALTH;
        this.row = -1;
        this.col = -1;
    }
    
    public boolean dead(){     
        return health<=0;
    }
    
    public float attack(){
        Dice dado = new Dice();
        return dado.intensity(strength);
    }
    
    public boolean defend(float receivedAttack){
        boolean isDead = this.dead();
        Dice dado = new Dice();
        if(!isDead){
            float defensiveEnergy = dado.intensity(this.intelligence);
            if(defensiveEnergy < receivedAttack){
                this.gotWounded();
                isDead = this.dead();
            }
        }
        return isDead;
    }
    
    public void setPos(int row, int col){
        this.row=row;
        this.col=col;
    }
    
    @Override
    public String toString(){
        String s="Name: "+name+"\n"+"Intelligence: "+intelligence+"\n"+"Strength: "+strength+"\n"+"Health: "+health+"\n"+"["+row+","+col+"]";
        return s;
    }
    
    private void gotWounded(){
        health--;
    }  
}


















