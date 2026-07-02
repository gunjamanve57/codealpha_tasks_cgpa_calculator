#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Convert Grade to Grade Point
double getGradePoint(string grade)
{
    if (grade == "A+")
        return 10.0;
    else if (grade == "A")
        return 9.0;
    else if (grade == "B+")
        return 8.0;
    else if (grade == "B")
        return 7.0;
    else if (grade == "C+")
        return 6.0;
    else if (grade == "C")
        return 5.0;
    else if (grade == "F")
        return 0.0;
    else
        return -1.0; // Invalid grade
}

class Subject
{
public:
    string name;
    int credit;
    string grade;
    double gradePoint;

    Subject(string n, int c, string g)
    {
        name = n;
        credit = c;
        grade = g;
        gradePoint = getGradePoint(g);
    }

    double getTotalGradePoints() const
    {
        return gradePoint * credit;
    }
};

class Semester
{
public:
    int semesterNo;
    vector<Subject> subjects;

    Semester(int semNo)
    {
        semesterNo = semNo;
    }

    void addSubject(string name, int credit, string grade)
    {
        subjects.push_back(Subject(name, credit, grade));
    }

    int getTotalCredits() const
    {
        int totalCredits = 0;

        for (const Subject &sub : subjects)
        {
            totalCredits += sub.credit;
        }

        return totalCredits;
    }

    double getTotalGradePoints() const
    {
        double totalGP = 0;

        for (const Subject &sub : subjects)
        {
            totalGP += sub.getTotalGradePoints();
        }

        return totalGP;
    }

    double calculateSGPA() const
    {
        int totalCredits = getTotalCredits();

        if (totalCredits == 0)
            return 0;

        return getTotalGradePoints() / totalCredits;
    }

    void displaySemesterReport() const
    {
        cout << "\n====================================";
        cout << "\nSemester " << semesterNo << " Report";
        cout << "\n====================================\n";

        for (const Subject &sub : subjects)
        {
            cout << "Subject Name     : " << sub.name << endl;
            cout << "Credits          : " << sub.credit << endl;
            cout << "Grade            : " << sub.grade << endl;
            cout << "Grade Point      : " << sub.gradePoint << endl;
            cout << "Grade Points     : "
                 << sub.getTotalGradePoints() << endl;
            cout << "------------------------------------\n";
        }

        cout << "Total Credits    : " << getTotalCredits() << endl;
        cout << "Total Grade Pts  : "
             << fixed << setprecision(2)
             << getTotalGradePoints() << endl;

        cout << "Semester GPA     : "
             << fixed << setprecision(2)
             << calculateSGPA() << endl;
    }
};

class Student
{
public:
    string name;
    vector<Semester> semesters;

    Student(string studentName)
    {
        name = studentName;
    }

    void addSemester(const Semester &sem)
    {
        semesters.push_back(sem);
    }

    int getTotalCredits() const
    {
        int totalCredits = 0;

        for (const Semester &sem : semesters)
        {
            totalCredits += sem.getTotalCredits();
        }

        return totalCredits;
    }

    double getTotalGradePoints() const
    {
        double totalGP = 0;

        for (const Semester &sem : semesters)
        {
            totalGP += sem.getTotalGradePoints();
        }

        return totalGP;
    }

    double calculateCGPA() const
    {
        int totalCredits = getTotalCredits();

        if (totalCredits == 0)
            return 0;

        return getTotalGradePoints() / totalCredits;
    }

    void displayReport() const
    {
        cout << "\n\n====================================";
        cout << "\n        STUDENT REPORT";
        cout << "\n====================================";
        cout << "\nStudent Name : " << name << endl;

        for (const Semester &sem : semesters)
        {
            sem.displaySemesterReport();
        }

        cout << "\n====================================";
        cout << "\nOVERALL RESULT";
        cout << "\n====================================\n";

        cout << "Total Credits Earned : "
             << getTotalCredits() << endl;

        cout << "Total Grade Points   : "
             << fixed << setprecision(2)
             << getTotalGradePoints() << endl;

        cout << "Final CGPA           : "
             << fixed << setprecision(2)
             << calculateCGPA() << endl;
    }
};

int main()
{
    string studentName;

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    Student student(studentName);

    int numSemesters;

    cout << "Enter Number of Semesters: ";
    cin >> numSemesters;

    while (numSemesters <= 0)
    {
        cout << "Please enter a valid number: ";
        cin >> numSemesters;
    }

    for (int i = 1; i <= numSemesters; i++)
    {
        Semester sem(i);

        int numSubjects;

        cout << "\nEnter Number of Subjects in Semester "
             << i << ": ";
        cin >> numSubjects;

        while (numSubjects <= 0)
        {
            cout << "Please enter a valid number: ";
            cin >> numSubjects;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int j = 1; j <= numSubjects; j++)
        {
            string subjectName;
            int credit;
            string grade;

            cout << "\nSubject " << j << endl;

            cout << "Enter Subject Name: ";
            getline(cin, subjectName);

            do
            {
                cout << "Enter Credit Hours: ";
                cin >> credit;

                if (credit <= 0)
                {
                    cout << "Credits must be greater than 0.\n";
                }

            } while (credit <= 0);

            do
            {
                cout << "Enter Grade (A+, A, B+, B, C+, C, F): ";
                cin >> grade;

                if (getGradePoint(grade) == -1)
                {
                    cout << "Invalid Grade. Try Again.\n";
                }

            } while (getGradePoint(grade) == -1);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            sem.addSubject(subjectName, credit, grade);
        }

        student.addSemester(sem);
    }

    student.displayReport();

    return 0;
}