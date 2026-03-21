module Irrgarten
  class FuzzyPlayer < Player
    def move(direction, valid_moves)
      # FuzzyPlayer usa Dice para decidir su movimiento de forma difusa
      Dice.nextstep(direction, valid_moves, @intelligence)
    end

    def attack
      # Suma un componente de azar al ataque base
      super + Dice.intensity(@strength)
    end

    def to_s
      "Fuzzy " + super.to_s
    end
  end
end