// Hotelli Harjoitustehtävä
// Joonas Akers


#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>
#include<ctype.h>
#include<limits>
#include<random>
using namespace std;

//prototyypit
int randn(int minimi, int maksimi);
int hintalasku(int tyyppi, int yöt, int alennus);


int main() {
    // kirjaimet
    setlocale(LC_ALL, "FI_fi");

    //Muuttujat ja valmistelut
    fstream infile;
    string line;
    vector<string> lines;
    string vaihtoehto; //mitä haluat tehdä ohjelmalla
    int huoneMäärä; //hotellin honeiden kokonaismäärä
    int huoneMäärä1hh; //jäljellä olevia yhden henkilön huoneet
    int huoneMäärä2hh; //jäljellä olevia kahden henkilön huoneet
    int randNum = 0; //satunnaisluvun hetkellinen tallennus paikka
    vector<bool> varausNumerot(100000, 0); //lista käytetyistä varausnumeroista
    string varausKonfirm; //varauksen varmistus onko oikein vai ei
    string uusiVaraus; //vastaus kysymykseen halutko varata toinen huone
    string off; //haluatko sulje ohjelma

    //varauksen profiili
    struct varaus {
        string nimi; //varaajan nimi
        int huoneNumero; //varatun huoneen numero
        int huoneTyyppi; //varatun huoneen tyyppi (1hh tai 2hh)
        int alennus; //mahdollinen alennus
        int yöt; //kuinka monta yötä on varattu
        int varausNumero; //varauksen numero
        int hinta; //varauksen kokonais hinta

        //tulostaa varauksen tiedot
        void näytäVaraus() {
            cout << "Nimi: " << nimi << endl;
            cout << "Huone Tyyppi: " << huoneTyyppi << endl;
            cout << "Huone Numero: " << huoneNumero << endl;
            cout << "Öitä: " << yöt << endl;
            cout << "Alennusprosentti: " << alennus << "%" << endl;
            cout << "Hinta: " << hinta << endl;
            cout << "Varausnumero: " << varausNumero << endl;
        }
    };

    vector<varaus> varaukset; //lista kaikista varatuista huoneista

    //Hae olemassa olevia hotellivaraukset (jos on)
    infile.open("varaukset.txt", fstream::in);
    if (infile.is_open())
    {
        while (getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();
    }
    else {
        //tekee uusi hotelli jos ei löydä tallennettu hotelli
        cout << "Ei olemassa olevia varauksia, luodaan hotelli..." << endl;
        randNum = randn(20, 131);
        huoneMäärä = randNum * 2;
        huoneMäärä1hh = randNum;
        huoneMäärä2hh = huoneMäärä1hh;
        cout << "Huoneiden määrä: " << huoneMäärä << endl << "1hh: " << huoneMäärä1hh << endl << "2hh: " << huoneMäärä2hh << endl;
    }

    //vectorit jolla tarkistetaan onko tietty huone varattu
    vector<bool> varattu1hh(huoneMäärä1hh + 1, 0); 
    vector<bool> varattu2hh(huoneMäärä2hh + 1, 0);  

    for (int k = 0; k < 1; k++) {
        cout << "Mitä haluat tehdä? " << endl << "V = Varaa Huone. " << endl << "S = Sulje Ohjelma. ";
        cin >> vaihtoehto;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (vaihtoehto == "v" || vaihtoehto == "V" || vaihtoehto == "varaa" || vaihtoehto == "Varaa" || vaihtoehto == "VARAA" || vaihtoehto == "varaa huone" || vaihtoehto == "Varaa huone" || vaihtoehto == "Varaa Huone" || vaihtoehto == "VARAA HUONE") {
            //Varaa huone
            for (int j = 0; j < 1; j++) {
                varaus tempVaraus;//hetkellinen varaus

                cout << "Mikä teidän nimenne on? ";
                getline(cin, tempVaraus.nimi);

                cout << "Haluaisitko yhden hengen huone (1) tai kahden hengen huone (2)? ";
                cin >> tempVaraus.huoneTyyppi;

                for (int i = 0; i < 1; i++) {
                    cout << "Mikä huonenumero haluaisitte? ";
                    cin >> tempVaraus.huoneNumero;
                    if (tempVaraus.huoneTyyppi == 1 && varattu1hh[tempVaraus.huoneNumero] == 1) {
                        cout << "Huone on Varattu, valitse toinen huone";
                        i--;
                    }
                    if (tempVaraus.huoneTyyppi == 2 && varattu2hh[tempVaraus.huoneNumero] == 1) {
                        cout << "Huone on Varattu, valitse toinen huone";
                        i--;
                    }
                }

                //arpoo alennus
                randNum = randn(0, 2);
                tempVaraus.alennus = randNum * 10;

                cout << "Kuinka monta yötä olette täällä? ";
                cin >> tempVaraus.yöt;

                //arpoo varausnumero
                for (int i = 0; i < 1; i++) {
                    randNum = randn(10000, 100000);
                    if (varausNumerot[randNum] == true) {
                        i--;
                    }
                }
                tempVaraus.varausNumero = randNum;

                //laskee hinta
                tempVaraus.hinta = hintalasku(tempVaraus.huoneTyyppi, tempVaraus.yöt, tempVaraus.alennus);

                //varmista onko haluatko tallentaa varaus (vimeinen hetki tarkistaa onko kirjoitettu oikein
                tempVaraus.näytäVaraus();
                cout << "Konfirmoi varaus (y/n)? ";
                cin >> varausKonfirm;
                if (varausKonfirm == "y" || varausKonfirm == "Y" || varausKonfirm == "yes" || varausKonfirm == "Yes" || varausKonfirm == "YES" || varausKonfirm == "k" || varausKonfirm == "K" || varausKonfirm == "kyllä" || varausKonfirm == "Kyllä" || varausKonfirm == "KYLLÄ" || varausKonfirm == "kylla" || varausKonfirm == "Kylla" || varausKonfirm == "KYLLA") {
                    varaukset.push_back(tempVaraus);
                    if (tempVaraus.huoneTyyppi == 1) {
                        varattu1hh[tempVaraus.huoneNumero] = 1;
                        huoneMäärä1hh--;
                    }
                    if (tempVaraus.huoneTyyppi == 2) {
                        varattu2hh[tempVaraus.huoneNumero] = 1;
                        huoneMäärä2hh--;
                    }
                }

                //haluatko tehdä toinen varaus
                cout << "Tee uusi varaus (y/n)? ";
                cin >> uusiVaraus;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (uusiVaraus == "y" || uusiVaraus == "Y" || uusiVaraus == "yes" || uusiVaraus == "Yes" || uusiVaraus == "YES" || uusiVaraus == "k" || uusiVaraus == "K" || uusiVaraus == "kyllä" || uusiVaraus == "Kyllä" || uusiVaraus == "KYLLÄ" || uusiVaraus == "kylla" || uusiVaraus == "Kylla" || uusiVaraus == "KYLLA") {
                    j--;
                }
                k--;
            }
        }
        if (vaihtoehto == "s" || vaihtoehto == "S" || vaihtoehto == "sulje" || vaihtoehto == "Sulje" || vaihtoehto == "SULJE" || vaihtoehto == "sulje ohjelma" || vaihtoehto == "Sulje ohjelma" || vaihtoehto == "Sulje Ohjelma" || vaihtoehto == "SULJE OHJELMA") {
            cout << "Sulje hotelli managementti Ohjelma (y/n)? ";
            cin >> off;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (off == "n" || off == "N" || off == "no" || off == "No" || off == "NO" || off == "e" || off == "E" || off == "ei" || off == "Ei" || off == "EI") {
                k--;
            }
        }
    }





    /*Tallenna hotellivaraukset
    fstream outfile;
    outfile.open("varaukset.txt", fstream::out);
    if (outfile.is_open())
    {
        for (int i = 0; i < lines.size(); i++) {
            outfile << lines[i] << endl;
        }
        outfile.close();
    }
    else cout << "Unable to open file";*/

    return 0;
}

// Satunnaisluku generaattori
int randn(int minimi, int maksimi) {

    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(minimi, maksimi);

    return dis(gen);
}

// laskee hinnat
int hintalasku(int tyyppi, int yöt, int alennus) {
    int hinta;

    if (tyyppi == 1) {
        hinta = (100.00 * yöt) - (100.00 * yöt / 100.00) * alennus;
    }
    if (tyyppi == 2) {
        hinta = (150.00 * yöt) - (150.00 * yöt / 100.00) * alennus;
    }

    return hinta;
}