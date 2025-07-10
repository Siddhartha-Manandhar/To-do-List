#include<graphics.h>
#include<string.h>
#include"Backend.h"

vector<Task> Task_Mananger::tasklist;


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
                user_name = lm.login_user();
                if(user_name != ""){
                    log = true;
                    Task_Mananger tm;
                    File_Manager fm;
                    tm.tasklist = fm.loadTasks(user_name);
                    cout<<"Logged in\n";
                    displayMainMenu();
                }
                else{
                    settextstyle(SANS_SERIF_FONT, 0, 1);
                    setcolor(RED);
                    outtextxy(400, 500, "Invalid Username or Password");
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(400 + 2, 280 + 2, 800 - 2, 320 - 2);
                    bar(400 + 2, 380 + 2, 800 - 2, 420 - 2);
                }

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
    
        setbkcolor(WHITE);
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
            if(leftclick(400, 300, 800, 380, BLUE)){
                managetask();
            }    
            if(leftclick(400, 400, 800, 480, BLUE)){
                viewTask();
            }    
            if(leftclick(400, 500, 800, 580, BLUE)){
                searchTask();
            }    
            if(leftclick(400, 600, 800, 680, BLUE)){
                showStatistics();
            } 
            if(leftclick(1100, 10, 1180, 40, RED)){
                File_Manager fm;
                fm.saveTasks(Task_Mananger::tasklist, user_name);
            }
            
        }
               
    }

    void Timer(Timer_Mananger timer){
        bool alarm = false;
        timer.isValid();
        
        while(timer.isTimeRemaining() && !timer.stopped){
            drawTimeButtons(timer);
            if(!timer.paused){
                DrawClock(timer.hours, timer.minutes, timer.seconds);
                delay(1000);
                timer.decrementTime();
            }
        }
        DrawClock(0, 0, 0);
        timer.playAlarm();
        alarm = true;

        setfillstyle(SOLID_FILL, WHITE);
        bar(380, 200, 460, 250);
        bar(740, 200, 820, 250);
        bar(380, 200, 820, 250);

        settextstyle(SANS_SERIF_FONT, 0, 2);
        setbkcolor(CYAN);
        setfillstyle(SOLID_FILL, CYAN);
        bar(560, 200, 640, 250);
        outtextxy(579, 214, "Slience");

        int waitTime = 0;
        while(alarm && waitTime < 10000){ // wait max 10 sec
            if(leftclick(560, 200, 640, 250, CYAN)){
                PlaySound(NULL, 0, 0);
                alarm = false;
            }
            delay(100); // prevent CPU overload
            waitTime += 100;
        }

        displayMainMenu();
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

    void searchTask() {
    setbkcolor(WHITE);
    cleardevice();

    const int tasksPerPage = 6;
    int pageNumber = 0;
    string searchTerm = "";
    vector<Task> filteredTasks = Task_Mananger::tasklist;
    int totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;

    while (true) {
        setbkcolor(WHITE);
        cleardevice();

        bool filter = false;
        bool sort = false;

        // Back Arrow

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        int arrowPoints[] = {
            80, 40,   // Point 1 (top-right)
            40, 60,   // Point 2 (tip of arrow)
            80, 80,   // Point 3 (bottom-right)
            80, 40    // Closing back to Point 1
        };
        fillpoly(4, arrowPoints);

        // Label "Back"
        setcolor(BLACK);
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(90, 52, "Back");

        //  UI: Search box
        setcolor(BLACK);
        rectangle(400, 10, 800, 50);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(280, 18, "Search Task:");

        // Search icon
        setcolor(DARKGRAY);
        drawSearchIcon(415, 25, 10);

        // Buttons
        settextstyle(SANS_SERIF_FONT, 0, 2);
        setfillstyle(SOLID_FILL, BLUE); setbkcolor(BLUE);
        bar(820, 13, 900, 47); outtextxy(830, 18, "Search");

        setfillstyle(SOLID_FILL, GREEN); setbkcolor(GREEN);
        bar(920, 13, 1000, 47); outtextxy(930, 18, "Filter");

        setfillstyle(SOLID_FILL, CYAN); setbkcolor(CYAN);
        bar(1020, 13, 1100, 47); outtextxy(1030, 18, "Sort");

        //  Display Task Grid
        int marginX = 50;
        int marginY = 100;  // space left for filter/sort later
        int gapX = 50, gapY = 50;
        int boxWidth = 500, boxHeight = 150;

        int startIndex = pageNumber * tasksPerPage;
        int endIndex = min(startIndex + tasksPerPage, (int)filteredTasks.size());

        setcolor(WHITE);
        for (int i = startIndex; i < endIndex; ++i) {
            int relIndex = i - startIndex;
            int row = relIndex / 2;
            int col = relIndex % 2;

            int x1 = marginX + col * (boxWidth + gapX);
            int y1 = marginY + row * (boxHeight + gapY);
            int x2 = x1 + boxWidth;
            int y2 = y1 + boxHeight;

            setfillstyle(SOLID_FILL, BLUE);
            bar(x1, y1, x2, y2);

            Task t = filteredTasks[i];
            string id = "ID: " + to_string(t.getId());
            string title = "Title: " + t.getTitle();
            string due = "Due Date: " + t.getDuedate().toString();
            const char* priorities[] = {"Low", "Medium", "High"};
            const char* statuses[] = {"Pending", "Completed", "Overdue"};
            string priority = "Priority: " + string(priorities[t.getPriority()]);
            string status = "Status: " + string(statuses[t.getStatus()]);

            setbkcolor(BLUE);
            outtextxy(x1 + 5, y1 + 5, (char*)id.c_str());
            outtextxy(x1 + 5, y1 + 40, (char*)title.c_str());
            outtextxy(x1 + 5, y1 + 75, (char*)due.c_str());
            outtextxy(x1 + 250, y1 + 5, (char*)priority.c_str());
            outtextxy(x1 + 250, y1 + 40, (char*)status.c_str());
        }

        //  Page Indicator
        string pageInfo = "Page " + to_string(pageNumber + 1) + " of " + to_string(totalPages);
        setcolor(BLACK);
        settextstyle(SANS_SERIF_FONT, 0, 1);
        setbkcolor(WHITE);
        outtextxy(550, 700, (char*)pageInfo.c_str());

        //  Page Controls
        setfillstyle(SOLID_FILL, RED);
        bar(100, 700, 200, 740); setbkcolor(RED); setcolor(WHITE);
        outtextxy(120, 710, "Prev");

        setfillstyle(SOLID_FILL, GREEN);
        bar(1000, 700, 1100, 740); setbkcolor(GREEN); setcolor(WHITE);
        outtextxy(1020, 710, "Next");

        //  Handle clicks
        while (true) {
            
            if (leftclick(400, 10, 800, 50, WHITE)) {
                searchTerm = getInput(430, 11, 795, 49, WHITE);
            }

            if (leftclick(820, 13, 900, 47, BLUE)) {
                // Filter by searchTerm
                filteredTasks.clear();
                for (Task& t : Task_Mananger::tasklist) {
                    if (toLower(t.getTitle()).find(toLower(searchTerm)) != string::npos)
                        filteredTasks.push_back(t);
                }
                pageNumber = 0;
                totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                break;
            }

            if (leftclick(100, 700, 200, 740, RED)) {
                if (pageNumber > 0) pageNumber--;
                break;
            }

            if (leftclick(1000, 700, 1100, 740, GREEN)) {
                if (pageNumber < totalPages - 1) pageNumber++;
                break;
            }

            if(leftclick(920, 13, 1000, 47, BLUE)) {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                settextstyle(SANS_SERIF_FONT, 0, 1);
                setbkcolor(LIGHTBLUE);
                bar(920, 47, 1000, 81); outtextxy(925, 48, "Pending");
                bar(920, 81, 1000, 115); outtextxy(925, 82, "Completed");
                bar(920, 115, 1000, 149); outtextxy(925, 116, "Overdue");
                bar(920, 149, 1000, 183); outtextxy(925, 150, "Low");
                bar(920, 183, 1000, 217); outtextxy(925, 184, "Medium");
                bar(920, 217, 1000, 251); outtextxy(925, 218, "High");
                filter = true;
            }
            if(leftclick(1020, 13, 1100, 47, BLUE)) {
                setfillstyle(SOLID_FILL, CYAN);
                settextstyle(SANS_SERIF_FONT, 0, 1);
                setbkcolor(CYAN);
                bar(1020, 47,  1100, 81); outtextxy (1020, 48, "Date");
                bar(1020, 81,  1100, 115); outtextxy(1020, 82, "Priority");
                bar(1020, 115, 1100, 149); outtextxy(1020, 116, "Status");
                bar(1020, 149, 1100, 183); outtextxy(1020, 150, "ID");

                sort = true;
            }
            if(filter){
                if(leftclick(920, 13, 1000, 47, BLUE)){
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(920, 47, 1000, 251);
                    filter = false;
                }
                if(leftclick(920, 47, 1000, 81, LIGHTBLUE)) {
                    filteredTasks.clear();
                    for (Task& t : Task_Mananger::tasklist) {
                        if (t.getStatus() == 0)
                            filteredTasks.push_back(t);
                    }
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(920, 81, 1000, 115, LIGHTBLUE)) {
                    filteredTasks.clear();
                    for (Task& t : Task_Mananger::tasklist) {
                        if (t.getStatus() == 1)
                            filteredTasks.push_back(t);
                    }
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(920, 115, 1000, 149, LIGHTBLUE)) {
                    filteredTasks.clear();
                    for (Task& t : Task_Mananger::tasklist) {
                        if (t.getStatus() == 2)
                            filteredTasks.push_back(t);
                    }
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(920, 149, 1000, 183, LIGHTBLUE)) {
                    filteredTasks.clear();
                    for (Task& t : Task_Mananger::tasklist) {
                        if (t.getPriority() == 0)
                            filteredTasks.push_back(t);
                    }
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(920, 183, 1000, 217, LIGHTBLUE)) {
                    filteredTasks.clear();
                    for (Task& t : Task_Mananger::tasklist) {
                        if (t.getPriority() == 1)
                            filteredTasks.push_back(t);
                    }
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(920, 217, 1000, 251, LIGHTBLUE)) {
                    filteredTasks.clear();
                    for (Task& t : Task_Mananger::tasklist) {
                        if (t.getPriority() == 2)
                            filteredTasks.push_back(t);
                    }
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }

            }
            if(sort){
                if(leftclick(1020, 13, 1100, 47, BLUE)){
                    setfillstyle(SOLID_FILL, WHITE);
                    bar(1020, 47, 1100, 183);
                    sort = false;
                }
                if(leftclick(1020, 47, 1100, 81, LIGHTBLUE)){
                    sort = false;
                    filteredTasks.clear();
                    filteredTasks = Task_Mananger::sortTask(1);
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(1020, 81, 1100, 115, LIGHTBLUE)){
                    sort = false;
                    filteredTasks.clear();
                    filteredTasks = Task_Mananger::sortTask(2);
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(1020, 115, 1100, 149, LIGHTBLUE)){
                    sort = false;
                    filteredTasks.clear();
                    filteredTasks = Task_Mananger::sortTask(3);
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
                if(leftclick(1020, 149, 1100, 183, LIGHTBLUE)){
                    sort = false;
                    filteredTasks.clear();
                    filteredTasks = Task_Mananger::sortTask(4);
                    pageNumber = 0;
                    totalPages = (filteredTasks.size() + tasksPerPage - 1) / tasksPerPage;
                    break;
                }
            }
            // Back arrow
            if (leftclick(40, 40, 110, 80, RED)) {
                displayMainMenu();
            }
        }
    }
}


    void showStatistics() {
    setbkcolor(WHITE);
    cleardevice();

    vector<Task>& tasks = Task_Mananger::tasklist;
    int total_tasks = tasks.size();

    int pending = 0, completed = 0, overdue = 0;
    int low = 0, medium = 0, high = 0;

    string longest_overdue_title = "None";
    int longest_overdue_days = 0;

    string next_pending_title = "None";
    Date next_pending_date;
    bool has_pending = false;

    Date today;
    // Back Arrow

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        int arrowPoints[] = {
            80, 40,   // Point 1 (top-right)
            40, 60,   // Point 2 (tip of arrow)
            80, 80,   // Point 3 (bottom-right)
            80, 40    // Closing back to Point 1
        };
        fillpoly(4, arrowPoints);

        // Label "Back"
        setcolor(BLACK);
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(90, 52, "Back");

    for (Task& t : tasks) {
        // Status count
        if (t.getStatus() == Pending) pending++;
        else if (t.getStatus() == Completed) completed++;
        else overdue++;

        // Priority count
        if (t.getPriority() == Low) low++;
        else if (t.getPriority() == Medium) medium++;
        else high++;

        // Longest overdue
        if (t.getStatus() == Overdue) {
            int overdue_days = t.getDuedate().daysBetween(today);
            if (overdue_days > longest_overdue_days) {
                longest_overdue_days = overdue_days;
                longest_overdue_title = t.getTitle();
            }
        }

        // Nearest pending task
        if (t.getStatus() == Pending) {
            if (!has_pending || t.getDuedate() < next_pending_date) {
                next_pending_date = t.getDuedate();
                next_pending_title = t.getTitle();
                has_pending = true;
            }
        }
        
    }

    float completion_rate = total_tasks ? (completed * 100.0f / total_tasks) : 0;

    //Display Section

    settextstyle(GOTHIC_FONT, 0, 5);
    setcolor(BLACK);
    outtextxy(460, 10, "Statistics:");

    // Task Status
    settextstyle(GOTHIC_FONT, 0, 2);
    outtextxy(20, 120, "Task Status:");

    int barx1 = (900 / Task_Mananger::tasklist.size()) * pending;

    setfillstyle(SOLID_FILL, BLUE);
    bar(200, 100, 200 + barx1, 160);
    string txt = "Pending: " + to_string(pending);
    outtextxy(220, 170, (char*)txt.c_str());

    setfillstyle(SOLID_FILL, GREEN);
    int barx2 = (900 / Task_Mananger::tasklist.size()) * completed;
    bar(200 + barx1, 100, 200 + barx1 + barx2, 160);
    txt = "Completed: " + to_string(completed);
    outtextxy(520, 170, (char*)txt.c_str());

    setfillstyle(SOLID_FILL, LIGHTRED);
    int barx3 = (900 / Task_Mananger::tasklist.size()) * overdue;
    bar(200 + barx1 + barx2, 100, 200 + barx1 + barx2 + barx3, 160);
    txt = "Overdue: " + to_string(overdue);
    outtextxy(820, 170, (char*)txt.c_str());

    // Priority
    settextstyle(GOTHIC_FONT, 0, 2);
    outtextxy(20, 220, "Priority:");

    setfillstyle(SOLID_FILL, BLUE);
    barx1 = (900 / Task_Mananger::tasklist.size()) * low;
    bar(200, 200, 200 + barx1, 260);
    txt = "Low: " + to_string(low);
    outtextxy(220, 270, (char*)txt.c_str());

    setfillstyle(SOLID_FILL, GREEN);
    barx2 = (900 / Task_Mananger::tasklist.size()) * medium;
    bar(200 + barx1, 200, 200 + barx1 + barx2, 260);
    txt = "Medium: " + to_string(medium);
    outtextxy(420, 270, (char*)txt.c_str());

    setfillstyle(SOLID_FILL, LIGHTRED);
    barx3 = (900 / Task_Mananger::tasklist.size()) * high;
    bar(200 + barx1 + barx2, 200, 200 + barx1 + barx2 + barx3, 260);
    txt = "High: " + to_string(high);
    outtextxy(920, 270, (char*)txt.c_str());

    // Completion Pie
    setfillstyle(SOLID_FILL, GREEN);
    pieslice(300, 450, 0, (int)(completion_rate * 3.6), 100);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    pieslice(300, 450, (int)(completion_rate * 3.6), 360, 100);
    setfillstyle(SOLID_FILL, WHITE);
    pieslice(300, 450, 0, 360, 80);
    settextstyle(GOTHIC_FONT, 0, 4);
    setcolor(BLACK);
    txt = to_string((int)completion_rate) + "%";
    outtextxy(260, 430, (char*)txt.c_str());

    settextstyle(GOTHIC_FONT, 0, 2);
    txt = "Completed: " + to_string((int)completion_rate) + "%";
    outtextxy(200, 560, (char*)txt.c_str());

    // Longest Overdue Task
    settextstyle(GOTHIC_FONT, 0, 3);
    txt = "Longest Overdue Task: " + longest_overdue_title;
    outtextxy(500, 400, (char*)txt.c_str());
    txt = "Overdue Time: " + to_string(longest_overdue_days) + " days";
    outtextxy(500, 460, (char*)txt.c_str());

    // Next pending Task
    txt = "Next pending Task: " + next_pending_title;
    outtextxy(500, 560, (char*)txt.c_str());

    txt = "Due Date: " + next_pending_date.toString();
    if (has_pending)
        outtextxy(500, 620, (char*)txt.c_str());
    else
        outtextxy(500, 620, "Due Date: None");

        while(true){
            if (leftclick(40, 40, 110, 80, RED)) {
                displayMainMenu();
                break;
            }
        }
}


    void managetask(){
        setbkcolor(WHITE);
        cleardevice();

        // Title
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        setcolor(BLUE);
        outtextxy(420, 150, "Manage Tasks");

        // Delete Task Button
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(405, 305, 805, 385);  // Shadow
        setfillstyle(SOLID_FILL, GREEN);
        bar(400, 300, 800, 380);
        setcolor(WHITE);
        setbkcolor(GREEN);
        settextstyle(SANS_SERIF_FONT, 0, 4);
        outtextxy(500, 324, "Add Task");

        // Edit Task Button
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(405, 405, 805, 485);  // Shadow
        setfillstyle(SOLID_FILL, MAGENTA);
        bar(400, 400, 800, 480);
        setcolor(WHITE);
        setbkcolor(MAGENTA);
        settextstyle(SANS_SERIF_FONT, 0, 4);
        outtextxy(510, 424, "Edit Task");

        // Add Task Button
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(405, 505, 805, 585);  // Shadow
        setfillstyle(SOLID_FILL, RED);
        bar(400, 500, 800, 580);
        setcolor(WHITE);
        setbkcolor(RED);
        settextstyle(SANS_SERIF_FONT, 0, 4);
        outtextxy(510, 524, "Delete Task");

        // Instruction
        settextstyle(SANS_SERIF_FONT, 0, 1);
        setbkcolor(WHITE);
        setcolor(DARKGRAY);
        outtextxy(450, 650, "Click on a button to continue.");
        // Back Arrow

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        int arrowPoints[] = {
            80, 40,   // Point 1 (top-right)
            40, 60,   // Point 2 (tip of arrow)
            80, 80,   // Point 3 (bottom-right)
            80, 40    // Closing back to Point 1
        };
        fillpoly(4, arrowPoints);

        // Label "Back"
        setcolor(BLACK);
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(90, 52, "Back");

        while(true){
            if(leftclick(400, 300, 800, 380,GREEN)){ // Delete Task Button
                addTaskForm();
            }
            else if(leftclick(400, 400, 800, 480, MAGENTA)){ // Edit Task Button
                editTask();
            }
            else if(leftclick(400, 500, 800, 580, RED)){ // Add Task Button
                deleteTaskForm();
            }
             // Back arrow
            if (leftclick(40, 40, 110, 80, RED)) {
                displayMainMenu();
            }
        }
        
    }

    void addTaskForm() {
        cleardevice();

        setbkcolor(WHITE);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, WHITE);
        bar(0, 0, getmaxx(), getmaxy());

        // Back Arrow

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        int arrowPoints[] = {
            80, 40,   // Point 1 (top-right)
            40, 60,   // Point 2 (tip of arrow)
            80, 80,   // Point 3 (bottom-right)
            80, 40    // Closing back to Point 1
        };
        fillpoly(4, arrowPoints);

        // Label "Back"
        setcolor(BLACK);
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(90, 52, "Back");

        // Title
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        setcolor(BLACK);
        outtextxy(500, 60, "Add New Task");

        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

        // Title Field
        setcolor(BLACK);
        outtextxy(400, 150, "Title:");
        rectangle(550, 145, 950, 180);

        // Description Field
        outtextxy(400, 210, "Description:");
        rectangle(550, 205, 950, 240);

        // Priority Field
        outtextxy(400, 270, "Priority:");
        rectangle(550, 265, 950, 300);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(DARKGRAY);
        outtextxy(560, 272, "eg: Low");

        // Due Date Field
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(BLACK);
        outtextxy(400, 330, "Due Date:");
        rectangle(550, 325, 950, 360);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(DARKGRAY);
        outtextxy(560, 332, "YYYY-MM-DD");

        // ADD TASK Button
        setfillstyle(SOLID_FILL, GREEN);
        bar(500, 400, 800, 450);
        setcolor(BLACK);
        setbkcolor(GREEN);
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        outtextxy(580, 415, "ADD TASK");

        // Input Variables
        string title, description, priority_str, date_str;
        Date due;
        bool submitted = false;

        while (!submitted) {
            if (leftclick(550, 145, 950, 180, WHITE)) {
                title = getInput(550, 145, 950, 180, WHITE);
            }
            if (leftclick(550, 205, 950, 240, WHITE)) {
                description = getInput(550, 205, 950, 240, WHITE);
            }
            if (leftclick(550, 265, 950, 300, WHITE)) {
                priority_str = getInput(550, 265, 950, 300, WHITE);
            }
            if (leftclick(550, 325, 950, 360, WHITE)) {
                date_str = getInput(550, 325, 950, 360, WHITE);
            }

            // Submit
            if (leftclick(500, 400, 800, 450, GREEN)) {
                int priority = 0;
                // if (!priority_str.empty()) priority = stoi(priority_str);
                if(priority_str ==  "low" || priority_str == "Low" || priority_str == "LOW"){
                    priority = 0;
                }
                else if(priority_str ==  "medium" || priority_str == "Medium" || priority_str == "MEDIUM"){
                    priority = 1;
                }
                else if(priority_str ==  "high" || priority_str == "High" || priority_str == "HIGH"){
                    priority = 2;
                }
                stringstream ss(date_str);
                int y, m, d;
                char sep;
                ss >> y >> sep >> m >> sep >> d;
                due = Date(y, m, d);
                Task_Mananger tm;
                Task newTask(tm.tasklist.size() + 1, title, description, due, priority, Pending);
                tm.tasklist.push_back(newTask);
                cout << "Task Added:\n" << title << "\n" << description << "\n" << priority << "\n" << due.toString() << endl;
                settextstyle(GOTHIC_FONT,0,2);
                outtextxy(500,480,"Task Added Succesfully");
                tm.displayAlltasks(tm.tasklist);
                //submitted = true;
                delay(100);
            }

            // Back arrow
            if (leftclick(40, 40, 110, 80, RED)) {
                managetask();
            }
        }
    }

   void deleteTaskForm() {
    cleardevice();

    string searched_term;
    int matched_index = -1;

    // Input Box
    setcolor(BLACK);
    rectangle(400, 10, 800, 50);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
    outtextxy(410, 15, "Enter Task Title or ID");

    // Find Button
    settextstyle(SANS_SERIF_FONT, 0, 2);
    setfillstyle(SOLID_FILL, BLUE);
    setbkcolor(BLUE);
    setcolor(WHITE);
    bar(820, 13, 900, 47);
    outtextxy(830, 18, "Find");

    // Decorative Blue Box
    setfillstyle(SOLID_FILL, BLUE);
    bar(300, 200, 900, 350);
    settextstyle(GOTHIC_FONT, 0, 2);
    outtextxy(310, 205, "ID: ");
    outtextxy(310, 235, "Title: ");
    outtextxy(310, 265 , "Priority: ");
    outtextxy(310, 295, "Due Date: ");
    outtextxy(310, 325, "Status: ");

    // Delete Button
    setfillstyle(SOLID_FILL, RED);
    setbkcolor(RED);
    settextstyle(GOTHIC_FONT, 0, 4);
    bar(300,500,900,550);
    outtextxy(470, 505, "Delete Task");

    // Back Arrow

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    int arrowPoints[] = {
        80, 40,   // Point 1 (top-right)
        40, 60,   // Point 2 (tip of arrow)
        80, 80,   // Point 3 (bottom-right)
        80, 40    // Closing back to Point 1
    };
    fillpoly(4, arrowPoints);

    // Label "Back"
    setcolor(BLACK);
    setbkcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, 0, 2);
    outtextxy(90, 52, "Back");

    while (true) {
        if (leftclick(400, 10, 800, 50, WHITE)) {
            searched_term = getInput(405, 11, 795, 49, WHITE);
        }

        if (leftclick(820, 13, 900, 47, BLUE)) {
            setfillstyle(SOLID_FILL, BLUE);
            bar(360, 205, 900, 225);
            bar(400, 235, 900, 255);
            bar(415, 265, 900, 285);
            bar(450, 295, 900, 315);
            bar(410, 325, 900, 345);
            string input = trim(searched_term);
            matched_index = -1;

            for (size_t i = 0; i < Task_Mananger::tasklist.size(); ++i) {
                bool match = false;

                if (isNumber(input)) {
                    int inputID = stoi(input);
                    match = (Task_Mananger::tasklist[i].getId() == inputID);
                } else {
                    match = (toLower(trim(Task_Mananger::tasklist[i].getTitle())) == toLower(input));
                }

                if (match) {
                    const char* Task_priority[] = {"Low", "Medium", "High"};
                    const char* Completed_status[] = {"Pending", "Completed", "Overdue"};

                    string ID = to_string(Task_Mananger::tasklist[i].getId());
                    string date = Task_Mananger::tasklist[i].getDuedate().toString();

                    settextstyle(GOTHIC_FONT, 0, 1);
                    setbkcolor(BLUE);
                    setcolor(WHITE);
                    outtextxy(360, 205, (char*)ID.c_str());
                    outtextxy(400, 235, (char*)Task_Mananger::tasklist[i].getTitle().c_str());
                    outtextxy(415, 265 , (char*)Task_priority[Task_Mananger::tasklist[i].getPriority()]);
                    outtextxy(450, 295, (char*)date.c_str());
                    outtextxy(410, 325, (char*)Completed_status[Task_Mananger::tasklist[i].getStatus()]);

                    matched_index = i;
                    break;
                }
            }

            if (matched_index == -1) {
                cout << "Task not found.\n";
                setbkcolor(WHITE);
                setcolor(RED);
                settextstyle(GOTHIC_FONT, 0, 2);
                outtextxy(500, 370, "Task Not Found");
            }
        }

        if (leftclick(300, 500, 900, 550, RED)) {
            if (matched_index != -1) {
                Task_Mananger::tasklist.erase(Task_Mananger::tasklist.begin() + matched_index);
                cout << "Task Deleted\n";

                settextstyle(GOTHIC_FONT, 0, 2);
                setbkcolor(WHITE);
                setcolor(GREEN);
                outtextxy(500, 580, "Task Deleted");

                matched_index = -1;
            }
        }
        // Back arrow
        if (leftclick(40, 40, 110, 80, RED)) {
            managetask();
        }
    }
}

    void editTask(){
        setbkcolor(WHITE);
        cleardevice();

        string searched_term;
        int matched_index = -1;
        // Input Variables
        string title, description, priority_str, date_str, status_str;
        Date due;

        // Input Box
        setcolor(BLACK);
        rectangle(400, 40, 800, 80);  // Moved slightly lower
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        outtextxy(410, 50, "Enter Task Title or ID");

        // Find Button
        settextstyle(SANS_SERIF_FONT, 0, 2);
        setfillstyle(SOLID_FILL, BLUE);
        setbkcolor(BLUE);
        setcolor(WHITE);
        bar(820, 43, 900, 77);  // aligned with input box
        outtextxy(830, 48, "Find");

        // Decorative Blue Box for task info
        setfillstyle(SOLID_FILL, BLUE);
        bar(300, 100, 900, 250);
        settextstyle(GOTHIC_FONT, 0, 2);
        setcolor(WHITE);
        outtextxy(310, 110, "ID: ");
        outtextxy(310, 140, "Title: ");
        outtextxy(310, 170, "Priority: ");
        outtextxy(310, 200, "Due Date: ");
        outtextxy(310, 230, "Status: ");

        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

        // Title Field
        setcolor(BLACK);
        outtextxy(250, 270, "Title:");
        rectangle(400, 265, 800, 300);

        // Description Field
        outtextxy(250, 330, "Description:");
        rectangle(400, 325, 800, 360);

        // Priority Field
        outtextxy(250, 390, "Priority:");
        rectangle(400, 385, 800, 420);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(DARKGRAY);
        outtextxy(410, 392, "eg: Low");

        // Due Date Field
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(BLACK);
        outtextxy(250, 450, "Due Date:");
        rectangle(400, 445, 800, 480);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(DARKGRAY);
        outtextxy(410, 452, "YYYY-MM-DD");

        // Status Field
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
        setcolor(BLACK);
        outtextxy(250, 510, "Status:");
        rectangle(400, 505, 800, 540);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
        setcolor(DARKGRAY);
        outtextxy(410, 512, "eg: Completed");

        // EDIT TASK Button
        setfillstyle(SOLID_FILL, MAGENTA);
        bar(450, 560, 750, 600);
        setcolor(BLACK);
        setbkcolor(MAGENTA);
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        outtextxy(540, 565, "EDIT TASK");

        // Back Arrow

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        int arrowPoints[] = {
            80, 40,   // Point 1 (top-right)
            40, 60,   // Point 2 (tip of arrow)
            80, 80,   // Point 3 (bottom-right)
            80, 40    // Closing back to Point 1
        };
        fillpoly(4, arrowPoints);

        // Label "Back"
        setcolor(BLACK);
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(90, 52, "Back");

        while (true) {
            if (leftclick(400, 40, 800, 80, WHITE)) {
                searched_term = getInput(405, 41, 795, 79, WHITE);
            }
            if (leftclick(820, 43, 900, 77, BLUE)) {
                setfillstyle(SOLID_FILL, BLUE);
                bar(360, 110, 900, 120);
                bar(400, 140, 900, 160);
                bar(415, 170, 900, 190);
                bar(450, 200, 900, 220);
                bar(410, 230, 900, 250);
                string input = trim(searched_term);
                matched_index = -1;

                for (size_t i = 0; i < Task_Mananger::tasklist.size(); ++i) {
                    bool match = false;

                    if (isNumber(input)) {
                        int inputID = stoi(input);
                        match = (Task_Mananger::tasklist[i].getId() == inputID);
                    } else {
                        match = (toLower(trim(Task_Mananger::tasklist[i].getTitle())) == toLower(input));
                    }

                    if (match) {
                        const char* Task_priority[] = {"Low", "Medium", "High"};
                        const char* Completed_status[] = {"Pending", "Completed", "Overdue"};

                        string ID = to_string(Task_Mananger::tasklist[i].getId());
                        string date = Task_Mananger::tasklist[i].getDuedate().toString();

                        settextstyle(GOTHIC_FONT, 0, 1);
                        setbkcolor(BLUE);
                        setcolor(WHITE);
                        outtextxy(360, 110, (char*)ID.c_str());
                        outtextxy(400, 140, (char*)Task_Mananger::tasklist[i].getTitle().c_str());
                        outtextxy(415, 170, (char*)Task_priority[Task_Mananger::tasklist[i].getPriority()]);
                        outtextxy(450, 200, (char*)date.c_str());
                        outtextxy(410, 230, (char*)Completed_status[Task_Mananger::tasklist[i].getStatus()]);

                        matched_index = i;
                        break;
                    }
                }

                if (matched_index == -1) {
                    cout << "Task not found.\n";
                    setbkcolor(WHITE);
                    setcolor(RED);
                    settextstyle(GOTHIC_FONT, 0, 2);
                    outtextxy(500, 370, "Task Not Found");
                }
            }
            if (leftclick(400, 265, 800, 300, WHITE)) {
                title = getInput(400, 265, 800, 300, WHITE);
            }
            if (leftclick(400, 325, 800, 360, WHITE)) {
                description = getInput(400, 325, 800, 360, WHITE);
            }
            if (leftclick(400, 385, 800, 420, WHITE)) {
                priority_str = getInput(400, 385, 800, 420, WHITE);
            }
            if (leftclick(400, 445, 800, 480, WHITE)) {
                date_str = getInput(400, 445, 800, 480, WHITE);
            }
            if(leftclick(400, 505, 800, 540, WHITE)){
                status_str = getInput(400, 505, 800, 540, WHITE);
            }

            if(leftclick(450, 560, 750, 600, MAGENTA)){

                if (matched_index != -1) {
                    Task_Mananger::tasklist[matched_index].editTask(title, description, date_str, priority_str, status_str);
                    setbkcolor(WHITE);
                    setcolor(GREEN);
                    settextstyle(GOTHIC_FONT, 0, 2);
                    outtextxy(500, 620, "Task Updated Successfully");
                }

        
            }
            // Back arrow
            if (leftclick(40, 40, 110, 80, RED)) {
                managetask();
            }
        
        }
    }


    string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }

    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t");
        size_t last = str.find_last_not_of(" \t");
        return (first == string::npos) ? "" : str.substr(first, last - first + 1);
    }

    bool isNumber(const string& s) {
        return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
    }

    void viewTask() {
    setbkcolor(WHITE);
    cleardevice();

    const int tasksPerPage = 6;
    int pageNumber = 0;
    int totalTasks = Task_Mananger::tasklist.size();
    int totalPages = (totalTasks + tasksPerPage - 1) / tasksPerPage;

    

    while (true) {
        setbkcolor(WHITE);
        cleardevice();
        // Back Arrow

        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        int arrowPoints[] = {
            80, 40,   // Point 1 (top-right)
            40, 60,   // Point 2 (tip of arrow)
            80, 80,   // Point 3 (bottom-right)
            80, 40    // Closing back to Point 1
        };
        fillpoly(4, arrowPoints);

        // Label "Back"
        setcolor(BLACK);
        setbkcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 2);
        outtextxy(90, 52, "Back");

        setfillstyle(SOLID_FILL, BLUE);
        setbkcolor(BLUE);
        setcolor(WHITE);
        settextstyle(SANS_SERIF_FONT, 0, 2);

        int marginX = 50;
        int marginY = 100;
        int gapX = 50;
        int gapY = 50;
        int boxWidth = 500;
        int boxHeight = 150;

        int startIndex = pageNumber * tasksPerPage;

        for (int i = 0; i < tasksPerPage && (startIndex + i) < totalTasks; ++i) {
            int row = i / 2;
            int col = i % 2;

            int x1 = marginX + col * (boxWidth + gapX);
            int y1 = marginY + row * (boxHeight + gapY);
            int x2 = x1 + boxWidth;
            int y2 = y1 + boxHeight;

            bar(x1, y1, x2, y2);

            Task t = Task_Mananger::tasklist[startIndex + i];
            string id = "ID: " + to_string(t.getId());
            string title = "Title: " + t.getTitle();
            string due = "Due Date: " + t.getDuedate().toString();
            const char* priorities[] = {"Low", "Medium", "High"};
            const char* statuses[] = {"Pending", "Completed", "Overdue"};
            string priority = "Priority: " + string(priorities[t.getPriority()]);
            string status = "Status: " + string(statuses[t.getStatus()]);

            outtextxy(x1 + 5, y1 + 5, (char*)id.c_str());
            outtextxy(x1 + 5, y1 + 40, (char*)title.c_str());
            outtextxy(x1 + 5, y1 + 75, (char*)due.c_str());
            outtextxy(x1 + 250, y1 + 5, (char*)priority.c_str());
            outtextxy(x1 + 250, y1 + 40, (char*)status.c_str());
        }

        // Page Info
        settextstyle(SANS_SERIF_FONT, 0, 1);
        setbkcolor(WHITE);
        setcolor(BLACK);
        string pageInfo = "Page " + to_string(pageNumber + 1) + " of " + to_string(totalPages);
        outtextxy(550, 700, (char*)pageInfo.c_str());

        // Next Button
        setfillstyle(SOLID_FILL, GREEN);
        bar(1000, 700, 1100, 740);
        setcolor(WHITE);
        setbkcolor(GREEN);
        outtextxy(1020, 710, "Next");

        // Prev Button
        setfillstyle(SOLID_FILL, RED);
        bar(100, 700, 200, 740);
        setcolor(WHITE);
        setbkcolor(RED);
        outtextxy(120, 710, "Prev");

        // Handle clicks
        while (true) {
            if (leftclick(1000, 700, 1100, 740, GREEN)) {
                if (pageNumber < totalPages - 1)
                    pageNumber++;
                break;
            }
            if (leftclick(100, 700, 200, 740, RED)) {
                if (pageNumber > 0)
                    pageNumber--;
                break;
            }
            // Back arrow
            if (leftclick(40, 40, 110, 80, RED)) {
                displayMainMenu();
            }
        }
    }
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
    Task_Mananger tm;
    fm.LoginMenu();

    getch();
    closegraph();
}