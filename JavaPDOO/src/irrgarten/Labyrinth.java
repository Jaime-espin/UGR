package irrgarten;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
import java.util.ArrayList;
/**
 *
 * @author Jaime Espín
 */
public class Labyrinth {
    private static final char BLOCK_CHAR = 'X';
    private static final char EMPTY_CHAR = '-';
    private static final char MONSTER_CHAR = 'M';
    private static final char COMBAT_CHAR = 'C';
    private static final char EXIT_CHAR = 'E';
    private static final int ROW = 0;
    private static final int COL = 1;
    
    private Monster[][] monsters;
    private Player[][] players;
    private char[][] labyrinth;
    
    private int nRows;
    private int nCols;
    private int exitRow;
    private int exitCol;

    public Labyrinth(int nRows, int nCols, int exitRow, int exitCol) {
        this.nRows = nRows;
        this.nCols = nCols;
        this.exitRow = exitRow;
        this.exitCol = exitCol;
        
        this.monsters = new Monster[nRows][nCols];
        this.players = new Player[nRows][nCols];
        this.labyrinth = new char[nRows][nCols];
        
        for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
                this.labyrinth[i][j] = EMPTY_CHAR;
            }
        }
        
        this.labyrinth[exitRow][exitCol] = EXIT_CHAR;
    }
    
    public boolean haveAWinner(){
        return players[exitRow][exitCol]!=null;
    }
    
    @Override
    public String toString(){
        String s = "";

        s += "LABYRINTH (Dimensions: " + nRows + " X " + nCols + ")\n";

        for (int i = 0; i < nRows; i++) {
            for (int c = 0; c < nCols; c++) {
                s += "---"; 
            }
            s += "\n";
            s += "| ";
            for (int j = 0; j < nCols; j++) {
                s += labyrinth[i][j];
                s += " | ";
            }
            s += "\n";
        }
        return s;
    }
    
    public void addMonster(int row,int col, Monster monster){
        if(posOK(row, col)){
            labyrinth[row][col]=MONSTER_CHAR;
            monster.setPos(row, col);
            monsters[row][col]=monster;
        }
    }
    
    private boolean posOK(int row, int col){
        return row<nRows && col<nCols && row>=0 && col>=0;
    }
    
    private boolean emptyPos(int row, int col){
        return posOK(row, col)&& labyrinth[row][col]==EMPTY_CHAR;
    }
    
    private boolean monsterPos(int row, int col){
        return labyrinth[row][col]==MONSTER_CHAR;
    }
    
    private boolean exitPos(int row, int col){
        return row==exitRow && col==exitCol;
    }
    
    private boolean combatPos(int row, int col){
        return labyrinth[row][col]==COMBAT_CHAR;
    }
    
    private boolean canStepOn(int row, int col){
        return posOK(row, col) && (emptyPos(row, col) || monsterPos(row, col) || exitPos(row, col));
    }
    
    private void updateOldPos(int row, int col){
        if(posOK(row, col)){
            if(combatPos(row, col)){
                labyrinth[row][col]=MONSTER_CHAR;
            }else{
                labyrinth[row][col]=EMPTY_CHAR;
            }
        }
    }
    
    private int[] dir2Pos(int row, int col, Directions direction){
        int[] pos = new int[2];
        if(null!=direction)switch (direction) {
            case DOWN:
                row+=1;
                break;
            case LEFT:
                col-=1;
                break;
            case RIGHT:
                col+=1;
                break;
            case UP:
                row-=1;
                break;
            default:
                break;
        }
        pos[0]=row;
        pos[1]=col;
        return pos;
    }
    
    private int[] randomEmptyPos(){
        Dice dado = new Dice();
        int[] pos = new int[2];
        int row;
        int col;
        do{
            row=dado.randomPos(this.nRows);
            col=dado.randomPos(this.nCols);
        }while(!emptyPos(row, col));
        
        pos[0]=row;
        pos[1]=col;
        return pos;
    }
    
    public void spreadPlayers(Player[] players){
        for(int i=0; i < players.length; i++){
            Player p = players[i];
            int[] pos = this.randomEmptyPos();
            this.putPlayer2D(-1, -1, pos[ROW], pos[COL], p);
        }
    }
    
    public Monster putPlayer(Directions direction, Player player){
        int oldRow = player.getRow();
        int oldCol = player.getCol();
        int[] newPos = this.dir2Pos(oldRow, oldCol, direction);
        Monster monster = this.putPlayer2D(oldRow, oldCol, newPos[ROW], newPos[COL], player);
        return monster;
    }
    
    public void addBlock(Orientation orientation, int startRow, int startCol, int length){
        int incRow, incCol;
        if(orientation == Orientation.VERTICAL){
            incRow=1;
            incCol=0;
        }else{
            incRow=0;
            incCol=1;
        }
        int row=startRow;
        int col=startCol;
        
        while(this.posOK(row, col) && this.emptyPos(row, col) && length > 0){
            this.labyrinth[row][col]=BLOCK_CHAR;
            length -= 1;
            row += incRow;
            col += incCol;
        }
    }
    public ArrayList<Directions> validMoves(int row,int col){
        ArrayList<Directions> output = new ArrayList<>();
        if (this.canStepOn(row+1, col))
            output.add(Directions.DOWN);
        if (this.canStepOn(row-1, col))
            output.add(Directions.UP);
        if (this.canStepOn(row, col+1))
            output.add(Directions.RIGHT);
        if (this.canStepOn(row, col-1))
            output.add(Directions.LEFT);
        
        return output;
    }
    
    private Monster putPlayer2D(int oldRow, int oldCol, int row, int col, Player player){
        Monster output = null;
        if(this.canStepOn(row, col)){
            if(this.posOK(oldRow, oldCol)){
                Player p = this.players[oldRow][oldCol];
                if(p==player){
                    this.updateOldPos(oldRow, oldCol);
                    this.players[oldRow][oldCol]=null;
                }
            }
            boolean monsterPos = this.monsterPos(row, col);
            
            if(monsterPos){
                this.labyrinth[row][col] = COMBAT_CHAR;
                output = this.monsters[row][col];
            }else{
                char number = player.getNumber();
                this.labyrinth[row][col] = number;
            }
            this.players[row][col] = player;
            
            player.setPos(row, col);
        }
        
        return output;
    }
}
