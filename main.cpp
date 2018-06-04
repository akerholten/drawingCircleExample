#include <SFML/Graphics.hpp>
#include <iostream>
#include "globals.hpp"


void line(sf::RenderWindow& window, float x1, float y1, float x2, float y2);


int main(){
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "SFML Textures");

    float posX = WINDOW_X/2;
    float posY = WINDOW_Y/2;

    sf::Image image;
    image.create(255, 255);
    sf::Vector2u imageSize = image.getSize();

    sf::Clock clock;
    float dt;

    std::random_device rnd;
    std::mt19937 rng(rnd());
    std::uniform_real_distribution<float> random(0.0f, 1.0f);


    // Code for making midpoint displacement for circle
    float lines[NUMBER_OF_LINES];
    float alpha = 50.0f;
    rng.seed(10.0f);
    lines[0] = random(rng) * alpha;
    lines[NUMBER_OF_LINES - 1] = random(rng) * alpha;
    for (int i = NUMBER_OF_LINES - 1; i > 1; i /= 2) {
        for (int j = i / 2; j < NUMBER_OF_LINES - 1; j += i) {
            lines[j] = ((lines[j - i / 2] + lines[j + i / 2]) / 2) + (random(rng) * alpha);
        }
    alpha /= 2.0f;
    }


    sf::Texture textureBall;
    textureBall.loadFromImage(image);
    
    sf::Sprite spriteBall(textureBall);

    while (window.isOpen()){
        dt = clock.getElapsedTime().asSeconds();
        sf::Event event;
        while(window.pollEvent(event)){
            dt = clock.getElapsedTime().asSeconds();
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                posX -= 20 * dt;
                spriteBall.move(-(20 * dt), 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                posX += 20 * dt;
                spriteBall.move(20 * dt, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                posY += 20 * dt;
                spriteBall.move(0, 20 * dt);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                posY -= 20 * dt;
                spriteBall.move(0, -(20 * dt));
            }

        window.clear();



        // Code for making a circle and drawing it
        sf::Vector2f startPosition(WINDOW_X/2, WINDOW_Y/2);
        int offsetRotation = 100;
        float rotAmount = 0.1f;
        sf::Vector2f previousVec(startPosition.x, startPosition.y + offsetRotation);

        for(int i = 0; i < NUMBER_OF_LINES; i++){
            sf::Vector2f newPos;

            sf::Vector2f selfVector = previousVec - startPosition;
             
            // Adding the midpoint displacement as a factor
            selfVector.y = selfVector.y + lines[i];

            // rotate pos vector
            newPos.x = ((selfVector.x * cos(rotAmount)) - (selfVector.y * sin(rotAmount))) + startPosition.x;
            newPos.y = ((selfVector.x * sin(rotAmount)) + (selfVector.y * cos(rotAmount))) + startPosition.y;

            line(window, previousVec.x, previousVec.y, newPos.x, newPos.y);

            previousVec.x = newPos.x;
            previousVec.y = newPos.y;
        }




        window.draw(spriteBall);
        window.display();
        clock.restart();
        }
    }
    return EXIT_SUCCESS;
}


void line(sf::RenderWindow& window, float x1, float y1, float x2, float y2){
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x1, y1)),
        sf::Vertex(sf::Vector2f(x2, y2))
    };
    window.draw(line, 2, sf::Lines);
}