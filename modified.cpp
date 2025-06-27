#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

enum Task_priority {
    Low,
    Medium,
    High
};

enum Completed_status {
    Pending,
    Completed
};

struct Date {
    int year;
    int month;
    int day;

    Date get_today_date(){
        time_t now = time(nullptr);
        tm* now_tm = localtime(&now);
        Date today;
        today.year = now_tm->tm_year + 1900;
        today.month = now_tm->tm_mon + 1;
        today.day = now_tm->tm_mday;
        return today;
    }
};

class Timer {
public:
    int hr;
    int min;
    int sec;

    Timer(int hr,int min,int sec){
        this->hr = hr;
        this->min = min;
        this->sec = sec;
    }

    Timer(){
        this->hr = 0;
        this->min = 0;
        this->sec = 0;
    }

    void StartTimer(){
        int total_sec = hr * 3600 + min * 60 + sec;

        while(total_sec > 0){
            int display_hr = total_sec / 3600;
            int display_min = (total_sec % 3600) / 60;
            int display_sec = total_sec % 60;

            cout << "\r" 
                 << (display_hr < 10 ? "0" : "") << display_hr << " : " 
                 << (display_min < 10 ? "0" : "") << display_min << " : " 
                 << (display_sec < 10 ? "0" : "") << display_sec << flush;

            this_thread::sleep_for(chrono::seconds(1));
            total_sec--;            
        }
        cout << "\nTime's up!\n";
    }
};

class Task {
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
        cout << "Enter task description (- for no description): ";
        getline(cin, description);
        cout << "Enter task priority (low = 0, medium = 1, high = 2): ";
        cin >> priority;
        cout << "Enter task due date (yyyy mm dd): ";
        cin >> due_date.year >> due_date.month >> due_date.day;
        cin.ignore();
    }

    void display_task(){
        const char* Task_priority_array[] = {"Low", "Medium", "High"};
        const char* Completed_status_array[] = {"Pending", "Completed"};
        cout << "Task: " << taskname << '\n';
        cout << "   Description: " << description << '\n';
        cout << "   Deadline: " << due_date.year << "/" << due_date.month << "/" << due_date.day << '\n';
        cout << "   Priority: " << Task_priority_array[priority] << '\n';
        cout << "   Status: " << Completed_status_array[completed] << '\n';
    }

    void start_task(){
        Timer timer;
        cout << "Enter time to complete task (hr min sec): ";
        cin >> timer.hr >> timer.min >> timer.sec;
        display_task();
        timer.StartTimer();
        cin.ignore();
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

class File_manager {
    vector<Task> tasklist;

public:
    void add_task(Task task){
        tasklist.push_back(task);
    }

    void save_tasks(const string &user_filename){
        ofstream outfile(user_filename);
        if(!outfile){
            cout << "Error opening file for save\n";
            return;
        }
        outfile << tasklist.size() << '\n';
        for(int i = 0; i < (int)tasklist.size(); ++i){
            outfile << tasklist[i].taskname << '|'
                    << tasklist[i].description << '|'
                    << tasklist[i].priority << '|'
                    << tasklist[i].completed << '|'
                    << tasklist[i].due_date.year << '-'
                    << tasklist[i].due_date.month << '-'
                    << tasklist[i].due_date.day << '\n';
        }
    }

    vector<Task> load_tasks(const string &user_filename){
        ifstream infile(user_filename);
        if(!infile){
            cout << "File not found\n";
            return {};
        }
        int n;
        infile >> n;
        infile.ignore();
        tasklist.clear();
        for(int i = 0; i < n; ++i){
            Task task;
            string line;
            getline(infile, line);
            stringstream iss(line);
            char sep;

            getline(iss, task.taskname, '|');
            getline(iss, task.description, '|');
            iss >> task.priority >> sep >> task.completed >> sep >> task.due_date.year >> sep >> task.due_date.month >> sep >> task.due_date.day;

            tasklist.push_back(task);
        }
        return tasklist;
    }
};

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

int main(){
    int auth_choice;

    while (true) {
        cout << "------------------------------\n";
        cout << "1. Register User\n";
        cout << "2. Login User\n";
        cout << "3. Exit\n";
        cout << "------------------------------\n";
        cout << "Enter your choice: ";
        cin >> auth_choice;

        if(auth_choice == 1){
            string user_name, password;

            cout << "Enter username: ";
            cin >> user_name;

            cout << "Enter password: ";
            cin >> password;

            ifstream test_file(user_name + "_tasks.txt");
            if(test_file.is_open()) {
                cout << "User already exists!\n";
            } else {
                ofstream new_file(user_name + "_tasks.txt");
                new_file << encryption(password, password.size()) << '\n';
                new_file.close();
                cout << "User registered successfully!\n";
            }
        } else if(auth_choice == 2){
            string user_name, password;

            cout << "Enter username: ";
            cin >> user_name;

            cout << "Enter password: ";
            cin >> password;

            ifstream test_file(user_name + "_tasks.txt");
            if(!test_file.is_open()) {
                cout << "User not found!\n";
            } else {
                string stored_password;
                test_file >> stored_password;

                if(stored_password == encryption(password, password.size())) {
                    test_file.close();

                    int choice = 0;

                    while(choice != 99){
                        cout << '\n';
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
                            case 1: {
                                Timer T;
                                cout << "Enter time (hr min sec): ";
                                cin >> T.hr >> T.min >> T.sec;
                                T.StartTimer();
                                break;
                            }
                            case 2: {
                                Task T;
                                File_manager file;
                                T.input_task();
                                T.display_task();
                                file.add_task(T);
                                file.save_tasks(user_name + "_tasks.txt");
                                break;
                            }
                            case 3: {
                                Task T;
                                T.start_task();
                                break;
                            }
                            case 4: {
                                int count = 1;
                                File_manager fm;
                                vector<Task> tasklist = fm.load_tasks(user_name + "_tasks.txt");
                                for(int i = 0; i < (int)tasklist.size(); ++i){
                                    if(tasklist[i].is_completed() == Pending){
                                        cout << count << ". ";
                                        tasklist[i].display_task();
                                        ++count;
                                    }
                                }
                                break;
                            }
                            case 5: {
                                int count = 1;
                                File_manager fm;
                                vector<Task> tasklist = fm.load_tasks(user_name + "_tasks.txt");
                                for(int i = 0; i < (int)tasklist.size(); ++i){
                                    if(tasklist[i].is_today() && tasklist[i].is_completed() == Pending){
                                        cout << count << ". ";
                                        tasklist[i].display_task();
                                        ++count;
                                    }
                                }
                                break;
                            }
                            case 6: {
                                cout << "Feature not implemented.\n";
                                break;
                            }
                            case 7: {
                                choice = 99;
                                break;
                            }
                            default:
                                cout << "Invalid choice\n";
                        }
                    }
                } else {
                    cout << "Invalid username or password!\n";
                }
            }
        } else if(auth_choice == 3) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
