#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Sierpinski arrowhead
    lsystem system("A", "A B-A-B B A+B+A");
    system.execute(7);
    system.write("Sierpinski Arrowhead");
    system.draw("Sierpinski Arrowhead", 60, 10);

    return 0;
}