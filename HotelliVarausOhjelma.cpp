// Hotelli Harjoitusteht‰v‰
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


int main() {
    // kirjaimet
    setlocale(LC_ALL, "FI_fi");

    //Muuttujat ja valmistelut
    fstream infile;
    string line;
    vector<string> lines;
    int huoneM‰‰r‰;
    int huoneM‰‰r‰1hh;
    int huoneM‰‰r‰2hh;
    //random_device rd;
    //mt19937 gen(rd());
    int randNum = 0;
    vector<bool> varausNumerot(100000, 0);
    /*for (int i = 0; i < 100000; i++) {
        varausNumerot.push_back(0);
        cout << varausNumerot.size() << endl;
    }*/
    string varausKonfirm;
    string uusiVaraus;

    struct varaus {
        string nimi;
        int huoneNumero;
        int huoneTyyppi;
        int alennus;
        int yˆt;
        int varausNumero;
        int hinta;

        void n‰yt‰Varaus() {
            cout << "Nimi: " << nimi << endl;
            cout << "Huone Tyyppi: " << huoneTyyppi << endl;
            cout << "Huone Numero: " << huoneNumero << endl;
            cout << "÷it‰: " << yˆt << endl;
            cout << "Alennusprosentti: " << alennus << "%" << endl;
            cout << "Hinta: " << hinta << endl;
            cout << "Varausnumero: " << varausNumero << endl;
        }
    };
    vector<varaus> varaukset;

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
        cout << "Ei olemassa olevia varauksia, luodaan hotelli..." << endl;
        randNum = randn(20, 131);
        huoneM‰‰r‰ = randNum * 2;
        huoneM‰‰r‰1hh = randNum;
        huoneM‰‰r‰2hh = huoneM‰‰r‰1hh;
        cout << "Huoneiden m‰‰r‰: " << huoneM‰‰r‰ << endl << "1hh: " << huoneM‰‰r‰1hh << endl << "2hh: " << huoneM‰‰r‰2hh << endl;
    }

    vector<bool> varattu1hh(huoneM‰‰r‰1hh + 1, 0); //varattu1hh[300] = 0;
    vector<bool> varattu2hh(huoneM‰‰r‰2hh + 1, 0); //varattu2hh[300] = 0; 


    //Varaa huone
    for (int j = 0; j < 1; j++) {
        varaus tempVaraus;
        cout << "Mik‰ teid‰n nimenne on? ";
        getline(cin, tempVaraus.nimi);
        cout << "Haluaisitko yhden hengen huone (1) tai kahden hengen huone (2)? ";
        cin >> tempVaraus.huoneTyyppi;
        for (int i = 0; i < 1; i++) {
            cout << "Mik‰ huonenumero haluaisitte? ";
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
        randNum = randn(0, 3);
        tempVaraus.alennus = randNum * 10;
        cout << "Kuinka monta yˆt‰ olette t‰‰ll‰? ";
        cin >> tempVaraus.yˆt;
        for (int i = 0; i < 1; i++) {
            randNum = randn(10000, 100000);
            if (varausNumerot[randNum] == true) {
                i--;
            }
        }
        tempVaraus.varausNumero = randNum;
        if (tempVaraus.huoneTyyppi == 1) {
            tempVaraus.hinta = (100.00 * tempVaraus.yˆt) - (100.00 * tempVaraus.yˆt / 100.00) * tempVaraus.alennus;
        }
        if (tempVaraus.huoneTyyppi == 2) {
            tempVaraus.hinta = (150.00 * tempVaraus.yˆt) - (150.00 * tempVaraus.yˆt / 100.00) * tempVaraus.alennus;
        }
        tempVaraus.n‰yt‰Varaus();
        cout << "Konfirmoi varaus (y/n)? ";
        cin >> varausKonfirm;
        if (varausKonfirm == "y" || varausKonfirm == "Y" || varausKonfirm == "yes" || varausKonfirm == "Yes" || varausKonfirm == "YES" || varausKonfirm == "k" || varausKonfirm == "K" || varausKonfirm == "kyll‰" || varausKonfirm == "Kyll‰" || varausKonfirm == "KYLLƒ" || varausKonfirm == "kylla" || varausKonfirm == "Kylla" || varausKonfirm == "KYLLA") {
            varaukset.push_back(tempVaraus);
            if (tempVaraus.huoneTyyppi == 1) {
                varattu1hh[tempVaraus.huoneNumero] = 1;
                huoneM‰‰r‰1hh--;
            }
            if (tempVaraus.huoneTyyppi == 2) {
                varattu2hh[tempVaraus.huoneNumero] = 1;
                huoneM‰‰r‰2hh--;
            }
        }
        cout << "Tee uusi varaus (y/n)? ";
        cin >> uusiVaraus;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (uusiVaraus == "y" || uusiVaraus == "Y" || uusiVaraus == "yes" || uusiVaraus == "Yes" || uusiVaraus == "YES" || uusiVaraus == "k" || uusiVaraus == "K" || uusiVaraus == "kyll‰" || uusiVaraus == "Kyll‰" || uusiVaraus == "KYLLƒ" || uusiVaraus == "kylla" || uusiVaraus == "Kylla" || uusiVaraus == "KYLLA") {
            j--;
        }
        /*for (int i = 0; i < varattu1hh.size(); i++) {
            cout << varattu1hh[i] << endl;
        }
        for (int i = 0; i < varattu2hh.size(); i++) {
            cout << varattu2hh[i] << endl;
        }*/
    }
    //struct varaus varaus = {"nimi", 16, 2, 1, 5, 11111};



    //debug
    /*for (int i = 0; i < 1000; i++) {
        randnum = randn();
        huoneM‰‰r‰ = randnum;
        cout << huoneM‰‰r‰ * 2 << " ";
    }*/


    /*funktio
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++)
            lines[i][j] = toupper(lines[i][j]);
    }*/






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