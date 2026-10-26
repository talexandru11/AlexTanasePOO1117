#include<iostream>
#include<string>

using namespace std;

class ServiceAuto {
private:
    const int id;
    string denumire;
    int nrMecanici;
    float* salarii;
public:
    static int nrServiceuri;

    ServiceAuto() : id(++nrServiceuri) {
        this->denumire = "Service auto general";
        this->nrMecanici = 0;
        this->salarii = nullptr;
    }

    ServiceAuto(int id, string denumire, int nrMecanici, float* salarii)
        : id(id) {
        nrServiceuri++;

        this->denumire = denumire;
        this->nrMecanici = nrMecanici;
        this->salarii = new float[nrMecanici];

        for (int i = 0; i < this->nrMecanici; i++) {
            this->salarii[i] = salarii[i];
        }

        delete[] salarii;
    }

    void afisare() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;
        cout << endl << "Nr. mecanici: " << this->nrMecanici;

        if (this->nrMecanici > 0) {
            cout << " cu urmatoarele salarii: ";

            for (int i = 0; i < this->nrMecanici - 1; i++) {
                cout << this->salarii[i] << " lei, ";
            }

            cout << this->salarii[this->nrMecanici - 1] << " lei.";
        }
    }
};

int ServiceAuto::nrServiceuri = 0;

int main() {
    ServiceAuto serviceGeneral;
    serviceGeneral.afisare();

    float* salarii = new float[] {3500, 4200, 5000};

    ServiceAuto* serviceDacia =
        new ServiceAuto(7, "Service Dacia", 3, salarii);

    serviceDacia->afisare();

    delete serviceDacia;

    cout << endl << "Numar service-uri: "
        << ServiceAuto::nrServiceuri;

    return 0;
}