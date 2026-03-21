require_relative 'personaje'
require_relative 'jugador'
require_relative 'mago'

p = Personaje.new('Jaime', 10)
j = Jugador.new(3, 'Jugador', 10)
m = Mago.new('Abracadabra', 10, 'boldemore', 10)

personajes = []

personajes << p << j << m

personajes.each do |p|
  p.atacar
end
