require_relative 'directions'
require_relative 'orientation'
require_relative 'game_character'
require_relative 'weapon'
require_relative 'shield'
require_relative 'dice'
require_relative 'game_state'

module Irrgarten
  class TestP1
    def self.main
      puts "============== PRUEBA DE LA PRÁCTICA 1 EN RUBY ==============\n"

      # 1. Probar los "Enumerados" (Módulos)
      puts '## 1. Probando Módulos (Enumerados) ##'
      puts "Dirección: #{Directions::UP}"
      puts "Orientación: #{Orientation::HORIZONTAL}"
      puts "Personaje: #{GameCharacter::PLAYER}"
    puts "--------------------------------\n"

    # 2. Crear instancias y probar métodos de Weapon y Shield
    puts '## 2. Probando Weapon y Shield ##'
    weapon = Weapon.new(3.5, 4)
    shield = Shield.new(2.8, 3)

    puts "Arma inicial: #{weapon}"
    puts "Ataque 1: #{weapon.attack}"
    puts "Ataque 2: #{weapon.attack}"
    puts "Arma tras 2 usos: #{weapon}"
    puts "¿Descartar arma con 2 usos? #{weapon.discard}"

    puts "\nEscudo inicial: #{shield}"
    puts "Defensa 1: #{shield.protect}"
    puts "Escudo tras 1 uso: #{shield}"
    puts "¿Descartar escudo con 2 usos? #{shield.discard}"
    puts "--------------------------------\n"

    # 3. Probar la clase GameState
    puts '## 3. Probando GameState ##'
    game_state = GameState.new(
      '|S| | |M|',
      'P1(5, 4.5)',
      'M1(3, 2.1)',
      0,
      false,
      'Inicio del juego'
    )
    puts "Laberinto: #{game_state.labyrinth}"
    puts "Jugadores: #{game_state.players}"
    puts "Monstruos: #{game_state.monsters}"
    puts "Jugador Actual: #{game_state.current_player}"
    puts "Hay ganador: #{game_state.winner}"
    puts "Log: #{game_state.log}"
    puts "--------------------------------\n"

    # 4. Probar la clase Dice 100 veces
    puts '## 4. Probando el módulo Dice (100 iteraciones) ##'
    resurrection_count = 0
    num_iterations = 100

    puts "\n--- Pruebas de métodos de Dice ---"
    num_iterations.times do |i|
      # Solo se imprimen algunos para no saturar la consola
      if i < 5
        puts "random_pos(10): #{Dice.random_pos(10)}"
        puts "who_starts(4): #{Dice.who_starts(4)}"
        puts "random_intelligence: #{Dice.random_intelligence}"
        puts "random_strength: #{Dice.random_strength}"
        puts "weapons_reward: #{Dice.weapons_reward}"
        puts "shields_reward: #{Dice.shields_reward}"
        puts "health_reward: #{Dice.health_reward}"
        puts "weapon_power: #{Dice.weapon_power}"
        puts "shield_power: #{Dice.shield_power}"
        puts "uses_left: #{Dice.uses_left}"
        puts "intensity(8.0): #{Dice.intensity(8.0)}"
        puts '----------------'
      end

      resurrection_count += 1 if Dice.resurrect_player
    end

    puts "\n--- Resumen de Probabilidades ---"
    expected_prob = 0.3 * 100
    puts "Probabilidad de resurrección esperada: #{expected_prob}%"
    puts "Resurrecciones obtenidas en #{num_iterations} intentos: #{resurrection_count} (#{resurrection_count}%)"
    puts "--------------------------------\n"

    puts '============== FIN DE LA PRUEBA =============='
  end
  end
end

# Línea para ejecutar el programa principal
Irrgarten::TestP1.main
