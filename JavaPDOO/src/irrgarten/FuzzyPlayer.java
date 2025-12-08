/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;
import java.util.ArrayList;

/**
 *
 * @author Jaime Espín
 */
public class FuzzyPlayer extends Player{

    public FuzzyPlayer(Player p) {
        super(p);
    }

    @Override
    public Directions move(Directions direction, ArrayList<Directions> validMoves) {
        Directions output;
        boolean contained = validMoves.contains(direction);
        if (contained && validMoves.size()>0){
            output = Dice.nextStep(direction, validMoves, getIntelligence());
        }
        else
        {
            validMoves.remove(direction);
            output = Dice.nextStep(validMoves.get(0), validMoves, getIntelligence());
        }
        return output;
    }

    @Override
    public float attack() {
        return super.attack();
    }
    
    protected float deffensiveEnergy(){
        return super.defensiveEnergy();
    }    
    
    @Override
    public String toString(){
        return "Fuzzy" + super.toString();
    }
    
}
