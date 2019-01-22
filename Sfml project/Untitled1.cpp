#include<bits/stdc++.h>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"

using namespace sf;

class guldi
{
public:
    Sprite shape;

    guldi(Texture *texture, Vector2f pos)
    {
        pos.x=pos.x+60;
        shape.setTexture(*texture);
        shape.setScale(0.07f, 0.07f);
        shape.setPosition(pos);
    }

};

class Enemy
{
public:
    Sprite shape;

    Enemy(Texture *texture, Vector2u windowSize)
    {
        shape.setTexture(*texture);
        shape.setScale(0.07f, 0.07f);
        shape.setPosition(1400,rand()%300);
    }
};

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1300,800),"Battle For Avenger");
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("Fonts/bala.TTF");
    Texture halk,bullet2,stone,mbg,space2,Fire;

    Color barr(252, 13, 13), notSelected(51, 255, 51),done(255,255,0);

    SoundBuffer bullettune,crashtune,coll,button,button1;

    Clock key,agun;
    float time=0.0f,aguntime=0.0f;

    Music gamemusic,menumusic;
    gamemusic.openFromFile("Music/game.wav");
    gamemusic.setVolume(1000);
    menumusic.openFromFile("Music/menu.wav");
    menumusic.setVolume(1000);

    halk.loadFromFile("Textures/halk.png");
    bullet2.loadFromFile("Textures/bullet2.png");
    stone.loadFromFile("Textures/lola.png");
    space2.loadFromFile("Textures/bg.jpg");
    bullettune.loadFromFile("Music/bullet.wav");
    crashtune.loadFromFile("Music/crash.wav");
    coll.loadFromFile("Music/collision.wav");
    mbg.loadFromFile("Textures/menu.jpg");
    button1.loadFromFile("Music/button.wav");
    button.loadFromFile("Music/select.wav");
    Fire.loadFromFile("Textures/fire.png");
    Sound fire(bullettune),crash(crashtune),collision(coll),menubutton(button1),menuok(button);

    Sprite menubg(mbg),Hulk(halk),lbg1(space2);
    lbg1.setScale(1.4f,1.2f);
    Hulk.setScale(0.2f,0.2f);
    menubg.setScale(1.4f,1.4f);
    menubg.setPosition(0.0f,0.0f);
    Text gameovertxt,scoretxt,lifetxt,gametxt,newgametxt,highscoretxt,helptxt,exittxt,loadgametxt;

    gametxt.setFont(font);
    gametxt.setString("Save  the people");
    gametxt.setCharacterSize(80);
    gametxt.setScale(1.f,1.f);
    gametxt.setFillColor(Color::Red);

    newgametxt.setFont(font);
    newgametxt.setString("New Game :");
    newgametxt.setCharacterSize(80);
    newgametxt.setScale(0.7f,0.7f);
    newgametxt.setFillColor(notSelected);

    loadgametxt.setFont(font);
    loadgametxt.setString("Load Game :");
    loadgametxt.setCharacterSize(80);
    loadgametxt.setScale(0.7f,0.7f);
    loadgametxt.setFillColor(notSelected);


    helptxt.setFont(font);
    helptxt.setString("Instruction :");
    helptxt.setCharacterSize(80);
    helptxt.setScale(0.7f,0.7f);
    helptxt.setFillColor(notSelected);

    exittxt.setFont(font);
    exittxt.setString("Exit :");
    exittxt.setCharacterSize(80);
    exittxt.setScale(0.7f,0.7f);
    exittxt.setFillColor(notSelected);

    scoretxt.setFont(font);
    scoretxt.setCharacterSize(20);
    scoretxt.setScale(1.5,1.5);
    scoretxt.setFillColor(Color::Blue);
    scoretxt.setPosition(20.f, window.getSize().y-40);

    lifetxt.setFont(font);
    lifetxt.setCharacterSize(20);
    lifetxt.setScale(1.5,1.5);
    lifetxt.setFillColor(Color::Green);
    lifetxt.setPosition(458.f, window.getSize().y-40);

    gameovertxt.setFont(font);
    gameovertxt.setCharacterSize(30);
    gameovertxt.setFillColor(Color::Red);
    gameovertxt.setPosition(100.f, window.getSize().y / 2);
    gameovertxt.setString("GAME OVER!");

    bool stage1=true,menu=true,level1=true;

    int score = 0,k=0,l;
    int shootTimer = 20;

    int enemySpawnTimer = 0,life=10;
    std::vector<Enemy> enemies;
    std::vector<guldi> bullets;

    unsigned menuselect = 1;


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        ///menu
        if(menu)
        {
                gametxt.setPosition(250.f,25.f);///250,25
                newgametxt.setPosition(600.f,200.f);///600,200
                loadgametxt.setPosition(580,280.f);///580,280
                helptxt.setPosition(521,360.f);///521,440
                exittxt.setPosition(740,440.f);///740,520

            time=key.getElapsedTime().asSeconds();

            if(Keyboard::isKeyPressed(Keyboard::Down) && time > 0.2)
            {
                menubutton.play();
                menuselect++;
                key.restart();
            }
            if(Keyboard::isKeyPressed(Keyboard::Up) && time > 0.2)
            {
                menubutton.play();
                menuselect--;
                key.restart();
            }
            if(Keyboard::isKeyPressed(Keyboard::Enter) && time > 0.2)
            {
                menuok.play();
                key.restart();
                if(menuselect%4 == 1)
                {
                    score = 0;
                    life=9;
                    enemies.clear();
                    enemySpawnTimer=0;
                    menumusic.stop();
                    gamemusic.play();
                    gamemusic.setLoop(true);
                    menu = false;
                }
                else if(menuselect%4==2)
                {
                    menumusic.stop();
                    gamemusic.play();
                    gamemusic.setLoop(true);
                    menu= false;
                }
                else if(menuselect%4==0)
                {
                    window.close();
                }
            }

            if(menuselect%4==1)
            {
                newgametxt.setFillColor(done);
                loadgametxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
            }
            else if(menuselect%4==2)
            {
                loadgametxt.setFillColor(done);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
            }
            else if(menuselect%4==3)
            {
                helptxt.setFillColor(done);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
            }
            else if(menuselect%4==0)
            {
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(done);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
            }
            window.clear();
            window.draw(menubg);
            window.draw(gametxt);
            window.draw(newgametxt);
            window.draw(loadgametxt);
            window.draw(helptxt);
            window.draw(exittxt);
            window.display();
        }

        ///gameloop
        if(life>=0 && level1 && !menu)
        {
            if(level1)
            {
                if(stage1)
                {
                    gamemusic.play();
                    gamemusic.setLoop(true);
                    lbg1.setPosition(0.f,0.f);
                    Hulk.setPosition(Vector2f(window.getSize().x/2,window.getSize().y-180));
                    stage1 = false;
                }
                if(Keyboard::isKeyPressed(Keyboard::Left))
                    Hulk.move(-10.f, 0.f);
                if(Keyboard::isKeyPressed(Keyboard::Right))
                    Hulk.move(10.f, 0.f);
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    gamemusic.stop();
                    menumusic.play();
                    menumusic.setLoop(true);
                    menu=true;
                }

                ///collision with window
                if (Hulk.getPosition().x <= 0) //Left
                    Hulk.setPosition(0.f, Hulk.getPosition().y);
                if (Hulk.getPosition().x >= window.getSize().x - Hulk.getGlobalBounds().width) //Right
                    Hulk.setPosition(window.getSize().x - Hulk.getGlobalBounds().width, Hulk.getPosition().y);

                if (shootTimer < 15)
                    shootTimer++;

                if ((Keyboard::isKeyPressed(Keyboard::Space)) && shootTimer >= 15) //Shooting
                {
                    fire.play();
                    bullets.push_back(guldi(&bullet2, Hulk.getPosition()));
                    shootTimer = 0; //reset timer
                }
                if(life == 0)
                {

                    gamemusic.stop();
                    menumusic.play();
                    menumusic.setLoop(true);
                    menu=true;
                }

                for (size_t i = 0; i < bullets.size(); i++)
                {
                    //Move
                    bullets[i].shape.move(0.f, -20.f);

                    //Out of window bounds
                    if (bullets[i].shape.getPosition().x > window.getSize().x)
                    {
                        bullets.erase(bullets.begin() + i);
                        break;
                    }

                    for (size_t k = 0; k < enemies.size(); k++)
                    {
                        if (bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
                        {
                            crash.play();
                            enemies.erase(enemies.begin() + k);
                            bullets.erase(bullets.begin() + i);
                            score++;
                            break;
                        }
                    }
                }
                //Enemy
                if (enemySpawnTimer < 20)
                    enemySpawnTimer++;

                //enemy spawn
                if (enemySpawnTimer >= 20)
                {
                    enemies.push_back(Enemy(&stone, window.getSize()));
                    enemySpawnTimer = 0; //reset timer
                }

                for (size_t i = 0; i < enemies.size(); i++)
                {
                    enemies[i].shape.move(-6.0f, 0.0f);

                    if (enemies[i].shape.getPosition().x < 0.0)
                    {
                        life--;
                        enemies.erase(enemies.begin() + i);
                        break;
                    }

                    scoretxt.setString("Score: " + std::to_string(score));
                }
                lifetxt.setString("Life: " + std::to_string(life+1));
                window.clear();
                window.draw(lbg1);
                window.draw(Hulk);

                for (size_t i = 0; i < bullets.size(); i++)
                    window.draw(bullets[i].shape);

                for (size_t i = 0; i < enemies.size(); i++)
                    window.draw(enemies[i].shape);

                window.draw(scoretxt);
                window.draw(lifetxt);

                if(life<0)
                    window.draw(gameovertxt);
                window.display();
            }
        }
    }
    return 0;
}
