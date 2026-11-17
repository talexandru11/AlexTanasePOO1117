
#include<iostream>
#include<string>

using namespace std;

enum Zona { CENTRALA = 1, PERIFERICA = 2 };

class ServiceAuto {
private:
    const int id;
    Zona zona;
    string denumire;
    float incasariTotale;
    int nrMecanici;
    float* salarii;

public:
    static int nrServiceuri;

    ServiceAuto() : id(++nrServiceuri) {
        this->denumire = "Service auto general";
        this->incasariTotale = 0;
        this->zona = PERIFERICA;
        this->nrMecanici = 0;
        this->salarii = nullptr;
    }

    ServiceAuto(int id, string denumire, float incasariTotale,
        int nrMecanici, float* salarii, Zona zona) : id(id) {

        nrServiceuri++;

        this->denumire = denumire;
        this->incasariTotale = incasariTotale;
        this->zona = zona;
        this->nrMecanici = nrMecanici;

        this->salarii = new float[nrMecanici];

        for (int i = 0; i < this->nrMecanici; i++) {
            this->salarii[i] = salarii[i];
        }

        delete[] salarii;
    }

    // Constructor de copiere
    ServiceAuto(const ServiceAuto& copie) : id(++nrServiceuri) {
        this->denumire = copie.denumire;
        this->nrMecanici = copie.nrMecanici;
        this->incasariTotale = copie.incasariTotale;
        this->zona = copie.zona;

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
            this->nrMecanici = copie.nrMecanici;
            this->incasariTotale = copie.incasariTotale;
            this->zona = copie.zona;

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
            else {
                this->salarii = nullptr;
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

    // Getter si setter pentru salarii
    float* getSalarii() {
        float* vSalarii = new float[this->nrMecanici];

        for (int i = 0; i < this->nrMecanici; i++) {
            vSalarii[i] = this->salarii[i];
        }

        return vSalarii;
    }

    void setSalarii(float* vSalarii, int dim) {
        setNrMecanici(dim);

        if (this->salarii != nullptr) {
            delete[] this->salarii;
            this->salarii = nullptr;
        }

        if (vSalarii != nullptr) {
            this->salarii = new float[this->nrMecanici];

            for (int i = 0; i < this->nrMecanici; i++) {
                this->salarii[i] = vSalarii[i];
            }

            delete[] vSalarii;
        }
        else {
            this->salarii = nullptr;
        }
    }

    // Afisare
    void afisare() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Denumire: " << this->denumire;
        cout << endl << "Incasari totale: " << this->incasariTotale;

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

    // Operator <
    bool operator<(const ServiceAuto& s) {
        return this->nrMecanici < s.nrMecanici;
    }

    // Destructor
    ~ServiceAuto() {
        cout << endl << "S-a apelat destructorul!";

        if (this->salarii != nullptr) {
            delete[] this->salarii;
        }
    }

    // Operator +=
    void operator+=(float incasariDeAdaugat) {
        this->incasariTotale += incasariDeAdaugat;
    }

    // Operator negatie !
    bool operator!() {
        return this->incasariTotale <= 0;
    }

    // Operator functie ()
    float operator()(float valoareDeAdaugat) {
        return this->incasariTotale + valoareDeAdaugat;
    }

    // Operator index []
    float& operator[](int index) {
        if (index >= 0 && index < this->nrMecanici) {
            return this->salarii[index];
        }
        else {
            throw exception();
        }
    }

    // Operator << / afisare
    friend ostream& operator<<(ostream& out, const ServiceAuto& s) {
        out << endl << "Operator de afisare: ";
        out << endl << "Id: " << s.id;
        out << endl << "Denumire: " << s.denumire;
        out << endl << "Incasari totale: " << s.incasariTotale;

        out << endl << "Zona: ";

        if (s.zona == CENTRALA) out << "CENTRALA";
        if (s.zona == PERIFERICA) out << "PERIFERICA";

        out << endl << "Nr. mecanici: " << s.nrMecanici;

        if (s.salarii != nullptr && s.nrMecanici > 0) {
            out << endl << "Salarii: ";

            for (int i = 0; i < s.nrMecanici - 1; i++) {
                out << s.salarii[i] << " lei, ";
            }

            out << s.salarii[s.nrMecanici - 1] << " lei.";
        }

        return out;
    }

    // Operator >> / citire
    friend istream& operator>>(istream& in, ServiceAuto& s);

    // Postincrementare ob++
    ServiceAuto operator++(int) {
        ServiceAuto copie = *this;
        this->incasariTotale++;

        return copie;
    }

    // Preincrementare ++ob
    ServiceAuto operator++() {
        this->incasariTotale++;

        return *this;
    }

    // Cast explicit
    explicit operator int() {
        return this->nrMecanici;
    }
};

// Operator >> definit in afara clasei
istream& operator>>(istream& in, ServiceAuto& s) {
    cout << endl << "Incasari totale: ";
    in >> s.incasariTotale;

    cout << endl << "Denumire: ";
    in >> s.denumire;

    cout << endl << "Zona: ";
    int zona;
    in >> zona;

    if (zona == 1) s.zona = CENTRALA;
    if (zona == 2) s.zona = PERIFERICA;

    cout << endl << "Nr. mecanici: ";
    in >> s.nrMecanici;

    if (s.nrMecanici < 0) {
        throw exception();
    }

    if (s.salarii != nullptr) {
        delete[] s.salarii;
        s.salarii = nullptr;
    }

    if (s.nrMecanici > 0) {
        s.salarii = new float[s.nrMecanici];

        cout << endl << "Salarii: ";

        for (int i = 0; i < s.nrMecanici; i++) {
            cout << endl << "salarii[" << i << "]: ";
            in >> s.salarii[i];
        }
    }

    return in;
}

int ServiceAuto::nrServiceuri = 0;

int main() {

    ServiceAuto serviceGeneral;

    // Operator negatie
    if (!serviceGeneral) {
        cout << endl << "Service-ul nu are incasari!";
    }
    else {
        cout << endl << "Service-ul are incasari!";
    }

    // Operator functie
    cout << endl << serviceGeneral(100);

    // Operator <<
    cout << serviceGeneral;

    float* salarii = new float[3] {3500, 4200, 5000};

    ServiceAuto* serviceDacia =
        new ServiceAuto(7, "Service_Dacia", 97000, 3, salarii, CENTRALA);

    // Operator +=
    (*serviceDacia) += 100;

    // Operator <
    if (serviceGeneral < *serviceDacia) {
        cout << endl << "Service-ul general are mai putini mecanici decat Service Dacia!";
    }
    else {
        cout << endl << "Service Dacia are mai putini mecanici decat service-ul general!";
    }

    // Operator []
    (*serviceDacia)[0] = 4000;

    cout << endl << (*serviceDacia)[0];

    // Operator <<
    cout << *serviceDacia;

    // Operator >>
    // ServiceAuto serviceUnirii;
    // cin >> serviceUnirii;
    // cout << serviceUnirii;

    // Postincrementare
    ServiceAuto service1 = serviceGeneral++;

    cout << service1;
    cout << serviceGeneral;

    // Preincrementare
    ServiceAuto service2 = ++serviceGeneral;

    cout << service2;
    cout << serviceGeneral;

    // Cast explicit
    cout << endl << "Cast service -> int: "
        << int(*serviceDacia);

    // Constructor de copiere
    ServiceAuto* serviceTineretului =
        new ServiceAuto(*serviceDacia);

    cout << *serviceTineretului;

    // Operator de atribuire
    serviceGeneral = *serviceTineretului;

    cout << serviceGeneral;

    // Getter si setter
    try {
        serviceGeneral.setNrMecanici(2);
    }
    catch (...) {
        cout << endl << "Numar invalid de mecanici!";
    }

    serviceGeneral.setSalarii(new float[2] {5400, 6200}, 2);

    float* vSalarii = serviceGeneral.getSalarii();

    for (int i = 0; i < serviceGeneral.getNrMecanici(); i++) {
        cout << endl << vSalarii[i] << " lei";
    }

    delete[] vSalarii;

    delete serviceDacia;
    delete serviceTineretului;

    cout << endl << "Numar service-uri: "
        << ServiceAuto::nrServiceuri;

    return 0;
}
