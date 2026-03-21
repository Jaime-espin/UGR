class Personaje
  def initialize(nombre, salud)
    @nombre = nombre
    @salud = salud
  end

  def atacar
    puts @nombre.to_s + " ataca\n"
  end

  def recibirDato(dato)
    @salud -= dato
  end
end
