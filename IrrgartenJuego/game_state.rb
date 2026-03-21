module Irrgarten
  class GameState
    attr_accessor :labyrinth, :players, :monsters, :current_player, :winner, :log

    def initialize(labyrinth, players, monsters, current_player, winner, log)
      @labyrinth = labyrinth.to_s
      @players = players
      @monsters = monsters
      @current_player = current_player.to_i
      @winner = winner
      @log = log.to_s
    end
  end
end
