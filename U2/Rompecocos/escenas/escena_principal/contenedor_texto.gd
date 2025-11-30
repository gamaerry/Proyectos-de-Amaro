class_name ContenedorTexto extends CanvasLayer

const MENSAJE_LOGRO_SECRETO: Array[String] = ["Logro secreto bloqueado", "Secret achievement locked"]

const CONSEJOS: Array[Dictionary] = [{
		0: "Consejo: En la primera casilla siempre irá el número más alto o el uno, ningún otro será digno.",
		1: "Tip: The first tile should always hold the highest number or the number one — nothing else is worthy."},{
		0: "Como es arriba es abajo.",
		1: "As above, so below."},{
		0: "Consejo: Come frutas y verduras.",
		1: "Tip: Eat fruits and vegetables."},{
		0: "¿Cuantas fichas debería tener el tablero de 1x1?",
		1: "How many tiles should a 1x1 board have?"},{
		0: "Consejo: Piensa fuera de la caja. . . pero dentro del tablero. . .",
		1: "Tip: Think outside the box. . . but inside the board. . ."},{
		0: "Si el Diablo existe, Dios existe.",
		1: "If the Devil exists, then God exists."},{
		0: "Consejo: Vive el presente.",
		1: "Tip: Live in the present."},{
		0: "Consejo: Es imposible conseguir los logros de día en modo noche.",
		1: "Tip: It's impossible to obtain daytime achievements in night mode."},{
		0: "Consejo: Cada que sales tu partida se guarda automáticamente, pero solo puedes guardar una por tamaño de tablero.",
		1: "Tip: Every time you exit, your game is saved automatically — but you can only have one save per board size."},{
		0: "Consejo: Si el modo noche se cambia solo al cargar una partida, es porque esa partida la guardaste de noche.",
		1: "Tip: If night mode switches automatically when loading a game, it's because you saved that game at night."},{
		0: "Consejo: Practica la gratitud.",
		1: "Tip: Practice gratitude."},{
		0: "Consejo: La solución trivial siempre se resuelve de día.",
		1: "Tip: The trivial solution is always solved during the day."},{
		0: "Consejo: Siempre la mitad de los logros se obtienen de día y la mitad de noche.",
		1: "Tip: Half of the achievements are always earned during the day, and the other half at night."},{
		0: "Consejo: Si alguna vez te sientes perdido, intenta voltear el tablero. . . mentalmente, no literalmente.",
		1: "Tip: If you ever feel lost, try flipping the board — mentally, not literally."},{
		0: "El modo noche no hace los rompecabezas más difíciles. . . ¿o sí?",
		1: "Night mode doesn’t make the puzzles harder. . . or does it?"},{
		0: "El término técnico del Serpenteado es Boustrofédon. . . A mí tampoco me salió a la primera.",
		1: "The technical term for the Serpentine pattern is Boustrophedon. . . I didn't get it right the first time either."},{
		0: "Consejo: Si no puedes resolverlo, quizá estás resolviendo el problema equivocado.",
		1: "Tip: If you can’t solve it, maybe you’re solving the wrong problem."},{
		0: "Consejo: El acrónimo del logro secreto es más revelador de lo que crees.",
		1: "Tip: The acronym for the secret achievement is more revealing than you think."},{
		0: "Consejo: Cuando todo falle, reinicia. . . tu mente, no el juego.",
		1: "Tip: When all else fails, restart. . . your mind, not the game."},{
		0: "Consejo: ¿Y si le preguntas a la IA?",
		1: "Tip: Thought about asking the AI for help?"},{
		0: "¡Mover fichas no quema calorias!",
		1: "Sliding tiles burns zero calories!"},{
		0: "Consejo: Sé el tablero.",
		1: "Tip: Be the board."},{
		0: "Es más probable que te caiga un rayo. . . varias veces. . . a que el tablero 4x4 aparezca resuelto al azar. (1 en 2.1 billones).",
		1: "You're more likely to be struck by lightning. . . multiple times. . . than to get a randomly solved 4x4 board. (1 in 2.1 trillion)."},{
		0: "El sol viene y se va porque en esta vida no hay luz sin oscuridad.",
		1: "The sun come and go because in this life there is no dawn without dusk."},{
		0: "El vacío es una ficha muy importante: Lo escencial es invisible a los ojos. . .",
		1: "The empty space is a very important tile: What is essential is invisible to the eye. . ."}
]

const LOGROS: Array[Dictionary] = [{
		0: "Logro conseguido OHC: Orden Horizontal Creciente",
		1: "Achievement unlocked IHO: Increasing Horizontal Order"},{
		0: "Logro conseguido EHC: Espiral en sentido Horario Creciente",
		1: "Achievement unlocked CIS: Clockwise Increasing Spiral"},{
		0: "Logro conseguido SHC: Serpenteado Horizontal Creciente",
		1: "Achievement unlocked ISH: Increasing Serpentine Horizontal"},{
		0: "Logro conseguido OHD: Orden Horizontal Decreciente",
		1: "Achievement unlocked DHO: Decreasing Horizontal Order"},{
		0: "Logro conseguido EHD: Espiral en sentido Horario Decreciente",
		1: "Achievement unlocked CDS: Clockwise Decreasing Spiral"},{
		0: "Logro conseguido SHD: Serpenteado Horizontal Decreciente",
		1: "Achievement unlocked DSH: Decreasing Serpentine Horizontal"},{
		0: "Logro conseguido OVC: Orden Vertical Creciente",
		1: "Achievement unlocked IVO: Increasing Vertical Order"},{
		0: "Logro conseguido EAC: Espiral en sentido Antihorario Creciente",
		1: "Achievement unlocked AIS: Anticlockwise Increasing Spiral"},{
		0: "Logro conseguido SVC: Serpenteado Vertical Creciente",
		1: "Achievement unlocked ISV: Increasing Serpentine Vertical"},{
		0: "Logro conseguido OVD: Orden Vertical Decreciente",
		1: "Achievement unlocked DVO: Decreasing Vertical Order"},{
		0: "Logro conseguido EAD: Espiral en sentido Antihorario Decreciente",
		1: "Achievement unlocked ADS: Anticlockwise Decreasing Spiral"},{
		0: "Logro conseguido SVD: Serpenteado Vertical Decreciente",
		1: "Achievement unlocked DSV: Decreasing Serpentine Vertical"}
]

func estado_actual_logros(contador: int, dimension: int) -> String:
	var fraccion: String = str(contador) + "/" + str(Global.NUMERO_DE_LOGROS)
	var dimension_str: String = str(dimension) + "x" + str(dimension)
	if Global.idioma == 0:
		return fraccion + " logros conseguidos del tablero de " + dimension_str
	else:
		return fraccion + " achievements obtained from the " + dimension_str + " board"

var tween: Tween  # tween reutilizable
var bolsa: Array[Dictionary] = []  # Shuffle bag
@export var consejos: bool = true
@export var audio_logro: AudioStreamPlayer2D
@onready var label: Label = $ColorRect/Consejos
@onready var color: ColorRect = $ColorRect
@onready var label2: Label = $ColorRect2/Logros
@onready var color2: ColorRect = $ColorRect2

func _ready() -> void:
	mostrar_consejo_random()

func _rellenar_bolsa() -> void:
	bolsa = CONSEJOS.duplicate()
	bolsa.shuffle()

func _espera(segundos: int) -> void:
	await get_tree().create_timer(segundos).timeout

func mostrar_consejo_random() -> void:
	if bolsa.is_empty():
		_rellenar_bolsa()
	await _espera(15)
	await aparecer_consejo()
	mostrar_consejo_random() # Recursividad infinita

func mostrar_logro(temporal: bool = true, logro: int = Global.gano_logro - 1,  logro_gris: bool = false) -> void:
	activar_mensaje_logros(logro_gris)
	if logro < 0:
		label2.text = estado_actual_logros(Global.obtener_numero_de_logros_conseguidos(), Global.dimension_actual)
	else:
		label2.text = LOGROS[logro][Global.idioma]
	if temporal:
		audio_logro.play()
		await _espera(5)
		tween = create_tween()
		tween.tween_property(label2, "modulate:a", 0.0, 1.5)
		tween.parallel().tween_property(color2, "modulate:a", 0.0, 1.5)
		Global.gano_logro = 0
		await tween.finished

func mostrar_logro_bloqueado(mensaje: String = MENSAJE_LOGRO_SECRETO[Global.idioma]):
	activar_mensaje_logros(true)
	label2.text = mensaje

func activar_mensaje_logros(bloqueado: bool):
	label2.modulate.a = 1
	color2.modulate.a = 1
	if bloqueado:
		color2.color = Color("0000007d")
	else:
		color2.color = Color("#82ff00a9")

func desactivar_mensaje_logros():
	label2.modulate.a = 0
	color2.modulate.a = 0

func aparecer_consejo() -> void:
	label.text = bolsa.pop_back()[Global.idioma]
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 1.0, 1.0)
	tween.parallel().tween_property(color, "modulate:a", 1.0, 1.0)
	await _espera(5)
	tween = create_tween()
	tween.tween_property(label, "modulate:a", 0.0, 1.5)
	tween.parallel().tween_property(color, "modulate:a", 0.0, 1.5)
	await tween.finished
