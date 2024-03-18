#include <iostream>
#include <vector>
#include <bitset>
#include <stdlib.h>     /* srand, rand */
using namespace std;

/*
gates_subset: a sequence of indices to swap the elements in the array [0, 1, 2, ... , M-1] to create the permutation matrix

chosen_gates: Different implementations determine this sequence differently. This uses the method in the algorithm article.
    - Another way is to use a seed that first determines gates_subset and also seeds a PRNG to produce a binary sequence (X) that will be
    XORED with the input text and modded (%) with M to determine the sequece of chosen gates  
*/
struct qpp_key {
    vector<int> gates_subset; //AKA "G"
    vector<int> chosen_gates; //AKA "M"
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
void populate_permutation_matrix(int permutation_mat_size, int** p_matrix, vector<int> swapping_indices);

int*** generate_permutation_matrices(int permutation_mat_size, int total_gates, vector<int> key_first_part); 

int*** generate_transpose_matrices(int*** og_matrices, int total_gates, int permutation_mat_size);

void delete_matricies(int*** matrices, int permutation_mat_size, int total_gates);

/*
plain_text_to_binary
binaryVector stores the 8 bit ascii representation of each character
*/
vector<bitset<8>> plain_text_to_binary(string text);

/*
message_bits: ascii binary representation of plaintext
*/
string binary_to_plaintext(vector<bitset<8>> message_bits);

/*
plain_text_to_2bit_decimal
binaryVector stores the 8 bit ascii representation of each character
decimalVector stores the decimal values of each two-bit segment of the binary representation
*/
vector<int> plain_text_to_2bit_decimal(string text);


//####################################################################################################################
// The following would be part of qpp_encrypt_decrypt.h
void encrypt_decrypt(vector<bitset<8>>* input_chunks, vector<bitset<8>>* output_bits, vector<int>* chosen_matrices, int chunk_size, int*** permutation_matrices);
