// Hotelli Harjoitusteht�v�
// Joonas Akers


#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>
#include<ctype.h>
#include<limits>
#include<random>
#include<sstream>
using namespace std;

struct varaus {
    string nimi; //varaajan nimi
    int huoneNumero; //varatun huoneen numero
    int huoneTyyppi; //varatun huoneen tyyppi (1hh tai 2hh)
    int alennus; //mahdollinen alennus
    int y�t; //kuinka monta y�t� on varattu
    int varausNumero; //varauksen numero
    int hinta; //varauksen kokonais hinta

    //tulostaa varauksen tiedot
    void n�yt�Varaus() {
        cout << "Nimi: " << nimi << endl;
        cout << "Huone Tyyppi: " << huoneTyyppi << "hh" << endl;
        cout << "Huone Numero: " << huoneNumero << endl;
        cout << "�it�: " << y�t << endl;
        cout << "Alennusprosentti: " << alennus << "%" << endl;
        cout << "Hinta: " << hinta << endl;
        cout << "Varausnumero: " << varausNumero << endl;
    }
};

//prototyypit
int randn(int minimi, int maksimi);
int hintalasku(int tyyppi, int y�t, int alennus);
int haku(string type, string name, int roomNumber, vector<varaus> varaukset);


int main() {
    // kirjaimet
    setlocale(LC_ALL, "FI_fi");

    //Muuttujat ja valmistelut
    fstream infile;
    string line;
    vector<string> lines;
    string vaihtoehto; //mit� haluat tehd� ohjelmalla
    int huoneM��r�; //hotellin honeiden kokonaism��r�
    int huoneM��r�1hh; //j�ljell� olevia yhden henkil�n huoneet
    int huoneM��r�2hh; //j�ljell� olevia kahden henkil�n huoneet
    int randNum = 0; //satunnaisluvun hetkellinen tallennus paikka
    vector<bool> varausNumerot(100000, 0); //lista k�ytetyist� varausnumeroista
    string varausKonfirm; //varauksen varmistus onko oikein vai ei
    string uusiVaraus; //vastaus kysymykseen halutko varata toinen huone
    string off; //haluatko sulje ohjelma
    string etsi; //etsitk� varaus numeronna vai nimell�
    int poistettavaVaraus;
    string varaajanNimi;
    int varauksenNro;
    int varauksenTyyppi;
    string poistoKonfirm;
    string uusiPoisto;
    int pituus;
    vector<string> debug;
    //hetkelliset tallennuspaikat
    string tempHuoneM��r�;
    string tempHuoneM��r�Koko;
    string tempHuoneM��r�1hh;
    string tempHuoneM��r�2hh;
    string tempNimi;
    int tempHuoneNumero; 
    int tempHuoneTyyppi; 
    int tempAlennus; 
    int tempY�t; 
    int tempVarausNumero; 
    int tempHinta;
    string tempPituus;
    


    //varauksen profiili

    vector<varaus> varaukset; //lista kaikista varatuista huoneista

    //vectorit jolla tarkistetaan onko tietty huone varattu
    vector<bool> varattu1hh(151, 0);
    vector<bool> varattu2hh(151, 0);

    //Hae olemassa olevia hotellivaraukset (jos on)
    infile.open("varaukset.txt", fstream::in);
    if (infile.is_open())
    {
        //hakee tallennetut tiedot
        string subdebug;
        while (getline(infile, subdebug)) {
            debug.push_back(subdebug);
        }

        // hakee varausten m��r�
        for (int i = 0; i < 4; i++) {
            if (i == 0) {
                tempHuoneM��r�Koko = debug[i];
            }
            if (i == 1) {
                tempHuoneM��r�1hh = debug[i];
            }
            if (i == 2) {
                tempHuoneM��r�2hh = debug[i];
            }
            if (i == 3) {
                tempPituus = debug[i];
            }
        }
        huoneM��r� = stoi(tempHuoneM��r�Koko);
        huoneM��r�1hh = stoi(tempHuoneM��r�1hh);
        huoneM��r�2hh = stoi(tempHuoneM��r�2hh);
        pituus = stoi(tempPituus);

        // hakee tallennettuja tarkistu booleaneja
        for (int i = 0; i < 150; i++) {
            varattu1hh[i] = stoi(debug[i+ 4]);
        }
        for (int i = 0; i < 150; i++) {
            varattu2hh[i] = stoi(debug[i + 154]);
        }

        //tekee varaukset
        for (int i = 0; i < pituus; i++) {
            varaus tempVaraus;
            tempVaraus.nimi = debug[i + 305];
            tempVaraus.huoneNumero = stoi(debug[i + pituus + 305]);
            tempVaraus.huoneTyyppi = stoi(debug[i + (pituus*2) + 305]);
            tempVaraus.alennus = stoi(debug[i + (pituus * 3) + 305]);
            tempVaraus.y�t = stoi(debug[i + (pituus * 4) + 305]);
            tempVaraus.varausNumero = stoi(debug[i + (pituus * 5) + 305]);
            tempVaraus.hinta = stoi(debug[i + (pituus * 6) + 305]);
            varaukset.push_back(tempVaraus);
        }
    }
    else {
        //tekee uusi hotelli jos ei l�yd� tallennettu hotelli
        cout << "Ei olemassa olevia varauksia, luodaan hotelli..." << endl;
        randNum = randn(20, 150);
        huoneM��r� = randNum * 2;
        huoneM��r�1hh = randNum;
        huoneM��r�2hh = huoneM��r�1hh;
    }

    cout << "Huoneiden m��r�: " << huoneM��r� << endl << "1hh: " << huoneM��r�1hh << endl << "2hh: " << huoneM��r�2hh << endl;
    
    // p��ohjelma
    for (int k = 0; k < 1; k++) {
        cout << "Mit� haluat tehd�? " << endl << "V = Varaa Huone. " << endl << "P = Poista Varaus. " << endl << "N = N�yt� Varaukset. " << endl << 
            "T = Tallenna Varaukset." << endl << "S = Sulje Ohjelma. ";
        cin >> vaihtoehto;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (vaihtoehto == "v" || vaihtoehto == "V" || vaihtoehto == "varaa" || vaihtoehto == "Varaa" || vaihtoehto == "VARAA" || vaihtoehto == "varaa huone" || 
            vaihtoehto == "Varaa huone" || vaihtoehto == "Varaa Huone" || vaihtoehto == "VARAA HUONE") {
            //Varaa huone
            for (int j = 0; j < 1; j++) {
                varaus tempVaraus;//hetkellinen varaus

                cout << "Mik� teid�n nimenne on? ";
                getline(cin, tempVaraus.nimi);

                for (int i = 0; i < 1; i++) {
                    cout << "Haluaisitko yhden hengen huone (1) tai kahden hengen huone (2)? ";
                    cin >> tempVaraus.huoneTyyppi;
                    if (tempVaraus.huoneTyyppi != 1 && tempVaraus.huoneTyyppi != 2) {
                        i--;
                        cout << "ERROR ''" << tempVaraus.huoneTyyppi << "'' ei ole validi vastaus" << endl;
                    }
                }

                for (int i = 0; i < 1; i++) {
                    cout << "Mik� huonenumero haluaisitte? ";
                    cin >> tempHuoneNumero;
                    if (tempHuoneNumero < 1 || tempHuoneNumero > huoneM��r� / 2) {
                        i--;
                        cout << "ERROR ''" << tempHuoneNumero << "'' ei ole validi vastaus" << endl;
                    }
                }

                for (int i = 0; i < 1; i++) {
                    if (tempVaraus.huoneTyyppi == 1 && varattu1hh[tempHuoneNumero] == 1) {
                        cout << "Huone on Varattu, valitse toinen huone";
                        i--;
                    }
                    if (tempVaraus.huoneTyyppi == 2 && varattu2hh[tempHuoneNumero] == 1) {
                        cout << "Huone on Varattu, valitse toinen huone";
                        i--;
                    }
                }

                tempVaraus.huoneNumero = tempHuoneNumero;

                //arpoo alennus
                randNum = randn(0, 2);
                tempVaraus.alennus = randNum * 10;

                for (int i = 0; i < 1; i++) {
                    cout << "Kuinka monta y�t� olette t��ll�? ";
                    cin >> tempVaraus.y�t;
                    if (tempVaraus.y�t < 1) {
                        i--;
                        cout << "ERROR ''" << tempVaraus.y�t << "'' ei ole validi vastaus" << endl;
                    }
                }

                //arpoo varausnumero
                for (int i = 0; i < 1; i++) {
                    randNum = randn(10000, 100000);
                    if (varausNumerot[randNum] == true) {
                        i--;
                    }
                }
                tempVaraus.varausNumero = randNum;

                //laskee hinta
                tempVaraus.hinta = hintalasku(tempVaraus.huoneTyyppi, tempVaraus.y�t, tempVaraus.alennus);

                //varmista onko haluatko tallentaa varaus (vimeinen hetki tarkistaa onko kirjoitettu oikein
                tempVaraus.n�yt�Varaus();
                for (int i = 0; i < 1; i++) {
                    cout << "Konfirmoi varaus (y/n)? ";
                    cin >> varausKonfirm;
                    if (varausKonfirm != "y" && varausKonfirm != "Y" && varausKonfirm != "yes" && varausKonfirm != "Yes" && varausKonfirm != "YES" && varausKonfirm != "k" &&
                        varausKonfirm != "K" && varausKonfirm != "kyll�" && varausKonfirm != "Kyll�" && varausKonfirm != "KYLL�" && varausKonfirm != "kylla" &&
                        varausKonfirm != "Kylla" && varausKonfirm != "KYLLA" && varausKonfirm != "n" && varausKonfirm != "N" && varausKonfirm != "no" && varausKonfirm != "No" &&
                        varausKonfirm != "NO" && varausKonfirm != "e" && varausKonfirm != "E" && varausKonfirm != "ei" && varausKonfirm != "Ei" && varausKonfirm != "EI") {
                        i--;
                        cout << "ERROR ''" << varausKonfirm << "'' ei ole validi vastaus" << endl;
                    }
                }
                if (varausKonfirm == "y" || varausKonfirm == "Y" || varausKonfirm == "yes" || varausKonfirm == "Yes" || varausKonfirm == "YES" || varausKonfirm == "k" || 
                    varausKonfirm == "K" || varausKonfirm == "kyll�" || varausKonfirm == "Kyll�" || varausKonfirm == "KYLL�" || varausKonfirm == "kylla" || 
                    varausKonfirm == "Kylla" || varausKonfirm == "KYLLA") {
                    varaukset.push_back(tempVaraus);
                    if (tempVaraus.huoneTyyppi == 1) {
                        varattu1hh[tempVaraus.huoneNumero] = 1;
                        huoneM��r�1hh--;
                    }
                    if (tempVaraus.huoneTyyppi == 2) {
                        varattu2hh[tempVaraus.huoneNumero] = 1;
                        huoneM��r�2hh--;
                    }
                }

                //haluatko tehd� toinen varaus
                for (int i = 0; i < 1; i++) {
                    cout << "Tee uusi varaus (y/n)? ";
                    cin >> uusiVaraus;
                    if (uusiVaraus != "y" && uusiVaraus != "Y" && uusiVaraus != "yes" && uusiVaraus != "Yes" && uusiVaraus != "YES" && uusiVaraus != "k" &&
                        uusiVaraus != "K" && uusiVaraus != "kyll�" && uusiVaraus != "Kyll�" && uusiVaraus != "KYLL�" && uusiVaraus != "kylla" &&
                        uusiVaraus != "Kylla" && uusiVaraus != "KYLLA" && uusiVaraus != "n" && uusiVaraus != "N" && uusiVaraus != "no" && uusiVaraus != "No" &&
                        uusiVaraus != "NO" && uusiVaraus != "e" && uusiVaraus != "E" && uusiVaraus != "ei" && uusiVaraus != "Ei" && uusiVaraus != "EI") {
                        i--;
                        cout << "ERROR ''" << uusiVaraus << "'' ei ole validi vastaus" << endl;
                    }
                }
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (uusiVaraus == "y" || uusiVaraus == "Y" || uusiVaraus == "yes" || uusiVaraus == "Yes" || uusiVaraus == "YES" || uusiVaraus == "k" || uusiVaraus == "K" || 
                    uusiVaraus == "kyll�" || uusiVaraus == "Kyll�" || uusiVaraus == "KYLL�" || uusiVaraus == "kylla" || uusiVaraus == "Kylla" || uusiVaraus == "KYLLA") {
                    j--;
                }
            }
            k--;
        }

        if (vaihtoehto == "p" || vaihtoehto == "P" || vaihtoehto == "poista" || vaihtoehto == "Poista" || vaihtoehto == "POISTA" || vaihtoehto == "poista varaus" || 
            vaihtoehto == "Poista varaus" || vaihtoehto == "Poista Varaus" || vaihtoehto == "POISTA HUONE") {
            for (int j = 0; j < 1; j++) {
                for (int i = 0; i < 1; i++) {
                    cout << "Yrit�tk� etsi� varausnumerolla (v) vai varaajan nimell� (n)? ";
                    cin >> etsi;
                    if (etsi != "v" && etsi != "V" && etsi != "numero" && etsi != "Numero" && etsi != "NUMERO" && etsi != "n" && etsi != "N" && etsi != "nimi" && 
                        etsi != "Nimi" && etsi != "NIMI") {
                        i--;
                        cout << "ERROR ''" << etsi << "'' ei ole validi vastaus" << endl;
                    }
                }
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (etsi == "v" || etsi == "V" || etsi == "numero" || etsi == "Numero" || etsi == "NUMERO") {
                    cout << "Mik� varaus etsit (varausnumero)? ";
                    cin >> varauksenNro; varaajanNimi = "null";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (etsi == "n" || etsi == "N" || etsi == "nimi" || etsi == "Nimi" || etsi == "NIMI") {
                    cout << "Mik� varaus etsit (varaajan nimi)? ";
                    getline(cin, varaajanNimi); varauksenNro = 0;
                }

                poistettavaVaraus = haku(etsi, varaajanNimi, varauksenNro, varaukset); //mik� varaus poistetaan
                
                //mink� tyyppinen huone poistetaan
                varauksenTyyppi = varaukset[poistettavaVaraus].huoneTyyppi;

                //varmista poisto
                for (int i = 0; i < 1; i++) {
                    cout << "Konfirmoi poisto (y/n)? ";
                    cin >> poistoKonfirm;
                    if (poistoKonfirm != "y" && poistoKonfirm != "Y" && poistoKonfirm != "yes" && poistoKonfirm != "Yes" && poistoKonfirm != "YES" && poistoKonfirm != "k" &&
                        poistoKonfirm != "K" && poistoKonfirm != "kyll�" && poistoKonfirm != "Kyll�" && poistoKonfirm != "KYLL�" && poistoKonfirm != "kylla" &&
                        poistoKonfirm != "Kylla" && poistoKonfirm != "KYLLA" && poistoKonfirm != "n" && poistoKonfirm != "N" && poistoKonfirm != "no" && poistoKonfirm != "No" &&
                        poistoKonfirm != "NO" && poistoKonfirm != "e" && poistoKonfirm != "E" && poistoKonfirm != "ei" && poistoKonfirm != "Ei" && poistoKonfirm != "EI") {
                        i--;
                        cout << "ERROR ''" << poistoKonfirm << "'' ei ole validi vastaus" << endl;
                    }
                }
                if (poistoKonfirm == "y" || poistoKonfirm == "Y" || poistoKonfirm == "yes" || poistoKonfirm == "Yes" || poistoKonfirm == "YES" || poistoKonfirm == "k" || 
                    poistoKonfirm == "K" || poistoKonfirm == "kyll�" || poistoKonfirm == "Kyll�" || poistoKonfirm == "KYLL�" || poistoKonfirm == "kylla" || 
                    poistoKonfirm == "Kylla" || poistoKonfirm == "KYLLA") {
                    //poista tarkistus listoista ja lis�� vapaa huone vapaiten huoneen listaan
                    if (varaukset[poistettavaVaraus].huoneTyyppi == 1) {
                        varattu1hh[varaukset[poistettavaVaraus].huoneNumero] = 0;
                        huoneM��r�1hh++;
                    }
                    if (varaukset[poistettavaVaraus].huoneTyyppi == 2) {
                        varattu2hh[varaukset[poistettavaVaraus].huoneNumero] = 0;
                        huoneM��r�2hh++;
                    }
                    //poista varauslistasta
                    varaukset.erase(varaukset.begin() + poistettavaVaraus);
                }

                //haluatko poista toinen varaus
                for (int i = 0; i < 1; i++) {
                    cout << "Poista toinen varaus (y/n)? ";
                    cin >> uusiPoisto;
                    if (uusiPoisto != "y" && uusiPoisto != "Y" && uusiPoisto != "yes" && uusiPoisto != "Yes" && uusiPoisto != "YES" && uusiPoisto != "k" &&
                        uusiPoisto != "K" && uusiPoisto != "kyll�" && uusiPoisto != "Kyll�" && uusiPoisto != "KYLL�" && uusiPoisto != "kylla" &&
                        uusiPoisto != "Kylla" && uusiPoisto != "KYLLA" && uusiPoisto != "n" && uusiPoisto != "N" && uusiPoisto != "no" && uusiPoisto != "No" &&
                        uusiPoisto != "NO" && uusiPoisto != "e" && uusiPoisto != "E" && uusiPoisto != "ei" && uusiPoisto != "Ei" && uusiPoisto != "EI") {
                        i--;
                        cout << "ERROR ''" << uusiPoisto << "'' ei ole validi vastaus" << endl;
                    }
                }
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (uusiPoisto == "y" || uusiPoisto == "Y" || uusiPoisto == "yes" || uusiPoisto == "Yes" || uusiPoisto == "YES" || uusiPoisto == "k" ||
                    uusiPoisto == "K" || uusiPoisto == "kyll�" || uusiPoisto == "Kyll�" || uusiPoisto == "KYLL�" || uusiPoisto == "kylla" || uusiPoisto == "Kylla" || 
                    uusiPoisto == "KYLLA") {
                    j--;
                }
            }
            k--;
        }

        if (vaihtoehto == "n" || vaihtoehto == "N" || vaihtoehto == "n�yt�" || vaihtoehto == "N�yt�" || vaihtoehto == "N�YT�") {
            for (int i = 0; i < varaukset.size(); i++) {
                varaukset[i].n�yt�Varaus();
            }
            k--;
        }

        //tallenna hotellivaraukset
        if (vaihtoehto == "t" || vaihtoehto == "T" || vaihtoehto == "tallenna" || vaihtoehto == "Tallenna" || vaihtoehto == "TALLENNA" || vaihtoehto == "tallenna ohjelma" || 
            vaihtoehto == "Tallenna ohjelma" || vaihtoehto == "Tallenna Ohjelma" || vaihtoehto == "TALLENNA OHJELMA") {
            for (int i = 0; i < varaukset.size(); i++) {
                fstream outfile;
                outfile.open("varaukset.txt", fstream::out);
                if (outfile.is_open())
                {
                    // tallenna varausten m��r�t
                    outfile << huoneM��r� << endl << huoneM��r�1hh << endl << huoneM��r�2hh << endl << (varaukset.size()/10);

                    // tallenna tarkistuslistat
                    for (int i = 0; i < varattu1hh.size(); i++) {
                        outfile << varattu2hh[i] << endl;
                    }
                    for (int i = 0; i < varattu2hh.size(); i++) {
                        outfile << varattu2hh[i] << endl;
                    }
                    
                    // tallenna varausten tiedot
                    for (int i = 0; i < varaukset.size(); i++) {
                        outfile << varaukset[i].nimi << endl;
                    }
                    for (int i = 0; i < varaukset.size(); i++) {
                        outfile << varaukset[i].huoneNumero << endl;
                    }
                    for (int i = 0; i < varaukset.size(); i++) {
                        outfile << varaukset[i].huoneTyyppi << endl;
                    }
                    for (int i = 0; i < varaukset.size(); i++) {
                        outfile << varaukset[i].alennus << endl;
                    }
                    for (int i = 0; i < varaukset.size(); i++) {
                        outfile << varaukset[i].y�t << endl;
                    }
                    for (int i = 0; i < varaukset.size(); i++) {
                        outfile << varaukset[i].varausNumero << endl;
                    }
                    for (int i = 0; i < varaukset.size(); i++) {
                        outfile << varaukset[i].hinta << endl;
                    }

                    outfile.close();
                }
                else cout << "Unable to open file";
            }
            k--;
            
        }

        //sulje ohjelma
        if (vaihtoehto == "s" || vaihtoehto == "S" || vaihtoehto == "sulje" || vaihtoehto == "Sulje" || vaihtoehto == "SULJE" || vaihtoehto == "sulje ohjelma" || 
            vaihtoehto == "Sulje ohjelma" || vaihtoehto == "Sulje Ohjelma" || vaihtoehto == "SULJE OHJELMA") {
            for (int i = 0; i < 1; i++) {
                cout << "Haluatko Varmasti sulkea hotelli managementti Ohjelma (y/n)? ";
                cin >> off;
                if (off != "y" && off != "Y" && off != "yes" && off != "Yes" && off != "YES" && off != "k" &&
                    off != "K" && off != "kyll�" && off != "Kyll�" && off != "KYLL�" && off != "kylla" &&
                    off != "Kylla" && off != "KYLLA" && off != "n" && off != "N" && off != "no" && off != "No" &&
                    off != "NO" && off != "e" && off != "E" && off != "ei" && off != "Ei" && off != "EI") {
                    i--;
                    cout << "ERROR ''" << off << "'' ei ole validi vastaus" << endl;
                }
            }
            if (off == "n" || off == "N" || off == "no" || off == "No" || off == "NO" || off == "e" || off == "E" || off == "ei" || off == "Ei" || off == "EI") {
                k--;
            }
        }

        if (vaihtoehto != "v" && vaihtoehto != "V" && vaihtoehto != "varaa" && vaihtoehto != "Varaa" && vaihtoehto != "VARAA" && vaihtoehto != "varaa huone" &&
            vaihtoehto != "Varaa huone" && vaihtoehto != "Varaa Huone" && vaihtoehto != "VARAA HUONE" && vaihtoehto != "p" && vaihtoehto != "P" && 
            vaihtoehto != "poista" && vaihtoehto != "Poista" && vaihtoehto != "POISTA" && vaihtoehto != "poista varaus" && vaihtoehto != "Poista varaus" && 
            vaihtoehto != "Poista Varaus" && vaihtoehto != "POISTA HUONE" && vaihtoehto != "n" && vaihtoehto != "N" && vaihtoehto != "n�yt�" && vaihtoehto != "N�yt�" && 
            vaihtoehto != "N�YT�" && vaihtoehto != "t" && vaihtoehto != "T" && vaihtoehto != "tallenna" && vaihtoehto != "Tallenna" && vaihtoehto != "TALLENNA" && 
            vaihtoehto != "tallenna ohjelma" && vaihtoehto != "Tallenna ohjelma" && vaihtoehto != "Tallenna Ohjelma" && vaihtoehto != "TALLENNA OHJELMA" && 
            vaihtoehto != "s" && vaihtoehto != "S" && vaihtoehto != "sulje" && vaihtoehto != "Sulje" && vaihtoehto != "SULJE" && vaihtoehto != "sulje ohjelma" &&
            vaihtoehto != "Sulje ohjelma" && vaihtoehto != "Sulje Ohjelma" && vaihtoehto != "SULJE OHJELMA") {
            cout << "ERROR ''" << vaihtoehto << "'' ei ole validi vastaus" << endl;
            k--;
        }
    }

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
int hintalasku(int tyyppi, int y�t, int alennus) {
    int hinta;

    if (tyyppi == 1) {
        hinta = (100.00 * y�t) - (100.00 * y�t / 100.00) * alennus;
    }
    if (tyyppi == 2) {
        hinta = (150.00 * y�t) - (150.00 * y�t / 100.00) * alennus;
    }

    return hinta;
}

// hae varaus
int haku(string type, string name, int roomNumber, vector<varaus> varaukset) {
    int etsitt�v�Varaus;

    if (type == "v" || type == "V" || type == "numero" || type == "Numero" || type == "NUMERO") {
        for (int i = 0; i < varaukset.size(); i++) {
            if (varaukset[i].varausNumero == roomNumber) {
                etsitt�v�Varaus = i;
            }
        }
    }

    if (type == "n" || type == "N" || type == "nimi" || type == "Nimi" || type == "NIMI") {
        for (int i = 0; i < varaukset.size(); i++) {
            if (varaukset[i].nimi == name) {
                etsitt�v�Varaus = i;
            }
        }
    }
    return etsitt�v�Varaus;
}