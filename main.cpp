#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

int characters(string pwd)
{
    return pwd.size() * 4;
}

int upperLetters(string pwd)
{
    int num = 0;
    for (int i = 0; i < pwd.size(); i++) {
        if (isupper(pwd[i]))
            num++;
    }
    if (num == 0)
        return 0;
    else
        return (pwd.size() - num) * 2;
}

int lowerLetters(string pwd)
{
    int num = 0;
    for (int i = 0; i < pwd.size(); i++) {
        if (islower(pwd[i]))
            num++;
    }
    if (num == 0)
        return 0;
    else
        return (pwd.size() - num) * 2;
}

int numbers(string pwd)
{
    int num = 0;
    for (int i = 0; i < pwd.size(); i++) {
        if (isdigit(pwd[i]))
            num++;
    }
    return num * 4;
}

int symbols(string pwd)
{
    int num = 0;
    for (int i = 0; i < pwd.size(); i++) {
        if (!isalnum(pwd[i]))
            num++;
    }
    return num * 6;
}

int diversity(string pwd)
{
    bool letter = false;
    bool number = false;
    bool symbol = false;
    for (int i = 0; i < pwd.size(); i++) {
        if (isalpha(pwd[i]))
            letter = true;
        if (isdigit(pwd[i]))
            number = true;
        if (!isalnum(pwd[i]))
            symbol = true;
        if (letter && number && symbol)
            return pwd.size() * 2;
    }
    return 0;
}

int lettersOnly(string pwd)
{
    for (int i = 0; i < pwd.size(); i++) {
        if (!isalpha(pwd[i]))
            return 0;
    }
    return pwd.size();
}

int numbersOnly(string pwd)
{
    for (int i = 0; i < pwd.size(); i++) {
        if (!isdigit(pwd[i]))
            return 0;
    }
    return pwd.size();
}

int repeatChars(string pwd)
{
    int num = 0;
    for (int i = 1; i < pwd.size(); i++) {
        if (pwd[i] == pwd[i-1])
            num++;
    }
    if (num > 0)
        return pow(num+1, 2);
    else
        return 0;
}

int consecutiveUpper(string pwd)
{
    int num = 0;
    for (int i = 1; i < pwd.size(); i++) {
        if (isupper(pwd[i]) && isupper(pwd[i-1]))
            num++;
    }
    return num * 2;
}

int consecutiveLower(string pwd)
{
    int num = 0;
    for (int i = 1; i < pwd.size(); i++) {
        if (islower(pwd[i]) && islower(pwd[i-1]))
            num++;
    }
    return num * 2;
}

int consecutiveNumbers(string pwd)
{
    int num = 0;
    for (int i = 1; i < pwd.size(); i++) {
        if (isdigit(pwd[i]) && isdigit(pwd[i-1]))
            num++;
    }
    return num * 2;
}

int sequentialAlNum(string pwd)
{
    int num = 0;
    for (int i = 2; i < pwd.size(); i++) {
        if ((pwd[i] == pwd[i-1]+1 && pwd[i-1] == pwd[i-2]+1) || (pwd[i] == pwd[i-1]-1 && pwd[i-1] == pwd[i-2]-1))
            num++;
    }
    return num * 3;
}

int commonPassword(string pwd)
{
    ifstream pwdFile("passwords.txt");
    string line;
    string word;
    int frequency;

    for (int i = 0; i < pwd.size(); i++) {
        if (isalpha(pwd[i]))
            pwd[i] = tolower(pwd[i]);
    }

    while (getline(pwdFile, line)) {
        word = line.substr(0, line.find(","));
        if (pwd.find(word) != string::npos) {
            int frequency = atoi(line.substr(line.find(" ")).c_str());
            if (pwd.size() == word.size())
                return frequency;
            else {
                return frequency * ((float)word.size() / (float)pwd.size());
            }
        }
    }
    return 0;
}

int minimumChars(string pwd)
{
    if (pwd.size() >= 8)
        return 0;
    else
        return (8 - pwd.size()) * 2;
}

int score(string pwd)
{
    return characters(pwd) + upperLetters(pwd) + lowerLetters(pwd) + numbers(pwd) + symbols(pwd) + diversity(pwd)
        - commonPassword(pwd) - lettersOnly(pwd) - numbersOnly(pwd) - repeatChars(pwd) - consecutiveUpper(pwd)
        - consecutiveLower(pwd) - consecutiveNumbers(pwd) - sequentialAlNum(pwd) - minimumChars(pwd);
}

void scoreBreakdown(string pwd)
{
    cout << "---- Additions ----" << endl
        << "Number Characters Score: " << characters(pwd) << endl
        << "Number Uppercase Score: " << upperLetters(pwd) << endl
        << "Number Lowercase Score: " << lowerLetters(pwd) << endl
        << "Numbers Score: " << numbers(pwd) << endl
        << "Symbols Score: " << symbols(pwd) << endl
        << "Diversity Score: " << diversity(pwd) << endl
        << "---- Penalties ----" << endl
        << "Below Minimum Characters: -" << minimumChars(pwd) << endl
        << "Common Password Penalty: -" << commonPassword(pwd) << endl
        << "Letters Only Penalty: -" << lettersOnly(pwd) << endl
        << "Numbers Only Penalty: -" << numbersOnly(pwd) << endl
        << "Repeat Characters Penalty: -" << repeatChars(pwd) << endl
        << "Consecutive Uppercase Penalty: -" << consecutiveUpper(pwd) << endl
        << "Consecutive Lowercase Penalty: -" << consecutiveLower(pwd) << endl
        << "Consecutive Numbers Penalty: -" << consecutiveNumbers(pwd) << endl
        << "Sequential Alphanumerics Penalty: -" << sequentialAlNum(pwd) << endl;
}

int main()
{
    string pwd;

    while (true) {
        cout << "Enter Password: ";
        cin >> pwd;
        if (pwd == "q")
            break;
        cout << endl;

        scoreBreakdown(pwd);
        int totalScore = score(pwd);
        cout << endl << "Total Score: " << totalScore;

        if (totalScore < -50) cout << " The Worst";
        else if (totalScore < 0) cout << " Terrible";
        else if (totalScore < 25) cout << " Weak";
        else if (totalScore < 50) cout << " Has potential";
        else if (totalScore < 75) cout << " Good";
        else if (totalScore < 100) cout << " Great";
        else if (totalScore > 100) cout << " The Best";
        cout << endl << endl;
    }

    return 0;
}
