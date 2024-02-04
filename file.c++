#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <cmath>
using namespace std;

string decimalToBinary(int i)
{
    string binaryResult = "";

    while (i > 0)
    {
        int remainder = i % 2;                              // 1011101
        binaryResult = to_string(remainder) + binaryResult; // prepend to the result  //1011101
        i /= 2;
    }

    return binaryResult.empty() ? "0" : binaryResult;
}

string stringToBinary(const string &str)
{
    string binaryResult = "";

    for (char c : str)
    {
        if (c == ' ')
        {
            binaryResult += " ";
            continue;
        }
        int asciiValue = (int)c;
        binaryResult += decimalToBinary(asciiValue);
        binaryResult += "\n";
    }
    return binaryResult;
}

void writeToFile(string str, string path)
{
    ofstream file;
    file.open(path);
    file << str;
    file.close();
}

string readFromFile(string path)
{
    ifstream file(path);
    string str;
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            str += line + '\n';
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file: " << path << endl;
    }

    return str;
}

int binaryToDecimal(const std::string &binaryNumber)
{
    int decimalResult = 0;
    int power = 0;

    for (int i = binaryNumber.length() - 1; i >= 0; --i)
    {
        if (binaryNumber[i] == '1')
        {
            decimalResult += std::pow(2, power);
        }
        ++power;
    }

    return decimalResult;
}

string binaryToString(const string &binaryStr)
{
    string result = "";
    string temp = "";
    char ch;
    for (int i = 0; i < binaryStr.length(); i++)
    {
        if (binaryStr[i] == ' ')
        {
            result += ' ';
        }
        else if (binaryStr[i] != '\n')
        {
            temp += binaryStr[i];
        }
        else if (binaryStr[i] == '\n')
        {
            ch = binaryToDecimal(temp);
            temp = "";
            result += ch;
        }
    }
    return result;
}

int main()
{
    int choice;

    do
    {
        cout << "Menu:\n";
        cout << "1. Convert a string to binary and save to file\n";
        cout << "2. Read binary data from file and convert to string\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1, 2, or 3): ";

        cin >> choice;
        cin.ignore(); // Consume the newline character left in the buffer

        switch (choice)
        {
        case 1:
        {
            string inputString;
            cout << "Enter a string: ";
            getline(cin, inputString);

            string binaryData = stringToBinary(inputString);
            // cout << "Binary representation:\n"
            //      << binaryData << endl;

            string filePath;
            cout << "Enter the file path to save the binary data: ";
            getline(cin, filePath);

            writeToFile(binaryData, filePath);
            cout << "Binary data saved to file: " << filePath << endl;
            break;
        }

        case 2:
        {
            string filePath;
            cout << "Enter the file path to read binary data: ";
            getline(cin, filePath);

            string binaryData = readFromFile(filePath);
            cout << "Binary data read from file:\n"
                 << binaryData << endl;

            string originalString = binaryToString(binaryData);
            cout << "Converted to original string: " << originalString << endl;
            break;
        }

        case 3:
            cout << "Exiting the program. Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            break;
        }

    } while (choice != 3);

    return 0;
}
