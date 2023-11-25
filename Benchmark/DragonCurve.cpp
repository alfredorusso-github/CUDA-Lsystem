#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Dragon Curve
    lsystem dragon("FX", "X X+YF+ Y -FX-Y");
    int iteration = 28;

    std::cout << "Executing on CPU..." << std::endl;
    double time = MeasureTime(&dragon, &lsystem::execute, iteration);

    std::cout << "Executing on GPU..." << std::endl;
    double GPUtime = MeasureTime(&dragon, &lsystem::executeOnGPU, iteration);

    std::cout << "Executing on GPU with modules..." << std::endl;
    double GPUtimeModules = MeasureTime(&dragon, &lsystem::executeOnGPUWithModules, iteration, 32);

    std::cout << "Dragon Curve" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime <<  "\tGPU modules time: " << GPUtimeModules << std::endl;

    return 0;
}
