class_name ControladorPartida extends Node

@export var datos_partida: DatosPartida

const RUTA: String = "user://partida.tres"

func guardar_partida():
	datos_partida.logros_obtenidos = Global.LOGROS_OBTENIDOS
	datos_partida.tablero_3 = Global.tablero_3
	datos_partida.tablero_4 = Global.tablero_4
	datos_partida.dia = Global.dia
	datos_partida.dia_guardado_3 = Global.dia_guardado_3
	datos_partida.dia_guardado_4 = Global.dia_guardado_4
	datos_partida.idioma = Global.idioma
	ResourceSaver.save(datos_partida, RUTA)

func cargar_partida(dimension: int):
	if ResourceLoader.exists(RUTA):
		datos_partida = load(RUTA)
		Global.LOGROS_OBTENIDOS = datos_partida.logros_obtenidos
		Global.tablero_3 = datos_partida.tablero_3
		Global.tablero_4 = datos_partida.tablero_4
		Global.idioma = datos_partida.idioma
		match dimension:
			3: Global.dia_guardado_3 = datos_partida.dia
			4: Global.dia_guardado_4 = datos_partida.dia
