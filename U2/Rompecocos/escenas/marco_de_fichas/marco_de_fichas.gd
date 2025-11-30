class_name MarcoDeFichas extends Sprite2D

@export var dimension: int #2, 3, 4 o 5
var numero_de_fichas: int
var orden_de_fichas: Array[int] 
var orden_inicial_de_fichas: Array[int]
var menos_dimension: int  # godot no permite expresiones en la estructura match
var indice: int
var indice_nulo: int
var tablero_actual: Array[int]
var dia_guardado: bool
var correccion_de_posicion: Vector2i
signal posible_orden_terminado(orden)

func _ready() -> void:
	_init_variables()
	posible_orden_terminado.connect(get_parent().on_posible_orden_terminado)
	if not tablero_actual.is_empty() and get_parent().fue_cargado:
		orden_de_fichas = tablero_actual
		if Global.dia != dia_guardado:
			get_parent().get_parent().cambiar_modo_dia()
		ordenar_posiciones()
	else:
		orden_de_fichas = Global.get_arreglo_resoluble(numero_de_fichas)
		for i in numero_de_fichas:
			get_child(i).set_numero(orden_de_fichas[i])
		orden_de_fichas.append(0)
		Global.update_tablero(orden_de_fichas)
	orden_inicial_de_fichas = orden_de_fichas.duplicate()

func _init_variables() -> void:
	dimension = Global.dimension_actual
	numero_de_fichas = dimension*dimension - 1
	menos_dimension = -dimension
	match dimension: # TODO: usar diccionarios globales cuando se haga el 5x5
		3: 
			tablero_actual = Global.tablero_3
			dia_guardado = Global.dia_guardado_3
			correccion_de_posicion = Vector2i(16,16)
		4: 
			tablero_actual = Global.tablero_4
			dia_guardado = Global.dia_guardado_4
			correccion_de_posicion = Vector2i(32,32)

func ordenar_posiciones() -> void:
	for i in numero_de_fichas:
		get_child(i).set_numero(orden_de_fichas[i])
		if orden_de_fichas[i] == 0:
			get_child(i).position = correccion_de_posicion
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
		var indice_encontrado: int = orden_inicial_de_fichas.find(orden_de_fichas[indice_a_mover])
		if get_parent().fue_cargado && indice_encontrado == numero_de_fichas:
			indice_encontrado = orden_inicial_de_fichas.find(0)
		get_child(indice_encontrado)._on_pressed()

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
	Global.update_tablero(orden_de_fichas)
	_verificar_posible_orden_terminado(orden_de_fichas[0], orden_de_fichas[numero_de_fichas])
	return movimiento

func _verificar_posible_orden_terminado(primero: int, ultimo: int) -> void:
	if (primero == 1 or primero == numero_de_fichas) and Global.get_posibles_ultimos().has(ultimo):
		posible_orden_terminado.emit(orden_de_fichas)
