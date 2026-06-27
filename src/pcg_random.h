#pragma once

#include "godot_cpp/classes/ref_counted.hpp"

using namespace godot;

class PcgRandom : public RefCounted {
	GDCLASS(PcgRandom, RefCounted)

protected:
	static void _bind_methods();

private:
	uint64_t state = 0;

public:
	PcgRandom() = default;
	~PcgRandom() override = default;

	void set_seed(int64_t p_seed);
	uint32_t next();
	int gaussian(int mean, int stddev);
};
