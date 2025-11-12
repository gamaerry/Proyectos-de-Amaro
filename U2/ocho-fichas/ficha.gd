class_name Ficha extends TextureButton

var numero: int = 9 # ficha por defecto (imposible)
var contenedor: MarcoDeFichas

func _ready() -> void:
	contenedor = get_parent() as MarcoDeFichas
	pressed.connect(_on_pressed)

func _textura() -> String:
	return "res://assets/" + str(numero) + ".png"


func set_numero_ficha(n: int) -> void:
	numero = n
	texture_normal = load(_textura())

func _on_pressed() -> void:
	var movimiento: int = contenedor.movimiento_posible(self)
	
