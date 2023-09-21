#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Island Curve
    lsystem island("F-F-F-F", "F F-b+FF-F-FF-Fb-FF+b-FF+F+FF+Fb+FFF b bbbbbb");
    int iteration = 6;

    std::cout << "Executing CPU algorithm..." << std::endl;
    double time = MeasureTime(&island, &lsystem::execute, iteration);

    std::cout << "Executing GPU algorithm..." << std::endl;
    double GPUtime = MeasureTime(&island, &lsystem::executeOnGPU, iteration);
    
    std::cout << "Island Curve" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    std::cout << "CPU size: " << island.get_result().length() << "\tGPU size: " << island.get_GPUResult().length() << std::endl;

    return 0;
}
