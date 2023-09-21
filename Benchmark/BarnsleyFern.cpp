#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Barnsley fern
    lsystem barnsley("X", "X F+[[X]-X]-F[-FX]+X F FF");
    int iteration = 14;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&barnsley, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&barnsley, &lsystem::executeOnGPU, iteration);
    
    std::cout << "Barnsley Fern" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    std::cout << "CPU size: " << barnsley.get_result().length() << "\tGPU size: " << barnsley.get_GPUResult().length() << std::endl;

    return 0;
}
