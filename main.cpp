#include <iostream>
#include <memory>
#include "Decoder.h"

int matrix_H [8][16] = {
        {0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
};

int main() {
    FILE *code = fopen("przed.txt", "r");
    FILE *code2 = fopen("po.txt", "r");
    FILE *code3 = fopen("zdekodowany.txt", "w");
    std::shared_ptr<Decoder> decoder = std::make_shared<Decoder>();
    //decoder->encode(matrix_H, code, code2);
    decoder->decode(matrix_H,code2, code3);
    fclose(code);
    fclose(code2);
    fclose(code3);
    return 0;
}
