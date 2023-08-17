#include "lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    lsystem custom("F-G-G", "F F-G+F+G-F G GG");
    custom.setCustomMeaning("F", custom.DRAW);
    custom.setCustomMeaning("G", custom.DONOTHING);
    custom.setCustomMeaning("-", custom.TURNLEFT);
    custom.setCustomMeaning("+", custom.TURNRIGHT);

    double time = MeasureTime(&custom, &lsystem::execute, 15);
    double GPUtime = MeasureTime(&custom, &lsystem::executeOnGPU, 15);
    std::cout << "CPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    // Check result
    size_t sizeCPU = custom.get_result().size();
    size_t sizeGPU = custom.get_GPUResult().size();
    std::cout << "CPU result size: " << sizeCPU << "\tGPU result size: " << sizeGPU << std::endl;

    std::string CPUresult = custom.get_result();
    std::string GPUresult = custom.get_GPUResult();

    for (int i = 0; i < sizeCPU; i++)
    {
        if(CPUresult[i] != GPUresult[i])
        {
            std::cerr << "Result error -> position [" << i << "] \t CPUresult[" << i << "] = " << CPUresult[i] << "\t GPUresult[" << i << "] = " << GPUresult[i] << std::endl;
            return 1; 
        }
    }
    
    std::cout << "Test Passed!" << std::endl;
    
    // custom.write("Custom");
    // custom.draw("Custom", 20, 10);

    return 0;
}
