class_name Nivel3x3 extends Nivel

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass
	
func on_posible_orden_terminado(orden: Array[int]) -> void:
	match orden:
		LINEAL_HORIZONTAL_3: printerr("LINEAL_HORIZONTAL_3!")
		LINEAL_HORIZONTAL_INV_3: printerr("LINEAL_HORIZONTAL_INV_3!")
		ESPIRAL_CRECIENTE_ANTIHORARIO_3: printerr("ESPIRAL_CRECIENTE_ANTIHORARIO_3!")
		ESPIRAL_DECRECIENTE_ANTIHORARIO_3: printerr("ESPIRAL_DECRECIENTE_ANTIHORARIO_3!")
