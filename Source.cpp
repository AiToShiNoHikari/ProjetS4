#include "IA.h"

void main()
{
#ifdef _DEBUG
	std::cout << ">>>>> Debug: <<<<<" << std::endl;
#else
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

	int TailleEcranH = sf::VideoMode::getDesktopMode().width;
	int TailleEcranV = sf::VideoMode::getDesktopMode().height;

	sf::RenderWindow window(sf::VideoMode(TailleEcranH, TailleEcranV), "ProjetSemestre4");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//Menu(window);
	Camera(window);

}