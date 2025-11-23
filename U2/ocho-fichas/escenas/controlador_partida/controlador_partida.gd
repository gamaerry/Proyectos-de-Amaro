class_name ControladorPartida extends Node

@export var datos_partida: DatosPartida

const RUTA: String = "user://partida.tres"

func guardar_partida():
	datos_partida.tablero_3 = Global.tablero_3
	datos_partida.logros_obtenidos_3 = Global.logros_obtenidos_3
	datos_partida.dia = Global.dia
	datos_partida.idioma = Global.idioma
	ResourceSaver.save(datos_partida, RUTA)

func cargar_partida():
	if ResourceLoader.exists(RUTA):
		datos_partida = load(RUTA)
		Global.tablero_3 = datos_partida.tablero_3
		Global.logros_obtenidos_3 = datos_partida.logros_obtenidos_3
		Global.dia_guardado = datos_partida.dia
		Global.idioma = datos_partida.idioma
