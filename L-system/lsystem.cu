#include "lsystem.h"

#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/scan.h>
#include<math.h>

lsystem::lsystem(std::string axiom, std::string rules): axiom(""), rules({})
{
    this->axiom = axiom;

    if(axiom.length() == 0)
    {
        throw AxiomEmptyExecption();
    }

    if(rules.length() == 0)
    {
        throw RulesEmptyException();
    }

    try
    {
        parseString(rules);
    }
    catch(const RulesWrongFormatException &e)
    {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
    
}

lsystem::lsystem(std::string axiom, std::map<char, std::string> rules): axiom(""), rules({})
{
    if(axiom.length() == 0)
    {
        throw AxiomEmptyExecption();
    } 

    if(rules.empty())
    {
        throw RulesEmptyException();
    }  

    this->axiom = axiom;
    this->rules = rules;
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
    freeMemory();
}

void lsystem::freeMemory()
{
    if(this->isGpuUsed && this->isFreeNeeded)
    {
        cudaFree(this->rulesKey);
        cudaFree(this->rulesValueLength);

        for (int i = 0; i < this->rulesLength; i++)
        {
            cudaFree(this->rulesValue[i]); 
        }
        cudaFree(this->rulesValue);

        isFreeNeeded = false;
        isGpuUsed = false;
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
    if(this->result.length() == 0)
    {
        throw EmptyResultExecption();
    }

    return this->result;
}

std::string lsystem::get_GPUResult() const
{
    if(this->GPUresult.length() == 0)
    {
        throw EmptyGpuResultExecption();
    }

    return this->GPUresult;
}

std::map<char, int> lsystem::get_meanings() const
{
    return this->meanings;
}

std::ostream &operator<<(std::ostream &os, const lsystem &system)
{
    if(system.rules.size() == 0 || system.axiom.empty())
    {
        throw RulesEmptyException();
    }

    os << "l-system specs" << std::endl;
    os << "axiom: " << system.get_axiom() << std::endl;

    os << "rules: "; 
    for (const auto& [key, value] : system.get_rules())
    {
        os << key << " → " << value << "  ";
    }

    os << std::endl <<  "meanings: ";
    for (const auto& [key, value] : system.get_meanings())
    {
        os << key << " → " << system.symbolMeaningsName[value] << "  ";
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

void lsystem::setMeaning(std::string symbols, int meaning)
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

void lsystem::write(const std::string name, const bool writeGPUResult) const
{
    if(writeGPUResult && this->GPUresult.length() == 0)
    {
        throw EmptyGpuResultExecption();
    }

    if(!writeGPUResult && this->result.length() == 0)
    {
        throw EmptyResultExecption();
    }

    std::ofstream file("../Results/" + name + ".txt", std::ios::out);

    std::string whatToWrite = writeGPUResult ? this->GPUresult : this->result;
    
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

void lsystem::draw(const std::string name, const double turnAngle, const int stepLength, const bool drawGPUResult, const int startingDirection)
{
    if(drawGPUResult && this->GPUresult.length() == 0)
    {
        throw EmptyGpuResultExecption();
    }

    if(!drawGPUResult && this->result.length() == 0)
    {
        throw EmptyResultExecption();
    }

    std::ofstream file("../Results/" + name + ".svg");
    if (!file.is_open()) {
        std::cerr << "An error occured when tried to open/create the files." << std::endl;
        return;
    }

    file << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl;

    double x = 0.0;
    double y = 0.0;

    double angle = startingDirection;

    std::string whatToDraw = drawGPUResult ? this->GPUresult : this->result;

    for (char c : whatToDraw) {
        if (this->meanings[c] == Draw) {
            
            double newX = x + stepLength * cos( angle * M_PI / 180.0 );
            double newY = y + stepLength * sin( angle * M_PI / 180.0 );

            file << "<line x1=\"" << static_cast<int>(x) << "\" y1=\"" << static_cast<int>(y)<< "\" x2=\"" << static_cast<int>(newX) << "\" y2=\"" << static_cast<int>(newY) << "\" stroke=\"black\" stroke-width=\"0.8\"/>" << std::endl;

            x = newX;
            y = newY;
        }
        else if (this->meanings[c] == Turnright) {
            angle += turnAngle;
        }
        else if (this->meanings[c] == Turnleft) {
            angle -= turnAngle;
        }
        else if(this->meanings[c] == Move)
        {
            double newX = x + stepLength * cos( angle * M_PI / 180.0 );
            double newY = y + stepLength * sin( angle * M_PI / 180.0 );

            x = newX;
            y = newY;
        }
        else if (this->meanings[c] == Push)
        {
            this->states.push(angle);
            this->states.push(y);
            this->states.push(x);
        }
        else if (this->meanings[c] == Pop)
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

__global__ void countKernelWithModules(const char* axiom, int* out, const char* rulesKey, const int* rulesValueLength, int axiomLength, int rulesLength, int n_modules, int modulesLength)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;

    bool found = false;

    if(tid < n_modules)
    {
        for (int i = 0; i < modulesLength; i++)
        {
            if(tid * modulesLength + i == axiomLength) break;

            for (int j = 0; j < rulesLength; j++)
            {
                if(axiom[tid * modulesLength + i] == rulesKey[j])
                {
                    out[tid] += rulesValueLength[j];
                    found = true;
                }
            }

            if(!found)
            {
                out[tid] += 1;
            }

            found = false;
        }
    }
}

__global__ void RewritingKernel(char* input, char* out, char* rulesKey, int* rulesValueLength, char** rulesValue, int* offsetArray, int inputLength, int rulesLength)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;

    bool found = false;

    if(tid < inputLength)
    {
        for (int i = 0; i < rulesLength; i++)
        {
            if(input[tid] == rulesKey[i])
            {
                // printf("Input[%d]: %c\tLetter[%d]: %c\n", tid, input[tid], i, rulesKey[i]);

                found = true;

                int size = rulesValueLength[i];
                for (int j = 0; j < size; j++)
                {
                    // printf("tid: %d\tout[%d] = parameters[%d][%d] -> %c\n", tid, offsetArray[tid] + j, i, j, rulesValue[i][j]);
                    out[offsetArray[tid] + j] = rulesValue[i][j];
                }

                break;
            }
        }

        if(!found)
        {
            // printf("out[%d] = input[%d] -> %c\n", offsetArray[tid], tid, input[tid]);
            printf("");
            out[offsetArray[tid]] = input[tid]; 
        }
    }
}

__global__ void RewritingKernelWithModules(char* input, char* out, char* rulesKey, int* rulesValueLength, char** rulesValue, int* offsetArray, int inputLength, int rulesLength, int n_modules, int modulesLength)
{
    int tid = blockDim.x * blockIdx.x + threadIdx.x;

    bool found = false;

    if(tid < n_modules)
    {
        int index = 0;

        for (int i = 0; i < modulesLength; i++)
        {
            if(tid * modulesLength + i == inputLength) break;

            // printf("tid: %d \t input[%d] = %c \n", tid, tid * modulesLength + i, input[tid * modulesLength + i]);
            
            for (int j = 0; j < rulesLength; j++)
            {
                if(input[tid * modulesLength + i] == rulesKey[j])
                {
                    found = true;
                    // if (tid == 6) printf("input[%d] = %c found at rulesKey[%d] = %c\n", tid * modulesLength + i, input[tid * modulesLength + i], j, rulesKey[j]);

                    int size = rulesValueLength[j];
                    for (int k = 0; k < size; k++)
                    {
                        out[offsetArray[tid] + index] = rulesValue[j][k];
                        // printf("out[%d] = %c\n", offsetArray[tid] + index, rulesValue[j][k]);
                        index += 1;
                    }
                }
            }

            if(!found)
            {
                out[offsetArray[tid] + index] = input[tid * modulesLength + i];
                // printf("Not found, out[%d] = %c\n", offsetArray[tid] + index, input[tid * modulesLength + i]);
                index += 1;
            }

            found = false;
        }
    }
}

void lsystem::executeOnGPU(const int iteration)
{
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) 
    {
        std::cerr << "CUDA initialization error: " << cudaGetErrorString(cudaStatus) << std::endl;
        return;
    }

    this->isGpuUsed = true;
    this->isFreeNeeded = true;

    setupGPUstuff();

    for (int i = 0; i < iteration; i++)
    {
        // std::cout << "Input: " << this->GPUresult << std::endl;
        
        int* valuesLength = count();
        // std::cout << "Counting substitute string length: ";
        // PrintArray(valuesLength, this->GPUresult.length());      

        // std::cout << "Iteration " << i << " string length: " << this->GPUresult.length() << std::endl;
        int* offsetArray;
        cudaMallocManaged(&offsetArray, (this->GPUresult.length() + 1) * sizeof(int)); 
        thrust::exclusive_scan(valuesLength, valuesLength + this->GPUresult.length() + 1, offsetArray);

        // for (int i = 0; i < this->GPUresult.length() + 1; i++)
        // {
        //     printf("%d ", offsetArray[i]);
        // }
        // printf("\n");        

        // std::cout << "Calculating offset array: ";
        // PrintArray(offsetArray, this->GPUresult.length() + 1);

        rewrite(offsetArray);
        // std::cout << "Output: " << this->GPUresult << std::endl;
    
        cudaFree(valuesLength);
        cudaFree(offsetArray);
    }
}

void lsystem::executeOnGPUWithModules(const int iteration, const int modulesLength)
{
    cudaError_t cudaStatus = cudaSetDevice(0);
    if (cudaStatus != cudaSuccess) 
    {
        std::cerr << "CUDA initialization error: " << cudaGetErrorString(cudaStatus) << std::endl;
        return;
    }

    this->isGpuUsed = true;
    this->isFreeNeeded = true;

    setupGPUstuff();

    for (int i = 0; i < iteration; i++)
    {
        int* valuesLength = countWithModules(modulesLength);    

        int* offsetArray;
        int n_modules = ceil(static_cast<float>(this->GPUresult.length()) / modulesLength);
        cudaMallocManaged(&offsetArray, (n_modules + 1) * sizeof(int));
        thrust::exclusive_scan(valuesLength, valuesLength + n_modules + 1, offsetArray);

        rewriteWithModules(offsetArray, modulesLength);          

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
    size_t n_character = this->GPUresult.length();

    int threads = n_character > 1024 ? 1024 : n_character;
    int blocks = (n_character + threads - 1) / threads;

    int* out;
    cudaMallocManaged(&out, n_character * sizeof(int));
    cudaMemset(out, 0, n_character * sizeof(int));

    char* axiom;
    cudaMalloc((void**) &axiom, n_character * sizeof(char));
    cudaMemcpy(axiom, this->GPUresult.c_str(), n_character, cudaMemcpyHostToDevice);

    countKernel<<<blocks, threads>>>(axiom, out, this->rulesKey, this->rulesValueLength, n_character, this->rulesLength);
    cudaDeviceSynchronize();

    cudaFree(axiom);

    return out;
}

int* lsystem::countWithModules(const int modulesLength)
{
    size_t n_character = this->GPUresult.length();
    size_t n_modules = ceil(static_cast<float>(this->GPUresult.length()) / modulesLength);
    // std::cout << "Modules: " << n_modules << std::endl;

    int threads = n_modules >  1024 ? 1024 : n_modules;
    int blocks = (n_modules + threads - 1) / threads;

    int* out;
    cudaMallocManaged(&out, n_modules * sizeof(int));
    cudaMemset(out, 0, n_modules * sizeof(int));

    char* axiom;
    cudaMalloc((void**) &axiom, n_character * sizeof(char));
    cudaMemcpy(axiom, this->GPUresult.c_str(), n_character, cudaMemcpyHostToDevice);

    countKernelWithModules<<<blocks, threads>>>(axiom, out, this->rulesKey, this->rulesValueLength, n_character, this->rulesLength, n_modules, modulesLength); 
    cudaDeviceSynchronize();

    cudaFree(axiom);
    
    return out;
}

void lsystem::rewrite(int* offsetArray)
{
    size_t n_character = this->GPUresult.length();

    char* input;
    cudaMalloc((void**) &input, n_character * sizeof(char));
    cudaMemcpy(input, this->GPUresult.c_str(), n_character * sizeof(char), cudaMemcpyHostToDevice);

    char* output;
    cudaMalloc((void**) &output, offsetArray[n_character] * sizeof(char));

    int threads = n_character > 1024 ? 1024 : n_character;
    int blocks = (n_character + threads - 1) / threads;

    RewritingKernel<<<blocks, threads>>>(input, output, this->rulesKey, this->rulesValueLength, this->rulesValue, offsetArray, n_character, this->rulesLength);
    cudaDeviceSynchronize();

    char* out = (char*) malloc(offsetArray[n_character] * sizeof(char));
    cudaMemcpy(out, output, offsetArray[n_character] * sizeof(char), cudaMemcpyDeviceToHost);

    this->GPUresult = out;

    cudaFree(input);
    cudaFree(output);
    free(out);
}

void lsystem::rewriteWithModules(int* offsetArray, const int modulesLength)
{
    size_t n_character = this->GPUresult.length();
    size_t n_modules = ceil(static_cast<float>(this->GPUresult.length()) / modulesLength);
    size_t output_characters = offsetArray[n_modules];

    char* input;
    cudaMalloc((void**) &input, n_character * sizeof(char));
    cudaMemcpy(input, this->GPUresult.c_str(), n_character * sizeof(char), cudaMemcpyHostToDevice);

    char* output = nullptr;
    cudaMalloc((void**) &output, output_characters * sizeof(char));
    cudaMemset(output, 'a', output_characters * sizeof(char));

    int threads = n_modules > 1024 ? 1024 : n_modules;
    int blocks = (n_modules + threads - 1) / threads;

    RewritingKernelWithModules<<<blocks, threads>>>(input, output, this->rulesKey, this->rulesValueLength, this->rulesValue, offsetArray, n_character, this->rulesLength, n_modules, modulesLength);
    cudaDeviceSynchronize();

    char* out = (char*) malloc(output_characters * sizeof(char));
    cudaMemcpy(out, output, output_characters * sizeof(char), cudaMemcpyDeviceToHost);

    this->GPUresult = out;

    cudaFree(input);
    cudaFree(output);
    free(out);
}