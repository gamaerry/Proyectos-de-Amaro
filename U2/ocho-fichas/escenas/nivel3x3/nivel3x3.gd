class_name Nivel3x3 extends Nivel

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass
	
func on_posible_orden_terminado(orden: Array[int]) -> void:
	match orden: 
		LINEAL_HORIZONTAL_3: _set_logro(1)
		LINEAL_HORIZONTAL_INV_3: _set_logro(2)
		ESPIRAL_CRECIENTE_ANTIHORARIO_3: _set_logro(7)
		ESPIRAL_DECRECIENTE_ANTIHORARIO_3: _set_logro(8)
		LINEAL_VERTICAL_3: _set_logro(3)
		LINEAL_VERTICAL_INV_3: _set_logro(4)
		ESPIRAL_CRECIENTE_HORARIO_3: _set_logro(5)
		ESPIRAL_DECRECIENTE_HORARIO_3: _set_logro(6)
