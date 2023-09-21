#include "../L-system/lsystem.h"
#include "../utils/MeasureTime.h"

int main(int argc, char const *argv[])
{
    // Albero di Pitaevskii
    lsystem pitaevskii("F", "F FF-[-F+F+F]+[+F-F-F]");

    pitaevskii.execute(5);
    pitaevskii.write("Albero di Pitaevskii");
    pitaevskii.draw("Albero di Pitaevskii", 25, 10, lsystem::UP);

    return 0;
}
