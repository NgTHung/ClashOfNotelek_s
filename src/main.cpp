#include <SFML/Graphics.hpp>
// #include "include/engine.hpp"
#include <iostream> // For error messages
#include <exception>
int main()
{
    // 1. Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}, 32), "SFML Hello World");
    window.setFramerateLimit(60); // Optional: Limit framerate

    // 2. Load a font
    sf::Font font;
    // IMPORTANT: Place 'arial.ttf' (or your chosen font file)
    // in the same directory as your executable, or provide the full path.
    if (!font.openFromFile("arial.ttf"))
    {
        std::cerr << "Error: Could not load font 'arial.ttf'." << std::endl;
        std::cerr << "Please ensure 'arial.ttf' is in the correct directory." << std::endl;
        return -1; // Indicate an error
    }

    std::vector<std::string> name{"NVA", "DHP", "NTH"};

    int index = 0;

    // 3. Create a text object
    sf::Text helloText(font, name[index], 50U);

    // Set the color
    helloText.setFillColor(sf::Color::White);

    // Set the style (optional)
    // helloText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Set the position (top-left corner of the text)
    // Let's center it roughly for better visibility
    sf::FloatRect textBounds = helloText.getLocalBounds();
    helloText.setOrigin(textBounds.getCenter());
    helloText.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.f);

    // 4. Main loop: runs as long as the window is open
    while (window.isOpen())
    {
        helloText.setString(name[index]);
        // Process events
        while (auto event = window.pollEvent())
        {
            if (!event.has_value())
                continue;
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
            // // Escape key: exit
            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                    (index += 1) %= 3;
            }
        }

        // Clear screen
        window.clear(sf::Color::Black); // Clear with black color

        // Draw the text
        window.draw(helloText);

        // Update the window
        window.display();
    }

    return 0;
}

// int main()
// {
//     try
//     {
//         Engine engine;
//         engine.Run();
//     }
//     catch (std::exception &e)
//     {
//         std::cout << "ERROR: " << e.what();
//     }
//     return 0;
// }