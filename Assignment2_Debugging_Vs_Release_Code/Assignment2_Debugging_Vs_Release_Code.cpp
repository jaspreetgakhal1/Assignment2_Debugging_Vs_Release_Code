#include <iostream>
#include <fstream> // Need this here for reading files
#include <string>
#include <vector>
#include <sstream>

// Jaspreet Singh Gakhal Student Number 8542862

// Avoid repeatedly using std::. For example, std::cout becomes cout and std::string becomes string.
using namespace std;


// Removed 1 blankspace from the beginning of a string if one exists.
// For instance suppose entry is " singh" it becomes "singh"
void removeBlankSpaceAtFront(string& text)
{
    // Check that the string is NOT empty AND if the first character is a space or not.
    if (!text.empty() && text.front() == ' ')
        // So if there is text, AND the text is blankspace, erase it.
        text.erase(0, 1);

}

// Stores information for each student. As instructed we start by creating a Struct STUDENT_DATA
// That holds first + last names of students. 
// Email is only included in the Pre-Release version.
struct STUDENT_DATA
{
    string firstName;
    string lastName;

    // In the pre-release version, we also store the email address of the student.
#ifdef PRE_RELEASE
    string email;
#endif
};

int main()
{

    // In MAIN, we start by checking if pre-release is selected at the time of compilation. 
    // We do that with the lines below, #ifdef PRE_RELEASE and #else.

    // If we are in pre-release mode, we'll be using the emails.txt file
#ifdef PRE_RELEASE
    cout << "Running PRE-RELEASE source code.\n";
    // Message printing we are in pre-release source code
    // Filenames const because it will remain the same
    const string filename = "StudentData_Emails.txt";
#else
    // Else meaning otherwise, we will be running in standard mode, using the student data txt file
    cout << "Running STANDARD source code.\n";
    // Again, file will remain const and unchanged
    const string filename = "StudentData.txt";
#endif
#ifdef _DEBUG
    // If in debug mode, we will print the build configuration as DEBUG and other way around
    cout << "Build Configuration: DEBUG\n";
#else
    cout << "Build Configuration: RELEASE\n";
#endif


    // Stores all student records read from the file.
        // As the instructions state, upon creating struct STUDENT_DATA, parse the data, create an object and
        //push the object into a vector space. This makes our vector dynamic.
    vector<STUDENT_DATA> students;

    // Opens whichever student data file was selected above.
    ifstream file(filename);

    // Just checking on the file if we are able to open it. IF we are not able to open it, 
    // Print an error msg and return 1, indicating an error.
    if (!file.is_open())
    {
        cerr << "Error opening the file: " << filename << '\n';
        return 1;
    }

    // Variable to store one full line read from student data file.
    string line;

    // Read the file one line at a time until your out of lines or have reached the end of the file.
    while (getline(file, line))
    {
        // Skip empty lines. Or specefically, while looping with getline(file,line) if we reach an empty line, we will continue to the next line.
        if (line.empty())
        {
            // again if empty continue
            continue;
        }

        // Creating a stringstream from the current line
        // because we want to split the line using commas ( As per instrucctions)
        // For example the standard line is Jaspreet, Gakhal but then pre-release would be Jaspreet, Gakhal, jgakhal2862@conestogac.on.ca
        stringstream ss(line);
        // Temporary student object to hold data as we parse it.
        STUDENT_DATA student;

        // PRE-RELEASE data portion of the code. Here we parse first name, last name, and email
#ifdef PRE_RELEASE

        // Pre-Release data contains first name, last name, and email.
        // The structure here is that we read first name, look for a coma, last name then coma again. Finally email comes at the end
        // The ',' tells getline to stop reading when it reaches a comma.
        // The && operators ensure that each value is sucessfully read before continuing
        if (getline(ss, student.firstName, ',') &&
            getline(ss, student.lastName, ',') &&
            getline(ss, student.email))
        {
            // Once the first name. last name and meail are sucessfully read, remove any leading blank space from the Last name and email

            removeBlankSpaceAtFront(student.lastName);
            removeBlankSpaceAtFront(student.email);

            // Once validated and cleaned of blank spaces, we can do the much antisipated push of the STUDENT_DATA object into the vector.
            students.push_back(student);
        }

#else
    // Otherwise, the standard version only reads the student's first and last name, since we handled the other scenario above.
        if (getline(ss, student.firstName, ',') &&
            getline(ss, student.lastName))
        {
            // Remove a possible blank space before the last name.
            removeBlankSpaceAtFront(student.lastName);

            // Push the completed student object into the vector.
            students.push_back(student);
        }
#endif
    }

    // Student information should only be displayed when the application is compiled in Debug mode.
#ifdef _DEBUG

    cout << "\n--- Student Data List (DEBUG MODE) ---\n";

    // Loop through every student data obj stored in the vector
    // student = The current student during each Loop iteration
    // students = The vector being traversed
    for (const STUDENT_DATA& student : students)
    {
        // Display the first and lats name
        cout << "First Name: " << student.firstName
            << ", Last Name: " << student.lastName;


        // We know emails are only seen when PRE_RELEASE is defined, so we will only display emails when that is the case.
#ifdef PRE_RELEASE
        cout << ", Email: " << student.email;
#endif
        // Next line after printing one student's data.
        cout << '\n';
    }

#endif

    return 0;
}