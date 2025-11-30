class_name Ficha extends TextureButton

@export var numero: int = 0
@export var audio_movimiento: AudioStreamPlayer2D
@export var audio_fallar: AudioStreamPlayer2D
var contenedor: MarcoDeFichas
var tween: Tween  # tween reutilizable
var en_movimiento: bool = false
const TAMANO_FICHA: int = 32

func _ready() -> void:
	contenedor = get_parent()
	pressed.connect(_on_pressed)
	#texture_normal = load(_textura())

func set_numero(n: int) -> void:
	numero = n
	if n == 0:
		return
	var ruta: String = "res://assets/imagenes/dia/" + str(n) + ".png"
	if !Global.dia:
		ruta = "res://assets/imagenes/noche/" + str(n) + "_noche.png"
	texture_normal = load(ruta)

func _on_pressed() -> void:
	if en_movimiento:
		return
	var movimiento: int = contenedor.movimiento_posible(numero)
	_init_tween()
	if movimiento >= 0:
		audio_movimiento.play()
	else:
		audio_fallar.play()
	match movimiento:
		0: _mover_derecha()
		1: _mover_abajo()
		2: _mover_izquierda()
		3: _mover_arriba()
		_: _fallar_movimiento()

func _init_tween() -> void:
	if tween:
		tween.kill()
	tween = create_tween()
	tween.set_ease(Tween.EASE_OUT)
	tween.set_trans(Tween.TRANS_CUBIC)
	en_movimiento = true
	tween.finished.connect(func(): en_movimiento = false)

func _mover_derecha():
	tween.tween_property(self, "position:x", position.x + TAMANO_FICHA, 0.2)

func _mover_abajo():
	tween.tween_property(self, "position:y", position.y + TAMANO_FICHA, 0.2)

func _mover_izquierda():
	tween.tween_property(self, "position:x", position.x - TAMANO_FICHA, 0.2)

func _mover_arriba():
	tween.tween_property(self, "position:y", position.y - TAMANO_FICHA, 0.2)

func _fallar_movimiento(): # Efecto de "rebote"
	tween.tween_property(self, "scale", Vector2(1.1, 1.1), 0.1)
	tween.tween_property(self, "scale", Vector2.ONE, 0.1)
