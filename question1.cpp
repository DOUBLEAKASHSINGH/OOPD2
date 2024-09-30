#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <unordered_map>
using namespace std;

bool containsSubstring(const string& str, const string& substr) {
    string str_lower = str;
    string substr_lower = substr;
    transform(str_lower.begin(), str_lower.end(), str_lower.begin(), ::tolower);
    transform(substr_lower.begin(), substr_lower.end(), substr_lower.begin(), ::tolower);

    return str_lower.find(substr_lower) != string::npos;
}


class AdministrativePersonnel {
protected:
    string name;
    string room_number;
    string telephone;
    string email;

public:
    AdministrativePersonnel(const string& name, const string& room_number, const string& telephone, const string& email)
        : name(name), room_number(room_number), telephone(telephone), email(email) {}

    virtual unordered_map<string, string> getDetails() const {
        return {
            {"Name", name},
            {"Room Number", room_number},
            {"Telephone", telephone},
            {"Email", email}
        };
    }

    string getName() const {
        return name;
    }
};

class Registrar : public AdministrativePersonnel {
public:
    Registrar(const string& name, const string& room_number, const string& telephone, const string& email)
        : AdministrativePersonnel(name, room_number, telephone, email) {}
};

vector<AdministrativePersonnel*> loadAdministrativeData(const string& file_path) {
    vector<AdministrativePersonnel*> personnel_list;
    ifstream file(file_path);
    string line, name, room_number, telephone, email, position;

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, name, ',');
        getline(iss, room_number, ',');
        getline(iss, telephone, ',');
        getline(iss, position, ',');
        getline(iss, email, ',');

        if (position == "Registrar") {
            personnel_list.push_back(new Registrar(name, room_number, telephone, email));
        } else {
            personnel_list.push_back(new AdministrativePersonnel(name, room_number, telephone, email));
        }
    }
    return personnel_list;
}

unordered_map<string, string> fetchDetailsByName(const vector<AdministrativePersonnel*>& personnel_list, const string& name) {    
    for (const auto& personnel : personnel_list) {
        if (containsSubstring(personnel->getName(), name)) {
            return personnel->getDetails();
        }
    }
    return {};
}


int main() {
    string file_path = "administrative_data.txt";
    vector<AdministrativePersonnel*> personnel_list = loadAdministrativeData(file_path);

    string name;
    cout << "Enter the name of the person: ";
    getline(cin, name);

    unordered_map<string, string> details = fetchDetailsByName(personnel_list, name);
    if (!details.empty()) {
        cout << "\nDetails for " << name << ":\n";
        for (const auto& detail : details) {
            cout << detail.first << ": " << detail.second << "\n";
        }
    } else {
        cout << "No details found for " << name << "\n";
    }

    // Clean up dynamically allocated memory
    for (auto& personnel : personnel_list) {
        delete personnel;
    }

    return 0;
}


