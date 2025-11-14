#include <iostream>
#include <Windows.h>
#include <ctime>
#include <iomanip>
#include <string>



// ------------------------------------------- Учетные записи --------------------------------------------------
size_t userSize = 2;
std::string userStatus[3]{ "Супер администратор", "Администратор", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "admin","user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[0] };
std::string currentStatus = statusArr[0];

//  -------------------------------------------------- Склад  --------------------------------------------------
size_t storageSize = 0;
bool staticStorageCreated = false;


int* idArr;
std::string* nameArr;
unsigned int* countArr;
double* priceArr;



// Функции склада
void CreateStorage();
void ShowStorage(int mode = 0);
void AddStorageItem();
void RemoveStorageItem();
void CgangePrice();
template<typename T>
void SwapArr(T* Arr, T* Arr2, size_t SizeArr);
void ChangeStorage();
void AddNewItem();

// Служебные функции
void Start();
bool Login();
void ShowSuperAdminMenu();
inline void Getline(std::string& str);
inline void Err(int time = 1500);
void Error()
{
    std::cout << "Некорректный ввод\n";
    std::cout << "Введенные данные не являются числом\n\n";
    Sleep(1500);

}

//  -------------------------------------------------- main  ----------------------------------------------------
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    Start();

    // Освобождение памяти
    delete[] loginArr;
    delete[] passArr;
    delete[] statusArr;

    if (staticStorageCreated)
    {
        delete[] idArr;
        delete[] nameArr;
        delete[] countArr;
        delete[] priceArr;
    }

    return 0;
}

//  -------------------------------------------------- СЛУЖЕБНЫЕ ФУНКЦИИ  -------------------------------------------
void Start()
{
    std::string choose;

    std::cout << "\n\n\n\t\t\tПРОДУКТОВЫЙ МАГАЗИН\n\n\n";

    if (Login())
    {
        if (currentStatus == userStatus[0])
        {
            while (true)
            {
                std::cout << "Выберите склад\n1 - Готовый\n2 - создать новый\nВвод - ";
                Getline(choose);

                if (choose == "1")
                {
                    CreateStorage();
                    system("cls");
                    ShowSuperAdminMenu();

                    /*
                     ShowStorage();
                    */
                    break;
                }
                else if (choose == "2")
                {
                    break;
                }
                else
                {
                    Err();
                }
            }
        }
        else if (currentStatus == userStatus[1])
        {
            CreateStorage();
        }
        else if (currentStatus == userStatus[2])
        {
            CreateStorage();
        }
    }
    else
    {
        system("cls");
        std::cout << "Завершение работы магазина\n\n";
    }
}

bool Login()
{
    std::string login, pass;

    while (true)
    {
        std::cout << "Введите логин - ";
        Getline(login);
        std::cout << "Введите пароль - ";
        Getline(pass);

        if (login == "exit" && pass == "exit")
        {
            currentStatus = "";
            return false;
        }

        if (login == loginArr[0] && pass == passArr[0])
        {
            std::cout << "Пользователь - " << loginArr[0] << "\n\nДобро пожаловать!\n";
            std::cout << "Ваш статус - " << statusArr[0] << "\n\n";
            currentStatus = statusArr[0];
            return true;
        }

        for (size_t i = 0; i < userSize; i++)
        {
            if (login == loginArr[i] && pass == passArr[i])
            {
                std::cout << "Пользватель - " << loginArr[i] << "\n\nДобро пожаловать!\n";
                std::cout << "Ваш статус - " << statusArr[i] << "\n\n";
                currentStatus = statusArr[i];
                return true;
            }
        }

        Err();
    }
}

void ShowSuperAdminMenu()
{
    std::string choose;

    while (true)
    {
        system("cls");
        std::cout << "1 - Начать продажу\n";
        std::cout << "2 - Показать склад\n";
        std::cout << "3 - Пополнить склад\n";
        std::cout << "4 - Списать товар\n";
        std::cout << "5 - Изменить цену\n";
        std::cout << "6 - Редактировать склад\n";
        std::cout << "7 - Редактировать персонал\n";
        std::cout << "8 - Отчёт о прибыли\n";
        std::cout << "0 - Закрыть магазин\n";
        std::cout << "Ввод: ";
        Getline(choose);
        if (choose == "1")
        {

        }
        else if (choose == "2")
        {
            ShowStorage();

        }
        else if (choose == "3")
        {
            AddStorageItem();

        }
        else if (choose == "4")
        {
            RemoveStorageItem();

        }
        else if (choose == "5")
        {
            CgangePrice();

        }
        else if (choose == "6")
        {
            ChangeStorage();
        }
        else if (choose == "7")
        {

        }
        else if (choose == "8")
        {

        }
        else if (choose == "0")
        {
            break;

        }
        else
        {
            Err();
        }
    }


}

//  -------------------------------------------------- ФУНКЦИИ СКЛАДА  ---------------------------------------

bool IsNumber(const std::string& str)
{
    if (str.size() <= 0 || str.size() >= 10)
    {
        Error();
        return false;
    }
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!std::isdigit(str[i]))
        {
            Error();
            return false;
        }

    }


    return true;
}




void CreateStorage()
{
    const int staticSize = 10;

    int id[staticSize]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    std::string name[staticSize]
    {
        "Яблоки",
        "Мясо",
        "Вода",
        "Рис",
        "Гречка",
        "Бананы",
        "Специи",
        "Хлеб",
        "Мука",
        "Томаты"
    };

    unsigned int count[staticSize]{ 32, 54, 213, 65, 23, 88, 433, 42, 66, 100 };
    double price[staticSize]{ 120.0, 400.0, 75.0, 88.0, 90.0, 123.0, 54.0, 70.5, 87.0, 143.4 };

    storageSize = staticSize;

    idArr = new int[storageSize];
    nameArr = new std::string[storageSize];
    countArr = new unsigned int[storageSize];
    priceArr = new double[storageSize];

    staticStorageCreated = true;

    SwapArr(idArr, id, storageSize);
    SwapArr(priceArr, price, storageSize);
    SwapArr(countArr, count, storageSize);
    SwapArr(nameArr, name, storageSize);
}

void ShowStorage(int mode)
{
    system("cls");
    if (mode == 0)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Цена\t\t" << "Кол-во\n";

        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i]
                << "\t" << priceArr[i] << " Рублей" << "\t" << countArr[i] << "\n";
        }
        system("pause");
        system("cls");

    }
    else if (mode == 1)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Кол-во\n";

        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i]
                << "\t" << countArr[i] << "\n";
        }
    }
    else if (mode == 2)
    {
        std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t"
            << "Цена\n";

        for (size_t i = 0; i < storageSize; i++)
        {
            std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i]
                << "\t" << priceArr[i] << " Рублей\n";
        }
    }
    else
    {
        std::cout << "StorageMode Error\n\n";
        std::invalid_argument("StorageMode Error");
    }
}

void AddStorageItem()
{
    std::string chooseId, chooseCount, choose;
    int id = 0;
    unsigned int count = 0;
    while (true)
    {
        system("cls");
        ShowStorage(1);
        std::cout << "\nВведите ID товара или \"exit\" для выхода - ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Отмена операции пополнения\n";
            Sleep(1500);
            system("cls");
            break;

        }
        std::cout << "Введите кол-во товара для пополнения - ";
        Getline(chooseCount);
        if (IsNumber(chooseId) && IsNumber(chooseCount))
        {

            id = std::stoi(chooseId) - 1;
            count = std::stoi(chooseCount);

            if (id < 0 || id > storageSize - 1 || count < 0 || count > 199)
            {
                std::cout << "Некоррекстный ID или кол-во\nМаксимальное кол-во 199\n";
                Sleep(1500);
            }
            else
            {
                std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << countArr[id] << " --> " << countArr[id] + count << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод - ";
                Getline(choose);
                if (choose == "1")
                {
                    countArr[id] += count;
                    std::cout << "Товар успешно пополнен\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }
                else if (choose == "2")
                {
                    std::cout << "Отмена пополнения товара\n";
                    Sleep(1500);
                }
                else
                {
                    Err();
                }

            }


        }

    }
}

void AddNewItem()
{
    std::string newName, newPrice, newCount, choose;
    double price = 0.0;
    unsigned int count = 0;
    bool exit = true;
    while (true)
    {
        while (true)
        {
            system("cls");
            std::cout << "\tДобавление нового товара!\n\nВведите\"exit\" для прекращения операции\n\n";
            std::cout << "Введите название нового товара: ";
            Getline(newName);
            if (newName == "exit")
            {
                std::cout << "Операция добавления товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }
            if (newName.size() <= 0 || newName.size() >= 60)
            {
                std::cout << "Ошибка имени. Максимальная длина 60 символов";
            }
            else
            {
                break;
            }
        }

        while (exit)
        {
            system("cls");
            std::cout << "\tДобавление нового товара!\n\nВведите\"exit\" для прекращения операции\n\n";
            std::cout << "Введите кол-во нового товара: ";
            Getline(newCount);
            if (newCount == "exit")
            {
                std::cout << "Операция добавления товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }
            if (IsNumber(newCount))
            {
                count = std::stoi(newCount);
                if (count > 199)
                {
                    std::cout << "Ошибка максимального размера товара. Не более 199 ед.\n";
                    Sleep(1500);
                }
                else
                {
                    break;
                }
            }
        }

        while (exit)
        {
            system("cls");
            std::cout << "\tДобавление нового товара!\n\nВведите\"exit\" для прекращения операции\n\n";
            std::cout << "Введите цену нового товара: ";
            Getline(newPrice);
            if (newPrice == "exit")
            {
                std::cout << "Операция добавления товара прервана!\n\n";
                Sleep(1500);
                exit = false;
                break;
            }
            if (IsNumber(newPrice))
            {
                count = std::stod(newPrice);
                if (price > 3000)
                {
                    std::cout << "Ошибка высокая цена.\n";
                    Sleep(1500);
                }
                else
                {
                    break;
                }
            }

        }
        system("pause");

        while (exit)
        {
            std::cout << "Новый товар: " << newName << "\n";
            std::cout << "Кол-во: " << count << "\n";
            std::cout << "Цена: " << price << "\n\n";
            std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
            Getline(choose);
            if (choose == "1")
            {
                storageSize++;
                int* idArrTemp = new[storageSize];
                std::string* nameArrTemp = new std::string[storageSize];
                unsigned int* countArrTemp = new unsigned[storageSize];
                double* priceArrTemp = new double[storageSize];


                SwapArr(idArrTemp, idArr, storageSize - 1);
                SwapArr(nameArrTemp, nameArr, storageSize - 1);
                SwapArr(countArrTemp, countArr, storageSize - 1);
                SwapArr(priceArrTemp, priceArr, storageSize - 1);

                idArrTemp[storageSize - 1] = storageSize;
                nameArrTemp[storageSize - 1] = newName;
                countArrTemp[storageSize - 1] = count;
                priceArrTemp[storageSize - 1] = price;

                std::swap(idArr, idArrTemp);
                std::swap(nameArr, nameArrTemp);
                std::swap(countArr, countArrTemp);
                std::swap(priceArr, priceArrTemp);

                delete[]idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
                std::cout << "Идёт подготовка... ";
                Sleep(2000);
                std::cout << "Товар успешно добавлен!\n\n";
                Sleep(1500);
                // закончили 
            }
            else if (choose == "2")
            {
                std::cout << "Отмена\n\n";
                Sleep(1500);
            }
            else
            {
                Err();
            }
        }




        if (exit == false)
        {
            break;
        }
    }
}


void ChangeStorage()
{
    std::string choose;
    while (true)
    {
        std::cout << "1 - Добавить новый товар\n";
        std::cout << "2 - Изменить имя товара\n";
        std::cout << "3 - Удалить товар\n";
        std::cout << "0 - Выйти из редактора\n";
        std::cout << "Ввод: ";
        Getline(choose);
        if (choose == "1")
        {
            AddNewItem();
        }
        else if (choose == "2")
        {

        }
        else if (choose == "3")
        {

        }
        else if (choose == "0")
        {

        }
        else
        {

        }
    }
}
void RemoveStorageItem()
{
    std::string chooseId, chooseCount, choose;
    int id = 0;
    unsigned int count = 0;
    while (true)
    {
        system("cls");
        ShowStorage(1);
        std::cout << "\nВведите ID товара или \"exit\" для выхода - ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Отмена операции списания товара\n";
            Sleep(1500);
            break;
        }
        std::cout << "Введите кол-во товара для списания - ";
        Getline(chooseCount);
        if (IsNumber(chooseId) && IsNumber(chooseCount))
        {
            id = std::stoi(chooseId) - 1;
            count = std::stoi(chooseCount);
            if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
            {
                std::cout << "Некоррекстный ID или кол-во\n";
                Sleep(1500);

            }
            else
            {
                std::cout << std::left << std::setw(25) << nameArr[id] <<
                    "\t" << countArr[id] << " --> " << countArr[id] - count << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод - ";
                Getline(choose);

                if (choose == "1")
                {
                    countArr[id] -= count;
                    std::cout << "Товар успешно списан\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }
                else if (choose == "2")
                {
                    std::cout << "Отмена списания товара\n";
                    Sleep(1500);
                }
                else
                {
                    Err();
                }
            }
        }
    }
}

void CgangePrice()
{
    std::string chooseId, newPrice, choose;
    int id = 0;
    double price = 0.0;
    while (true)
    {
        system("cls");
        ShowStorage(2);
        std::cout << "\nВведите ID товара или \"exit\" для выхода - ";
        Getline(chooseId);
        if (chooseId == "exit")
        {
            std::cout << "Отмена операции изменения цены\n";
            Sleep(1500);
            break;
        }
        std::cout << "Введите новую цену товара - ";
        Getline(newPrice);
        if (IsNumber(chooseId) && IsNumber(newPrice))
        {
            id = std::stoi(chooseId) - 1;
            price = std::stoi(newPrice);
            if (id < 0 || id > storageSize - 1 || price < 0.0 || price > 99999.9)
            {
                std::cout << "Некоррекстный ID или кол-в\nМаксимальный ценник 99999.9\n";
                Sleep(1500);
            }
            else
            {
                std::cout << std::left << std::setw(25) << nameArr[id] <<
                    "\t" << priceArr[id] << " --> " << price << "\n\n";
                std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод - ";
                Getline(choose);

                if (choose == "1")
                {
                    priceArr[id] = price;
                    std::cout << "Цена успешно изменена\n\n";
                    Sleep(1500);
                    system("cls");
                    break;
                }
                else if (choose == "2")
                {
                    std::cout << "Отмена изменения цены\n";
                    Sleep(1500);
                }
                else
                {
                    Err();
                }
            }
        }
    }
}



// -------------------------------------------------- ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ  --------------------------------------

template<typename T>
void SwapArr(T* Arr, T* Arr2, size_t SizeArr)
{
    for (size_t i = 0; i < SizeArr; i++)
    {
        Arr[i] = Arr2[i];
    }
}

inline void Getline(std::string& str)
{

    std::getline(std::cin, str, '\n');

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(365000, '\n');
    }
}

inline void Err(int time)
{
    std::cout << "Некорректный ввод\n";
    Sleep(1500);
    system("cls");
}