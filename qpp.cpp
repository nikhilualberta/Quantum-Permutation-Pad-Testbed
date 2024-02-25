#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

struct qpp_key {
    vector<int> gates_subset; //AKA "G"
    vector<int> chosen_gates; //AKA "M"
};


/*
permutation_mat_size: length of the square permutation matricies used for encryption
    - This is also the length of each chunk in the encryption
    - There are a total of permutation_mat_size! possible matricies

gates_chosen: used to specify the number of gates from permutation_mat_size! chosen to be used for the encryption
    - should be >=2 so that a matrix with either index 0 or 1 can be chosen
*/
void generate_key(qpp_key* encryption_key, int permutation_mat_size, int gates_chosen) {
    for (int i = 0; i < permutation_mat_size + gates_chosen; i++) {
        encryption_key->gates_subset.push_back(rand() % permutation_mat_size); //Need to use seeding
        encryption_key->chosen_gates.push_back(rand() % gates_chosen); 
    }
    return;
}

int** generate_permutation_matrix(int permutation_mat_size, vector<int> gates_subset) {
    int k[permutation_mat_size];
    int indexes[permutation_mat_size]; // AKA "S[]"
    int index;
    int** P = new int*[permutation_mat_size]; //FIXME: use a more efficient matrix class? https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new/28841507#28841507
    for(int i = 0; i < permutation_mat_size; ++i)
        P[i] = new int[permutation_mat_size];

    // int P[permutation_mat_size][permutation_mat_size] = {0};

    for (int i = 0; i < permutation_mat_size; i++) {
        k[i] = gates_subset[i];
        indexes[i] = i;
        for (int j = 0; j < permutation_mat_size; j++) {
            P[i][j] = 0;
        }
    }

    printf("indexes: ");
    for (int num : indexes)
        printf("%d", num);
    printf("\n");

    for (int i = permutation_mat_size-1; i >= 0; i--) {
        index = k[i];
        printf("index: %d\n", index);
        printf("%d, %d\n", indexes[index], indexes[i]);
        swap(indexes[index], indexes[i]);
        printf("%d, %d\n", indexes[index], indexes[i]);
    }
    printf("indexes: ");
    for (int num : indexes)
        printf("%d", num);
    printf("\n");
    for (int i = 0; i < permutation_mat_size; i++) {
        P[i][indexes[i]] = 1;
    }

    return P;
}

/*
plain_text_to_2bit_decimal
binaryVector stores the 8 bit ascii representation of each character
decimalVector stores the decimal values of each two-bit segment of the binary representation
*/
vector<int> plain_text_to_2bit_decimal(string text) {
    vector<bitset<8>> binaryVector;
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

int main() {
    // vector<int> output = plain_text_to_2bit_decimal("Hello World");
    
    // for (const auto x: output){
    //     cout << x << endl;
    // }
    // printf();

    int permutation_mat_size = 5, gates_chosen = 3;
    qpp_key test_key;
    generate_key(&test_key, permutation_mat_size, gates_chosen);
    
    for(int num : test_key.gates_subset) {
        printf("%d ", num);
    }
    printf("\n");
    for(int num : test_key.chosen_gates) {
        printf("%d ", num);
    }
    printf("\n");

    // Testing generated permutation matrix
    int** P = generate_permutation_matrix(5, test_key.gates_subset);
    for(int i = 0; i < permutation_mat_size; i++) {
        for (int j = 0; j < permutation_mat_size; j++) {
            printf("%d ", P[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < permutation_mat_size; i++) {
        delete[] P[i];
    }
    delete[] P;

    return 0;
}