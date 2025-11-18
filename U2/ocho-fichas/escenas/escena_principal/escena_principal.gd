extends Node2D

@export var niveles: Array[PackedScene]
@onready var boton_inicio: Button = $Menu/VBoxContainer/Inicio
@onready var boton_cargar: Button = $Menu/VBoxContainer/Cargar
@onready var boton_dia: Button = $Menu/dia
@onready var boton_logros: Button = $Menu/Logros
@onready var boton_regresar: Button = $RegresarAlMenu
@onready var logros: GridContainer = $GridContainer
@onready var menu: HBoxContainer = $Menu
@onready var fondo_dia: Sprite2D = $FondoDia
@onready var fondo_noche: Sprite2D = $FondoNoche
@onready var contenedor_texto: ContenedorTexto = $ContenedorTexto
@onready var controlador_partida: ControladorPartida = $ControladorPartida
signal gano_logro
var tween: Tween  # tween reutilizable
var _dimension_actual: int = 3
var index_actual: int = _dimension_actual - 3
var _nivel_instanciado: Node2D
const ICONOS: Array[String] = ["  ⏾  ","  ☀︎  "]
const RECORRIDO_NECESARIO: int = 110
var logros_en_movimiento: bool = false
var logros_en_pantalla: bool = false

func _ready() -> void:
	controlador_partida.cargar_partida()
	_actualizar_logros_obtenidos()
	cambiar_modo_dia()
	boton_regresar.visible = false
	boton_inicio.pressed.connect(_crear_nivel.bind(index_actual))
	boton_dia.pressed.connect(cambiar_modo_dia)
	gano_logro.connect(contenedor_texto.mostrar_logro)
	boton_cargar.pressed.connect(_cargar)
	boton_logros.pressed.connect(_mostrar_logros)
	boton_regresar.pressed.connect(regresar_al_menu)
	_dimension_actual = 3
	
func _cargar() -> void:
	_crear_nivel(index_actual)
	controlador_partida.cargar_partida()
	_nivel_instanciado.fue_cargado = true

func _actualizar_logros_obtenidos() -> void:
	for i in Global.NUMERO_DE_LOGROS:
		if Global.logros_obtenidos_3[i]:
			logros.get_child(i).pressed.connect(contenedor_texto.mostrar_logro.bind(false, i))
			logros.get_child(i).add_theme_stylebox_override("normal", load("res://escenas/menu_principal/tema_botones_obtenidos_normal.tres"))
			logros.get_child(i).add_theme_stylebox_override("hover", load("res://escenas/menu_principal/tema_botones_obtenidos_hover.tres"))
			logros.get_child(i).add_theme_stylebox_override("pressed", load("res://escenas/menu_principal/tema_botones_obtenidos_pressed.tres"))
			logros.get_child(i).add_theme_stylebox_override("disabled", load("res://escenas/menu_principal/tema_botones_obtenidos_disable.tres"))

func _mostrar_logros() -> void:
	if !logros_en_movimiento:
		if !logros_en_pantalla:
			_mover_logros(logros.position.x + RECORRIDO_NECESARIO)
			logros_en_pantalla = true
		else:
			_mover_logros(logros.position.x - RECORRIDO_NECESARIO)
			contenedor_texto.desactivar_mensaje_logros()
			logros_en_pantalla = false

func _mover_logros(nueva_posicion: float)->void:
		tween = create_tween()
		tween.set_ease(Tween.EASE_OUT)
		tween.set_trans(Tween.TRANS_CUBIC)
		logros_en_movimiento = true
		tween.finished.connect(func(): logros_en_movimiento = false)
		tween.tween_property(logros, "position:x", nueva_posicion , 0.5)

func cambiar_modo_dia():
	Global.dia = !Global.dia
	fondo_dia.visible = Global.dia
	fondo_noche.visible = !Global.dia
	boton_dia.text = ICONOS[int(!Global.dia)]
	ordenar_logros()

func ordenar_logros() -> void:
	for i in Global.NUMERO_DE_LOGROS:
		logros.get_child(i).disabled = Global.ORDEN_LOGROS_3[i] != Global.dia

func regresar_al_menu():
	_actualizar_logros_obtenidos()
	controlador_partida.guardar_partida()
	_nivel_instanciado.queue_free()
	_nivel_instanciado = null
	menu.visible = true
	boton_regresar.visible = false

func _crear_nivel(index: int):
	_nivel_instanciado = niveles[index].instantiate()
	add_child.call_deferred(_nivel_instanciado)
	menu.visible = false
	boton_regresar.visible = true
	if logros_en_pantalla:
		_mostrar_logros()
	
func _eliminar_nivel():
	_nivel_instanciado.queue_free()

func _reiniciar_nivel():
	_eliminar_nivel()
	_crear_nivel(_dimension_actual - 3)
