class_name Global extends Object

static var dia: bool = true # dia por defecto
const TOTAL_IDIOMAS: int = 2
const DIMENSION_MINIMA: int = 3
const DIMENSIONES_DISPONIBLES: int = 3
static var idioma: int = 0 # español por defecto
static var gano_logro: int = 0
static var dia_guardado_3: bool
static var dia_guardado_4: bool
static var estado_actual_dimensiones: Dictionary[int, bool] = {3: false, 4: false, 5: false} # 3x3 completado, 4x4 completado, 5x5 completado
const NUMERO_DE_LOGROS: int = 12
const ORDEN_LOGROS_3: Array[bool] = [true,false,false,true,false,false,false,true,true,false,true,true]
const ORDEN_LOGROS_4: Array[bool] = [true,true,false,false,false,true,true,true,false,false,false,true]
static var logros_obtenidos_3: Array[bool] = [false,false,false,false,false,false,false,false,false,false,false,false]
static var logros_obtenidos_4: Array[bool] = [false,false,false,false,false,false,false,false,false,false,false,false]
static var logros_obtenidos_5: Array[bool] = [false,false,false,false,false,false,false,false,false,false,false,false]
#static var logros_obtenidos_3: Array[bool] = [true,true,true,true,true,true,true,true,true,true,true,true]
static var tablero_3: Array[int]
static var tablero_4: Array[int]
static var dimension_actual: int = 3

static func update_tablero(nuevo: Array[int]):
	match dimension_actual:
		3: tablero_3 = nuevo
		4: tablero_4 = nuevo

static func dimension_desbloqueada(dimension: int) -> bool:
	if dimension < 4: # 1, 2 y 3 siempre estaran desbloqueadas
		return true
	else:
		return estado_actual_dimensiones[dimension-1]

static func obtener_numero_de_logros_conseguidos() -> int:
	var contador = 0
	var obtenidos: Array[bool]
	match dimension_actual:
		3: obtenidos = logros_obtenidos_3
		4: obtenidos = logros_obtenidos_4
		_: obtenidos = logros_obtenidos_5
	for i in NUMERO_DE_LOGROS:
		if obtenidos[i]:
			++contador
	return contador

static func get_acronimo(texto: String) -> String:
	return texto.substr(texto.find(":") - 3, 3)

static func get_posibles_ultimos() -> Dictionary[int, bool]: # posibles ultimas fichas en espiral, serpenteado y lineal
	match dimension_actual: 
		3: return {4: true, 5: true, 0: true}
		4: return {7: true, 9: true, 3: true, 13: true, 0: true}
		_: return {} # tecnicamente imposible

# Devuelve cuántas inversiones tiene el arreglo
static func _contar_inversiones(arreglo: Array[int]) -> int:
	var inversiones: int = 0
	for i in range(arreglo.size()-1):
		for j in range(i + 1, arreglo.size()):
			if arreglo[i] > arreglo[j]:
				inversiones += 1
	return inversiones

static func _resoluble(arr: Array[int]) -> bool:
	return _contar_inversiones(arr) % 2 == 0

static func get_arreglo_resoluble(tamano: int) -> Array[int]:
	var arreglo_aleatorio: Array[int] = []
	for i in tamano:
		arreglo_aleatorio.push_back(i+1)
	arreglo_aleatorio.shuffle()
	while !(_resoluble(arreglo_aleatorio) == Global.dia): # en realidad resoluble significa que es resoluble en modo dia
		var i: int = randi() % arreglo_aleatorio.size()
		var j: int = (i + 1) % arreglo_aleatorio.size()
		var tmp: int = arreglo_aleatorio[i]
		arreglo_aleatorio[i] = arreglo_aleatorio[j]
		arreglo_aleatorio[j] = tmp
	return arreglo_aleatorio
