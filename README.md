# PcgRandom Godot Extension Addon
A [Permuted Congruential Generator](https://pcg-random.org) which creates random numbers. All methods use purely integer math, therefore the same seed is guaranteed to generate the same sequence of numbers regardless of what machine it is running on. This is useful for things such as roguelite run seeds, where you want to ensure results are exactly the same regardless of what hardware a player has.

## Features
* `next()` method can be used to return a random 32 bit integer
* `gaussian(mean, stddev)` method can be used to instead return a random number along a gaussian normal curve
    * Because of the limitations of working with integers, this is not perfect, see the notes at the bottom of this README for further details
* Written in C++ as a GDExtension addon, which works with official builds of Godot Engine (Versions 4.3+ supported)
* Can be accessed by GDScript, C#, and any language Godot supports

## Limitations of gaussian Method
Because this works exclusively with int type, values are rounded TOWARDS the mean. This means that if you provide a low standard deviation, the real stddev of the generated numbers will be smaller (e.g. given stddev = 2, results will really have a stddev of ~1.6). A workaround for this is to multiply all of your numbers by some factor of 10, as this issue becomes unnoticable for stddev over 100. A stddev of 10 is probably even enough for most people.
