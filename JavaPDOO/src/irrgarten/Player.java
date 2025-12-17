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
        this.number = p.number;
        this.consecutiveHits = p.consecutiveHits;
        
        // Copia profunda de las armas
        this.weapons = new ArrayList<>();
        for (Weapon w : p.weapons) {
            this.weapons.add(w);
        }
        
        // Copia profunda de los escudos
        this.shields = new ArrayList<>();
        for (Shield s : p.shields) {
            this.shields.add(s);
        }
        
        // Los CardDecks se comparten (son mazo común)
        this.shieldCardDeck = p.shieldCardDeck;
        this.weaponCardDeck = p.weaponCardDeck;
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
        int wReward = Dice.weaponsReward();
        int sReward = Dice.shieldsReward();
        
        for(int i=0; i<wReward; i++){
            Weapon wnew = weaponCardDeck.nextCard();
            this.receiveWeapon(wnew);
        }
        for(int i=0; i<sReward; i++){
            Shield snew = shieldCardDeck.nextCard();
            this.receiveShield(snew);
        }
        int extraHealth = Dice.healthReward();
        
        setHealth(getHealth()+extraHealth);
    }
    
    private void receiveWeapon(Weapon w){
        // Eliminar armas descartadas iterando hacia atrás
        for(int i = this.weapons.size() - 1; i >= 0; i--){
            Weapon wi = this.weapons.get(i);
            boolean discard = wi.discard();
            if(discard){
                this.weapons.remove(i);
            }
        }
        // Añadir nueva arma si hay espacio
        if(this.weapons.size() < MAX_WEAPONS){
            this.weapons.add(w);
        } 
    }
    
    private void receiveShield(Shield s){
        // Eliminar escudos descartados iterando hacia atrás
        for(int i = this.shields.size() - 1; i >= 0; i--){
            Shield si = this.shields.get(i);
            boolean discard = si.discard();
            if(discard){
                this.shields.remove(i);
            }
        }
        // Añadir nuevo escudo si hay espacio
        if(this.shields.size() < MAX_SHIELD){
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
    
    private boolean manageHit(float receivedAttack){
        float defense = this.defensiveEnergy();
        boolean lose;
        
        if(defense < receivedAttack){
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
    
    @Override
    public String toString() {
        String result = super.toString();
        
        // Añadir información de armas
        result += " Weapons: [";
        for (int i = 0; i < weapons.size(); i++) {
            result += weapons.get(i).toString();
            if (i < weapons.size() - 1) {
                result += ", ";
            }
        }
        result += "]";
        
        // Añadir información de escudos
        result += " Shields: [";
        for (int i = 0; i < shields.size(); i++) {
            result += shields.get(i).toString();
            if (i < shields.size() - 1) {
                result += ", ";
            }
        }
        result += "]";
        
        return result;
    }
    
}
