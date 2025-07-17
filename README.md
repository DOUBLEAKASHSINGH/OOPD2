# **Hierarchical Issue Escalation Simulator**  
*A C++ system for faculty data retrieval and student query resolution with hierarchical escalation*  

## **📌 Overview**  
This project consists of two core modules:  
1. **Faculty Data Retrieval** – Fetches faculty details (name, department, contact) from text files.  
2. **Issue Escalation System** – Simulates a 3-tier workflow for resolving student queries (TA → Instructor → HOD) with a 3-day delay between escalations.  

Built for academic assignments, it demonstrates **file handling, conditional logic, and workflow automation** in C++.  

## **📂 Project Structure**  
Hierarchical-Escalation-Simulator/
│
├── data/
│ ├── administrative_data.txt # Faculty records (name, room, email, etc.)
│ └── question2_data.txt # Department-wise faculty data
│
├── src/
│ ├── faculty_search.cpp # Searches faculty by name/department
│ └── query_escalation.cpp # Handles student issue escalation logic
│
└── README.md

text

## **⚙️ Features**  
### **1. Faculty Data Retrieval**  
- **Search by Name**: Fetch contact/details of a specific faculty member.  
- **Search by Department**: List all faculty in a given department.  
- *Data Format*: Text files with structured entries (e.g., `Name, RoomNo, Email`).  

### **2. Query Resolution System**  
- **4 Query Types**: Course-related, Guidance, Registration, Other.  
- **Automated Escalation**: Unresolved issues escalate after 3 simulated days.  
- **Hierarchy**:  
  ```mermaid  
  graph LR  
    A[TA/TF] -->|Not resolved| B[Instructor]  
    B -->|Not resolved| C[Head of Department]  
### How to Run
- Compile:
g++ src/faculty_search.cpp -o faculty_search  
g++ src/query_escalation.cpp -o query_escalation  

- Execute:
./faculty_search          # For faculty data lookup  
./query_escalation        # To simulate query resolution  

## Sample Workflow
Faculty Search

Enter faculty name: Arani  
Name: Arani
Room: 505  
Email: arani@uni.edu 

## Query Escalation
Select issue type (1-4): 1 [Course-related]  
Issue unresolved by TA. Escalating to Instructor after 3 days...  

## Dependencies
- C++17 compiler (e.g., g++)
- Text files formatted as per project specs

### License
Academic Free Use. Modify as needed for assignments.

### Key Concepts Demonstrated
File I/O in C++
Conditional escalation logic
Structured data parsing

