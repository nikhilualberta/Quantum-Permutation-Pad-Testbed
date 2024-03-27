#include "qpp_all_functions.h"

void generate_key(qpp_key* encryption_key, int permutation_mat_size, int total_gates) {
    for (int i = 0; i < permutation_mat_size + total_gates - 1; i++) { // -1 because each time a new permutation matrix is created we shift 
        encryption_key->gates_subset[i] = (rand() % permutation_mat_size);
        encryption_key->chosen_gates[i] = (rand() % total_gates);
    }
    return;
}

/*
permutation_mat_size: side length of the square permutation matrix
swapping_indices: the indexes to swap in the range [0, permutation_mat_size-1] to determine which columns in each row of the permutation matrix gets assigned 1
    - AKA (a splice of G)
*/
void populate_permutation_matricies(int (*matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE], int permutation_mat_size, int total_gates, int* swapping_indices) {
    // Fixme: implement length checking of "swapping_indices"
    for (int mat = 0; mat < total_gates; mat++)
    {
        int indexes[permutation_mat_size]; // AKA "S[]"
        int current_swapping_indices[permutation_mat_size];
        int index;

        for (int i = mat; i < mat + PERMUTATION_MAT_SIZE; i++) {
            printf("i: %d, start: %d, stop: %d\n", i, mat, mat + PERMUTATION_MAT_SIZE);
            current_swapping_indices[i-mat] = swapping_indices[i];
        }

        for (int i = 0; i < permutation_mat_size; i++) {
            indexes[i] = i;
            for (int j = 0; j < permutation_mat_size; j++) {
                matrices[mat][i][j] = 0;
            }
        }

        for (int i = permutation_mat_size-1; i >= 0; i--) {
            index = current_swapping_indices[i];
            swap(indexes[index], indexes[i]);
        }
        
        for (int i = 0; i < permutation_mat_size; i++) {
            matrices[mat][i][indexes[i]] = 1;
        }
    }
}

void populate_transpose_matrices(int (*og_matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE], int (*transpose_matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE], int permutation_mat_size, int total_gates) {
    // Array of Transpose Matrices

    for (int mat = 0; mat < total_gates; mat++) {
        for (int row = 0; row < permutation_mat_size; ++row) {
            for (int col = 0; col < permutation_mat_size; col++) {
                transpose_matrices[mat][row][col] = og_matrices[mat][col][row];
            }
        }
    }
}

/*
plain_text_to_binary
binaryVector stores the 8 bit ascii representation of each character
*/
void plain_text_to_binary(char* text, int input_length, bitset<8>* binary) {
    // store each character in plain text input as 8 bit ascii representation
    for (int i = 0; i < input_length; i++) {
        binary[i] = (int(text[i]));
    }
}

// /*
// message_bits: ascii binary representation of plaintext
// */
void binary_to_plaintext(bitset<8>* message_bits, char* message_string, int length) {
    for (int i = 0; i < length; i++) {
        message_string[i] = char(message_bits[i].to_ulong());
    }
}

void encrypt_decrypt(bitset<8>* input_chunks, bitset<8>* output_bits, int input_length, int* chosen_matrices, int (*permutation_matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE]) {
    int (*mat)[PERMUTATION_MAT_SIZE];
    for (int chunk = 0; chunk < input_length; chunk++)
    {
        mat = permutation_matrices[chosen_matrices[chunk % TOTAL_GATES]];

        // Encryption
        for (int row = 0; row < PERMUTATION_MAT_SIZE; row++) {
            for (int col = 0; col < PERMUTATION_MAT_SIZE; col++) {
                if ((mat[row][col] == 1) && input_chunks[chunk].test(PERMUTATION_MAT_SIZE - col - 1)) { // i.e the bit at index col in the current chunk is 1
                    output_bits[chunk].set(PERMUTATION_MAT_SIZE - row - 1);
                    break;
                }
            }
        }
    }
}