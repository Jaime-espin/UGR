require 'io/console'
require_relative '../directions'

module Irrgarten
  module UI
    class TextUI
    # https://gist.github.com/acook/4190379
    def read_char
      STDIN.echo = false
      STDIN.raw!

      input = STDIN.getc.chr
      if input == "\e"
        begin
          input << STDIN.read_nonblock(3)
        rescue StandardError
          nil
        end
        begin
          input << STDIN.read_nonblock(2)
        rescue StandardError
          nil
        end
      end
    ensure
      STDIN.echo = true
      STDIN.cooked!

      return input
    end

    def next_move
      print 'Where? '
      got_input = false
      until got_input
        c = read_char
        case c
        when "\e[A"
          puts 'UP ARROW'
          output = Irrgarten::Directions::UP
          got_input = true
        when "\e[B"
          puts 'DOWN ARROW'
          output = Irrgarten::Directions::DOWN
          got_input = true
        when "\e[C"
          puts 'RIGHT ARROW'
          output = Irrgarten::Directions::RIGHT
          got_input = true
        when "\e[D"
          puts 'LEFT ARROW'
          output = Irrgarten::Directions::LEFT
          got_input = true
        when "\u0003"
          puts 'CONTROL-C'
          got_input = true
          exit(1)
        else
          # Error
        end
      end
      output
    end

    def show_game(game_state)
      # Limpiar la consola
      print "\e[2J\e[H"

      # Muestra el laberinto
      puts '--- LABERINTO ---'
      puts game_state.labyrinth
      puts

      # Muestra estado de jugadores y monstruos
      puts '--- JUGADORES ---'
      puts game_state.players
      puts '--- MONSTRUOS ---'
      puts game_state.monsters
      puts '-------------------'

      # Muestra el jugador actual y si hay ganador
      puts "Turno del jugador: #{game_state.current_player}"
      puts "¡¡¡ EL JUGADOR #{game_state.current_player} HA GANADO !!!" if game_state.winner
      puts

      # Muestra el log de eventos
      puts '--- LOG ---'
      puts game_state.log
      puts '-----------'
    end
    end # class
  end # module UI
end # module Irrgarten
