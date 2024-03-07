#include <iostream>
#include <string>
#include <vector>

#include "qpp_encryption_utilities.h"
#include "qpp_encrypt_decrypt.h"
using namespace std;

int main() {
    // int a = 300;
    // int data = 38;
    // printf("%d", a^data);

    // /Testing rand()
    // for (int i = 0; i < 10; i++) {
    //     int prand_value = rand();
    //     printf("%d\n", prand_value % 8);
    // }

    // vector<int> output = plain_text_to_2bit_decimal("Hello World");
    
    // for (const auto x: output){
    //     cout << x << endl;
    // }
    // printf("\n");

    int permutation_mat_size = 8, total_gates = 64; // Should be constants
    qpp_key test_key;
    int*** permutation_matrices;
    generate_key(&test_key, permutation_mat_size, total_gates);
    
    for(int num : test_key.gates_subset) {
        printf("%d ", num);
    }
    printf("\n");
    for(int num : test_key.chosen_gates) {
        printf("%d ", num);
    }
    printf("\n");

    // Testing generated permutation matrix
    permutation_matrices = generate_permutation_matrices(permutation_mat_size, total_gates, test_key.gates_subset);
    for(int mat = 0; mat < total_gates; mat++) {
        for (int row = 0; row < permutation_mat_size; row++) {
            for (int col = 0; col < permutation_mat_size; col++) {
                printf("%d ", permutation_matrices[mat][row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }

    string test_string = "Hello world my name is David!";
    vector<bitset<8>> input_bits = plain_text_to_binary(test_string);
    bitset<8> output_bits[input_bits.size()];

    printf("Input chunks:\n");
    for (auto chunk : input_bits) {
        cout << chunk << endl;
    }

    encrypt_plaintext(&input_bits, output_bits, &(test_key.chosen_gates), permutation_mat_size, permutation_matrices);

    printf("Final output chunks:\n");
    for (auto chunk : output_bits) {
        cout << chunk << endl;
    }
    // printf("encrypted message: ");
    // for (int num; i < 40; i++) {
    //     printf("%d ", ptr[i]);
    // }
    // printf("\n");

    // Deallocate memory
    delete_matricies(permutation_matrices, permutation_mat_size, total_gates);

    return 0;
}