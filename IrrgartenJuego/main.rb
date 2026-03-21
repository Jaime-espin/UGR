require_relative './game'
require_relative './ui/textUI'
require_relative './controller/controller'

# --- Ejecución Principal ---
  # 1. Crear la vista
  # Asumiendo que TextUI está en Irrgarten::UI
  view = Irrgarten::UI::TextUI.new

  # 2. Crear el modelo del juego
  # El constructor de Game necesita el número de jugadores [cite: 460]
  n_players = 2 # Asumimos 2 jugadores
  game = Irrgarten::Game.new(n_players)

  # 3. Crear el controlador
  # Asumiendo que Controller está en Irrgarten::Controller
  # y que recibe el juego y la vista [cite: 531]
  controller = Irrgarten::Controller::Controller.new(game, view)

  # 4. Iniciar la partida
  controller.play