#include "lsystem.h"

lsystem::lsystem(std::string axiom, std::map<char, std::string> rules): axiom(""), rules({})
{
   this->axiom = axiom;
   this->rules = rules; 

    for (const auto& pair : this->rules) {
        const std::string& value = pair.second;

        if(this->longestRule < value.length())
        {
            this->longestRule = value.length();
        }
    }
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

std::string lsystem::get_result() const
{
    return this->result;
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

void lsystem::parseString(const std::string rules)
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

        if(this->longestRule < value.length())
        {
            this->longestRule = value.length();
        }

        this->rules[key] = value;
    }
}

void lsystem::setCustomMeaning(std::string symbols, int meaning)
{
    for(char c: symbols)
    {
        if(c != ' ')
        {
            this->meanings[c] = meaning;
        }
    }
}

void lsystem::execute(const int iteration)
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

    // std::cout << "The result is: " << result << std::endl;
    this->result = result;
}

void lsystem::execute(const int iteration, const bool useGPU)
{
    // int nKeys = this->rules.size();

    // char keys[nKeys];
    // const char* values[nKeys];

    // int i = 0;
    // for (auto it = this->rules.begin(); it != this->rules.end(); ++it) {
    //     keys[i] = it -> first;
    //     values[i] = this->rules[keys[i]].c_str();
    //     i++;
    // }

    // size_t estimatedOutputsize = this->axiom.length() * this->longestRule * iteration;

}

__global__ void lsystemKernel(char* input, char* output, int inputLength, int outputLength, int iterations)
{

}

void lsystem::write(std::string name) const
{
    std::ofstream file("../Results/" + name + ".txt", std::ios::out);
    
    if (file.is_open())
    {
        file << this->result;
        file.close();

        std::cout << "The string has been written to the file." << std::endl;
    }
    else
    {
        std::cout << "Unable to open file." << std::endl;
    }
}

void lsystem::draw(const std::string name, const double turnAngle, const int stepLength, const int startingDirection)
{
    if(this->meanings.size() == 0)
    {
        this->meanings = this->defaultMeaning;
    }

    std::ofstream file("../Results/" + name + ".svg");
    if (!file.is_open()) {
        std::cout << "Errore nell'apertura del file." << std::endl;
        return;
    }

    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;

    double x = 0.0;
    double y = 0.0;

    double angle = startingDirection;

    for (char c : this->result) {
        if (this->meanings[c] == DRAW) {
            
            double newX = x + stepLength * cos( angle * M_PI / 180.0 );
            double newY = y + stepLength * sin( angle * M_PI / 180.0 );

            file << "<line x1=\"" << static_cast<int>(x) << "\" y1=\"" << static_cast<int>(y)<< "\" x2=\"" << static_cast<int>(newX) << "\" y2=\"" << static_cast<int>(newY) << "\" stroke=\"black\" stroke-width=\"0.8\"/>" << std::endl;

            x = newX;
            y = newY;
        }
        else if (this->meanings[c] == TURNRIGHT) {
            angle += turnAngle;
        }
        else if (this->meanings[c] == TURNLEFT) {
            angle -= turnAngle;
        }
        else if(this->meanings[c] == MOVE)
        {
            double newX = x + stepLength * cos( angle * M_PI / 180.0 );
            double newY = y + stepLength * sin( angle * M_PI / 180.0 );

            x = newX;
            y = newY;
        }
        else if (this->meanings[c] == PUSH)
        {
            this->positions.push(std::make_pair(x, y));
            this->orientations.push(angle);
        }
        else if (this->meanings[c] == POP)
        {
            x = this->positions.top().first;
            y = this->positions.top().second;
            angle = this->orientations.top();

            this->positions.pop();
            this->orientations.pop();
        }
    }

    file << "</svg>" << std::endl;
    file.close();

    std::cout << "Image successfully generated: " << name << std::endl;
}