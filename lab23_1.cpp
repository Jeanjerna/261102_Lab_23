#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include <algorithm>

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

void importDataFromFile(string filename , vector<string> &names , vector<int> &scores , vector<char> &grades)
{
    char format[] = "%[^:]:%d %d %d";
    
    ifstream source(filename);
    string text;
    while(getline(source , text))
    {
        const char *text_char = text.c_str();
        char temp_name[100];
        int a,b,c , temp_score;
        
        sscanf(text_char , format , temp_name , &a , &b , &c);
    
        temp_score = a+b+c;
        names.push_back(temp_name);
        scores.push_back(temp_score);
        grades.push_back(score2grade(temp_score));
    }
}

void getCommand(string &command, string &key)
{
    string input_command;
    
    cout << "Please input your command:\n";
    getline(cin , input_command);
    
    const char *input_command_char = input_command.c_str();
    char format[] = "%s";
    
    char command_split[20];
    
    sscanf(input_command_char , format , command_split);
    
    command = command_split;
    
    int input_len = input_command.size();
    int command_len = command.size();
    
    
    if (command_len != input_len)
    {
        key = input_command.substr((command_len+1));
    }
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    vector<string> names_toupper;
    for(unsigned int i = 0 ; i < names.size() ; i++)
    {
        names_toupper.push_back(toUpperStr(names[i]));
    }
    
    unsigned int index = std::distance(names_toupper.begin() , std::find(names_toupper.begin() , names_toupper.end() , key));
    
    if(index == names_toupper.size())
    {
        cout << "---------------------------------\n" ; 
        cout << "Cannot found.\n";
        cout << "---------------------------------\n" ;
    }
    else
    {
        cout << "---------------------------------\n" ;
        cout << names[index] << "'s score = " << scores[index] << endl;
        cout << names[index] << "'s grade = " << grades[index] << endl;
        cout << "---------------------------------\n" ;
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    int count = 0 ;
    
    cout << "---------------------------------\n" ;
    
    for(unsigned int i = 0 ; i < grades.size() ; i++)
    {
        if(grades[i] == key[0])
        {
            count++;
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }
    
    if(count == 0)
    {
        cout << "Cannot found.\n";
    }
    
    cout << "---------------------------------\n" ;

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