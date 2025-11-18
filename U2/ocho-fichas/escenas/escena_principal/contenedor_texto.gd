class_name ContenedorTexto extends CanvasLayer

const CONSEJOS: Array[String] = [
	"En la primera casilla siempre irá el número más alto o el uno, ningún otro será digno.",
	"Como es arriba es abajo.",
	"Come frutas y verduras.",
	"¿Cuantas fichas debería tener el tablero de 1x1?",
	"Piensa fuera de la caja. . . pero dentro del tablero. . .",
	"Si el Diablo existe, Dios existe.",
	"Vive el presente.",
	"Cada que sales tu partida se guarda automáticamente, pero solo puedes guardar una.",
	"Sí, tambien tus logros se guardan al salir.",
	"Practica la gratitud.",
	"La solución trivial siempre se resuelve de día.",
	"Siempre la mitad de los logros se obtienen de día y la mitad de noche."
]

const LOGROS: Array[String] = [
	"Logro conseguido OHC: Orden Horizontal Creciente",
	"Logro conseguido OHD: Orden Horizontal Decreciente",
	"Logro conseguido OVC: Orden Vertival Creciente",
	"Logro conseguido OVD: Orden Vertical Decreciente",
	"Logro conseguido EHC: Espiral en sentido Horario Creciente",
	"Logro conseguido EHD: Espiral en sentido Horario Decreciente",
	"Logro conseguido EAC: Espiral en sentido Antihorario Creciente",
	"Logro conseguido EAD: Espiral en sentido Antihorario Decreciente",
]

var tween: Tween  # tween reutilizable
var consejos_activados: bool = true
var bolsa: Array[String] = []  # Shuffle bag
@export var consejos: bool = true
@onready var label: Label = $ColorRect/Consejos
@onready var color: ColorRect = $ColorRect
@onready var label2: Label = $ColorRect2/Logros
@onready var color2: ColorRect = $ColorRect2

func _ready() -> void:
	self.visible = false
	mostrar_consejo_random()

func _rellenar_bolsa() -> void:
	bolsa = CONSEJOS.duplicate()
	bolsa.shuffle()

func _espera(segundos: int) -> void:
	await get_tree().create_timer(segundos).timeout

func mostrar_consejo_random() -> void:
	if !consejos_activados:
		return
	elif bolsa.is_empty():
		_rellenar_bolsa()
	await _espera(15)
	if consejos_activados:
		await aparecer_consejo()
		mostrar_consejo_random() # Recursividad infinita

func mostrar_logro(temporal: bool = true, logro: int = Global.gano_logro - 1) -> void:
	activar_mensaje_logros()
	label2.text = LOGROS[logro]
	if temporal:
		await _espera(5)
		tween = create_tween()
		tween.tween_property(label2, "modulate:a", 0.0, 1.5)
		tween.parallel().tween_property(color2, "modulate:a", 0.0, 1.5)
		Global.gano_logro = 0
		await tween.finished
		consejos_activados = true
		mostrar_consejo_random() # al ganar logro se detiene la recursividad

func activar_mensaje_logros():
	self.visible = true
	consejos_activados = false
	label2.modulate.a = 1
	color2.modulate.a = 1

func desactivar_mensaje_logros():
	self.visible = false
	consejos_activados = true
	label2.modulate.a = 0
	color2.modulate.a = 0

func aparecer_consejo() -> void:
	self.visible = true
	label.text = "Consejo: " + bolsa.pop_front()
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 1.0, 1.0)
	tween.parallel().tween_property(color, "modulate:a", 1.0, 1.0)
	await _espera(5)
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 0.0, 1.5)
	tween.parallel().tween_property(color, "modulate:a", 0.0, 1.5)
	await tween.finished
	self.visible = false
