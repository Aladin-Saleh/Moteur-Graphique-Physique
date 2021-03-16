#include <iostream>
#include "GameEngine.hpp"
#include "Debug.hpp"

using namespace Ge;

int main()
{
	Debug::Info("Moteur Graphique");
	GameEngine engine;

	if (!engine.Initialize())
	{
		Debug::Error("Erreur D'intialisation du moteur graphique");
		return -1;
	}

	try
	{
		engine.Start();	
	}
	catch (std::runtime_error& e)
	{
		Debug::Error("Exception : %s", e.what());
		return -1;
	}
	catch (std::bad_alloc& e)
	{
		Debug::Error("Exception : %s", e.what());
		return -1;
	}
	catch (const std::exception& e)
	{
		Debug::Error("Exception : %s", e.what());
		return -1;
	}

	
	engine.Release();
	std::cin.ignore();
	return 0;
}