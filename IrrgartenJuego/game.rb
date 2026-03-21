require_relative 'game_character'
require_relative 'player'
require_relative 'monster'
require_relative 'labyrinth'
require_relative 'dice'
require_relative 'orientation'
require_relative 'game_state'
module Irrgarten
  class Game
    NUM_PLAYERS = 2
    NUM_MONSTERS = 3
    DEFAULT_N_ROWS = 10
    DEFAULT_N_COLS = 10
    DEFAULT_EXIT_ROW = 0
    DEFAULT_EXIT_COL = 9
    DEFAULT_INTELLIGENCE = 10.0
    DEFAULT_STRENGTH = 10.0

    MAX_ROUNDS = 10
    def initialize(nplayers)
      @monsters = []
      @log = ''

      @players = []

      (0...nplayers).each do |i|
        new_player = Player.new((i + 1).to_s, DEFAULT_INTELLIGENCE, DEFAULT_STRENGTH)
        @players << new_player
      end

      @labyrinth = Labyrinth.new(DEFAULT_N_ROWS, DEFAULT_N_COLS, DEFAULT_EXIT_ROW, DEFAULT_EXIT_COL)

      @current_player_index = Dice.who_starts(nplayers)

      @current_player = @players[@current_player_index]

      configure_labyrinth

      @labyrinth.spread_players(@players)
    end

    def finished
      @labyrinth.have_a_winner
    end

    def next_step(preferred_direction)
      @log = ''
      dead = @current_player.dead
      unless dead
        direction = actual_direction(preferred_direction)
        log_player_no_orders if direction != preferred_direction
        monster = @labyrinth.put_player(direction, @current_player)
        if monster.nil?
          log_no_monster
        else
          winner = combat(monster)
          manage_reward(winner, monster)
        end
      else
        manage_resurrection
      end
      # Después de procesar el paso, pasar al siguiente jugador solo si el juego no ha terminado
      next_player unless finished

      # Devolver booleano que indica si el juego ha terminado
      finished
    end

    def get_game_state
      Irrgarten::GameState.new(
        @labyrinth.to_s,
        @players,
        @monsters,
        @current_player_index + 1,
        finished,
        @log
      )
    end

    def log_player_won
      @log += "Jugador gana combate: #{@current_player}\n"
    end

    def log_monster_won(monster = nil)
      monster_str = monster ? monster.to_s : "Monstruo"
      @log += "Monstruo gana combate: #{monster_str}\n"
    end

    def log_resurrected
      @log += "Jugador resucitado: #{@current_player}\n"
    end

    def log_player_skip_turn
      @log += "Jugador pierde turno por estar muerto: #{@current_player}\n"
    end

    def log_player_no_orders
      @log += "No fue posible seguir las instrucciones \n"
    end

    def log_no_monster
      @log += "Jugador en celda vacía/no fue posible moverse \n"
    end

    def log_rounds(rounds, max)
      @log += "Se han producido #{rounds} de #{max} rondas de combate\n"
    end

    def log_reward(weapons, shields, health)
      @log += "Recompensa recibida: #{weapons} arma(s), #{shields} escudo(s), #{health} puntos de salud\n"
    end

    private

    def configure_labyrinth
      @labyrinth.add_block(Orientation::VERTICAL, 2, 2, 5)
      @labyrinth.add_block(Orientation::HORIZONTAL, 7, 1, 6)

      monster1 = Monster.new('Monster1', Dice.random_intelligence, Dice.random_strength)
      @monsters << monster1
      @labyrinth.add_monster(2, 3, monster1)
    end

    def next_player
      @current_player_index = (@current_player_index + 1) % @players.size
      @current_player = @players[@current_player_index]
    end

    def actual_direction(preferred_direction)
      current_row = @current_player.row
      current_col = @current_player.col
      valid_moves = @labyrinth.valid_moves(current_row, current_col)
      @current_player.move(preferred_direction, valid_moves)
    end

    def combat(monster)
      rounds = 0
      winner = GameCharacter::PLAYER
      player_attack = @current_player.attack
      lose = monster.defend(player_attack)

      while !lose && rounds < MAX_ROUNDS
        rounds += 1
        monster_attack = monster.attack
        lose = @current_player.defend(monster_attack)
        if lose
          winner = GameCharacter::MONSTER
          break
        end

        player_attack = @current_player.attack
        lose = monster.defend(player_attack)
      end
      
      # Si salimos del bucle porque se alcanzó MAX_ROUNDS sin que nadie muriera, gana el monstruo
      if !lose && rounds >= MAX_ROUNDS
        winner = GameCharacter::MONSTER
      end
      
      log_rounds(rounds, MAX_ROUNDS)
      winner
    end

    def manage_reward(winner, monster)
      if winner == GameCharacter::PLAYER
        rewards = @current_player.receive_reward
        log_player_won
        log_reward(rewards[0], rewards[1], rewards[2])
      else
        log_monster_won(monster)
      end
    end

    def manage_resurrection
      resurrect = Dice.resurrect_player
      if resurrect
        @current_player.resurrect
        log_resurrected
      else
        log_player_skip_turn
      end
    end
  end
end
