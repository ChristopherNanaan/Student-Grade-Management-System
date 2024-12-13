#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void AddStudentRecords();      // Function Declarations 
void ModifyStudentRecords();
void DeleteStudentRecords();
void ViewAllRecords();
void CalculateAndDisplayFinalGrades();
void SaveRecordsToFile();
void LoadRecordsFromFile();

class Student {                // class named Student with attributes listed below 
public:
    string name;
    string ID;
    vector<int> QuizScore;     // vector to hold Students quiz scores
    vector<int> ProjectScore;  // Vector to hold Students project scores
    int FinalExamScore = 0;
    double FinalGradeScore = 0.0;
    string LetterGrade;
};

vector<Student> students;    // Vector to hold all of the students information (Everything listed in Student)

void AddStudentRecords() {   // Function that takes all of the student information and stores it in a vector called (students)
    int numberOfStudents;    
    cout << "Enter the number of students to add: ";
    cin >> numberOfStudents; // user enters how many students they want to add to the program

    for (int i = 0; i < numberOfStudents; ++i) { // loop goes through the number of students added by user 
        Student student;
        cout << "Enter Student " << i + 1 << " Information:\n";  // Outputs as: Enter Student 1 Information: and so forth.
        cout << "Name: ";
        cin >> student.name; // Takes the value that the user inputed and stores it as (name) in the (class Student) 
        cout << "ID: ";      
        cin >> student.ID;   // Takes the value that the user inputed and stores it as (ID) in the (class Student)

        cout << "Enter 10 quiz scores (separated by spaces): ";
        student.QuizScore.clear();        // .clear() used to reset the old data before taking in new data to prevent conflict with existing data in the vector
        for (int j = 0; j < 10; ++j) {    // loop created to take in 10 quiz grades for each student 
            int score;                    
            cin >> score;                 // stores the value entered by user as a variable called (score) 
            student.QuizScore.push_back(score);    // adds value that was stored in (score) to the end of the QuizScore vector through the use of .pushback() 
        }   // student.QuizScore adds the quiz score for the specified student

        cout << "Enter 2 project scores (separated by spaces): ";
        student.ProjectScore.clear();     // .clear() used to reset the old data before taking in new data to prevent conflict with existing data in the vector
        for (int j = 0; j < 2; ++j) {     // loop created to take in 2 project grades for each student 
            int score;                    
            cin >> score;                 // stores the value entered by user as a variable called (score)
            student.ProjectScore.push_back(score); // adds value that was stored in (score) to the end of the ProjectScore vector through the use of .pushback() 
        }   // student.ProjectScore adds the project score for the specified student

        cout << "Enter Final Exam Score: ";
        cin >> student.FinalExamScore; // takes the value the user inputed and stores it as (FinalExamScore) in the  (class Student)  
        students.push_back(student);   // adds all the information that was asked including the final exam score in a new single vector called students
    }   // There is three vectors 1. Quiz Scores , 2. Project Scores , 3. Takes all the information in student and stores it in a single vector  
}       // Third Vector (students) will have [name, ID, QuizScore, ProjectScore, FinalExamScore, LetterGrade] for each student that is entered

void ModifyStudentRecords() {  // Function that allows the user to make modifications to the given information in the program 
    string id;                 // creates a new variable called (id)
    cout << "Enter Student ID to modify: ";
    cin >> id;                 // user enters the student id they wish to modify and stores it as (id)

    for (auto &student : students) {  // range-based for loop, (auto) automatically determines the variable type which is (Student), (&student) is a reference used to modify the information in the vector (students)   
        if (student.ID == id) {       // used to find the ID the user wants to modify 
            int option;
            cout << "What would you like to modify?\n"
                 << "1) Quiz Scores\n"
                 << "2) Project Scores\n"
                 << "3) Final Exam Score\n"
                 << "Enter your choice: ";
            cin >> option;            // takes the input from user which will be 1,2, or 3

            switch (option) {
                case 1:
                    cout << "Enter 10 new quiz scores: ";
                    student.QuizScore.clear();           
                    for (int i = 0; i < 10; ++i) {    // for loop used to input new quiz grades 
                        int score;
                        cin >> score;
                        student.QuizScore.push_back(score);
                    }
                    break;
                case 2:
                    cout << "Enter 2 new project scores: ";
                    student.ProjectScore.clear();
                    for (int i = 0; i < 2; ++i) {    // for loop used to input new project grades 
                        int score;
                        cin >> score;
                        student.ProjectScore.push_back(score);
                    }
                    break;
                case 3:
                    cout << "Enter new Final Exam Score: ";
                    cin >> student.FinalExamScore;   // takes in new final exam score 
                    break;
                default:
                    cout << "Invalid option.\n";     // Displayed if user does not pick 1 of the 3 options listed 
            }
            return;
        }
    }
    cout << "Student ID not found.\n";    // Displayed if users input of the ID is not found 
}

void DeleteStudentRecords() {
    string id;
    cout << "Enter Student ID to delete: ";
    cin >> id;

    for (auto it = students.begin(); it != students.end(); ++it) { //.begin() points to first element, .end()points past the last element in the vector, the loop stops before .end()
        if (it->ID == id) {                  // (it) is used as a pointer for the elements in the vector, (++it) moves (it) through the vector
            students.erase(it);              // deletes the given student ID 
            cout << "Record deleted successfully.\n";
            return;
        }
    }
    cout << "Student ID not found.\n";
}

void ViewAllRecords() {                     // function used to view students records given by user 
    if (students.empty()) {                 // checks to see if the vector is empty 
        cout << "No records available.\n";  // displayed if a empty vector is found 
        return;
    }

    for (const auto &student : students) {       // goes through (students vector) which contains all the (Student Objects)
        cout << "Name: " << student.name << ", ID: " << student.ID << "\n"; // prints students name and ID 
        cout << "Quiz Scores: ";
        for (int score : student.QuizScore) {    // prints student quiz scores 
            cout << score << " ";
        }
        cout << "\nProject Scores: ";
        for (int score : student.ProjectScore) { // prints student project scores 
            cout << score << " ";
        }
        cout << "\nFinal Exam Score: " << student.FinalExamScore << "\n";  // prints student final exam score 
        cout << "Final Grade: " << student.FinalGradeScore << " (" << student.LetterGrade << ")\n\n";  // prints students final grade score and letter grade score 
    }
}

void CalculateAndDisplayFinalGrades() {   // function used to display calculated final grades 
    for (auto &student : students) {
        int totalQuizScore = 0;
        for (int score : student.QuizScore) {
            totalQuizScore += score;      // adds all the scores of the quiz 
        }

        int totalProjectScore = 0;
        for (int score : student.ProjectScore) {
            totalProjectScore += score;   // adds all the scores of the project 
        }

        student.FinalGradeScore = (totalQuizScore / 10.0) * 0.4 + (totalProjectScore / 2.0) * 0.3 + student.FinalExamScore * 0.3; // gives total weighed grade 

        if (student.FinalGradeScore >= 90)
            student.LetterGrade = "A";
        else if (student.FinalGradeScore >= 80)
            student.LetterGrade = "B";
        else if (student.FinalGradeScore >= 70)
            student.LetterGrade = "C";
        else if (student.FinalGradeScore >= 60)
            student.LetterGrade = "D";
        else
            student.LetterGrade = "F";
    }

    ViewAllRecords();
}

void SaveRecordsToFile() {                              // function that saves the data used in the program onto a file 
    ofstream file("student_records.txt");
    if (!file) {
        cout << "Error opening file for saving.\n";     // displayed if there is any problems with saving records to file 
        return;
    }

    for (const auto &student : students) {
        file << student.name << " " << student.ID << "\n";   //outputs name and ID to file 
        for (int score : student.QuizScore) {
            file << score << " ";                    //outputs quiz scores to file  
        }
        file << "\n";
        for (int score : student.ProjectScore) {
            file << score << " ";                    // outputs project scores to file 
        }
        file << "\n";
        file << student.FinalExamScore << "\n";      // outputs final exam score to file
        file << student.FinalGradeScore << "\n";     // outputs final grade score to file 
        file << student.LetterGrade << "\n";         // outputs final letter grade to file 
    }

    cout << "Records saved successfully.\n";
}

void LoadRecordsFromFile() {                         // function that loads information that has been saved on a file 
    ifstream file("student_records.txt");
    if (!file) {
        cout << "Error opening file for loading.\n"; // displayed if file does not exist or cannot be opened 
        return;
    }

    students.clear();                       // .clear() used to reset the old data before taking in new data to prevent conflict with existing data in the vector
    while (file) {                          // keeps looping as long as the file stream (file) is in a good state
        Student student;
        file >> student.name >> student.ID; // loads student name and ID from file 
        if (file.eof()) break;              // file.eof() checks if end of file has reached, exits loop if true 

        student.QuizScore.clear();
        for (int i = 0; i < 10; ++i) {
            int score;
            file >> score;                      // loads student quiz score from file 
            student.QuizScore.push_back(score); // adds the scors to the QuizScors vector
        }

        student.ProjectScore.clear();
        for (int i = 0; i < 2; ++i) {
            int score;
            file >> score;                // loads student project score from file 
            student.ProjectScore.push_back(score); // adds the scores to the ProjectScores vector 
        }

        file >> student.FinalExamScore;   // loads student final exam score from file  
        file >> student.FinalGradeScore;  // loads student final grade score from file 
        file >> student.LetterGrade;      // loads student letter grade from file 

        students.push_back(student);      // adds all of the information stored in the Class (Student) into the (vector students)
    }

    cout << "Records loaded successfully.\n";
}

void Menu() {      // Displays the menu which calls to the functions for each part of the menu 
    while (true) {
        cout << "\nPlease select an option:\n"
             << "1) Add Student Records\n"
             << "2) Modify Student Records\n"
             << "3) Delete Student Records\n"
             << "4) View All Records\n"
             << "5) Calculate and Display Final Grades\n"
             << "6) Save Records to File\n"
             << "7) Load Records from File\n"
             << "8) Exit\n"
             << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {  // Depending on what chocie the user inputs it calls the following functions listed below associated with it
            case 1:
                AddStudentRecords();
                break;
            case 2:
                ModifyStudentRecords();
                break;
            case 3:
                DeleteStudentRecords();
                break;
            case 4:
                ViewAllRecords();
                break;
            case 5:
                CalculateAndDisplayFinalGrades();
                break;
            case 6:
                SaveRecordsToFile();
                break;
            case 7:
                LoadRecordsFromFile();
                break;
            case 8:
                cout << "Exiting the program. Goodbye!\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {      // Main Code 
    Menu();       // Calls the Menu Function 
      return 0;
}
