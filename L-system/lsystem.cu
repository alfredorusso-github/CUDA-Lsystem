#include "lsystem.h"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/scan.h>

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
    if(this->rulesKey != nullptr)
    {
       cudaFree(this->rulesKey);
       cudaFree(this->rulesValueLength);

       for (int i = 0; i < this->rulesLength; i++)
       {
            cudaFree(this->rulesValue[i]); 
       }
       cudaFree(this->rulesValue);
    }
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

std::string lsystem::get_GPUResult() const
{
    return this->GPUresult;
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
            this->states.push(angle);
            this->states.push(y);
            this->states.push(x);
        }
        else if (this->meanings[c] == POP)
        {
            x = this->states.top();
            this->states.pop();

            y = this->states.top();
            this->states.pop();

            angle = this->states.top();
            this->states.pop();
        }
    }

    file << "</svg>" << std::endl;
    file.close();

    std::cout << "Image successfully generated: " << name << std::endl;
}

/*************************************************
*                                                *
*                   GPU STUFF                    *
*                                                *
**************************************************/

__global__ void countKernel(const char* axiom, int* out, const char* rulesKey, const int* rulesValueLength, int axiomLength, int rulesLength)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;

    bool found = false;

    if(tid < axiomLength)
    {
        for (int i = 0; i < rulesLength; i++)
        {
            if(axiom[tid] == rulesKey[i])
            {
                out[tid] += rulesValueLength[i];
                found = true;
                break; 
            }
        }

        if(!found)
        {
            out[tid] += 1;
        }
    }
}

__global__ void RewritingKernel(char* input, char* out, char* rulesKey, int* rulesValueLength, char** rulesValue, int* offsetArray, int inputLength, int rulesLength)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;

    bool found = false;

    if(tid < inputLength)
    {
        for (int i = 0; i < rulesLength; ++i)
        {
            if(input[tid] == rulesKey[i])
            {
                // printf("Input[%d]: %c\tLetter[%d]: %c\n", tid, input[tid], i, rulesKey[i]);

                found = true;

                int size = rulesValueLength[i];
                for (int j = 0; j < size; j++)
                {
                    // printf("out[%d] = parameters[%d][%d] -> %c\n", offsetArray[tid] + j, i, j, rulesValue[i][j]);
                    out[offsetArray[tid] + j] = rulesValue[i][j];
                }

                break;
            }
        }

        if(!found)
        {
            // printf("out[%d] = input[%d] -> %c\n", offsetArray[tid], tid, input[tid]);
            out[offsetArray[tid]] = input[tid]; 
        }
    }
}

void PrintArray(int* array, int length)
{
    for (int i = 0; i < length; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    
}

void lsystem::execute(const int iteration, const bool useGPU)
{
    setupGPUstuff();

    for (int i = 0; i < iteration; i++)
    {
        // std::cout << "Input: " << this->GPUresult << std::endl;
 
        int* valuesLength = count();
        // std::cout << "Counting substitute string length: ";
        // PrintArray(valuesLength, this->GPUresult.length());

        int* offsetArray;
        cudaMallocManaged(&offsetArray, (GPUresult.length() + 1) * sizeof(int)); 
        offsetArray = prefixSum(valuesLength);

        // std::cout << "Calculating offset array: ";
        // PrintArray(offsetArray, this->GPUresult.length() + 1);

        rewrite(offsetArray);
        // std::cout << "Output: " << this->GPUresult << std::endl;
        
        cudaFree(valuesLength);
        cudaFree(offsetArray);
    }
}

void lsystem::setupGPUstuff()
{
    this->GPUresult = this->axiom;

    this->rulesLength = this->rules.size();
    cudaMallocManaged(&this->rulesKey, this->rulesLength * sizeof(char));
    cudaMallocManaged(&this->rulesValueLength, this->rulesLength * sizeof(int));

    // Allocating memory for rules string on GPU
    cudaMallocManaged(&this->rulesValue, this->rulesLength * sizeof(char*));    

    int i = 0;
    for (const auto& [key, value] : this->rules)
    {
        this->rulesKey[i] = key;
        this->rulesValueLength[i] = value.length();

        // Allocating on GPU memory arrays of string
        cudaMallocManaged(&this->rulesValue[i], (value.length() + 1) * sizeof(char));
        strcpy(this->rulesValue[i], value.c_str());

        i++;
    }
}

int* lsystem::count()
{
    int threads = 1024;
    int blocks = (this->GPUresult.length() + threads - 1) / threads;

    int* out;
    cudaMallocManaged(&out, this->GPUresult.length() * sizeof(int));
    cudaMemset(out, 0, this->GPUresult.length() * sizeof(int));

    char* axiom;
    cudaMallocManaged(&axiom, this->GPUresult.length() * sizeof(char));
    memcpy(axiom, this->GPUresult.c_str(), this->GPUresult.length() * sizeof(char));

    countKernel<<<blocks, threads>>>(axiom, out, this->rulesKey, this->rulesValueLength, this->GPUresult.length(), this->rulesLength);
    cudaDeviceSynchronize();

    return out;
}

int* lsystem::prefixSum(int* input)
{
    thrust::device_vector<int> d_input(input, input + this->GPUresult.length());
    thrust::device_vector<int> d_output(this->GPUresult.length() + 1);

    thrust::inclusive_scan(d_input.begin(), d_input.end(), d_output.begin() + 1);

    int* result;
    cudaMallocManaged(&result, (this->GPUresult.length() + 1) * sizeof(int));
    cudaMemcpy(result, thrust::raw_pointer_cast(d_output.data()), (this->GPUresult.length() + 1) * sizeof(int), cudaMemcpyDeviceToDevice);

    return result;
}

void lsystem::rewrite(int* offsetArray)
{
    char* input;
    cudaMallocManaged(&input, this->GPUresult.length() * sizeof(char));
    memcpy(input, this->GPUresult.c_str(), this->GPUresult.length() * sizeof(char));

    char* out;
    cudaMallocManaged(&out, offsetArray[this->GPUresult.length()] * sizeof(char));
    cudaMemset(out, 0, offsetArray[this->GPUresult.length()] * sizeof(char));

    int threads = 1024;
    int blocks = (this->GPUresult.length() * threads - 1) / threads;

    RewritingKernel<<<blocks, threads>>>(input, out, this->rulesKey, this->rulesValueLength, this->rulesValue, offsetArray, this->GPUresult.length(), this->rulesLength);
    cudaDeviceSynchronize();

    this->GPUresult = out;

    cudaFree(input);
    cudaFree(out);
}