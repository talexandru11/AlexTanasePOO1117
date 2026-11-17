
#include<iostream>
#include<string>
#include<exception>

using namespace std;

// Exceptie personalizata
class ExceptieCustom : public exception {
private:
    string mesaj;

public:
    ExceptieCustom(const char* mesaj) : mesaj(mesaj) {}

    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

// Interfata
class IService {
public:
    virtual float calculareCost(float valoare) = 0;
    virtual bool areProgramareDisponibila() = 0;

    virtual ~IService() {}
};

// Clasa abstracta
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
    static const float SALARIU_MINIM;

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

        if (nrMecanici < 0) {
            throw ExceptieCustom("Numar invalid de mecanici!");
        }

        for (int i = 0; i < nrMecanici; i++) {
            if (salarii[i] < SALARIU_MINIM) {
                throw ExceptieCustom("Salariul este prea mic!");
            }
        }

        this->denumire = denumire;
        this->incasariTotale = incasariTotale;
        this->zona = zona;
        this->nrMecanici = nrMecanici;

        if (nrMecanici > 0) {
            this->salarii = new float[nrMecanici];

            for (int i = 0; i < nrMecanici; i++) {
                this->salarii[i] = salarii[i];
            }
        }
        else {
            this->salarii = nullptr;
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
            throw ExceptieCustom("Numar negativ de mecanici!");
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
            throw ExceptieCustom("Dimensiune invalida!");
        }

        for (int i = 0; i < dim; i++) {
            if (vSalarii[i] < SALARIU_MINIM) {
                throw ExceptieCustom("Salariul este prea mic!");
            }
        }

        if (this->salarii != nullptr) {
            delete[] this->salarii;
            this->salarii = nullptr;
        }

        this->nrMecanici = dim;

        if (dim > 0 && vSalarii != nullptr) {
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

    // Functie virtuala
    virtual void afisare() {
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

    // Functie virtuala pura
    virtual float getProcentReducere() = 0;

    // Operator <
    bool operator<(const ServiceAuto& s) {
        return this->nrMecanici < s.nrMecanici;
    }

    // Operator +=
    void operator+=(float incasariDeAdaugat) {
        this->incasariTotale += incasariDeAdaugat;
    }

    // Operator !
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
            throw ExceptieCustom("Index invalid!");
        }
    }

    // Operator <<
    friend ostream& operator<<(ostream& out, const ServiceAuto& s) {
        out << endl << "Operator de afisare:";
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

    // Operator >>
    friend istream& operator>>(istream& in, ServiceAuto& s);

    // Postincrementare
    float operator++(int) {
        float copie = this->incasariTotale;
        this->incasariTotale++;

        return copie;
    }

    // Preincrementare
    float operator++() {
        this->incasariTotale++;

        return this->incasariTotale;
    }

    // Cast explicit
    explicit operator int() {
        return this->nrMecanici;
    }

    // Destructor virtual
    virtual ~ServiceAuto() {
        cout << endl << "Destructor ServiceAuto!";

        if (this->salarii != nullptr) {
            delete[] this->salarii;
        }
    }
};

// Definire membri statici
int ServiceAuto::nrServiceuri = 0;
const float ServiceAuto::SALARIU_MINIM = 1000;

// Operator >> definit in afara clasei
istream& operator>>(istream& in, ServiceAuto& s) {
    cout << endl << "Incasari totale: ";
    in >> s.incasariTotale;

    cout << endl << "Denumire: ";
    in >> s.denumire;

    cout << endl << "Zona: ";
    int zona;
    in >> zona;

    if (zona == 1) {
        s.zona = CENTRALA;
    }
    else if (zona == 2) {
        s.zona = PERIFERICA;
    }
    else {
        throw ExceptieCustom("Zona invalida!");
    }

    cout << endl << "Nr. mecanici: ";
    in >> s.nrMecanici;

    if (s.nrMecanici < 0) {
        throw ExceptieCustom("Numar invalid de mecanici!");
    }

    if (s.salarii != nullptr) {
        delete[] s.salarii;
        s.salarii = nullptr;
    }

    if (s.nrMecanici > 0) {
        s.salarii = new float[s.nrMecanici];

        for (int i = 0; i < s.nrMecanici; i++) {
            cout << endl << "salarii[" << i << "]: ";
            in >> s.salarii[i];

            if (s.salarii[i] < ServiceAuto::SALARIU_MINIM) {
                throw ExceptieCustom("Salariul este prea mic!");
            }
        }
    }

    return in;
}

// Clasa derivata 1
class ServiceAutoAutorizat : public ServiceAuto, public IService {
private:
    float procentReducere;
    bool programareDisponibila;

public:
    ServiceAutoAutorizat() : ServiceAuto(), procentReducere(10),
        programareDisponibila(true) {
    }

    ServiceAutoAutorizat(int id, string denumire, float incasari,
        int nrMecanici, float* salarii, Zona zona,
        float procentReducere, bool programare)
        : ServiceAuto(id, denumire, incasari, nrMecanici, salarii, zona) {

        this->procentReducere = procentReducere;
        this->programareDisponibila = programare;
    }

    void afisare() override {
        ServiceAuto::afisare();

        cout << endl << "Tip: Service autorizat";
        cout << endl << "Procent reducere: " << this->procentReducere;
    }

    float getProcentReducere() override {
        return this->procentReducere;
    }

    // Implementarea interfetei
    float calculareCost(float valoare) override {
        return valoare - valoare * this->procentReducere / 100;
    }

    bool areProgramareDisponibila() override {
        return this->programareDisponibila;
    }
};

// Clasa derivata 2
class ServiceAutoIndependent : public ServiceAuto, public IService {
private:
    float procentReducere;
    bool programareDisponibila;

public:
    ServiceAutoIndependent() : ServiceAuto(), procentReducere(5),
        programareDisponibila(false) {
    }

    ServiceAutoIndependent(int id, string denumire, float incasari,
        int nrMecanici, float* salarii, Zona zona,
        float procentReducere, bool programare)
        : ServiceAuto(id, denumire, incasari, nrMecanici, salarii, zona) {

        this->procentReducere = procentReducere;
        this->programareDisponibila = programare;
    }

    void afisare() override {
        ServiceAuto::afisare();

        cout << endl << "Tip: Service independent";
        cout << endl << "Procent reducere: " << this->procentReducere;
    }

    float getProcentReducere() override {
        return this->procentReducere;
    }

    // Implementarea interfetei
    float calculareCost(float valoare) override {
        return valoare - valoare * this->procentReducere / 100;
    }

    bool areProgramareDisponibila() override {
        return this->programareDisponibila;
    }
};

int main() {

    try {

        // Creare obiecte prin clase derivate
        ServiceAuto* service[3];

        service[0] = new ServiceAutoAutorizat(
            1, "Service_Dacia", 97000, 3,
            new float[3] {3500, 4200, 5000},
            CENTRALA, 15, true
        );

        service[1] = new ServiceAutoIndependent(
            2, "Service_BMW", 85000, 2,
            new float[2] {4000, 5500},
            PERIFERICA, 5, false
        );

        service[2] = new ServiceAutoAutorizat(
            3, "Service_Auto", 120000, 2,
            new float[2] {4500, 6000},
            CENTRALA, 20, true
        );

        // Polimorfism
        for (int i = 0; i < 3; i++) {
            service[i]->afisare();

            cout << endl << "Reducere: "
                << service[i]->getProcentReducere() << "%";
        }

        // Interfata
        IService* operation = dynamic_cast<IService*>(service[0]);

        cout << endl << "Cost dupa reducere: "
            << operation->calculareCost(1000);

        cout << endl << "Programare disponibila: "
            << operation->areProgramareDisponibila();

        // Operator +=
        (*service[0]) += 500;

        // Operator []
        (*service[0])[0] = 4500;

        // Operator <<
        cout << *service[0];

        // Operator !
        if (!(*service[1])) {
            cout << endl << "Service-ul nu are incasari!";
        }

        // Operator functie ()
        cout << endl << "Incasari + 100: "
            << (*service[0])(100);

        // Operator <
        if (*service[0] < *service[1]) {
            cout << endl << "Primul service are mai putini mecanici!";
        }

        // Postincrementare
        float valoareVeche = (*service[0])++;

        cout << endl << "Valoare veche: " << valoareVeche;

        // Preincrementare
        float valoareNoua = ++(*service[0]);

        cout << endl << "Valoare noua: " << valoareNoua;

        // Cast explicit
        cout << endl << "Numar mecanici: "
            << int(*service[0]);

        // Exceptie personalizata
        try {
            service[0]->setNrMecanici(-2);
        }
        catch (ExceptieCustom& e) {
            cout << endl << "Eroare: " << e.what();
        }

        // Eliberare memorie
        for (int i = 0; i < 3; i++) {
            delete service[i];
        }

        cout << endl << "Numar service-uri create: "
            << ServiceAuto::nrServiceuri;

    }
    catch (ExceptieCustom& e) {
        cout << endl << "Exceptie: " << e.what();
    }

    return 0;
}
