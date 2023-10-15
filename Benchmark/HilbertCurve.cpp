#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Hilber Curve
    lsystem hilbert("LFL+F+LFL", "L -RF+LFL+FR- R +LF-RFR-FL+");
    int iteration = 13;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&hilbert, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&hilbert, &lsystem::executeOnGPU, iteration);

    std::cout << "Executing GPU algorithm with modules..." << std::endl;
    double GPUtimeModules = MeasureTime(&hilbert, &lsystem::executeOnGPUWithModules, iteration, 30);
    
    std::cout << "Hilber Curve" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << "\tGPU modules time: "<< GPUtimeModules << std::endl;

    return 0;
}
