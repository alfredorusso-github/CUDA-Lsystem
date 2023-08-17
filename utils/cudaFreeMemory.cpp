#include <iostream>
#include <cuda_runtime.h>

int main() {
    size_t freeMemory, totalMemory;
    cudaError_t cudaStatus;

    cudaStatus = cudaMemGetInfo(&freeMemory, &totalMemory);
    if (cudaStatus != cudaSuccess) {
        std::cerr << "Errore nell'ottenere le informazioni sulla memoria: " << cudaGetErrorString(cudaStatus) << std::endl;
        return 1;
    }

    std::cout << "Memoria GPU disponibile: " << freeMemory << " bytes" << std::endl;
    std::cout << "Memoria GPU totale: " << totalMemory << " bytes" << std::endl;

    return 0;
}