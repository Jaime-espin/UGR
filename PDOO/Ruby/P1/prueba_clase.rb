require_relative 'tipo_monstruo.rb'
require_relative 'monstruo.rb'

m1 = Monstruo.new("Jaime", TipoMonstruo::ESQUELETO)
m2 = Monstruo.new("Marvin", TipoMonstruo::ORCO)
m3 = Monstruo.new("Omar", TipoMonstruo::DRAGON)

puts m1.mostrar_info
puts m2.mostrar_info
puts m3.mostrar_info