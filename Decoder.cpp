
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
//    int encoded_byte[(bits_number * 2)], errors[bits_number], letter;                     to nie działa jeszcze
//    int errors_counter, bit_index = 0;
//    int signCounter = 1;
//
//    while ((letter = fgetc(text_encoded)) != EOF) {
//        if (letter != '\n')
//        {
//            letter_to_binary(encoded_byte[bit_index], letter);
//            bit_index++;
//        }
//        else
//        {
//            int error_index[2];
//            reset_table(errors, bits_number);
//            for (int i = 0; i < bits_number; i++)
//            {
//                for (int j = 0; j < (2 * bits_number); j++)
//                {
//                    errors[i] += encoded_byte[i] * matrix_H[i][j];
//                }
//                errors[i] %= 2;
//                if (errors[i] == 1)
//                {
//                    errors_counter++;
//                }
//            }
//            if (errors_counter == 1)
//            {
//                for (int i = 0; i < (bits_number * 2); i++)
//                {
//                    for (int j = 0; j < bits_number; j++)
//                    {
//                        if (matrix_H[j][i] != errors[j]) {
//                            break;
//                        }
//
//                        if (j == bits_number - 1)
//                        {
//                            encoded_byte[i] = !encoded_byte[i];
//                            i = (bits_number * 2);
//                        }
//                    }
//                }
//            }
//            if (errors_counter == 2)
//            {
//                std::cout<<"Do zrobienia!";
//            }
//            bit_index = 0;
//            signCounter++;
//            errors_counter = 0;
//            int a = 128;
//            char kod = 0;
//            for (int i = 0; i < bits_number; i++) {
//                kod += a * encoded_byte[i];
//                a /= 2;
//            }
//            fputc(kod, text_decoded);
//        }
//    }
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

void Decoder::letter_to_binary(int bit, int letter) {
    if (letter == '0')
        bit = 0;
    else if (letter == '1')
        bit = 1;
}



