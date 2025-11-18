extends Node2D

@export var niveles: Array[PackedScene]
@onready var boton_inicio: Button = $Menu/VBoxContainer/Inicio
@onready var boton_cargar: Button = $Menu/VBoxContainer/Cargar
@onready var boton_dia: Button = $Menu/dia
@onready var boton_logros: Button = $Menu/Logros
@onready var logros: GridContainer = $GridContainer
@onready var menu: HBoxContainer = $Menu
@onready var fondo_dia: Sprite2D = $FondoDia
@onready var fondo_noche: Sprite2D = $FondoNoche
@onready var contenedor_texto: CanvasLayer = $ContenedorTexto
signal gano_logro
var tween: Tween  # tween reutilizable
var _dimension_actual: int = 3
var _index_actual: int = _dimension_actual - 3
var _nivel_instanciado: Node2D
const ICONOS: Array[String] = ["  ⏾  ","  ☀︎  "]
const RECORRIDO_NECESARIO: int = 110
var logros_en_movimiento: bool = false
var logros_en_pantalla: bool = false

func _ready() -> void:
	fondo_dia.visible = Global.dia
	fondo_noche.visible = !Global.dia
	boton_inicio.pressed.connect(_crear_nivel.bind(_index_actual))
	boton_dia.pressed.connect(_cambiar_modo_dia)
	gano_logro.connect(contenedor_texto.mostrar_logro)
	boton_logros.pressed.connect(_mostrar_logros)
	_dimension_actual = 3
	
func _mostrar_logros() -> void:
	if !logros_en_movimiento:
		if !logros_en_pantalla:
			_mover_logros(logros.position.x + RECORRIDO_NECESARIO)
			logros_en_pantalla = true
		else:
			_mover_logros(logros.position.x - RECORRIDO_NECESARIO)
			logros_en_pantalla = false

func _mover_logros(nueva_posicion: float)->void:
		tween = create_tween()
		tween.set_ease(Tween.EASE_OUT)
		tween.set_trans(Tween.TRANS_CUBIC)
		logros_en_movimiento = true
		tween.finished.connect(func(): logros_en_movimiento = false)
		tween.tween_property(logros, "position:x", nueva_posicion , 1)

func _cambiar_modo_dia():
	Global.dia = !Global.dia
	fondo_dia.visible = Global.dia
	fondo_noche.visible = !Global.dia
	boton_dia.text = ICONOS[int(!Global.dia)]

func _crear_nivel(index: int):
	_nivel_instanciado = niveles[index].instantiate()
	add_child.call_deferred(_nivel_instanciado)
	menu.visible = false
	
func _eliminar_nivel():
	_nivel_instanciado.queue_free()

func _reiniciar_nivel():
	_eliminar_nivel()
	_crear_nivel(_dimension_actual - 3)
