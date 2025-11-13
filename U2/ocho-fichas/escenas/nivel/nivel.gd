extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var viewport_size = get_viewport().get_visible_rect().size
	print("Viewport real:", viewport_size, "  ratio:", viewport_size.x / viewport_size.y)
