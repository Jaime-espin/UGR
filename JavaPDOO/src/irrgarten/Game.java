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
public class Game {
    
    private static final int NUM_PLAYERS = 2; 
    private static final int NUM_MONSTERS = 3;
    private static final int DEFAULT_N_ROWS = 10;
    private static final int DEFAULT_N_COLS = 10;
    private static final int DEFAULT_EXIT_ROW = 0;
    private static final int DEFAULT_EXIT_COL = 9;
    private static final float DEFAULT_INTELLIGENCE = 10;
    private static final float DEFAULT_STREGNTH = 10;
    
    
    private static final int MAX_ROUNDS = 10;
    private int currentPlayerIndex;
    private String log;
    
    private Labyrinth labyrinth;
    private ArrayList<Monster> monsters;
    private ArrayList<Player> players;
    private Player currentPlayer;

    public Game(int nplayers) {
        this.monsters = new ArrayList<>();
        this.log = "";
        
        this.players = new ArrayList<>();
        
        for(int i = 0; i<nplayers; i++){
            Player newPlayer = new Player((char)(i+1), DEFAULT_INTELLIGENCE, DEFAULT_STREGNTH);
            this.players.add(newPlayer);
        }
        
        this.labyrinth = new Labyrinth(DEFAULT_N_ROWS,DEFAULT_N_COLS,DEFAULT_EXIT_ROW,DEFAULT_EXIT_COL);
        
        Dice dado = new Dice();
        
        this.currentPlayerIndex = dado.whoStarts(nplayers);
        
        this.currentPlayer = this.players.get(this.currentPlayerIndex);
        
        this.configureLabyrinth();
        
        this.labyrinth.spreadPlayers(this.players.toArray(new Player[0]));
    }
    
   public boolean finished(){
       return this.labyrinth.haveAWinner();
   }
   
   public boolean nextStep(Directions preferredDirection){
       log = "";
       boolean dead = this.currentPlayer.dead();
       Directions direction = this.actualDirection(preferredDirection);
       if(!dead){
        if(direction != preferredDirection){
            this.logPlayernoOrders();
        }
        Monster monster = this.labyrinth.putPlayer(direction, currentPlayer);

        if(monster == null){
            this.logNoMonster();
        }else{
            GameCharacter winner = this.combat(monster);
            this.manageReward(winner);
        }
       }else{
           this.manageResurrection();
       }
       boolean endGame = this.finished();
       if(!endGame){
           this.nextPlayer();
       }
       return endGame;
   }
   
   public GameState getGameState(){
       GameState gamestate = new GameState(this.labyrinth.toString(), this.players.toString(), this.monsters.toString(), this.currentPlayerIndex, this.finished(), this.log);
       return gamestate;
   }
   
   private void configureLabyrinth(){
       this.labyrinth.addBlock(Orientation.VERTICAL, 2, 2, 5);
       this.labyrinth.addBlock(Orientation.HORIZONTAL, 7, 1, 6);
       
       Monster monster1 = new Monster("Monster1", Dice.randomIntelligence(), Dice.randomStrength());
       monsters.add(monster1);
       labyrinth.addMonster(2, 3, monster1);
   }
   
   private void nextPlayer(){
       this.currentPlayerIndex = (this.currentPlayerIndex+1)%this.players.size();
       this.currentPlayer=this.players.get(this.currentPlayerIndex);
   }
   
   private void logPlayerWon(){
       log += "Jugador gana combate: " + this.currentPlayer + "\n";
   }
   
   private void logMonsterWon(){
       log += "Montruo gana combate: " + this.monsters.get(this.currentPlayerIndex) + "\n";
   }
   
   private void logResurrected(){
       log += "Jugador resucitado: " + this.currentPlayer + "\n";
   }
   
   private void logPlayerSkipTurn(){
       log += "Jugador pierde turno por estar muerto: " + this.currentPlayer + "\n";
   }
   
   private void logPlayernoOrders(){
       log += "No fue posible seguir las instrucciones \n";
   }
   
   private void logNoMonster(){
       log += "Jugador en cleda vacía/no fue posible moverse \n";
   }
   
   private void logRound(int rounds, int max){
       log += "Se han producido "+ rounds +" de " + max + " rondas de combate";
   }
   

   private Directions actualDirection(Directions preferredDirection){
       int currentRow = this.currentPlayer.getRow();
       int currentCol = this.currentPlayer.getCol();
       Directions[] validMoves = this.labyrinth.validMoves(currentRow, currentCol);
       Directions output = this.currentPlayer.move(preferredDirection, validMoves);
       return output;
   }
   private GameCharacter combat(Monster monster){
       int rounds = 0;
       GameCharacter winner = GameCharacter.PLAYER;
       
       float playerAttack = this.currentPlayer.attack();
       boolean lose = monster.defend(playerAttack);
       
       while((!lose) && (rounds < MAX_ROUNDS)){
           winner = GameCharacter.MONSTER;
           rounds++;
           float monsterAttack = monster.attack();
           lose = this.currentPlayer.defend(monsterAttack);
           if(!lose){
               playerAttack=this.currentPlayer.attack();
               winner = GameCharacter.PLAYER;
               lose = monster.defend(playerAttack);
           }
       }
       this.logRound(rounds, MAX_ROUNDS);
       return winner;
   }
   private void manageReward(GameCharacter winner){
       if(winner == GameCharacter.PLAYER){
           this.currentPlayer.receiveReward();
           this.logPlayerWon();
       }else{
           this.logMonsterWon();
       }
   }
   private void manageResurrection(){
       Dice dado = new Dice();
       
       boolean resurrect = dado.resurrectPlayer();
       
       if(resurrect){
           this.currentPlayer.resurrect();
           this.logResurrected();
       }else{
           this.logPlayerSkipTurn();
       }
   }

}