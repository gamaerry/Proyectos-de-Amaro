class_name BotonLogro extends Button

var imposible: bool = false

var estilos: Array[StyleBox] = [
	get_theme_stylebox("normal", "Button"),
	get_theme_stylebox("pressed", "Button"),
	get_theme_stylebox("hover", "Button"),
	get_theme_stylebox("disabled", "Button")]

var font_disable := get_theme_font("disable", "Button")

func set_imposible(_imposible: bool) -> void:
	imposible = _imposible
	_set_tema_bloqueado()
		
func _set_tema_bloqueado() -> void:
	if imposible:
		add_theme_stylebox_override("normal", estilos[3])
		add_theme_stylebox_override("hover", estilos[3])
		add_theme_stylebox_override("pressed", estilos[3])
		add_theme_color_override("font_color", get_theme_color("font_disabled_color", "Button"))
		add_theme_color_override("font_hover_color", get_theme_color("font_disabled_color", "Button"))
		add_theme_color_override("font_pressed_color", get_theme_color("font_disabled_color", "Button"))
		add_theme_color_override("font_focus_color", get_theme_color("font_disabled_color", "Button"))
		
	else:
		add_theme_stylebox_override("normal", estilos[0])
		add_theme_stylebox_override("hover", estilos[1])
		add_theme_stylebox_override("pressed", estilos[2])
		remove_theme_color_override("font_color")
		remove_theme_color_override("font_hover_color")
		remove_theme_color_override("font_pressed_color")
		remove_theme_color_override("font_focus_color")

func set_tema_desbloqueado() -> void:
	if imposible:
		add_theme_stylebox_override("normal", load("res://escenas/menu_principal/tema_botones_obtenidos_disable.tres"))
		add_theme_stylebox_override("hover", load("res://escenas/menu_principal/tema_botones_obtenidos_disable.tres"))
		add_theme_stylebox_override("pressed", load("res://escenas/menu_principal/tema_botones_obtenidos_disable.tres"))
	else:
		add_theme_stylebox_override("normal", load("res://escenas/menu_principal/tema_botones_obtenidos_normal.tres"))
		add_theme_stylebox_override("hover", load("res://escenas/menu_principal/tema_botones_obtenidos_hover.tres"))
		add_theme_stylebox_override("pressed", load("res://escenas/menu_principal/tema_botones_obtenidos_pressed.tres"))
