module Irrgarten
  class Dice
    MAX_USES = 5                  # número máximo de usos de armas y escudos
    MAX_INTELLIGENCE = 10.0       # valor máximo para la inteligencia de jugadores y monstruos
    MAX_STRENGTH = 10.0           # valor máximo para la fuerza de jugadores y monstruos
    RESURRECT_PROB = 0.3          # probabilidad de resurrección por turno
    WEAPONS_REWARD = 2            # número máximo de armas recibidas al ganar un combate
    SHIELDS_REWARD = 3            # número máximo de escudos recibidos al ganar un combate
    HEALTH_REWARD = 5             # número máximo de unidades de salud recibidas al ganar un combate
    MAX_ATTACK = 3                # máxima potencia de las armas
    MAX_SHIELD = 2                # máxima potencia de los escudos

    @@generator = Random.new

    def self.random_pos(max)
      @@generator.rand(0...max)
    end

    def self.who_starts(nplayers)
      @@generator.rand(0...nplayers)
    end

    def self.random_intelligence
      @@generator.rand(0...MAX_INTELLIGENCE).round(2)
    end

    def self.random_strength
      @@generator.rand(0...MAX_STRENGTH).round(2)
    end

    def self.resurrect_player
      @@generator.rand < RESURRECT_PROB
    end

    def self.weapons_reward
      @@generator.rand(0..WEAPONS_REWARD)
    end

    def self.shields_reward
      @@generator.rand(0..SHIELDS_REWARD)
    end

    def self.health_reward
      @@generator.rand(0..HEALTH_REWARD)
    end

    def self.weapon_power
      @@generator.rand(0...MAX_ATTACK)
    end

    def self.shield_power
      @@generator.rand(0...MAX_SHIELD)
    end

    def self.uses_left
      @@generator.rand(0..MAX_USES)
    end

    def self.intensity(competence)
      @@generator.rand(0...competence)
    end

    def self.discard_element(usesLeft)
      probability = 1.0 - (usesLeft.to_f / MAX_USES)
      @@generator.rand < probability
    end

    def self.nextstep(preference, validmoves, intelligence)
      if @@generator.rand(MAX_INTELLIGENCE) < intelligence
        direccion = preference
      else
        x = @@generator.rand(validmoves.size)
        direccion = validmoves[x]
      end
      direccion
    end
  end
end
