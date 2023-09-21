#include "../L-system/lsystem.h"
#include  "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Koch Curve
    lsystem koch("F", "F F+F-F-F+F");
    int iteration = 12;

    std::cout << "Executing on CPU..." << std::endl;
    double time = MeasureTime(&koch, &lsystem::execute, iteration);

    std::cout << "Executing on GPU..." << std::endl;
    double GPUtime = MeasureTime(&koch, &lsystem::executeOnGPU, iteration);

    std::cout << "Koch Curve" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    return 0;
}
