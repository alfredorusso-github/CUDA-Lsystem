#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Albero di Pitaevskii
    lsystem pitaevskii("F", "F FF-[-F+F+F]+[+F-F-F]");
    int iteration = 9;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&pitaevskii, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&pitaevskii, &lsystem::executeOnGPU, iteration);
    
    std::cout << "Pitaevskii Tree" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    // std::cout << "Pitaevskii tree" << "\t Iteration: " << iteration << "\tCPU Time: " << time << std::endl;

    std::cout << "CPU size: " << pitaevskii.get_result().length() << "\tGPU size: " << pitaevskii.get_GPUResult().length() << std::endl;

    return 0;
}
