
#include <iostream>
#include <fstream>
#include <memory>
#include "Decoder.h"

void Decoder::decode(int matrix_H[8][16], std::ifstream& text_received, const std::string& filename)
{
    std::ofstream decoded;
    decoded.open(filename);
    int encoded_byte[(bits_number * 2)], errors[bits_number], letter;
    int test[bits_number], test2[bits_number];
    int signCounter = 1;
    bool error = false;
    int parity_bits;

    while (((letter = text_received.get()) | (parity_bits = text_received.get())) != EOF) {
        convert_to_binary(letter, test);
        convert_to_binary(parity_bits, test2);
        for (int i = 0; i < 8; i++) {
            encoded_byte[i] = test[i];
        }
        for (int i = 8; i < 16; i++) {
            encoded_byte[i] = test2[i - 8];
        }
        int error_index[2];
        reset_table(errors, bits_number);
        for (int i = 0; i < bits_number; i++)
        {
            for (int j = 0; j < (2 * bits_number); j++)
            {
                errors[i] += encoded_byte[j] * matrix_H[i][j];
            }
            errors[i] %= 2;
            if (errors[i] == 1)
            {
                error = true;
            }
        }
        if (error)
        {
            bool double_error;
            for (int i = 0; i < 15; i++) {
                for (int j = i + 1; j < (bits_number * 2); j++) {
                    double_error = true;
                    for (int k = 0; k < bits_number; k++) {
                        if (errors[k] != matrix_H[k][i] ^ matrix_H[k][j]) {
                            double_error = false;
                            break;
                        }
                    }
                    if (double_error) {
                        error_index[0] = i;
                        error_index[1] = j;
                        encoded_byte[error_index[0]] = !encoded_byte[error_index[0]];
                        encoded_byte[error_index[1]] = !encoded_byte[error_index[1]];
                        i = (bits_number * 2);
                        break;
                    }
                }
            }
            for (int i = 0; i < (bits_number * 2); i++)
            {
                for (int j = 0; j < bits_number; j++)
                {
                    if (matrix_H[j][i] != errors[j]) {
                        break;
                    }

                    if (j == bits_number - 1)
                    {
                        encoded_byte[i] = !encoded_byte[i];
                        i = (bits_number * 2);
                    }
                }
            }
        }
        signCounter++;
    decoded<<convert_from_binary(encoded_byte);
    }
    decoded.close();
}

void Decoder::reset_table(int *table, int bits_number)
{
    for (int i = 0; i < bits_number; i++)
    {
        table[i] = 0;
    }
}

void Decoder::convert_to_binary(int sign, int *message)
{
    for (int i = bits_number - 1; i > -1; i--)
    {
        message[i] = sign % 2;
        sign /= 2;
    }
}

void Decoder::calculate_parity(int *parity_bits, int *message, int matrix_H[8][16])
{
    for (int i = 0; i < bits_number; i++)
    {
        for (int j = 0; j < bits_number; j++)
        {
            parity_bits[i] += message[j] * matrix_H[i][j];
        }
        parity_bits[i] %= 2;
    }
}


char Decoder::convert_from_binary(int *table) {
    int a = 128;
    char kod = 0;
    for (int i = 0; i < bits_number; i++) {
        kod += a * table[i];
        a /= 2;
    }
    return kod;
}

void Decoder::encode(int (*matrix_H)[16], std::ifstream& text_received, const std::string& filename) {

    int letter = 0;
    int message[bits_number], parity_bits[bits_number];
    std::ofstream save;
    save.open(filename, std::ios::out | std::ios::binary);

    while ((letter = text_received.get()) != EOF)
    {
        reset_table(parity_bits, bits_number);
        convert_to_binary(letter, message);
        calculate_parity(parity_bits, message, matrix_H);
        save_letter(message, filename, save);
        save_letter(parity_bits, filename, save);
    }


    save.close();
}

void Decoder::save_letter(int *table, const std::string& filename, std::ofstream& save) {

    save<<convert_from_binary(table);

}



