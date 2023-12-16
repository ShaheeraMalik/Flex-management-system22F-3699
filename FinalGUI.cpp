#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<map>
// Forward declarations
class BasePerson;
class Administrator;
class Student;
class Teacher;
class FileManager;
class GUIManager;


// FileManager class for file operations
class FileManager {
public:
    // Reads data from a file and returns it as a string
    static std::string readFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << fileName << std::endl;
            return "";
        }

        std::string data, line;
        while (getline(file, line)) {
            data += line + "\n";
        }

        file.close();
        return data;
    }

    // Writes data to a file
    static void writeFile(const std::string& fileName, const std::string& data) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Unable to open file for writing: " << fileName << std::endl;
            return;
        }

        file << data;

        file.close();
    }
};
// BasePerson class
class BasePerson {
protected:
    std::string firstName;
    std::string lastName;
    std::string id;
    std::string department;
    std::string contactNo;
    std::string address;
    std::string registrationDate;
    std::string username;
    std::string password;

public:
    BasePerson(const std::string& fName, const std::string& lName, const std::string& id,
        const std::string& dept, const std::string& contNo, const std::string& addr,
        const std::string& regDate)
        : firstName(fName), lastName(lName), id(id), department(dept),
        contactNo(contNo), address(addr), registrationDate(regDate) {}

    virtual void signIn() = 0;
    virtual void viewDetails() const = 0;
    virtual void editDetails() = 0;


    // ... Other virtual functions
};

// Administrator class
class Administrator : public BasePerson {
public:
    Administrator(const std::string& fName, const std::string& lName, const std::string& id,
        const std::string& dept, const std::string& contNo, const std::string& addr,
        const std::string& regDate)
        : BasePerson(fName, lName, id, dept, contNo, addr, regDate) {
        // Additional initialization specific to Administrator can be added here
    }
    Administrator() : BasePerson("", "", "", "", "", "", "") {
        // Initialize with default values or add custom initialization logic
    }
    void signIn() override {
        std::string username, password;
        std::cout << "Admin Sign-In\nUsername: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;

        if (username == "admin" && password == "admin") {
            std::cout << "Administrator signed in successfully." << std::endl;
        }
        else {
            std::cout << "Invalid credentials." << std::endl;
        }
    }
    void viewDetails() const override {
        std::cout << "Viewing Administrator Details" << std::endl;

        // Assuming the administrator details are stored in "AdministratorDetails.txt"
        std::string details = FileManager::readFile("AdministratorDetails.txt");

        if (!details.empty()) {
            std::cout << "Administrator Details:\n" << details << std::endl;
        }
        else {
            std::cout << "No details found or unable to read file." << std::endl;
        }
    }
    void editDetails() override {
        std::cout << "Editing Administrator Details" << std::endl;

        std::cout << "Enter new first name (current: " << firstName << "): ";
        std::cin >> firstName;

        std::cout << "Enter new last name (current: " << lastName << "): ";
        std::cin >> lastName;

        std::cout << "Enter new contact number (current: " << contactNo << "): ";
        std::cin >> contactNo;

        std::cout << "Enter new address (current: " << address << "): ";
        std::cin >> address;

        // Here you can add more fields as per your requirement

        // Save the updated details to a file
        std::string data = "First Name: " + firstName + "\n"
            "Last Name: " + lastName + "\n"
            "Contact No: " + contactNo + "\n"
            "Address: " + address + "\n";

        FileManager::writeFile("AdministratorDetails.txt", data);
        std::cout << "Administrator details updated successfully." << std::endl;
    }
    void addNewTeacher() {
        std::string firstName, lastName, department, username, password, regDate, gender, contactNo, qualification, address;
        int departmentChoice;
        static int teacherCount = 0; // to keep track of the number of teachers

        std::cout << "Adding New Teacher" << std::endl;

        std::cout << "Enter First Name: ";
        std::cin >> firstName;

        std::cout << "Enter Last Name: ";
        std::cin >> lastName;

        std::cout << "Choose Department: \n1. Computer Science\n2. Electric Engineering\n3. Software Engineering\n4. Business\n5. Social Sciences\nEnter choice: ";
        std::cin >> departmentChoice;

        switch (departmentChoice) {
        case 1: department = "Computer Science"; break;
        case 2: department = "Electric Engineering"; break;
        case 3: department = "Software Engineering"; break;
        case 4: department = "Business"; break;
        case 5: department = "Social Sciences"; break;
        default: department = "Unknown"; break;
        }

        std::cout << "Enter Registration Date (YYYY-MM-DD): ";
        std::cin >> regDate;

        std::cout << "Enter Gender: ";
        std::cin >> gender;

        std::cout << "Enter Contact Number: ";
        std::cin >> contactNo;

        std::cout << "Enter Qualification: ";
        std::cin >> qualification;

        std::cout << "Enter Address: ";
        std::cin >> address;

        // Generate unique ID and credentials
        teacherCount++;
        std::string teacherId = department.substr(0, 1) + "-" + std::to_string(1000 + teacherCount);
        username = firstName.substr(0, 1) + lastName.substr(0, 1) + "-" + std::to_string(teacherCount);
        password = "teacher" + std::to_string(teacherCount);

        // Save the details to a file
        std::string data = "Teacher ID: " + teacherId + "\n"
            "First Name: " + firstName + "\n"
            "Last Name: " + lastName + "\n"
            "Department: " + department + "\n"
            "Username: " + username + "\n"
            "Password: " + password + "\n"
            "Registration Date: " + regDate + "\n"
            "Gender: " + gender + "\n"
            "Contact No: " + contactNo + "\n"
            "Qualification: " + qualification + "\n"
            "Address: " + address + "\n";

        FileManager::writeFile("Teacher.txt", data); // Assuming all teachers' details are stored in the same file
        std::cout << "New teacher added successfully. ID: " << teacherId << std::endl;
    }
    void addNewStudent() {
        std::string firstName, lastName, department, username, password, regDate, gender, contactNo, bloodGroup, address, feeStatus, qualification;
        int departmentChoice;
        static int studentCount = 0;  // to keep track of the number of students

        std::cout << "Adding New Student" << std::endl;

        std::cout << "Enter First Name: ";
        std::cin >> firstName;

        std::cout << "Enter Last Name: ";
        std::cin >> lastName;

        std::cout << "Choose Department: \n1. Computer Science\n2. Electric Engineering\n3. Software Engineering\n4. Business\n5. Social Sciences\nEnter choice: ";
        std::cin >> departmentChoice;

        switch (departmentChoice) {
        case 1: department = "Computer Science"; break;
        case 2: department = "Electric Engineering"; break;
        case 3: department = "Software Engineering"; break;
        case 4: department = "Business"; break;
        case 5: department = "Social Sciences"; break;
        default: department = "Unknown"; break;
        }

        std::cout << "Enter Registration Date (YYYY-MM-DD): ";
        std::cin >> regDate;

        std::cout << "Enter Gender: ";
        std::cin >> gender;

        std::cout << "Enter Contact Number: ";
        std::cin >> contactNo;

        std::cout << "Enter Blood Group: ";
        std::cin >> bloodGroup;

        std::cout << "Enter Address: ";
        std::cin >> address;

        std::cout << "Enter Fee Status: ";
        std::cin >> feeStatus;

        std::cout << "Enter Qualification: ";
        std::cin >> qualification;

        // Generate unique ID and credentials
        studentCount++;
        std::string studentId = department.substr(0, 2) + std::to_string(studentCount);
        username = "student" + std::to_string(studentCount);
        password = "pass" + std::to_string(studentCount);

        // Save the details to a file
        std::string data = "Student ID: " + studentId + "\n"
            "First Name: " + firstName + "\n"
            "Last Name: " + lastName + "\n"
            "Department: " + department + "\n"
            "Username: " + username + "\n"
            "Password: " + password + "\n"
            "Registration Date: " + regDate + "\n"
            "Gender: " + gender + "\n"
            "Contact No: " + contactNo + "\n"
            "Blood Group: " + bloodGroup + "\n"
            "Address: " + address + "\n"
            "Fee Status: " + feeStatus + "\n"
            "Qualification: " + qualification + "\n";

        FileManager::writeFile("Student.txt", data); // Assuming all students' details are stored in the same file
        std::cout << "New student added successfully. ID: " << studentId << std::endl;
    }
    void editStudentDetails() {
        std::string studentId;
        std::cout << "Enter Student ID to edit: ";
        std::cin >> studentId;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line;
        std::map<std::string, std::string> studentDetails;
        bool studentFound = false;

        // Parse and find the student
        while (getline(fileStream, line)) {
            auto delimiterPos = line.find(": ");
            auto key = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 2);

            if (key == "Student ID" && value == studentId) {
                studentFound = true;
            }

            if (studentFound) {
                studentDetails[key] = value;
                if (key == "Qualification") { // Assuming 'Qualification' is the last field for a student
                    break;
                }
            }
        }

        if (!studentFound) {
            std::cout << "Student ID not found." << std::endl;
            return;
        }

        // Allow editing of specific fields
        std::string newFirstName, newLastName, newFeeStatus, newAddress, newContactNo;
        std::cout << "Editing Student ID: " << studentId << std::endl;
        std::cout << "Enter new First Name (current: " << studentDetails["First Name"] << "): ";
        std::getline(std::cin >> std::ws, newFirstName);
        std::cout << "Enter new Last Name (current: " << studentDetails["Last Name"] << "): ";
        std::getline(std::cin >> std::ws, newLastName);
        std::cout << "Enter new Fee Status (current: " << studentDetails["Fee Status"] << "): ";
        std::getline(std::cin >> std::ws, newFeeStatus);
        std::cout << "Enter new Address (current: " << studentDetails["Address"] << "): ";
        std::getline(std::cin >> std::ws, newAddress);
        std::cout << "Enter new Contact No (current: " << studentDetails["Contact No"] << "): ";
        std::getline(std::cin >> std::ws, newContactNo);

        // Update the details in the map
        studentDetails["First Name"] = !newFirstName.empty() ? newFirstName : studentDetails["First Name"];
        studentDetails["Last Name"] = !newLastName.empty() ? newLastName : studentDetails["Last Name"];
        studentDetails["Fee Status"] = !newFeeStatus.empty() ? newFeeStatus : studentDetails["Fee Status"];
        studentDetails["Address"] = !newAddress.empty() ? newAddress : studentDetails["Address"];
        studentDetails["Contact No"] = !newContactNo.empty() ? newContactNo : studentDetails["Contact No"];

        // Save the updated details back to the file
        std::string updatedData;
        for (const auto& pair : studentDetails) {
            updatedData += pair.first + ": " + pair.second + "\n";
        }

        FileManager::writeFile("Student.txt", updatedData); // This will overwrite the existing file
        std::cout << "Student details updated successfully." << std::endl;
    }
    void editTeacherDetails() {
        std::string teacherId;
        std::cout << "Enter Teacher ID to edit: ";
        std::cin >> teacherId;

        std::string fileData = FileManager::readFile("Teacher.txt");
        std::istringstream fileStream(fileData);
        std::string line;
        std::map<std::string, std::string> teacherDetails;
        bool teacherFound = false;

        // Parse and find the teacher
        while (getline(fileStream, line)) {
            auto delimiterPos = line.find(": ");
            auto key = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 2);

            if (key == "Teacher ID" && value == teacherId) {
                teacherFound = true;
            }

            if (teacherFound) {
                teacherDetails[key] = value;
                if (key == "Qualification") { // Assuming 'Qualification' is the last field for a teacher
                    break;
                }
            }
        }

        if (!teacherFound) {
            std::cout << "Teacher ID not found." << std::endl;
            return;
        }

        // Allow editing of specific fields
        std::string newAddress, newContactNo, newQualification, newSalary;
        std::cout << "Editing Teacher ID: " << teacherId << std::endl;
        std::cout << "Enter new Address (current: " << teacherDetails["Address"] << "): ";
        std::getline(std::cin >> std::ws, newAddress);
        std::cout << "Enter new Contact No (current: " << teacherDetails["Contact No"] << "): ";
        std::getline(std::cin >> std::ws, newContactNo);
        std::cout << "Enter new Qualification (current: " << teacherDetails["Qualification"] << "): ";
        std::getline(std::cin >> std::ws, newQualification);
        std::cout << "Enter new Salary (optional): ";
        std::getline(std::cin >> std::ws, newSalary);

        // Update the details in the map
        teacherDetails["Address"] = !newAddress.empty() ? newAddress : teacherDetails["Address"];
        teacherDetails["Contact No"] = !newContactNo.empty() ? newContactNo : teacherDetails["Contact No"];
        teacherDetails["Qualification"] = !newQualification.empty() ? newQualification : teacherDetails["Qualification"];
        if (!newSalary.empty()) {
            teacherDetails["Salary"] = newSalary;
        }

        // Save the updated details back to the file
        std::string updatedData;
        for (const auto& pair : teacherDetails) {
            updatedData += pair.first + ": " + pair.second + "\n";
        }

        FileManager::writeFile("Teacher.txt", updatedData); // This will overwrite the existing file
        std::cout << "Teacher details updated successfully." << std::endl;
    }
    void viewAllStudents() {
        std::string fileData = FileManager::readFile("Student.txt");
        if (fileData.empty()) {
            std::cout << "No student data found or unable to read file." << std::endl;
            return;
        }

        std::istringstream fileStream(fileData);
        std::string line;
        std::cout << "All Registered Students:" << std::endl;
        std::cout << "------------------------------------" << std::endl;

        while (getline(fileStream, line)) {
            // Assuming each student's record is separated by a blank line
            if (line.empty()) {
                std::cout << "------------------------------------" << std::endl;
                continue;
            }
            std::cout << line << std::endl;
        }

        std::cout << "------------------------------------" << std::endl;
    }
    void viewAllTeachers() {
        std::string fileData = FileManager::readFile("Teacher.txt");
        if (fileData.empty()) {
            std::cout << "No teacher data found or unable to read file." << std::endl;
            return;
        }

        std::istringstream fileStream(fileData);
        std::string line;
        std::cout << "All Registered Teachers:" << std::endl;
        std::cout << "------------------------------------" << std::endl;

        while (getline(fileStream, line)) {
            // Assuming each teacher's record is separated by a blank line
            if (line.empty()) {
                std::cout << "------------------------------------" << std::endl;
                continue;
            }
            std::cout << line << std::endl;
        }

        std::cout << "------------------------------------" << std::endl;
    }
};

// Student class
class Student : public BasePerson {
    std::string studentId;
    std::string username;
    std::string password;
public:

    Student(const std::string& fName, const std::string& lName, const std::string& id,
        const std::string& dept, const std::string& contNo, const std::string& addr,
        const std::string& regDate, const std::string& user, const std::string& pass)
        : BasePerson(fName, lName, id, dept, contNo, addr, regDate), studentId(id),
        username(user), password(pass) {}
    Student() : BasePerson("", "", "", "", "", "", "") {
        // Initialize with default values or add custom initialization logic
    }

    void signIn() override {
        std::string inputUsername, inputPassword;
        std::cout << "Student Sign-In\nUsername: ";
        std::cin >> inputUsername;
        std::cout << "Password: ";
        std::cin >> inputPassword;

        // Read student details from file
        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line;

        bool credentialsValid = false;
        while (getline(fileStream, line)) {
            if (line.find("Username: " + inputUsername) != std::string::npos) {
                std::string nextLine;
                getline(fileStream, nextLine); // This should be the password line
                if (nextLine.find("Password: " + inputPassword) != std::string::npos) {
                    credentialsValid = true;
                    break;
                }
            }
        }

        if (credentialsValid) {
            std::cout << "Login successful." << std::endl;
            // Further code for successful login
        }
        else {
            std::cout << "Invalid credentials." << std::endl;
            // Code for handling invalid login
        }
    }
    void editDetails() override {
        std::cout << "Editing Student Details" << std::endl;

        std::cout << "Enter new first name (current: " << firstName << "): ";
        std::cin >> firstName;

        std::cout << "Enter new last name (current: " << lastName << "): ";
        std::cin >> lastName;

        std::cout << "Enter new contact number (current: " << contactNo << "): ";
        std::cin >> contactNo;

        std::cout << "Enter new address (current: " << address << "): ";
        std::cin >> address;

        // Additional details specific to Student can be added here
        // For example, updating the department, fee status, etc.

        // Save the updated details to a file
        std::string data = "First Name: " + firstName + "\n"
            "Last Name: " + lastName + "\n"
            "Contact No: " + contactNo + "\n"
            "Address: " + address + "\n"
            // Include other updated details in the data string
            ;

        FileManager::writeFile("Studen.txt", data);
        std::cout << "Student details updated successfully." << std::endl;
    }
    void viewDetails() const override {
        std::cout << "Viewing Student Details" << std::endl;

        // Assuming the student details are stored in "StudentDetails.txt"
        std::string details = FileManager::readFile("Student.txt");

        if (!details.empty()) {
            std::cout << "Student Details:\n" << details << std::endl;
        }
        else {
            std::cout << "No details found or unable to read file." << std::endl;
        }
    }
    void viewAttendance() {
        std::cout << "Viewing Attendance for Student ID: " << studentId << std::endl;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line;
        bool attendanceFound = false;

        // Parse and find the student's attendance record
        while (getline(fileStream, line)) {
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                attendanceFound = true;
                std::cout << "Attendance Record for " << firstName << " " << lastName << " (ID: " << studentId << "):" << std::endl;
            }

            if (attendanceFound) {
                if (line.empty()) { // Assuming each student's attendance record is separated by a blank line
                    break;
                }
                std::cout << line << std::endl;
            }
        }

        if (!attendanceFound) {
            std::cout << "Attendance record not found for Student ID: " << studentId << std::endl;
        }
    }
    void viewMarks() {
        std::cout << "Viewing Marks for Student ID: " << studentId << std::endl;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line;
        bool marksFound = false;

        // Parse and find the student's marks record
        while (getline(fileStream, line)) {
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                marksFound = true;
                std::cout << "Marks Record for " << firstName << " " << lastName << " (ID: " << studentId << "):" << std::endl;
            }

            if (marksFound) {
                if (line.empty()) { // Assuming each student's marks record is separated by a blank line
                    break;
                }
                std::cout << line << std::endl;
            }
        }

        if (!marksFound) {
            std::cout << "Marks record not found for Student ID: " << studentId << std::endl;
        }
    }
    void viewGrades() {
        std::cout << "Viewing Grades for Student ID: " << studentId << std::endl;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line;
        bool gradesFound = false;

        // Parse and find the student's grade record
        while (getline(fileStream, line)) {
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                gradesFound = true;
                std::cout << "Grades Record for " << firstName << " " << lastName << " (ID: " << studentId << "):" << std::endl;
            }

            if (gradesFound) {
                if (line.empty()) { // Assuming each student's grades record is separated by a blank line
                    break;
                }
                std::cout << line << std::endl;
            }
        }

        if (!gradesFound) {
            std::cout << "Grades record not found for Student ID: " << studentId << std::endl;
        }
    }
    void viewRegisteredCourses() {
        std::cout << "Viewing Registered Courses for Student ID: " << studentId << std::endl;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line;
        bool coursesFound = false;

        // Parse and find the student's registered courses
        while (getline(fileStream, line)) {
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                coursesFound = true;
                std::cout << "Registered Courses for " << firstName << " " << lastName << " (ID: " << studentId << "):" << std::endl;
            }

            if (coursesFound) {
                if (line.empty()) { // Assuming each student's courses record is separated by a blank line
                    break;
                }
                std::cout << line << std::endl;
            }
        }

        if (!coursesFound) {
            std::cout << "No registered courses found for Student ID: " << studentId << std::endl;
        }
    }
    void viewFeeStatus() {
        std::cout << "Viewing Fee Status for Student ID: " << studentId << std::endl;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line;
        bool feeStatusFound = false;

        // Parse and find the student's fee status
        while (getline(fileStream, line)) {
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                feeStatusFound = true;
                std::cout << "Fee Status for " << firstName << " " << lastName << " (ID: " << studentId << "):" << std::endl;
            }

            if (feeStatusFound) {
                if (line.find("Fee Status: ") != std::string::npos) {
                    std::cout << line << std::endl;
                    break;
                }
            }
        }

        if (!feeStatusFound) {
            std::cout << "No fee status found for Student ID: " << studentId << std::endl;
        }
    }
};

// Teacher class
class Teacher : public BasePerson {
    std::string teacherId;
    std::string username;
    std::string password;
public:
    Teacher(const std::string& fName, const std::string& lName, const std::string& id,
        const std::string& dept, const std::string& contNo, const std::string& addr,
        const std::string& regDate, const std::string& user, const std::string& pass)
        : BasePerson(fName, lName, id, dept, contNo, addr, regDate), teacherId(id),
        username(user), password(pass) {}
    Teacher() : BasePerson("", "", "", "", "", "", "") {
        // Initialize with default values or add custom initialization logic
    }

    void signIn() override {
        std::string inputUsername, inputPassword;
        std::cout << "Teacher Sign-In\nUsername: ";
        std::cin >> inputUsername;
        std::cout << "Password: ";
        std::cin >> inputPassword;

        // Read teacher details from file
        std::string fileData = FileManager::readFile("Teacher.txt");
        std::istringstream fileStream(fileData);
        std::string line;

        bool credentialsValid = false;
        while (getline(fileStream, line)) {
            if (line.find("Username: " + inputUsername) != std::string::npos) {
                std::string nextLine;
                getline(fileStream, nextLine); // This should be the password line
                if (nextLine.find("Password: " + inputPassword) != std::string::npos) {
                    credentialsValid = true;
                    break;
                }
            }
        }

        if (credentialsValid) {
            std::cout << "Login successful." << std::endl;
            // Further code for successful login
        }
        else {
            std::cout << "Invalid credentials." << std::endl;
            // Code for handling invalid login
        }
    }
    void editDetails() override {
        std::cout << "Editing Teacher Details" << std::endl;

        std::cout << "Enter new first name (current: " << firstName << "): ";
        std::cin >> firstName;

        std::cout << "Enter new last name (current: " << lastName << "): ";
        std::cin >> lastName;

        std::cout << "Enter new contact number (current: " << contactNo << "): ";
        std::cin >> contactNo;

        std::cout << "Enter new address (current: " << address << "): ";
        std::cin >> address;

        std::cout << "Enter new qualification: ";
        std::string qualification;
        std::cin >> qualification;

        // Here you can add more fields as per your requirement

        // Save the updated details to a file
        std::string data = "First Name: " + firstName + "\n"
            "Last Name: " + lastName + "\n"
            "Contact No: " + contactNo + "\n"
            "Address: " + address + "\n"
            "Qualification: " + qualification + "\n";

        FileManager::writeFile("Teacher.txt", data);
        std::cout << "Teacher details updated successfully." << std::endl;
    }
    void viewDetails() const override {
        std::cout << "Viewing Teacher Details" << std::endl;

        // Assuming the teacher details are stored in "TeacherDetails.txt"
        std::string details = FileManager::readFile("Teacher.txt");

        if (!details.empty()) {
            std::cout << "Teacher Details:\n" << details << std::endl;
        }
        else {
            std::cout << "No details found or unable to read file." << std::endl;
        }
    }
    void teacherTimetable() {
        std::cout << "Timetable for Teacher: " << firstName << " " << lastName << "\n";
        std::cout << "-----------------------------------\n";

        // Mock timetable data for each day of the week
        std::cout << "Monday:\n";
        std::cout << "  09:00 - 10:00: Computer Science Class\n";
        std::cout << "  11:00 - 12:00: Lab Session\n\n";

        std::cout << "Tuesday:\n";
        std::cout << "  10:00 - 11:00: Software Engineering Class\n";
        std::cout << "  14:00 - 15:00: Department Meeting\n\n";

        std::cout << "Wednesday:\n";
        std::cout << "  09:00 - 11:00: Research Time\n";
        std::cout << "  13:00 - 14:30: Advanced Algorithms Class\n\n";

        std::cout << "Thursday:\n";
        std::cout << "  10:00 - 12:00: Project Supervision\n";
        std::cout << "  15:00 - 16:00: Open Office Hours\n\n";

        std::cout << "Friday:\n";
        std::cout << "  09:00 - 10:30: Data Structures Class\n";
        std::cout << "  11:00 - 12:30: Faculty Seminar\n\n";

        // Optionally, include weekend activities if relevant
        std::cout << "Saturday:\n";
        std::cout << "  Free Day / No Scheduled Classes\n\n";

        std::cout << "Sunday:\n";
        std::cout << "  Free Day / No Scheduled Classes\n\n";

        std::cout << "Note: This is a mock timetable. Actual schedule may vary.\n";
    }
    void assignMarks() {
        std::string studentId;
        std::cout << "Enter Student ID to assign marks: ";
        std::cin >> studentId;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line, updatedData;
        bool studentFound = false, updated = false;

        while (getline(fileStream, line)) {
            // Check if the line contains the student ID
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                studentFound = true;
            }

            if (studentFound) {
                // If the marks line is found, update it
                if (line.find("Marks: ") != std::string::npos) {
                    std::string newMarks;
                    std::cout << "Enter new marks for Student ID " << studentId << ": ";
                    std::cin >> newMarks;
                    line = "Marks: " + newMarks;
                    updated = true;
                }
            }

            // Add the line to updated data
            updatedData += line + "\n";

            // If it's the end of a student record
            if (line.empty() && studentFound) {
                if (!updated) {
                    // If marks were not found, add them
                    std::string newMarks;
                    std::cout << "Enter new marks for Student ID " << studentId << ": ";
                    std::cin >> newMarks;
                    updatedData += "Marks: " + newMarks + "\n";
                }
                break;
            }
        }

        if (!studentFound) {
            std::cout << "Student ID not found." << std::endl;
            return;
        }

        // Write the updated data back to the file
        FileManager::writeFile("Student.txt", updatedData);
        std::cout << "Marks updated successfully for Student ID: " << studentId << std::endl;
    }
    void markingAttendance() {
        std::string studentId;
        std::cout << "Enter Student ID to mark attendance: ";
        std::cin >> studentId;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line, updatedData;
        bool studentFound = false, updated = false;

        while (getline(fileStream, line)) {
            // Check if the line contains the student ID
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                studentFound = true;
            }

            if (studentFound) {
                // If the attendance line is found, update it
                if (line.find("Attendance: ") != std::string::npos) {
                    std::string newAttendance;
                    std::cout << "Enter new attendance status for Student ID " << studentId << " (P/A): ";
                    std::cin >> newAttendance;
                    line = "Attendance: " + newAttendance;
                    updated = true;
                }
            }

            // Add the line to updated data
            updatedData += line + "\n";

            // If it's the end of a student record
            if (line.empty() && studentFound) {
                if (!updated) {
                    // If attendance was not found, add it
                    std::string newAttendance;
                    std::cout << "Enter new attendance status for Student ID " << studentId << " (P/A): ";
                    std::cin >> newAttendance;
                    updatedData += "Attendance: " + newAttendance + "\n";
                }
                break;
            }
        }

        if (!studentFound) {
            std::cout << "Student ID not found." << std::endl;
            return;
        }

        // Write the updated data back to the file
        FileManager::writeFile("Student.txt", updatedData);
        std::cout << "Attendance updated successfully for Student ID: " << studentId << std::endl;
    }
    void assignGrades() {
        std::string studentId;
        std::cout << "Enter Student ID to assign grades: ";
        std::cin >> studentId;

        std::string fileData = FileManager::readFile("Student.txt");
        std::istringstream fileStream(fileData);
        std::string line, updatedData;
        bool studentFound = false, updated = false;

        while (getline(fileStream, line)) {
            // Check if the line contains the student ID
            if (line.find("Student ID: " + studentId) != std::string::npos) {
                studentFound = true;
            }

            if (studentFound) {
                // If the grade line is found, update it
                if (line.find("Grade: ") != std::string::npos) {
                    std::string newGrade;
                    std::cout << "Enter new grade for Student ID " << studentId << ": ";
                    std::cin >> newGrade;
                    line = "Grade: " + newGrade;
                    updated = true;
                }
            }

            // Add the line to updated data
            updatedData += line + "\n";

            // If it's the end of a student record
            if (line.empty() && studentFound) {
                if (!updated) {
                    // If grade was not found, add it
                    std::string newGrade;
                    std::cout << "Enter new grade for Student ID " << studentId << ": ";
                    std::cin >> newGrade;
                    updatedData += "Grade: " + newGrade + "\n";
                }
                break;
            }
        }

        if (!studentFound) {
            std::cout << "Student ID not found." << std::endl;
            return;
        }

        // Write the updated data back to the file
        FileManager::writeFile("Student.txt", updatedData);
        std::cout << "Grades updated successfully for Student ID: " << studentId << std::endl;
    }

};
class GUIManager {
public:
    // Function to create a new SFML window
    static void initializeWindow(sf::RenderWindow& window, const std::string& title, int width, int height) {
        window.create(sf::VideoMode(width, height), title);
    }

    // Function to draw text on a window
    static void drawText(sf::RenderWindow& window, const std::string& text, int x, int y, unsigned int fontSize, sf::Color color) {
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            // Handle error
        }
        sf::Text sfText;
        sfText.setFont(font);
        sfText.setString(text);
        sfText.setCharacterSize(fontSize);
        sfText.setFillColor(color);
        sfText.setPosition(static_cast<float>(x), static_cast<float>(y));
        window.draw(sfText);
    }

    // Add more functions as needed for buttons, shapes, images, etc.
};
// Main function
void administratorMenu(Administrator& admin, sf::RenderWindow& window) {
    bool adminSession = true;
    while (adminSession) {
        std::cout << "\nAdministrator Menu:\n";
        std::cout << "1. Add New Teacher\n";
        std::cout << "2. Add New Student\n";
        std::cout << "3. Edit Student Details\n";
        std::cout << "4. Edit Teacher Details\n";
        std::cout << "5. View All Students\n";
        std::cout << "6. View All Teachers\n";
        std::cout << "7. Logout\n";
        std::cout << "Enter your choice: ";

        int adminChoice;
        std::cin >> adminChoice;

        switch (adminChoice) {
        case 1:
            admin.addNewTeacher();
            break;
        case 2:
            admin.addNewStudent();
            break;
        case 3:
            admin.editStudentDetails();
            break;
        case 4:
            admin.editTeacherDetails();
            break;
        case 5:
            admin.viewAllStudents();
            break;
        case 6:
            admin.viewAllTeachers();
            break;
        case 7:
            adminSession = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

        // Example of using GUIManager to display text in SFML window
        window.clear();
        GUIManager::drawText(window, "Administrator Panel", 50, 50, 24, sf::Color::White);
        window.display();

        // Check for window close event
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                adminSession = false;
            }
        }
    }
}
void teacherMenu(Teacher& teacher, sf::RenderWindow& window) {
    bool teacherSession = true;
    while (teacherSession) {
        std::cout << "\nTeacher Menu:\n";
        std::cout << "1. View Timetable\n";
        std::cout << "2. Assign Marks\n";
        std::cout << "3. Mark Attendance\n";
        std::cout << "4. Assign Grades\n";
        std::cout << "5. Logout\n";
        std::cout << "Enter your choice: ";

        int teacherChoice;
        std::cin >> teacherChoice;

        switch (teacherChoice) {
        case 1:
            teacher.teacherTimetable();
            break;
        case 2:
            teacher.assignMarks();
            break;
        case 3:
            teacher.markingAttendance();
            break;
        case 4:
            teacher.assignGrades();
            break;
        case 5:
            teacherSession = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

        // Example of using GUIManager to display text in SFML window
        window.clear();
        GUIManager::drawText(window, "Teacher Panel", 50, 50, 24, sf::Color::White);
        window.display();

        // Check for window close event
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                teacherSession = false;
            }
        }
    }
}
void studentMenu(Student& student, sf::RenderWindow& window) {
    bool studentSession = true;
    while (studentSession) {
        std::cout << "\nStudent Menu:\n";
        std::cout << "1. View Details\n";
        std::cout << "2. View Attendance\n";
        std::cout << "3. View Marks\n";
        std::cout << "4. View Grades\n";
        std::cout << "5. View Registered Courses\n";
        std::cout << "6. View Fee Status\n";
        std::cout << "7. Logout\n";
        std::cout << "Enter your choice: ";

        int studentChoice;
        std::cin >> studentChoice;

        switch (studentChoice) {
        case 1:
            student.viewDetails();
            break;
        case 2:
            student.viewAttendance();
            break;
        case 3:
            student.viewMarks();
            break;
        case 4:
            student.viewGrades();
            break;
        case 5:
            student.viewRegisteredCourses();
            break;
        case 6:
            student.viewFeeStatus();
            break;
        case 7:
            studentSession = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }

        // Example of using GUIManager to display text in SFML window
        window.clear();
        GUIManager::drawText(window, "Student Panel", 50, 50, 24, sf::Color::White);
        window.display();

        // Check for window close event
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                studentSession = false;
            }
        }
    }
}
int main() {
    sf::RenderWindow window;
    GUIManager::initializeWindow(window, "Flex Management System", 800, 600);

    // Load and play background music using SFML
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:/Users/HP/Downloads/hope.mp3")) 
    {
        // Handle error
    }
    backgroundMusic.play();
    backgroundMusic.setLoop(true);

    // Main menu loop
    bool running = true;
    while (running) {
        // Display main menu options
        std::cout << "1. Administrator\n2. Teacher\n3. Student\n4. Exit\nEnter choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Administrator login and functionalities
            Administrator admin;
            admin.signIn();
            administratorMenu(admin, window);
            // Display Administrator-specific options
            break;
        }
        case 2: {
            // Teacher login and functionalities
            Teacher teacher;
            teacher.signIn();
            teacherMenu(teacher, window);
            // Display Teacher-specific options
            break;
        }
        case 3: {
            // Student login and functionalities
            Student student;
            student.signIn();
            studentMenu(student, window); // Student menu functionality

            // Display Student-specific options
            break;
        }
        case 4:
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        // SFML event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                running = false;
            }
        }

        window.clear();
        // Draw graphics, text, etc. using GUIManager
        window.display();
    }
    system("pause");
    return 0;
}