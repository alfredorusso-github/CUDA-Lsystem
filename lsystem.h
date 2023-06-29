#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <map>
#include <iostream>
#include <sstream>


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

        // The rules has to be in the format "F X[+F][-F] X XX" the number of rules doesn't matter
        void parseString(std::string rules);

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

        // Costruttore di default

        // Costruttore
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

        // redefinition ostream operator
        friend std::ostream& operator<<(std::ostream& os, const lsystem& system);

        // Execute l-system
        void execute(int iteration);
};

#endif