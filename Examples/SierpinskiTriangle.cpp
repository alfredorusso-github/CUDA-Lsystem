#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Sierpinski triangle
    lsystem triangle("F-G-G", "F F-G+F+G-F G GG");
    triangle.execute(6);
    triangle.executeOnGPU(6);
    triangle.write("Sierpinski triangle");
    triangle.draw("Sierpinski triangle", 120, 10);

    return 0;
}
