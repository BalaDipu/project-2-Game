#include<bits/stdc++.h>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SFML\Audio.hpp"

using namespace sf;

class Bullet1
{
public:
    Sprite shape;

    Bullet1(Texture *texture, Vector2f pos)
    {
        pos.x=pos.x+50;
        shape.setTexture(*texture);
        shape.setScale(0.07f, 0.07f);
        shape.setPosition(pos);
    }

};

class Player
{
public:
    Sprite shape;
    Texture *texture;
    std::vector<Bullet1> bullets;
    Player(Texture *texture)
    {
        shape.setTexture(*texture);
        shape.setScale(0.07f, 0.07f);
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
        shape.setPosition(rand()% (int)(windowSize.x - this->shape.getGlobalBounds().width),0);
    }
};

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1300,800),"Battle For Avenger");
    window.setFramerateLimit(60);

    Font font,style,style1;
    font.loadFromFile("Fonts/fine.ttf");
    style.loadFromFile("Fonts/font4.TTF");
    style1.loadFromFile("Fonts/font6.TTF");

    Texture stark,thor,spider,halk,thanos,bullet1,bullet2,bullet3,bullet4,stone,space1,mbg,space2,space3,Fire,step1,step2,step3,step4;

    Color barr(252, 13, 13), notSelected(51, 255, 51),done(255,255,0), beat(200, 20, 20), dev(255, 255, 255, 100),Spark;

    SoundBuffer bullettune,crashtune,coll,button,button1;

    Clock key,agun;
    float time=0.0f,aguntime=0.0f;

    Music gamemusic,menumusic;
    gamemusic.openFromFile("Music/game.wav");
    gamemusic.setVolume(1000);
    menumusic.openFromFile("Music/menu.wav");
    menumusic.setVolume(1000);

    stark.loadFromFile("Textures/stark.png");
    thor.loadFromFile("Textures/thor.png");
    thanos.loadFromFile("Textures/thanos.png");
    halk.loadFromFile("Textures/halk.png");
    spider.loadFromFile("Textures/spider.png");
    bullet1.loadFromFile("Textures/bullet1.png");
    bullet2.loadFromFile("Textures/bullet2.png");
    bullet3.loadFromFile("Textures/bullet3.png");
    bullet4.loadFromFile("Textures/bullet4.png");
    stone.loadFromFile("Textures/stone.png");
    space1.loadFromFile("Textures/space5.jpg");
    bullettune.loadFromFile("Music/bullet.wav");
    crashtune.loadFromFile("Music/crash.wav");
    coll.loadFromFile("Music/collision.wav");
    mbg.loadFromFile("Textures/menu.jpg");
    space2.loadFromFile("Textures/space2.jpg");
    space3.loadFromFile("Textures/space4.jpg");
    button1.loadFromFile("Music/button.wav");
    button.loadFromFile("Music/select.wav");
    Fire.loadFromFile("Textures/fire.png");
    step1.loadFromFile("Textures/step1.png");
    step2.loadFromFile("Textures/step2.png");
    step3.loadFromFile("Textures/step3.png");
    step4.loadFromFile("Textures/step4.png");

    Sound fire(bullettune),crash(crashtune),collision(coll),menubutton(button1),menuok(button);

    Sprite bg1(space1),bg2(space1),menubg(mbg),Stark(stark),Thanos(thanos),Thor(thor),Hulk(halk)
    ,lbg1(space2),lbg2(space2),lbg3(space3),lbg4(space3),menupic1(space1),menupic2(space2),menupic3(space3),spark(Fire),
    Step1(step1),Step2(step2),Step3(step3),Step4(step4);

    Step1.setScale(0.3f,0.3f);
    Step2.setScale(0.3f,0.3f);
    Step3.setScale(0.3f,0.3f);
    Step4.setScale(0.3f,0.3f);
    bg1.setScale(0.6f,0.34f);
    bg2.setScale(0.6f,0.34f);
    menubg.setScale(0.34f,0.38f);
    menubg.setPosition(0.0f,0.0f);
    spark.setScale(0.3f,0.3f);

    Text scoretxt,gameovertxt,lifetxt,mgzntxt,gametxt,newgametxt,highscoretxt,stagetxt,helptxt,exittxt,loadgametxt;

    gametxt.setFont(style);
    gametxt.setString("Battle For Avenger!");
    gametxt.setCharacterSize(80);
    gametxt.setScale(1.f,1.f);
    gametxt.setFillColor(Color::Red);

    newgametxt.setFont(style1);
    newgametxt.setString("New Game :");
    newgametxt.setCharacterSize(80);
    newgametxt.setScale(0.7f,0.7f);
    newgametxt.setFillColor(notSelected);

    loadgametxt.setFont(style1);
    loadgametxt.setString("Load Game :");
    loadgametxt.setCharacterSize(80);
    loadgametxt.setScale(0.7f,0.7f);
    loadgametxt.setFillColor(notSelected);

    stagetxt.setFont(style1);
    stagetxt.setString("Stages :");
    stagetxt.setCharacterSize(80);
    stagetxt.setScale(0.7f,0.7f);
    stagetxt.setFillColor(notSelected);

    helptxt.setFont(style1);
    helptxt.setString("Instruction :");
    helptxt.setCharacterSize(80);
    helptxt.setScale(0.7f,0.7f);
    helptxt.setFillColor(notSelected);

    exittxt.setFont(style1);
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
    lifetxt.setString("Life:");

    mgzntxt.setFont(font);
    mgzntxt.setCharacterSize(20);
    mgzntxt.setScale(1.5,1.5);
    mgzntxt.setFillColor(Color::Red);
    mgzntxt.setPosition(933.f, window.getSize().y-40);
    mgzntxt.setString("Bullet:");

    gameovertxt.setFont(font);
    gameovertxt.setCharacterSize(30);
    gameovertxt.setFillColor(Color::Red);
    gameovertxt.setPosition(100.f, window.getSize().y / 2);
    gameovertxt.setString("GAME OVER!");

    bool stage1=true,menu=true,me=true,level1=true,level2=false,level3=false,agunbool=false,blll=false;

    //Player init
    int score = 0,mgzn=100,k=0,l;
    Player player(&halk);
    int shootTimer = 20;

    RectangleShape bar(Vector2f(window.getSize().x+50,100));
    bar.setFillColor(Color::White);
    bar.setPosition(window.getPosition().x/2-155,window.getSize().y-50);

    //Enemy init
    int enemySpawnTimer = 0,life=10;
    std::vector<Enemy> enemies;

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
            if(me)
            {
                menumusic.play();
                menumusic.setLoop(true);

                Thanos.setRotation(55.f);
                Thanos.setScale(0.25f,0.25f);
                Hulk.setRotation(55.f);
                Hulk.setScale(0.10f,0.10f);
                Thor.setRotation(20.f);
                Thor.setScale(0.09f,0.09f);
                Stark.setScale(0.08f,0.08f);

                gametxt.setPosition(250.f,-100.f);///250,25
                newgametxt.setPosition(window.getSize().x,200.f);///600,200
                loadgametxt.setPosition(window.getSize().x,280.f);///580,280
                stagetxt.setPosition(window.getSize().x,360.f);///687,360
                helptxt.setPosition(window.getSize().x,440.f);///521,440
                exittxt.setPosition(window.getSize().x,520.f);///740,520

                Hulk.setPosition(0.f,400.f);///hulk280,400
                Thanos.setPosition(200.f,0.f);///thanos200,250
                Thor.setPosition(320.f,window.getSize().y);///thor320,550
                Stark.setPosition(window.getSize().x,600);///stark440,600
                menupic1.setScale(0.05f,0.05f);
                menupic1.setPosition(600.f,100.f);
                me=false;
            }

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
                if(menuselect%5 == 1)
                {
                    score = 0;
                    life = 10;
                    mgzn=100;
                    enemies.clear();
                    enemySpawnTimer=0;
                    menumusic.stop();
                    gamemusic.play();
                    gamemusic.setLoop(true);
                    menu = false;
                }
                else if(menuselect%5==2)
                {
                    menumusic.stop();
                    gamemusic.play();
                    gamemusic.setLoop(true);
                    menu= false;
                }
                else if(menuselect%5==0)
                {
                    window.close();
                }
            }

            if(menuselect%5==1)
            {
                newgametxt.setFillColor(done);
                loadgametxt.setFillColor(notSelected);
                stagetxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
            }
            else if(menuselect%5==2)
            {
                loadgametxt.setFillColor(done);
                stagetxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
            }
            else if(menuselect%5==3)
            {
                stagetxt.setFillColor(done);
                helptxt.setFillColor(notSelected);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
            }
            else if(menuselect%5==4)
            {
                helptxt.setFillColor(done);
                exittxt.setFillColor(notSelected);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
                stagetxt.setFillColor(notSelected);
            }
            else if(menuselect%5==0)
            {
                exittxt.setFillColor(done);
                newgametxt.setFillColor(notSelected);
                loadgametxt.setFillColor(notSelected);
                stagetxt.setFillColor(notSelected);
                helptxt.setFillColor(notSelected);
            }

            if(newgametxt.getPosition().x!=600)
                newgametxt.move(-10.f,0.f);
            if(loadgametxt.getPosition().x!=580)
                loadgametxt.move(-10.f,0.f);
            if(stagetxt.getPosition().x!=690)
                stagetxt.move(-10.f,0.f);
            if(helptxt.getPosition().x!=520)
                helptxt.move(-10.f,0.f);
            if(exittxt.getPosition().x!=740)
                exittxt.move(-10.f,0.f);
            if(gametxt.getPosition().y!=25)
                gametxt.move(0.f,5.0f);

            if(Hulk.getPosition().x!=280)
                Hulk.move(5.f,0.f);
            if(Thanos.getPosition().y!=250)
                Thanos.move(0.f,5.f);
            if(Thor.getPosition().y!=550)
                Thor.move(0.f,-5.f);
            if(Stark.getPosition().x!=440)
                Stark.move(-10.f,0.f);

            window.clear();
            window.draw(menubg);
            window.draw(Thanos);
            window.draw(Hulk);
            window.draw(Thor);
            window.draw(Stark);
            window.draw(gametxt);
            window.draw(newgametxt);
            window.draw(loadgametxt);
            window.draw(stagetxt);
            window.draw(helptxt);
            window.draw(exittxt);
            window.display();
        }

        ///gameloop
        if(life>=0 && (level1 || level2 || level3) && !menu)
        {
            ///stage1
            if(level1)
            {
                if(stage1)
                {
                    gamemusic.play();
                    gamemusic.setLoop(true);
                    bg1.setPosition(0.f,0.f);
                    bg2.setPosition(0.f,bg1.getPosition().y-window.getSize().y+70);
                    player.shape.setPosition(Vector2f(window.getSize().x/2,window.getSize().y-150));
                    mgzn=100;
                    stage1 = false;
                }
                if(Keyboard::isKeyPressed(Keyboard::Left))
                    player.shape.move(-10.f, 0.f);
                if(Keyboard::isKeyPressed(Keyboard::Right))
                    player.shape.move(10.f, 0.f);
                if(Keyboard::isKeyPressed(Keyboard::Escape))
                {
                    gamemusic.stop();
                    menumusic.play();
                    menumusic.setLoop(true);
                    menu=true;
                    me=true;
                }

                ///collision with window
                if (player.shape.getPosition().x <= 0) //Left
                    player.shape.setPosition(0.f, player.shape.getPosition().y);
                if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //Right
                    player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);

                if (shootTimer < 15)
                    shootTimer++;

                if ((Mouse::isButtonPressed(Mouse::Left)||Keyboard::isKeyPressed(Keyboard::Space)) && shootTimer >= 15 && mgzn > 0) //Shooting
                {
                    fire.play();
                    mgzn--;
                    player.bullets.push_back(Bullet1(&bullet2, player.shape.getPosition()));
                    shootTimer = 0; //reset timer
                }
                if(mgzn==0 || life == 0)
                {

                    gamemusic.stop();
                    menumusic.play();
                    menumusic.setLoop(true);
                    menu=true;
                    me=true;
                }

                for (size_t i = 0; i < player.bullets.size(); i++)
                {
                    //Move
                    player.bullets[i].shape.move(0.f, -20.f);

                    //Out of window bounds
                    if (player.bullets[i].shape.getPosition().x > window.getSize().x)
                    {
                        player.bullets.erase(player.bullets.begin() + i);
                        break;
                    }

                    for (size_t k = 0; k < enemies.size(); k++)
                    {
                        if (player.bullets[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds()))
                        {
                            crash.play();
                            enemies.erase(enemies.begin() + k);
                            player.bullets.erase(player.bullets.begin() + i);
                            score++;
                            break;
                        }
                    }
                }
                //Enemy
                if (enemySpawnTimer < 10)
                    enemySpawnTimer++;

                //enemy spawn
                if (enemySpawnTimer >= 10 && score < 25)
                {
                    enemies.push_back(Enemy(&stone, window.getSize()));
                    enemySpawnTimer = 0; //reset timer
                }

                if (enemySpawnTimer >= 6 && score >= 25)
                {
                    enemies.push_back(Enemy(&stone, window.getSize()));
                    enemySpawnTimer = 0; //reset timer
                }

                for (size_t i = 0; i < enemies.size(); i++)
                {
                    enemies[i].shape.move(0.f, 6.0f);

                    if (enemies[i].shape.getPosition().y >= window.getSize().y - enemies[i].shape.getGlobalBounds().height)
                    {
                        enemies.erase(enemies.begin() + i);
                        break;
                    }

                    if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds()))
                    {
                        collision.play();
                        enemies.erase(enemies.begin() + i);
                        life--; // PLAYER TAKE DAMAGE
                        agunbool=true;
                        blll=true;
                        break;
                    }
                    scoretxt.setString("Score: " + std::to_string(score));
                }

                RectangleShape health(Vector2f(life*20,25));
                health.setFillColor(Color::Green);
                health.setPosition(550,window.getSize().y-35);

                RectangleShape magazine(Vector2f(mgzn*2,25));
                magazine.setFillColor(Color::Red);
                magazine.setPosition(1050,window.getSize().y-35);

                bg1.move(0.f,0.7f);
                bg2.move(0.f,0.7f);
                if(bg1.getPosition().y>0)
                    bg2.setPosition(0.f,bg1.getPosition().y+70-window.getSize().y);
                if(bg2.getPosition().y>0)
                    bg1.setPosition(0.f,bg2.getPosition().y+70-window.getSize().y);

                window.clear();
                window.draw(bg1);
                window.draw(bg2);
                window.draw(player.shape);

                for (size_t i = 0; i < player.bullets.size(); i++)
                    window.draw(player.bullets[i].shape);

                for (size_t i = 0; i < enemies.size(); i++)
                    window.draw(enemies[i].shape);

                window.draw(bar);
                window.draw(scoretxt);
                window.draw(lifetxt);
                window.draw(mgzntxt);
                window.draw(magazine);
                window.draw(health);

                if(blll)
                    {
                        agun.restart();
                        blll=false;
                    }
                    aguntime=agun.getElapsedTime().asSeconds();

                if(agunbool)
                {
                    if(aguntime <0.15)
                    {
                        Step1.setPosition(player.shape.getPosition().x,player.shape.getPosition().y+20);
                        window.draw(Step1);
                    }
                    if(aguntime > 0.15 &&  aguntime <= 0.3)
                    {
                        Step2.setPosition(player.shape.getPosition().x,player.shape.getPosition().y+20);
                        window.draw(Step2);
                    }
                    if(aguntime > 0.3 &&  aguntime <= 0.45)
                    {
                        Step3.setPosition(player.shape.getPosition().x,player.shape.getPosition().y+20);
                        window.draw(Step3);
                    }
                    if(aguntime > 0.45 && aguntime <= 0.6)
                    {
                        Step4.setPosition(player.shape.getPosition().x,player.shape.getPosition().y+20);
                        window.draw(Step4);
                    }
                    if(aguntime > 0.6)
                        agunbool=false;
                }
                if(life<0)
                    window.draw(gameovertxt);
                window.display();
            }

            ///stage 2

            else if(score >50 && score <100)
            {

            }

            ///stage 3

            else
            {

            }

        }
    }
    return 0;
}


