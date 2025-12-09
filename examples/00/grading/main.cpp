/*
#############################################################################
# COMP.CS.110 Programming 2: Techniques                                     #
# Example: Grade calculator                                                 #
# File: main.cpp                                                            #
# Description: Counts the total grade of the course based on the points     #
#              collected in different categories (N, P1, P2, B),            #
#              and the exam grade                                           #
# Notes: * Points from normal exercises, projects 1&2, and bonus points     #
#          are given in the same line, separated by an empty space.         #
#############################################################################
*/


#include <iostream>
#include <sstream>  // needed for ostringstream

using namespace std;

// The constant values below are valid at the beginning of the course.
// At the end of the course, if you use this program to calculate your total
// grade, check the values and update them identical with those in Plussa,
// if needed.
const unsigned int MAX_P_POINTS_PER_PROJECT = 50;
const unsigned int MAX_P_POINTS = 2 * MAX_P_POINTS_PER_PROJECT;
const unsigned int MAX_N_POINTS = 650;
const unsigned int MAX_B_POINTS = 10;

// Prints the values of the constants used in calculations to a string and
// returns the string.
string print_constants()
{
    ostringstream outputstream{""};
    outputstream << "The program uses the following values for constants:" << endl;
    outputstream << "  MAX_P_POINTS: " << MAX_P_POINTS << endl;
    outputstream << "  MAX_N_POINTS: " << MAX_N_POINTS << endl;
    outputstream << "  MAX_B_POINTS: " << MAX_B_POINTS << endl;
    outputstream << "Update the values, if they do not match with those in Plussa.";
    return outputstream.str();
}

// Informs about invalid (too big) N, P, and B points.
// Returns true, if all these points are valid, otherwise returns false.
bool is_valid_points(unsigned int n, unsigned int p1,
                     unsigned int p2, unsigned int b)
{
    bool is_valid = true;
    if( n > MAX_N_POINTS )
    {
        cout << "Impossible normal exercise points" << endl;
        is_valid = false;
    }
    if( p1 > MAX_P_POINTS_PER_PROJECT or p2 > MAX_P_POINTS_PER_PROJECT )
    {
        cout << "Impossible project points" << endl;
        is_valid = false;
    }
    if( b > MAX_B_POINTS )
    {
        cout << "Impossible bonus points" << endl;
        is_valid = false;
    }
    return is_valid;
}

// Informs about invalid (too big) exam grade.
// Returns true, if the given exam grade is valid, otherwise returns false.
bool is_valid_exam(unsigned int e)
{
    if( e > 5 )
    {
        cout << "Impossible exam grade" << endl;
        return false;
    }
    return true;
}

// Calculates score from weekly exercises.
unsigned int score_from_weekly_exercises(unsigned int n)
{
    float percents = (n * 100.0) / MAX_N_POINTS;
    if( percents < 50.0 ) { return 0; }
    if( percents < 60.0 ) { return 1; }
    if( percents < 70.0 ) { return 2; }
    if( percents < 80.0 ) { return 3; }
    if( percents < 90.0 ) { return 4; }
    return 5;
}

// Calculates score from projects.
unsigned int score_from_projects(unsigned int p1, unsigned int p2)
{
    // A project not done or just 1 point from automated tests
    if( p1 <= 1 or p2 <= 1 ) { return 0; }

    // Both projects done
    unsigned int total_p = p1 + p2;
    if( total_p < 40 ) { return 0; }
    if( total_p < 50 ) { return 1; }
    if( total_p < 60 ) { return 2; }
    if( total_p < 70 ) { return 3; }
    if( total_p < 80 ) { return 4; }
    return 5;
}

// Calculates the total grade.
unsigned int calculate_total_grade(unsigned int n, unsigned int p1,
                                   unsigned int p2, unsigned int e)
{
    int score_w = score_from_weekly_exercises(n);
    int score_p = score_from_projects(p1, p2);

    if( score_w == 0 or score_p == 0 )
    {
        return 0;
    }
    if( e == 0 )
    {
        if( score_w >= 4 and score_p >= 4 )
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    float mean = (score_w + score_p + e) / 3.0;

    // Casting from float to int discards the digits after the decimal point.
    // By adding 0.5 before casting has the effect that decimal values
    // greater than and equal to 0.5 are rounded upwards, while
    // decimal values less than 0.5 are rounded downwards.
    return static_cast<unsigned int>(mean + 0.5);
}

// Main function.
// Asks first for N, P, and B points, and if all these points are valid,
// prints scores from weekly exercises and projects, and asks for exam grade.
// If also the given exam grade is valid, prints the total grade.
int main()
{
    cout << print_constants() << endl << endl;

    unsigned int n = 0;
    unsigned int p1 = 0;
    unsigned int p2 = 0;
    unsigned int b = 0;

    cout << "Enter points from categories N, P1, P2, B: ";
    cin >> n;
    cin >> p1;
    cin >> p2;
    cin >> b;

    if( is_valid_points(n, p1, p2, b) )
    {
        cout << "-> Score from weekly exercises: "
             << score_from_weekly_exercises(n + b) << endl;
        cout << "-> Score from projects:         "
             << score_from_projects(p1, p2) << endl;

        unsigned int e = 0;
        cout << "Enter exam grade (if no exam, enter zero): ";
        cin >> e;

        if( is_valid_exam(e) )
        {
            cout << "-> Total grade: "
                 << calculate_total_grade(n + b, p1, p2, e) << endl;
        }
    }

    return 0;
}

