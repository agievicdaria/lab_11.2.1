#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_STUDENTS = 100;

enum Specialty
{
    COMPUTER_SCIENCE,
    INFORMATICS,
    MATH_ECON,
    PHYS_INF,
    HANDICRAFT
};

struct Student {
    int studentNumber;
    string lastName;
    int course;
    string specialty;
    int physicsGrade;
    int mathGrade;
    int computerScienceGrade;
};

string specialtyStr[] = {"computer science", "informatics", "math_economics", "physics_informatics", "handicraft"};

int readDataFromFile(const string& filename, Student students[MAX_STUDENTS]) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Unable to open the file: " << filename << endl;
        return false;
    }

    int studentNumber = 1;
    int count = 0;

    while (inputFile >> students[count].lastName >> students[count].course >> students[count].specialty >>
           students[count].physicsGrade >> students[count].mathGrade >> students[count].computerScienceGrade) {
        students[count].studentNumber = studentNumber++;
        count++;
    }

    inputFile.close();
    return count;
}

void displayTable(const Student students[MAX_STUDENTS], int count) {
    cout << "========================================================================================"
         << endl;
    cout << "| №  | Прізвище  | Курс | Спеціальність            | Фізика | Математика | Інформатика |"
         << endl;
    cout << "----------------------------------------------------------------------------------------"
         << endl;

    for (int i = 0; i < count; i++)
    {
        cout << "| " << setw(2) << right << i + 1 << " "
             << "| " << setw(10) << left << students[i].lastName
             << "| " << setw(5) << right << students[i].course
             << "| " << setw(25) << left << students[i].specialty
             << "| " << setw(7) << right << students[i].physicsGrade
             << "| " << setw(11) << right << students[i].mathGrade
             << "| " << setw(11) << right << students[i].computerScienceGrade << " |" << endl;
    }
    cout << "========================================================================================"
         << endl;
    cout << endl;
}

void findExcellentStudents(const Student students[MAX_STUDENTS], int count) {
    cout << "Excellent students:" << endl;

    for (int i = 0; i < count; ++i) {
        if (students[i].physicsGrade == 5 && students[i].mathGrade == 5 &&
            students[i].computerScienceGrade == 5) {
            cout << students[i].lastName << endl;
        }
    }
}

int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    Student students[MAX_STUDENTS];
    int count = readDataFromFile(filename, students);

    displayTable(students, count);

    findExcellentStudents(students, count);

    return 0;
}