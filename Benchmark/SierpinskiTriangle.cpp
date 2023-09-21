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

    std::cout << "Sierpinski Triangle" << "\t Iteration: " << iteration << "\tCPU Time: " << time << "\tGPU Time: " << GPUtime << std::endl;

    std::cout << "CPU size: " << triangle.get_result().length() << "\tGPU size: " << triangle.get_GPUResult().size() << std::endl;

    return 0;
}
