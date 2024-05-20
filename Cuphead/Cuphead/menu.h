#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class menu
{
public:
    Text mainmenu[3];
    Text options[3];
    Text deathMenu[3];
    int volumeLevel[3] = { 10,10,10 }; //default volume levels

    menu(float width, float height); // Constructor for main menu
    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    void setSelected(int n);
    int pressed() {
        return selected;
    }

    // Functions for options menu
    void drawOptions(RenderWindow& window);
    void MoveUpOp();
    void MoveDownOp();
    void setSelectedOp(int n);
    int isPressed() {
        return selectedOp;
    }

    //functions for death menu
    void drawDm(RenderWindow& window);
    void MoveUpDm();
    void MoveDownDm();
    void setSelectedDm(int n);
    int pressedDm() {
        return selectedDm;
    }

    ~menu(); // Destructor

private:
    int selected;
    int selectedOp;
    int selectedDm;
    Font font;
};