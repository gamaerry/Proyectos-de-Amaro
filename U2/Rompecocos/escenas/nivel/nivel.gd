class_name Nivel extends Node2D

#DIA3x3:
const LINEAL_HORIZONTAL_3: Array[int] = [1,2,3,4,5,6,7,8,0]
const LINEAL_HORIZONTAL_INV_3: Array[int] = [8,7,6,5,4,3,2,1,0]
const ESPIRAL_CRECIENTE_ANTIHORARIO_3: Array[int] = [1,8,7,2,0,6,3,4,5]
const ESPIRAL_DECRECIENTE_ANTIHORARIO_3: Array[int] = [8,1,2,7,0,3,6,5,4]
const SERPENTEADO_VERTICAL_3: Array[int] = [1,6,7,2,5,8,3,4,0]
const SERPENTEADO_VERTICAL_INV_3: Array[int] = [8,3,2,7,4,1,6,5,0]
#NOCHE3x3:
const LINEAL_VERTICAL_3: Array[int] = [1,4,7,2,5,8,3,6,0]
const LINEAL_VERTICAL_INV_3: Array[int] = [8,5,2,7,4,1,6,3,0]
const ESPIRAL_DECRECIENTE_HORARIO_3: Array[int] = [8,7,6,1,0,5,2,3,4]
const ESPIRAL_CRECIENTE_HORARIO_3: Array[int] = [1,2,3,8,0,4,7,6,5]
const SERPENTEADO_HORIZONTAL_3: Array[int] = [1,2,3,6,5,4,7,8,0]
const SERPENTEADO_HORIZONTAL_INV_3: Array[int] = [8,7,6,3,4,5,2,1,0]
# DIA4x4
const LINEAL_HORIZONTAL_4: Array[int] = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0]
const ESPIRAL_CRECIENTE_HORARIO_4: Array[int] = [1,2,3,4,12,13,14,5,11,0,15,6,10,9,8,7]
const SERPENTEADO_HORIZONTAL_INV_4: Array[int] = [15,14,13,12,8,9,10,11,7,6,5,4,0,1,2,3]
const LINEAL_VERTICAL_4: Array[int] = [1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,0]
const ESPIRAL_CRECIENTE_ANTIHORARIO_4: Array[int] = [1,12,11,10,2,13,0,9,3,14,15,8,4,5,6,7]
const SERPENTEADO_VERTICAL_INV_4: Array[int] = [15,8,7,0,14,9,6,1,13,10,5,2,12,11,4,3]
# NOCHE4x4
const SERPENTEADO_HORIZONTAL_4: Array[int] = [1,2,3,4,8,7,6,5,9,10,11,12,0,15,14,13]
const LINEAL_HORIZONTAL_INV_4: Array[int] = [15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0]
const ESPIRAL_DECRECIENTE_HORARIO_4: Array[int] = [15,14,13,12,4,3,2,11,5,0,1,10,6,7,8,9]
const SERPENTEADO_VERTICAL_4: Array[int] = [1,8,9,0,2,7,10,15,3,6,11,14,4,5,12,13]
const LINEAL_VERTICAL_INV_4: Array[int] = [15,11,7,3,14,10,6,2,13,9,5,1,12,8,4,0]
const ESPIRAL_DECRECIENTE_ANTIHORARIO_4: Array[int] = [15,4,5,6,14,3,0,7,13,2,1,8,12,11,10,9]

var fue_cargado: bool = false

func on_posible_orden_terminado(_orden: Array[int]) -> void:
	pass

func _set_logro(logro: int) -> void:
	Global.gano_logro = logro
	get_parent().gano_logro.emit() #escena principal siempre es parent
	Global.LOGROS_OBTENIDOS[Global.dimension_actual][logro - 1] = true
	
