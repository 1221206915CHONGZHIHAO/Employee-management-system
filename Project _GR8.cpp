#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Profile {
    char fullName[100];
    char email[100];
    char phone[20];
};

struct Record {
    int id;
    char name[50];
    char department[50];
    double salary;
};

struct Worklog {
    int id;
    char task[100];
    char date[20];
};

struct Leave {
    char startDate[20];
    int duration;
    char reason[200];
    
};

struct EmployeeDetail {
    string id;
    string name;
    string position;
    float basicSalary;
    string joinDate;
    string department;
    
    void display() const {
        cout << "\nEmployee Details:\n";
        cout << "ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Position: " << position << "\n";
        cout << "Basic Salary: " << basicSalary << "\n";
        cout << "Join Date: " << joinDate << "\n";
        cout << "Department: " << department << "\n";
    }
    
    string serialize() const {
        return id + "," + name + "," + position + "," + 
               to_string(basicSalary) + "," + joinDate + "," + department;
    }
    
    static EmployeeDetail deserialize(const string& data) {
        EmployeeDetail emp;
        size_t pos = 0;
        size_t next_pos = data.find(',', pos);
        emp.id = data.substr(pos, next_pos - pos);
        
        pos = next_pos + 1;
        next_pos = data.find(',', pos);
        emp.name = data.substr(pos, next_pos - pos);
        
        pos = next_pos + 1;
        next_pos = data.find(',', pos);
        emp.position = data.substr(pos, next_pos - pos);
        
        pos = next_pos + 1;
        next_pos = data.find(',', pos);
        emp.basicSalary = stod(data.substr(pos, next_pos - pos));
        
        pos = next_pos + 1;
        next_pos = data.find(',', pos);
        emp.joinDate = data.substr(pos, next_pos - pos);
        
        emp.department = data.substr(next_pos + 1);
        
        return emp;
    }
};

struct RegisteredEmployee {
    string id;
    string name;
    string password;
    
    string serialize() const {
        return id + "," + name + "," + password;
    }
    
    static RegisteredEmployee deserialize(const string& data) {
        RegisteredEmployee emp;
        size_t pos = 0;
        size_t next_pos = data.find(',', pos);
        emp.id = data.substr(pos, next_pos - pos);
        
        pos = next_pos + 1;
        next_pos = data.find(',', pos);
        emp.name = data.substr(pos, next_pos - pos);
        
        emp.password = data.substr(next_pos + 1);
        
        return emp;
    }
    
    bool equals(const RegisteredEmployee& other) const {
        return id == other.id && name == other.name && password == other.password;
    }
};

struct LeaveRecord {
    string employeeId;
    string leaveType;
    int leaveDays;
    string startDate;
    string status;
    string reason;
};

struct LeaveRequest {
    string employeeId;
    string employeeName;
    string leaveType;
    string startDate;
    int leaveDays;
    string reason;
    string status;
};

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;
    
    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
    
public:
    DynamicArray() : capacity(10), size(0) {
        data = new T[capacity];
    }
    
    ~DynamicArray() {
        delete[] data;
    }
    
    void push_back(const T& value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }
    
    T& operator[](int index) {
        return data[index];
    }
    
    const T& operator[](int index) const {
        return data[index];
    }
    
    int getSize() const {
        return size;
    }
    
    void erase(int index) {
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
    
    bool contains(const T& value) const {
        for (int i = 0; i < size; i++) {
            if (data[i].equals(value)) {
                return true;
            }
        }
        return false;
    }
    
    void clear() {
        delete[] data;
        capacity = 10;
        size = 0;
        data = new T[capacity];
    }
};

class User {
protected:
    string id;
    string name;
    string password;
    
public:
    User(string id = "", string name = "", string password = "")
        : id(id), name(name), password(password) {}
    
    virtual ~User() {}
    
    string getId() const { return id; }
    string getName() const { return name; }
    string getPassword() const { return password; }
    
    void setName(const string& newName) { name = newName; }
    void setPassword(const string& newPassword) { password = newPassword; }
    
    virtual void display() const {
        cout << "ID: " << id << "\n";
        cout << "Name: " << name << "\n";
    }
};

class FileHandler {
protected:
    virtual void loadData() = 0;
    virtual void saveData() = 0;
    
    void splitString(const string& str, char delimiter, string* tokens, int maxTokens) {
        size_t start = 0;
        size_t end = str.find(delimiter);
        int tokenCount = 0;
        
        while (end != string::npos && tokenCount < maxTokens - 1) {
            tokens[tokenCount++] = str.substr(start, end - start);
            start = end + 1;
            end = str.find(delimiter, start);
        }
        
        if (tokenCount < maxTokens) {
            tokens[tokenCount] = str.substr(start);
        }
    }
    
public:
    virtual ~FileHandler() {}
    
    void clearInputBuffer() {
        cin.ignore(1000, '\n');
    }
};

struct Superadmin {
    string username;
    string password;
    
    string serialize() const {
        return username + "," + password;
    }
    
    static Superadmin deserialize(const string& data) {
        Superadmin sa;
        size_t pos = data.find(',');
        sa.username = data.substr(0, pos);
        sa.password = data.substr(pos + 1);
        return sa;
    }
};

class Admin : public User {
private:
    string phone;
    string email;

public:
    Admin(string id = "", string name = "", string password = "", 
          string phone = "", string email = "")
        : User(id, name, password), phone(phone), email(email) {}

    string getPhone() const { return phone; }
    string getEmail() const { return email; }

    void setPhone(const string& newPhone) { phone = newPhone; }
    void setEmail(const string& newEmail) { email = newEmail; }

    void display() const override {
        cout << "\nAdmin Details:\n";
        User::display();
        cout << "Phone: " << phone << "\n";
        cout << "Email: " << email << "\n";
    }

    string serialize() const {
        return User::getId() + "," + User::getName() + "," + 
               User::getPassword() + "," + phone + "," + email;
    }

    static Admin deserialize(const string& data) {
        string tokens[5];
        size_t start = 0;
        size_t end = data.find(',');
        int tokenCount = 0;
        
        while (end != string::npos && tokenCount < 4) {
            tokens[tokenCount++] = data.substr(start, end - start);
            start = end + 1;
            end = data.find(',', start);
        }
        tokens[tokenCount] = data.substr(start);
        
        return Admin(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
    }
};

class EmployeeManager : public User, public FileHandler {
private:
    DynamicArray<EmployeeDetail> employees;
    DynamicArray<RegisteredEmployee> registeredEmployees;
    const string registeredFilename = "employees.txt";
    const string detailsFilename = "employee_details.txt";
    
    void sortById() {
        for (int i = 0; i < employees.getSize() - 1; i++) {
            for (int j = 0; j < employees.getSize() - i - 1; j++) {
                if (employees[j].id > employees[j + 1].id) {
                    EmployeeDetail temp = employees[j];
                    employees[j] = employees[j + 1];
                    employees[j + 1] = temp;
                }
            }
        }
    }
    
    int searchById(const string& id) {
        for (int i = 0; i < employees.getSize(); i++) {
            if (employees[i].id == id) {
                return i;
            }
        }
        return -1;
    }
    
    void loadRegisteredEmployees() {
        registeredEmployees.clear();
        ifstream regFile(registeredFilename);
        if (regFile.is_open()) {
            string line;
            while (getline(regFile, line)) {
                if (!line.empty()) {
                    RegisteredEmployee emp = RegisteredEmployee::deserialize(line);
                    registeredEmployees.push_back(emp);
                }
            }
            regFile.close();
        }
    }
    
    void loadData() override {
        employees.clear();
        ifstream detFile(detailsFilename);
        if (detFile.is_open()) {
            string line;
            while (getline(detFile, line)) {
                if (!line.empty()) {
                    employees.push_back(EmployeeDetail::deserialize(line));
                }
            }
            detFile.close();
        }
        
        loadRegisteredEmployees();
        sortById();
    }
    
    void saveData() override {
        ofstream regFile(registeredFilename);
        if (regFile.is_open()) {
            for (int i = 0; i < registeredEmployees.getSize(); i++) {
                if (!registeredEmployees[i].id.empty()) {
                    regFile << registeredEmployees[i].serialize() << "\n";
                }
            }
            regFile.close();
        }
        
        ofstream detFile(detailsFilename);
        if (detFile.is_open()) {
            for (int i = 0; i < employees.getSize(); i++) {
                if (!employees[i].id.empty()) {
                    detFile << employees[i].serialize() << "\n";
                }
            }
            detFile.close();
        }
    }
    
    bool isEmployeeRegistered(const string& id) {
        for (int i = 0; i < registeredEmployees.getSize(); i++) {
            if (registeredEmployees[i].id == id) {
                return true;
            }
        }
        return false;
    }
    
    string getRegisteredEmployeeName(const string& id) {
        for (int i = 0; i < registeredEmployees.getSize(); i++) {
            if (registeredEmployees[i].id == id) {
                return registeredEmployees[i].name;
            }
        }
        return "";
    }
    
public:
    EmployeeManager() {
        loadData();
    }
    
    ~EmployeeManager() {
        saveData();
    }
    
    void addNewEmployee() {
        string inputId;
        
        cout << "\n--- Add New Employee Details ---\n";
        cout << "Enter Employee ID: ";
        cin >> inputId;
        
        loadRegisteredEmployees();
        
        if (!isEmployeeRegistered(inputId)) {
            cout << "No registered employee found with ID: " << inputId << "\n";
            return;
        }
        
        if (searchById(inputId) != -1) {
            cout << "Employee details already exist for ID: " << inputId << "\n";
            displayAllEmployees();
            system("cls");
            return;
        }
        
        EmployeeDetail emp;
        emp.id = inputId;
        emp.name = getRegisteredEmployeeName(inputId);
        
        clearInputBuffer();
        
        cout << "Employee Name: " << emp.name << endl;
        cout << "Enter Position: ";
        getline(cin, emp.position);
        
        cout << "Enter Basic Salary: ";
        cin >> emp.basicSalary;
        clearInputBuffer();
        
        cout << "Enter Join Date (DD/MM/YYYY): ";
        getline(cin, emp.joinDate);
        
        cout << "Enter Department: ";
        getline(cin, emp.department);
        
        employees.push_back(emp);
        sortById();
        saveData();
        cout << "Employee details added successfully!\n\n";
        system("pause");
        system("cls");
    }
    
    void editEmployee() {
        string empId;
        cout << "\n--- Edit Employee Record ---\n";
        cout << "Enter Employee ID: ";
        cin >> empId;
        
        int index = searchById(empId);
        if (index == -1) {
            cout << "Employee details not found for ID: " << empId << "\n";
            return;
        }
        
        EmployeeDetail& emp = employees[index];
        
        clearInputBuffer();
        
        cout << "Current Position: " << emp.position << endl;
        cout << "Enter new Position: ";
        getline(cin, emp.position);
        
        cout << "Current Basic Salary: " << emp.basicSalary << endl;
        cout << "Enter new Basic Salary: ";
        cin >> emp.basicSalary;
        clearInputBuffer();
        
        cout << "Current Join Date: " << emp.joinDate << endl;
        cout << "Enter new Join Date: ";
        getline(cin, emp.joinDate);
        
        cout << "Current Department: " << emp.department << endl;
        cout << "Enter new Department: ";
        getline(cin, emp.department);
        
        saveData();
        cout << "Employee record updated successfully!\n\n";
        system("pause");
        system("cls");
    }
    
    void deleteEmployee() {
        string empId;
        cout << "\nEnter Employee ID to delete: ";
        cin >> empId;
        
        int index = searchById(empId);
        if (index == -1) {
            cout << "Employee not found!\n";
            return;
        }
        
        employees.erase(index);
        saveData();
        cout << "Employee details deleted successfully!\n\n";
        system("pause");
        system("cls");
    }
    
    void displayAllEmployees() {
        if (employees.getSize() == 0) {
            cout << "\nNo employees found!\n";
            return;
        }
        
        cout << "\n--- Employee List ---\n";
        for (int i = 0; i < employees.getSize(); i++) {
            employees[i].display();
            cout << "----------------------\n";
        }
        system("pause");
        system("cls");
    }
    
    void searchEmployeeById(const string& id) {
        int index = searchById(id);
        if (index != -1) {
            cout << "\nEmployee Found:\n";
            employees[index].display();
        } else {
            cout << "Employee not found with ID: " << id << "\n";
        }
        cout << "\n";
        system("pause");
        system("cls");
    }
};

class AdminManager : public User, public FileHandler {
private:
    DynamicArray<Admin> admins;
    const string adminFilename = "credentials.txt";
    
    void loadData() override {
        admins.clear();
        ifstream file(adminFilename);
        if (!file.is_open()) {
            return;
        }

        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                Admin admin = Admin::deserialize(line);
                admins.push_back(admin);
            }
        }
        file.close();
    }
    
    void saveData() override {
        ofstream file(adminFilename);
        if (!file.is_open()) {
            return;
        }

        for (int i = 0; i < admins.getSize(); i++) {
            file << admins[i].serialize() << "\n";
        }
        file.close();
    }
    
    string generateAdminId() {
        int maxId = 1000;
        for (int i = 0; i < admins.getSize(); i++) {
            string idStr = admins[i].getId().substr(1);
            int currentId = atoi(idStr.c_str());
            if (currentId > maxId) maxId = currentId;
        }
        return "A" + to_string(maxId + 1);
    }
    
public:
    AdminManager() {
        loadData();
    }
    
    ~AdminManager() {
        saveData();
    }
    
    int getSize() const {
    return admins.getSize();
}
	
	void registerAdmin() {
        string name, password, phone, email;

        cout << "\n--- Admin Registration ---\n";
        clearInputBuffer();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Password: ";
        getline(cin, password);

        cout << "Enter Phone: ";
        getline(cin, phone);
        
        cout << "Enter Email: ";
        getline(cin, email);

        string id = generateAdminId();
        Admin newAdmin(id, name, password, phone, email);
        admins.push_back(newAdmin);
        saveData();

        cout << "\nRegistration Successful!\n";
        cout << "Your Admin ID is: " << id << "\n\n";
        system("pause");
        system("cls");
    }
    
    Admin* login() {
        string id, password;
        cout << "\n--- Admin Login ---\n";
        cout << "Enter Admin ID: ";
        cin >> id;
        cout << "Enter Password: ";
        cin >> password;

        for (int i = 0; i < admins.getSize(); i++) {
            if (admins[i].getId() == id && admins[i].getPassword() == password) {
                cout << "\nLogin Successful!\n";
                system("pause");
                system("cls");
                return &admins[i];
            }
        }
        cout << "\nLogin Failed! Invalid ID or Password.\n";
        return nullptr;
    }
    
    void displayAllAdmins() {
        if (admins.getSize() == 0) {
            cout << "\nNo admins found!\n";
            return;
        }
        
        cout << "\n=== Admin List ===\n";
        for (int i = 0; i < admins.getSize(); i++) {
            admins[i].display();
            cout << "----------------------\n\n";
        }
            system("pause");
            system("cls");
    }
    
    void deleteAdmin(const string& id) {
        for (int i = 0; i < admins.getSize(); i++) {
            if (admins[i].getId() == id) {
                admins.erase(i);
                saveData();
                cout << "Admin deleted successfully!\n\n";
                system("pause");
                system("cls");
                return;
            }
        }
        cout << "Admin not found with ID: " << id << "\n";
    }
};

class SuperadminManager {
private:
    const string superadminFilename = "superadmin.txt";
    AdminManager adminManager;
    EmployeeManager empManager;
    
    bool checkSuperadminCredentials(const string& username, const string& password) {
        ifstream file(superadminFilename);
        if (!file.is_open()) {
            ofstream createFile(superadminFilename);
            createFile << "ADMIN|ADMIN123#";
            createFile.close();
            return (username == "ADMIN" && password == "ADMIN123#");
        }
        
        string line;
        if (getline(file, line)) {
            size_t pos = line.find(',');
            string fileUser = line.substr(0, pos);
            string filePass = line.substr(pos + 1);
            return (fileUser == username && filePass == password);
        }
        file.close();
        return false;
    }
    
public:
    bool login() {
        string username, password;
        
        cout << "\n=== Superadmin Login ===\n";
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        
        if (checkSuperadminCredentials(username, password)) {
            cout << "\nSuperadmin login successful!\n";
            system("pause");
            system("cls");
            return true;
        }
        
        cout << "\nInvalid superadmin credentials!\n";
        return false;
    }
    
    void superadminMenu() {
        int choice;
        do {
            cout << "\n=== Superadmin Dashboard ===\n\n";
            cout << "1. Register New Admin\n";
            cout << "2. View All Admins\n";
            cout << "3. Delete Admin\n";
            cout << "4. Add Employee Details\n";
            cout << "5. Edit Employee Record\n";
            cout << "6. Delete Employee\n";
            cout << "7. View All Employees\n";
            cout << "8. Search Employee\n";
            cout << "9. Logout\n";
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    system("cls");
                    adminManager.registerAdmin();
                    break;
                case 2:
                    system("cls");
                    adminManager.displayAllAdmins();
                    break;
                case 3: {
                    system("cls");
                    string adminId;
                    cout << "Enter Admin ID to delete: ";
                    cin >> adminId;
                    adminManager.deleteAdmin(adminId);
                    break;
                }
                case 4:
                    system("cls");
                    empManager.addNewEmployee();
                    break;
                case 5:
                    system("cls");
                    empManager.editEmployee();
                    break;
                case 6:
                    system("cls");
                    empManager.deleteEmployee();
                    break;
                case 7:
                    system("cls");
                    empManager.displayAllEmployees();
                    break;
                case 8: {
                    system("cls");
                    string searchId;
                    cout << "Enter Employee ID to search: ";
                    cin >> searchId;
                    empManager.searchEmployeeById(searchId);
                    break;
                }
                case 9:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 9);
    }
};

class LeaveList {
private:
    struct Node {
        LeaveRecord data;
        Node* next;
        Node(const LeaveRecord& record) : data(record), next(nullptr) {}
    };
    Node* head;
    
public:
    LeaveList() : head(nullptr) {}
    ~LeaveList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    void insert(const LeaveRecord& record) {
        Node* newNode = new Node(record);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
    
    LeaveRecord* search(const string& employeeId) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data.employeeId == employeeId) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }
    
    void displayAll() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Employee ID: " << current->data.employeeId << endl;
            cout << "Leave Type: " << current->data.leaveType << endl;
            cout << "Leave Days: " << current->data.leaveDays << endl;
            cout << "Start Date: " << current->data.startDate << endl;
            cout << "Status: " << current->data.status << endl;
            cout << "Reason: " << current->data.reason << endl;
            cout << "----------------------------" << endl;
            current = current->next;
        }
    }
    
    friend void sortLeavesById(LeaveList& leaves);
    friend void sortLeavesByDate(LeaveList& leaves);
    friend int countTotalLeaveDays(const LeaveList& leaves, const string& employeeId);
    friend void findLeavesByType(const LeaveList& leaves, const string& leaveType);
};

void sortLeavesById(LeaveList& leaves) {
    if (leaves.head == nullptr || leaves.head->next == nullptr) return;

    bool swapped;
    LeaveList::Node* ptr1;
    LeaveList::Node* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = leaves.head;

        while (ptr1->next != lptr) {
            if (ptr1->data.employeeId > ptr1->next->data.employeeId) {
                swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sortLeavesByDate(LeaveList& leaves) {
    if (leaves.head == nullptr || leaves.head->next == nullptr) return;

    bool swapped;
    LeaveList::Node* ptr1;
    LeaveList::Node* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = leaves.head;

        while (ptr1->next != lptr) {
            if (ptr1->data.startDate > ptr1->next->data.startDate) {
                swap(ptr1->data, ptr1->next->data);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int countTotalLeaveDays(const LeaveList& leaves, const string& employeeId) {
    int totalDays = 0;
    LeaveList::Node* current = leaves.head;
    
    while (current != nullptr) {
        if (current->data.employeeId == employeeId) {
            totalDays += current->data.leaveDays;
        }
        current = current->next;
    }
    
    return totalDays;
}

void findLeavesByType(const LeaveList& leaves, const string& leaveType) {
    LeaveList::Node* current = leaves.head;
    bool found = false;
    
    cout << "Leaves of type '" << leaveType << "':" << endl;
    cout << "----------------------------------------" << endl;
    
    while (current != nullptr) {
        if (current->data.leaveType == leaveType) {
            found = true;
            cout << "Employee ID: " << current->data.employeeId << endl;
            cout << "Leave Days: " << current->data.leaveDays << endl;
            cout << "Start Date: " << current->data.startDate << endl;
            cout << "Status: " << current->data.status << endl;
            cout << "Reason: " << current->data.reason << endl;
            cout << "----------------------------------------" << endl;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "No leaves found of type '" << leaveType << "'" << endl;
    }
}

void displayWelcomeMessage() {
    system("cls");
    cout << "====================================" << endl;
    cout << "     EMPLOYEE MANAGEMENT SYSTEM     " << endl;
    cout << "====================================" << endl;
    cout << endl;
}

void displayExitMessage() {
    system("cls");
    cout << "====================================" << endl;
    cout << "  Thank you for using the system!   " << endl;
    cout << "====================================" << endl;
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void handleError(const string& message) {
    cerr << "Error: " << message << endl;
    pauseScreen();
}

int stringToInt(const string& str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!(date[i] >= '0' && date[i] <= '9')) return false;
    }
    
    return true;
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, 11, "%Y-%m-%d", ltm);
    return string(buffer);
}

void bubbleSortEmployees(EmployeeDetail* employees, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (employees[j].id > employees[j + 1].id) {
                EmployeeDetail temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

int binarySearchEmployees(EmployeeDetail* employees, int left, int right, const string& target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (employees[mid].id == target) {
            return mid;
        }
        if (employees[mid].id < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

class LeaveAdmin : public User {
public:
    LeaveAdmin(const string& uname, const string& pwd) : User(uname, "", pwd) {}
    ~LeaveAdmin() override {}
    
    void displayMenu() {
        int choice;
        do {
            displayWelcomeMessage();
            cout << "ADMIN MENU (" << id << ")" << endl;
            cout << "1. Edit Employee Leave Days" << endl;
            cout << "2. View Employees" << endl;
            cout << "3. View Leave Requests" << endl;
            cout << "4. Search Employee Leave" << endl;
            cout << "5. Sort Leave Records" << endl;
            cout << "6. Generate Report" << endl;
            cout << "7. Back to Admin Menu" << endl;
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    editEmployeeLeave();
                    break;
                case 2:
                    viewEmployees();
                    break;
                case 3:
                    viewLeaveRequests();
                    break;
                case 4:
                    searchEmployeeLeave();
                    break;
                case 5:
                    sortLeaves();
                    break;
                case 6:
                    generateReport();
                    break;
                case 7:
                    return;
                default:
                    handleError("Invalid choice!");
            }
        } while (true);
    }
    
    void editEmployeeLeave() {
        displayWelcomeMessage();
        cout << "EDIT EMPLOYEE LEAVE BALANCE" << endl;
        
        string empId;
        cout << "Enter employee ID to edit: ";
        cin >> empId;
        
        ifstream empFile("employees.txt");
        bool empExists = false;
        string empName;
        string line;
        
        while (getline(empFile, line)) {
            size_t pos = line.find(',');
            if (line.substr(0, pos) == empId) {
                empExists = true;
                size_t pos2 = line.find(',', pos + 1);
                empName = line.substr(pos + 1, pos2 - pos - 1);
                break;
            }
        }
        empFile.close();
        
        if (!empExists) {
            handleError("Employee not found!");
            return;
        }
        
        ifstream leaveFile("leave_details.txt");
        string fileContent;
        string leaveRecords[100];
        int recordCount = 0;
        bool recordFound = false;
        
        while (getline(leaveFile, line)) {
            if (!line.empty()) {
                size_t pos = line.find(',');
                if (line.substr(0, pos) == empId) {
                    recordFound = true;
                    leaveRecords[recordCount++] = line;
                } else {
                    fileContent += line + "\n";
                }
            }
        }
        leaveFile.close();
        
        cout << "\nEmployee: " << empName << " (" << empId << ")" << endl;
        cout << "Current Leave Details:" << endl;
        
        if (recordFound) {
            for (int i = 0; i < recordCount; i++) {
                size_t pos1 = leaveRecords[i].find(',');
                size_t pos2 = leaveRecords[i].find(',', pos1 + 1);
                
                string leaveType = leaveRecords[i].substr(pos1 + 1, pos2 - pos1 - 1);
                string leaveDays = leaveRecords[i].substr(pos2 + 1);
                
                cout << i+1 << ". " << leaveType << ": " << leaveDays << " days" << endl;
            }
        } else {
            cout << "No leave records found for this employee." << endl;
        }
        
        int choice;
        cout << "\nOptions:" << endl;
        cout << "1. Add new leave type" << endl;
        cout << "2. Edit leave type" << endl;
        cout << "3. Delete leave type" << endl;
        cout << "0. Cancel" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            
            string newType;
            int newDays;
            
            cout << "Enter new leave type (MC/Annual/Other): ";
            cin >> newType;
            cout << "Enter leave days: ";
            cin >> newDays;
            
            if (newDays < 0) {
                handleError("Leave days cannot be negative!");
                return;
            }
            
            for (int i = 0; i < recordCount; i++) {
                size_t pos1 = leaveRecords[i].find(',');
                string existingType = leaveRecords[i].substr(pos1 + 1, leaveRecords[i].find(',', pos1 + 1) - pos1 - 1);
                
                if (existingType == newType) {
                    handleError("This leave type already exists for this employee!");
                    return;
                }
            }
            
            if (recordCount < 100) {
                leaveRecords[recordCount++] = empId + "," + newType + "," + to_string(newDays);
                cout << "New leave type added successfully!" << endl;
            } else {
                handleError("Maximum leave records reached (100)!");
                return;
            }
            
        } else if (choice == 2 && recordFound) {

            int recordChoice;
            cout << "Select leave record to edit (1-" << recordCount << "): ";
            cin >> recordChoice;
            
            if (recordChoice < 1 || recordChoice > recordCount) {
                handleError("Invalid selection!");
                return;
            }
            
            string newValue;
            cout << "Enter new number of days: ";
            cin >> newValue;
            
            int newDays = stringToInt(newValue);
            if (newDays < 0) {
                handleError("Leave days cannot be negative!");
                return;
            }
            
            size_t pos1 = leaveRecords[recordChoice-1].find(',');
            size_t pos2 = leaveRecords[recordChoice-1].find(',', pos1 + 1);
            
            string leaveType = leaveRecords[recordChoice-1].substr(pos1 + 1, pos2 - pos1 - 1);
            leaveRecords[recordChoice-1] = empId + "," + leaveType + "," + to_string(newDays);
            
            cout << "Leave record updated successfully!" << endl;
            
        } else if (choice == 3 && recordFound) {

            int recordChoice;
            cout << "Select leave record to delete (1-" << recordCount << "): ";
            cin >> recordChoice;
            
            if (recordChoice < 1 || recordChoice > recordCount) {
                handleError("Invalid selection!");
                return;
            }
            
            for (int i = recordChoice-1; i < recordCount-1; i++) {
                leaveRecords[i] = leaveRecords[i+1];
            }
            recordCount--;
            cout << "Leave record deleted successfully!" << endl;
            
        } else if (choice != 0) {
            handleError("Invalid choice or no records to edit!");
            return;
        }
        
        for (int i = 0; i < recordCount; i++) {
            fileContent += leaveRecords[i] + "\n";
        }
        
        ofstream outFile("leave_details.txt");
        outFile << fileContent;
        outFile.close();
        
        pauseScreen();
    }
    
    void viewEmployees() {
        displayWelcomeMessage();
        cout << "EMPLOYEE LIST WITH LEAVE BALANCES" << endl;
        
        ifstream countFile("employees.txt");
        int empCount = 0;
        string tempLine;
        while (getline(countFile, tempLine)) {
            empCount++;
        }
        countFile.close();
        
        if (empCount == 0) {
            cout << "No employees found!" << endl;
            pauseScreen();
            return;
        }
        
        const int MAX_EMPLOYEES = 1000;
        if (empCount > MAX_EMPLOYEES) {
            handleError("Too many employees to process!");
            return;
        }
        
        struct EmployeeData {
            string id;
            string name;
            string department;
            int mcDays;
            int annualLeave;
            int otherLeave;
        } employees[MAX_EMPLOYEES];
        
        ifstream empFile("employee_details.txt");
        int index = 0;
        while (getline(empFile, tempLine) &&index < empCount) {
            size_t pos1 = tempLine.find(',');
            size_t pos2 = tempLine.find(',', pos1 + 1);
            size_t pos3 = tempLine.find(',', pos2 + 1);
            size_t pos4 = tempLine.find(',', pos3 + 1);
            size_t pos5 = tempLine.find(',', pos4 + 1);
            
            employees[index].id = tempLine.substr(0, pos1);
            employees[index].name = tempLine.substr(pos1 + 1, pos2 - pos1 - 1);
            employees[index].department = tempLine.substr(pos2 + 1, pos3 - pos2 - 1);
            
            if (pos4 != string::npos && pos5 != string::npos) {
                employees[index].mcDays = stringToInt(tempLine.substr(pos3 + 1, pos4 - pos3 - 1));
                employees[index].annualLeave = stringToInt(tempLine.substr(pos4 + 1, pos5 - pos4 - 1));
                employees[index].otherLeave = stringToInt(tempLine.substr(pos5 + 1));
            } else {
                employees[index].mcDays = 0;
                employees[index].annualLeave = 0;
                employees[index].otherLeave = 0;
            }
            index++;
        }
        empFile.close();
        
        const int MAX_LEAVES = 1000;
        struct LeaveData {
            string employeeId;
            string leaveType;
            int leaveDays;
        } leaves[MAX_LEAVES];
        int leaveCount = 0;
        
        ifstream leaveFile("leave_details.txt");
        while (getline(leaveFile, tempLine) && leaveCount < MAX_LEAVES) {
            size_t pos1 = tempLine.find(',');
            size_t pos2 = tempLine.find(',', pos1 + 1);
            
            leaves[leaveCount].employeeId = tempLine.substr(0, pos1);
            leaves[leaveCount].leaveType = tempLine.substr(pos1 + 1, pos2 - pos1 - 1);
            leaves[leaveCount].leaveDays = stringToInt(tempLine.substr(pos2 + 1));
            leaveCount++;
        }
        leaveFile.close();
        
        for (int i = 0; i < empCount; i++) {
            cout << "\nEmployee ID: " << employees[i].id << endl;
            cout << "Name: " << employees[i].name << endl;
            cout << "Department: " << employees[i].department << endl;
            
            bool hasLeave = false;
            for (int j = 0; j < leaveCount; j++) {
                if (leaves[j].employeeId == employees[i].id) {
                    if (!hasLeave) {
                        cout << "Leave Balances:\n" << endl;
                        hasLeave = true;
                    }
                    cout << "- " << leaves[j].leaveType << ": " << leaves[j].leaveDays << " days" << endl;
                }
            }
            if (!hasLeave) {
                cout << "Leave Balances: No leave records found" << endl;
            }
            
            cout << "----------------------------" << endl;
        }
        
        pauseScreen();
    }
    
    void viewLeaveRequests() {
        displayWelcomeMessage();
        cout << "LEAVE REQUESTS" << endl;
        
        ifstream reqFile("leave_requests.txt");
        if (!reqFile) {
            cout << "No leave requests found!" << endl;
            return;
        }
        
        string line;
        int count = 0;
        
        while (getline(reqFile, line)) {
            if (line.empty()) continue;
            
            count++;
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            
            cout << "Leave Request " << count << endl;
            cout << "Employee ID: " << line.substr(0, pos1) << endl;
            cout << "Leave Type: " << line.substr(pos1 + 1, pos2 - pos1 - 1) << endl;
            cout << "Start Date: " << line.substr(pos2 + 1, pos3 - pos2 - 1) << endl;
            cout << "Days: " << line.substr(pos3 + 1, pos4 - pos3 - 1) << endl;
            cout << "Reason: " << line.substr(pos4 + 1) << endl;
            cout << "----------------------------" << endl;
        }
        
        if (count == 0) {
            cout << "No leave requests found!" << endl;
        } else {
            cout << "Total requests: " << count << endl;
        }
        
        reqFile.close();
        pauseScreen();
    }
    
    void searchEmployeeLeave() {
        displayWelcomeMessage();
        cout << "SEARCH EMPLOYEE LEAVE REQUESTS" << endl;
        
        string empId;
        cout << "Enter employee ID to search: ";
        cin >> empId;
        
        ifstream reqFile("leave_requests.txt");
        if (!reqFile) {
            cout << "No leave requests found for any employee!" << endl;
            pauseScreen();
            return;
        }
        
        string line;
        bool found = false;
        int count = 0;
        
        cout << "\nLeave Requests for Employee ID: " << empId << endl;
        cout << "----------------------------------------" << endl;
        
        while (getline(reqFile, line)) {
            if (line.empty()) continue;
            
            size_t pos = line.find(',');
            if (line.substr(0, pos) == empId) {
                found = true;
                count++;
                
                size_t pos1 = pos;
                size_t pos2 = line.find(',', pos1 + 1);
                size_t pos3 = line.find(',', pos2 + 1);
                size_t pos4 = line.find(',', pos3 + 1);
                
                cout << "Request #" << count << endl;
                cout << "Leave Type: " << line.substr(pos1 + 1, pos2 - pos1 - 1) << endl;
                cout << "Start Date: " << line.substr(pos2 + 1, pos3 - pos2 - 1) << endl;
                cout << "Days: " << line.substr(pos3 + 1, pos4 - pos3 - 1) << endl;
                cout << "Reason: " << line.substr(pos4 + 1) << endl;
                cout << "----------------------------------------" << endl;
            }
        }
        
        if (!found) {
            cout << "No leave requests found for this employee." << endl;
        } else {
            cout << "Total requests found: " << count << endl;
        }
        
        reqFile.close();
        pauseScreen();
    }
    
    void sortLeaves() {
        displayWelcomeMessage();
        cout << "SORT LEAVE RECORDS" << endl;
        
        const int MAX_REQUESTS = 100;
        struct LeaveRequest {
            string employeeId;
            string leaveType;
            string startDate;
            string days;
            string reason;
        } requests[MAX_REQUESTS];
        
        int count = 0;
        ifstream reqFile("leave_requests.txt");
        if (!reqFile) {
            cout << "No leave requests found!" << endl;
            pauseScreen();
            return;
        }
        
        string line;
        while (count < MAX_REQUESTS && getline(reqFile, line)) {
            if (line.empty()) continue;
            
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            size_t pos3 = line.find(',', pos2 + 1);
            size_t pos4 = line.find(',', pos3 + 1);
            
            requests[count].employeeId = line.substr(0, pos1);
            requests[count].leaveType = line.substr(pos1 + 1, pos2 - pos1 - 1);
            requests[count].startDate = line.substr(pos2 + 1, pos3 - pos2 - 1);
            requests[count].days = line.substr(pos3 + 1, pos4 - pos3 - 1);
            requests[count].reason = line.substr(pos4 + 1);
            count++;
        }
        reqFile.close();
        
        if (count == 0) {
            cout << "No leave requests to sort!" << endl;
            pauseScreen();
            return;
        }
        
        int choice;
        cout << "Sort by:\n";
        cout << "1. Employee ID\n";
        cout << "2. Date\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                bool shouldSwap = false;
                if (choice == 1 && requests[j].employeeId > requests[j+1].employeeId) {
                    shouldSwap = true;
                } else if (choice == 2 && requests[j].startDate > requests[j+1].startDate) {
                    shouldSwap = true;
                }
                
                if (shouldSwap) {
                    swap(requests[j], requests[j+1]);
                }
            }
        }
        
        cout << "\nSORTED LEAVE REQUESTS" << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < count; i++) {
            cout << "Employee ID: " << requests[i].employeeId << endl;
            cout << "Leave Type: " << requests[i].leaveType << endl;
            cout << "Start Date: " << requests[i].startDate << endl;
            cout << "Days: " << requests[i].days << endl;
            cout << "Reason: " << requests[i].reason << endl;
            cout << "----------------------------------------" << endl;
        }
        
        pauseScreen();
    }
    
    void generateReport() {
    	system("cls");
	    ofstream report("leave_report.txt");
	    if (!report) {
	        cout << "Unable to create report file!" << endl;
	        pauseScreen();
	        return;
	    }
	
	    ifstream empFile("employee_details.txt");
	    if (!empFile) {
	        cout << "Unable to open employee details file!" << endl;
	        pauseScreen();
	        return;
	    }
	
	    string line;
	    while (getline(empFile, line)) {
	        if (line.empty()) continue;
	
	        size_t pos1 = line.find(',');
	        size_t pos2 = line.find(',', pos1 + 1);
	        size_t pos3 = line.find(',', pos2 + 1);
	        size_t pos4 = line.find(',', pos3 + 1);
	        size_t pos5 = line.find(',', pos4 + 1);
	
	        string id = line.substr(0, pos1);
	        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
	        string position = line.substr(pos2 + 1, pos3 - pos2 - 1);
	        string salary = line.substr(pos3 + 1, pos4 - pos3 - 1);
	        string joinDate = line.substr(pos4 + 1, pos5 - pos4 - 1);
	        string department = line.substr(pos5 + 1);
	
	        report << "Employee Details:" << endl;
	        report << "ID: " << id << endl;
	        report << "Name: " << name << endl;
	        report << "Position: " << position << endl;
	        report << "Salary: " << salary << endl;
	        report << "Join Date: " << joinDate << endl;
	        report << "Department: " << department << endl;
	
	        ifstream leaveFile("leave_requests.txt");
	        if (leaveFile) {
	            report << "\nLeave Requests:" << endl;
	            int leaveCount = 0;
	            string leaveLine;
	
	            while (getline(leaveFile, leaveLine)) {
	                if (leaveLine.empty()) continue;
	
	                size_t lpos1 = leaveLine.find(',');
	                if (leaveLine.substr(0, lpos1) == id) {
	                    leaveCount++;
	                    size_t lpos2 = leaveLine.find(',', lpos1 + 1);
	                    size_t lpos3 = leaveLine.find(',', lpos2 + 1);
	                    size_t lpos4 = leaveLine.find(',', lpos3 + 1);
	
	                    report << leaveCount << ". Type: " << leaveLine.substr(lpos1 + 1, lpos2 - lpos1 - 1)
	                           << ", Date: " << leaveLine.substr(lpos2 + 1, lpos3 - lpos2 - 1)
	                           << ", Days: " << leaveLine.substr(lpos3 + 1, lpos4 - lpos3 - 1)
	                           << ", Reason: " << leaveLine.substr(lpos4 + 1) << endl;
	                }
	            }
	
	            if (leaveCount == 0) {
	                report << "No leave requests found for this employee." << endl;
	            }
	
	            leaveFile.close();
	        }
	
	        report << "----------------------------------------\n" << endl;
	    }
	
	    empFile.close();
	    report.close();
	
	    cout << "Report successfully generated and saved to 'leave_report.txt'." << endl;
	    pauseScreen();
	}
};

class Employee {
private:
    int employeeID;
    char password[50];
    Profile profile;
    int MAX_LEAVE_DAYS;
    
    struct LeaveBalance {
        char type[20];
        int balance;
    };
    
    LeaveBalance leaveBalances[10];
    int leaveBalanceCount;
    
public:
    Employee() {
        employeeID = 0;
        password[0] = '\0';
    }

	int getEmployeeID() const { return employeeID; }
	 
    void registerEmployee() {
        cout << "\n--- Employee Registration ---\n";
        cout << "Enter full name: ";
        cin.ignore();
        cin.getline(profile.fullName, 100);

        do {
            cout << "Enter email (@gmail.com only): ";
            cin.getline(profile.email, 100);
            string emailStr(profile.email);
            if (emailStr.find("@gmail.com") == string::npos || emailStr.find('@') != emailStr.rfind('@')) {
                cout << "Invalid email. Please use a valid @gmail.com email.\n";
            } else {
                break;
            }
        } while (true);

        do {
            cout << "Enter phone (10 or 11 digits only): ";
            cin.getline(profile.phone, 20);
            string phoneStr(profile.phone);
            if (phoneStr.length() < 10 || phoneStr.length() > 11 || phoneStr.find_first_not_of("0123456789") != string::npos) {
                cout << "Invalid phone number. Enter 10 or 11 numeric digits only.\n";
            } else {
                break;
            }
        } while (true);

        cout << "Enter password: ";
        cin >> password;

        employeeID = generateEmployeeID();

        ofstream file("employees.txt", ios::app);
        file << employeeID << "," << profile.fullName << "," << password << ","
             << profile.email << "," << profile.phone << endl;
        file.close();

        cout << "\nRegistered successfully! Your Employee ID is: " << employeeID << endl;
        cout << "Please remember this ID for login.\n";
    }

    bool loginEmployee() {
        int inputID;
        cout << "\nEnter Employee ID: ";
        cin >> inputID;

        ifstream file("employees.txt");
        if (!file.is_open()) {
            cout << "Error: Employee database not found.\n";
            return false;
        }

        char line[300];
        int id;
        char pass[50], name[100], email[100], phone[20];
        bool found = false;

        while (file.getline(line, 300)) {

            sscanf(line, "%d,%[^,],%[^,],%[^,],%s", &id, name, pass, email, phone);
            
            if (id == inputID) {
                found = true;
                break;
            }
        }
        file.close();

        if (!found) {
            cout << "Employee ID not found.\n";
            return false;
        }

        char inputPass[50];
        cout << "Enter Password: ";
        cin >> inputPass;

        if (strcmp(pass, inputPass) == 0) {
            employeeID = id;
            strcpy(profile.fullName, name);
            strcpy(password, pass);
            strcpy(profile.email, email);
            strcpy(profile.phone, phone);
            cout << "Login Successful!\n\n";
            system("pause");
            system("cls");
            return true;
        } 
        else {
            cout << "Incorrect password.\n";
            return false;
        }
    }
    
    void updateProfile() {
        cout << "\n--- Employee Profile ---\n";
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << profile.fullName << endl;
        cout << "Email: " << profile.email << endl;
        cout << "Phone: " << profile.phone << endl;       
        cout << "\n--- Update Profile ---\n";
        cout << "Enter new full name: ";
        cin.getline(profile.fullName, 100);

        do {
            cout << "Enter new email (@gmail.com only): ";
            cin.getline(profile.email, 100);
            string emailStr(profile.email);
            if (emailStr.find("@gmail.com") == string::npos || emailStr.find('@') != emailStr.rfind('@')) {
                cout << "Invalid email. Please use a valid @gmail.com email.\n";
            } else {
                break;
            }
        } while (true);

        do {
            cout << "Enter new phone (10 or 11 digits only): ";
            cin.getline(profile.phone, 20);
            string phoneStr(profile.phone);
            if (phoneStr.length() < 10 || phoneStr.length() > 11 || phoneStr.find_first_not_of("0123456789") != string::npos) {
                cout << "Invalid phone number. Enter 10 or 11 numeric digits only.\n";
            } else {
                break;
            }
        } while (true);

        saveChanges();
        cout << "\nProfile updated successfully!\n\n";
        system("pause");
        system("cls");
    }

    void changePassword() {
        cout << "Enter new password: ";
        cin >> password;
        saveChanges();
        cout << "Password changed successfully!\n\n";
        system("pause");
        system("cls");
    }

    void showProfile() {
        cout << "--- Employee Profile ---\n";
        cout << "Employee ID: " << employeeID << endl;
        cout << "Name: " << profile.fullName << endl;
        cout << "Email: " << profile.email << endl;
        cout << "Phone: " << profile.phone << endl;
        cout << "\n";
        system("pause");
        system("cls");
    }

    void addWorklogRecord() {
        ofstream file;
        file.open(getWorklogFilename(), ios::app);
        Worklog log;
        cout << "Enter Worklog ID: ";
        cin >> log.id;
        cin.ignore();
        cout << "Enter Task Description: "; 
        cin.getline(log.task, 100);
        cout << "Enter Date (YYYY-MM-DD): "; 
        cin.getline(log.date, 20);
        file << log.id << "," << log.task << "," << log.date << endl;
        file.close();
        cout << "\nWorklog record added successfully.\n\n";
        system("pause");
        system("cls");
    }

    void editWorklogRecord() {
        cout << "--- Edit Worklog Record ---\n\n";
        
        ifstream checkFile(getWorklogFilename());
        if (!checkFile.is_open() || checkFile.peek() == ifstream::traits_type::eof()) {
            cout << "\nNo worklog records found to edit.\n";
            checkFile.close();
            system("pause");
            system("cls");
            return;
        }
        checkFile.close();
        displayAllWorklogs();
        
        int editID;
        cout << "\nEnter Worklog ID to edit: "; 
        cin >> editID; 
        cin.ignore();
        
        ifstream inFile(getWorklogFilename());
        ofstream tempFile("temp.txt");
        char line[300];
        bool found = false;
        Worklog log;
        
        while (inFile.getline(line, 300)) {
            sscanf(line, "%d,%[^,],%s", &log.id, log.task, log.date);
            if (log.id == editID) {
                found = true;
                cout << "\nCurrent Record:\n";
                cout << "ID: " << log.id << "\nTask: " << log.task << "\nDate: " << log.date << endl;
                
                cout << "\nEnter new Task Description: "; 
                cin.getline(log.task, 100);
                cout << "Enter new Date (YYYY-MM-DD): "; 
                cin.getline(log.date, 20);
                
                tempFile << log.id << "," << log.task << "," << log.date << endl;
                cout << "Record updated successfully!\n\n";
            } else {
                tempFile << line << endl;
            }
        }
        
        inFile.close();
        tempFile.close();
        
        if (!found) {
            cout << "Worklog ID not found.\n";
            remove("temp.txt");
        } else {
            remove(getWorklogFilename().c_str());
            rename("temp.txt", getWorklogFilename().c_str());
        }
        
        system("pause");
        system("cls");
    }

    void deleteWorklogRecord() {
        cout << "--- Delete Worklog Record ---\n";
        
        ifstream checkFile(getWorklogFilename());
        if (!checkFile.is_open() || checkFile.peek() == ifstream::traits_type::eof()) {
            cout << "\nNo worklog records found to delete.\n";
            checkFile.close();
            system("pause");
            system("cls");
            return;
        }
        checkFile.close();
        displayAllWorklogs();
        
        int choice;
        cout << "\nDelete by:\n1. ID\n2. Date\nEnter choice: "; 
        cin >> choice; 
        cin.ignore();
        
        ifstream inFile(getWorklogFilename());
        ofstream tempFile("temp.txt");
        char line[300];
        bool found = false;
        Worklog log;
        char searchDate[20];
        int deleteID;
        
        if (choice == 1) {
            cout << "Enter Worklog ID to delete: "; 
            cin >> deleteID; 
            cin.ignore();
        } else if (choice == 2) {
            cout << "Enter Date to delete (YYYY-MM-DD): "; 
            cin.getline(searchDate, 20);
        } else {
            cout << "Invalid choice.\n";
            inFile.close();
            tempFile.close();
            remove("temp.txt");
            system("pause");
            system("cls");
            return;
        }
        
        while (inFile.getline(line, 300)) {
            sscanf(line, "%d,%[^,],%s", &log.id, log.task, log.date);
            
            bool match = false;
            if (choice == 1 && log.id == deleteID) {
                match = true;
            } else if (choice == 2 && strcmp(log.date, searchDate) == 0) {
                match = true;
            }
            
            if (!match) {
                tempFile << line << endl;
            } else {
                found = true;
                cout << "\nDeleted Record:\n";
                cout << "ID: " << log.id << "\nTask: " << log.task << "\nDate: " << log.date << endl;
            }
        }
        
        inFile.close();
        tempFile.close();
        
        if (!found) {
            cout << "No matching records found.\n";
            remove("temp.txt");
        } else {
            remove(getWorklogFilename().c_str());
            rename("temp.txt", getWorklogFilename().c_str());
            cout << "Record(s) deleted successfully!\n\n";
        }
        
        system("pause");
        system("cls");
    }

    void searchWorklogRecord() {
        cout << "--- Search Worklog Records ---\n";
        
        ifstream checkFile(getWorklogFilename());
        if (!checkFile.is_open() || checkFile.peek() == ifstream::traits_type::eof()) {
            cout << "\nNo worklog records found to search.\n";
            checkFile.close();
            system("pause");
            system("cls");
            return;
        }
        checkFile.close();
        
        int choice;
        cout << "Search by:\n1. Keyword in task\n2. Date\nEnter choice: "; cin >> choice; cin.ignore();
        
        char searchTerm[100];
        if (choice == 1) {
            cout << "Enter keyword to search in tasks: "; cin.getline(searchTerm, 100);
        } else if (choice == 2) {
            cout << "Enter date to search (YYYY-MM-DD): "; cin.getline(searchTerm, 20);
        } else {
            cout << "Invalid choice.\n";
            system("pause");
            system("cls");
            return;
        }
        
        ifstream file(getWorklogFilename());
        char line[300];
        Worklog log;
        bool found = false;
        
        cout << "\nSearch Results:\n";
        cout << "----------------------------------------\n";
        while (file.getline(line, 300)) {
            sscanf(line, "%d,%[^,],%s", &log.id, log.task, log.date);
            
            bool match = false;
            if (choice == 1 && strstr(log.task, searchTerm) != NULL) {
                match = true;
            } else if (choice == 2 && strcmp(log.date, searchTerm) == 0) {
                match = true;
            }
            
            if (match) {
                found = true;
                cout << "ID: " << log.id << "\nTask: " << log.task << "\nDate: " << log.date << endl;
                cout << "----------------------------------------\n";
            }
        }
        file.close();
        
        if (!found) {
            cout << "No matching records found.\n";
        }
        
        system("pause");
        system("cls");
    }

    void sortWorklogRecords() {
	    int choice;
	    
	    while (true) {
	    	system("cls");
	    	displayWelcomeMessage();
	        cout << "--- Sort Worklog Records ---\n";
	        
	        ifstream checkFile(getWorklogFilename());
	        if (!checkFile.is_open() || checkFile.peek() == ifstream::traits_type::eof()) {
	            cout << "\nNo worklog records found to sort.\n";
	            checkFile.close();
	            system("pause");
	            return;
	        }
	        checkFile.close();
	        
	        cout << "\nSort by:\n"; 
	        cout << "1. Date\n"; 
	        cout << "2. Task Name\n";
	        cout << "Enter choice (0 to cancel): "; 
	        cin >> choice; 
	        cin.ignore();
	        
	        if (choice == 0) {
	            return;  // User chose to cancel
	        }
	        else if (choice == 1 || choice == 2) {
	            break;  // Valid choice, proceed with sorting
	        }
	        else {
	            cout << "Invalid choice. Please enter 1 or 2.\n\n";
	            system("pause");
	            continue;  // This will restart the loop
	        }
	    }
	    
	    ifstream countFile(getWorklogFilename());
	    int count = 0;
	    char line[300];
	    while (countFile.getline(line, 300)) count++;
	    countFile.close();
	    
	    if (count == 0) {
	        cout << "No records to sort.\n";
	        system("pause");
	        return;
	    }
	    
	    Worklog* logs = new Worklog[count];
	    ifstream inFile(getWorklogFilename());
	    for (int i = 0; i < count; i++) {
	        inFile.getline(line, 300);
	        sscanf(line, "%d,%[^,],%s", &logs[i].id, logs[i].task, logs[i].date);
	    }
	    inFile.close();
	    
	    for (int i = 0; i < count-1; i++) {
	        for (int j = 0; j < count-i-1; j++) {
	            bool swapNeeded = false;
	            if (choice == 1) {
	                if (strcmp(logs[j].date, logs[j+1].date) > 0) {
	                    swapNeeded = true;
	                }
	            } else if (choice == 2) {
	                if (strcmp(logs[j].task, logs[j+1].task) > 0) {
	                    swapNeeded = true;
	                }
	            }
	            
	            if (swapNeeded) {
	                Worklog temp = logs[j];
	                logs[j] = logs[j+1];
	                logs[j+1] = temp;
	            }
	        }
	    }
	    
	    ofstream outFile(getWorklogFilename());
	    for (int i = 0; i < count; i++) {
	        outFile << logs[i].id << "," << logs[i].task << "," << logs[i].date << endl;
	    }
	    outFile.close();
	    delete[] logs;
	    
	    cout << "\nRecords sorted successfully!\n";
	    displayAllWorklogs();
	    cout << "\n";
	    system("pause");
	}
    
    void loadLeaveBalances() {
        leaveBalanceCount = 0;
        
        ifstream file("leave_details.txt");
        char line[100];
        
        while (file.getline(line, 100) && leaveBalanceCount < 10) {
            char empId[20];
            sscanf(line, "%[^,],%[^,],%d", empId, leaveBalances[leaveBalanceCount].type, &leaveBalances[leaveBalanceCount].balance);
            
            if (strcmp(empId, to_string(employeeID).c_str()) == 0) {
                leaveBalanceCount++;
            }
        }
        file.close();
    }
    
void requestLeave() {
    system("cls");
    cout << "=============================" << endl;
	cout << "        Request Leave        " << endl;
    cout << "=============================" << endl;
    
    loadLeaveBalances();
    
    if (leaveBalanceCount == 0) {
        cout << "\nNo leave types added for you from admin.\n\n";
        system("pause");
        system("cls");
        return;
    }
    
    cout << "\nAvailable Leave Types:\n\n";
    for (int i = 0; i < leaveBalanceCount; i++) {
        cout << (i+1) << ". " << leaveBalances[i].type 
             << " (" << leaveBalances[i].balance << " days left)\n";
    }
    
    int choice;
    cout << "\nEnter your choice (1-" << leaveBalanceCount << "): ";
    cin >> choice;
    cin.ignore();
    
    if (choice < 1 || choice > leaveBalanceCount) {
        cout << "Invalid choice!\n";
        system("pause");
        system("cls");
        return;
    }
    
    int selectedIndex = choice - 1;
    int availableDays = leaveBalances[selectedIndex].balance;
    
    char startDate[20];
    int days;
    char reason[100];
    
    cout << "Start Date (YYYY-MM-DD): ";
    cin.getline(startDate, 20);
    
    cout << "Days (max " << availableDays << "): ";
    cin >> days;
    cin.ignore();
    
    if (days <= 0 || days > availableDays) {
        cout << "Invalid number of days!\n";
        system("pause");
        system("cls");
        return;
    }
    
    cout << "Reason: ";
    cin.getline(reason, 100);
    
    char confirm;
    cout << "Confirm request? (Y/N): ";
    cin >> confirm;
    
    if (toupper(confirm) != 'Y') {
        cout << "Request cancelled.\n";
        system("pause");
        system("cls");
        return;
    }
    
    ofstream requestFile("leave_requests.txt", ios::app);
    requestFile << employeeID << "," 
                << leaveBalances[selectedIndex].type << ","
                << startDate << ","
                << days << ","
                << reason << "\n";
    requestFile.close();
    
    ifstream inFile("leave_details.txt");
    ofstream tempFile("temp.txt");
    char line[100];
    
    while (inFile.getline(line, 100)) {
        char empId[20], type[20];
        int balance;
        
        sscanf(line, "%[^,],%[^,],%d", empId, type, &balance);
        
        if (strcmp(empId, to_string(employeeID).c_str()) == 0 && 
            strcmp(type, leaveBalances[selectedIndex].type) == 0) {
            tempFile << empId << "," << type << "," << (balance - days) << "\n";
        } else {
            tempFile << line << "\n";
        }
    }
    
    inFile.close();
    tempFile.close();
    
    remove("leave_details.txt");
    rename("temp.txt", "leave_details.txt");
    
    cout << "\nLeave request submitted successfully!\n\n";
    system("pause");
    system("cls");
}

void viewLeaveRequests() {
    system("cls");
    displayWelcomeMessage();
    cout << "\n------- Your Leave Requests -------\n";
    
    loadLeaveBalances();
    
    ifstream file(getLeaveFilename());
    if (!file.is_open()) {
        cout << "No leave requests found.\n";
        system("pause");
        system("cls");
        return;
    }
    
    int requestCount = 0;
    char line[500];
    while (file.getline(line, 500)) {
        requestCount++;
    }
    file.clear();
    file.seekg(0);
    
    struct LeaveRequest {
        int employeeId;
        char type[20];
        char startDate[20];
        int duration;
        char reason[100];
    } requests[100];
    
    int actualRequests = 0;
    while (file.getline(line, 500) && actualRequests < 100) {
        sscanf(line, "%d,%[^,],%[^,],%d,%[^\n]", 
               &requests[actualRequests].employeeId,
               requests[actualRequests].type,
               requests[actualRequests].startDate,
               &requests[actualRequests].duration,
               requests[actualRequests].reason);
        
        if (requests[actualRequests].employeeId == employeeID) {
            actualRequests++;
        }
    }
    file.close();
    
    if (actualRequests == 0) {
        cout << "No leave requests found for you.\n";
    } else {
        cout << "Start Date   | Duration |   Type   |  Reason\n";
        cout << "---------------------------------------------\n";
        for (int i = 0; i < actualRequests; i++) {
            printf("%-12s| %-9d| %-10s | %s\n", 
                   requests[i].startDate, 
                   requests[i].duration, 
                   requests[i].type, 
                   requests[i].reason);
        }
        
        struct LeaveUsage {
            char type[20];
            int used;
        } usedLeaveDays[10] = {0};
        int usedLeaveCount = 0;
        
        for (int i = 0; i < actualRequests; i++) {
            bool found = false;
            for (int j = 0; j < usedLeaveCount; j++) {
                if (strcmp(usedLeaveDays[j].type, requests[i].type) == 0) {
                    usedLeaveDays[j].used += requests[i].duration;
                    found = true;
                    break;
                }
            }
            
            if (!found && usedLeaveCount < 10) {
                strcpy(usedLeaveDays[usedLeaveCount].type, requests[i].type);
                usedLeaveDays[usedLeaveCount].used = requests[i].duration;
                usedLeaveCount++;
            }
        }
        
        cout << "\nLeave Requested:\n\n";
        for (int i = 0; i < leaveBalanceCount; i++) {
            int used = 0;
            for (int j = 0; j < usedLeaveCount; j++) {
                if (strcmp(leaveBalances[i].type, usedLeaveDays[j].type) == 0) {
                    used = usedLeaveDays[j].used;
                    break;
                }
            }
            
            cout << leaveBalances[i].type << ": " << used << "/" << (leaveBalances[i].balance + used) 
                 << " (Remaining: " << leaveBalances[i].balance << ")\n";
        }
    }
    cout << "\n";
    system("pause");
    system("cls");
}

    void generateSummaryReport() {
        cout << "\n--- Worklog Summary Report ---\n";
        
        ifstream countFile(getWorklogFilename());
        int count = 0;
        char line[300];
        while (countFile.getline(line, 300)) count++;
        countFile.close();
        
        if (count == 0) {
            cout << "\nNo worklog records found.\n";
            system("pause");
            system("cls");
            return;
        }
        
        Worklog* logs = new Worklog[count];
        ifstream inFile(getWorklogFilename());
        for (int i = 0; i < count; i++) {
            inFile.getline(line, 300);
            sscanf(line, "%d,%[^,],%s", &logs[i].id, logs[i].task, logs[i].date);
        }
        inFile.close();
        
        string reportFilename = "worklog_report_" + to_string(employeeID) + ".txt";
        ofstream report(reportFilename);
        
        report << "Worklog Summary Report for Employee ID: " << employeeID << endl;
        report << "Employee Name: " << profile.fullName << endl;
        report << "Total Worklog Entries: " << count << endl;
        report << "----------------------------------------\n\n";
        
        cout << "\nGenerating report...\n";
        
        for (int i = 0; i < count; i++) {
            report << "Entry #" << i+1 << ":\n";
            report << "ID: " << logs[i].id << endl;
            report << "Task: " << logs[i].task << endl;
            report << "Date: " << logs[i].date << endl;
            report << "----------------------------------------\n";
        }
        
        report << "\nReport generated on: " << getCurrentDate() << endl;
        report.close();
        delete[] logs;
        
        cout << "Report generated successfully! Saved as: " << reportFilename << endl;
        cout << "\n";
		system("pause");
        system("cls");
    }

private:
    int generateEmployeeID() {
        ifstream file("employees.txt");
        int lastID = 1000;
        char line[300];
        while (file.getline(line, 300)) {
            int id;
            sscanf(line, "%d,", &id);
            if (id > lastID) lastID = id;
        }
        return lastID + 1;
    }

    string getWorklogFilename() {
        return "worklog_" + to_string(employeeID) + ".txt";
    }

    void saveChanges() {
        ifstream file("employees.txt");
        ofstream temp("temp.txt");
        char line[300];
        while (file.getline(line, 300)) {
            int id;
            sscanf(line, "%d,", &id);
            if (id == employeeID) {
                temp << employeeID << "," << profile.fullName << "," <<  password<< ","
                     << profile.email << "," << profile.phone << endl;
            } else {
                temp << line << endl;
            }
        }
        file.close();
        temp.close();
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
    }

    void displayAllWorklogs() {
        ifstream file(getWorklogFilename());
        if (!file.is_open() || file.peek() == ifstream::traits_type::eof()) {
            cout << "\nNo worklog records found.\n";
            file.close();
            return;
        }

        char line[300];
        Worklog log;
        cout << "ID  | Task Description          | Date\n";
        cout << "----------------------------------------\n";
        
        while (file.getline(line, 300)) {
            sscanf(line, "%d,%[^,],%s", &log.id, log.task, log.date);
            printf("%-4d| %-25s| %s\n", log.id, log.task, log.date);
        }
        file.close();
    }

    string getLeaveFilename() {
        return "leave_requests.txt";
    }

    int calculateUsedLeaveDays() {
        ifstream file(getLeaveFilename());
        if (!file.is_open()) {
            return 0;
        }

        char line[500];
        int totalDays = 0;
        int id;

        while (file.getline(line, 500)) {
            Leave leave;
            sscanf(line, "%d,%[^,],%d,%[^,\n]", 
                   &id, leave.startDate, &leave.duration, leave.reason);
            
            if (id == employeeID) {
                totalDays += leave.duration;
            }
        }
        file.close();
        return totalDays;
    }
};

void displayMainMenu() {
    displayWelcomeMessage();
    cout << "1. Superadmin Login\n";
    cout << "2. Admin Login\n";
    cout << "3. Employee Login\n";
    cout << "4. Employee Registration\n";
    cout << "5. Exit\n";
    cout << "\nEnter your choice: ";
}

void adminMenu(Admin* admin) {
    int choice;
    do {
        displayWelcomeMessage();
        cout << "ADMIN MENU (" << admin->getId() << ")\n";
        cout << "1. Manage Employee Records\n";
        cout << "2. Manage Leave Requests\n";
        cout << "3. Generate Reports\n";
        cout << "4. Logout\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                EmployeeManager empManager;
                int empChoice;
                do {
                    displayWelcomeMessage();
                    cout << "EMPLOYEE RECORD MANAGEMENT\n";
                    cout << "1. Add New Employee Record\n";
                    cout << "2. Edit Employee Record\n";
                    cout << "3. Delete Employee\n";
                    cout << "4. View All Employees\n";
                    cout << "5. Search Employee\n";
                    cout << "6. Back to Admin Menu\n";
                    cout << "\nEnter your choice: ";
                    cin >> empChoice;

                    switch (empChoice) {
                        case 1:
                        	system("cls");
                            empManager.addNewEmployee();
                            break;
                        case 2:
                        	system("cls");
                            empManager.editEmployee();
                            break;
                        case 3:
                        	system("cls");
                            empManager.deleteEmployee();
                            break;
                        case 4:
                        	system("cls");
                            empManager.displayAllEmployees();
                            break;
                        case 5: {
                        	system("cls");
                            string searchId;
                            cout << "Enter Employee ID to search: ";
                            cin >> searchId;
                            empManager.searchEmployeeById(searchId);
                            break;
                        }
                        case 6:
                            break;
                        default:
                            cout << "Invalid choice!\n";
                            break;
                    }
                    if (empChoice != 6);
                } while (empChoice != 6);
            }
                break;
            case 2: {
                LeaveAdmin leaveAdmin(admin->getId(), admin->getPassword());
                leaveAdmin.displayMenu();
                break;
            }
            case 3: {
                system("cls");
                cout << "\n=== GENERATE REPORTS ===\n";
                
                ifstream empFile("employee_details.txt");
                int employeeCount = 0;
                string line;
                while (getline(empFile, line)) {
                    if (!line.empty()) employeeCount++;
                }
                empFile.close();
                
                ifstream leaveFile("leave_requests.txt");
                int leaveCount = 0;
                while (getline(leaveFile, line)) {
                    if (!line.empty()) leaveCount++;
                }
                leaveFile.close();
                
                ifstream deptFile("employee_details.txt");
                string departments[50];
                int deptCount = 0;
                while (getline(deptFile, line) && deptCount < 50) {
                    if (!line.empty()) {
                        size_t lastComma = line.rfind(',');
                        if (lastComma != string::npos) {
                            string dept = line.substr(lastComma + 1);
                            bool found = false;
                            for (int i = 0; i < deptCount; i++) {
                                if (departments[i] == dept) {
                                    found = true;
                                    break;
                                }
                            }
                            if (!found) {
                                departments[deptCount++] = dept;
                            }
                        }
                    }
                }
                deptFile.close();
                
                time_t now = time(0);
                tm* ltm = localtime(&now);
                char timeStr[20];
                strftime(timeStr, 20, "%Y%m%d_%H%M%S", ltm);
                string reportFilename = "admin_report_" + string(timeStr) + ".txt";
                
                ofstream report(reportFilename);
                report << "=== ADMIN REPORT ===\n";
                report << "Generated by: " << admin->getName() << " (" << admin->getId() << ")\n";
                report << "Date: " << getCurrentDate() << "\n\n";
                
                report << "=== EMPLOYEE SUMMARY ===\n";
                report << "Total Employees: " << employeeCount << "\n";
                report << "Departments: ";
                for (int i = 0; i < deptCount; i++) {
                    report << departments[i];
                    if (i < deptCount - 1) report << ", ";
                }
                report << "\n\n";
                
                report << "=== LEAVE SUMMARY ===\n";
                report << "Total Leave Requests: " << leaveCount << "\n";
                
                if (leaveCount > 0) {
                    ifstream leaveTypeFile("leave_requests.txt");
                    string leaveTypes[10];
                    int leaveTypeCount = 0;
                    int leaveTypeStats[10] = {0};
                    
                    while (getline(leaveTypeFile, line) && leaveTypeCount < 10) {
                        if (!line.empty()) {
                            size_t firstComma = line.find(',');
                            size_t secondComma = line.find(',', firstComma + 1);
                            if (firstComma != string::npos && secondComma != string::npos) {
                                string type = line.substr(firstComma + 1, secondComma - firstComma - 1);
                                bool found = false;
                                for (int i = 0; i < leaveTypeCount; i++) {
                                    if (leaveTypes[i] == type) {
                                        leaveTypeStats[i]++;
                                        found = true;
                                        break;
                                    }
                                }
                                if (!found) {
                                    leaveTypes[leaveTypeCount] = type;
                                    leaveTypeStats[leaveTypeCount]++;
                                    leaveTypeCount++;
                                }
                            }
                        }
                    }
                    leaveTypeFile.close();
                    
                    report << "Leave Types:\n";
                    for (int i = 0; i < leaveTypeCount; i++) {
                        report << "- " << leaveTypes[i] << ": " << leaveTypeStats[i] << " requests\n";
                    }
                }
                
                report << "\n=== SYSTEM SUMMARY ===\n";
                report << "Admins: " << AdminManager().getSize() << "\n";
                report << "Last Generated: " << ctime(&now);
                
                report.close();
                
                cout << "Report generated successfully!\n";
                cout << "Saved as: " << reportFilename << "\n";
                pauseScreen();
                break;
            }
            case 4:
                return;
            default:
                cout << "Invalid choice!\n";
                pauseScreen();
        }
    } while (true);
}

void employeeMenu(Employee& emp) {
    int choice;
    do {
        displayWelcomeMessage();
        cout << "EMPLOYEE MENU (ID: " << emp.getEmployeeID() << ")\n";
        cout << "1. View Profile\n";
        cout << "2. Update Profile\n";
        cout << "3. Change Password\n";
        cout << "4. Worklog Management\n";
        cout << "5. Leave Management\n";
        cout << "6. Logout\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            	system("cls");
            	displayWelcomeMessage();
                emp.showProfile();
                break;
            case 2:
            	system("cls");
            	displayWelcomeMessage();
                emp.updateProfile();
                break;
            case 3:system("cls");
            	displayWelcomeMessage();
                emp.changePassword();
                break;
            case 4: {
            	system("cls");
                int worklogChoice;
                do {
                    displayWelcomeMessage();
                    cout << "WORKLOG MANAGEMENT\n";
                    cout << "1. Add Worklog\n";
                    cout << "2. Edit Worklog\n";
                    cout << "3. Delete Worklog\n";
                    cout << "4. Search Worklog\n";
                    cout << "5. Sort Worklogs\n";
                    cout << "6. Generate Report\n";
                    cout << "7. Back to Employee Menu\n";
                    cout << "\nEnter your choice: ";
                    cin >> worklogChoice;
                    cin.ignore();

                    switch (worklogChoice) {
                        case 1:
                        	displayWelcomeMessage();
                            emp.addWorklogRecord();
                            break;
                        case 2:
                        	displayWelcomeMessage();
                            emp.editWorklogRecord();
                            break;
                        case 3:
                        	displayWelcomeMessage();
                            emp.deleteWorklogRecord();
                            break;
                        case 4:
                        	displayWelcomeMessage();
                            emp.searchWorklogRecord();
                            break;
                        case 5:
                        	displayWelcomeMessage();
                            emp.sortWorklogRecords();
                            break;
                        case 6:
                        	displayWelcomeMessage();
                            emp.generateSummaryReport();
                            break;
                        case 7:
                            break;
                        default:
                            cout << "Invalid choice!\n";
                            pauseScreen();
                    }
                } while (worklogChoice != 7);
                break;
            }
            case 5: {
            	system("cls");
                int leaveChoice;
                do {
                    displayWelcomeMessage();
                    cout << "LEAVE MANAGEMENT\n";
                    cout << "1. Request Leave\n";
                    cout << "2. View Leave Requests\n";
                    cout << "3. Back to Employee Menu\n";
                    cout << "\nEnter your choice: ";
                    cin >> leaveChoice;
                    cin.ignore();

                    switch (leaveChoice) {
                        case 1:
                            emp.requestLeave();
                            break;
                        case 2:
                            emp.viewLeaveRequests();
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Invalid choice!\n";
                            pauseScreen();
                    }
                } while (leaveChoice != 3);
                break;
            }
            case 6:
                return;
            default:
                cout << "Invalid choice!\n";
                pauseScreen();
        }
    } while (true);
}

int main() {
    int choice;
    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                SuperadminManager superadmin;
                if (superadmin.login()) {
                    superadmin.superadminMenu();
                }
                break;
            }
            case 2: {
                AdminManager adminManager;
                Admin* admin = adminManager.login();
                if (admin != nullptr) {
                    adminMenu(admin);
                }
                break;
            }
            case 3: {
                Employee emp;
                if (emp.loginEmployee()) {
                    employeeMenu(emp);
                }
                break;
            }
            case 4: {
                Employee emp;
                emp.registerEmployee();
                break;
            }
            case 5:
                displayExitMessage();
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
        pauseScreen();
    } while (true);

    return 0;
}