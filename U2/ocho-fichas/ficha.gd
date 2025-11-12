class_name Ficha
extends TextureButton

var numero: int = 9 # ficha por defecto (imposible)

func _textura() -> String:
	return "res://assets/" + str(numero) + ".png"

func _ready() -> void:
	pressed.connect(_on_pressed)

func set_numero_ficha(n: int) -> void:
	numero = n
	texture_normal = load(_textura())

func _on_pressed() -> void:
	pass
