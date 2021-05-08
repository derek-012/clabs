#include <iostream>
#include <windows.h>
#include <fstream>
#include "is_number.h"
#include "get_functions.h"
#include "human.h"

using namespace std;



string DIRNAME = R"(L:\projects\CLionProjects\CLabs\Lab7\lab7_2\data\)";
string FILENAME;
bool ACTIVE_FILE = false;


bool FileExists(const char *fname)
{
    return::GetFileAttributes(fname) != DWORD(-1);
}

bool file_is_open() {
    return ACTIVE_FILE;
}

void select_file(string filename) {
    FILENAME = std::move(filename);
    ACTIVE_FILE = true;
}

void unselect_file() {
    ACTIVE_FILE = false;
}

string get_filename() {
    return file_is_open() ? DIRNAME + FILENAME : string(nullptr);
}

void create_file() {
    cout << "Введите имя файла: ";
    string temp_name;
    cin >> temp_name;
    string temp_path = DIRNAME + temp_name;
    cout << "Полный путь: " << temp_path << endl;
    if (FileExists(temp_path.data())) {
        cout << "Файл уже существует. Перезаписать? (Y - да, N - нет): ";
        if (get_answer()) {
            select_file(temp_name);
        }
    } else {
        select_file(temp_name);
    }

    if (file_is_open()) {
        ofstream outfile(temp_name, ios::binary);
        outfile.write("", 0);
        outfile.close();
    }
}

void open_file() {
    cout << "Введите имя файла: ";
    string temp_name;
    cin >> temp_name;
    string temp_path = DIRNAME + temp_name;
    if (FileExists(temp_path.data())) {
        select_file(temp_name);
        cout << "Файл " << temp_name << " выбран!" << endl;
    } else {
        cout << "Файл не найден!" << endl;
    }
}

void delete_file(char* filename) {
    if (FileExists(filename)) {
        cout << "Подтвердите удаление (Y - да, N - нет): ";
        if (get_answer()) {
            if (remove(filename) == 0) {
                unselect_file();
                cout << "Файл удачно удален!" << endl;
            }
        }
    } else {
        cout << "Файл не найден!" << endl;
    }
}

void addOne() {
    string filename = get_filename();
    if (filename.data() == nullptr) {
        cout << "Сначала создайте или откройте файл!" << endl;
        return;
    }

    Human *h = new_human();
    ofstream outfile = get_stream_append((char*)filename.data());
    outfile.write((char *) h, sizeof(Human));
    outfile.close();
}

void addSome() {
    string filename = get_filename();
    if (filename.data() == nullptr) {
        cout << "Сначала создайте или откройте файл!" << endl;
        return;
    }
    const string line = "------------------------------";
    cout << "Сколько записей ввести?: ";
    int count = get_int();

    if (count == 0) return;

    ofstream outfile = get_stream_append((char*)filename.data());
    for (int i = 0; i < count; i++) {
        cout << "Запись №" << i << ":\n\n";
        outfile.write((char *) new_human(), sizeof(Human));
        cout << "\n" << line << endl;
    }

    outfile.close();
}

void deleteOne() {
    string filename = get_filename();
    if (filename.data() == nullptr) {
        cout << "Сначала создайте или откройте файл!" << endl;
        return;
    }
    ifstream infile(filename, ios::binary);
    int size = get_count_data(&infile);
    if (size == 0) {
        cout << "Файл пустой." << endl;
        return;
    }
    cout << "Всего записей: " << size << ". Введите индекс записи которую надо удалить: ";
    int index;
    do {
        index = get_int();
        if (index >= size || index < 0)
            cout << "Введенный индекс отсутствует, введите корректные данные: ";
        else
            break;
    } while (true);
    cout << "Out of loop" << endl;
    Human list[size - 1];
    for (int i = 0; i < size; i++) {
        if (infile.read((char*) &list[i], sizeof(Human)).eof())
            break;
        if (i == index) {
            i--;
            index = -1;
        }
    }
    infile.close();

    ofstream outfile(filename, ios::binary);
    outfile.write((char*) &list, sizeof(Human) * size - 1);
    outfile.close();
    cout << "Запись удалена!" << endl;
}

void deleteSome() {
    string filename = get_filename();
    if (filename.data() == nullptr) {
        cout << "Сначала создайте или откройте файл!" << endl;
        return;
    }
    ifstream infile(filename, ios::binary);
    int size = get_count_data(&infile);
    if (size == 0) {
        cout << "Файл пустой." << endl;
        return;
    }

    Human list[size - 1];
    for (int i = 0; i < size; i++) {
        if (infile.read((char*) &list[i], sizeof(Human)).eof())
            break;
    }
    infile.close();

    cout << "Всего записей: " << size << ". Сколько записей надо удалить: ";
    int count;
    do {
        count = get_int();
        if (count < 0 || count > size) {
            cout << "Значение меньше нуля либо больше имеющегося количества записей. Повторите попытку: ";
        } else {
            break;
        }
    } while (true);

    if (count == 0) {
        return;
    }

    ofstream outfile(filename, ios::binary);

    if (count == size) {
        outfile.write(nullptr, 1);
        cout << "Все записи удалены!" << endl;
    } else {
        int index;
        bool list_map[size];
        for (int i = 0; i < size; i++)
            list_map[i] = true;
        for (int i = 0; i < count; i++) {
            cout << "Индекс записи №" << i << ": ";
            do {
                index = get_int();
                if (index >= size || index < 0) {
                    cout << "Некорректный индекс. Повторите попытку: ";
                } else {
                    list_map[index] = false;
                    break;
                }
            } while(true);
        }
        for (int i = 0; i < size; i++) {
            if (list_map[i])
                outfile.write((char*) &list[i], sizeof(Human));
        }
        cout << "Выбранные записи удалены!" << endl;
    }

    outfile.close();
}

void show() {
    string filename = get_filename();
    if (filename.data() == nullptr) {
        cout << "Сначала создайте или откройте файл!" << endl;
        return;
    }
    ifstream infile(filename, ios::binary);
    int size = get_count_data(&infile);
    if (size == 0) {

    }
    Human h;

    while (!infile.read((char*) &h, sizeof (Human)).eof()) {
        printHuman(h);
    }
    infile.close();
}



void showWithParam() {
    string filename = get_filename();
    if (filename.data() == nullptr) {
        cout << "Сначала создайте или откройте файл!" << endl;
        return;
    }

    ifstream infile(filename, ios::binary);
    int size = get_count_data(&infile);
    cout << "Size: " << size << endl;
    Human *list = get_list(&infile);
    int weight, beginyear, endyear;
    cout << "Задание А. Введите критерии:\n\tВес: ";
    weight = get_int();
    cout << "\tНачальный год рождения: ";
    beginyear = get_year();
    cout << "\tКонечный год рождения: ";
    endyear = get_year();
    cout << endl;
    exerciseA(list, size, weight, beginyear, endyear);
    cout << endl << endl;
    int height;
    cout << "Задание B. Введите критерии:\n\tРост: ";
    height = get_int();
    cout << endl;
    exerciseB(list, size, height);
    cout << endl << endl;
    exerciseC(list, size);
    infile.close();
}

void deleteFile() {
    string filename = get_filename();
    if (filename.data() == nullptr) {
        cout << "Сначала создайте или откройте файл!" << endl;
        return;
    }

    delete_file((char*)filename.data());
}

void menu() {
    char c;
    do {
        system("cls");

        if (ACTIVE_FILE) {
            cout << "Текущий файл: " << FILENAME << endl << endl;
        }

        printf("Меню:\n"
               "\t1 - Создать файл\n"
               "\t2 - Открыть файл\n"
               "\t3 - Добавить запись\n"
               "\t4 - Добавить несколько записей\n"
               "\t5 - Удалить запись\n"
               "\t6 - Удалить несколько записей\n"
               "\t7 - Вывести содержимое файла\n"
               "\t8 - Вывести содержание файла по критериям\n"
               "\t9 - Удалить файл\n"
               "\t0 - Выйти из программы\n"
               "\n"
               "Выберите пункт меню: ");

        cin >> c;
        cin.ignore();

        switch (c) {
            case '1':
                create_file(); break;
            case '2':
                open_file(); break;
            case '3':
                addOne(); break;
            case '4':
                addSome(); break;
            case '5':
                deleteOne(); break;
            case '6':
                deleteSome(); break;
            case '7':
                show(); break;
            case '8':
                showWithParam(); break;
            case '9':
                deleteFile(); break;
            case '0':
                printf("Выход из программы...\n"); break;
            default:
                printf("Введенное значение является неверным. Повторите попытку.\n");
        }
        printf("Для продолжения нажмите Enter...");
        getchar();
    } while (c != '0');
}

int main() {
    SetConsoleOutputCP( 65001 );
    menu();
    return 0;
}