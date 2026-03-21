require_relative 'labyrinthCharacter'

module Irrgarten
  class Monster < LabyrinthCharacter
    INITIAL_HEALTH = 5

    def initialize(name, intelligence, strength)
      super(name, intelligence, strength, INITIAL_HEALTH)

      @row = -1
      @col = -1
    end

    def attack
      Dice.intensity(@strength)
    end

    def to_s
      super.to_s
    end

    def defend(received_attack)
      is_dead = dead
      unless is_dead
        defensive_energy = Dice.intensity(@intelligence)
        if defensive_energy < received_attack
          got_wounded
          is_dead = dead
        end
      end
      is_dead
    end

    private

    def got_wounded
      @health -= 1.0
    end
  end
end
