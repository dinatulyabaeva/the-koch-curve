#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace sf;
using namespace std;

RenderWindow window(VideoMode(1000, 1000), "koch fractal");
void Koch(float startx, float endx, float starty, float endy, int level)
{
    sf::RectangleShape line(sf::Vector2f(150, 5));
    float x1, x2, x3, y1, y2, y3, L, cosa, sina, h;
    //L - длина отрезка, от начальной до конечной точки, 
    //h - высота равностороннего треугольника, который образует "галочку"
    //x1, y1 - координаты первой точки, что делит отрезок на три части
    //x3, y3 - координаты второй точки, что делит отрезок на три части
    //x2, y2 - координаты вершины "галочки"
    if (level == 1)
    {
        sf::Vertex line[] =
        {
          sf::Vertex(sf::Vector2f(200+800*startx, 500+800*starty)),
          sf::Vertex(sf::Vector2f(200+800*endx,500+800*endy))
        };
        line[1].color = Color::White;
        window.draw(line, 2, sf::Lines);
       // ofstream d("test.txt", ios_base::app);
       //d << startx << " " << starty << " " << endx << " " << endy << endl;

    }
    else
    {
        L = sqrt((endx - startx) * (endx - startx) + (endy - starty) * (endy - starty));
        h = L / (2 * sqrt(3));
        sina = (endy - starty) / L;
        cosa = (endx - startx) / L;
        x1 = startx + (endx - startx) / 3;
        x2 = (endx + startx) / 2 + h * sina;
        x3 = startx + 2 * (endx - startx) / 3;
        y1 = starty + (endy - starty) / 3;
        y2 = (endy + starty) / 2 - h * cosa;
        y3 = starty + 2 * (endy - starty) / 3;
        Koch(startx, x1, starty, y1, level - 1);
        Koch(x1, x2, y1, y2, level - 1);
        Koch(x2, x3, y2, y3, level - 1);
        Koch(x3, endx, y3, endy, level - 1);
    }
}

int main()
{
    float x1, x2, y1, y2;
    x1 = 0;
    x2 = 1;
    y1 = 0;
    y2 = 0;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else
                Koch(x1, x2,  y1, y2, 3);
        }
        window.display();
    }
}