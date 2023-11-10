// File Headers to be used:
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <iomanip>
#include <libxl.h>
#include <stdlib.h>

using namespace libxl;
using namespace std;


// Global Variables
string Username, Password, P_ID;
char Selections;
int tries = 0, checker_exist = 0, Options;
const int maximumrow = 10;
string Prisoner_ID[maximumrow];
string Prisoner_NAME[maximumrow];
string Prisoner_LASTNAME[maximumrow];
string Prisoner_SENTENCE[maximumrow];
string Prisoner_TRIAL[maximumrow];
string Prisoner_CRIME[maximumrow];
string Prisoner_RELEASEDATE[maximumrow];

// Security Login
int Log_in() {
    while (tries < 3) {
        cout << "<=============[\033[34mWELCOME ADMIN PRISON MANAGEMENT SYSTEM\033[0m]=============>" << endl;
        cout << "USERNAME: ";
        cin >> Username;
        cout << "PASSWORD: ";
        cin >> Password;

        // Check if the username and password match to continue to the main program
        if (Username == "ADMIN" && Password == "ADMIN") {
            cout << "\033[32mSUCCESS!!\033[0m" << endl;
            sleep(5);
            system("CLS");
            break;
        } else {
            cout << "PLEASE TRY AGAIN!" << endl;
            sleep(1);
            system("CLS");
            tries++;
        }

        if (tries == 3) {
            break;
        }
    }

    return 0;
}

 void Create_record() {
    system("CLS");
    string P_ID, P_NAME, P_LNAME, P_SNTC, P_TRL, P_CRM, P_RD;
    cin.ignore();
    cout << "ENTER PRISONER ID NUM: ";
    getline(cin, P_ID);

    // Check if the ID already exists
    for (int i = 0; i < maximumrow; i++) {
        if (Prisoner_ID[i] == P_ID) {
            cout << "\033[32mDATA HAS ALREADY BEEN ADDED!!\033[0m" << endl;
            return;
        }
    }

    cout << "ENTER PRISONER NAME: ";
    getline(cin, P_NAME);
    cout << "ENTER PRISONER LASTNAME: ";
    getline(cin, P_LNAME);
    cout << "ENTER PRISONER SENTENCE: ";
    getline(cin, P_SNTC);
    cout << "ENTER PRISONER TRIAL DATE: ";
    getline(cin, P_TRL);
    cout << "ENTER PRISONER CRIME/CASE: ";
    getline(cin, P_CRM);
    cout << "ENTER PRISONER RELEASE DATE: ";
    getline(cin, P_RD);

    // Load existing Excel file
    libxl::Book* book = xlCreateXMLBook();
    if (book->load("prisoner_records.xls")) {
        libxl::Sheet* sheet = book->getSheet(0);

        // Find the first empty row
        int emptyRow = -1;
        for (int i = 0; i < maximumrow; i++) {
            if (Prisoner_ID[i].empty()) {
                emptyRow = i;
                break;
            }
        }

        // Check if an empty row was found
        if (emptyRow != -1) {
            Prisoner_ID[emptyRow] = P_ID;
            Prisoner_NAME[emptyRow] = P_NAME;
            Prisoner_LASTNAME[emptyRow] = P_LNAME;
            Prisoner_SENTENCE[emptyRow] = P_SNTC;
            Prisoner_TRIAL[emptyRow] = P_TRL;
            Prisoner_CRIME[emptyRow] = P_CRM;
            Prisoner_RELEASEDATE[emptyRow] = P_RD;

            // Write data to Excel sheet
            sheet->writeStr(emptyRow + 1, 1, P_ID.c_str());
            sheet->writeStr(emptyRow + 1, 2, P_NAME.c_str());
            sheet->writeStr(emptyRow + 1, 3, P_LNAME.c_str());
            sheet->writeStr(emptyRow + 1, 4, P_SNTC.c_str());
            sheet->writeStr(emptyRow + 1, 5, P_TRL.c_str());
            sheet->writeStr(emptyRow + 1, 6, P_CRM.c_str());
            sheet->writeStr(emptyRow + 1, 7, P_RD.c_str());

            book->save("prisoner_records.xls");
            book->release();

            cout << "\033[32mDATA ENTRY HAS BEEN ADDED AND SAVED TO EXCEL FILE!!\033[0m" << endl;
        } else {
            cout << "No empty rows available for new entry." << endl;
        }
    } else {
        cout << "Failed to load Excel file." << endl;
    }
}


void Display_Record() {
    system("CLS");
    cout << setw(112) << "|<---\033[32mDATA BASE RECORD OF PRISONER\033[0m--->|" << endl;
    for (int i = 0; i < 177; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "---------ID---------|---------NAME---------|---------LASTNAME---------|---------SENTENCE---------|---------TRIAL---------|---------CRIME---------|---------RELEASEDATE---------|" << endl;

    int checker_exist = 0; // Reset the checker_exist variable

    for (int i = 0; i < maximumrow; i++) {
                if (!Prisoner_ID[i].empty()) {
            cout << "\t" << Prisoner_ID[i] << setw(15);
            cout << "\t" << Prisoner_NAME[i]<< setw(15);
            cout << "\t" <<  Prisoner_LASTNAME[i]<< setw(15);
            cout << "\t" <<  Prisoner_SENTENCE[i]<< setw(15);
            cout << "\t" <<  Prisoner_TRIAL[i]<< setw(15);
            cout << "\t" <<  Prisoner_CRIME[i];
            cout << "\t" << Prisoner_RELEASEDATE[i] << endl;
            checker_exist++;
        }
    }

    if (checker_exist == 0) {
        cout << "\033[32mNo records found!\033[0m" << endl;
    }

    for (int i = 0; i < 177; i++) {
        cout << "-";
    }
    cout << endl;
}

void Search_Record(string Search){
 system("CLS");
    cout << setw(112) << "|<---\033[32mDATA BASE RECORD OF PRISONER\033[0m--->|" << endl;
    for (int i = 0; i < 177; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "---------ID---------|---------NAME---------|---------LASTNAME---------|---------SENTENCE---------|---------TRIAL---------|---------CRIME---------|---------RELEASEDATE---------|" << endl;

    int checker_exist = 0;

    for (int i = 0; i < maximumrow; i++) {
                if (Prisoner_ID[i] == Search) {
            cout << "\t" << Prisoner_ID[i] << setw(15);
            cout << "\t" << Prisoner_NAME[i]<< setw(15);
            cout << "\t" <<  Prisoner_LASTNAME[i]<< setw(15);
            cout << "\t" <<  Prisoner_SENTENCE[i]<< setw(15);
            cout << "\t" <<  Prisoner_TRIAL[i]<< setw(15);
            cout << "\t" <<  Prisoner_CRIME[i];
            cout << "\t" << Prisoner_RELEASEDATE[i] << endl;
            checker_exist++;
        }
    }

    if (checker_exist == 0) {
        cout << "\033[32mNo records found!\033[0m" << endl;
    }

    for (int i = 0; i < 177; i++) {
        cout << "-";
    }
    cout << endl;


}











int main() {

    while (Options != 6) {
        cout << "[\033[31mP\033[0m]RISON [\033[31mM\033[0m]ANAGEMENT MAIN-MENU" << endl;
        cout << "1.CREATE A RECORD" << endl;
        cout << "2.UPDATE A RECORD" << endl;
        cout << "3.DELETE A RECORD" << endl;
        cout << "4.SEARCH A RECORD" << endl;
        cout << "5.DISPLAY ALL RECORDS" << endl;
        cout << "6.LOGOUT AND SAVE UPDATES TO EXECEL" << endl;
        cout << "ENTER COMMAND:";
        cin >> Options;

        // SYSTEM FUNCTIONS
        switch (Options) {
            case 1:
                Create_record();
                break;
            case 2:
                cout << "2.UPDATE A RECORD" << endl;
                break;
            case 3:
                cout << "3.DELETE A RECORD" << endl;
                break;
            case 4:
                cout << " [S]EARCH BY ID [N]UMBER: " << endl;
                cout << "ENTER COMMAND: " << endl;
                getline(cin, P_ID);
                Search_Record(P_ID);
                break;
            case 5:
                Display_Record();
                cout << "[\033[32mR\033[0m]RETURN TO MAIN MENU SCREEN OR [\033[32mL\033[0m]LOGOUT" << endl;
                cout << "ENTER COMMAND: ";
                cin >> Selections;
                if (Selections == 'R' || Selections == 'r') {
                    system("CLS");
                    main();
                }else if (Selections == 'L' || 'l'){
                  exit(1);
                  break;
                }
            case 6:
                break;
            default:
                cout << "INVALID INPUT" << endl;
                return main();
        }

        sleep(1);
        system("CLS");
    }
}

