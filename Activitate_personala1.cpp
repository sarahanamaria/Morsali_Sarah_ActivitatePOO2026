#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Produs {
private:
    static int numarProduse;
    const int idProdus;
    char* denumire;
    double pretCurent;

public:
    // Constructor fara parametri
    Produs() : idProdus(++numarProduse) {
        this->denumire = new char[strlen("Necunoscut") + 1];
        strcpy(this->denumire, "Necunoscut");
        this->pretCurent = 0;
    }

    // Constructor cu parametri
    Produs(const char* denumire, double pretCurent)
        : idProdus(++numarProduse) {

        // Validari
        if (denumire != nullptr && strlen(denumire) > 0) {
            this->denumire = new char[strlen(denumire) + 1];
            strcpy(this->denumire, denumire);
        }
        else {
            this->denumire = new char[strlen("Necunoscut") + 1];
            strcpy(this->denumire, "Necunoscut");
        }

        if (pretCurent >= 0) {
            this->pretCurent = pretCurent;
        }
        else {
            this->pretCurent = 0;
        }
    }

    // Destructor: eliberam memoria obiectului
    ~Produs() {
        delete[] this->denumire;
    }

    // Constructor de copiere: obiect nou, cu ID nou
    Produs(const Produs& p) : idProdus(++numarProduse) {
        this->denumire = new char[strlen(p.denumire) + 1];
        strcpy(this->denumire, p.denumire);
        this->pretCurent = p.pretCurent;
    }

    // Operator =: modificam un obiect care exista deja
    Produs& operator=(const Produs& p) {
        // Evitam stergerea propriei surse la p1 = p1
        if (this != &p) {
            // Facem copia inainte sa stergem memoria veche
            char* copie = new char[strlen(p.denumire) + 1];
            strcpy(copie, p.denumire);

            delete[] this->denumire;
            this->denumire = copie;
            this->pretCurent = p.pretCurent;
            // ID-ul ramane neschimbat
        }
        return *this;
    }

    // friend permite accesul la atributele private
    friend ostream& operator<<(ostream& out, const Produs& p) {
        out << "ID: " << p.idProdus
            << " | Denumire: " << p.denumire
            << " | Pret: " << p.pretCurent << " lei";
        return out;
    }
};

int Produs::numarProduse = 0;

int main() {
    // Testam constructorul fara parametri
    Produs p1;
    cout << "Fara parametri: " << p1 << endl;

    // Testam constructorul cu parametri
    Produs p2("Laptop", 3500);
    cout << "Cu parametri: " << p2 << endl;

    // Testam denumirea nula si pretul negativ
    Produs p3(nullptr, -10);
    cout << "Valori invalide: " << p3 << endl;

    // Testam denumirea goala
    Produs p4("", 20);
    cout << "Denumire goala: " << p4 << endl;

    // Obiect nou: constructor de copiere
    Produs p5(p2);
    cout << "Copie: " << p5 << endl;

    // Obiect existent: operator =
    p1 = p2;
    cout << "Dupa atribuire: " << p1 << endl;

    // Testam autoatribuirea
    p1 = p1;
    cout << "Dupa autoatribuire: " << p1 << endl;

    // Modificam sursa pentru a verifica independenta copiilor
    Produs p6("Mouse", 100);
    p2 = p6;

    cout << "Sursa modificata: " << p2 << endl;
    cout << "Copia ramane Laptop: " << p5 << endl;
    cout << "Produsul atribuit ramane Laptop: " << p1 << endl;

    // Destructorii se apeleaza automat la iesirea din main
    return 0;
}