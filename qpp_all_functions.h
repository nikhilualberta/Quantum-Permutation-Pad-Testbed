#include <iostream>
#include <vector>
#include <bitset>
#include <stdlib.h>     /* srand, rand */
using namespace std;

const int PERMUTATION_MAT_SIZE = 8;
const int TOTAL_GATES = 10;

/*
gates_subset: a sequence of indices to swap the elements in the array [0, 1, 2, ... , M-1] to create the permutation matrix

chosen_gates: Different implementations determine this sequence differently. This uses the method in the algorithm article.
    - Another way is to use a seed that first determines gates_subset and also seeds a PRNG to produce a binary sequence (X) that will be
    XORED with the input text and modded (%) with M to determine the sequece of chosen gates  
*/
struct qpp_key {
    int gates_subset[PERMUTATION_MAT_SIZE + TOTAL_GATES - 1]; //AKA "G"
    int chosen_gates[PERMUTATION_MAT_SIZE + TOTAL_GATES - 1]; //AKA "M"
};

/*
permutation_mat_size: length of the square permutation matricies used for encryption
    - This is also the length of each chunk in the encryption
    - There are a total of permutation_mat_size! possible matricies

total_gates: used to specify the number of gates from permutation_mat_size! chosen to be used for the encryption
    - should be >=2 so that a matrix with either index 0 or 1 can be chosen
*/
void generate_key(qpp_key* encryption_key, int permutation_mat_size, int total_gates);

/*
permutation_mat_size: side length of the square permutation matrix
swapping_indices: the indexes to swap in the range [0, permutation_mat_size-1] to determine which columns in each row of the permutation matrix gets assigned 1
    - AKA (a splice of G)
*/
void populate_permutation_matricies(int (*matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE], int permutation_mat_size, int total_gates, int* swapping_indices);

void populate_transpose_matrices(int (*og_matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE], int (*transpose_matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE], int permutation_mat_size, int total_gates);

/*
plain_text_to_binary
binary stores the 8 bit ascii representation of each character
*/
void plain_text_to_binary(char* text, int input_length, bitset<8>* binary);

// /*
// message_bits: ascii binary representation of plaintext
// */
void binary_to_plaintext(bitset<8>* message_bits, char* message_string, int length);

// //####################################################################################################################
// // The following would be part of qpp_encrypt_decrypt.h
void encrypt_decrypt(bitset<8>* input_chunks, bitset<8>* output_bits, int input_length, int* chosen_matrices, int (*permutation_matrices)[PERMUTATION_MAT_SIZE][PERMUTATION_MAT_SIZE]);
