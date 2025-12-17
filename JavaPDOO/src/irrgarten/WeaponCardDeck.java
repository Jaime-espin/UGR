/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package irrgarten;

/**
 *
 * @author Jaime Espín
 */
public class WeaponCardDeck extends CardDeck<Weapon>{
    @Override
    protected void addCards(){
        final int N = 15;
        for (int i=0; i<N; i++){
            Weapon arma = new Weapon(Dice.weaponPower(), Dice.usesLeft());
            addCard(arma);
        }
        
    }
}
