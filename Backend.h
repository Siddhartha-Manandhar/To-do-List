#ifndef BACKEND_H
#define BACKEND_H

#include<iostream>
#include<graphics.h>
#include<ctime>
#include<conio.h>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib") // Link Multimedia sound library

using namespace std;

enum Task_priority{
    Low,
    Medium,
    High
};

enum Completed_status{
    Pending,
    Completed,
    Overdue
};

class Date{
    int year;
    int month;
    int day;

    public:
    Date(){
        time_t now = time(nullptr);
        tm* now_tm = localtime(&now);

        year = now_tm -> tm_year + 1900;
        month = now_tm  -> tm_mon + 1;
        day = now_tm -> tm_mday;
    }
    Date(int y, int m, int d): year(y), month(m), day(d) {}

    bool isToday(){
        Date today;
        return (*this == today);
    }
    bool isOverdue(){
        Date today;
        if (today.year < this->year || (today.year == this->year && today.month < this->month) || (today.year == this->year && today.month == this->month && today.day < this->day)){
            return true;
        }
        return false;
    }
    
    string toString(){
        string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        stringstream ss;
        ss << this->day <<   th(this->day) << " " << months[this->month - 1] << ", " << this->year;
        return ss.str();
    }
    string th(int day){
        if (day == 1 || day == 21 || day == 31){
            return "st";
        }
        else if (day == 2 || day == 22){
            return "nd";
        }
        else if (day == 3 || day == 23){
            return "rd";
        }
        else{
            return "th";
        }
    }
    
    bool operator==(const Date& d) const {
    return year == d.year && month == d.month && day == d.day;
    }

    bool operator<(Date d) const{
        if(year != d.year) return year < d.year;
        if(month != d.month) return month < d.month;
        return day < d.day;
    }
    bool isLeap(int year) const {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

    int countDays() const {
        int days = year * 365 + day;
        int monthDays[] = {0, 31, 59, 90, 120, 151, 181, 212,
                           243, 273, 304, 334};

        days += monthDays[month - 1];
        days += year / 4 - year / 100 + year / 400;

        if (month > 2 && isLeap(year))
            days += 1;

        return days;
    }

    int daysBetween( Date d) {
        return abs(this->countDays() - d.countDays());
    }

    friend class Task;
    friend class File_Manager;

};

class Task{
    
    int id;
    string title;
    string description;
    Date duedate;
    int priority;
    int status;

    public:
    Task(): id(0), title(""), description(""), duedate(Date()), priority(Low), status(Pending) {}
    Task(int id, string title, string description, Date duedate, int priority = Low, int status = Pending): id(id), title(title), description(description), duedate(duedate), priority(priority), status(status) {}

    void markCompleted(){
        status = Completed;
    }

    void markOverdue(){
        status = Overdue;
    }
    void editTask(){
        string input;

        cout << "Current Title: " << title << endl;
        cout << "Enter new title: ";
        getline(cin, input);
        if(!input.empty()){
            title = input;
        }

        cout << "Current Description: " << description << endl;
        cout << "Enter new description: ";
        getline(cin, input);
        if(!input.empty()){
            description = input;
        }

        cout << duedate.toString() << endl;
        cout << "Enter new due date: ";
        getline(cin, input);
        if(!input.empty()){
            // duedate = Date(stoi(input.substr(0, 4)), stoi(input.substr(5, 2)), stoi(input.substr(8, 2)));
            stringstream ss(input);
            int new_year;
            int new_month;
            int new_day;
            char sep;
            ss >> new_year >> sep >> new_month >> sep >> new_day;
            duedate = Date(new_year, new_month, new_day);
        }

        cout << "Current Priority: " << priority << endl;
        cout << "Enter new priority(low = 0, medium = 1, high = 2): ";
        getline(cin, input);
        if(!input.empty()){
            priority = stoi(input);
        }

        cout << "Current Status: " << status << endl;
        cout << "Enter new status(pending = 0, completed = 1, overdue = 2): ";
        getline(cin, input);
        if(!input.empty()){
            status = stoi(input);
        }
    }

    void displayTask(){

        const char* Task_priority[] = {"Low" , "Medium" , "High"};
        const char* Completed_status[] = {"Pending" , "Completed", "Overdue"};

        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Due Date: " << duedate.toString() << endl;
        cout << "Priority: " << Task_priority[priority] << endl;
        cout << "Status: " << Completed_status[status] << endl;
    }   

    int getId(){
        return id;
    }
    int getStatus(){
        return status;
    }
    Date getDuedate(){
        return duedate;
    }
    int getPriority(){
        return priority;
    }
    string getTitle(){
        return title;
    }
    friend class File_Manager;
};

class File_Manager{
    public:
    void saveTasks(vector<Task> tasklist, string user_name){
        ofstream file(user_name + "tasklist.txt", ios::out | ios::trunc);
        if (!file) {
            cout << "Unable to open file for saving.\n";
            return;
        }

        for(size_t i = 0; i < tasklist.size(); i++){
            
            file << tasklist[i].id << '|';
            file << tasklist[i].title << '|';
            file << tasklist[i].description << '|';
            file << tasklist[i].priority << '|';
            file << tasklist[i].status << '|';
            file << tasklist[i].duedate.year << '-';
            file << tasklist[i].duedate.month << '-';
            file << tasklist[i].duedate.day << endl;
        }
        cout << "Tasks saved\n";
        file.close();
    }

    vector<Task> loadTasks(string user_name){

        vector<Task> tasklist;
        ifstream infile(user_name + "tasklist.txt");

        if (!infile) {
            cout << "No existing task file found. Starting fresh.\n";
            return tasklist;
        }

        tasklist.clear();
        string line;

        while(getline(infile,line)){
            Task task;
            char sep;

            stringstream iss(line);

            iss >> task.id >> sep;
            getline(iss,task.title,'|');
            getline(iss,task.description,'|');

            iss >> task.priority >> sep >> task.status >> sep >> task.duedate.year >> sep >> task.duedate.month >> sep >> task.duedate.day;

            tasklist.push_back(task);
        }

        infile.close();
        return tasklist;

    }
};

class Task_Mananger{

    vector<Task> tasklist;

    public:
    void addTask(Task task){
        tasklist.push_back(task);
    }
    void deleteTask(Task task){
        tasklist.erase(tasklist.begin() + task.getId() - 1);
    }

    vector<Task> filterTasklist(int choice = 1){

        vector<Task> filteredTasklist;
        switch(choice){
            case 1:{
                //pending tasks
                for(size_t i = 0; i < tasklist.size(); i++){
                    if(tasklist[i].getStatus() == 0){
                        filteredTasklist.push_back(tasklist[i]);
                    }
                }
                return filteredTasklist;
                break;
            }

            case 2:{
                //completed tasks
                for(size_t i = 0; i < tasklist.size(); i++){
                    if(tasklist[i].getStatus() == 1){
                        filteredTasklist.push_back(tasklist[i]);
                    }
                }
                return filteredTasklist;
                break;
            }

            case 3:{
                //overdue tasks
                for(size_t i = 0; i < tasklist.size(); i++){
                    if(tasklist[i].getStatus() == 2){
                        filteredTasklist.push_back(tasklist[i]);
                    }
                }
                return filteredTasklist;
                break;
            }

            case 4:{
                //Today Tasks
                for(size_t i = 0; i < tasklist.size(); i++){
                    if(tasklist[i].getDuedate().isToday()){
                        filteredTasklist.push_back(tasklist[i]);
                    }
                }
                return filteredTasklist;
                break;
            }

            case 5:{
                //Low Priority
                for(size_t i = 0; i < tasklist.size(); i++){
                    if(tasklist[i].getPriority() == 0){
                        filteredTasklist.push_back(tasklist[i]);
                    }
                }
                return filteredTasklist;
                break;
            }

            case 6:{
                //Medium Priority
                for(size_t i = 0; i < tasklist.size(); i++){
                    if(tasklist[i].getPriority() == 1){
                        filteredTasklist.push_back(tasklist[i]);
                    }
                }
                return filteredTasklist;
                break;
            }

            case 7:{
                //High Priority
                for(size_t i = 0; i < tasklist.size(); i++){
                    if(tasklist[i].getPriority() == 2){
                        filteredTasklist.push_back(tasklist[i]);
                    }
                }
                return filteredTasklist;
                break;
            }
        }
    }

    vector<Task> sortTask(int choice = 1){

        switch(choice){
            case 1:{
                //sort by due date
                vector<Task> sortedTasklist = tasklist;
                sort(sortedTasklist.begin(), sortedTasklist.end(), [](Task a, Task b) {
                    return a.getDuedate() < b.getDuedate();
                });
                return sortedTasklist;
                break;
            }

            case 2:{
                //sort by priority
                vector<Task> sortedTasklist = tasklist;
                sort(sortedTasklist.begin(), sortedTasklist.end(), [](Task a, Task b) {
                    return a.getPriority() < b.getPriority();
                });
                return sortedTasklist;
                break;
            }

            case 3:{
                //sort by status
                vector<Task> sortedTasklist = tasklist;
                sort(sortedTasklist.begin(), sortedTasklist.end(), [](Task a, Task b) {
                    return a.getStatus() < b.getStatus();
                });
                return sortedTasklist;
                break;
            }
            case 4:{
                //sort by id
                vector<Task> sortedTasklist = tasklist;
                sort(sortedTasklist.begin(), sortedTasklist.end(), [](Task a, Task b) {
                    return a.getId() < b.getId();
                });
                return sortedTasklist;
                break;
            }
        }
    }

    vector<Task> searchTask(string search_term){

        vector<Task> searchedTasklist;
        for(size_t i = 0; i < tasklist.size(); i++){
            if(tasklist[i].getTitle().find(search_term) != string::npos){
                searchedTasklist.push_back(tasklist[i]);
            }
        }
        return searchedTasklist;
    }
    void displayAlltasks(vector<Task> custom_tasklist){
        for(size_t i = 0; i < custom_tasklist.size(); i++){
            custom_tasklist[i].displayTask();
        }
    }
    void showStatistics(){
        size_t total_tasks = tasklist.size();
        int completed_tasks = 0;
        int pending_tasks = 0;
        int overdue_tasks = 0;
        int low_priority_tasks = 0;
        int medium_priority_tasks = 0;
        int high_priority_tasks = 0;
        float completion_rate = 0;
        int longest_overdue_task_length = 0;
        int shortest_pending_task_length = 10000;
        string longest_overdue_task = "";
        string next_pending_task = "";

        for(size_t i = 0; i < tasklist.size(); i++){
            if(tasklist[i].getStatus() == 1){
                completed_tasks++;
            }
            else if(tasklist[i].getStatus() == 0){
                pending_tasks++;
            }
            else{
                overdue_tasks++;
            }
        }

        for(size_t i = 0; i < tasklist.size(); i++){
            if(tasklist[i].getPriority() == 0){
                low_priority_tasks++;
            }
            else if(tasklist[i].getPriority() == 1){
                medium_priority_tasks++;
            }
            else{
                high_priority_tasks++;
            }
        }
        completion_rate = ((float)completed_tasks / total_tasks) * 100;

        vector<Task> overdue_tasks_list = filterTasklist(3);
        Date today;
        for(size_t i = 0; i < overdue_tasks_list.size(); i++){
            if(overdue_tasks_list[i].getDuedate().daysBetween(today) > longest_overdue_task_length){
                longest_overdue_task_length = overdue_tasks_list[i].getDuedate().daysBetween(today);
                longest_overdue_task = overdue_tasks_list[i].getTitle();
            }
        }

        vector<Task> pending_tasks_list = filterTasklist(1);
        for(size_t i = 0; i < pending_tasks_list.size(); i++){
            if(pending_tasks_list.empty()){
                next_pending_task = "No pending tasks";
                shortest_pending_task_length = 0;
                break;
            }
            if(pending_tasks_list[i].getDuedate().daysBetween(today) < shortest_pending_task_length){
                shortest_pending_task_length = pending_tasks_list[i].getDuedate().daysBetween(today);
                next_pending_task = pending_tasks_list[i].getTitle();
            }
            
        }

        cout<<"Total tasks: "<<total_tasks<<endl;
        cout<<"Completed tasks: "<<completed_tasks<<endl;
        cout<<"Pending tasks: "<<pending_tasks<<endl;
        cout<<"Overdue tasks: "<<overdue_tasks<<endl;
        cout<<"Low priority tasks: "<<low_priority_tasks<<endl;
        cout<<"Medium priority tasks: "<<medium_priority_tasks<<endl;
        cout<<"High priority tasks: "<<high_priority_tasks<<endl;
        cout<<"Completion rate: "<< fixed << setprecision(2) <<completion_rate<<"%"<<endl;
        cout<<"Longest overdue task: "<<longest_overdue_task<<endl;
        cout<<"Longest overdue task length: "<<longest_overdue_task_length<<" days"<<endl;
        cout<<"Next pending task: "<<next_pending_task<<endl;
        cout<<"Days Remaining: "<<shortest_pending_task_length<<" days"<<endl;
    }
    vector<Task> getTasklist(){return tasklist;}

};

class Timer_Mananger{
public:
    int hours, minutes, seconds;
    bool paused;
    bool stopped;

    void playAlarm() {
    cout << "\nTime's up! Press any key to stop the alarm.\n";

    // Play the sound in async mode so it loops in the background
    PlaySoundA("alarm.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    // Wait for any key to stop
    getch();

    // Stop the sound
    PlaySoundA(NULL, 0, 0);

    cout << "Alarm stopped.\n";
}

    void decrementTime() {
        if (seconds > 0) {
            --seconds;
        } else if (minutes > 0) {
            --minutes;
            seconds = 59;
        } else if (hours > 0) {
            --hours;
            minutes = 59;
            seconds = 59;
        }
    }

    bool isTimeRemaining() const {
        return hours > 0 || minutes > 0 || seconds > 0;
    }

    void displayTime() const {
        cout << "\rTime left: "
             << setw(2) << setfill('0') << hours << ":"
             << setw(2) << setfill('0') << minutes << ":"
             << setw(2) << setfill('0') << seconds << flush;
    }

    Timer_Mananger(int h, int m, int s) : hours(h), minutes(m), seconds(s), paused(false), stopped(true) {}

    bool isValid() const {
        return hours >= 0 && minutes >= 0 && seconds >= 0 &&
               (hours > 0 || minutes > 0 || seconds > 0);
    }

    void start() {
        while (isTimeRemaining()) {
            if (_kbhit()) {
                char c = _getch();
                if (c == 's' || c == 'S') {
                    cout << "\nTimer stopped\n";
                    return;
                } else if (c == 'p' || c == 'P') {
                    cout << "\nTimer paused. Press 'r' to resume\n";
                    paused = true;
                } else if (c == 'r' || c == 'R') {
                    if (paused) {
                        cout << "\nResuming timer...\n";
                        paused = false;
                    }
                }
            }

            if (!paused) {
                displayTime();
                Sleep(1000);
                decrementTime();
            }
        }

        displayTime(); // Show 00:00:00 before alarm
        playAlarm();
    }

    void reset(int h, int m, int s) {
        hours = h;
        minutes = m;
        seconds = s;
        paused = false;
    }


};
class Login_Mananger{
    string user_name;
    string password;
    int choice;

    public:
    void register_user(){
        fstream file ("user_info.txt", ios::out | ios::app);
        if(!file){
            cout<<"File not found\n";
            exit(1);
        }

        file << user_name << '|' << encryption(password, password.length()) << endl;
        file.close();

        ofstream outfile (user_name + "tasklist.txt");
        outfile.close();
    }

    string login_user(){
        ifstream infile ("user_info.txt");

        if(!infile){
            cout<<"File not found\n";
            exit(1);
        }
        string line;

        while(getline(infile,line)){
            string Uname, Pwd;
            char sep;
            stringstream ss(line);
            getline(ss,Uname,'|');
            getline(ss,Pwd,'|');
            if(user_name == Uname && password == decryption(Pwd, password.length())){
                infile.close();
                return Uname;
            }
    
        }
        cout << "User not found\n";
        infile.close();
        return "";

    }

    string encryption(string password, int key, int digit = 0) {
        string encryptData = ""; 
        if(digit == 0) digit = key;

        for (auto chr : password) {
            if ('A' <= chr && 'Z' >= chr) {
                encryptData += (65 + (chr - 65 + key) % 26);
            } else if ('a' <= chr && 'z' >= chr) {
                encryptData += (97 + (chr - 97 + key) % 26);
            } else if ('0' <= chr && '9' >= chr) {
                encryptData += ('0' + (chr - '0' + digit) % 10);
            } else {
                encryptData += chr;
            }
        }
        return encryptData;
    }

    string decryption(string password, int key) {
        return encryption(password, 26 - key, 10 - key);
    }
    void getUsername(string username) { user_name = username; }
    void getPassword(string password) { this->password = password; }

};
#endif