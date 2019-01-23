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

    guldi(Texture *texture)
    {
        shape.setTexture(*texture);
        shape.setScale(0.07f, 0.07f);
    }

};

class Aircraft
{
public:
    Sprite shape;

    Aircraft(Texture *texture, Vector2u windowSize)
    {
        shape.setTexture(*texture);
        shape.setScale(0.07f, 0.07f);
        shape.setPosition(1400,rand()%300);
    }
};

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1300,800),"Save The People");
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("Fonts/bala.TTF");
    Texture superweapon,guli,juddhobiman,mbg,backgra,Fire,biman,bomb;

    Color barr(252, 13, 13), notSelected(51, 255, 51),done(255,255,0);

    SoundBuffer bullettune,crashtune,coll,button,button1;

    Clock key,agun;
    float time=0.0f,aguntime=0.0f;

    Music gamemusic,menumusic;
    gamemusic.openFromFile("Music/game.wav");
    gamemusic.setVolume(10);
    menumusic.openFromFile("Music/menu.wav");
    menumusic.setVolume(20);
    //bullettune.loadFromFile("Music/bullet.wav");
   // bullettune.setVolume(50);


    superweapon.loadFromFile("Textures/superweapon.png");
    guli.loadFromFile("Textures/guli.png");
    juddhobiman.loadFromFile("Textures/lola1.png");
    biman.loadFromFile("Textures/lola.png");
    backgra.loadFromFile("Textures/bg.jpg");
    bullettune.loadFromFile("Music/bullet.wav");
    crashtune.loadFromFile("Music/crash.wav");
    coll.loadFromFile("Music/collision.wav");
    mbg.loadFromFile("Textures/menu.jpg");
    button1.loadFromFile("Music/menu.ogg");
    button.loadFromFile("Music/select.wav");
    Fire.loadFromFile("Textures/fire.png");
    bomb.loadFromFile("Textures/bomb.png");

    Sound fire(bullettune),crash(crashtune),collision(coll),menubutton(button1),menuok(button);

    Sprite menubg(mbg),Bala(superweapon),lbg1(backgra),bmn1(biman),bmn2(biman);
    lbg1.setScale(1.4f,1.2f);
    Bala.setScale(0.2f,0.2f);
    menubg.setScale(1.4f,1.4f);
    menubg.setPosition(0.0f,0.0f);
    bmn1.setScale(0.1,0.1);
    bmn2.setScale(0.1,0.1);
    Text gameovertxt,scoretxt,lifetxt,gametxt,newgametxt,highscoretxt,helptxt,exittxt,loadgametxt;

    gametxt.setFont(font);
    gametxt.setString("Save the people");
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

    bool stage=true,menu=true,level1=true,bm1=true,bm2=false;

    int score = 0,k=0,l;
    int shootTimer = 20;

    int enemySpawnTimer = 0,life=10,bb=0;
    std::vector<Aircraft> enemies;
    std::vector<guldi> bullets;
    std::vector<guldi> b1;

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
                    life=10;
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
                if(stage)
                {
                    gamemusic.play();
                    gamemusic.setLoop(true);
                    lbg1.setPosition(0.f,0.f);
                    Bala.setPosition(Vector2f(window.getSize().x/2,window.getSize().y-180));
                    bmn1.setPosition(10.f,10.f);
                    bmn2.setPosition(window.getSize().x-70,10);
                    stage = false;
                    bb=0;
                }
                if(Keyboard::isKeyPressed(Keyboard::Left))
                    Bala.move(-10.f, 0.f);
                if(Keyboard::isKeyPressed(Keyboard::Right))
                    Bala.move(10.f, 0.f);
                if(Keyboard::isKeyPressed(Keyboard::Up))
                    Bala.move(0.f, -10.f);
                if(Keyboard::isKeyPressed(Keyboard::Down))
                    Bala.move(0.f, 10.f);
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    gamemusic.stop();
                    menumusic.play();
                    menumusic.setLoop(true);
                    menu=true;
                }

                ///collision with window
                if (Bala.getPosition().x <= 0) //Left
                    Bala.setPosition(0.f, Bala.getPosition().y);
                if (Bala.getPosition().x >= window.getSize().x - Bala.getGlobalBounds().width) //Right
                    Bala.setPosition(window.getSize().x - Bala.getGlobalBounds().width, Bala.getPosition().y);
                if (Bala.getPosition().y <= 0) //Left
                    Bala.setPosition(Bala.getPosition().x,0);
                if (Bala.getPosition().y >= window.getSize().y - Bala.getGlobalBounds().height+50) //Right
                    Bala.setPosition( Bala.getPosition().x,50+window.getSize().y - Bala.getGlobalBounds().height);


                if (shootTimer < 10)
                    shootTimer++;

                if ((Keyboard::isKeyPressed(Keyboard::Space)) && shootTimer >= 10)//Shooting
                {
                    fire.play();
                    bullets.push_back(guldi(&guli));
                    bullets[bullets.size()-1].shape.setPosition(Vector2f(Bala.getPosition().x+40,Bala.getPosition().y));
                    bullets.push_back(guldi(&guli));
                    bullets[bullets.size()-1].shape.setPosition(Vector2f(Bala.getPosition().x+85,Bala.getPosition().y));
                    shootTimer = 0;//reset timer
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
                if (enemySpawnTimer < 15)
                    enemySpawnTimer++;
                    if(bb<30)
                        bb++;
                    if(bb >=30)
                    {
                        bb=0;
                        b1.push_back(guldi(&bomb));
                        b1[b1.size()-1].shape.setScale(0.2f,0.2f);
                        b1[b1.size()-1].shape.setPosition(bmn1.getPosition().x+15,bmn1.getPosition().y+10);
                        b1.push_back(guldi(&bomb));
                        b1[b1.size()-1].shape.setScale(0.2f,0.2f);
                        b1[b1.size()-1].shape.setPosition(bmn2.getPosition().x+15,bmn2.getPosition().y+10);
                    }
                    for(int k=0 ; k < b1.size() ; k++)
                    {
                        b1[k].shape.move(0,12.f);
                        if(b1[k].shape.getPosition().y > window.getSize().y)
                            b1.erase(b1.begin()+k);
                        if(b1[k].shape.getGlobalBounds().intersects(Bala.getGlobalBounds()))
                        {
                             b1.erase(b1.begin()+k);
                             life--;
                        }
                    }

                //enemy spawn
                if (enemySpawnTimer >= 15)
                {
                    enemies.push_back(Aircraft(&juddhobiman, window.getSize()));
                    enemies[enemies.size()-1].shape.setScale(0.7,0.7);
                    enemySpawnTimer = 0; //reset timer
                }

                if(bm1)
                {
                    bmn1.move(8.0,0.0);
                    if(bmn1.getPosition().x > window.getSize().x-60)
                        bm1=false;
                }
                if(!bm1)
                {
                    bmn1.move(-8.0,0.0);
                    if(bmn1.getPosition().x < 10)
                        bm1=true;
                }
                 if(bm2)
                {
                    bmn2.move(8.0,0.0);
                    if(bmn2.getPosition().x > window.getSize().x-60)
                        bm2=false;
                }
                if(!bm2)
                {
                    bmn2.move(-8.0,0.0);
                    if(bmn2.getPosition().x < 10)
                        bm2=true;
                }

                for (size_t i = 0; i < enemies.size(); i++)
                {
                    enemies[i].shape.move(-6.0f, 0.0f);

                    if (enemies[i].shape.getPosition().x < 0.0)
                    {
                        enemies.erase(enemies.begin() + i);
                        break;
                    }

                    scoretxt.setString("Score: " + std::to_string(score));
                }
                lifetxt.setString("Life: " + std::to_string(life+1));
                window.clear();
                window.draw(lbg1);
                window.draw(Bala);

                for (size_t i = 0; i < bullets.size(); i++)
                    window.draw(bullets[i].shape);

                for (size_t i = 0; i < enemies.size(); i++)
                    window.draw(enemies[i].shape);

                 for (size_t i = 0; i < b1.size(); i++)
                    window.draw(b1[i].shape);

                window.draw(scoretxt);
                window.draw(lifetxt);
                window.draw(bmn1);
                window.draw(bmn2);

                if(life<0)
                    window.draw(gameovertxt);
                window.display();
            }
        }
    }
    return 0;
}
