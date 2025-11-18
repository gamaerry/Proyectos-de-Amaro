class_name Global extends Object

static var dia: bool = false 
static var gano_logro: int = 0
static var dia_guardado: bool
const NUMERO_DE_LOGROS: int = 8
const ORDEN_LOGROS_3: Array[bool] = [true,true,false,false,false,false,true,true]
static var logros_obtenidos_3: Array[bool] = [false,false,false,false,false,false,false,false]
#static var logros_obtenidos_3: Array[bool] = [true,true,false,false,false,false,true,true]
static var tablero_3: Array[int]
static func get_numeros_espirales(n: int) -> Vector2i:
	return Vector2i(2*n-1, (n-1)**2) # 5 y 4 en el caso de dimension 3

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
