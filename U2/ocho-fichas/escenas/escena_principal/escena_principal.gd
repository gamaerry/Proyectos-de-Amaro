extends Node2D

@export var niveles: Array[PackedScene]
@onready var boton_inicio: Button = $Menu/VBoxContainer/Inicio
@onready var boton_cargar: Button = $Menu/VBoxContainer/Cargar
@onready var boton_dia: Button = $Menu/dia
@onready var menu: HBoxContainer = $Menu
@onready var fondo_dia: Sprite2D = $FondoDia
@onready var fondo_noche: Sprite2D = $FondoNoche

var _dimension_actual: int = 3
var _index_actual: int = _dimension_actual - 3
var _nivel_instanciado: Node2D
const ICONOS: Array[String] = ["  ⏾  ","  ☀︎  "]

func _ready() -> void:
	fondo_dia.visible = Global.dia
	fondo_noche.visible = !Global.dia
	boton_inicio.pressed.connect(_crear_nivel.bind(_index_actual))
	boton_dia.pressed.connect(_cambiar_modo_dia)
	_dimension_actual = 3
	
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
