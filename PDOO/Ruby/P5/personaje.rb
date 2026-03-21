require_relative 'ser_vivo'

class Personaje < Ser_vivo
  attr_accessor :tipo

  TIPO_MONSTRUO = 'Monstruo'
  TIPO_JUGADOR = 'Jugador'

  def initialize
    raise 'Error'
  end

  def atacar
    raise 'Error'
  end

  def defender
    raise 'Error'
  end
end
