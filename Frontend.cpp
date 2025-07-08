#include<graphics.h>
#include"Backend.h"
class Frontend_Manager{
    string user_name;
    public:
    void LoginMenu(){
        Login_Mananger lm;

        settextstyle(SANS_SERIF_FONT, 0, 1);

        //Username and Password
        setbkcolor(LIGHTBLUE);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        bar(200, 200, 1000, 600);
        setfillstyle(SOLID_FILL, WHITE);
        setcolor(WHITE);
        outtextxy(410, 260, "User Name:");
        bar(400, 280, 800, 320);
        outtextxy(410, 360, "Password:");
        bar(400, 380, 800, 420);

        //Login and Register
        setbkcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        bar(400, 450, 480, 500);
        outtextxy(410, 460, "Login");
        bar(690, 450, 800, 500);
        outtextxy(710, 460, "Register");

        bool log = false;

        while(!log){
            if(leftclick(400, 450, 480, 500, RED)){
                lm.login_user();
                log = true;
                cout<<"Logged in\n";
            }
            if(leftclick(690, 450, 800, 500, RED)){
                lm.register_user();
                cout<<"Registered\n";
                setfillstyle(SOLID_FILL, WHITE);
                bar(400 + 2, 280 + 2, 800 - 2, 320 - 2);
                bar(400 + 2, 380 + 2, 800 - 2, 420 - 2);
            }
            if(leftclick(400, 280, 800, 320, WHITE)){
                user_name =getInput(400, 280, 800, 320, WHITE);
                lm.getUsername(user_name);
                cout<<user_name<<endl;
                
            }
            if(leftclick(400, 380, 800, 420, WHITE)){
                string password = getInput(400, 380, 800, 420, WHITE, true);
                lm.getPassword(password);
                cout<<password<<endl;
            }
            
        }
    }

    bool leftclick(int x1, int y1, int x2, int y2, int color){
        int mx, my;
        int selectcolor = WHITE;
        setlinestyle(SOLID_LINE, 0, 5);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            clearmouseclick(WM_LBUTTONDOWN);
        }
            if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2) {
                if (color == WHITE) selectcolor = BLACK;
                setcolor(selectcolor);
                rectangle(x1, y1, x2, y2);  
                mx = 0;
                my = 0;
                delay(100);
                setcolor(color);
                rectangle(x1, y1, x2, y2);
                return true;
            }

        
        return false;
    }

    string getInput(int x1, int y1, int x2, int y2, int color, bool hide = false, bool clock = false) {
        char ch;
        string inputString = "";
        setbkcolor(WHITE);
        if(!clock){settextstyle(SANS_SERIF_FONT, 0, 1);}
        else {settextstyle(10, HORIZ_DIR, 5);}
        
        while (true) {
            if (kbhit()) {
                ch = getch();
                if (ch == 13) { // Enter key
                    return inputString;
                } else if (ch == 8) { // Backspace
                    if (!inputString.empty()) {
                        inputString.pop_back();
                    }
                } else if (isprint(ch)) { // Printable characters
                    if (textwidth((char*)inputString.c_str()) + 10 < (x2 - x1)) { // Prevent overflow
                        inputString += ch;
                    }
                }

                // Clear the input area
                setfillstyle(SOLID_FILL, color);
                bar(x1 + 2, y1 + 2, x2 - 2, y2 - 2);

                // Render the string
                string displayString = inputString;
                if (hide) {
                    displayString = string(inputString.size(), '*');
                }
                setcolor(BLACK);
                outtextxy(x1 + 5, y1 + 5, (char*)displayString.c_str());
            }
        }
    }

    void displayMainMenu(){
        bool selected = false;
        int hours, minutes, seconds;

        cleardevice();
        DrawClock(0, 0, 0);
        //Start
        settextstyle(SANS_SERIF_FONT, 0, 2);
        setbkcolor(LIGHTGREEN);
        setfillstyle(SOLID_FILL, LIGHTGREEN);
        bar(560, 200, 640, 250);
        outtextxy(579, 214, "Start");

        //Manage Task
        settextstyle(SANS_SERIF_FONT, 0, 4);
        setcolor(WHITE);
        setbkcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(400, 300, 800, 380);
        outtextxy(480, 324, "Manage Task");

        //View Task
        settextstyle(SANS_SERIF_FONT, 0, 4);
        setcolor(WHITE);
        setbkcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(400, 400, 800, 480);
        outtextxy(480, 424, "View Task");

        //Search Task
        settextstyle(SANS_SERIF_FONT, 0, 4);
        setcolor(WHITE);
        setbkcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(400, 500, 800, 580);
        outtextxy(480, 524, "Search Task");

        //Show Statistics
        settextstyle(SANS_SERIF_FONT, 0, 4);
        setcolor(WHITE);
        setbkcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        bar(400, 600, 800, 680);
        outtextxy(480, 624, "Show Statistics");

        //Logout
        settextstyle(SANS_SERIF_FONT, 0, 2);
        setcolor(WHITE);
        setbkcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        bar(1100, 10, 1180, 40);
        outtextxy(1110, 12, "Logout");

        while(!selected){
            if(leftclick(500, 100, 900, 150, WHITE)){
                string line = getInput(500, 100, 900, 150, WHITE, false, true);
                stringstream ss(line);
                char sep;
                ss >> hours >> sep >> minutes >> sep >> seconds;
            }
            if(leftclick(560, 200, 640, 250, LIGHTGREEN)){
                Timer_Mananger timer(hours, minutes, seconds);
                timer.stopped = false;
                cout<<"Timer started\n";
                Timer(timer);
            }
        }
        

            
            
    }

    void Timer(Timer_Mananger timer){
        timer.isValid();
        
        while(timer.isTimeRemaining() || timer.stopped){
            drawTimeButtons(timer);
            if(!timer.paused){
                DrawClock(timer.hours, timer.minutes, timer.seconds);
                delay(1000);
                timer.decrementTime();
            }
        }
        DrawClock(0, 0, 0);
        timer.playAlarm();
    }

    void drawTimeButtons(Timer_Mananger &timer){
        settextstyle(SANS_SERIF_FONT, 0, 2);

                //Stop
                setbkcolor(RED);
                setfillstyle(SOLID_FILL, RED);
                bar(560, 200, 640, 250);
                outtextxy(579, 214, "Stop");

                //Pause
                setbkcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                bar(740, 200, 820, 250);
                outtextxy(755, 214, "Pause");

                //Resume
                setbkcolor(GREEN);
                setfillstyle(SOLID_FILL, GREEN);
                bar(380, 200, 460, 250);
                outtextxy(385, 214, "Resume");

                if(leftclick(560, 200, 640, 250, RED)){
                    timer.reset(0,0,0);
                    cout<<"Stopped"<<endl;
                    timer.stopped = true;
                }
                if(leftclick(740, 200, 820, 250, YELLOW)){
                    timer.paused = true;
                    cout<<"Paused"<<endl;
                }
                if(leftclick(380, 200, 460, 250, GREEN)){
                    timer.paused = false;
                    cout<<"Resumed"<<endl;
                }
    }
    void DrawClock(int h, int m, int s) {
        setbkcolor(WHITE); 
        setcolor(BLACK); 
        settextstyle(10, HORIZ_DIR, 5); 
        
        stringstream ss;
        ss << (h < 10 ? "0" : "") << h << ":" 
        << (m < 10 ? "0" : "") << m << ":" 
        << (s < 10 ? "0" : "") << s;

        string timeStr = ss.str(); 
        outtextxy(500, 100, (char*)timeStr.c_str()); 
    }

    void drawSearchIcon(int x, int y, int r) {
        setlinestyle(0, 0, 3);
        // Draw circle (lens)
        circle(x, y, r);
        // Draw handle
        line(x + r * 0.7, y + r * 0.7, x + r * 1.5, y + r * 1.5);
    }

    void searchTask(){
        cleardevice();

        setcolor(BLACK);
        rectangle(400, 10, 800, 50);

        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(280, 18, "Search Task:");

        // Draw search icon inside the rectangle
        setcolor(DARKGRAY);
        int iconX = 415;  // position inside the rectangle
        int iconY = 25;
        int iconR = 10;
        drawSearchIcon(iconX, iconY, iconR);

        settextstyle(SANS_SERIF_FONT, 0, 2);
        setfillstyle(SOLID_FILL, BLUE);
        setbkcolor(BLUE);
        setcolor(WHITE);
        bar(820, 13, 900, 47);
        outtextxy(830, 18, "Search");

        setfillstyle(SOLID_FILL, GREEN);
        setbkcolor(GREEN);
        bar(920, 13, 1000, 47);
        outtextxy(930, 18, "Filter");

        setfillstyle(SOLID_FILL, CYAN);
        setbkcolor(CYAN);
        bar(1020, 13, 1100, 47);
        outtextxy(1030, 18, "Sort");



        setfillstyle(SOLID_FILL, BLUE);
        setlinestyle(SANS_SERIF_FONT, 0, 2);
        setbkcolor(BLUE);

        int marginX = 50;
        int marginY = 100;
        int gapX = 50;
        int gapY = 50;

        int boxWidth = 500;     // fits 2 columns with 50 gap
        int boxHeight = 150;    // fits 3 rows with 20 gaps

        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 2; ++col) {
                int x1 = marginX + col * (boxWidth + gapX);
                int y1 = marginY + row * (boxHeight + gapY);
                int x2 = x1 + boxWidth;
                int y2 = y1 + boxHeight;

                bar(x1, y1, x2, y2);
                outtextxy(x1 + 5, y1 + 5, "ID: ");
                outtextxy(x1 + 5, y1 + 40, "Title: ");
                outtextxy(x1 + 5, y1 + 75, "Due Date: ");
                outtextxy(x1 + 250, y1 + 5, "Priority: ");
                outtextxy(x1 + 250, y1 + 40, "Status: ");
            }
        }

    }

    void showStatistics(){
        cleardevice();

        int taskno = 10;

        settextstyle(GOTHIC_FONT, 0, 5);
        setcolor(BLACK);
        outtextxy(460, 10, "Statistics:");
        //Task Status
        settextstyle(GOTHIC_FONT, 0, 2);
        outtextxy(20, 120, "Task Status:");

        setfillstyle(SOLID_FILL, BLUE);
        bar(200, 100, 500, 160);
        outtextxy(220, 170, "Pending: 5");

        setfillstyle(SOLID_FILL, GREEN);
        bar(500, 100, 800, 160);
        outtextxy(520, 170, "Completed: 5");

        setfillstyle(SOLID_FILL, LIGHTRED);
        bar(800, 100, 1100, 160);
        outtextxy(820, 170, "Overdue: 5");


        //Priority
        settextstyle(GOTHIC_FONT, 0, 2);
        outtextxy(20, 220, "Priority:");

        setfillstyle(SOLID_FILL, BLUE);
        bar(200, 200, 400, 260);
        outtextxy(220, 270, "Low: 3");

        setfillstyle(SOLID_FILL, GREEN);
        bar(400, 200, 900, 260);
        outtextxy(520, 270, "Medium: 5");

        setfillstyle(SOLID_FILL, LIGHTRED);
        bar(900, 200, 1100, 260);
        outtextxy(820, 270, "High: 4");

        setfillstyle(SOLID_FILL, GREEN);
        pieslice(300, 450, 90, 20, 100);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        pieslice(300, 450, 20, 90, 100);
        setfillstyle(SOLID_FILL, WHITE);
        pieslice(300, 450, 0, 180, 80);
        pieslice(300, 450, 180, 360, 80);

        outtextxy(200, 560, "Completed: 80%");
        settextstyle(GOTHIC_FONT, 0, 4);
        outtextxy(260, 430, "80%");

        //Longest Overdue Task
        settextstyle(GOTHIC_FONT, 0, 3);
        outtextxy(500, 400, "Longest Overdue Task: Driving Lessons");
        outtextxy(500, 460, "Overdue Time: 10 days");

        //Next pending Task
        settextstyle(GOTHIC_FONT, 0, 3);
        outtextxy(500, 560, "Next pending Task: Study");
        outtextxy(500, 620, "Due Date: 10/10/2023");

    }

        string getUsername(string user_name){
            return user_name;
        }
        
        
    };

int main(){
    Frontend_Manager fm;
    initwindow(1200, 800, "Menu");
    setbkcolor(WHITE);
    cleardevice();
     //fm.LoginMenu();
     //fm.displayMainMenu();
    //fm.searchTask();
    fm.showStatistics();

    getch();
    closegraph();
}