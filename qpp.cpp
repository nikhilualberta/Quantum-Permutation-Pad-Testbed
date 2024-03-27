#include <iostream>
#include <string>
#include <vector>

#include "qpp_all_functions.h"
using namespace std;

int main() {
    qpp_key test_key;
    int permutation_matrices[TOTAL_GATES][PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE];
    int transpose_matrices[TOTAL_GATES][PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE];
    generate_key(&test_key, PERMUTATION_MAT_SIZE, TOTAL_GATES);
    
    for(int num : test_key.gates_subset) {
        printf("%d ", num);
    }
    printf("\n");
    for(int num : test_key.chosen_gates) {
        printf("%d ", num);
    }
    printf("\n");

    // Testing generated permutation matricies
    printf("Permutation Gates: \n");
    populate_permutation_matricies(permutation_matrices, PERMUTATION_MAT_SIZE, TOTAL_GATES, test_key.gates_subset);
    for(int mat = 0; mat < 1; mat++) {
        printf("#%d\n", mat);
        for (int row = 0; row < PERMUTATION_MAT_SIZE; row++) {
            for (int col = 0; col < PERMUTATION_MAT_SIZE; col++) {
                printf("%d ", permutation_matrices[mat][row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }

    // // Testing generated transpose matricies
    printf("transposes: \n");
    populate_transpose_matrices(permutation_matrices, transpose_matrices, PERMUTATION_MAT_SIZE, TOTAL_GATES);
    for(int mat = 0; mat < 1; mat++) {
        printf("#%d\n", mat);
        for (int row = 0; row < PERMUTATION_MAT_SIZE; row++) {
            for (int col = 0; col < PERMUTATION_MAT_SIZE; col++) {
                printf("%d ", transpose_matrices[mat][row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }

    //Sender
    char test_string[] = "Hello world my name is David -- this is a test!";
    int input_length = sizeof(test_string)/sizeof(test_string[0]);
    char cypher_text[input_length];
    bitset<8> binary_input[input_length];
    bitset<8> cypher_bits[input_length];
    plain_text_to_binary(test_string, input_length, binary_input);

    //Receiver
    bitset<8> decyphered_bits[input_length];
    char decrypted_text[input_length];

    // // Start
    cout << "Original Message: " << test_string << endl;

    // Encryption
    encrypt_decrypt(binary_input, cypher_bits, input_length, test_key.chosen_gates, permutation_matrices);
    binary_to_plaintext(cypher_bits, cypher_text, input_length);
    cout << "Cypher text" << cypher_text << endl;
    
    // Decryption
    encrypt_decrypt(cypher_bits, decyphered_bits, input_length, test_key.chosen_gates, transpose_matrices);
    binary_to_plaintext(decyphered_bits, decrypted_text, input_length);
    cout << "Decrypted Message at Receiver: " << decrypted_text << endl;

    return 0;
}