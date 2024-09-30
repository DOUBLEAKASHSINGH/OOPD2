#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

bool containsSubstring(const string& str, const string& substr) {
    string str_lower = str;
    string substr_lower = substr;
    transform(str_lower.begin(), str_lower.end(), str_lower.begin(), ::tolower);
    transform(substr_lower.begin(), substr_lower.end(), substr_lower.begin(), ::tolower);

    return str_lower.find(substr_lower) != string::npos;
}


class Faculty {
protected:
    string name;
    string room_number;
    string telephone;

public:
    Faculty() {}
    Faculty(const string& name, const string& room_number, const string& telephone)
        : name(name), room_number(room_number), telephone(telephone) {}

    virtual map<string, string> getDetails() const {
        return {
            {"Name", name},
            {"Room Number", room_number},
            {"Telephone", telephone}
        };
    }

    string getName() const {
        return name;
    }
};

class HeadOfDepartment : public Faculty {
public:
    HeadOfDepartment(){}
    HeadOfDepartment(const string& name, const string& room_number, const string& telephone)
        : Faculty(name, room_number, telephone) {}
};

class AdministrativeOfficer {
protected:
    string name;
    string room_number;
    string telephone;

public:
    AdministrativeOfficer() {}
    AdministrativeOfficer(const string& name, const string& room_number, const string& telephone)
        : name(name), room_number(room_number), telephone(telephone) {}

    map<string, string> getDetails() const {
        return {
            {"Name", name},
            {"Room Number", room_number},
            {"Telephone", telephone}
        };
    }

    string getName() const {
        return name;
    }
};

class Department {
private:
    string department_name;
    HeadOfDepartment head;
    AdministrativeOfficer admin_officer;
    vector<Faculty> faculty_members;

public:
    Department() {}
    Department(const string& department_name, const HeadOfDepartment& head, const AdministrativeOfficer& admin_officer, const vector<Faculty>& faculty_members)
        : department_name(department_name), head(head), admin_officer(admin_officer), faculty_members(faculty_members) {}

    string getDepartmentName() const {
        return department_name;
    }

    void setDepartmentName(const string& name) {
        department_name = name;
    }

    HeadOfDepartment getHead() const {
        return head;
    }

    void setHead(const HeadOfDepartment& head) {
        this->head = head;
    }

    AdministrativeOfficer getAdminOfficer() const {
        return admin_officer;
    }

    void setAdminOfficer(const AdministrativeOfficer& admin_officer) {
        this->admin_officer = admin_officer;
    }

    vector<Faculty> getFacultyMembers() const {
        return faculty_members;
    }

    void setFacultyMembers(const vector<Faculty>& faculty_members) {
        this->faculty_members = faculty_members;
    }

    void addFacultyMember(const Faculty& faculty_member) {
        faculty_members.push_back(faculty_member);
    }

    vector<map<string, string>> getAllDetails() const {
        vector<map<string, string>> details;
        details.push_back(head.getDetails());
        details.push_back(admin_officer.getDetails());
        for (const auto& faculty : faculty_members) {
            details.push_back(faculty.getDetails());
        }
        return details;
    }
};

vector<Department> loadDepartments(const string& file_path) {
    vector<Department> departments;
    ifstream file(file_path);
    string line, department_name, name, position, telephone, email, room_number;

    map<string, Department> department_map;

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, department_name, ',');
        getline(iss, name, ',');
        getline(iss, position, ',');
        getline(iss, telephone, ',');
        getline(iss, email, ',');
        getline(iss, room_number, ',');

        if (department_map.find(department_name) == department_map.end()) {
            department_map[department_name] = Department(department_name, HeadOfDepartment("", "", ""), AdministrativeOfficer("", "", ""), vector<Faculty>());
        }

        if (position.find("Head") != string::npos) {
            department_map[department_name].setHead(HeadOfDepartment(name, room_number, telephone));
        } else if (position.find("Administrative") != string::npos) {
            department_map[department_name].setAdminOfficer(AdministrativeOfficer(name, room_number, telephone));
        } else {
            department_map[department_name].addFacultyMember(Faculty(name, room_number, telephone));
        }
    }

    for (const auto& department : department_map) {
        departments.push_back(department.second);
    }

    return departments;
}

int main() {
    string file_path = "question2_data.txt";
    vector<Department> departments = loadDepartments(file_path);

    string department_name;
    cout << "Enter the department name : ";
    getline(cin, department_name);

    for (const auto& department : departments) {
        if (containsSubstring(department.getDepartmentName(), department_name)) {
            cout << "Department: " << department.getDepartmentName() << endl;
            vector<map<string, string>> details = department.getAllDetails();
            for (const auto& detail : details) {
                for (const auto& pair : detail) {
                    cout << pair.first << ": " << pair.second << endl;
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    return 0;
}