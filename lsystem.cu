#include "lsystem.h"

lsystem::lsystem(std::string axiom, std::map<char, std::string> rules): axiom(""), rules({})
{
   this->axiom = axiom;
   this->rules = rules; 
}

lsystem::lsystem(std::string axiom, std::string rules): axiom(""), rules({})
{
    this->axiom = axiom;

    try
    {
        parseString(rules);
    }
    catch(const RulesWrongFormatException &e)
    {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
    
}

lsystem::lsystem(const lsystem& other)
{
    this->axiom = other.axiom;
    this->rules = other.rules;
}

lsystem& lsystem::operator=(const lsystem &other)
{
    if(this != &other)
    {
        lsystem tmp(other);
        std::swap(tmp.axiom, this->axiom);
        std::swap(tmp.rules, this->rules);
    }

    return *this;
}

lsystem::~lsystem()
{

}

std::string lsystem::get_axiom() const
{
    return this->axiom;
}

std::map<char, std::string> lsystem::get_rules() const
{
    return this->rules;
}

std::ostream &operator<<(std::ostream &os, const lsystem &system)
{
    if(system.rules.size() == 0 || system.axiom.empty())
    {
        throw RulesEmptyException();
    }

    os << "l-system with axiom: " << system.get_axiom() << " and rules: ";

    for (const auto& [key, value] : system.get_rules())
    {
        os << key << " → " << value << "    ";
    }

    return os;
}

void lsystem::parseString(std::string rules)
{
    std::stringstream ss(rules);
    char key;
    std::string value;

    while(ss >> key)
    {
        if(!(ss >> value))
        {
            this->rules = {};
            this->axiom = "";
            throw RulesWrongFormatException();
        }

        // std::cout << "Key: " << key << " value: " << value << std::endl;

        this->rules[key] = value;
    }
}

void lsystem::execute(int iteration)
{
    std::string result = this->axiom;

    for(int i = 0; i < iteration; i++)
    {
        std::string tmp = "";

        for(char c: result)
        {
            if(this->rules.find(c) != this->rules.end())
            {
                tmp += this->rules[c];
            }
            else
            {
                tmp += c;
            }
        }

        result = tmp;
    }

    std::cout << "The result is: " << result << std::endl;
}