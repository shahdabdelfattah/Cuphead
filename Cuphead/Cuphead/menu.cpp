#include "menu.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

menu::menu(float width, float height) {
    font.loadFromFile("fonts/MainMenu/Cat_Comic.otf");
    //Main Menu
    mainmenu[0].setFont(font);
    mainmenu[0].setFillColor(Color::White);
    mainmenu[0].setString("START");
    mainmenu[0].setCharacterSize(50);
    mainmenu[0].setPosition((width / 2) - 150, (height / 2) - 100);

    mainmenu[1].setFont(font);
    mainmenu[1].setFillColor(Color{ 128,128,128 });
    mainmenu[1].setString("OPTIONS");
    mainmenu[1].setCharacterSize(50);
    mainmenu[1].setPosition((width / 2) - 180, (height / 2) - 30);

    mainmenu[2].setFont(font);
    mainmenu[2].setFillColor(Color{ 128,128,128 });
    mainmenu[2].setString("EXIT");
    mainmenu[2].setCharacterSize(50);
    mainmenu[2].setPosition((width / 2) - 145, (height / 2) + 33);

    //Options
    options[0].setFont(font);
    options[0].setFillColor(Color::White);
    options[0].setString("MASTER VOLUME: ----------");
    options[0].setCharacterSize(50);
    options[0].setPosition((width / 2) - 320, (height / 2) - 100);

    options[1].setFont(font);
    options[1].setFillColor(Color{ 128,128,128 });
    options[1].setString("SFX VOLUME: ----------");
    options[1].setCharacterSize(50);
    options[1].setPosition((width / 2) - 320, (height / 2) - 30);

    options[2].setFont(font);
    options[2].setFillColor(Color{ 128,128,128 });
    options[2].setString("MUSIC VOLUME: ----------");
    options[2].setCharacterSize(50);
    options[2].setPosition((width / 2) - 320, (height / 2) + 33);

    //Death Menu
    deathMenu[0].setFont(font);
    deathMenu[0].setFillColor(Color::Red);
    deathMenu[0].setString("RETRY");
    deathMenu[0].setCharacterSize(50);
    deathMenu[0].setPosition((width / 2) - 320, (height / 2) - 100);

    deathMenu[1].setFont(font);
    deathMenu[1].setFillColor(Color::Black);
    deathMenu[1].setString("EXIT TO MAP");
    deathMenu[1].setCharacterSize(50);
    deathMenu[1].setPosition((width / 2) - 320, (height / 2) - 30);

    deathMenu[2].setFont(font);
    deathMenu[2].setFillColor(Color::Black);
    deathMenu[2].setString("QUIT GAME");
    deathMenu[2].setCharacterSize(50);
    deathMenu[2].setPosition((width / 2) - 320, (height / 2) + 33);

    selectedOp = 0;
    selected = 0;
    selectedDm = 0;
}

menu::~menu() {}

//Main Menu
void menu::setSelected(int n) {
    selected = n;
}

void  menu::draw(RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(mainmenu[i]);
    }
}

void menu::MoveDown() {
    if (selected + 1 <= 3) //not exit
    {
        mainmenu[selected].setFillColor(Color{ 128,128,128 });
        selected++;
        if (selected == 3) {
            selected = 0;
        }
        mainmenu[selected].setFillColor(Color::White);

    }
}

void menu::MoveUp() {
    if (selected - 1 >= -1) //not play
    {
        mainmenu[selected].setFillColor(Color{ 128,128,128 });
        selected--;
        if (selected == -1) {
            selected = 2;
        }
        mainmenu[selected].setFillColor(Color::White);

    }
}


//Options
void menu::drawOptions(RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(options[i]);
    }
}

void menu::MoveDownOp() {
    if (selectedOp + 1 <= 3)
    {
        options[selectedOp].setFillColor(Color{ 128,128,128 });
        selectedOp++;
        if (selectedOp == 3) {
            selectedOp = 0;
        }
        options[selectedOp].setFillColor(Color::White);
    }
}

void menu::MoveUpOp() {
    if (selectedOp - 1 >= -1)
    {
        options[selectedOp].setFillColor(Color{ 128,128,128 });
        selectedOp--;
        if (selectedOp == -1) {
            selectedOp = 2;
        }
        options[selectedOp].setFillColor(Color::White);
    }
}

void menu::setSelectedOp(int n) {
    selectedOp = n;
}

//Death Menu

void menu::setSelectedDm(int n) {
    selectedDm = n;
}

void  menu::drawDm(RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        window.draw(deathMenu[i]);
    }
}

void menu::MoveDownDm() {
    if (selectedDm + 1 <= 3)
    {
        deathMenu[selectedDm].setFillColor(Color::Black);
        selectedDm++;
        if (selectedDm == 3) {
            selectedDm = 0;
        }
        deathMenu[selectedDm].setFillColor(Color::Red);

    }
}

void menu::MoveUpDm() {
    if (selectedDm - 1 >= -1)
    {
        deathMenu[selectedDm].setFillColor(Color::Black);
        selectedDm--;
        if (selectedDm == -1) {
            selectedDm = 2;
        }
        deathMenu[selectedDm].setFillColor(Color::Red);

    }
}

