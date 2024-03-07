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
void generate_key(qpp_key* encryption_key, int permutation_mat_size, int total_gates) {
    for (int i = 0; i < permutation_mat_size + total_gates - 1; i++) { // -1 because each time a new permutation matrix is created we shift 
        encryption_key->gates_subset.push_back(rand() % permutation_mat_size);
        encryption_key->chosen_gates.push_back(rand() % total_gates);
    }
    return;
}

/*
permutation_mat_size: side length of the square permutation matrix
swapping_indices: the indexes to swap in the range [0, permutation_mat_size-1] to determine which columns in each row of the permutation matrix gets assigned 1
    - AKA (a splice of G)
*/
void populate_permutation_matrix(int permutation_mat_size, int** p_matrix, vector<int> swapping_indices) {
    // Fixme: implement length checking of "swapping_indices"
    int k[permutation_mat_size];
    int indexes[permutation_mat_size]; // AKA "S[]"
    int index;

    for (int i = 0; i < permutation_mat_size; i++) {
        k[i] = swapping_indices[i];
        indexes[i] = i;
        for (int j = 0; j < permutation_mat_size; j++) {
            p_matrix[i][j] = 0;
        }
    }

    printf("k: ");
    for (int num : k)
        printf("%d", num);
    printf("\n");

    printf("indexes: ");
    for (int num : indexes)
        printf("%d", num);
    printf("\n");

    for (int i = permutation_mat_size-1; i >= 0; i--) {
        index = k[i];
        printf("swapping indices %d and %d\n", index, i);
        swap(indexes[index], indexes[i]);
        printf("indexes: ");
        for (int num : indexes)
            printf("%d", num);
        printf("\n");
    }
    
    for (int i = 0; i < permutation_mat_size; i++) {
        p_matrix[i][indexes[i]] = 1;
    }
}

int*** generate_permutation_matrices(int permutation_mat_size, int total_gates, vector<int> key_first_part) {
    // Array of Permutation Matrices
    int*** matrices = new int**[total_gates];
    
    for (int i = 0; i < total_gates; i++) {
        // Find the indices to swap for this particular matrix
        auto start = key_first_part.begin() + i;
        auto end = start + permutation_mat_size;
        // To store the sliced vector
        vector<int> swapping_indices = vector<int>(start, end);
        printf("swapping_indices: ");
        for (int num : swapping_indices)
            printf("%d", num);
        printf("\n");

        // Allocate memory for the matrix
        int** P = new int*[permutation_mat_size]; //FIXME: use a more efficient matrix class? https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new/28841507#28841507
        for (int j = 0; j < permutation_mat_size; ++j) {
            P[j] = new int[permutation_mat_size];
        }
        populate_permutation_matrix(permutation_mat_size, P, swapping_indices);
        matrices[i] = P;
    }
    return matrices;
}

void delete_matricies(int*** matrices, int permutation_mat_size, int total_gates) {
    for (int mat = 0; mat < total_gates; mat++) {
            for (int row = 0; row < permutation_mat_size; row++) {
                delete[] matrices[mat][row];
            }
            delete[] matrices[mat];
        }
        delete[] matrices;
}

/*
plain_text_to_binary
binaryVector stores the 8 bit ascii representation of each character
*/
vector<bitset<8>> plain_text_to_binary(string text) {
    vector<bitset<8>> binaryVector;
    // store each character in plain text input as 8 bit ascii representation
    for (char c : text) {
        binaryVector.push_back(int(c));
    }
    return binaryVector;
}

/*
plain_text_to_2bit_decimal
binaryVector stores the 8 bit ascii representation of each character
decimalVector stores the decimal values of each two-bit segment of the binary representation
*/
vector<int> plain_text_to_2bit_decimal(string text) {
    vector<bitset<8>> binaryVector;
    // store each character in plain text input as 8 bit ascii representation
    for (char c : text) {
        binaryVector.push_back(bitset<8>(c));
    }
    vector<int> decimalVector;
    // store each character in plain text input as 8 bit ascii representation
    for (char c : text) {
        binaryVector.push_back(bitset<8>(c));
    }
    
    // Group each 8 bit ascii representation of a character to 2 bits, and convert the 2 bits to decimal
    for (const auto& binary : binaryVector) {
        for (int i = 7; i >= 0; i -= 2) { 
            int decimal_value = binary[i] * 2 + binary[i - 1] * 1; 
            decimalVector.push_back(decimal_value);
        }
    }
    
    return decimalVector;
}

