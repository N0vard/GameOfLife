#include "Universe.h"

size_t Universe::calculate
(
	const size_t str, 
	const size_t coll
)
{
	size_t live_neighbors = 0;

	std::for_each(std::begin(universe) + str - 1, std::begin(universe) + str + 2, [&](auto& it) {
		std::for_each(std::begin(it) + coll - 1, std::begin(it) + coll + 2, [&](char& cell) {
			if (cell == '*' || cell == 'x')
				live_neighbors++;
		});
	});

	return live_neighbors;
}

void Universe::checkRules
(
	const size_t str, 
	const size_t coll
)
{
	std::vector<std::vector<char>>::iterator i_str = std::begin(universe) + str;
	std::vector<char>::iterator i_coll = std::begin(*i_str) + coll;

	size_t live_neighbors = calculate(str, coll);
	if (*i_coll == '*')
		--live_neighbors;

	if (*i_coll == '*' && (live_neighbors < 2 || live_neighbors > 3))
		*i_coll = 'x';
	else if (*i_coll == ' ' && live_neighbors == 3)
		*i_coll = 'o';
}

Universe::Universe
(
	const size_t width, 
	const size_t height, 
	const size_t population
)
{
	srand(time(nullptr));
	alpha = std::chrono::high_resolution_clock::now();
	universe.resize(height + 4);
	std::for_each(std::begin(universe), std::end(universe), [&](auto& it) {
		it.resize(width + 4, ' ');
	});
	std::for_each(std::begin(universe) + 2, std::end(universe) - 2, [&](auto& it) {
		std::for_each(std::begin(it) + 2, std::begin(it) + width / population + 2, [&](char& cell) {
			cell = '*';
		});
		std::random_shuffle(std::begin(it) + 2, std::end(it) - 2);
	});
}

void Universe::printUniverse(size_t sleep_for)
{
	std::for_each(std::begin(universe) + 2, std::end(universe) - 2, [](auto& it) {
		std::for_each(std::begin(it) + 2, std::end(it) - 2, [](char& cell) {
			std::cout << cell;
		});
		std::cout << std::endl;
	});
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));
	system("cls");
}

void Universe::oneGeneration()
{
	size_t str = 2, coll = 2;
	std::for_each(std::begin(universe) + 2, std::end(universe) - 2, [&](auto& it) {
		coll = 2;
		for (auto cell = std::begin(it) + 2; cell != std::end(it) - 2; ++cell)
			checkRules(str, coll++);
		str++;
	});
	std::for_each(std::begin(universe) + 2, std::end(universe) - 2, [](auto& it) {
		std::for_each(std::begin(it) + 2, std::end(it) - 2, [](char& cell) {
			if (cell == 'x')
				cell = ' ';
			if (cell == 'o')
				cell = '*';
		});
	});
}

Universe::~Universe()
{
	omega = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> time_line = omega - alpha;
	std::cout << "\n\t\t\t\t\t------------------------------------------\n\t\t\t\t\t|\tExistance time : " << time_line.count() << " s\t |\n\t\t\t\t\t------------------------------------------" << std::endl;
}
