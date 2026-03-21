# frozen_string_literal: true

# encoding:utf-8

# Importar todos los módulos y clases necesarias.
# Asegúrate de que los archivos de P1 (directions.rb, game_character.rb, weapon.rb, shield.rb, dice.rb, game_state.rb)
# y los nuevos de P2 (monster.rb, player.rb, labyrinth.rb, game.rb) se carguen correctamente.

# Suponiendo que el directorio principal es 'irrgarten' (módulo principal)
require_relative 'directions'
require_relative 'game_character'
require_relative 'weapon'
require_relative 'shield'
require_relative 'dice'
require_relative 'game_state'
require_relative 'monster'
require_relative 'player'
require_relative 'labyrinth'
require_relative 'game'

module Irrgarten
  # Clase TestP2 para organizar las pruebas
  class TestP2
    NROWS = 5
    NCOLS = 7
    NPLAYERS = 2

    # El método main para ejecutar las pruebas
    def self.main
      puts '--- PRUEBAS DE LA PRÁCTICA 2: CLASES PRINCIPALES (Ruby) ---'

      # 1. PRUEBA DE LA CLASE MONSTER
      test_monster

      puts "\n" + '---' * 20

      # 2. PRUEBA DE LA CLASE PLAYER
      test_player

      puts "\n" + '---' * 20

      # 3. PRUEBA DE LA CLASE LABYRINTH
      test_labyrinth

      puts "\n" + '---' * 20

      # 4. PRUEBA DE LA CLASE GAME (CONSTRUCTOR Y MÉTODOS SIMPLES)
      test_game

      puts "\n--- FIN DE PRUEBAS P2 ---"
    end

    # =========================================================================
    # MÉTODOS DE PRUEBA
    # =========================================================================

    def self.test_monster
      puts '## Prueba de Monster 👹'

      # El constructor de Monster toma (nombre, intelligence, strength) [cite: 370, 372]
      monster1 = Monster.new('Goblin', 5.0, 2.0)
      puts "1. Constructor/to_s: #{monster1}" # Prueba to_s [cite: 35]

      # Prueba set_pos
      monster1.set_pos(2, 3) # setPos en Java es set_pos en Ruby [cite: 34]
      puts "2. set_pos(2, 3): #{monster1}"

      # Prueba dead() (inicialmente debería ser false)
      puts "3. ¿Está muerto (dead)? #{monster1.dead}"

      # Los métodos attack/defend solo necesitan verificación de cabecera.
      # puts "6. Valor de attack(): #{monster1.attack}" # Delega en Dice [cite: 33]
    end

    def self.test_player
      puts '## Prueba de Player 🧑'

      # Constructor: toma (number, dice) [cite: 372] e inicializa el nombre como "Player #N" [cite: 40, 41]
      player1 = Player.new('0', 10, 10)
      puts "1. Constructor/to_s (Player #0): #{player1}" # Prueba to_s [cite: 51]

      player2 = Player.new('1', 9, 9)
      puts "2. Constructor/to_s (Player #1): #{player2}"

      # Prueba set_pos
      player1.set_pos(1, 1) # setPos en Java es set_pos en Ruby [cite: 44]
      puts "3. set_pos(1, 1): #{player1}"

      # Prueba resurrect()
      player1.resurrect # Vacía listas, reinicia salud e impactos [cite: 42, 43]
      puts "8. Después de resurrect: #{player1}"

      # Prueba dead()
      puts "9. ¿Está muerto (dead)? #{player1.dead}"

      # Prueba sum_weapons/shields y attack/defensive_energy
      # Estos requieren que el jugador tenga armas/escudos
      # puts "10. sum_weapons: #{player1.sum_weapons}" [cite: 58]
      # puts "11. sum_shields: #{player1.sum_shields}" [cite: 59]
      # puts "12. attack: #{player1.attack}" [cite: 49]
      # puts "13. defensive_energy: #{player1.defensive_energy}" [cite: 54]
    end

    def self.test_labyrinth
      puts '## Prueba de Labyrinth 🏰'

      # Asumiendo que el constructor toma (n_rows, n_cols, exit_row, exit_col)
      labyrinth = Labyrinth.new(NROWS, NCOLS, 3, 5)
      puts "1. Constructor/to_s: \n#{labyrinth}" # Prueba to_s [cite: 89]

      # Prueba add_monster
      monster2 = Monster.new('Orc', 4.0, 1.0)
      labyrinth.add_monster(1, 4, monster2) # Anota presencia y llama a monster.setPos [cite: 90]
      puts "7. Labyrinth después de add_monster(1, 4, Orc):\n#{labyrinth}"

      # Prueba have_a_winner
      puts "15. ¿Hay ganador (have_a_winner)? #{labyrinth.have_a_winner}"
    end

    def self.test_game
      puts '## Prueba de Game 🎲'

      # El constructor crea jugadores, laberinto, monstruos y configura el laberinto. [cite: 118, 119, 121]
      game = Game.new(NPLAYERS) # Asume un constructor Game.new(n_players)

      puts '1. Constructor: Laberinto/Jugadores inicializados.'

      # Prueba finished()
      puts "2. ¿Ha terminado (finished)? #{game.finished}" # Delega en labyrinth.have_a_winner [cite: 126]

      # Prueba next_player()
      # state = game.get_game_state # getGameState en Java es get_game_state en Ruby [cite: 127]
      # initial_player = state.get_current_player
      # game.next_player # Actualiza el jugador con el turno [cite: 130]
      # next_state = game.get_game_state
      # next_player = next_state.get_current_player
      # puts "3. next_player: Jugador actual: #{initial_player} -> #{next_player}"

      # Prueba los métodos log (concatenan cadenas al atributo log)
      game.log_player_won # logPlayerWon en Java es log_player_won en Ruby [cite: 131]
      game.log_monster_won # [cite: 133]
      game.log_resurrected # [cite: 135]
      game.log_player_skip_turn # [cite: 137]
      game.log_player_no_orders # [cite: 139]
      game.log_no_monster # [cite: 141]
      game.log_rounds(3, 5) # [cite: 143]

      # puts "4. Log después de varios eventos: #{game.get_game_state.get_log}" # Verifica el log
    end
  end
end # end module Irrgarten

# Línea de código para ejecutar el método main de TestP2 al ejecutar el fichero
Irrgarten::TestP2.main
