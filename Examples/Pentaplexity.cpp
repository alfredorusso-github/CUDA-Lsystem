#include "../L-system/lsystem.h"

int main(int argc, char const *argv[])
{
    // Pentaplexity
    lsystem pentaplexity("F++F++F++F++F", "F F++F++F+++++F-F++F");
    pentaplexity.execute(4);
    pentaplexity.write("Pentaplexity");
    pentaplexity.draw("Pentaplexity", 36, 10);

    return 0;
}
