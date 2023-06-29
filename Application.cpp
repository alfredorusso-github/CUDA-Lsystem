#include "lsystem.h"

int main(int argc, char const *argv[])
{
    // Sierpinski arrowhead
    lsystem system("A", "A B-A-B B A+B+A");
    system.execute(3);

    return 0;
}
