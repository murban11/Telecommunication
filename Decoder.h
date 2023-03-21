
#ifndef TELECOMMUNICATION_DECODER_H
#define TELECOMMUNICATION_DECODER_H

#include <cstdio>

class Decoder
{
private:
    const int bits_number = 8;
    void reset_table(int* table, int bits_number);
    void convert_to_binary(int sign, int* message);
    void calculate_parity(int* parity_bits, int* message, int matrix_H[8][16]);
    void save_letter(int* table, FILE* text_encoded);
    void letter_to_binary(int bit, int letter);

public:
    void encode(int matrix_H[8][16], FILE* text_received, FILE* text_encoded);
    void decode(int matrix_H[8][16], FILE* text_encoded, FILE* text_decoded);

};

#endif //TELECOMMUNICATION_DECODER_H
