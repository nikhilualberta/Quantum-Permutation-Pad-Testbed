#include <iostream>
#include <string>
#include <vector>

#include "qpp_encryption_utilities.h"
#include "qpp_encrypt_decrypt.h"
using namespace std;

int main() {
    int permutation_mat_size = 8, total_gates = 1; // Should be constants
    qpp_key test_key;
    int*** permutation_matrices;
    int*** transpose_matrices;
    generate_key(&test_key, permutation_mat_size, total_gates);
    
    // for(int num : test_key.gates_subset) {
    //     printf("%d ", num);
    // }
    // printf("\n");
    // for(int num : test_key.chosen_gates) {
    //     printf("%d ", num);
    // }
    // printf("\n");

    // Testing generated permutation matricies
    // printf("transposes: \n");
    permutation_matrices = generate_permutation_matrices(permutation_mat_size, total_gates, test_key.gates_subset);
    // for(int mat = 0; mat < total_gates; mat++) {
    //     printf("#%d\n", mat);
    //     for (int row = 0; row < permutation_mat_size; row++) {
    //         for (int col = 0; col < permutation_mat_size; col++) {
    //             printf("%d ", permutation_matrices[mat][row][col]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }

    // Testing generated transpose matricies
    // printf("transposes: \n");
    transpose_matrices = generate_transpose_matrices(permutation_matrices, total_gates, permutation_mat_size);
    // for(int mat = 0; mat < total_gates; mat++) {
    //     printf("#%d\n", mat);
    //     for (int row = 0; row < permutation_mat_size; row++) {
    //         for (int col = 0; col < permutation_mat_size; col++) {
    //             printf("%d ", transpose_matrices[mat][row][col]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }

    string test_string = "Hello world my name is David! This is QPP - #$%6&";
    vector<bitset<8>> og_message_bits = plain_text_to_binary(test_string);
    vector<bitset<8>> cypher_bits(og_message_bits.size(), 00000000);
    vector<bitset<8>> decyphered_bits(og_message_bits.size(), 00000000);

    // Start
    cout << "Original Message: " << test_string << endl;

    // Encryption
    encrypt_decrypt(&og_message_bits, &cypher_bits, &(test_key.chosen_gates), permutation_mat_size, permutation_matrices);
    string encrypted_text = binary_to_plaintext(cypher_bits);
    cout << "Encrypted Text: " << encrypted_text << endl;
    // printf("Cypher chunks:\n");
    // for (auto chunk : cypher_bits) {
    //     cout << chunk << " ";
    // }
    // cout << endl;
    
    // Decryption
    encrypt_decrypt(&cypher_bits, &decyphered_bits, &(test_key.chosen_gates), permutation_mat_size, transpose_matrices);
    string decrypted_text = binary_to_plaintext(decyphered_bits);
    cout << "Decrypted Message at Receiver: " << decrypted_text << endl;
    // printf("Input chunks:\n");
    // for (auto chunk : og_message_bits) {
    //     cout << chunk << " ";
    // }
    // cout << endl;

    // printf("Decyphered chunks:\n");
    // for (auto chunk : decyphered_bits) {
    //     cout << chunk << " ";
    // }
    // cout << endl;
    
    // Deallocate memory
    delete_matricies(permutation_matrices, permutation_mat_size, total_gates);
    delete_matricies(transpose_matrices, permutation_mat_size, total_gates);

    return 0;
}