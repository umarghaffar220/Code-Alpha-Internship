#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
float gradePoint(string grade)
{
    if (grade == "A" || grade == "a")
        return 4.0;
    else if (grade == "A-" || grade == "a-")
        return 3.7;
    else if (grade == "B+" || grade == "b+")
        return 3.3;
    else if (grade == "B" || grade == "b")
        return 3.0;
    else if (grade == "B-" || grade == "b-")
        return 2.7;
    else if (grade == "C+" || grade == "c+")
        return 2.3;
    else if (grade == "C" || grade == "c")
        return 2.0;
    else if (grade == "C-" || grade == "c-")
        return 1.7;
    else if (grade == "F" || grade == "f")
        return 0.0;
    else
        return -1.0;
}

void getInfo(string sNames[], int cHours[], string grade[], float aGp[], int nOs)
{
    for (int i = 0; i < nOs; i++)
    {
        cout << "Enter the Name of Subject " << (i + 1) << ": ";
        cin >> sNames[i];

        cout << "Enter the Credit Hours: ";
        cin >> cHours[i];

        cout << "Enter Grade (A/A-/B+/B/B-/C+/C/C-/F): ";
        cin >> grade[i];

        aGp[i] = gradePoint(grade[i]);

        cout << endl;
    }
}
double calGp(float aGp[], int cHours[], int nOs)
{
    double total = 0;

    for (int i = 0; i < nOs; i++)
    {
        total = total + (aGp[i] * cHours[i]);
    }
    return total;
}
int calCr(int cHours[], int nOs)
{
    int total = 0;

    for (int i = 0; i < nOs; i++)
    {
        total = total + cHours[i];
    }

    return total;
}
double calCgpa(double semesterGpa[], int semesterCr[], int semesters)
{
    double totalPoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < semesters; i++)
    {
        totalPoints = totalPoints + (semesterGpa[i] * semesterCr[i]);
        totalCredits = totalCredits + semesterCr[i];
    }

    if (totalCredits == 0)
        return 0;

    return totalPoints / totalCredits;
}

  
    int main(){
    int choice;

    do
    {
        cout << "1. Calculate GPA" << endl;
        cout << "2. Calculate CGPA" << endl;
        cout << "3. Exit" << endl;
        cout << "Choose Any Option: ";
        cin >> choice;

        if (choice < 1 || choice > 3)
        {
            cout << "Enter Correct Option" << endl;
        }
        else if (choice == 1)
        {
 int nOs;

    // Program Heading
    cout << "============================================================" << endl;
    cout << "                     GPA CALCULATOR" << endl;
    cout << "                   STUDENT TRANSCRIPT" << endl;
    cout << "============================================================" << endl;

    cout << endl;

    cout << "Enter the Number of Subjects: ";
    cin >> nOs;

    string sNames[nOs];
    int cHours[nOs];
    string grade[nOs];
    float aGp[nOs];

    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "                  ENTER SUBJECT DETAILS" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;

    getInfo(sNames, cHours, grade, aGp, nOs);

    // Calculate Total Grade Points
    double totalPoints = calGp(aGp, cHours, nOs);

    // Calculate Total Credit Hours
    int totalCreditHours = calCr(cHours, nOs);

    // Calculate GPA
    double gpa = totalPoints / totalCreditHours;

    // Student Transcript
    cout << endl;
    cout << endl;

    cout << "============================================================" << endl;
    cout << "                    STUDENT TRANSCRIPT" << endl;
    cout << "============================================================" << endl;

    cout << left
         << setw(5) << "No."
         << setw(25) << "Subject"
         << setw(15) << "Credit Hours"
         << setw(12) << "Grade"
         << setw(12) << "Grade Point"
         << endl;

    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < nOs; i++)
    {
        cout << left
             << setw(5) << i + 1
             << setw(25) << sNames[i]
             << setw(15) << cHours[i]
             << setw(12) << grade[i]
             << setw(12) << fixed << setprecision(2) << aGp[i]
             << endl;
    }

    cout << "------------------------------------------------------------" << endl;

    cout << endl;

    // GPA Summary
    cout << "============================================================" << endl;
    cout << "                      GPA SUMMARY" << endl;
    cout << "============================================================" << endl;

    cout << fixed << setprecision(2);

    cout << "Total Credit Hours : " << totalCreditHours << endl;
    cout << "Total Grade Points : " << totalPoints << endl;
    cout << "GPA                : " << gpa << endl;

    cout << "============================================================" << endl;
    cout << "                  END OF TRANSCRIPT" << endl;
    cout << "============================================================" << endl;
        }
        else if (choice == 2)
        {
            int semesters;

    // Program Heading
    cout << "============================================================" << endl;
    cout << "                    CGPA CALCULATOR" << endl;
    cout << "                  STUDENT TRANSCRIPT" << endl;
    cout << "============================================================" << endl;

    cout << endl;

    do
    {
        cout << "Enter number of semesters (1-10): ";
        cin >> semesters;

        if (semesters <= 0 || semesters > 10)
        {
            cout << "Invalid number of semesters. Please enter again." << endl;
        }

    } while (semesters <= 0 || semesters > 10);

    double semesterGpa[10];
    int semesterCr[10];

    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "                 ENTER SEMESTER DETAILS" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;

    for (int i = 0; i < semesters; i++)
    {
        cout << "Enter GPA of Semester " << i + 1 << ": ";
        cin >> semesterGpa[i];

        cout << "Enter Credit Hours of Semester " << i + 1 << ": ";
        cin >> semesterCr[i];

        cout << endl;
    }

    double cgpa = calCgpa(semesterGpa, semesterCr, semesters);

    // CGPA Transcript
    cout << endl;
    cout << "============================================================" << endl;
    cout << "                  STUDENT TRANSCRIPT" << endl;
    cout << "============================================================" << endl;

    cout << left
         << setw(8) << "Sem."
         << setw(20) << "Semester GPA"
         << setw(20) << "Credit Hours"
         << endl;

    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < semesters; i++)
    {
        cout << left
             << setw(8) << i + 1
             << setw(20) << fixed << setprecision(2) << semesterGpa[i]
             << setw(20) << semesterCr[i]
             << endl;
    }

    cout << "------------------------------------------------------------" << endl;

    cout << endl;

    // CGPA Summary
    cout << "============================================================" << endl;
    cout << "                     CGPA SUMMARY" << endl;
    cout << "============================================================" << endl;

    cout << fixed << setprecision(2);

    cout << "Total Semesters    : " << semesters << endl;

    int totalCredits = 0;
    for (int i = 0; i < semesters; i++)
    {
        totalCredits = totalCredits + semesterCr[i];
    }

    cout << "Total Credit Hours : " << totalCredits << endl;
    cout << "CGPA               : " << cgpa << endl;

    cout << "============================================================" << endl;
    cout << "                  END OF TRANSCRIPT" << endl;
    cout << "============================================================" << endl;
        }
    } while (choice != 3);

    return 0;
}



