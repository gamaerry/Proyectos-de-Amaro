extends Node2D

@export var niveles: Array[PackedScene]
@onready var boton_inicio: Button = $MenuPrincipal/Inicio
@onready var boton_cargar: Button = $MenuPrincipal/Cargar
@onready var boton_dia: TextureButton = $OpcionesDeMenu/Dia
@onready var boton_logros: TextureButton = $OpcionesDeMenu/Logros
@onready var boton_idioma: TextureButton = $OpcionesDeMenu/Idioma
@onready var boton_regresar: TextureButton = $RegresarAlMenu
@onready var logros: GridContainer = $Logros
@onready var menu: VBoxContainer = $MenuPrincipal
@onready var opciones: VBoxContainer = $OpcionesDeMenu
@onready var fondo_dia: Sprite2D = $FondoDia
@onready var fondo_noche: Sprite2D = $FondoNoche
@onready var contenedor_texto: ContenedorTexto = $ContenedorTexto
@onready var controlador_partida: ControladorPartida = $ControladorPartida
signal gano_logro
var tween: Tween  # tween reutilizable
var _dimension_actual: int = 3
var index_actual: int = _dimension_actual - 3
var _nivel_instanciado: Node2D
const RECORRIDO_NECESARIO: int = 133
var logros_en_movimiento: bool = false
var logros_en_pantalla: bool = false

func _ready() -> void:
	controlador_partida.cargar_partida()
	cambiar_modo_dia()
	boton_regresar.visible = false
	boton_inicio.pressed.connect(_crear_nivel.bind(index_actual))
	boton_dia.pressed.connect(cambiar_modo_dia)
	gano_logro.connect(contenedor_texto.mostrar_logro)
	boton_cargar.pressed.connect(_cargar)
	boton_logros.pressed.connect(_mostrar_ocultar_logros)
	boton_regresar.pressed.connect(regresar_al_menu)
	_dimension_actual = 3
	
func _cargar() -> void:
	_crear_nivel(index_actual)
	controlador_partida.cargar_partida()
	_nivel_instanciado.fue_cargado = true

func _actualizar_logros_obtenidos() -> void:
	for i in Global.NUMERO_DE_LOGROS:
		var logro: Node = logros.get_child(i)
		for c in logro.pressed.get_connections():
			logro.pressed.disconnect(c.callable)
		if Global.logros_obtenidos_3[i]:
			logro.pressed.connect(contenedor_texto.mostrar_logro.bind(false, i))
			logro.set_tema_desbloqueado()
		elif logro.imposible:
			logro.pressed.connect(contenedor_texto.desactivar_mensaje_logros)
		else:
			logro.pressed.connect(contenedor_texto.mostrar_logro_bloqueado)

func _mostrar_ocultar_logros() -> void:
	if !logros_en_movimiento:
		if !logros_en_pantalla:
			_mover_logros(logros.position.x + RECORRIDO_NECESARIO)
			logros_en_pantalla = true
		else:
			_mover_logros(logros.position.x - RECORRIDO_NECESARIO)
			contenedor_texto.desactivar_mensaje_logros()
			logros_en_pantalla = false

func _mover_logros(nueva_posicion: float)->void:
	tween = create_tween()
	tween.set_ease(Tween.EASE_OUT)
	tween.set_trans(Tween.TRANS_CUBIC)
	logros_en_movimiento = true
	tween.finished.connect(func(): logros_en_movimiento = false, CONNECT_ONE_SHOT)
	tween.tween_property(logros, "position:x", nueva_posicion , 0.4)

func cambiar_modo_dia():
	Global.dia = !Global.dia
	fondo_dia.visible = Global.dia
	fondo_noche.visible = !Global.dia
	cambiar_aspecto_boton_dia()
	ordenar_logros()
	_actualizar_logros_obtenidos()
	if logros_en_pantalla:
		_mostrar_ocultar_logros()
		
func cambiar_aspecto_boton_dia() -> void:
	if !Global.dia:
		boton_dia.texture_normal = load("res://assets/imagenes/boton_dia_normal.png")
		boton_dia.texture_hover = load("res://assets/imagenes/boton_dia_hover.png")
		boton_dia.texture_pressed = load("res://assets/imagenes/boton_dia_pressed.png")
	else:
		boton_dia.texture_normal = load("res://assets/imagenes/boton_noche_normal.png")
		boton_dia.texture_hover = load("res://assets/imagenes/boton_noche_hover.png")
		boton_dia.texture_pressed = load("res://assets/imagenes/boton_noche_pressed.png")


func ordenar_logros() -> void:
	for i in Global.NUMERO_DE_LOGROS:
		logros.get_child(i).set_imposible(Global.ORDEN_LOGROS_3[i] != Global.dia)

func regresar_al_menu():
	_actualizar_logros_obtenidos()
	controlador_partida.guardar_partida()
	_nivel_instanciado.queue_free()
	_nivel_instanciado = null
	menu.visible = true
	opciones.visible = true
	boton_regresar.visible = false

func _crear_nivel(index: int):
	_nivel_instanciado = niveles[index].instantiate()
	add_child.call_deferred(_nivel_instanciado)
	menu.visible = false
	opciones.visible = false
	boton_regresar.visible = true
	if logros_en_pantalla:
		_mostrar_ocultar_logros()
	
func _eliminar_nivel():
	_nivel_instanciado.queue_free()

func _reiniciar_nivel():
	_eliminar_nivel()
	_crear_nivel(_dimension_actual - 3)
