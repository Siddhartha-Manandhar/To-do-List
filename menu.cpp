#include<graphics.h>
#include<iostream>
using namespace std;

int LightBlue = RGB(173, 216, 230);
int NavyBlue = RGB(0, 0, 128);
int Cyan = RGB(0, 255, 255);

int bkcolor = LightBlue; //Background color
int txtcolor = WHITE; //Text color and Line color
int boxcolor = NavyBlue; //Box color
int highlight = Cyan;

bool Back = false;

void Start(int midx, int midy);
int TaskMenu(int midx, int midy);
void Todolist(int midx);
void Tasks(int midx);
void Settings();

int main() {
    initwindow(1200, 800, "Menu");

    int height = getmaxy();
    int width = getmaxx();
    int midx = width / 2;
    int midy = height / 2;

    int x;

    // Setting the Theme
    setbkcolor(bkcolor);
    cleardevice();
    settextstyle(4, 0, 2);
    setfillstyle(SOLID_FILL, boxcolor);
    setlinestyle(SOLID_LINE, 0, 5);
 
    Start(midx, midy); //First Menu
    label1:
    x = TaskMenu(midx, midy); //Second Menu
    Back = false;

    switch(x){
        case 0:
            Todolist(midx);
            if(Back) goto label1;
            break;
        case 1:
            Tasks(midx);  
            if(Back) goto label1;  
            break;
        case 2:
            Settings();
            if(Back) goto label1;
            break;
        case 3:
            exit(0);
            break;
    }

    getch();
    closegraph();
    return 0;
}

void Start(int midx, int midy){
    setbkcolor(boxcolor);
        char x = 0;
       // Draw the filled rectangle (button background)
       bar(midx - 300, midy - 100, midx + 300, midy + 100);
       outtextxy(midx - 50, midy, "Start");
  
      //flickering outline
      while (true) {
  
          // Draw the outline
          setcolor(txtcolor);
          rectangle(midx - 300, midy - 100, midx + 300, midy + 100);
  
          x = getch(); //Input from keyboard
          setbkcolor(bkcolor);
          if (x == 13) break; // Press enter to exit
      }
      

}

int TaskMenu(int midx, int midy){
    int y = 0;
    int prev_y = y;
    char x = 0;
    cleardevice();
    setcolor(txtcolor);

    //flickering outline
    while (true) {
        
        char* menuItems[] = {"To do list", "Tasks", "Settings", "Exit"};
        int menuOffsets[] = {-300, -150, 0, 150}; // Y-axis offsets for menu items
        
        for (int i = 0; i < 4; i++) {
            int color = (y == i) ? highlight : boxcolor;
            
            setfillstyle(SOLID_FILL, color);
            setbkcolor(color);
            
            int top = midy + menuOffsets[i];
            int bottom = top + 100;
            
            bar(midx - 250, top, midx + 250, bottom);
            outtextxy(midx - 50, top + 30, menuItems[i]);
        }
        
        x= getch(); //Input from keyboard
        if(x == 80) y++; //Down
        if(x == 72) y--; //Up
       
        //Boundary
        if(y < 0){
            y = 0;
            continue;
        }
        if(y > 3){
            y = 3;
            continue;
        }
        setbkcolor(bkcolor);
        if(x == 13) return y;
         
    }
    
}

void Todolist( int midx){
    char x;
    cleardevice();
    setcolor(txtcolor);
    setbkcolor(boxcolor);
    int n = 5;
    string List[n] = {"Task 1", "Task 2", "Task 3", "Task 4", "Task 5"};
    for(int i = 0; i < n; i++){
        bar(midx - 300, 100 + (i * 100), midx + 300, 160 + (i * 100));
        outtextxy(midx - strlen(List[i].c_str()) -30, 110 + (i * 100), (char *)List[i].c_str());
    }
    setbkcolor(bkcolor);
    outtextxy(100, 700, "Press backspace to go back");
    x = getch();
    
    if(x == '\b') Back = true;
}

void Tasks(int midx){
    cleardevice();
    setcolor(txtcolor);
    setbkcolor(boxcolor);

    char x;

    int n = 5;
    string List[n] = {"Task 1", "Task 2", "Task 3", "Task 4", "Task 5"};
    for(int i = 0; i < n; i++){
        bar(midx - 300, 100 + (i * 100), midx + 300, 160 + (i * 100));
        outtextxy(midx - strlen(List[i].c_str()) -30, 110 + (i * 100), (char *)List[i].c_str());
    }

    setbkcolor(bkcolor);
    outtextxy(100, 700, "Press enter to go back");

    x = getch();
    if(x == '\b') Back = true;
}

void Settings(){
    char x;
    cleardevice();
    setcolor(txtcolor);
    outtextxy(100, 100, "Settings");
    outtextxy(100, 500, "Press enter to go back");   
    if(x == '\b') Back = true; 
}