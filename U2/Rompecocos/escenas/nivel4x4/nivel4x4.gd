class_name Nivel4x4 extends Nivel

func on_posible_orden_terminado(orden: Array[int]) -> void:
	match orden: # TODO: borrar esta clase al implementar el 5x5
		LINEAL_HORIZONTAL_4: _set_logro(1)
		ESPIRAL_CRECIENTE_HORARIO_4: _set_logro(2)
		SERPENTEADO_HORIZONTAL_4: _set_logro(3)
		LINEAL_HORIZONTAL_INV_4: _set_logro(4)
		ESPIRAL_DECRECIENTE_HORARIO_4: _set_logro(5)
		SERPENTEADO_HORIZONTAL_INV_4: _set_logro(6)
		LINEAL_VERTICAL_4: _set_logro(7)
		ESPIRAL_CRECIENTE_ANTIHORARIO_4: _set_logro(8)
		SERPENTEADO_VERTICAL_4: _set_logro(9)
		LINEAL_VERTICAL_INV_4: _set_logro(10)
		ESPIRAL_DECRECIENTE_ANTIHORARIO_4: _set_logro(11)
		SERPENTEADO_VERTICAL_INV_4: _set_logro(12)
