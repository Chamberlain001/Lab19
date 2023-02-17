#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin(filename);
    string textline;
    while(getline(fin, textline)){
        char format[] = "%[^:]: %d %d %d";
        int a, b, c, score;
        char name[100];
        sscanf(textline.c_str(), format, name, &a, &b, &c);
        score = a + b + c;
        names.push_back(name);
        scores.push_back(score);
        grades.push_back(score2grade(score));
    }
    fin.close();
}

void getCommand(string &command, string &key){
    string text;
    char format[] = "%s %[^\n]";
    char x[100], y[100];
    cout << "Please input your command: ";
    getline(cin, text);
    sscanf(text.c_str(), format, x, y);
    command = x;
    key = y;
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int length = names.size(), counter = 0;
    for(int i = 0; i < length; i++){
        if(key == toUpperStr(names[i])){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
        }else counter++;
    }
    if(counter == length){
        cout << "---------------------------------\n";
        cout << "Cannot found." << "\n";
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    int length = grades.size(), counter = 0;
    cout << "---------------------------------\n";
    for(int i = 0; i < length; i++){
        string s(1, grades[i]);
        if(key == s){
            cout << names[i] << " (" << scores[i] << ")\n";
        }else counter++;
    }
    if(counter == length){
        cout << "Cannot found." << "\n";
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
