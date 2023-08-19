/*
 * Name: Hadi Abdelaal
 * Class: CS-300
 * 7-1 Final Project
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;


struct course
{
    string code;
    string name;
    queue<string> pre;
public:
    void print()
    {
        cout << "Course code : " << code << endl;
        cout << "Name of the course : " << name << endl;
        bool l = false;
        if (!pre.empty())
        {
            l = true;
            queue<string> temp;
            cout << "Prequisties : ";
            while (!pre.empty())
            {
                cout << pre.front() << " ";
                temp.push(pre.front());
                pre.pop();
            }
            while (!temp.empty())
            {
                pre.push(temp.front());
                temp.pop();
            }

        }
        if(l)
        cout << endl<<endl;
    }

};
class data {
    ifstream file;
    vector<course> courses;
    vector<pair<string,string>> sortedCourses;

    bool load=false;
public:
    bool isLoaded()
    {
        return load;
    }
    void LoadData(string name)
    {
        if(load)
        {
            cout << "File already loaded\n";
            return;
        }
        file.open(name);
        if (file.is_open())
        {
            load = true;
            while (!file.eof())
            {
                string line;
                getline(file,line );

                string word = "";
                int flag = 0;
                course temp;

                for (int i = 0; i < line.length(); i++)
                {
                    if (line[i] != ',' && i != line.length() - 1)
                    {
                        word += line[i];

                    }
                    else
                    {
                        if (i == line.length() - 1)
                            word += line[i];

                        flag++;
                        if (flag == 1)
                        {
                            temp.code = word;
                            word = "";


                        }
                        else if (flag == 2)
                        {
                            temp.name = word;
                            word = "";
                        }
                        else
                        {
                            temp.pre.push(word);
                            word = "";

                        }

                    }
                }

                courses.push_back(temp);
                sortedCourses.push_back(make_pair(temp.code, temp.name));

            }

        }
        else
            cout << "Error openning file\n";

    }

    void printSortedNames()
    {

        cout << "Here is a sample schedule:\n\n";

        sort(sortedCourses.begin(), sortedCourses.end());

        for (auto x : sortedCourses)
        {
            cout << x.first << ", " << x.second << endl;
        }
        cout << endl;
    }

    void getCourse(string word)
    {
        for (int i = 0; i < word.length(); i++)
            if (word[i] >= 'a' && word[i] <= 'z')
                word[i] -= 32;


        for (auto v : courses)
        {
            if (v.code == word)
            {
                v.print();
                return;
            }
        }
        cout << "Course not found!\n";
    }
};

int main()
{

    class data obj;
    int loaded = 0;
    string str;
    cout << "Welcome to The Course Planner!\n";
    cout << "-----------------------------------\n";
    while (true)
    {
        cout << "1. Load Data Structure. " << endl;
        cout << "2. Print Course List. " << endl;
        cout << "3. Print Course. " << endl;
        cout << "4. Exit.\n";
        cout << "What would you like to do? ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (obj.isLoaded())
            {
                cout << "File already loaded\n"; break;
            }
            cout << "\nEnter file name : ";
            cin >> str;
            obj.LoadData(str);
            loaded = obj.isLoaded();
            if (!loaded)
            {
                cout << "Error could not open file\n";
            }
            else
            {
                cout << "File Loaded successfully!\n";
            }
            break;
        case 2:
            if (loaded == 0)
            {
                cout << "File is not loaded\n";
                break;
            }
            else
            {
                obj.printSortedNames();
            }
            break;
        case 3:
            if (loaded == 0)
            {
                cout << "File is not loaded\n";
                break;
            }
            else
            {
                cout << "What course do you want to know about? ";
                string word;
                cin >> word;


                obj.getCourse(word);
                break;
            }

        case 4:
            cout << "Thank you for using the course planner!\n";
            return 0;
            break;
        default:
            cout << "Task not found!\n";
            break;
        }
    }


    return 0;
}

