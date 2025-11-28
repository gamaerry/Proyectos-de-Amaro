class_name BotonDimension extends TextureButton

@export var dimension: int
var estilos: Array[Resource] # normal, hover, pressed y disabled

func _ready() -> void:
	var dimension_str: String = str(dimension)
	estilos = [ load("res://assets/imagenes/botones/dimensiones/" + dimension_str + "_normal.png"),
			load("res://assets/imagenes/botones/dimensiones/" + dimension_str + "_hover.png"),
			load("res://assets/imagenes/botones/dimensiones/" + dimension_str + "_pressed.png"),
			load("res://assets/imagenes/botones/dimensiones/" + dimension_str + "_disabled.png")]

func set_tema_bloqueado() -> void:
	texture_normal = estilos[3]
	texture_hover = estilos[3]
	texture_pressed = estilos[3]

func set_tema_desbloqueado() -> void:
	texture_normal = estilos[0]
	texture_hover = estilos[1]
	texture_pressed = estilos[2]
