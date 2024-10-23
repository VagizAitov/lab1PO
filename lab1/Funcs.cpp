#include "Header.h"
#include <iostream>
#include <string>

using namespace std;

void addFilm(Film_linear film, std::fstream& add, std::fstream& rows, int& rows_count) {
    cout << "Введите название фильма: ";
    cin >> film.name;
    cout << "Введите бюджет фильма: ";
    cin >> film.budget;
    cout << "Введите цену билета: ";
    cin >> film.price;
    cout << "Введите количество свободных мест: ";
    cin >> film.quantity;
    cout << "Введите возрастное ограничение: ";
    cin >> film.age_limit;
    add.open("bin.bin", ios::out | ios::binary | ios::app);
    add.write((char*)&film, sizeof(Film_linear));
    add.close();
    rows_count++;
    rows.open("rows.bin", ios::out | ios::binary);
    rows.write((char*)&rows_count, sizeof(int));
    rows.close();
}
void readFilms(std::fstream& read, int& rows_count) {
    read.open("bin.bin", ios::in | ios::binary);
    for (int i = 0; i < rows_count; i++) {
        Film_linear temp{};
        read.read(reinterpret_cast<char*>(&temp), sizeof(Film_linear));
        cout << temp.name << " " << temp.budget << " " << temp.price << " " << temp.quantity << " " << temp.age_limit << endl;
    }
    read.close();
}

void findFilmByKey(std::fstream& read, int& rows_count) {
    int s_move;
    cout << "[1] По совпадению с названием\n[2] По интервалу цены билета\n";
    cin >> s_move;
    read.open("bin.bin", ios::in | ios::binary);
    string name;
    string sub_str;
    switch (s_move) {
    default:
        break;
    case 1:
        cout << "Введите строковый атрибут: ";
        cin >> sub_str;
        for (int i = 0; i < rows_count; i++) {
            Film_linear temp{};

            read.read(reinterpret_cast<char*>(&temp), sizeof(Film_linear));
            name = temp.name;
            if (name.find(sub_str) != std::string::npos) {
                cout << temp.name << " " << temp.budget << " " << temp.price << " " << temp.quantity << " " << temp.age_limit << endl;
            }
        }
        read.close();
        break;
    case 2:
        int a, b;

        cout << "Введите первое значение интервала: ";
        cin >> a;
        cout << "Введите второе значение интервала: ";
        cin >> b;


        for (int i = 0; i < rows_count; i++) {
            Film_linear temp{};

            read.read(reinterpret_cast<char*>(&temp), sizeof(Film_linear));
            if ((temp.price >= a) && (temp.price <= b)) {
                cout << temp.name << " " << temp.budget << " " << temp.price << " " << temp.quantity << " " << temp.age_limit << endl;
            }
        }
        read.close();
    }
}