require_relative 'jugador'
require_relative 'monstruo'

j1 = Jugador.new('Jaime', 10)
m1 = Monstruo.new('Marvin', 10)

j1.atacar
m1.defender
j1.defender
m1.atacar
