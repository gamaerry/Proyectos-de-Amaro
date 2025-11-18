extends CanvasLayer

const CONSEJOS: Array[String] = [
	"En la primera casilla siempre irá número más alto o el uno, ningún otro será digno.",
	"Como es arriba es abajo.",
	"Come frutas y verduras.",
	"Piensa a la inversa, pero dentro de la caja.",
	"Si el Diablo existe, Dios existe.",
	"Vive el presente.",
	"Practica la gratitud.",
	"Siempre la mitad de los logros se obtienen de día y la mitad de noche."
]

#@export var consejos: bool = true
@onready var label: Label = $ColorRect/Consejos
@onready var color: ColorRect = $ColorRect

func _ready() -> void:
	mostrar_consejo_random()

func _espera(segundos: int) -> void:
	await get_tree().create_timer(segundos).timeout

func mostrar_consejo_random() -> void:
	printerr("inicio")
	_espera(17)
	printerr("se mostrara")
	await show_tip()
	printerr("se desvanecio")
	mostrar_consejo_random() # Recursividad infinita

func show_tip() -> void:
	label.text = "Consejo: " + CONSEJOS.pick_random()
	var tween: Tween = create_tween()
	tween.tween_property(label, "modulate:a", 1.0, 1.0)
	tween.parallel().tween_property(color, "modulate:a", 1.0, 1.0)
	self.visible = true
	_espera(7)
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 0.0, 1.5)
	tween.parallel().tween_property(color, "modulate:a", 0.0, 1.5)
	await tween.finished
	self.visible = false
