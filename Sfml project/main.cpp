#include "SFML\Graphics.hpp"
#include <iostream>
using namespace std;
using namespace sf;
int main()

{
    RenderWindow Window;
    Window.setFramerateLimit(10);
    Window.create(VideoMode(800,600),"My First Sfml Game", Style::Titlebar | Style::Close | Style::Resize);
    Window.setFramerateLimit(10);
    IntRect arrowRect(0,0,96,96);
    IntRect batRect(0,0,800,800);
    bool shooting = false;
    Clock clock;
    float time=0.0f;
    int i;
       Event event;

       Texture backgraTexture;
       backgraTexture.loadFromFile("the backgra.png");
       Sprite backgraSprite(backgraTexture);


       Texture treeTexture;
       treeTexture.loadFromFile("tree.png");
       Sprite treeSprite(treeTexture);

       Texture batTexture;
       batTexture.loadFromFile("the bats.png");
       Sprite batSprite(batTexture);
        batSprite.setTextureRect(batRect);

       //vector<Sprite> bats;

        Texture arrowTexture;
       arrowTexture.loadFromFile("arrow.png");
       Sprite arrowSprite(arrowTexture);
       arrowSprite.setTextureRect(arrowRect);

       batSprite.setOrigin(300, 300);
       batSprite.setPosition(800,200);
       treeSprite.setPosition(0,100);

       arrowSprite.setPosition(170,430);
       backgraSprite.scale(.2,.25);
       treeSprite.scale(.25,.4);
       batSprite.scale(-.1,.1);
       arrowSprite.scale(1,1);
       int batFlyPos = 0;
       int arrowFlyPos = 0;

    while(Window.isOpen())
    {
        while(Window.pollEvent(event))
        {
            if(event.type==Event::EventType::Closed)
             Window.close();
        }
        Window.clear();
        Window.draw(backgraSprite);
        Window.draw(treeSprite);
        Window.draw(batSprite);
        Window.draw(arrowSprite);
        Window.display();

        if(batFlyPos<2400 && batSprite.getPosition().x>150) batFlyPos+=800;
        else if(batSprite.getPosition().x<=150) batFlyPos=1600;
        else batFlyPos=0;
        batRect.left=batFlyPos;
        batSprite.setTextureRect(batRect);
        if(batSprite.getPosition().x>150)batSprite.move(-10, 0);
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            shooting = true;
        }
        if(shooting) {
            if(arrowFlyPos<510) arrowFlyPos+=102;
            else shooting = false, arrowFlyPos=0;
        }
        Vector2i MousePos = Mouse::getPosition();
        cout<<MousePos.x<<"\t"<<MousePos.y<<"\n";
        arrowRect.left=arrowFlyPos;
        arrowSprite.setTextureRect(arrowRect);

    }
    return 0;
}
