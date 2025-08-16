#include <SFML/Graphics.hpp>
#include <iostream> 
#include <exception>
#include <Engine/Engine.hpp>
#include"Graphic/Weapon.hpp"
#include "Utility/Logger.hpp"

int main()
{
    try
    {
        Engine engine;
        engine.Prepare();
        engine.Run();
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR: " << e.what();
    }
    return 0;
}
