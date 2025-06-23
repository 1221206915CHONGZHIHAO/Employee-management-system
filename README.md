Employee Management System
Overview
The Employee Management System is a comprehensive C++ application designed to streamline HR processes, including employee registration, leave management, work logging, and administrative tasks. This system provides separate interfaces for superadmins, administrators, and employees, each with tailored functionalities to meet their specific needs.

Features
Superadmin Features
Admin Management: Register, view, and delete administrators

Employee Records: Add, edit, delete, and search employee details

Comprehensive Oversight: Full access to all system functionalities

Admin Features
Employee Management: Add, edit, and delete employee records

Leave Administration: Approve/reject leave requests and manage leave balances

Reporting: Generate detailed reports on employees and leave statistics

Employee Features
Profile Management: View and update personal information

Worklog System: Record, edit, and track daily tasks

Leave Requests: Submit and track leave applications

Self-Service: Change passwords and generate work reports

Technical Details
Data Structures Used
Dynamic Arrays: For storing and managing employee/admin records

Linked Lists: For efficient leave request management

File Handling: Persistent data storage using text files

Sorting Algorithms: Bubble sort for organizing records

Search Algorithms: Linear and binary search for quick data retrieval

File Structure
employees.txt: Stores employee registration data

employee_details.txt: Contains detailed employee records

credentials.txt: Holds admin login credentials

leave_requests.txt: Manages all leave applications

leave_details.txt: Tracks employee leave balances

worklog_[ID].txt: Individual work logs for each employee

Installation
Prerequisites
C++ compiler (GCC, Clang, or MSVC)

Standard Library support

Basic terminal/command prompt knowledge

Compilation
Clone the repository:

bash
git clone [repository-url]
cd employee-management-system
Compile the source code:

bash
g++ Project_GR8.cpp -o emp_management
Run the executable:

bash
./emp_management
Usage
Initial Setup:

The system comes with a default superadmin account:

Username: ADMIN

Password: ADMIN123#

Main Menu:

Choose between Superadmin, Admin, or Employee login

New employees can register through the main menu

Navigation:

Each user type has a dedicated menu with clear options

Follow on-screen instructions for specific operations

Security Notes
Passwords are stored in plaintext (for educational purposes only)

In a production environment, implement proper password hashing

The system includes basic input validation for critical operations
