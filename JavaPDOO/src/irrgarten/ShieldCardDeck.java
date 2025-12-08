/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author Jaime Espín
 */
public class ShieldCardDeck extends CardDeck<Shield>{
    @Override
    protected void addCards(){
        final int N = 15;
        for (int i=0; i<N; i++){
            Shield escudo = new Shield(Dice.shieldPower(), Dice.usesLeft());
            addCard(escudo);
        }  
    }    
}
