class_name Global extends Object

static var dia: bool = true # dia por defecto
const TOTAL_IDIOMAS: int = 2
const DIMENSION_MINIMA: int = 3
const DIMENSIONES_DISPONIBLES: int = 3
static var idioma: int = 0 # español por defecto
static var gano_logro: int = 0
static var dia_guardado_3: bool
static var dia_guardado_4: bool
static var dimension_desbloqueada: Dictionary[int, bool] = {3: true, 4: false, 5:false}
const NUMERO_DE_LOGROS: int = 12
const ORDEN_LOGROS: Dictionary = {
		3: [true,false,false,true,false,false,false,true,true,false,true,true], 
		4: [true,true,false,false,false,true,true,true,false,false,false,true]}
static var LOGROS_OBTENIDOS: Dictionary = {
#		3: [true,true,true,true,true,true,true,true,true,true,true,true], 
#		4: [true,true,true,true,true,true,true,true,true,true,true,true]}
		3: [false,false,false,false,false,false,false,false,false,false,false,false], 
		4: [false,false,false,false,false,false,false,false,false,false,false,false]}
static var tablero_3: Array[int]
static var tablero_4: Array[int]
static var dimension_actual: int = 3

static func get_mensaje_logro_imposible() -> String:
	if dia:
		return ["Logro imposible en modo día", "Impossible achievement in day mode" ][idioma]
	else:
		return ["Logro imposible en modo noche", "Impossible achievement in night mode"][idioma]

static func update_tablero(nuevo: Array[int]):
	match dimension_actual:
		3: tablero_3 = nuevo
		4: tablero_4 = nuevo

static func obtener_numero_de_logros_conseguidos() -> int:
	return LOGROS_OBTENIDOS[dimension_actual].count(true)

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
