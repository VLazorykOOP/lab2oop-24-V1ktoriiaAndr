#include <iostream>
using namespace std;
#include "Tasks.h"
#include "Examples.h"
#include <bitset>
void MenuTask()
{
    cout << "     Menu Task   \n";
    cout << "    1.  Calculation of expressions using bitwise operations  \n";
    cout << "    2.  Data encryption using bitwise operations \n";
    cout << "    3.  Data encryption using structures with bit fields \n";
    cout << "    4.  The problem of using bitwise operations \n";
    cout << "    5.  Examples of problems using bitwise operations \n";
    cout << "    6.  Exit \n";
}

int calculateParityBit8(int byte) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (byte & (1 << i)) count++;
    }
    return (count % 2 == 0) ? 0 : 1;
}

// Підрахунок парності для наступних полів (6 біт)
int calculateParityBit6(int byte) {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (byte & (1 << i)) count++;
    }
    return (count % 2 == 0) ? 0 : 1;
}

void task1() {
    // Обчислення виразів з використанням побітових операцій
    // Calculation of expressions using bitwise operations 
    cout << " Calculation of expressions using bitwise operations  \n";
    int a, b, c, d;
    cout << "Enter values for a, b, c, d:" << '\n';
    cin >> a >> b >> c >> d;
    int bitexpression = ((b << 11) + b)  // b * 2049
        + (((d << 4) - d)  // d * 15
        + ((a << 3) + (a << 2)) >> 11)  // (a * 12) / 2048
        - ((c << 6) + ((c << 5) + (c << 2)))  // c * 100
        + ((d << 6) + (d << 5) + (d << 3)); // d * 104

    int expression = 2049 * b + ((d * 15 + 12 * a) / 2048) - c * 100 + d * 104;

    cout << "First task :" << endl;
    cout << "By bit: " << bitexpression << endl;
    cout << "Arithmetic: " << expression << endl;
    
    cout << "Press Enter to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищення буфера
    cin.get(); // Очікування Enter перед поверненням
}

void task2()
{
    // Шифрування даних з використання побітових операцій 
    // Data encryption using bitwise operations
    cout << " Data encryption using bitwise operations  \n";
    string Text[16];

    // Введення тексту по рядках
    for (int i = 0; i < 16; i++) {
        cout << "Enter text row number " << i + 1 << " (4 characters): ";
        cin >> Text[i];

        // Перевірка довжини
        while (Text[i].length() != 4) {
            cout << "Incorrect number of characters! Must be exactly 4. Try again: ";
            cin >> Text[i];
        }

        // Доповнюємо до 16 символів пробілами
        Text[i].resize(16, ' ');
    }


    int Encoded[16][16];


    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            char ch = Text[i][j];
            int ascii = (int)ch;

            int rowNumber = i & 0xF;             // 4 біти (рядок символу)
            int asciiHigh = (ascii >> 4) & 0xF;  // 4 біти (старша частина ASCII)

            int firstField = (rowNumber) | (asciiHigh << 4);
            int parity8 = calculateParityBit8(firstField);  // 8-й біт парності перших полів

            int asciiLow = ascii & 0xF;          // 4 біти (молодша частина ASCII)
            int positionInRow = j & 0x3;         // 2 біти (позиція символу в рядку)
            int secondField = (asciiLow) | (positionInRow << 4);

            int parity6 = calculateParityBit6(secondField); // 6-й біт парності наступних полів

            // Збираємо повністю 16-бітове число
            int encoded = 0;
            encoded |= firstField;           // біти 0-7
            encoded |= (parity8 << 8);       // біт 8
            encoded |= (secondField << 9);   // біти 9-14
            encoded |= (parity6 << 15);      // біт 15

            // Зберігаємо
            Encoded[i][j] = encoded;
        }
    }

    // Вивід результату
    cout << "\nCiphered Text (binary):\n";
    for (int i = 0; i < 16; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < 16; j++) {
            cout << bitset<16>(Encoded[i][j]) << " "; // Вивід у двійковому форматі
        }
        cout << endl;
    }

    cout << "Press Enter to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищення буфера
    cin.get(); // Очікування Enter перед поверненням
}

struct EncodedSymbol {
    unsigned short rowNumber : 4;   // 4 біти – номер рядка
    unsigned short asciiHigh : 4;   // 4 біти – старші 4 біти ASCII
    unsigned short parity8 : 1;     // 1 біт – біт парності перших двох полів
    unsigned short asciiLow : 4;    // 4 біти – молодші 4 біти ASCII
    unsigned short position : 2;    // 2 біти – позиція символу в рядку
    unsigned short parity6 : 1;     // 1 біт – біт парності останніх двох полів
};

// Об’єднання для збереження зашифрованого символу
union EncodedData {
    EncodedSymbol symbol; // Доступ до структури
    unsigned short value; // Доступ до 16-бітного представлення
};

void task3()
{
    // Шифрування даних з використання стуктур з бітовими полями 
    // Data encryption using structures with bit fields
    cout << "  Data encryption using structures with bit fields \n";
    string Text[16];

    // Введення тексту по рядках
    for (int i = 0; i < 16; i++) {
        cout << "Enter text row number " << i + 1 << " (4 characters): ";
        cin >> Text[i];

        // Перевірка довжини
        while (Text[i].length() != 4) {
            cout << "Incorrect number of characters! Must be exactly 4. Try again: ";
            cin >> Text[i];
        }

        // Доповнюємо до 16 символів пробілами
        Text[i].resize(16, ' ');
    }

    EncodedData Encoded[16][16]; // Масив для збереження закодованих значень нового типу(об'єднання)

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            char ch = Text[i][j];
            int ascii = (int)ch;

            // Заповнюємо структуру
            Encoded[i][j].symbol.rowNumber = i & 0xF;  // 4 біти – номер рядка
            Encoded[i][j].symbol.asciiHigh = (ascii >> 4) & 0xF; // 4 біти – старша частина ASCII
            int firstField = (Encoded[i][j].symbol.rowNumber) | (Encoded[i][j].symbol.asciiHigh << 4);
            Encoded[i][j].symbol.parity8 = calculateParityBit8(firstField); // 8-й біт парності

            Encoded[i][j].symbol.asciiLow = ascii & 0xF; // 4 біти – молодша частина ASCII
            Encoded[i][j].symbol.position = j & 0x3; // 2 біти – позиція символу в рядку
            int secondField = (Encoded[i][j].symbol.asciiLow) | (Encoded[i][j].symbol.position << 4);
            Encoded[i][j].symbol.parity6 = calculateParityBit6(secondField); // 15-й біт парності
        }
    }

    cout << "\nCiphered Text (binary):\n";
    for (int i = 0; i < 16; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < 16; j++) {
            cout << bitset<16>(Encoded[i][j].value) << " "; // Вивід у двійковому форматі
        }
        cout << endl;
    }

    cout << "Press Enter to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищення буфера
    cin.get(); // Очікування Enter перед поверненням
}

// Функція для перевірки контрольних бітів
bool verify_word(uint16_t word) {
    int bit_14 = (word >> 14) & 1; // Отримуємо 14-й біт (контрольна сума для непарних бітів)
    int bit_15 = (word >> 15) & 1; // Отримуємо 15-й біт (контрольна сума для парних бітів)

    int odd_bits_xor = 0, even_bits_xor = 0;

    // Перебираємо перші 14 бітів слова (0-13) і розраховуємо контрольні біти
    for (int i = 0; i < 14; i++) {
        // Біт i вважається непарним, якщо його індекс i % 2 == 0
        ((i % 2 == 1) ? even_bits_xor : odd_bits_xor) ^= (word >> i) & 1;
    }

    // Перевіряємо, чи збігаються контрольні біти з розрахованими
    if (bit_14 != odd_bits_xor || bit_15 != even_bits_xor) {
        cout << "Error in a word: " << bitset<16>(word) << endl;
        return false;
    }
    return true;
}

void task4()
{   // Задача із використання побітових операцій
    // The problem of using bitwise operations
    cout << " Data encryption using structures with bit fields \n";
    uint16_t word;
    cout << "Enter 16-bit word (10 or 16 numeric system): ";
    cin >> word;

    // Вивід введеного слова у двійковому та шістнадцятковому вигляді
    cout << "Entered word: " << bitset<16>(word) << " (" << hex << word << "h)" << endl;

    // Перевіряємо слово на помилки
    if (verify_word(word)) {
        cout << "No errors in transferring." << endl;
    }
    else {
        cout << "Error in transferring!" << endl;
    }
   
    cout << "Press Enter to return to the menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищення буфера
    cin.get(); // Очікування Enter перед поверненням
}


