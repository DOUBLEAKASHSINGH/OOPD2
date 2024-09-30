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


// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include <map>
// #include <algorithm>
// using namespace std;

// bool containsSubstring(const string& str, const string& substr) {
//     string str_lower = str;
//     string substr_lower = substr;
//     transform(str_lower.begin(), str_lower.end(), str_lower.begin(), ::tolower);
//     transform(substr_lower.begin(), substr_lower.end(), substr_lower.begin(), ::tolower);

//     return str_lower.find(substr_lower) != string::npos;
// }

// class Faculty {
// protected:
//     string name;
//     string room_number;
//     string telephone;

// public:
//     Faculty(const string& name, const string& room_number, const string& telephone)
//         : name(name), room_number(room_number), telephone(telephone) {}

//     virtual map<string, string> getDetails() const {
//         return {
//             {"Name", name},
//             {"Room Number", room_number},
//             {"Telephone", telephone}
//         };
//     }

//     string getName() const {
//         return name;
//     }
// };

// class HeadOfDepartment : public Faculty {
// public:
//     HeadOfDepartment(const string& name, const string& room_number, const string& telephone)
//         : Faculty(name, room_number, telephone) {}
// };

// class AdministrativeOfficer {
// protected:
//     string name;
//     string room_number;
//     string telephone;

// public:
//     AdministrativeOfficer(const string& name, const string& room_number, const string& telephone)
//         : name(name), room_number(room_number), telephone(telephone) {}

//     map<string, string> getDetails() const {
//         return {
//             {"Name", name},
//             {"Room Number", room_number},
//             {"Telephone", telephone}
//         };
//     }

//     string getName() const {
//         return name;
//     }
// };

// class Department {
// private:
//     string department_name;
//     HeadOfDepartment head;
//     AdministrativeOfficer admin_officer;
//     vector<Faculty> faculty_members;

// public:
//     Department(const string& department_name, const HeadOfDepartment& head, const AdministrativeOfficer& admin_officer, const vector<Faculty>& faculty_members)
//         : department_name(department_name), head(head), admin_officer(admin_officer), faculty_members(faculty_members) {}

//     string getDepartmentName() const {
//         return department_name;
//     }

//     vector<map<string, string>> getAllDetails() const {
//         vector<map<string, string>> details;
//         details.push_back(head.getDetails());
//         details.push_back(admin_officer.getDetails());
//         for (const auto& faculty : faculty_members) {
//             details.push_back(faculty.getDetails());
//         }
//         return details;
//     }
// };

// vector<Department> loadDepartments(const string& file_path) {
//     vector<Department> departments;
//     ifstream file(file_path);
//     string line, department_name, name, position, telephone, email, room_number;

//     while (getline(file, line)) {
//         istringstream iss(line);
//         getline(iss, department_name, ',');
//         getline(iss, name, ',');
//         getline(iss, position, ',');
//         getline(iss, telephone, ',');
//         getline(iss, email, ',');
//         getline(iss, room_number, ',');

//         if (position == "HeadOfDepartment") {
//             HeadOfDepartment hod(name, room_number, telephone);
//             getline(file, line); // Read the next line for the administrative officer
//             istringstream iss2(line);
//             getline(iss2, department_name, ',');
//             getline(iss2, name, ',');
//             getline(iss2, position, ',');
//             getline(iss2, telephone, ',');
//             getline(iss2, email, ',');
//             getline(iss2, room_number, ',');
//             AdministrativeOfficer admin(name, room_number, telephone);

//             vector<Faculty> faculty_members;
//             for (int i = 0; i < 3; ++i) { // Assuming 3 more faculty members
//                 getline(file, line);
//                 istringstream iss3(line);
//                 getline(iss3, department_name, ',');
//                 getline(iss3, name, ',');
//                 getline(iss3, position, ',');
//                 getline(iss3, telephone, ',');
//                 getline(iss3, email, ',');
//                 getline(iss3, room_number, ',');
//                 faculty_members.push_back(Faculty(name, room_number, telephone));
//             }
//             departments.push_back(Department(department_name, hod, admin, faculty_members));
//         }
//     }
//     return departments;
// }

// string toLowerCase(const string& str) {
//     string lower_str = str;
//     transform(lower_str.begin(), lower_str.end(), lower_str.begin(), ::tolower);
//     return lower_str;
// }

// string trim(const string& str) {
//     size_t first = str.find_first_not_of(' ');
//     size_t last = str.find_last_not_of(' ');
//     return str.substr(first, (last - first + 1));
// }

// int main() {
//     string file_path = "question2_data.txt";
//     vector<Department> departments = loadDepartments(file_path);

//     string department_name;
//     cout << "Enter the name of the department: ";
//     getline(cin, department_name);

//     department_name = toLowerCase(trim(department_name));

//     bool found = false;
//     for (const auto& department : departments) {
//     string dept_name_in_list = department.getDepartmentName();
//     cout << "Department Name in List: " << dept_name_in_list << endl; // Print department name for debugging
//     cout << "Comparing: " << dept_name_in_list << " with " << department_name << endl; // Compare the values

//     if (containsSubstring(dept_name_in_list, department_name)) {
//         cout << "Match found: " << dept_name_in_list << " contains " << department_name << endl;
//         found = true;
//         vector<map<string, string>> details = department.getAllDetails();
//         cout << "Details for department " << department_name << ":\n";
//         for (const auto& detail : details) {
//             cout << "Name: " << detail.at("Name") << ", Telephone: " << detail.at("Telephone") << ", Room Number: " << detail.at("Room Number") << "\n";
//         }
//         break;
//     }
// }

//     if (!found) {
//         cout << "No details found for department " << department_name << "\n";
//     }

//     return 0;
// }