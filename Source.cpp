#include<iostream>
#include<ctime>
#include<graphics.h>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

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
    friend class Task_manager;

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
    void save_tasks(string user_name){
        fstream file(user_name + "tasklist.txt", ios::out | ios::app);
        if(!file){
            cout<<"File not found\n";
            exit(1);
        }

        for(size_t i = 0; i < tasklist.size(); i++){
            
            file << tasklist[i].taskname << '|';
            file << tasklist[i].description << '|';
            file << tasklist[i].priority << '|';
            file << tasklist[i].completed << '|';
            file << tasklist[i].due_date.year << '-';
            file << tasklist[i].due_date.month << '-';
            file << tasklist[i].due_date.day << endl;
        }
        cout << "Tasks saved\n";
        file.close();
    }

    vector<Task> load_tasks(string user_name){
        ifstream infile(user_name + "tasklist.txt");

        if(!infile){
            cout<<"File not found\n";
            exit(1);
        }

        tasklist.clear();
        string line;

        while(getline(infile,line)){
            Task task;
            char sep;

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

class Login_Mananger{
    string user_name;
    string password;
    int choice;

    public:
    void register_user(){
        cout << "Enter a user name: ";
        cin >> user_name;

        cout << "Enter a password: ";
        cin >> password;

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

        cout << "Enter a user name: ";
        cin >> user_name;

        cout<< "Enter a password: ";
        cin >> password;

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

};
class Task_manager{
  public:
    void start_task(string user_name) {
        File_manager file;
        vector<Task> tasklist = file.load_tasks(user_name);

        if (tasklist.empty()) {
            cout << "No tasks found.\n";
            return;
        }

        cout << "\nSelect a task to start:\n";
        for (size_t i = 0; i < tasklist.size(); ++i) {
            cout << i + 1 << ". ";
            tasklist[i].display_task();
        }

        int choice;
        cout << "Enter the number of the task you want to start: ";
        cin >> choice;

        if (choice < 1 || choice > tasklist.size()) {
            cout << "Invalid choice.\n";
            return;
        }

        Task &selected_task = tasklist[choice - 1];

        Timer timer;
        cout << "Enter time to complete the task (hr min sec): ";
        cin >> timer.hr >> timer.min >> timer.sec;
        cin.ignore();

        selected_task.display_task();
        timer.StartTimer();

        char completed_choice;
        cout << "Have you completed the task? (y/n): ";
        cin >> completed_choice;

        if (completed_choice == 'y' || completed_choice == 'Y') {
            selected_task.completed = Completed;
            cout << "Task marked as completed.\n";
        } else {
            cout << "Task remains pending.\n";
        }

        // Save updated tasks back to the file
        fstream outfile(user_name + "tasklist.txt", ios::out | ios::trunc);
        if (!outfile) {
            cout << "File could not be opened for writing.\n";
            return;
        }

        for (const auto &task : tasklist) {
            outfile << task.taskname << '|'
                    << task.description << '|'
                    << task.priority << '|'
                    << task.completed << '|'
                    << task.due_date.year << '-'
                    << task.due_date.month << '-'
                    << task.due_date.day << endl;
        }

        outfile.close();
    }

    void delete_task(string user_name){
        File_manager file;
        vector<Task> tasklist = file.load_tasks(user_name);

        if(tasklist.empty()){
            cout << "No tasks to delete.\n";
            return;
        }

        cout << "\nAll Tasks:\n";
        for(size_t i = 0; i < tasklist.size(); i++){
            cout << i + 1 << ". ";
            tasklist[i].display_task();
        }

        int del_choice;
        cout << "Enter the number of the task to delete: ";
        cin >> del_choice;
        cin.ignore();

        if(del_choice < 1 || del_choice > tasklist.size()){
            cout << "Invalid choice.\n";
            return;
        }

        tasklist.erase(tasklist.begin() + del_choice - 1);

        fstream outfile(user_name + "tasklist.txt", ios::out | ios::trunc);
        if(!outfile){
            cout << "File could not be opened.\n";
            return;
        }

        for(const auto &task : tasklist){
            outfile << task.taskname << '|'
                    << task.description << '|'
                    << task.priority << '|'
                    << task.completed << '|'
                    << task.due_date.year << '-'
                    << task.due_date.month << '-'
                    << task.due_date.day << endl;
        }

        outfile.close();
        cout << "Task deleted successfully.\n";
    }

};

// In Menu class, update TaskMenu:

class Menu{
    string user_name;
    public:
    void LoginMenu(){
        int auth_choice = 0;
        Login_Mananger lm;

        while (auth_choice != 99) {
            cout << "------------------------------\n";
            cout << "1. Register User\n";
            cout << "2. Login User\n";
            cout << "3. Exit\n";
            cout << "------------------------------\n";
            cout << "Enter your choice: ";
            cin >> auth_choice;

            switch (auth_choice) {
                case 1:{
                    lm.register_user();
                    break;
                }
                case 2:{
                    user_name = lm.login_user();
                    if(user_name != "") auth_choice = 99;
                    break;
                }
                case 3:
                    exit(0);
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void TaskMenu(){
        int choice = 0;

        while(choice != 99){

            cout << endl;
            cout << "1. Set Timer\n";
            cout << "2. Add Task\n";
            cout << "3. Start Task\n";
            cout << "4. View Tasks\n";
            cout << "5. View Daily Tasks\n";
            cout << "6. View Statistics\n";
            cout << "7. Delete Task\n";
            cout << "8. Exit\n";
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
                    file.save_tasks(user_name);
                    break;
                }
                case 3:{
                    Task_manager T;
                    T.start_task(user_name);
                    break;
                }
                case 4:{
                    int count = 1;
                    vector<Task> tasklist = File_manager().load_tasks(user_name);
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
                    vector<Task> tasklist = File_manager().load_tasks(user_name);
                    
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
                        vector<Task> tasklist = File_manager().load_tasks(user_name);
                        int total = tasklist.size();
                        int completed_count = 0;
                        int pending_count = 0;

                        for (auto &task : tasklist) {
                            if (task.is_completed() == Completed)
                                completed_count++;
                            else
                                pending_count++;
                        }

                        cout << "\n--- Task Statistics ---\n";
                        cout << "Total Tasks: " << total << endl;
                        cout << "Completed Tasks: " << completed_count << endl;
                        cout << "Pending Tasks: " << pending_count << endl;

                        if (total > 0) {
                            double percentage = (static_cast<double>(completed_count) / total) * 100.0;
                            cout << "Completion Percentage: " << percentage << "%" << endl;
                        } else {
                            cout << "No tasks to display statistics.\n";
                        }
                        cout << "------------------------\n";
                        break;
                    
                }
                case 7:{
                    Task_manager T;
                    T.delete_task(user_name);
                    break;
                }
                case 8:{
                    choice = 99;
                    break;
                }
                default:
                    cout << "Invalid choice\n";
                    break;
            }

        }
    }


};

int main(){

    Menu m;
    m.LoginMenu();
    m.TaskMenu();
    return 0;
}