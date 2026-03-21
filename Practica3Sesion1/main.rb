require_relative 'controlador/controlador'
require_relative 'modelo/contacto'
require_relative 'modelo/usuario'
require_relative 'vista/vista'

def flujoApp(controlador)
  # Flujo de la aplicación
  controlador.mostrar_perfil
  controlador.actualizar_perfil
  controlador.actualizar_informacion_contacto
end

# Inicialización de MVC
contacto = Modelo::Contacto.new('Calle Falsa 123', 'usuario@ejemplo.com', '600000000')
usuario = Modelo::Usuario.new('Nombre', 'Apellidos', contacto)
vista = Vista::VistaPerfilUsuario.new
controlador = Controlador::ControladorPerfilUsuario.new(usuario, vista)

# llamada a la función flujoApp
flujoApp(controlador)


