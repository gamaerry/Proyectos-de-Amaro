extends CanvasLayer

const CONSEJOS: Array[String] = [
	"En la primera casilla siempre irá el número más alto o el uno, ningún otro será digno.",
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

const LOGROS: Array[String] = [
	"Ha completado OHC: Orden Horizontal Creciente",
	"Ha completado OHD: Orden Horizontal Decreciente",
	"Ha completado OVC: Orden Vertival Creciente",
	"Ha completado OVD: Orden Vertical Decreciente",
	"Ha completado EHC: Espiral en sentido Horario Creciente",
	"Ha completado EHD: Espiral en sentido Horario Decreciente",
	"Ha completado EAC: Espiral en sentido Antihorario Creciente",
	"Ha completado EAD: Espiral en sentido Antihorario Decreciente",
]

var mostrar_consejos: bool = true
var bolsa: Array[String] = []  # Shuffle bag
@export var consejos: bool = true
@onready var label: Label = $ColorRect/Consejos
@onready var color: ColorRect = $ColorRect
@onready var label2: Label = $ColorRect2/Logros
@onready var color2: ColorRect = $ColorRect2

func _ready() -> void:
	_rellenar_bolsa()
	_mostrar_consejo_random()

func _rellenar_bolsa() -> void:
	bolsa = CONSEJOS.duplicate()
	bolsa.shuffle()

func _espera(segundos: int) -> void:
	await get_tree().create_timer(segundos).timeout

func _mostrar_consejo_random() -> void:
	if Global.gano_logro != 0:
		return
	elif bolsa.is_empty():
		_rellenar_bolsa()
	else:
		await _espera(15)
		await show_tip()
		_mostrar_consejo_random() # Recursividad infinita

func mostrar_logro() -> void:
	label.modulate.a = 0
	color.modulate.a = 0
	label2.modulate.a = 1
	color2.modulate.a = 1
	label2.text = LOGROS[Global.gano_logro - 1]
	await _espera(7)
	var tween: Tween = create_tween()
	tween.tween_property(label2, "modulate:a", 0.0, 1.5)
	tween.parallel().tween_property(color2, "modulate:a", 0.0, 1.5)
	_mostrar_consejo_random() # al ganar logro se detiene la recursividad
	Global.gano_logro = 0

func show_tip() -> void:
	label.text = "Consejo: " + bolsa.pop_front()
	var tween: Tween = create_tween()
	tween.tween_property(label, "modulate:a", 1.0, 1.0)
	tween.parallel().tween_property(color, "modulate:a", 1.0, 1.0)
	await _espera(7)
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 0.0, 1.5)
	tween.parallel().tween_property(color, "modulate:a", 0.0, 1.5)
	await tween.finished
