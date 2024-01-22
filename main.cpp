#include <iostream>
#include <random>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <cctype>
#include <vector>


class Settings {
public:

   virtual void ForPrint() = 0;

    virtual void ForEncode() = 0;

    virtual void ForDecode() = 0;

    virtual ~Settings() {};

};


class CaesarCode : public Settings {
public:
    char forMessage[10000];
    char forChar;
    int choose = 0;
    int key = 0, i = 0;
  

    virtual void ForPrint() {

        //тут он сливает пояснения в одно целое, 
        //поэтому просто надо вводить их по очереди
        printf("Enter a message to fix it: ");
        gets_s(forMessage);
        printf("Enter key: ");
        scanf_s("%d", &key);
    }
    virtual void ForEncode() {

        ForPrint();

        for (i = 0; forMessage[i] != '\0'; ++i) {
            forChar = forMessage[i];
            if (forChar >= 'a' && forChar <= 'z') {
                forChar = forChar + key;
                if (forChar > 'z') {
                    forChar = forChar - 'z' + 'a' - 1;
                }
                forMessage[i] = forChar;
            }
            else if (forChar >= 'A' && forChar <= 'Z') {
                forChar = forChar + key;
                if (forChar > 'Z') {
                    forChar = forChar - 'Z' + 'A' - 1;
                }
                forMessage[i] = forChar;
            }
        }
        printf("Full message: %s", forMessage);
    }
    virtual void ForDecode() {

        ForPrint();

        for (i = 0; forMessage[i] != '\0'; ++i) {
            forChar = forMessage[i];
            if (forChar >= 'a' && forChar <= 'z') {
                forChar = forChar - key;
                if (forChar < 'a') {
                    forChar = forChar + 'z' - 'a' + 1;
                }
                forMessage[i] = forChar;
            }
            else if (forChar >= 'A' && forChar <= 'Z') {
                forChar = forChar - key;
                if (forChar < 'A') {
                    forChar = forChar + 'Z' - 'A' + 1;
                }
                forMessage[i] = forChar;
            }
        }
        printf("Full message: %s", forMessage);
    }
};

class VigenereCode : public Settings {
public:
   
    
    std::string alphabeth = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string forText, key;
    int i = 0, xNum = 0;
    char codeWord; //для зашифрованного слова
    

    int FindCode(char codeWord) {
        for (int i = 0; i < alphabeth.length(); i++)
        {
            if (codeWord == alphabeth[i]) {
                 return i;
            }
        }
        return 0;
    }

    virtual void ForPrint() {

        //вводить без пробелов
        printf("Enter a message: ");
        std::cin >> forText;

        printf("Enter key: ");
        std::cin >> key;

        //перевод в верхний регистр
        for (auto& c : forText)
        {
            c = toupper(c);
        }
        for (auto& c : key)
        {
            c = toupper(c);
        }
    }

    virtual void ForEncode() {
        ForPrint();
        std::string codeWord;
        std::cout << "Full message: ";
        for (int i = 0; i < forText.length(); i++)
        {
           codeWord+= alphabeth[(FindCode(forText[i]) +
                FindCode(key[i % key.length()])) % alphabeth.length()];
           
        }
        std::cout << codeWord;
    }

    virtual void ForDecode() {
        ForPrint();
        std::string codeWord;
        std::cout << "Full message: ";
        for (int i = 0; i < forText.length(); i++)
        {
            codeWord += alphabeth[(FindCode(forText[i]) -
                FindCode(key[i % key.length()]) + alphabeth.length()) % alphabeth.length()];
        }
        std::cout << codeWord;
    }


};

class AthenaCode : public Settings {
public:
    std::string alphabeth = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int key = 0, multKey = 0, invMultKey = 0;
    std::string forText;

    int findCode(char codeWord) {
        for (int i = 0; i < alphabeth.length(); i++)
        {
            if (codeWord == alphabeth[i]) {
                return i;
            }
        }
        return 0;
    }

    virtual void ForEncode() {

        ForPrint();

        for (int i = 0; i < forText.length(); i++)
        {
            std::cout.width(3); //для красивого вывода
            std::cout << alphabeth[(findCode(forText[i]) * multKey + key) % alphabeth.length()] ;

        }
    }

    virtual void ForDecode() {

        ForPrint();

        for (int i = 0; i < forText.length(); i++)
        {
            std::cout.width(3); //для красивого вывода
            std::cout << alphabeth[((findCode(forText[i]) - key + alphabeth.length()) * invMultKey) % alphabeth.length()];

        }
    }

    virtual void ForPrint() {

        //вводить без пробелов
        printf("Enter a message to encrypt: ");
        std::cin >> forText;

        for (auto& c : forText)
        {
            c = toupper(c);
        }

        //для ключа
        printf("Enter key: ");
        scanf_s("%d", &key);
        if (key % alphabeth.length() == 0) {
            printf("error!");
            exit(0);
        }
        if (key < 0) {
            key = key % alphabeth.length();
        }
        std::cout << forText << "\n";
        std::cout << key;

        //мульти-ключ
        bool check = true;
        while (check)
        {
            printf("\nEnter multy-key: ");
            scanf_s("%d", &multKey);

            if (multKey < 0 || multKey > alphabeth.length()) {
                multKey = multKey % alphabeth.length();
            }

            for (int i = 0; i < alphabeth.length(); i++)
            {
                if (multKey * i % alphabeth.length() == 1) {
                    invMultKey = i;
                    std::cout << "Инверсия ключа: " << invMultKey << std::endl;
                    check = false;
                    break;
                }
            }
            if (check == true) {
                printf("Try another key");
            }
        }

    }
    
};

void Menu() {

    int chooseIt = 0;
    std::vector <Settings*> code;

    std::cout << "Choose the type: \n" <<
        "1 - CaesarCode, 2 - VigenereCode, 3 - AthenaCode\n";
    std::cin >> chooseIt;
    std::cout << std::endl;

    switch (chooseIt)
    {
    case 1:
    {
        code.push_back(new CaesarCode);

        for (auto& el : code)
        {
            printf("\t\t\tCAESAR CODE\n");
            printf("encode:\n");
            el->ForPrint();
            el->ForEncode();
            std::cout << std::endl;
            printf("decode:\n");
            el->ForPrint();
            el->ForDecode();
            std::cout << std::endl;
        }
        break;
    }
    case 2:
    {
        code.push_back(new VigenereCode);

        for (auto& el : code)
        {
            printf("\t\t\tVIGENERE CODE\n");
            printf("encode:\n");
            el->ForEncode();
            std::cout << std::endl;
            printf("decode:\n");
            el->ForDecode();
            std::cout << std::endl;
        }
        break;
    }
    case 3:
    {
        code.push_back(new AthenaCode);

        for (auto& el : code)
        {
            printf("\t\t\tАФИННЫЙ ШИФР\n");

            printf("encode:\n");
            el->ForEncode();
            std::cout << std::endl;
            printf("decode:\n");
            el->ForDecode();
            std::cout << std::endl;
        }

        break;
    }
    default:
    {
        printf("Smt is incorrect!");
        break;
    }
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));

  
    Menu();




    return 0;
}

