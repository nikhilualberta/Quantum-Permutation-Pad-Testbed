#include <iostream>
#include <vector>

void encrypt_plaintext(vector<bitset<8>>* input_chunks, bitset<8>* cypher_bits, vector<int>* chosen_matrices, int chunk_size, int*** permutation_matrices) {
    int** mat;
    int chunk_num = 0;

    for (const bitset<8>& chunk : *input_chunks) {
        // Determine matrix
        mat = permutation_matrices[(*chosen_matrices)[chunk_num % (chosen_matrices->size())]];

        // Display current permutation matrix
        printf("current matrix:\n");
        for (int row = 0; row < chunk_size; row++) {
            for (int col = 0; col < chunk_size; col++) {
                printf("%d ", mat[row][col]);
            }
            printf("\n");
        }
        printf("\n");

        printf("Current Chunk: ");
        cout << chunk << endl;

        printf("Current Output: ");
        cout << (cypher_bits)[chunk_num] << endl;

        // Encryption
        for (int row = 0; row < chunk_size; row++) {
            printf("Row: %d\n", row);
            for (int col = 0; col < chunk_size; col++) {
                printf("\tCol: %d -- Matval: %d -- chunkBit: %d\n", col, mat[row][col], chunk.test(chunk_size - col - 1));
                if ((mat[row][col] == 1) && chunk.test(chunk_size - col - 1)) { // i.e the bit at index col in the current chunk is 1
                    printf("\tInserting 1 to index %d of chunk %d\n", col, chunk_num);
                    (cypher_bits)[chunk_num].set(chunk_size - row - 1);
                    cout << "Current output for chunk #" << chunk_num << " " << (cypher_bits)[chunk_num] << endl;
                    break;
                }
            }
        }
        chunk_num++;
    }
}
