#include <iostream>
#include <string>
#include <vector>
using namespace std;

void handleEscalation(const string& category, int level) {
    vector<string> escalationChain;

    if (category == "Course Related") {
        escalationChain = {"TAs/TFs", "Instructor", "HoD", "DOAA"};
    } else if (category == "Course Guidance") {
        escalationChain = {"Instructor", "Program Coordinator", "HoD", "DOAA"};
    } else if (category == "Registration related") {
        escalationChain = {"JM/AM/DM Academics", "Manager (Academics)", "DOAA"};
    } else if (category == "Other Academic Issues") {
        escalationChain = {"JM/AM/DM Academics", "Manager (Academics)", "HoD", "DOAA"};
    } else {
        cout << "Invalid issue type entered. Please seek assistance.\n";
        return;
    }

    if (level < escalationChain.size()) {
        if (level == 0) {
            cout << "The issue is being forwarded to: " << escalationChain[level] << endl;
        } else {
            cout << escalationChain[level] << "\n";
        }
    }
}

int main() {
    string issueType;
    char resolutionStatus;
    int currentLevel = 0;

    cout << "Enter your issue type (e.g., Course Related, Course Guidance, Registration related, Other Academic Issues): ";
    getline(cin, issueType);

    while (true) {
        if (currentLevel > 0) {
            cout << "It's been 3 days without resolution, escalating the issue to: ";
        }
        handleEscalation(issueType, currentLevel);

        cout << "Has your issue been resolved? (y/n): ";
        cin >> resolutionStatus;

        if (resolutionStatus == 'y' || resolutionStatus == 'Y') {
            cout << "We're glad your issue has been resolved.\n";
            break;
        } else if (resolutionStatus == 'n' || resolutionStatus == 'N') {
            currentLevel++;

            if ((issueType == "Course Related" && currentLevel >= 4) ||
                (issueType == "Course Guidance" && currentLevel >= 4) ||
                (issueType == "Registration related" && currentLevel >= 3) ||
                (issueType == "Other Academic Issues" && currentLevel >= 4)) {
                cout << "Maximum escalation level reached. Please verify the issue type.\n";
                break;
            }
        } else {
            cout << "Invalid response. Please enter 'y' or 'n'.\n";
        }
    }

    return 0;
}
