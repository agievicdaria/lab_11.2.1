#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

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

struct Student
{
    string lastName;
    int course;
    Specialty specialty;
    int physicsGrade;
    int mathGrade;
    int informaticsGrade;
};

string specialtyStr[] = {"Computer Science", "Informatics", "Math Economics", "Physics Informatics", "Handicraft"};

void writeStudentToFile(const string &fileName, const Student &student, int &studentCount)
{
    ofstream outFile(fileName, ios::binary | ios::app);

    if (outFile.is_open())
    {
        outFile.write((char *)&student, sizeof(Student));
        outFile.close();
        ++studentCount;
    }
    else
    {
        cerr << "Error opening file for writing.\n";
    }
}

void inputStudents(const string &fileName, int &numberOfStudents)
{
    int studentCount;
    cout << "Enter the number of students: ";
    cin >> studentCount;

    for (int i = 0; i < studentCount && numberOfStudents < MAX_STUDENTS; ++i)
    {
        Student student;
        cout << "Student " << (i + 1) << ":\n";
        cout << "Last Name: ";
        cin >> student.lastName;
        cout << "Course: ";
        cin >> student.course;

        cout << "Specialty (Enter the corresponding number):\n";
        for (int i = 0; i < 5; ++i)
        {
            cout << i << ". " << specialtyStr[i] << endl;
        }

        int specialtyChoice;
        cin >> specialtyChoice;

        if (specialtyChoice >= 0 && specialtyChoice < 5)
        {
            student.specialty = static_cast<Specialty>(specialtyChoice);
        }
        else
        {
            cerr << "Invalid specialty choice.\n";
            continue;
        }

        cout << "Physics Grade: ";
        cin >> student.physicsGrade;
        cout << "Math Grade: ";
        cin >> student.mathGrade;
        cout << "Informatics Grade: ";
        cin >> student.informaticsGrade;

        writeStudentToFile(fileName, student, numberOfStudents);
    }
}

void printExcellentStudents(const string &fileName, int studentCount)
{
    ifstream inFile(fileName, ios::binary);

    if (inFile.is_open())
    {
        cout << "\nExcellent Students:\n";

        int studentNumber = 1;
        Student student;
        bool foundExcellentStudent = false;

        while (inFile.read((char *)&student, sizeof(Student)) && studentNumber <= studentCount)
        {
            if (student.physicsGrade == 5 && student.mathGrade == 5 && student.informaticsGrade == 5)
            {
                cout << student.lastName << endl;
                foundExcellentStudent = true;
            }
            ++studentNumber;
        }

        if (!foundExcellentStudent)
        {
            cout << "No excellent students found.\n";
        }

        inFile.close();
    }
    else
    {
        cerr << "Error opening file for reading.\n";
    }
}

void printStudents(const string &fileName, int studentCount)
{
    ifstream inFile(fileName, ios::binary);

    if (inFile.is_open())
    {
        cout << "\nAll Students:\n";
        cout << "------------------------------------------------------------------------------------\n";
        cout << "|  No.| Last Name | Course | Specialty           | Physics | Math | Informatics |\n";
        cout << "-------------------------------------------------------------------------------------\n";

        int studentNumber = 1;
        Student student;
        while (inFile.read((char *)&student, sizeof(Student)) && studentNumber <= studentCount)
        {
            cout << "| " << setw(4) << right << studentNumber
                 << "| " << setw(10) << left << student.lastName
                 << "| " << setw(7) << right << student.course
                 << "| " << setw(20) << left << specialtyStr[student.specialty]
                 << "| " << setw(8) << right << student.physicsGrade
                 << "| " << setw(5) << right << student.mathGrade
                 << "| " << setw(11) << right << student.informaticsGrade << " |\n";
            cout << "------------------------------------------------------------------------------------\n";
            ++studentNumber;
        }

        inFile.close();

        printExcellentStudents(fileName, studentCount);
    }
    else
    {
        cerr << "Error opening file for reading.\n";
    }
}

int main()
{
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    Student students[MAX_STUDENTS];
    int numberOfStudents = 0;

    inputStudents(fileName, numberOfStudents);
    printStudents(fileName, numberOfStudents);

    return 0;
}
