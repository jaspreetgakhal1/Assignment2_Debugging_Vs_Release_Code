#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// Avoid repeatedly using std::. For example,
// std::cout becomes cout and std::string becomes string.
using namespace std;


// Removes one blank space from the beginning of a string if one exists.
// For example, " Singh" becomes "Singh".
void removeBlankSpaceAtFront(string& text)
{
    // Check that the string is not empty and that
    // the first character is a blank space.
    if (!text.empty() && text.front() == ' ')
        text.erase(0, 1);
}


// Stores information for each student.
// As instructed, STUDENT_DATA contains the student's
// first and last name.
struct STUDENT_DATA
{
    string firstName;
    string lastName;
};


int main()
{
    // StudentData.txt is the input file required for the
    // initial implementation.
    const string filename = "StudentData.txt";

    // Stores all student objects created from the input file.
    // The vector can grow as student objects are added.
    vector<STUDENT_DATA> students;

    // Open the student data file.
    ifstream file(filename);

    // Check whether the file was opened successfully.
    // Return 1 if the file cannot be opened.
    if (!file.is_open())
    {
        cerr << "Error opening the file: " << filename << '\n';
        return 1;
    }

    // Stores one full line read from the student data file.
    string line;

    // Read the file one line at a time until the end of the file.
    while (getline(file, line))
    {
        // Skip any empty lines.
        if (line.empty())
        {
            continue;
        }

        // Create a stringstream from the current line so the
        // first and last names can be separated using the comma.
        stringstream ss(line);

        // Temporary student object used to store the parsed data.
        STUDENT_DATA student;

        // Read the first name until the comma, then read the
        // remaining text as the last name.
        if (getline(ss, student.firstName, ',') &&
            getline(ss, student.lastName))
        {
            // Remove a possible blank space before the last name.
            removeBlankSpaceAtFront(student.lastName);

            // Push the completed STUDENT_DATA object into the vector.
            students.push_back(student);
        }
    }

    return 0;
}