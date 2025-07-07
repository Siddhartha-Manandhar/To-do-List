#include<graphics.h>
#include"Backend.h"
class Frontend_Manager{
    public:
    void LoginMenu(){
        setbkcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(200, 200, 1000, 600);
        setfillstyle(SOLID_FILL, WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 1);
        setcolor(WHITE);
        outtextxy(410, 260, "User Name:");
        bar(400, 280, 800, 320);
        outtextxy(410, 360, "Password:");
        bar(400, 380, 800, 420);
        outtextxy(410, 460, "Login");
        outtextxy(410, 540, "Register");
    }
};

int main(){
    Frontend_Manager fm;
    initwindow(1200, 800, "Menu");
    setbkcolor(WHITE);
    cleardevice();

    fm.LoginMenu();

    getch();
    closegraph();
}