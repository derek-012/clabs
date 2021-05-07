#include <iostream>
#include <windows.h>
#include <io.h>
#include <fstream>

using namespace std;

struct Human {
    char name[60];
    int birthyear;
    int height;
    int weight;
    bool gender;
};

// Проверка на число
bool is_number(string str) {
    int size = str.length();
    if (size == 0)
        return false;

    for (int i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }

    return true;
}

// Функция для получения ответа да/нет
bool get_answer() {
    char c;
    do {
        cin >> c;
        cin.ignore();
        if (c == 'Y' || c == 'y')
            return true;

        if (c == 'N' || c == 'n')
            return false;

        printf("Ответ некорректный, повторите попытку (Y - да, N - нет): ");
    } while (true);
}

// Функция для получения int
int get_int() {
    string c;
    int result;
    do {
        cin >> c;
        cin.ignore();

        if (is_number(c)) {
            result = stoi(c);
            return result;
        }

        printf("Введенное значение не является числом, повторите попытку: ");
    } while (true);
}

// Функция получения года
int get_year() {
    int year;
    do {
        year = get_int();
        if (year > 1950 && year <= 2021)
            return year;
        cout << "Введенные данные не являются годом, повторите попытку: ";
    } while (true);
}

// Функция получения пола
bool get_gender() {
    char c;
    do {
        cin >> c;
        cin.ignore();
        if (c == 'M' || c == 'm')
            return false;

        if (c == 'F' || c == 'f')
            return true;

        printf("Ответ некорректный, повторите попытку (M - мужской, F - женский): ");
    } while (true);
}





string DIRNAME = R"(L:\projects\CLionProjects\CLabs\Lab6\lab6_2\data\)";
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

ofstream get_stream_append(char* filename) {
    ofstream outfile(filename, ios::binary | ios::app);
    cout << outfile.is_open() << endl;
    return outfile;
}

size_t get_count_data(ifstream* infile) {
    int temp = infile->tellg();
    infile->seekg(0, ios_base::end);
    int pos = infile->tellg();
    infile->seekg(temp, ios::beg);
    return pos / sizeof(Human);
}

Human* get_list(ifstream* infile) {

    int size = get_count_data(infile);
    if (size == 0)
        return nullptr;

    Human* list = new Human[size];

    for (int i = 0; i < size; i++) {
        if (infile->read((char*) &list[i], sizeof(Human)).eof())
            break;
    }

    return list;
}


Human* new_human() {
    //const string line = "------------------------------";
    auto *h = new Human;
    string name;
    cout << "Ввод данных о человеке:" << endl;
    cout << "Имя: ";         std::getline(cin, name); name.copy(h->name, name.length()); h->name[name.length()] = '\0';
    cout << "Год рождения: ";  h->birthyear = get_year();
    cout << "Рост: ";        h->height = get_int();
    cout << "Вес: ";         h->weight = get_int();
    cout << "Пол: ";         h->gender = get_gender();

    return h;
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

void printHuman(Human human) {
    printf("%s:\n\tГод рождения: %d\n\tРост: %dcm\n\tВес: %dkg\n\tПол: %s\n",
           human.name, human.birthyear, human.height, human.weight, (human.gender == 0) ? "мужской" : "женский");
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

void exerciseA(Human* people, int list_size, int weight, int beginyear, int endyear) {
    printf("Задание A: люди с весом более %d, и годом рождения между %d и %d:\n",
           weight, beginyear, endyear);
    int count = 0;
    for(int i = 0; i < list_size; i++) {
        if (people[i].weight > weight && people[i].birthyear >= beginyear && people[i].birthyear <= endyear) {
            printHuman(people[i]);
            printf("\n");
            count++;
        }
    }
    if (count == 0)
        printf("Отсутствуют");
}

void exerciseB(Human* people, int list_size, int height) {
    printf("Задание B: женщины с ростом %d:\n", height);
    int count = 0;
    for(int i = 0; i < list_size; i++) {
        if (people[i].gender == 1 && people[i].height == height) {
            printHuman(people[i]);
            printf("\n");
            count++;
        }
    }
    if (count == 0)
        printf("Отсутствуют");
}

void exerciseC(Human* people, int list_size) {
    printf("Задание C: информация о людях в алфавитном порядке:\n");

    int l[4] = {0, 1, 2, 3};
    int t;
    for(int i = 0; i < list_size; i++) {
        for (int j = list_size - 1; j > i; j--) {
            if (strcmp(people[l[j]].name, people[l[j - 1]].name) < 0) {
                t = l[j];
                l[j] = l[j-1];
                l[j-1] = t;
            }
        }
    }

    for (int i : l) {
        printHuman(people[i]);
        printf("\n");
    }
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