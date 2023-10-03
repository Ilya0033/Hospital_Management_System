#include <bits/stdc++.h>
using namespace std;

void Menu();

void Password()
{
    string pass;
    cout << "          PLEASE ENTER A PASSWORD:" << "\n          ";
    cin >> pass;

    string s;
    ifstream file("password.txt");

    while (getline(file, s))
    {
        if (s == pass)
        {
            system("cls");
            cout << "     CORRECT!";
            this_thread::sleep_for(chrono::milliseconds(1999));
            system("cls");
            Menu();
            break;
        }
        else
        {
            while (s != pass)
            {
                cout << "INCORRECT PASSWORD, TRY AGAIN: "; cin >> pass;
            }
            system("cls");
            cout << "     CORRECT!";
            this_thread::sleep_for(chrono::milliseconds(1917));
            system("cls");
            Menu();
            break;
        }
    }
    file.close();
}

void Change_Password()
{
    system("cls");
    string new_pass;
    cout << "\n              WRITE NEW PASSWORD: "; cin >> new_pass;
    ofstream file;
    file.open("password.txt");
    if (file.is_open())
    {
        file << new_pass;
        system("cls");
        cout << "\n              PASSWORD SUCCESSFULLY CHANGED!";
        this_thread::sleep_for(chrono::milliseconds(1999));
        system("cls");
    }
    else {
        cout << "FILE NOT FOUND";
        system("pause");
    }
    file.close();
}

class People
{
protected:
    string fir_name, last_name, age, phone_number, salary;
public:
    People(string age, string salary, string fir_name, string last_name, string phone_number)
    {
        this->age= age;
        this->salary= salary;
        this->fir_name= fir_name;
        this->last_name= last_name;
        this->phone_number= phone_number;
    }
    virtual void Info() = 0;
};

class Patient: public People
{
private:
    string diagnosis, work_place;
    vector <string> med_hist;
public:
    Patient(string age, string salary, string fir_name,string last_name, string work_place, string phone_number, string diagnosis): People(age, salary, fir_name, last_name, phone_number)
    {
        this->diagnosis= diagnosis;
        this->work_place = work_place;
    }

    void add_disease(string disease) /// IN DEVELOPING...
    {
        med_hist.emplace_back(disease);
    }

    void Info_ab_med_hist() /// IN DEVELOPING...
    {
        for (auto it:med_hist)
        {
            cout << it <<"\n";
        }
    }

    void Info() override
    {
        cout << "First name: " << this->fir_name << "\n\n";
        cout << "Last name: " << this->last_name << "\n\n";
        cout << "Age: " << this->age << "\n\n";
        cout << "Salary: " << this->salary << "\n\n";
        cout << "Diagnosis: " << this->diagnosis << "\n\n";
        cout << "Place of work: " << this->work_place << "\n\n";
        cout << "Phone Number: " << this->phone_number << "\n\n\n";
    }

    friend void find_pat(string f_n, string l_n);

};

class Doctor : public People
{
private:
    string working_time, specializ;

public:
    Doctor(string age, string salary, string fir_name, string last_name, string phone_number, string working_time, string specializ): People(age, salary, fir_name ,last_name,phone_number)
    {
        this->specializ= specializ;
        this->working_time= working_time;
    }
    void Info() override
    {
        cout << "First name: " << this->fir_name << "\n\n";
        cout << "Last name: " << this->last_name << "\n\n";
        cout << "Age: " << this->age << "\n\n";
        cout << "Specialization: " << this->specializ << "\n\n";
        cout << "Working Time: " << this->working_time << "\n\n";
        cout << "Salary: " << this->salary << "\n\n";
        cout << "Phone Number: " << this->phone_number << "\n\n\n";
    }

    friend void find_doc(string f_n, string l_n);
};



vector<Doctor> doctors;
int kol_doc;

vector<Patient> patients;
int kol_pat;

void read_doc_file()
{
    kol_doc = 0;
    ifstream file;
    file.open("doctors.txt");
    string age,fir_name, last_name, specializ, time_working, salary, phone_num;
    if (file.is_open())
    {
        while (!file.eof())
        {
            fir_name = "";
            file >> fir_name >> last_name >> age >> specializ >> time_working >> salary >> phone_num;
            if (fir_name == "") break;
            doctors.emplace_back(Doctor(age, salary, fir_name, last_name, phone_num, time_working, specializ));
            kol_doc++;
        }
    }
    else
    {
        cout << "FILE NAMED 'doctors.txt' NOT FOUND" << "\n\n";
        system("pause");
    }
    file.close();
}

void Info_about_all_doc()
{
    for (int i = 0; i < kol_doc; i++)
    {
        doctors[i].Info();
        cout << "\n";
    }
    //cout << kol_doc;
}

void read_pat_file()
{
    kol_pat = 0;///
    ifstream file;
    file.open("patients.txt");
    string fir_name, last_name, age, diagnoz , work_place, salary, phone_num;
    if (file.is_open())
    {
        while (!file.eof())
        {
            fir_name = "";
            file >> fir_name >> last_name >> age >> salary >> diagnoz >> work_place >> phone_num;
            if (fir_name == "") break;
            patients.emplace_back(Patient(age, salary, fir_name, last_name, work_place, phone_num, diagnoz));
            kol_pat++;
        }
    }
    else
    {
        cout << "FILE NAMED 'patients.txt' NOT FOUND" << "\n\n";
        system("pause");
    }
    file.close();
}

void Info_about_all_pat()
{
    for (int i = 0; i < kol_pat; i++)
    {
        patients[i].Info();
        cout << "\n";
    }
    //cout << kol_pat;
}


void Add_Patient(string f_n, string l_n, string age, string sal, string diag, string w_pl, string ph_num)
{
    ofstream file;
    file.open("patients.txt",ofstream::app);
    if (file.is_open())
    {
        file << "\n" << f_n << " " << l_n << " " << age << " " << sal << " " << diag << " " << w_pl << " " << ph_num;
    }
    else {
        cout << "ERROR FOR FOUND FILE";
        system("pause");
    }
    file.close();

    patients.erase(patients.begin(), patients.end());
    patients.shrink_to_fit();

    read_pat_file();

}

void Add_Doctor(string f_n, string l_n, string age, string special, string w_t, string sal, string ph_num)
{
    ofstream file;
    file.open("doctors.txt",ofstream::app);

    if (file.is_open())
    {
        file << "\n" << f_n << " " << l_n << " " << age << " " << special << " " << w_t << " " << sal << " " << ph_num;
    }
    else {
        cout << "ERROR FOR FOUND FILE";
        system("pause");
    }
    file.close();

    doctors.erase(doctors.begin(), doctors.end());
    doctors.shrink_to_fit();

    read_doc_file();
}

void find_pat(string f_n, string l_n)
{
    int c = 0;
    for (int i = 0; i < kol_pat; i++)
    {
        if (f_n == patients[i].fir_name && l_n == patients[i].last_name)
        {
            c=1;
            patients[i].Info();
        }
    }
    if (c == 0)
    {
        cout << "     NO SUCH PATIENT FOUND :(";
    }
}

void find_doc(string f_n, string l_n)
{
    int c = 0;
    for (int i = 0; i < kol_doc; i++)
    {
        if (f_n == doctors[i].fir_name && l_n == doctors[i].last_name)
        {
            c=1;
            doctors[i].Info();
        }
    }
    if (c == 0)
    {
        cout << "     NO SUCH DOCTOR FOUND :(";
    }
}


void Menu()
{
    system("cls");
    cout << "\n\n\n";
    cout << "          :    ***************   MAIN MENU   ***************    :" << "\n";
    cout << "          :              Hospital Management System             :" << "\n";
    cout << "          :=====================================================:" << "\n\n";
    cout << "-----------------------------------------------------------------------------------" << "\n\n";
    cout << "                          PLEASE SELECR ANY OPTION" << "\n\n";
    cout << "      PRESS '1' TO CHANGE PASSWORD   \n\n";
    cout << "      PRESS '2' TO GET INFORMATION ABOUT ALL DOCTORS   \n\n";
    cout << "      PRESS '3' TO GET INFORMATION ABOUT ALL PATIENT   \n\n";
    cout << "      PRESS '4' TO ADD NEW PATIENT   \n\n";
    cout << "      PRESS '5' TO ADD NEW DOCTOR   \n\n";
    cout << "      PRESS '6' TO FIND PATIENT   \n\n";
    cout << "      PRESS '7' TO FIND DOCTOR   \n\n";
    cout << "      PRESS '8' TO LOGOUT   \n\n";

    string choise;
    cin >> choise;

    if (choise == "1")
    {
        Change_Password();
        Menu();
    }
    if (choise == "2")
    {
        system("cls");
        Info_about_all_doc();
        cout << "PRESS '1' TO CONTINUE AND '2' TO LOGOUT  \n   ";
        cin >> choise;
        if (choise == "1") Menu(); else { system("cls"); exit(0); }
    }
    if (choise == "3")
    {
        system("cls");
        Info_about_all_pat();
        cout << "PRESS '1' TO CONTINUE AND '2' TO LOGOUT  \n   ";
        cin >> choise;
        if (choise == "1") Menu(); else { system("cls"); exit(0); }
    }
    if (choise == "4")
    {
        string f_n, l_n, age,  sal,  diag,  w_pl, ph_num;
        system("cls");
        cout << "  ENTER PATIENT FIRST NAME: "; cin >> f_n;
        cout << "  ENTER PATIENT LAST NAME: "; cin >> l_n;
        cout << "  ENTER PATIENT AGE: "; cin >> age;
        cout << "  ENTER PATIENT SALARY: "; cin >> sal;
        cout << "  ENTER PATIENT DIAGNOSIS: "; cin >> diag;
        cout << "  ENTER PATIENT WORK PLACE: "; cin >> w_pl;
        cout << "  ENTER PATIENT PHONE NUMBER: "; cin >> ph_num;
        Add_Patient(f_n, l_n, age, sal, diag, w_pl, ph_num);
        system("cls");
        cout << "\n\n PATIENT WAS SUCCESSFULLY ADDED! ";
        this_thread::sleep_for(chrono::milliseconds(2599));
        Menu();
    }
    if (choise == "5")
    {
        string f_n,  l_n,  age,  special,  w_t,  sal,  ph_num;
        system("cls");
        cout << "  ENTER DOCTOR FIRST NAME: "; cin >> f_n;
        cout << "  ENTER DOCTOR LAST NAME: "; cin >> l_n;
        cout << "  ENTER DOCTOR AGE: "; cin >> age;
        cout << "  ENTER DOCTOR SPECIALIZATION: "; cin >> special;
        cout << "  ENTER DOCTOR SALARY: "; cin >> sal;
        cout << "  ENTER DOCTOR WORK TIME: "; cin >> w_t;
        cout << "  ENTER DOCTOR PHONE NUMBER: "; cin >> ph_num;
        Add_Doctor(f_n, l_n, age, special, w_t, sal, ph_num);
        system("cls");
        cout << "\n\n DOCTOR WAS SUCCESSFULLY ADDED! ";
        this_thread::sleep_for(chrono::milliseconds(2599));
        Menu();
    }
    if (choise == "6")
    {
        string f_n , l_n;
        system("cls");
        cout << "  ENTER PATIENT FIRST NAME: "; cin >> f_n;
        cout << "  ENTER PATIENT LAST NAME: "; cin >> l_n;
        system("cls");
        cout << "   SEARCH...";
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("cls");
        find_pat(f_n, l_n); cout << "\n\n";
        cout << "  PRESS '1' TO CONTINUE AND '2' TO LOGOUT  \n   ";
        cin >> choise;
        if (choise == "1") Menu(); else { system("cls"); exit(0); }
    }
    if (choise == "7")
    {
        string f_n , l_n;
        system("cls");
        cout << "  ENTER DOCTOR FIRST NAME: "; cin >> f_n;
        cout << "  ENTER DOCTOR LAST NAME: "; cin >> l_n;
        system("cls");
        cout << "   SEARCH...";
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("cls");
        find_doc(f_n, l_n); cout << "\n\n";
        cout << "  PRESS '1' TO CONTINUE AND '2' TO LOGOUT  \n   ";
        cin >> choise;
        if (choise == "1") Menu(); else { system("cls"); exit(0); }
    }
    if (choise == "8")
    {
        system("cls"); exit(0);
    }
}


int main()
{
    read_doc_file();
    read_pat_file();

    Password();
    Menu();

    return 0;
}
