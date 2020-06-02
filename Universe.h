#pragma once

#include <ctime>
#include <thread>

#include <iostream>
#include <algorithm>

#include <vector>

class Universe
{
private:
	std::chrono::time_point<std::chrono::steady_clock> alpha, omega;
	std::vector<std::vector<char>> universe;

	size_t calculate
	(
		const size_t str,
		const size_t coll
	);

	void checkRules
	(
		const size_t str, 
		const size_t coll
	);
public:
	Universe
	(
		const size_t width, 
		const size_t height, 
		const size_t population = 5
	);

	void printUniverse(size_t sleep_for = 200);

	void oneGeneration();

	~Universe();
};

