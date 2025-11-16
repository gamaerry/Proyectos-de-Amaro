class_name Nivel extends Node2D

#DIA:
const LINEAL_HORIZONTAL_3: Array[int] = [1,2,3,4,5,6,7,8,0]
const LINEAL_HORIZONTAL_INV_3: Array[int] = [8,7,6,5,4,3,2,1,0]
const ESPIRAL_CRECIENTE_ANTIHORARIO_3: Array[int] = [1,8,7,2,0,6,3,4,5]
const ESPIRAL_DECRECIENTE_ANTIHORARIO_3: Array[int] = [8,1,2,7,0,3,6,5,4]

#NOCHE:
#const LINEAL_VERTICAL_3: Array[int] = [1,4,7,2,5,8,3,6,0]
#const LINEAL_VERTICAL_INV_3: Array[int] = [8,5,2,7,4,1,6,3,0]
#const ESPIRAL_DECRECIENTE_HORARIO_3: Array[int] = [8,7,6,1,0,5,2,3,4]
#const ESPIRAL_CRECIENTE_HORARIO_3: Array[int] = [1,2,3,8,0,4,7,6,5]

func on_posible_orden_terminado(orden: Array[int]) -> void:
	match orden:
		LINEAL_HORIZONTAL_3: printerr("LINEAL_HORIZONTAL_3!")
		LINEAL_HORIZONTAL_INV_3: printerr("LINEAL_HORIZONTAL_INV_3!")
		ESPIRAL_CRECIENTE_ANTIHORARIO_3: printerr("ESPIRAL_CRECIENTE_ANTIHORARIO_3!")
		ESPIRAL_DECRECIENTE_ANTIHORARIO_3: printerr("ESPIRAL_DECRECIENTE_ANTIHORARIO_3!")
