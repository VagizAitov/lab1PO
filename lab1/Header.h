#pragma once
#include <fstream>
#include <vector>
#include <string>
struct Film_linear {
    char name[50];
    char budget[30];
    double price;
    int quantity;
    int age_limit;
};
void addFilm(Film_linear film, std::fstream& add, std::fstream& rows, int& rows_count);
void readFilms(std::fstream& read, int& rows_count);
void findFilmByKey(std::fstream& read, int& rows_count);