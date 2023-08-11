#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/scan.h>

int main() {
    // Input data
    int input[] = {3, 1, 7, 0, 4, 1, 6, 3};
    int num_elements = sizeof(input) / sizeof(input[0]);
    // printf("num_elements: %d \t sizeof 1 element: %d\n", num_elements, sizeof(input[0]));

    int* prova = (int*) malloc(4 * sizeof(int));
    printf("%d\n", sizeof(prova));

    // Transfer data to the device
    thrust::device_vector<int> d_input(input, input + num_elements);
    thrust::device_vector<int> d_output(num_elements + 1);

    // Perform prefix sum
    thrust::inclusive_scan(d_input.begin(), d_input.end(), d_output.begin() + 1);

    // Transfer the result back to the host
    thrust::host_vector<int> h_output = d_output;

    // Print the result
    std::cout << "Input: ";
    for (int i = 0; i < num_elements; ++i) {
        std::cout << input[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Output: ";
    for (int i = 0; i <= num_elements; ++i) {
        std::cout << h_output[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
