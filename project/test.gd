extends Node2D


func _init() -> void:
	var pcg_rand = PcgRandom.new()
	pcg_rand.set_seed(918237549873333)
	var nums = []
	for i in range(80):
		nums.append(pcg_rand.gaussian(500, 200))
	print(str(nums))
