extends Node2D

@export var niveles: Array[PackedScene]
var _dimension_actual: int
var _nivel_instanciado: Node2D

func _ready() -> void:
	_dimension_actual = 3
	_crear_nivel(_dimension_actual - 3)

func _crear_nivel(index: int):
	_nivel_instanciado = niveles[index].instantiate()
	add_child.call_deferred(_nivel_instanciado)
	
func _eliminar_nivel():
	_nivel_instanciado.queue_free()

func _reiniciar_nivel():
	_eliminar_nivel()
	_crear_nivel(_dimension_actual - 3)
