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
    FILE *code = fopen("przed_kodowaniem.txt", "r");
    FILE *code2 = fopen("po_kodowaniu.txt", "w");
    FILE *code3 = fopen("zakodowany.txt", "r");
    FILE *code4 = fopen("odkodowany", "w");
    std::shared_ptr<Decoder> decoder = std::make_shared<Decoder>();
    decoder->encode(matrix_H, code, code2);
    decoder->decode(matrix_H,code3, code4);
    fclose(code);
    fclose(code2);
    fclose(code3);
    fclose(code4);
    return 0;
}
