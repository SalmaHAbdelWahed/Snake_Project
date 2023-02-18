#include "Cell.h"
#include <sfml\Graphics.hpp>
#include <sfml\Window.hpp>
#include <vector>
#include <iostream>

int gridx = 20;
int gridy = 20;
float gridw=50, gridh = 50;
void appleCheck(Apple& a, vector<Snake>& s);
bool gameOverCheck(vector<Snake>& s);
void moves(vector<Snake>& s, bool addtail);

int main() {
    vector<Snake> s;
    Snake head("r", 5, 5);
    Snake B1("r", 4, 5);
    Snake B2("r", 3, 5);
    Apple a;
    s.push_back(head);
    s.push_back(B1);
    s.push_back(B2);
    int score = s.size()-3;
    string sscore = to_string(score);
    sscore = "Score: " + sscore;
    sf::RenderWindow window(sf::VideoMode(1000, 1050), "Snake Game");
    sf::RectangleShape rectangle(sf::Vector2f(1000.f, 50.f));
    rectangle.setFillColor(sf::Color(180, 180, 180));
    //setting score text up
    sf::Font font;
    if (!font.loadFromFile("BOOKOS.ttf"))
    {
        // error...
    }
    sf::Text text;
    text.setFont(font);
    text.setString(sscore);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    //Setup framerate
    sf::Clock clk;
    window.setFramerateLimit(17);
   // window.setKeyRepeatEnabled(false);
    while (window.isOpen())
    {
        float starttime = clk.restart().asMilliseconds();
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed ) {
                //float currtime = clk.getElapsedTime().asMilliseconds();
                //cout << currtime << endl;
                if (event.key.code == sf::Keyboard::Right) {
                    if (s[0].getdirection() == "u" || s[0].getdirection() == "d") {
                        s[0].setdirection("r");
                    }
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    if (s[0].getdirection() == "u" || s[0].getdirection() == "d") {
                        s[0].setdirection("l");
                    }
                }
                else if (event.key.code == sf::Keyboard::Up) {
                    if (s[0].getdirection() == "r" || s[0].getdirection() == "l") {
                        s[0].setdirection("u");
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if (s[0].getdirection() == "r" || s[0].getdirection() == "l") {
                        s[0].setdirection("d");
                    }
                }
            }
        }
        if (gameOverCheck(s)) {
            sf::Text gameOver;
            gameOver.setFont(font);
            gameOver.setString("Game Over");
            gameOver.setCharacterSize(80);
            gameOver.setFillColor(sf::Color::White);
            gameOver.setStyle(sf::Text::Bold);
            gameOver.setPosition(300,400);
            window.draw(gameOver);
            window.display();
        }
        else {
            //Check if apple eaten
            appleCheck(a, s);
            //Calculate new score
            score = s.size() - 3;
            sscore = to_string(score);
            sscore = "Score: " + sscore;
            text.setString(sscore);

            window.clear();
            window.draw(rectangle);
            window.draw(text);
            ///////////////  Draw grid /////////////////
            sf::Vertex line[] = { sf::Vertex(sf::Vector2f(0.f, 90.f)), sf::Vertex(sf::Vector2f(0.f, 950.f)) };
            window.draw(line, 2, sf::Lines);
            for (int i = 1; i < 21; i++) {
                sf::Vertex line[] = { sf::Vertex(sf::Vector2f(i * gridw , 50.f)), sf::Vertex(sf::Vector2f(i * gridw, 1050.f)) };
                window.draw(line, 2, sf::Lines);
            }
            for (int i = 1; i < 21; i++) {
                sf::Vertex line[] = { sf::Vertex(sf::Vector2f(0.f,i * gridh)), sf::Vertex(sf::Vector2f(1000.f,i * gridh)) };
                window.draw(line, 2, sf::Lines);
            }
            ////////////// Draw Snake  /////////////////
            int sx = 0, sy = 0;
            for (int i = 0; i < s.size(); i++) {
                sf::RectangleShape srect(sf::Vector2f(gridw - 2, gridh - 2));
                srect.setFillColor(sf::Color::Green);
                sx = (s[i].getheadx()) * gridw;
                sy = (s[i].getheady()) * gridh;
                srect.setPosition(sx, sy);
                window.draw(srect);
            }
            /////////// Draw Apple  /////////////////        
            sf::RectangleShape appler(sf::Vector2f(gridw - 2, gridh - 2));
            appler.setFillColor(sf::Color::Red);
            sx = (a.getx()) * gridw;
            sy = (a.gety()) * gridh;
            appler.setPosition(sx, sy);
            window.draw(appler);
            window.display();
        }
    }
    return 0;
}
void appleCheck(Apple& a, vector<Snake>& s) { // Check if apple eaten to increase score and change a place 
    if (a.getx() == s[0].getheadx() && a.gety() == s[0].getheady()) {
        a.setxy();
        moves(s,1);
    }
    else {
        moves(s, 0);
    }
}
void moves(vector<Snake>& s,bool addtail) { //Move the snake
    int tempx = s[0].getheadx();
    int tempy = s[0].getheady();
    int newx, newy;
    if (addtail) { //We add an extra node in case an apple was eaten
        int newx = s[s.size() - 1].getheadx();
        int newy = s[s.size() - 1].getheady();
        string d = s[s.size() - 1].getdirection();
        Snake body(d, newx, newy);
        s.push_back(body);
    }
    for (int i = s.size() - 1; i > 0; i--) { // move the snake body
        int tempx = s[i-1].getheadx();
        int tempy = s[i-1].getheady();
        s[i].setheadx(tempx);
        s[i].setheady(tempy);
    }
    //move the snake head based on direction
    if (s[0].getdirection() == "l") {
        newx = tempx - 1;
        if (newx < 0) { newx = gridx; }
        s[0].setheadx(newx);
    }
    else if (s[0].getdirection() == "r") {
        newx = tempx + 1;
        if (newx > gridx) { newx = 0; }
        s[0].setheadx(newx);
    }
    else if (s[0].getdirection() == "u") {
        newy = tempy - 1;
        if (newy <= 0) { newy = gridy; }
        s[0].setheady(newy);
    }
    else if (s[0].getdirection() == "d") {
        newy = tempy + 1;
        if (newy > gridy) { newy = 1; }
        s[0].setheady(newy);
    }
}
bool gameOverCheck(vector<Snake>& s) { // Check if head collided with any part of the snake's body 
    for (int i = 1; i < s.size(); i++) {
        if (s[0].getheadx()==s[i].getheadx() && s[0].getheady() == s[i].getheady()) {
            return true;
        }
    }
    return false;
}