#include<graphics.h>
#include<iostream>
using namespace std;

int bkcolor = BLACK;
int txtcolor = WHITE;
int boxcolor = CYAN;

void Start(int midx, int midy);
void TaskMenu(int midx, int midy);

int main() {
    initwindow(1200, 800, "Menu");

    int height = getmaxy();
    int width = getmaxx();
    int midx = width / 2;
    int midy = height / 2;

    // Setting the Theme
    setbkcolor(bkcolor);
    cleardevice();
    settextstyle(4, 0, 2);
    setfillstyle(SOLID_FILL, boxcolor);
    setlinestyle(SOLID_LINE, 0, 5);
 
    Start(midx, midy);
    TaskMenu(midx, midy);
    getch();
    closegraph();
    return 0;
}

void Start(int midx, int midy){
        char x = 0;
       // Draw the filled rectangle (button background)
       bar(midx - 300, midy - 100, midx + 300, midy + 100);
       outtextxy(midx - 50, midy, "Start");
  
      //flickering outline
      while (true) {
  
          // Draw the outline
          setcolor(txtcolor);
          rectangle(midx - 300, midy - 100, midx + 300, midy + 100);
        //   delay(500); // Outline visible for 500ms
  
        //   // Clear the outline by drawing over it with white color
        //   setcolor(boxcolor);
        //   rectangle(midx - 300, midy - 100, midx + 300, midy + 100);
        //   delay(500); // Outline hidden for 500ms
  
          x = getch();
          if (x == 13) break;
      }
      

}

void TaskMenu(int midx, int midy){
    int y = 0;
    int prev_y = y;
    char x = 0;
    cleardevice();
    bar(midx - 250, midy - 300, midx + 250, midy -200);
    bar(midx - 250, midy - 150 , midx + 250, midy -50 );
    bar(midx - 250, midy , midx + 250, midy + 100);
    bar(midx - 250, midy + 150, midx + 250, midy + 250);

    setcolor(txtcolor);
    outtextxy(midx - 50, midy - 270, "To do list");
    outtextxy(midx - 50, midy - 120, "Tasks");
    outtextxy(midx - 50, midy + 30, "Settings");
    outtextxy(midx - 50, midy + 180, "Exit");

    //flickering outline
    while (true) {
        
        prev_y = y;

        // Draw the outline
        setcolor(txtcolor);
        rectangle(midx - 250, midy - 300 + (y * 150), midx + 250, midy -200 + (y * 150));
        
        x= getch();
        if(x == 80) y++;
        if(x == 72) y--;
        if(x == 13) break;

        if(y < 0){
            y = 0;
            continue;
        }
        if(y > 3){
            y = 3;
            continue;
        }
        setcolor(boxcolor);
        rectangle(midx - 250, midy - 300 + (prev_y * 150), midx + 250, midy -200 + (prev_y* 150));
    }
    

}