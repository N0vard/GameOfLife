#include "Universe/Universe.h"

void slowPrintString
(
	const std::string string, 
	const size_t sleep_for
);

int main(void)
{	
	std::string Title = "\"Life\" John Conway's Math Game",
		Width	= "Enter the width Space : ",
		Height	= "Enter the height Space : ";

	size_t width, height;

	do {
		std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

		std::cout << "\t\t\t\t\t\t\b\b";
		slowPrintString(Title, 30);
		std::cout << std::endl;

		std::cout << "------------------------------------------------------------------------------------------------------------------------\n" << std::endl;

		slowPrintString(Width, 30);
		std::cin >> width;

		std::cout << "---------------------------|\n";

		slowPrintString(Height, 30);
		std::cin >> height;

		system("cls");
	} while (width < 20 || width > 120 || height < 10 || height > 29);

	Universe u(width, height);

	u.printUniverse();

	while (true) {
		u.oneGeneration();

		u.printUniverse();
	}

	return 0;
}

void slowPrintString
(
	const std::string string, 
	const size_t sleep_for
)
{
	for (char ch : string) {
		std::cout << ch;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_for));
	}
}
