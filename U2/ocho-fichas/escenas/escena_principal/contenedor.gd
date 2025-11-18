extends CanvasLayer

const CONSEJOS: Array[String] = [
	"En la primera casilla siempre irá número más alto o el uno, ningún otro será digno.",
	"Como es arriba es abajo.",
	"Come frutas y verduras.",
	"¿Cuantas fichas debería tener el tablero de 1x1?",
	"Piensa fuera de la caja... pero dentro del tablero...",
	"Si el Diablo existe, Dios existe.",
	"Vive el presente.",
	"Practica la gratitud.",
	"La solución trivial siempre se resuelve de día.",
	"Siempre la mitad de los logros se obtienen de día y la mitad de noche."
]

var mostrar_consejos: bool = true
var bolsa: Array[String] = []  # Shuffle bag
@export var consejos: bool = true
@onready var label: Label = $ColorRect/Consejos
@onready var color: ColorRect = $ColorRect

func _ready() -> void:
	_rellenar_bolsa()
	mostrar_consejo_random()

func _rellenar_bolsa() -> void:
	bolsa = CONSEJOS.duplicate()
	bolsa.shuffle()

func _espera(segundos: int) -> void:
	await get_tree().create_timer(segundos).timeout

func mostrar_consejo_random() -> void:
	if !mostrar_consejos:
		return
	elif bolsa.is_empty():
		_rellenar_bolsa()
	else:
		await _espera(14)
		await show_tip()
		mostrar_consejo_random() # Recursividad infinita

func show_tip() -> void:
	label.text = "Consejo: " + bolsa.pop_front()
	var tween: Tween = create_tween()
	tween.tween_property(label, "modulate:a", 1.0, 1.0)
	tween.parallel().tween_property(color, "modulate:a", 1.0, 1.0)
	self.visible = true
	await _espera(7)
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 0.0, 1.5)
	tween.parallel().tween_property(color, "modulate:a", 0.0, 1.5)
	await tween.finished
	self.visible = false
