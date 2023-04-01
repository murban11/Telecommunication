
#ifndef TELECOMMUNICATION_DECODER_H
#define TELECOMMUNICATION_DECODER_H

#include <cstdio>

class Decoder
{
private:
    const int bits_number = 8;
    void reset_table(int* table, int bits_number);
    void calculate_parity(int* parity_bits, int* message, int matrix_H[8][16]);


public:
    void encode(int matrix_H[8][16], std::ifstream& text_received, const std::string& filename);
    void decode(int matrix_H[8][16], std::ifstream& text_received, const std::string& filename);
    void convert_to_binary(int sign, int* message);
    void save_letter(int* table, const std::string& filename, std::ofstream& save);
    char convert_from_binary(int* table);

};

#endif //TELECOMMUNICATION_DECODER_H
