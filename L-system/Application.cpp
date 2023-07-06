#include "lsystem.h"

int main(int argc, char const *argv[])
{
    lsystem custom("F-G-G", "F F-G+F+G-F G GG");
    custom.setCustomMeaning("F", custom.DRAW);
    custom.setCustomMeaning("G", custom.DONOTHING);
    custom.setCustomMeaning("-", custom.TURNLEFT);
    custom.setCustomMeaning("+", custom.TURNRIGHT);
    custom.execute(7);
    custom.write("Custom");
    custom.draw("Custom");

    return 0;
}
