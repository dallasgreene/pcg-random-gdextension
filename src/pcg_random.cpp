#include "pcg_random.h"
#include "gaussian_x_fixed_point_table.h"

void PcgRandom::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("set_seed", "seed"), &PcgRandom::set_seed);
	godot::ClassDB::bind_method(D_METHOD("next"), &PcgRandom::next);
	godot::ClassDB::bind_method(D_METHOD("gaussian", "mean", "stddev"), &PcgRandom::gaussian);
}

void PcgRandom::set_seed(int64_t p_seed) {
	state = static_cast<uint64_t>(p_seed);
	next();
}

// See https://pcg-random.org/download.html
// It provides a "Minimal C Implementation" which is identical to this except:
//  - The increment value is hardcoded based on what the experts use:
//    https://github.com/imneme/pcg-cpp/blob/428802d1a5634f96bcd0705fab379ff0113bcf13/include/pcg_random.hpp#L159
//  - The state is stored in the class rather than being passed in
//  - static_cast is added to be extra explicit
uint32_t PcgRandom::next() {
	uint64_t oldstate = state;
	// Advance internal state
	state = oldstate * 6364136223846793005ULL + 1442695040888963407ULL;
	// Calculate output function (XSH RR), uses old state for max ILP
	uint32_t xorshifted = static_cast<uint32_t>(((oldstate >> 18u) ^ oldstate) >> 27u);
	uint32_t rot = static_cast<uint32_t>(oldstate >> 59u);
	return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

int PcgRandom::gaussian(int mean, int stddev) {
	int z_value = lookup_in_fixed_point_table(next());
	// C++ integer division truncates toward 0, so the results will be symmetrical
	return mean + ((z_value * stddev) / GAUSSIAN_X_FIXED_POINT_TABLE_SCALE);
}