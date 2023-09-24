#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
#include <cuda_runtime.h>

class AxiomEmptyExecption : public std::exception
{
    public:
        const char* what() const noexcept override
        {
            return "Error occured: Impossible to initialize a l-system with an empty axiom.";
        }
};

class RulesEmptyException : public std::exception
{
    public:
        const char* what() const noexcept override 
        {
            return "Error occured: impossible to initialize an l-system with no rules.";
        }
};

// Custom exception used when a rules is given in a wrong string format
class RulesWrongFormatException : public std::exception
{
    public:

        const char* what() const noexcept override 
        {
            return "Wrong format for the rules string, check if the rules string is in the correct format.";
        }
};

class EmptyResultExecption : public std::exception
{
    public:

        const char* what() const noexcept override 
        {
            return "Impossible to operate with an empty result, try to execute the l-system first.";
        }
};

class EmptyGpuResultExecption : public std::exception
{
    public:

        const char* what() const noexcept override 
        {
            return "Impossible to operate with an empty gpu result, try to execute the l-system first, using an Nvidia Card.";
        }
};

class lsystem
{
    private:

        std::string axiom;
        std::map<char, std::string> rules;

        // Maps used for let the user create his own grammar
        std::map<char, int> meanings{{'A', Draw}, {'B', Draw}, {'F', Draw}, {'G', Draw}, {'b', Move}, {'[', Push}, {']', Pop}, {'-', Turnleft}, {'+', Turnright}};
        std::string symbolMeaningsName[7] = {"Move", "Draw", "Push", "Pop", "Turnleft", "Turnright", "Donothing"};


        // Stack used in order to deal with backtracked l-system
        std::stack<int> states;

        // The result of the l-system
        std::string result;

        // The rules has to be in the format "F X[+F][-F] X XX" the number of rules doesn't matter
        void parseString(const std::string rules);

        /*************************************************
        *                                                *
        *                   GPU STUFF                    *
        *                                                *
        **************************************************/

        // variable used for checking if GPU is used to compute the l-system result
        bool isGpuUsed = false;

        // variable used for checking if it's needed to free the resources
        bool isFreeNeeded = false;

        // array of letters of the production rules
        char* rulesKey = nullptr;
        
        // number of letters of the value related to a production rule
        int* rulesValueLength = nullptr;

        // The array of string related to the values of the production rules
        char** rulesValue = nullptr;

        // Length of the rulesKey and rulesValueLength arrays
        int rulesLength;

        // The result computed using GPU
        std::string GPUresult;

        // Method used in order to setup and fill all the previous variables 
        void setupGPUstuff();

        // Method used to launch a Kernel in order to calculate how many characters a letter generates according to the production rules
        int* count();

        // Method used to launch a Kernel in order to perform string rewriting
        void rewrite(int* offsetArray);

    public:

        // Enum used when user want to specify a custom grammar
        enum symbolMeanings
        {
            Move,
            Draw,
            Push,
            Pop,
            Turnleft,
            Turnright,
            Donothing
        };

        // Costant used for specifying the starting direction for drawing the l-system
        static const int RIGHT = 0;
        static const int LEFT = 180;
        static const int UP = 270;
        static const int DOWN = 90;

        // Constructors
        lsystem(std::string axiom, std::string rules);
        lsystem(std::string axiom, std::map<char, std::string> rules);

        // Copy Constructor
        lsystem(const lsystem& other);

        // Assignment Operator
        lsystem &operator=(const lsystem &other);

        // Destructor
        ~lsystem();

        // Getter
        std::string get_axiom() const;
        std::map<char, std::string> get_rules() const;
        std::string get_result() const;
        std::string get_GPUResult() const;
        std::map<char, int> get_meanings() const;

        // Redefinition ostream operator
        friend std::ostream& operator<<(std::ostream& os, const lsystem& system);

        // Let the user decide symbols meaning
        void setMeaning(std::string symbols, int meaning);

        // Execute l-system
        void execute(const int iteration);
        void executeOnGPU(const int iteration);

        // Writing the result on file
        void write(const std::string name) const;

        // Drawing l-system result
        void draw(const std::string name, const double turnAngle, const int stepLength, const bool drawGPUResult = false, const int startingDirection = RIGHT);

        // Method used inside the destructor in order to free the memory used on GPU
        void freeMemory();
};

#endif