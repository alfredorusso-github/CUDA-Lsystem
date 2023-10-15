#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Sierpinski triangle
    lsystem triangle("F-G-G", "F F-G+F+G-F G GG");
    int iteration = 18;

    std::cout << "Executing on CPU..." << std::endl;
    double time = MeasureTime(&triangle, &lsystem::execute, iteration);

    std::cout << "Executing on GPU..." << std::endl;
    double GPUtime = MeasureTime(&triangle, &lsystem::executeOnGPU, iteration);

    std::cout << "Executing on GPU with modules..." << std::endl;
    double GPUtimeModules = MeasureTime(&triangle, &lsystem::executeOnGPUWithModules, iteration, 20);

    std::cout << "Sierpinski Triangle" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << "\tGPU modules time: " << GPUtimeModules << std::endl;

    return 0;
}
