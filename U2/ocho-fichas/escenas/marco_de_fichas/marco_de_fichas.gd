class_name MarcoDeFichas extends Sprite2D

@export var dimension: int = 3 #2, 3, 4 o 5
var numero_de_fichas: int = dimension*dimension - 1
var fichas_para_espiral: Vector2i = Global.get_numeros_espirales(dimension)
var orden_de_fichas: Array[int] 
var orden_inicial_de_fichas: Array[int]
var menos_dimension: int = -dimension # godot no permite expresiones en la estructura match
var indice: int
var indice_nulo: int
signal posible_orden_terminado(orden)

func _ready() -> void:
	posible_orden_terminado.connect(get_parent().on_posible_orden_terminado)
	if !Global.tablero_3.is_empty() && get_parent().fue_cargado:
		orden_de_fichas = Global.tablero_3
		if Global.dia != Global.dia_guardado:
			get_parent().get_parent().cambiar_modo_dia()
		ordenar_posiciones()
	else:
		orden_de_fichas = Global.get_arreglo_resoluble(numero_de_fichas)
		for i in numero_de_fichas:
			get_child(i).set_numero(orden_de_fichas[i])
		orden_de_fichas.append(0)
	orden_inicial_de_fichas = orden_de_fichas.duplicate()
	printerr(orden_de_fichas)

func ordenar_posiciones() -> void:
	for i in numero_de_fichas:
		get_child(i).set_numero(orden_de_fichas[i])
		if orden_de_fichas[i] == 0:
			get_child(i).position = Vector2i(16,16)
			get_child(i).set_numero(orden_de_fichas[numero_de_fichas])

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("abajo"):
		_abajo()
	elif event.is_action_pressed("arriba"):
		_arriba()
	elif event.is_action_pressed("derecha"):
		_derecha()
	elif event.is_action_pressed("izquierda"):
		_izquierda()

func _presionar_si_es_posible(indice_a_mover: int):
	if indice_a_mover >= 0 and indice_a_mover <= numero_de_fichas:
		get_child(orden_inicial_de_fichas.find(orden_de_fichas[indice_a_mover]))._on_pressed()

func _abajo() -> void:
	_presionar_si_es_posible(orden_de_fichas.find(0) - dimension)
	
func _arriba() -> void:
	_presionar_si_es_posible(orden_de_fichas.find(0) + dimension)
	
func _derecha() -> void:
	indice = orden_de_fichas.find(0) - 1
	if (indice+1) % dimension != 0:
		_presionar_si_es_posible(indice)

func _izquierda() -> void:
	indice = orden_de_fichas.find(0) + 1
	if indice % dimension != 0:
		_presionar_si_es_posible(indice)

func movimiento_posible(ficha: int) -> int: # 0, 1, 2, 3 o -1
	indice = orden_de_fichas.find(ficha)
	indice_nulo = orden_de_fichas.find(0)
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
	Global.tablero_3 = orden_de_fichas
	_verificar_posible_orden_terminado(orden_de_fichas[0], orden_de_fichas[numero_de_fichas])
	return movimiento

func _verificar_posible_orden_terminado(primero: int, ultimo: int) -> void:
	if (primero == 1 || primero == numero_de_fichas) && (ultimo == 0 || ultimo == fichas_para_espiral.x || ultimo == fichas_para_espiral.y):
		posible_orden_terminado.emit(orden_de_fichas)
