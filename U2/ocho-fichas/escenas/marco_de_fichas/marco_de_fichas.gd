class_name MarcoDeFichas extends Sprite2D

@export var dimension: int = 3 #2, 3, 4 o 5
@export var numero_de_fichas: int = dimension*dimension - 1
var orden_de_fichas: Array[int] = Global.get_arreglo_resoluble(numero_de_fichas)

func _ready() -> void:
	for i in numero_de_fichas:
		get_child(i).set_numero(orden_de_fichas[i])
	orden_de_fichas.append(0)

func movimiento_posible(ficha: int) -> int: # 0, 1, 2, 3 o -1
	var indice: int = orden_de_fichas.find(ficha)
	var indice_nulo: int = orden_de_fichas.find(0)
	var menos_dimension: int = -dimension # godot no permite expresiones en la estructura match
	var movimiento: int = -1
	match indice - indice_nulo:
		-1: if (indice + 1) % dimension == 0:
			return movimiento
		else:
			movimiento = 0
		1: if indice % dimension == 0:
			return movimiento
		else:
			movimiento = 2
		dimension: movimiento = 3
		menos_dimension: movimiento = 1
		_: return movimiento
	orden_de_fichas[indice] = 0
	orden_de_fichas[indice_nulo] = ficha
	return movimiento
