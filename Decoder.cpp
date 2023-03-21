
#include <iostream>
#include "Decoder.h"

void Decoder::encode(int matrix_H[8][16], FILE* text_received, FILE* text_encoded)
{
    int letter, message[bits_number], parity_bits[bits_number];

    while ((letter = fgetc(text_received)) != EOF)
    {
        reset_table(parity_bits, bits_number);
        convert_to_binary(letter, message);
        calculate_parity(parity_bits, message, matrix_H);
        save_letter(message, text_encoded);
        save_letter(parity_bits, text_encoded);
        fputc('\n', text_encoded);

    }

}

void Decoder::decode(int matrix_H[8][16], FILE* text_encoded, FILE* text_decoded)
{
    int encoded_byte[(bits_number * 2)], errors[bits_number], letter;
    int bit_index = 0;
    int signCounter = 1;
    bool error = false;

    while ((letter = fgetc(text_encoded)) != EOF) {
        if (letter != '\n') {
            letter_to_binary(encoded_byte, letter, bit_index);
            bit_index++;
        }
        else
        {
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
                        if (double_error == 1) {
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
            bit_index = 0;
            signCounter++;
            convert_from_binary(encoded_byte, text_decoded);
        }
    }
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

void Decoder::save_letter(int *table, FILE *text_encoded)
{
    for (int i = 0; i < bits_number; i++)
    {
        if (table[i] == 0)
        {
            fputc('0', text_encoded);
        } else if (table[i] == 1)
        {
            fputc('1', text_encoded);
        }
    }
}

void Decoder::letter_to_binary(int table[], int letter, int bit_index) {
    if (letter == 48)
        table[bit_index] = 0;
    else if (letter == 49)
        table[bit_index] = 1;
}

void Decoder::convert_from_binary(int *table, FILE *text_decoded) {
    int a = 128;
    char kod = 0;
    for (int i = 0; i < bits_number; i++) {
        kod += a * table[i];
        a /= 2;
    }
    fputc(kod, text_decoded);
}



