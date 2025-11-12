class_name MarcoDeFichas extends Node2D

var dimension: int = 3 #2, 3, 4 o 5
var fichas_en_orden_actual: Array[Ficha] #orden actual, 

func _ready() -> void:
	fichas_en_orden_actual.assign(get_children())
	fichas_en_orden_actual.shuffle()
	fichas_en_orden_actual.append(null)

func movimiento_posible(ficha: Ficha) -> int: # 0, 1, 2, 3 o -1
	var indice: int = fichas_en_orden_actual.find(ficha)
	var indice_nulo: int = fichas_en_orden_actual.find(null)
	var menos_dimension: int = -dimension # godot no permite expresiones en la estructura match
	match indice - indice_nulo:
		-1: return 0
		1: return 2
		dimension: return 3
		menos_dimension: return 1
		_: return -1
