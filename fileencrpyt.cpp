                                                 /*************************************************
                                                  **                                             **
                                                  **    FILE MANANGEMENT AND ENCRYPTION SYSTEM   **
                                                  **    PROGRAMMED IN C++                        **
                                                  **    BY PRANAV BHATLAPENUMARTHI               **
                                                  **                                             **
                                                  *************************************************/

                                                 
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string split_space(string st){ // FUNCTION TO SPLIT THE STRING AT WHITESPACES
    istringstream ss(st);
    string word, words[2];
    int i = 0;
    while(ss >> word){
        words[i] = word;
        i++;
    }

    return words[0];
}

void loading(void){ // FUNCTION TO SIMULATE A LOADING PROCESS
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 75000000; j++) {
            i++;
            i--;
        }
        cout << ".";
    }
}

void wait(void){ // FUNCTION TO SIMULATE A WAITING PERIOD
    for(int i = 0; i < 200000; i++){
        i++; i--;
    }
}

class Acc_create{ // CLASS TO CREATE AN ACCOUNT
    string username, password;
    int date, month, year;
public:
    string f_name, l_name;

    void get_data(string firstname, string lastname){
        f_name = firstname;
        l_name = lastname;
        cout << "ENTER DETAILS FOR DATE OF BIRTH\n";
        
        cout << "\tDATE:  "; cin >> date;
        cout << "\tMONTH:  "; cin >> month;
        cout << "\tYEAR:  "; cin >> year;
        if(2024-year < 18){
            cout << "USERS MUST BE ABOVE 18 YEARS TO HAVE AN INDIVIDUAL ACCOUNT." << endl;
            exit(0);
        }
        //display();
        create_acc();
    }

    void create_acc(void){ // FUNCTION TO CREATE USERNAME AND PASSWORD
        cout << "ENTER YOUR USERNAME:  "; cin >> username;
        cout << "YOUR PASSWORD MUST BE AT LEAST 8 CHARACTERS LONG AND MUST CONTAIN AT LEAST ONE SPECIAL CHARACTER\n";
        cout << "ENTER YOUR PASSWORD:  "; cin >> password;
        while(!(password.length() >= 8)){
            cout << "INVALID PASSWORD INPUT. PLEASE TRY AGAIN\n";
            cout << "ENTER YOUR PASSWORD:  "; cin >> password;
        }

        ofstream fp("Acc_details.txt", ios::app);
        fp << username << endl;
        fp << password << endl;
        fp.close();
        account_created();
    }

    void account_created(void){ // FUNCTION TO VERIFY AND CONFIRM ACCOUNT CREATION
        cout << "PLEASE WAIT WHILE WE PROCESS YOUR DATA\n";
        loading();
        cout << "\n\nACCOUNT CREATED SUCCESSFULLY !!" << endl;
        wait();
    }

    friend void account_login(Acc_create acc); // FRIEND FUNCTION DECLARATION
};

void account_login(Acc_create acc){ // FRIEND FUNCTION BODY FOR FIRST TIME LOGIN
    string login_user, login_passwd;
    cout << "\t\t========== LOGIN ==========" << endl;
    cout << "\n\nENTER USERNAME:  "; cin >> login_user;
    cout << "ENTER PASSWORD:  "; cin >>  login_passwd;
    
    while(acc.username != login_user || acc.password != login_passwd){
        cout << "INVALID USERNAME OR PASSWORD. PLEASE TRY AGAIN" << endl;
        cout << "ENTER USERNAME:  "; cin >> login_user;
        cout << "ENTER PASSWORD:  "; cin >>  login_passwd;
    }

    cout << "\nVERIFYING LOGIN CREDENTIALS...\n" << endl;
    loading();

    cout << "\n\nLOGIN SUCCESSFUL !!" << endl;
    wait();

}

void acc_login(void){ // FRIEND FUNCTION BODY FOR LOGIN AFTER FIRST TIME
    ifstream fp("Acc_details.txt", ios::in);
    string login_user, login_passwd, user, pwd;
    cout << "\t\t========== LOGIN ==========" << endl;
    cout << "\n\nENTER USERNAME:  "; cin >> login_user;
    cout << "ENTER PASSWORD:  "; cin >> login_passwd;

    if(fp.is_open()){
        string read, read1;
        getline(fp, read);
        fp.ignore();
        user = read;
        getline(fp, read1);
        pwd = read;
    }

    //cout << user << " " << pwd << endl;

    while(user != login_user){
        cout << "INVALID USERNAME OR PASSWORD. PLEASE TRY AGAIN" << endl;
        cout << "ENTER USERNAME:  "; cin >> login_user;
        cout << "ENTER PASSWORD:  "; cin >>  login_passwd;
    }

    cout << "\nVERIFYING LOGIN CREDENTIALS...\n" << endl;
    loading();

    cout << "\n\nLOGIN SUCCESSFUL !!" << endl;
    wait();
}

class Caeser_Passwd{ // CLASS TO GENERATE PASSWORDS BY IMPLEMENTING CAESAR CIPHER
    public:
    char caeser(char input){
        char output;

        output = input - 5;
        return output;
    }

    char caeser1(char input){
        char output;

        input = toupper(input);
        output = input + 3;

        return output;
    }        
};

class in_acc: public Acc_create{ // INHERITING CLASS "Acc_create" IN PUBLIC MODE
    public:
        void welcome(void){ // FUNCTION TO DISPLAY A WELCOME MSG TO THE USER
            cout << "\t\tWELCOME TO YOUR VERY OWN FILE MANAGEMENT SYSTEM, " << f_name << " " << l_name <<  endl;
            menu();
        }

        void create_file(void);
        void open_file(void);
        void menu(void){
            int choice;
            cout << "HOW CAN WE HELP YOU TODAY??" << endl;
            cout << "1. CREATE NEW FILE\n2. OPEN EXISTING FILE\n3. EXIT" << endl;
            cout << "ENTER YOUR CHOICE:  "; cin >> choice;

            switch(choice){ // INITIALISING SWITCH CASE
                case 1:
                    system("cls");
                    create_file(); 
                    break;
                case 2:
                    system("cls");
                    open_file();
                    break;
                case 3:
                    exit(0);
                    break;
                default:
                    cout << "INVALID CHOICE. PLEASE TRY AGAIN" << endl;
                    cin.ignore();
                    cout << "ENTER YOUR CHOICE:  "; cin >> choice;
            }
        }

};

void in_acc::create_file(void){// FUNCTION TO CREATE A FILE
    string name, password, txt;
    char chk;
    cout << "ENTER THE NAME OF YOUR FILE(ALONG WITH THE EXTENSION):  "; cin >> name;
    cout << "WOULD YOU LIKE THE SYSTEM TO GENERATE A SECURE PASSWORD FOR YOU?" << endl;
    cout << "ENTER Y/y FOR YES AND N/n FOR NO:  "; cin >> chk;

    if (chk == 'y' || chk == 'Y'){ // GENERATING PASSWORD USING CAESER CIPHER
        Caeser_Passwd pswd;

        for(int i = 0; i < f_name.length(); i++){
            password += pswd.caeser(f_name[i]);
        }

        for(int i = 0; i < l_name.length(); i++){
            password += pswd.caeser1(l_name[i]);
        }

        cout << "YOUR PASSWORD IS:  "<< password << endl;
        cout << "PLEASE NOTE IT DOWN !" << endl;

    }

    else{ // MANUALLY RECEIVING PASSWORD AS INPUT FROM THE USER
        cout << "ENTER YOUR PASSWORD: "; cin >> password;
    }

    ofstream fp("files.txt", ios::app); // creation of ofstream class object in append mode
    fp << name << " " << password << endl;
    cout << "YOUR FILE HAS BEEN CREATED !" << endl;
    ofstream fp1(name, ios::app);
    cout << "Type something (this will be stored in your file):" << endl;
    cin.ignore();
    getline(cin, txt);
    fp1 << txt;
    cout << "YOUR DATA HAS BEEN ADDED TO THE FILE !" << endl;
    fp1.close();
    fp.close();

    cout << "TYPE SOMETHING TO RETURN TO MENU PAGE" << endl;
    string ch; cin >> ch;
    system("cls");
    menu();
}

void in_acc::open_file(void){ // FUNCTION TO OPEN AN EXISTING FILE
    string input,st; int flag = 0;
    cout << "ENTER REQUIRED FILE NAME(WITH EXTENSION) AND PASSWORD SEPARATED WITH SPACE: "; 
    cin.ignore();
    getline(cin , input);
    ifstream fp("files.txt", ios::in); // creation of ifstream class object to read the contents of the file
    if(fp.is_open()){
        while(getline(fp, st)){
            if(input == st){
                flag = 1;
                break;
            }
        }
    }
    else{
        cout << "FILE OPENING ERROR" << endl;
    }

    if(flag == 1){ // TO READ THE CONTENT OF SPECIFIED FILE AND DISPLAYING IT
        string name = split_space(input);
        ifstream fp1(name, ios::in);
        if(fp1.is_open()){
            string txt;
            while(getline(fp1, txt)){
                cout << txt << endl;
            }
        }
        fp1.close();
    }

    else{
        cout << "INCORRECT FILE NAME OR PASSWORD" << endl;
    }
    fp.close();

    cout << "TYPE SOMETHING TO RETURN TO MENU PAGE" << endl;
    string ch; cin >> ch;
    system("cls");
    menu();
}

// DRIVER CODE STARTS  

int main(void){

    cout << "\t\tFILE MANAGEMENT AND ENCRYPTION SYSTEM" << endl;
    cout << "1. CREATE NEW ACCOUNT\n2. LOGIN TO EXISTING ACCOUNT" << endl;
    int choice; cin >> choice;
    string first_name, last_name;
    in_acc account;

    switch(choice){
        case 1:
            cout << "ENTER FIRST NAME:  "; cin >> first_name;
            cout << "ENTER LAST NAME:  "; cin >> last_name;
            account.get_data(first_name, last_name);
            system("cls");
            account_login(account);

            system("cls");
            account.welcome();
            break;
        case 2:
            acc_login();
            system("cls");
            account.welcome();
            break;
        default:
            cout << "INVALID INPUT" << endl;
            break;
    }
    
    return 0;
}
