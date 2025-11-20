package irrgarten;


import java.util.ArrayList;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */

/**
 *
 * @author Jaime Espín
 */
public class Player {
    private static final int MAX_WEAPONS = 2;
    private static final int MAX_SHIELD = 3;
    private static final int INITIAL_HEALTH = 10;
    private static final int HITS2LOSE = 3;
    
    private String name;
    private char number;
    private float intelligence;
    private float strength;
    private float health;
    private int row;
    private int col;
    private int consecutiveHits = 0;
    
    private ArrayList<Weapon> weapons;
    private ArrayList<Shield> shields;

    public Player(char number, float intelligence, float strength) {
        this.number = number;
        this.intelligence = intelligence;
        this.strength = strength;
        
        this.name = "Player #"+number;
        
        this.health=INITIAL_HEALTH;
        this.weapons = new ArrayList<>();
        this.shields = new ArrayList<>();
        this.consecutiveHits=0;
    }
    
    public void resurrect(){
        this.health=INITIAL_HEALTH;
        this.weapons.clear();
        this.shields.clear();
        this.consecutiveHits=0;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public char getNumber() {
        return number;
    }
    
    public void setPos(int row, int col){
        this.row=row;
        this.col=col;
    }
    
    public boolean dead(){
        return this.health<=0;
    }
    
    public Directions move(Directions direction, Directions[] validMoves){
        int size = validMoves.length;
        boolean contained = false;
        for (int i=0; i<size; i++) {
            Directions d = validMoves[i];
            if (d == direction) {
                contained = true;
                break;
            }
        }
        
        if (size > 0 && !contained) {
            Directions firstElement = validMoves[0];
            return firstElement;
        } else {
            return direction;
        }
    }
    
    public float attack(){
        return this.strength + this.sumWeapons();
    }
    
    public boolean defend(float receivedAttack){
        return manageHit(receivedAttack);
    }
    
    public void receiveReward(){
        Dice dado = new Dice();
        int wReward = dado.weaponsReward();
        int sReward = dado.shieldsReward();
        
        for(int i=1; i<wReward; i++){
            Weapon wnew = this.newWeapon();
            this.receiveWeapon(wnew);
        }
        for(int i=1; i<sReward; i++){
            Shield snew = this.newShield();
            this.receiveShield(snew);
        }
        int extraHealth = dado.healthReward();
        
        this.health += extraHealth;
    }
    
    @Override
    public String toString(){
        String s = this.name + "\n" + "  Stats: [Int=" + this.intelligence + ", Str=" + this.strength + ", Health=" + this.health + "]\n" + "  Position: [" + this.row + ", " + this.col + "]\n" +"  Items: [" + this.weapons.size() + " Armas, " + this.shields.size() + " Escudos]\n" + "  Consecutive Hits: " + this.consecutiveHits;
        return s;
   }
    
    private void receiveWeapon(Weapon w){
        Weapon wi;
        int size = this.weapons.size();
        for(int i = 0; i < size; i++){
            wi=this.weapons.get(i);
            boolean discard = wi.discard();
            if(discard){
                this.weapons.remove(wi);
            }
        }
        if(size<MAX_WEAPONS){
            this.weapons.add(w);
        } 
    }
    
    private void receiveShield(Shield s){
        Shield si;
        int size = this.shields.size();
        for(int i = 0; i < size; i++){
            si=this.shields.get(i);
            boolean discard = si.discard();
            if(discard){
                this.shields.remove(si);
            }
        }
        if(size<MAX_SHIELD){
            this.shields.add(s);
        } 
    }
    
    private Weapon newWeapon(){
        Dice dado=new Dice();
        Weapon arma= new Weapon(dado.weaponPower(), dado.usesLeft());
        return arma;
    }
    
    private Shield newShield(){
        Dice dado=new Dice();
        Shield escudo= new Shield(dado.shieldPower(), dado.usesLeft());
        return escudo;
    }
    
    private float sumWeapons(){
        float sum=0;
        for(int i=0; i<weapons.size(); i++){
            sum+=weapons.get(i).attack();
        }
        return sum;
    }
    
    private float sumShields(){
        float sum=0;
        for(int i=0; i<shields.size(); i++){
            sum+=shields.get(i).protect();
        }
        return sum;
    }
    
    private float defensiveEnergy(){
        return this.intelligence+this.sumShields();
    }
    
    private boolean manageHit(float recievedAttack){
        float defense = this.defensiveEnergy();
        boolean lose;
        
        if(defense < recievedAttack){
            this.gotWounded();
            this.incConsecutiveHits();
        }else{
            this.resetHits();
        }
        
        if(this.consecutiveHits==HITS2LOSE || this.dead()){
            this.resetHits();
            lose=true;
        }else{
            lose=false;
        }
        return lose;
    }
    
    private void resetHits(){
        this.consecutiveHits=0;
    }
    
    private void gotWounded(){
        this.health--;
    }
    
    private void incConsecutiveHits(){
         this.consecutiveHits++;
   }
    
}
