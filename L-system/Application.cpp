#include "lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    lsystem custom("F-G-G", "F F-G+F+G-F G GG");

    custom.execute(7);
    custom.executeOnGPU(7);

    // std::cout << "CPU result size: " << custom.get_result().length() << "\t GPU result size: " << custom.get_GPUResult().length() << std::endl;

    std::cout << custom << std::endl;

    return 0;
}