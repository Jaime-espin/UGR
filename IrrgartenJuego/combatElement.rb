module Irrgarten
  class CombatElement
    def initialize(effect, uses)
      @effect = effect
      @uses = uses
    end

    protected

    def produce_effect
      if @uses > 0
        @uses -= 1
        @effect
      else
        0
      end
    end

    public

    def discard
      Dice.discard_element(@uses)
    end

    def to_s
      efecto = @effect || ' '
      usos = @uses || ' '
      "#{efecto} #{usos}"
    end

    private_class_method :new
  end
end
