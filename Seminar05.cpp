#include<iostream>
#include<string>  
#include <fstream>

using namespace std;

class ExceptieCustom : public exception
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj) {}
};

class Producator {
private:
	string nume;
	string tara;

public:
	Producator(string nume = "N/A", string tara = "RO") : nume(nume), tara(tara) {}

	string getNume() const
	{
		return this->nume;
	}

	string getTara() const
	{
		return this->tara;
	}

	void setNume(string nume)
	{
		this->nume = nume;
	}

	void setTara(string tara)
	{
		this->tara = tara;
	}
};

class Produs {
protected:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() :id(0), denumire("Laptop"), pret(5000) {}

	Produs(int idP, string denumireP, float pretP) :id(idP), denumire(denumireP), pret(pretP) {
		if (pret < PRET_MINIM) {
			throw ExceptieCustom("Pretul este prea mic!");
		}
	}

	virtual void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;
	}

	~Produs() {}

	virtual float getProcentReducere() = 0;
};

const float Produs::PRET_MINIM = 1;

class ProdusRedus : public Produs {
private:
	float procentReducere;
	Producator producator;

public:
	ProdusRedus() : Produs(), procentReducere(10), producator() {}

	ProdusRedus(int id, string denumire, float pret, float procentReducere, string numeProducator, string taraProducator)
		: Produs(id, denumire, pret), procentReducere(procentReducere), producator(numeProducator, taraProducator) {
	}

	void afisare() override {
		this->Produs::afisare();
		cout << endl << "Procent reducere: " << this->procentReducere;
		cout << endl << "Nume producator: " << this->producator.getNume();
		cout << endl << "Tara producator: " << this->producator.getTara();
	}

	float getProcentReducere() {
		return this->procentReducere;
	}

	ProdusRedus& operator=(const ProdusRedus& altul)
	{
		if (this != &altul)
		{
			this->denumire = altul.denumire;
			this->pret = altul.pret;
			this->procentReducere = altul.procentReducere;
			this->producator.setNume(altul.producator.getNume());
			this->producator.setTara(altul.producator.getTara());
		}
		return *this;
	}

	friend ofstream& operator<<(ofstream& fout, const ProdusRedus& pr)
	{
		fout << pr.id << " " << pr.denumire << " " << pr.pret
			<< " " << pr.procentReducere << " " << pr.producator.getNume()
			<< " " << pr.producator.getTara() << endl;

		return fout;
	}

	friend ifstream& operator>>(ifstream& fin, ProdusRedus& pr)
	{
		int id;
		string denumire;
		float pret;
		float procentReducere;
		string numeProducator;
		string taraProducator;

		if (fin >> id >> denumire >> pret >> procentReducere >> numeProducator >> taraProducator)
		{
			ProdusRedus copieProdusRedus(id, denumire, pret, procentReducere, numeProducator, taraProducator);
			pr = copieProdusRedus;
		}
		return fin;
	}
};

template<typename T, typename Q>
class MathInterface {
public:
	virtual T adunare(T a, Q b) = 0;
	virtual T scadere(T a, T b) = 0;
	virtual T inmultire(T a, T b) = 0;
	virtual T impartire(T a, T b) = 0;
};

template<typename T, typename Q>
class MathOperation : public MathInterface<T, Q> {
public:
	T adunare(T a, Q b) {
		return a + b;
	}

	T scadere(T a, T b) {
		return a - b;
	}

	T inmultire(T a, T b) {
		return a * b;
	}

	T impartire(T a, T b) {
		if (b != 0) {
			return a / b;
		}
		throw ExceptieCustom("Nu putem avea impartire la 0!");
	}
};

int main() {
	ProdusRedus p1(1, "Paine", 2, 10, "PaineCo", "Romania");
	ProdusRedus p2(2, "Peste", 15, 8, "PesteCo", "Japonia");
	ProdusRedus p3(3, "Portocale", 10, 12, "PortocaleCo", "Grecia");

	ofstream fout("produse.txt");
	if (!fout.is_open())
	{
		throw ExceptieCustom("Nu s-a putut deschide fisierul pentru scriere.");
	}
	fout << p1 << p2 << p3;
	fout.close();

	ifstream fin("produse.txt");
	if (!fin.is_open()) {
		throw ExceptieCustom("Nu s-a putut deschide fisierul pentru citire.");
	}

	ProdusRedus produsCitit;
	cout << endl << endl << "Citite din fisier:";
	while (fin >> produsCitit) {
		produsCitit.afisare();
		cout << endl;
	}
	fin.close();

	MathInterface<int, int>* operationInt = new MathOperation<int, int>();
	cout << endl << operationInt->adunare(1, 2);
	delete operationInt;

	MathInterface<double, double>* operationDouble = new MathOperation<double, double>();
	cout << endl << operationDouble->inmultire(1.50, 4.50);
	delete operationDouble;

	MathInterface<double, int>* operationDoubleInt = new MathOperation<double, int>();
	cout << endl << operationDoubleInt->adunare(1.52, 2);
	delete operationDoubleInt;

	return 0;
}