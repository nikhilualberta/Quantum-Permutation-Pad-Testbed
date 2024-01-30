#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

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
    vector<int> output = plain_text_to_2bit_decimal("Hello World");
    
    for (const auto x: output){
        cout << x << endl;
    }

    return 0;
}