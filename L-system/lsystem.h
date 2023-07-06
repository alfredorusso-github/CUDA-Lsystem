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

        std::string axiom;
        std::map<char, std::string> rules;

        // Maps used for let the user create his own grammar
        std::map<char, int> meanings;
        std::map<char, int> defaultMeaning{{'A', DRAW}, {'B', DRAW}, {'F', DRAW}, {'G', DRAW}, {'b', MOVE}, {'[', PUSH}, {']', POP}, {'-', TURNLEFT}, {'+', TURNRIGHT}};

        // Stack used in order to deal with backtracked l-system
        std::stack<std::pair<int, int>> positions;
        std::stack<int> orientations;

        // Value used for making and estimation on how big the array containing the result can be in order to use it with CUDA
        int longestRule;

        // The result of the l-system
        std::string result;

        // The rules has to be in the format "F X[+F][-F] X XX" the number of rules doesn't matter
        void parseString(const std::string rules);

        // Custom exception used when a rules is given in a wrong string format
        class RulesWrongFormatException : public std::exception
        {
            public:

                const char* what() const noexcept override 
                {
                    return "Wrong format for the rules string, check if the rules string is in the correct format";
                }
        };

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
};

#endif