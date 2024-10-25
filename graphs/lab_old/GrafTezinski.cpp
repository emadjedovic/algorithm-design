#include <limits.h>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>

void TezinskiGraf::dodajGranu(int i, int j, double w) {
    lista_susjedstva[i].push_back({j,w});
    if(!usmjeren)
        lista_susjedstva[j].push_back({i,w});
}

vector<double> TezinskiGraf::DijkstraSporo(int pocetni) {
    vector<bool> obradjeni(broj_cvorova, false);
    vector<double> udaljenosti(broj_cvorova, INT_MAX);
    obradjeni[pocetni] = true;
    udaljenosti[pocetni] = 0;
    int trenutni = pocetni;

    for(int i = 0; i < broj_cvorova - 1; i++) {
        for(auto el: lista_susjedstva[trenutni])
            if(!obradjeni[el.first] && udaljenosti[trenutni] + el.second < udaljenosti[el.first])
                udaljenosti[el.first] = udaljenosti[trenutni] + el.second;

        pair<double,int> minimum = {INT_MAX,-1};
        for(int j = 0; j < broj_cvorova; j++)
            if(!obradjeni[j] && udaljenosti[j] < minimum.first)
                minimum = {udaljenosti[j], j};

        trenutni = minimum.second;
        obradjeni[trenutni] = true;
    }
    return udaljenosti;
}

pair<bool, vector<double>> TezinskiGraf::BelmanFord(int pocetni) {

    vector<double> udaljenosti(broj_cvorova, INT_MAX);
    udaljenosti[pocetni] = 0;
    for(int iteracija = 1; iteracija < broj_cvorova; iteracija++)
        for(int i = 0; i < broj_cvorova; i++)
            for(auto el: lista_susjedstva[i])
                if(udaljenosti[el.first] > udaljenosti[i] + el.second)
                    udaljenosti[el.first] = udaljenosti[i] + el.second;

    for(int i = 0; i < broj_cvorova; i++)
        for(auto el: lista_susjedstva[i])
            if(udaljenosti[el.first] > udaljenosti[i] + el.second)
                return {false, udaljenosti};

    return {true, udaljenosti};
}

pair<double, vector<pair<int,int>>> TezinskiGraf::Prim() {
    int pocetni = 0;
    vector<bool> obradjeni(broj_cvorova, false);
    vector<double> udaljenosti(broj_cvorova, INT_MAX);  //udaljenost od obradjenog dijela
    obradjeni[pocetni] = true;
    udaljenosti[pocetni] = 0;
    int trenutni = pocetni;
    set<pair<double, int>> stablo;
    vector<int> prethodnik(broj_cvorova, -1);
    pair<double, vector<pair<int,int>>> MST{0,vector<pair<int,int>> ()};

    for(int i = 0; i < broj_cvorova - 1; i++) {
        for(auto el: lista_susjedstva[trenutni]) {
            if(!obradjeni[el.first] && el.second < udaljenosti[el.first]) {
                if(stablo.find({udaljenosti[el.first],el.first}) != stablo.end())
                    stablo.erase({udaljenosti[el.first],el.first});

                udaljenosti[el.first] = el.second;
                stablo.insert({udaljenosti[el.first],el.first});
                prethodnik[el.first] = trenutni;
            }
        }
        int novi = stablo.begin()->second;
        MST.first += stablo.begin()->first;
        MST.second.push_back({prethodnik[novi], novi});
        stablo.erase(stablo.begin());
        trenutni = novi;
        obradjeni[trenutni] = true;
    }
    return MST;
}


pair<double, vector<pair<int,int>>> TezinskiGraf::Kruskal() {

    vector<pair<double,pair<int,int>>> grane;
    for(int i = 0; i < broj_cvorova; i++)
        for(auto el:lista_susjedstva[i]) {
            if(i < el.first)
                grane.push_back({el.second,{i,el.first}});
        }

    sort(grane.begin(),grane.end());
    pair<double, vector<pair<int,int>>> MST{0,vector<pair<int,int>> ()};
    DisjunktniSkupovi ds(broj_cvorova);
    int brojac = 0;
    for(int i = 0; i < grane.size(); i++) {
        if(ds.Nadji(grane[i].second.first) != ds.Nadji(grane[i].second.second)) {
            ds.Spoji(grane[i].second.first,grane[i].second.second);
            brojac++;
            MST.first += grane[i].first;
            MST.second.push_back(grane[i].second);
        }
        if(brojac == broj_cvorova - 1)
            break;
    }
    return MST;
}


vector<double> TezinskiGraf::DijkstraBrzo(int pocetni) {
    vector<bool> obradjeni(broj_cvorova, false);
    vector<double> udaljenosti(broj_cvorova, INT_MAX);
    obradjeni[pocetni] = true;
    udaljenosti[pocetni] = 0;
    int trenutni = pocetni;
    set<pair<double, int>> stablo;

    for(int i = 0; i < broj_cvorova - 1; i++) {
        for(auto el: lista_susjedstva[trenutni]) {
            if(!obradjeni[el.first] && udaljenosti[trenutni] + el.second < udaljenosti[el.first]) {
                if(stablo.find({udaljenosti[el.first],el.first}) != stablo.end())
                    stablo.erase({udaljenosti[el.first],el.first});

                udaljenosti[el.first] = udaljenosti[trenutni] + el.second;
                stablo.insert({udaljenosti[el.first],el.first});
            }
        }
        trenutni = stablo.begin()->second;
        stablo.erase(stablo.begin());
        obradjeni[trenutni] = true;
    }
    return udaljenosti;
}

double TezinskiGraf::maksimalanProtok(int pocetni, int krajnji) {
    int n = broj_cvorova;
    //najprije pravimo matricu udaljenosti pomocnog grafa i popunjavamo je nulama
    vector<vector<double>> matricaUdaljenosti(n);
    for(int i = 0; i < n; i++)
        matricaUdaljenosti[i].resize(n);

    //sada pravimo listu susjedstva pomocnog grafa
    //bitno je samo da li postoji grana (ne i njen kapacitet)
    //moramo pamtiti i da li je ta grana u originalnom grafu (true ako jeste)
    vector<list<pair<int,bool>>> susjedi(n);
    for(int i=0;i<n;i++)
        for(auto it = lista_susjedstva[i].begin();it!=lista_susjedstva[i].end();it++) {
            susjedi[i].push_back({it->first,true});
            susjedi[it->first].push_back({i,false});
            matricaUdaljenosti[i][it->first] = it->second;
            //na pocetku samo postoji grana od i do it->first koja je jednaka kapacitetu
            //grana u suprotnom smjeru zasad ostaje na 0
        }

    double maksimalan_protok = 0;
    //sada trazimo puteve od pocetnog do krajnjeg u pomocnom grafu
    //kada vise ne bude puteva onda prekidamo petlju
    while(true) {
        //koristimo BFS
        queue<int> red;
        red.push(pocetni);
        //za svaki cvor pamtimo ko ga je pronasao kako bi rekonstruisali put
        //-1 znaci da nije pronadjen, a -2 da se radi o pocetnom cvoru
        //pored toga pamtimo da li ta grana po kojoj je pronadjen pripada originalnom grafu
        vector<pair<int,bool>> ko_ga_je_nasao(n,{-1,false});
        ko_ga_je_nasao[pocetni].first = -2;
        while(!red.empty()) {
            int trenutni = red.front();
            red.pop();
            for(auto it = susjedi[trenutni].begin();it!=susjedi[trenutni].end();it++) {
                //moguce je da u pomocnom grafu postoji grana ali ako je njena tezina 0 to znaci da je u sustini nema
                if(matricaUdaljenosti[trenutni][it->first] == 0)
                continue;

                if(ko_ga_je_nasao[it->first].first == -1) {
                    red.push(it->first);
                    ko_ga_je_nasao[it->first] = {trenutni,it->second};
                }
            }
            //ako smo vec nasli krajnji nema potrebe dalje traziti
            if(ko_ga_je_nasao[krajnji].first != -1)
                break;
        }
        //ako nema puta znaci da smo nasli najveci protok
        if(ko_ga_je_nasao[krajnji].first == -1)
            break;
        //sada treba rekonstruisati put
        //u putu cuvamo grane i za svaku granu pamtimo da li grana pripada originalnom grafu
        vector<pair<pair<int,int>,bool>> put;
        //usput ćemo i vidjeti koja je najmanja grana na tom putu
        double duzina_najmanje_grane = INT_MAX;
        int trenutni = krajnji;
        do {
            put.push_back({{ko_ga_je_nasao[trenutni].first,trenutni},ko_ga_je_nasao[trenutni].second});
            if(matricaUdaljenosti[ko_ga_je_nasao[trenutni].first][trenutni] < duzina_najmanje_grane)
                duzina_najmanje_grane = matricaUdaljenosti[ko_ga_je_nasao[trenutni].first][trenutni];

            trenutni = ko_ga_je_nasao[trenutni].first;
        } while(trenutni != pocetni);
        //povecavamo protok za vrijednost najmanje grane
        maksimalan_protok += duzina_najmanje_grane;
        //modifikujemo graf
        for(int i = 0;i<put.size();i++) {
            cout<<"("<<put[i].first.first<<","<<put[i].first.second<<")";
            if(put[i].second) {
                matricaUdaljenosti[put[i].first.first][put[i].first.second] -= duzina_najmanje_grane;
                matricaUdaljenosti[put[i].first.second][put[i].first.first] += duzina_najmanje_grane;
            }
            else {
                matricaUdaljenosti[put[i].first.first][put[i].first.second] += duzina_najmanje_grane;
                matricaUdaljenosti[put[i].first.second][put[i].first.first] -= duzina_najmanje_grane;
            }
        }
        cout<<endl;
    }
    return maksimalan_protok;
}



