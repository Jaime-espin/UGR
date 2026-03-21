require_relative 'weapon'
require_relative 'shield'
require_relative 'labyrinthCharacter'

module Irrgarten
  class Player < LabyrinthCharacter
    MAX_WEAPONS = 2
    MAX_SHIELD = 3
    INITIAL_HEALTH = 10
    HITS2LOSE = 3

    def initialize(number, intelligence, strength)
      super(number, intelligence, strength, INITIAL_HEALTH)
      @number = number
      @weapons = []
      @shields = []
      @consecutive_hits = 0
    end

    def copia(lc)
      copia_labchar(lc)
      @weapons = lc.weapons
      @shields = lc.shields
      @consecutive_hits = lc.consecutive_hits
      @number = lc.number
    end

    def resurrect
      @health = INITIAL_HEALTH
      @weapons = []
      @shields = []
      @consecutive_hits = 0
    end

    def move(direction, valid_moves)
      size = valid_moves.size
      contained = valid_moves.include?(direction)

      if size > 0 && !contained
        valid_moves[0]
      else
        direction
      end
    end

    def attack
      @strength + sum_weapons
    end

    def defend(received_attack)
      manage_hit(received_attack)
    end

    def receive_reward
      w_reward = Dice.weapons_reward
      s_reward = Dice.shields_reward

      (1..w_reward).each do
        receive_weapon(new_weapon)
      end

      (1..s_reward).each do
        receive_shield(new_shield)
      end
      extra_health = Dice.health_reward
      @health += extra_health
      
      [w_reward, s_reward, extra_health]
    end

    def to_s
      weapons_str = @weapons.empty? ? "" : @weapons.map(&:to_s).join(", ")
      shields_str = @shields.empty? ? "" : @shields.map(&:to_s).join(", ")
      "Player##{@number} - " + super.to_s + " [Armas: #{weapons_str}] [Escudos: #{shields_str}]"
    end

    attr_reader :number, :col, :row, :intelligence, :strength, :shields, :weapons, :consecutive_hits

    private

    def receive_weapon(w)
      return unless w.is_a?(Weapon)
      
      @weapons.reject! { |weapon| weapon.discard }
      @weapons << w if @weapons.size < MAX_WEAPONS
    end

    def receive_shield(s)
      return unless s.is_a?(Shield)
      
      @shields.reject! { |shield| shield.discard }
      @shields << s if @shields.size < MAX_SHIELD
    end

    def new_weapon
      Weapon.new(Dice.weapon_power, Dice.uses_left)
    end

    def new_shield
      Shield.new(Dice.shield_power, Dice.uses_left)
    end

    def sum_weapons
      @weapons.sum { |weapon| weapon.attack }
    end

    def sum_shields
      @shields.sum { |shield| shield.protect }
    end

    def defensive_energy
      @intelligence + sum_shields
    end

    def manage_hit(received_attack)
      defense = defensive_energy
      if defense < received_attack
        got_wounded
        inc_consecutive_hits
      else
        reset_hits
      end

      lose = @consecutive_hits == HITS2LOSE || dead
      reset_hits if lose
      lose
    end

    def reset_hits
      @consecutive_hits = 0
    end

    def got_wounded
      @health -= 1
    end

    def inc_consecutive_hits
      @consecutive_hits += 1
    end
  end
end
