#include<iostream>
#include<ctime>
#include<graphics.h>
#include<vector>
#include<fstream>

using namespace std;

enum Task_priority{
    Low,
    Medium,
    High
};

enum  Completed_status{
    Pending,
    Completed
};
struct Date{
    int year;
    int month;
    int day;

    Date get_today_date(){
        time_t now = time(nullptr);
        tm* now_tm = localtime(&now);

        Date today;
        today.year = now_tm -> tm_year + 1900;
        today.month = now_tm  -> tm_mon + 1;
        today.day = now_tm -> tm_mday;

        return today;
    }
};
class Timer{
    public:
    int hr;
    int min;
    int sec;
    Timer(int hr,int min,int sec){
        this -> hr = hr;
        this -> min = min;
        this -> sec = sec;
    }
    Timer(){
        this -> hr = 0;
        this -> min = 0;
        this -> sec = 0;
    }
    void StartTimer(){
        int display_hr, display_min, display_sec;
        int total_sec = hr * 60 * 60+ min * 60 + sec;

        while(total_sec > 0){
            display_hr = total_sec / 3600;
            display_min = (total_sec % 3600) / 60;
            display_sec = total_sec % 60;
            cout << "\r" << (display_hr < 10 ? "0" : "") << display_hr << " : " << (display_min < 10 ? "0" : "") << display_min << " : " <<(display_sec < 10 ? "0" : "") << display_sec;
            delay(1000);
            total_sec--;
            
        }
        cout << "\nTimes up \n";

    }
};

class Task{
    string taskname;
    string description;
    bool completed;
    int priority;
    Date due_date;

    public:

    Task(){

        description = "-";
        priority = Low;
        completed = Pending;
        due_date = due_date.get_today_date();

    }
    void input_task(){
        
        cout << "Enter task name: ";
        getline(cin,taskname);
        cout << "Enter task description(- for no description): ";
        getline(cin, description);
        cout << "Enter task priority(low = 0, medium = 1, high = 2): ";
        cin >> priority;
        cout << "Enter task due date(yyyy mm dd): ";
        cin >> due_date.year >> due_date.month >> due_date.day;

    }

    void display_task(){
        const char* Task_priority[] = {"Low" , "Medium" , "High"};
        const char* Completed_status[] = {"Pending" , "Completed"};

        cout << "Task: " << taskname << endl;
        cout << "   Description: " << description << endl;
        cout << "   Deadline: " << due_date.year <<"/" << due_date.month << "/" << due_date.day << endl;
        cout << "   Priority: " << Task_priority[priority] << endl;
        cout << "   Status: " << Completed_status[completed] << endl;

    }

    void start_task(){
        Timer timer;
        cout << "Enter time to complete task(hr min sec): ";
        cin >> timer.hr >> timer.min >> timer.sec;
        display_task();
        timer.StartTimer();
    }
    
    bool is_today(){
        
        if(due_date.year == due_date.get_today_date().year && due_date.month == due_date.get_today_date().month && due_date.day == due_date.get_today_date().day){
            return true;
        }
        return false;
    }

    bool is_completed(){
        return completed;
    }

    friend class File_manager;

};

class File_manager{
    vector<Task> tasklist;

    public:
    void add_task(Task task){
        tasklist.push_back(task);
    }
    void remove_task(Task task, int n){
        tasklist.erase(tasklist.begin() + n);
    }
    void save_tasks(){
        int n;
        fstream outfile("tasklist.txt", ios::out | ios::in);

        if(!outfile){
            cout<<"File not found\n";
            exit(1);
        }

        outfile >> n;
        outfile.ignore();

        if(n > 0){
        outfile.seekp(0,ios::beg);
        outfile << n + tasklist.size() << endl;
        outfile.seekp(0,ios::end);
        }
        else{
            outfile.seekp(0,ios::beg);
            outfile << tasklist.size() << endl;
        }

        for(int i = 0; i < tasklist.size(); i++){
            outfile << tasklist[i].taskname << '|';
            outfile << tasklist[i].description << '|';
            outfile << tasklist[i].priority << '|';
            outfile << tasklist[i].completed << '|';
            outfile << tasklist[i].due_date.year << '-';
            outfile << tasklist[i].due_date.month << '-';
            outfile << tasklist[i].due_date.day << endl;
        }
        outfile.close();
    }

    vector<Task> load_tasks(){
        ifstream infile("tasklist.txt");
        int n;

        if(!infile){
            cout<<"File not found\n";
            exit(1);
        }

        infile >> n;
        infile.ignore();
        tasklist.clear();
        string line;

        for(int i = 0; i < n; i++){
            Task task;
            char sep;

            getline(infile,line);

            stringstream iss(line);

            getline(iss,task.taskname,'|');
            getline(iss,task.description,'|');


            iss >>task.priority >> sep >> task.completed >> sep >> task.due_date.year >> sep >> task.due_date.month >> sep >> task.due_date.day;

            tasklist.push_back(task);
        }

        infile.close();
        return tasklist;
    }

};

int main(){

int choice = 0;

while(choice != 99){

    cout << endl;
    cout << "1. Set Timer\n";
    cout << "2. Add Task\n";
    cout << "3. Start Task\n";
    cout << "4. View Tasks\n";
    cout << "5. View Daily Tasks\n";
    cout << "6. View Statistics\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch(choice){

        case 1:{
            Timer T;
            cout << "Enter time(hr min sec): ";
            cin >> T.hr >> T.min >> T.sec;
            T.StartTimer();
            break;
        }
        case 2:{
            Task T;
            File_manager file;
            T.input_task();
            T.display_task();
            file.add_task(T);
            file.save_tasks();
            break;
        }
        case 3:{
            Task T;
            T.start_task();
            break;
        }
        case 4:{
            int count = 1;
            vector<Task> tasklist = File_manager().load_tasks();
            for(int i = 0; i < tasklist.size(); i++){
                if(tasklist[i].is_completed() == Pending){
                cout << count << ". "; 
                tasklist[i].display_task();
                count++;
                }
            }
            break;
        }
        case 5:{
            int count = 1;
            vector<Task> tasklist = File_manager().load_tasks();
            
            for(int i = 0; i < tasklist.size(); i++){
                if(tasklist[i].is_today() && tasklist[i].is_completed() == Pending){
                    cout << count << ". "; 
                    tasklist[i].display_task();
                    count++;
                }
            }
            break;
        }
        case 6:{
            //See Statistics
            break;
        }
        case 7:{
            choice = 99;
            break;
        }
        default:
            cout << "Invalid choice\n";
            break;
    }

}

}