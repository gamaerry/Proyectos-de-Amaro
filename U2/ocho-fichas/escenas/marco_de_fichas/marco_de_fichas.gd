class_name MarcoDeFichas extends Sprite2D

@export var dimension: int = 3 #2, 3, 4 o 5
@export var numero_de_fichas: int = dimension*dimension - 1
var orden_de_fichas: Array[int] = Global.get_arreglo_resoluble(numero_de_fichas)
var fichas_en_orden_actual: Array[Node] # Deberian ser de tipo Ficha, pero no es necesario

func _ready() -> void:
	fichas_en_orden_actual = get_children()
	for i in numero_de_fichas:
		var ficha: Ficha = fichas_en_orden_actual[i]
		ficha.numero = orden_de_fichas[i]
		ficha.set_textura()
	fichas_en_orden_actual.append(null)

func movimiento_posible(ficha: Ficha) -> int: # 0, 1, 2, 3 o -1
	var indice: int = fichas_en_orden_actual.find(ficha)
	var indice_nulo: int = fichas_en_orden_actual.find(null)
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
	fichas_en_orden_actual[indice] = null
	fichas_en_orden_actual[indice_nulo] = ficha
	return movimiento
