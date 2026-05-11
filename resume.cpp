#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct ResumeData {
    string name, job, location, phone, email, objective;
    vector<string> experience;
    vector<string> education;
    vector<string> skills;
};

const int LINE_WIDTH = 75;

void printDivider() {
    cout << "\t" << string(LINE_WIDTH, '-') << endl;
}

void printHeader(string name, string job, string loc, string phone, string email) {
    cout << "\n\n\t" << string(LINE_WIDTH, '=') << endl;
    cout << "\t" << name << endl;
    cout << "\t" << job << endl;
    cout << "\t" << loc << " | " << phone << " | " << email << endl;
    cout << "\t" << string(LINE_WIDTH, '=') << endl;
}

void printWrapped(string content, string label = "") {
    int indent = 8;
    int availableWidth = LINE_WIDTH - indent;
    
    if (!label.empty()) {
        cout << "\t" << left << setw(indent) << label;
    } else {
        cout << "\t" << string(indent, ' ');
    }

    size_t start = 0;
    bool firstLine = true;

    while (start < content.length()) {
        if (!firstLine) {
            cout << "\t" << string(indent, ' ');
        }
        
        string line = content.substr(start, availableWidth);
        
        if (line.length() == availableWidth && start + availableWidth < content.length()) {
            size_t lastSpace = line.find_last_of(' ');
            if (lastSpace != string::npos) {
                line = line.substr(0, lastSpace);
            }
        }

        cout << line << endl;
        start += line.length();
        if (start < content.length() && content[start] == ' ') start++;
        firstLine = false;
    }
}

void displayModernResume(const ResumeData& r) {
    printHeader(r.name, r.job, r.location, r.phone, r.email);

    cout << "\n\tOBJECTIVE" << endl;
    printDivider();
    printWrapped(r.objective);

    cout << "\n\tWORK EXPERIENCE" << endl;
    printDivider();
    for (const auto& exp : r.experience) {
        printWrapped(exp, " - ");
    }

    cout << "\n\tEDUCATION" << endl;
    printDivider();
    for (const auto& edu : r.education) {
        printWrapped(edu, " - ");
    }

    cout << "\n\tSKILLS & ABILITIES" << endl;
    printDivider();
    for (const auto& skill : r.skills) {
        printWrapped(skill, " * ");
    }

    cout << "\n\t" << string(LINE_WIDTH, '=') << endl;
}

int main() {
    ResumeData r;
    int choice;

    while (true) {
        cout << "\n========================================" << endl;
        cout << "      MODERN RESUME GENERATOR (C++)     " << endl;
        cout << "========================================" << endl;
        cout << "1. Create / Input Data" << endl;
        cout << "2. Generate Resume" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cout << "[!] Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore();

        if (choice == 1) {
            cout << "\n--- PERSONAL INFORMATION ---" << endl;
            cout << "Full Name: "; getline(cin, r.name);
            cout << "Job Position: "; getline(cin, r.job);
            cout << "Location: "; getline(cin, r.location);
            cout << "Phone: "; getline(cin, r.phone);
            cout << "Email: "; getline(cin, r.email);
            cout << "Objective: "; getline(cin, r.objective);

            auto inputList = [](vector<string>& list, string label) {
                list.clear();
                int n;
                cout << "\nNumber of entries for " << label << ": ";
                while (!(cin >> n)) {
                    cout << "[!] Invalid number. Try again: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                cin.ignore();
                
                for(int i = 0; i < n; i++) {
                    string temp;
                    cout << "  #" << i + 1 << ": ";
                    getline(cin, temp);
                    list.push_back(temp);
                }
            };

            inputList(r.experience, "Experience");
            inputList(r.education, "Education");
            inputList(r.skills, "Skills");
            
            cout << "\n[SUCCESS] Data saved!" << endl;
        } 
        else if (choice == 2) {
            if (r.name.empty()) {
                cout << "\n[!] No data found. Please select option 1 first." << endl;
            } else {
                displayModernResume(r);
            }
        } 
        else if (choice == 3) {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } 
        else {
            cout << "[!] Invalid choice. Select 1-3." << endl;
        }
    }
    return 0;
}