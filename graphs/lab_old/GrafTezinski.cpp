#include <limits.h>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>

/*
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

*/

