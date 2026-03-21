class Monstruo

  def initialize(nombre, tipo)
    @nombre = nombre
    @tipo = tipo
  end

  def mostrar_info
    "Nombre: #{@nombre}, Tipo: #{@tipo}"
  end
end