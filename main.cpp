#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>
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

void show_binary(int* file_binary, int size)
{
    for (int i = 0; i < 8 * size; i++)
    {
        std::cout<<file_binary[i]<<" ";
        if (i % 16 == 15)
        {
            std::cout<<std::endl;
        }
    }
}

void edit_binary(std::shared_ptr<Decoder> decoder)
{
    std::cout<<"Podaj nazwe pliku do edycji: "<<std::endl;
    std::string filename;
    std::cin>>filename;
    int size = std::filesystem::file_size(filename);
    int file_binary [8 * size];
    std::ifstream file;
    int file_char [size];
    file.open(filename);
    for (int i = 0; i < size; i++)
    {
        file_char[i] = file.get();
    }
    for (int i = 0; i < size; i++)
    {
        int binary[8];
        decoder->convert_to_binary(file_char[i], binary);
        for (int j = 0; j < 8; j++)
        {
            file_binary[8 * i + j] = binary[j];
        }
    }

    bool exit = false;
    while(exit == false)
    {
        int choice;
        show_binary(file_binary, size);
        std::cout<<"Wpisz numer bitu do zmiany (lub wpisz -1, żeby wyjsc i zapisac zmiany): ";
        std::cin>>choice;
        std::cout<<std::endl;
        if (choice == -1)
        {
            exit = true;
            continue;
        }
        else {
            file_binary[choice] = !file_binary[choice];
        }


    }
    file.close();
    std::ofstream file_edited;
    file_edited.open(filename);
    for (int i = 0; i < size; i++)
    {
        int binary[8];
        for (int j = 0; j < 8; j++)
        {
            binary[j] = file_binary[8 * i + j];
        }
        decoder->save_letter(binary, filename, file_edited);
    }
    file_edited.close();
}

int main() {

    char choice = 0;
    bool exit = false;
    std::ifstream code, code2;
    std::shared_ptr<Decoder> decoder = std::make_shared<Decoder>();
    do
    {
        if (choice == 0)
        {
            std::cout<<"Wybierz operacje: "<<std::endl;
            std::cout<<"1. Kodowanie"<<std::endl;
            std::cout<<"2. Edycja pliku binarnego"<<std::endl;
            std::cout<<"3. Odkodowanie i korekcja bledow"<<std::endl;
            std::cout<<"4. Wyjscie"<<std::endl;
            std::cin>>choice;
        }


        switch(choice)
        {
            case '1':
            {
                std::string filename;
                std::cout<<"Podaj nazwe pliku do zakodowania: "<<std::endl;
                std::cin>>filename;
                code.open(filename);
                decoder->encode(matrix_H, code, filename + "_zakodowany");
                choice = 0;
                break;
            }
            case '2':
            {
                edit_binary(decoder);
                choice = 0;
                break;
            }
            case '3':
            {
                std::string filename;
                std::cout<<"Podaj nazwe pliku do odkodowania: "<<std::endl;
                std::cin>>filename;
                code2.open(filename, std::ios::binary);
                decoder->decode(matrix_H,code2, filename + "_odkodowany");
                choice = 0;
                code2.close();
                break;
            }
            case '4':
            {
                exit = true;
                break;
            }
            default:
            {
                std::cout<<"Nieprawidlowy znak, wybierz jeszcze raz: "<<std::endl;
                std::cin>>choice;
                break;
            }


        }

    } while(exit == false);

    code.close();

    return 0;
}
