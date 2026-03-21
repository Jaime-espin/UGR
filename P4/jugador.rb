class Jugador < Personaje
  def initialize(nivel, nombre, salud)
    super(nombre, salud)
    @nivel = nivel
  end

  def atacar
    super
    puts '... con nivel ' + @nivel.to_s
  end

  def subir_nivel
    @nivel += 1
  end
end
