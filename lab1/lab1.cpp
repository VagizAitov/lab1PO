#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <typeinfo>
#include "Header.h"



using namespace std;

struct Film{
    string name;
    string budget;
    double price;
    int quantity;
    int age_limit;
};

void linear() {
    setlocale(LC_ALL, "ru");
    int f_move;
    cout << "[1] Добавить фильм\n[2] Посмотреть каталог фильмов\n[3] Поиск фильмов по атрибуту\n";
    cin >> f_move;
    int rows_count = 0;
    fstream rows;
    rows.open("rows.bin", ios::in | ios::binary);
    rows.read((char*)&rows_count, sizeof(int));
    rows.close();


    string sub_str;

    fstream add;
    fstream read;
    vector<Film_linear> films(rows_count);

    Film_linear film{};
    switch (f_move) {
    default:
        break;
    case 1:
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
        break;
    case 2:
        read.open("bin.bin", ios::in | ios::binary);
        for (int i = 0; i < rows_count; i++) {
            Film_linear temp{};
            read.read(reinterpret_cast<char*>(&temp), sizeof(Film_linear));
            cout << temp.name << " " << temp.budget << " " << temp.price << " " << temp.quantity << " " << temp.age_limit << endl;
        }
        read.close();
        break;
    case 3:
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
        break;
    }
}

void link() {
    int n_films = 0;

    Film* films = new Film[n_films]{
    };
    fstream bin;
    fstream write;

    Film* films_to_add = new Film[n_films];
    Film* film = new Film;

    int f_move;
    cout << "[1] Добавить фильм\n[2] Посмотреть каталог фильмов\n[3] Поиск фильмов по атрибуту\n";
    cin >> f_move;

    string sub_str;

    switch (f_move)
    {
    default:
        cout << ":(";
        break;
    case 1:
        cout << "Введите название фильма: ";
        cin >> film->name;
        cout << "Введите бюджет фильма: ";
        cin >> film->budget;
        cout << "Введите цену билета: ";
        cin >> film->price;
        cout << "Введите количество свободных мест: ";
        cin >> film->quantity;
        cout << "Введите возрастное ограничение: ";
        cin >> film->age_limit;
        bin.open("bin.bin", std::ios::in | std::ios::binary);
        bin.read((char*)&n_films, sizeof(n_films));
        films = new Film[n_films]{};
        bin.read((char*)films, n_films * sizeof(Film));  // считать набор байтов
        bin.close();

        films_to_add = new Film[n_films + 1]{};
        for (int i = 0; i < n_films; i++) {
            films_to_add[i] = { films[i].name, films[i].budget, films[i].price, films[i].quantity, films[i].age_limit };
        }
        films_to_add[n_films] = { film->name, film->budget, film->price, film->quantity, film->age_limit };
        n_films++;
        write.open("bin.bin", std::ios::out | std::ios::binary);
        write.write((char*)&n_films, sizeof(n_films));        // записать набор байтов
        write.write((char*)films_to_add, n_films * sizeof(Film));  // записать набор байтов
        write.close();
        delete[] films_to_add;
        break;
    case 2:
        bin.open("bin.bin", std::ios::in | std::ios::binary);
        bin.read((char*)&n_films, sizeof(n_films));
        films = new Film[n_films]{};
        bin.read((char*)films, n_films * sizeof(Film));  // считать набор байтов
        bin.close();
        for (int i = 0; i < n_films; i++) {
            cout << films[i].name << " " << films[i].budget << " " << films[i].price << " " << films[i].quantity << " " << films[i].age_limit << endl;
        }

        break;
    case 3:
        int s_move;
        cout << "[1] По совпадению с названием\n[2] По интервалу цены билета\n";
        cin >> s_move;
        switch (s_move)
        {
        default:
            break;
        case 1:
            cout << "Введите строковый атрибут: ";
            cin >> sub_str;
            bin.open("bin.bin", std::ios::in | std::ios::binary);
            bin.read((char*)&n_films, sizeof(n_films));
            films = new Film[n_films]{};
            bin.read((char*)films, n_films * sizeof(Film));  // считать набор байтов
            bin.close();
            cout << "Совпадения:" << endl;
            for (int i = 0; i < n_films; i++) {
                if (films[i].name.find(sub_str) != std::string::npos) {
                    cout << films[i].name << " " << films[i].budget << " " << films[i].price << " " << films[i].quantity << " " << films[i].age_limit << endl;
                }
            }
            break;
        case 2:
            int a, b;

            cout << "Введите первое значение интервала: ";
            cin >> a;
            cout << "Введите второе значение интервала: ";
            cin >> b;
            bin.open("bin.bin", std::ios::in | std::ios::binary);
            bin.read((char*)&n_films, sizeof(n_films));
            films = new Film[n_films]{};
            bin.read((char*)films, n_films * sizeof(Film));  // считать набор байтов
            bin.close();
            for (int i = 0; i < n_films; i++) {
                if ((films[i].price >= a) && (films[i].price <= b)) {
                    cout << films[i].name << " " << films[i].budget << " " << films[i].price << " " << films[i].quantity << " " << films[i].age_limit << endl;
                }
            }
            break;
        }
        break;
    }
}

void func() {
    setlocale(LC_ALL, "ru");
    int f_move;
    cout << "[1] Добавить фильм\n[2] Посмотреть каталог фильмов\n[3] Поиск фильмов по атрибуту\n";
    cin >> f_move;
    int rows_count = 0;
    fstream rows;
    rows.open("rows.bin", ios::in | ios::binary);
    rows.read((char*)&rows_count, sizeof(int));
    rows.close();


    string sub_str;

    fstream add;
    fstream read;
    vector<Film_linear> films(rows_count);

    Film_linear film{};
    switch (f_move) {
    default:
        break;
    case 1:
        addFilm(film, add, rows, rows_count);
        break;
    case 2:
        readFilms(read, rows_count);
        break;
    case 3:
        findFilmByKey(read, rows_count);
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    func();
    return 0;
}