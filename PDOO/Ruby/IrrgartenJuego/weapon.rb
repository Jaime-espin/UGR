require_relative 'combatElement'
module Irrgarten
  class Weapon < CombatElement
    def initialize(power, uses)
      super(power, uses)
    end

    def attack
      produce_effect
    end

    def to_s
      "W[#{super}]"
    end

    public_class_method :new
  end
end
