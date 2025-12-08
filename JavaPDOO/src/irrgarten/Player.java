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
public class Player extends LabyrinthCharacter{
    private static final int MAX_WEAPONS = 2;
    private static final int MAX_SHIELD = 3;
    private static final int INITIAL_HEALTH = 10;
    private static final int HITS2LOSE = 3;
    
    private char number;
    private int consecutiveHits = 0;
    
    private ArrayList<Weapon> weapons;
    private ArrayList<Shield> shields;
    
    private ShieldCardDeck shieldCardDeck;
    private WeaponCardDeck weaponCardDeck;

    public Player(char number, float intelligence, float strength) {
        super("Player# " + number, intelligence, strength, INITIAL_HEALTH);
        this.number = number;
        this.weapons = new ArrayList<>();
        this.shields = new ArrayList<>();
        this.consecutiveHits=0;
        
        shieldCardDeck = new ShieldCardDeck();
        shieldCardDeck.addCards();
        weaponCardDeck = new WeaponCardDeck();
        weaponCardDeck.addCards();
        
    }
    
    public Player(Player p){
        super(p);
        number = p.number;
        shields = p.shields;
        weapons = p.weapons;
        shieldCardDeck = p.shieldCardDeck;
        weaponCardDeck = p.weaponCardDeck;
    }
    
    public void resurrect(){
        setHealth(INITIAL_HEALTH);
        this.weapons.clear();
        this.shields.clear();
        this.consecutiveHits=0;
    }

    public char getNumber() {
        return number;
    }
    
    public Directions move(Directions direction, ArrayList<Directions> validMoves){
        int size = validMoves.size();
        boolean contained = validMoves.contains(direction);
        
        if (size > 0 && !contained) {
            Directions firstElement = validMoves.get(0);
            return firstElement;
        } else {
            return direction;
        }
    }
    
    @Override
    public float attack(){
        return getStrength() + this.sumWeapons();
    }
    
    @Override
    public boolean defend(float receivedAttack){
        return manageHit(receivedAttack);
    }
    
    public void receiveReward(){
        Dice dado = new Dice();
        int wReward = dado.weaponsReward();
        int sReward = dado.shieldsReward();
        
        for(int i=1; i<wReward; i++){
            Weapon wnew = weaponCardDeck.nextCard();
            this.receiveWeapon(wnew);
        }
        for(int i=1; i<sReward; i++){
            Shield snew = shieldCardDeck.nextCard();
            this.receiveShield(snew);
        }
        int extraHealth = dado.healthReward();
        
        setHealth(getHealth()+extraHealth);
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
    
    /*
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
    */
    
    protected float sumWeapons(){
        float sum=0;
        for(int i=0; i<weapons.size(); i++){
            sum+=weapons.get(i).attack();
        }
        return sum;
    }
    
    protected float sumShields(){
        float sum=0;
        for(int i=0; i<shields.size(); i++){
            sum+=shields.get(i).protect();
        }
        return sum;
    }
    
    protected float defensiveEnergy(){
        return getIntelligence()+this.sumShields();
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
    
    private void incConsecutiveHits(){
         this.consecutiveHits++;
   }
    
}
