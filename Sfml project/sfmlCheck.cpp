#include<SFML/Graphics.hpp>
using namespace sf;

int main() {
    RenderWindow baal(VideoMode(600,600), "Bala");
    CircleShape golBaal(100.0f);
    golBaal.setFillColor(Color::Red);
    while(baal.isOpen()){
        Event ev;
        while(baal.pollEvent(ev)){
            if(ev.type==Event::Closed) baal.close();
        }
        baal.clear();
        baal.draw(golBaal);
        baal.display();
    }
    return 0;
}
