#include<iostream>
#include<string>

using namespace std;

enum Zona {
    CENTRALA = 1,
    PERIFERICA = 2
};

class ServiceAuto {
private:
    const int id;
    Zona zona;
    string denumire;
    int nrMecanici;
    float* salarii;

public:
    static int nrServiceuri;

    ServiceAuto() : id(++nrServiceuri) {
        this->denumire = "Service auto general";
        this->zona = PERIFERICA;
        this->nrMecanici = 0;
        this->salarii = nullptr;
    }

    ServiceAuto(int id, string denumire, int nrMecanici,
        float* salarii, Zona zona) : id(id) {
        nrServiceuri++;

        this->denumire = denumire;
        this->zona = zona;
        this->nrMecanici = nrMecanici;

        this->salarii = new float[nrMecanici];

        for (int i = 0; i < this->nrMecanici; i++) {
            this->salarii[i] = salarii[i];
        }

        delete[] salarii;
    }

    // Constructor de copiere
    ServiceAuto(const ServiceAuto& copie)
        : id(++nrServiceuri) {

        this->denumire = copie.denumire;
        this->zona = copie.zona;
        this->nrMecanici = copie.nrMecanici;

        if (copie.salarii != nullptr) {
            this->salarii = new float[this->nrMecanici];

            for (int i = 0; i < this->nrMecanici; i++) {
                this->salarii[i] = copie.salarii[i];
            }
        }
        else {
            this->salarii = nullptr;
        }
    }

    // Operator de atribuire
    ServiceAuto& operator=(const ServiceAuto& copie) {
        if (this != &copie) {
            this->denumire = copie.denumire;
            this->zona = copie.zona;
            this->nrMecanici = copie.nrMecanici;

            if (this->salarii != nullptr) {
                delete[] this->salarii;
                this->salarii = nullptr;
            }

            if (copie.salarii != nullptr) {
                this->salarii = new float[this->nrMecanici];

                for (int i = 0; i < this->nrMecanici; i++) {
                    this->salarii[i] = copie.salarii[i];
                }
            }
        }

        return *this;
    }

    // Getter si setter pentru nrMecanici
    int getNrMecanici() {
        return this->nrMecanici;
    }

    void setNrMecanici(int valoareNoua) {
        if (valoareNoua >= 0) {
            this->nrMecanici = valoareNoua;
        }
        else {
            throw exception();
        }
    }

    // Getter pentru salarii
    float* getSalarii() {
        float* vSalarii = new float[this->nrMecanici];

        for (int i = 0; i < this->nrMecanici; i++) {
            vSalarii[i] = this->salarii[i];
        }

        return vSalarii;
    }

    // Setter pentru salarii
    void setSalarii(float* vSalarii, int dim) {
        if (dim < 0) {
            throw exception();
        }

        if (dim > 0 && vSalarii == nullptr) {
            throw exception();
        }

        if (this->salarii != nullptr) {
            delete[] this->salarii;
            this->salarii = nullptr;
        }

        this->nrMecanici = dim;

        if (dim > 0) {
            this->salarii = new float[dim];

            for (int i = 0; i < dim; i++) {
                this->salarii[i] = vSalarii[i];
            }
        }
        else {
            this->salarii = nullptr;
        }

        delete[] vSalarii;
    }

    void afisare() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;

        cout << endl << "Zona: ";

        if (this->zona == CENTRALA) {
            cout << "CENTRALA";
        }
        else {
            cout << "PERIFERICA";
        }

        cout << endl << "Nr. mecanici: " << this->nrMecanici;

        if (this->nrMecanici > 0) {
            cout << " cu urmatoarele salarii: ";

            for (int i = 0; i < this->nrMecanici - 1; i++) {
                cout << this->salarii[i] << " lei, ";
            }

            cout << this->salarii[this->nrMecanici - 1] << " lei.";
        }
    }

    bool operator<(const ServiceAuto& s) {
        return this->nrMecanici < s.nrMecanici;
    }

    ~ServiceAuto() {
        cout << endl << "S-a apelat destructorul!";

        if (this->salarii != nullptr) {
            delete[] this->salarii;
        }
    }
};

int ServiceAuto::nrServiceuri = 0;

int main() {
    ServiceAuto serviceGeneral;
    serviceGeneral.afisare();

    float* salarii = new float[] {3500, 4200, 5000};

    ServiceAuto* serviceDacia =
        new ServiceAuto(7, "Service Dacia", 3, salarii, CENTRALA);

    serviceDacia->afisare();

    // Constructor de copiere
    ServiceAuto* serviceTineretului =
        new ServiceAuto(*serviceDacia);

    serviceTineretului->afisare();

    // Operator de atribuire
    serviceGeneral = *serviceTineretului;
    serviceGeneral.afisare();

    ServiceAuto serviceX;
    serviceX = serviceGeneral;
    serviceX.afisare();

    // Testarea setterului
    try {
        serviceX.setNrMecanici(2);
    }
    catch (int cod) {
        cout << endl << cod;
    }
    catch (const char* mesaj) {
        cout << endl << mesaj;
    }
    catch (...) {
        cout << endl << "Numar invalid de mecanici!";
    }

    cout << endl << "Noul numar de mecanici este: "
        << serviceX.getNrMecanici() << endl;

    // Modificarea salariilor
    serviceX.setSalarii(new float[2] {5400, 6200}, 2);

    float* vSalarii = serviceX.getSalarii();

    for (int i = 0; i < serviceX.getNrMecanici(); i++) {
        cout << vSalarii[i] << " lei, ";
    }

    // Compararea service-urilor
    if (serviceX < serviceGeneral) {
        cout << endl
            << "ServiceX are mai putini mecanici decat serviceGeneral!";
    }
    else {
        cout << endl
            << "ServiceGeneral are mai putini mecanici decat serviceX!";
    }

    delete[] vSalarii;

    delete serviceDacia;
    delete serviceTineretului;

    cout << endl << "Numar service-uri: "
        << ServiceAuto::nrServiceuri;

    return 0;
}