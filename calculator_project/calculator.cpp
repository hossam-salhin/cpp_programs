#include <iostream>
#include <limits>
#include <fstream>
#include <ctime>

namespace calculator
{
    struct CalcResult
    {
        int result;
        std::string operation;
        int num1;
        int num2;
    };
    enum LogLevel
    {
        INFO,
        ERROR
    };
    void logToFile(LogLevel level, const std::string &text) // function to log messages to a file with timestamp and log level
    {
        std::ofstream file ("calculation_log.txt", std::ios::app);
        if(file.is_open())
        {
            time_t now = time(0);
            std::string timestr = ctime(&now);
            timestr.pop_back(); // remove the newline character from the end of the timestamp
            std::string levelstr;
            if(level == INFO) {levelstr = "[INFO]";}
            else if (level == ERROR) {levelstr = "[ERROR]";}
            file << "Time: " << "["  << timestr << "] "<< levelstr << " " << text << std::endl;
            file << "-----------------------------" << std::endl;
            file.close();
        }
        else
        {
            std::cout << "unable to open the file." <<std::endl;
        }
    }

    bool getInput(int& num) // function to get input from the user and validate it, returning false if the input is invalid
    {
        std::cin >> num;
        if(!std::cin)
        {
            std::cout << "invalid input." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            logToFile(ERROR, "invalid input recieved.");   
            return false;
        }
        return true;
    }


    int add(int num1, int num2)
    {
        return num1 + num2;
    }
    int subtract(int num1, int num2)
    {
        return num1 - num2; 
    }
    int multiply(int num1, int num2)
    {
        return num1 * num2;
    }
    int divide(int num1, int num2)
    {
        if(num2 == 0)
        {
            std::cout << "Error: Division by zero is not allowed." << std::endl;
            logToFile(ERROR, "division by zero error: " + std::to_string(num1) + " / " + std::to_string(num2));
            return 0;
        }
        return num1 / num2;
    }

    int compute(char operation, int num1, int num2)
    {
        switch(operation)
        {
            case '+':
                return add(num1, num2);
            case '-':
                return subtract(num1, num2);
            case '*':
                return multiply(num1, num2);
            case '/':
                return divide(num1, num2);

            default:
                std::cout << "Invalid operation. Please enter a valid operator." << std::endl;
                logToFile(ERROR, "invalid operation: " + std::string(1, operation));
                return 0;
        }

    }

    
}

int main()
{
    std::cout << "Welcome to the calculautor program!" << std::endl;

    calculator::logToFile(calculator::INFO, "program started.");
    bool continue_loop = true;  // variable to control the main loop of the program, allowing the user to perform multiple calculations until they choose to exit
    
    while(continue_loop)
    {
        int num1, num2;
        char operation;

        std::cout << "Enter the first number: ";
        if(!calculator::getInput(num1)) { continue; } // if the input is invalid, skip the rest of the loop and start over

        std::cout << "\nEnter the second number: ";
        if(!calculator::getInput(num2)) { continue;}
        
        std::cout << "\nEnter the operation (+, -, *, /): ";
        if(!(std::cin >> operation))    // if the input is invalid, skip the rest of the loop and start over
        {
            std::cout << "invalid input." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            calculator::logToFile(calculator::ERROR, "invalid input for operation.");
            continue;
        }

        if(operation != '+' && operation != '-' && operation != '*' && operation != '/')  // if the operation is not one of the valid operators, skip the rest of the loop and start over
        {
            std::cout << "Invalid operation. Please enter a valid operator." << std::endl;
            calculator::logToFile(calculator::ERROR, "invalid operation input: " + std::string(1, operation));
            continue;
        }

        int result = calculator::compute(operation, num1, num2);
        std::cout << "Result: " << result << std::endl;
        calculator::logToFile(calculator::INFO, "operation: " + std::string(1, operation) + "\ninputs: " + std::to_string(num1) + " and " + std::to_string(num2) + "\nresult: " + std::to_string(result));

        std::cout << "Do you want to perform another calculation? (y/n): ";  // ask the user if they want to perform another calculation, and validate the input to ensure it is either 'y' or 'n'
        char choice;
        while(true)  // loop to validate the user's input for whether they want to perform another calculation, ensuring that it is either 'y' or 'n'
        {
            std::cin >> choice;
            if(std::cin && (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N'))
            {
                break;
            }
            else
            {
                std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
                calculator::logToFile(calculator::ERROR, "invalid input for choice.");
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        if(choice == 'y' || choice == 'Y')
        {
            continue_loop = true;
        }
        else
        {
            continue_loop = false;
            std::cout << "Thank you for using the calculator program. Goodbye!" << std::endl;
            calculator::logToFile(calculator::INFO, "program ended.");
            break;
        }
    }
    
    return 0;
}