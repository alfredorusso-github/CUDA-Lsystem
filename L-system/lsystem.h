#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>

class RulesEmptyException : public std::exception
{
    public:
        const char* what() const noexcept override 
        {
            return "Error occured: impossible to print an l-system not correctly initialized";
        }
};

class lsystem
{
    private:

        // Custom exception used when a rules is given in a wrong string format
        class RulesWrongFormatException : public std::exception
        {
            public:

                const char* what() const noexcept override 
                {
                    return "Wrong format for the rules string, check if the rules string is in the correct format";
                }
        };

        std::string axiom;
        std::map<char, std::string> rules;

        // Maps used for let the user create his own grammar
        std::map<char, int> meanings;
        std::map<char, int> defaultMeaning{{'A', DRAW}, {'B', DRAW}, {'F', DRAW}, {'G', DRAW}, {'b', MOVE}, {'[', PUSH}, {']', POP}, {'-', TURNLEFT}, {'+', TURNRIGHT}};

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

        // array of letters of the production rules
        char* rulesKey = nullptr;
        
        // number of letters of the value related to a production rule
        int* rulesValueLength = nullptr;

        // The array of string related to the values of the production rules
        char** rulesValue = nullptr;

        // Length of the rulesKey and rulesValueLength arrays
        int rulesLength;

        // 
        std::string GPUresult;

        void setupGPUstuff();

        // Method in order to setup and run the kernel for computing the number of elements
        int* count();

        // Method used to setup the prefix sum of the array using cuda libraries
        int* prefixSum(int* input);

        void rewrite(int* offsetArray);

    public:

        // Constant used when the user want to specify the custom grammar
        static const int MOVE = 1;
        static const int DRAW = 2;
        static const int PUSH = 3;
        static const int POP = 4;
        static const int TURNLEFT = 5;
        static const int TURNRIGHT = 6;
        static const int DONOTHING = 7;

        // Costant used for specifying which direction to use for start drawing
        static const int RIGHT = 0;
        static const int LEFT = 180;
        static const int UP = 270;
        static const int DOWN = 90;

        static const bool useGPU = true;

        // Costruttore di default

        // Costruttori
        lsystem(std::string axiom, std::map<char, std::string> rules);
        lsystem(std::string axiom, std::string rules);

        // Copy Constructor
        lsystem(const lsystem& other);

        // Operatore di assegnamento
        lsystem &operator=(const lsystem &other);

        // Distruttore
        ~lsystem();

        // Getter
        std::string get_axiom() const;
        std::map<char, std::string> get_rules() const;
        std::string get_result() const;
        std::string get_GPUResult() const;

        // Setter

        // Redefinition ostream operator
        friend std::ostream& operator<<(std::ostream& os, const lsystem& system);

        // Let the user to decide symbols meaning
        void setCustomMeaning(std::string symbols, int meaning);

        // Execute l-system
        void execute(const int iteration);
        void execute(const int iteration, const bool useGPU);

        // Writing the result on file
        void write(const std::string name) const;

        // Drawing the l-system
        void draw(const std::string name, const double turnAngle, const int stepLength, const int startingDirection = RIGHT);

        /*************************************************
        *                                                * 
        *                   GPU STUFF                    *
        *                                                *
        **************************************************/
};

#endif