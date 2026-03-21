class Mago < Jugador
  def initialize(hechizo, nivel, nombre, salud)
    super(nivel, nombre, salud)
    @hechizo = hechizo
  end

  def atacar
    super
    puts '... con el hechizo ' + @hechizo.to_s
  end

  def aprender(hechizo)
    @hechizo = hechizo
  end
end
