#include "lsystem.h"
#include "../utils/MeasureTime.h"

double BarnsleyFernTime;
double BarnsleyFernGPUTime;
double BarnsleyFernGPUModulesTime;

double DragonCurveTime;
double DragonCurveGPUTime;
double DragonCurveGPUModulesTime;

double HilbertCurveTime;
double HilbertCurveGPUTime;
double HilbertCurveGPUModulesTime;

double IslandCurveTime;
double IslandCurveGPUTime;
double IslandCurveGPUModulesTime;

double KochCurveTime;
double KochCurveGPUTime;
double KochCurveGPUModulesTime;

double PentaplexityTime;
double PentaplexityGPUTime;
double PentaplexityGPUModulesTime;

double PitaevskiiTime;
double PitaevskiiGPUTime;
double PitaevskiiGPUModulesTime;

double ArrowheadTime;
double ArrowheadGPUTime;
double ArrowheadGPUModulesTime;

double TriangleTime;
double TriangleGPUTime;
double TriangleGPUModulesTime;

double SticksTime;
double SticksGPUTime;
double SticksGPUModulesTime;

void test_BarnsleyFern()
{
    lsystem barnsley("X", "X F+[[X]-X]-F[-FX]+X F FF");
    int iteration = 7;

    std::cout << "Executing Barnsley Fern l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    BarnsleyFernTime = MeasureTime(&barnsley, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    BarnsleyFernGPUTime = MeasureTime(&barnsley, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    BarnsleyFernGPUModulesTime = MeasureTime(&barnsley, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_DragonCurve()
{
    lsystem dragon("FX", "X X+YF+ Y -FX-Y");
    int iteration = 12;

    std::cout << "Executing Dragon Curve l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    DragonCurveTime = MeasureTime(&dragon, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    DragonCurveGPUTime = MeasureTime(&dragon, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    DragonCurveGPUModulesTime = MeasureTime(&dragon, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_HilbertCurve()
{
    lsystem hilbert("LFL+F+LFL", "L -RF+LFL+FR- R +LF-RFR-FL+");
    int iteration = 5;

    std::cout << "Executing Hilbert Curve l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    HilbertCurveTime = MeasureTime(&hilbert, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    HilbertCurveGPUTime = MeasureTime(&hilbert, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    HilbertCurveGPUModulesTime = MeasureTime(&hilbert, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_IslandCurve()
{
    lsystem island("F-F-F-F", "F F-b+FF-F-FF-Fb-FF+b-FF+F+FF+Fb+FFF b bbbbbb");
    int iteration = 2;

    std::cout << "Executing Island Curve l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    IslandCurveTime = MeasureTime(&island, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    IslandCurveGPUTime = MeasureTime(&island, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    IslandCurveGPUModulesTime = MeasureTime(&island, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_KochCurve()
{
    lsystem koch("F", "F F+F-F-F+F");
    int iteration = 4;

    std::cout << "Executing Koch Curve l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    KochCurveTime = MeasureTime(&koch, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    KochCurveGPUTime = MeasureTime(&koch, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    KochCurveGPUModulesTime = MeasureTime(&koch, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_Pentaplexity()
{
    lsystem pentaplexity("F++F++F++F++F", "F F++F++F+++++F-F++F");
    int iteration = 4;

    std::cout << "Executing Pentaplexity l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    PentaplexityTime = MeasureTime(&pentaplexity, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    PentaplexityGPUTime = MeasureTime(&pentaplexity, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    PentaplexityGPUModulesTime = MeasureTime(&pentaplexity, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_PitaevskiiTree()
{
    lsystem pitaevskii("F", "F FF-[-F+F+F]+[+F-F-F]");
    int iteration = 5;

    std::cout << "Executing Pitaevskii Tree l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    PitaevskiiTime = MeasureTime(&pitaevskii, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    PitaevskiiGPUTime = MeasureTime(&pitaevskii, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    PitaevskiiGPUModulesTime = MeasureTime(&pitaevskii, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_SierpinskiArrowhead()
{
    lsystem arrowhead("A", "A B-A-B B A+B+A");
    int iteration = 7;

    std::cout << "Executing Sierpiski Arrowhead l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    ArrowheadTime = MeasureTime(&arrowhead, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    ArrowheadGPUTime = MeasureTime(&arrowhead, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    ArrowheadGPUModulesTime = MeasureTime(&arrowhead, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_SierpinskiTriangle()
{
    lsystem triangle("F-G-G", "F F-G+F+G-F G GG");
    int iteration = 7;

    std::cout << "Executing Sierpiski Triangle l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    TriangleTime = MeasureTime(&triangle, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    TriangleGPUTime = MeasureTime(&triangle, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    TriangleGPUModulesTime = MeasureTime(&triangle, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void test_Sticks()
{
    lsystem sticks("X", "X F[+X]F[-X]+X F FF");
    int iteration = 9;

    std::cout << "Executing Sticks l-system..." << std::endl;

    std::cout << "CPU execution..." << std::endl;
    SticksTime = MeasureTime(&sticks, &lsystem::execute, iteration);

    std::cout << "GPU execution..." << std::endl;
    SticksGPUTime = MeasureTime(&sticks, &lsystem::executeOnGPU, iteration);

    std::cout << "GPU execution with modules..." << std::endl;
    SticksGPUModulesTime = MeasureTime(&sticks, &lsystem::executeOnGPUWithModules, iteration, 3);
}

void printResults()
{
    std::cout << "Results\nBarnsley Fern\tCPU time: " << BarnsleyFernTime << "\tGPU time: " << BarnsleyFernGPUTime << std::endl;
    std::cout << "Dragon Curve\tCPU time: " << DragonCurveTime << "\tGPU time: " << DragonCurveGPUTime << std::endl;
    std::cout << "Hilber Curve\tCPU time: " << HilbertCurveTime << "\tGPU time: " << HilbertCurveGPUTime << std::endl;
    std::cout << "Koch Curve\tCPU time: " << KochCurveTime << "\tGPU time: " << KochCurveGPUTime << std::endl;
    std::cout << "Pentaplexity\tCPU time: " << PentaplexityTime << "\tGPU time: " << PentaplexityGPUTime << std::endl;
    std::cout << "Sierpinski Arrowhead\tCPU time: " << ArrowheadTime << "\tGPU time: " << ArrowheadGPUTime << std::endl;
    std::cout << "Sierpinski Triangle\tCPU time: " << TriangleTime << "\tGPU time: " << TriangleGPUTime << std::endl;
    std::cout << "Sticks\tCPU time: " << SticksTime << "\tGPU time: " << SticksGPUTime << std::endl;
}

void writeResults()
{
    std::ofstream outputFile("ResultsSmall.txt");

    if (!outputFile.is_open()) {
        std::cerr << "Errore nell'apertura del file" << std::endl;
        return;
    }

    std::string result = 
        "Results\nBarnsley Fern\tCPU time: " + std::to_string(BarnsleyFernTime) + "\tGPU time: " + std::to_string(BarnsleyFernGPUTime) + "\tGPU Module time: " + std::to_string(BarnsleyFernGPUModulesTime) +
        "\nDragon Curve\tCPU time: " + std::to_string(DragonCurveTime) + "\tGPU time: " + std::to_string(DragonCurveGPUTime) + "\tGPU Module time: " + std::to_string(DragonCurveGPUModulesTime) +
        "\nHilber Curve\tCPU time: " + std::to_string(HilbertCurveTime) + "\tGPU time: " + std::to_string(HilbertCurveGPUTime) + "\tGPU Module time: " + std::to_string(HilbertCurveGPUModulesTime) +
        "\nKoch Curve\tCPU time: " + std::to_string(KochCurveTime) + "\tGPU time: " + std::to_string(KochCurveGPUTime) + "\tGPU Module time: " + std::to_string(KochCurveGPUModulesTime) +
        "\nPentaplexity\tCPU time: " + std::to_string(PentaplexityTime) + "\tGPU time: " + std::to_string(PentaplexityGPUTime) + "\tGPU Module time: " + std::to_string(PentaplexityGPUModulesTime) +
        "\nSierpinski Arrowhead\tCPU time: " + std::to_string(ArrowheadTime) + "\tGPU time: " + std::to_string(ArrowheadGPUTime) + "\tGPU Module time: " + std::to_string(ArrowheadGPUModulesTime) +
        "\nSierpinski Triangle\tCPU time: " + std::to_string(TriangleTime) + "\tGPU time: " + std::to_string(TriangleGPUTime) + "\tGPU Module time: " + std::to_string(TriangleGPUModulesTime) +
        "\nSticks\tCPU time: " + std::to_string(SticksTime) + "\tGPU time: " + std::to_string(SticksGPUTime) + "\tGPU Module time: " + std::to_string(SticksGPUModulesTime);

    outputFile << result << std::endl;

    outputFile.close();

    std::cout << "Result correctly written on file." << std::endl;
}

int main(int argc, char const *argv[])
{
    test_SierpinskiArrowhead();
    test_SierpinskiTriangle();
    test_Sticks();
    test_BarnsleyFern();
    test_DragonCurve();
    test_HilbertCurve();
    test_KochCurve();  
    test_Pentaplexity();  

    printResults();
    writeResults();

    return 0;
}