class_name Global extends Object

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
	while !_resoluble(arreglo_aleatorio):
		var i: int = randi() % arreglo_aleatorio.size()
		var j: int = (i + 1) % arreglo_aleatorio.size()
		var tmp: int = arreglo_aleatorio[i]
		arreglo_aleatorio[i] = arreglo_aleatorio[j]
		arreglo_aleatorio[j] = tmp
	return arreglo_aleatorio
