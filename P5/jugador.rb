require_relative 'personaje'

class Jugador < Personaje
  def initialize(nombre, vida)
    @nombre = nombre
    @vida = vida
    @tipo = Personaje::TIPO_JUGADOR
  end

  def atacar
    puts @nombre + ' ataca con espada'
  end

  def defender
    puts @nombre + ' defiende con escudo'
  end
end
