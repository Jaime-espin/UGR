require_relative 'personaje'

class Monstruo < Personaje
  def initialize(nombre, vida)
    @nombre = nombre
    @vida = vida
    @tipo = Personaje::TIPO_MONSTRUO
  end

  def atacar
    puts @nombre + ' ataca con garra'
  end

  def defender
    puts @nombre + ' defiende con escudo de monstruo'
  end
end
