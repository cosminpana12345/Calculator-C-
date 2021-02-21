#include <bits/stdc++.h>

using namespace std;

string calcul;

vector <pair<char, int>> paranteze;
vector <double> numere;
vector <char> operatii;

vector <pair <int, int>> parantezeRotunde;
vector <pair <int, int>> parantezePatrate;
vector <pair <int, int>> parantezeAcolade;

void print_paranteze(){
    for(pair<char, int> pereche : paranteze)
        cout<<pereche.first<<' '<<pereche.second<<endl;

    cout<<endl<<endl;
}

void print_numere(){
    for(double nr : numere)
        cout<<nr<<endl;

    cout<<endl<<endl;
}

void print_op(){
    for(char nr : operatii)
        cout<<nr<<endl;

    cout<<endl<<endl;
}

void menu(){
    cout << "Introduceti calculul pe care doriti sa il efectuati si apasati" << endl;
    cout << "+ -> plus" << endl;
    cout << "- -> minus" << endl;
    cout << ": -> impartire" << endl;
    cout << "* -> inmultire" << endl;
}
void citire() {
    double curNr;
    char curChar;
    int nextChar;
    bool bec= true;

    while(bec){
        nextChar = iss.peek();
        if(nextChar == EOF) return;
        if(isdigit(nextChar)){
            iss >> curNr;
            numere.push_back(curNr);
        }else{
            iss >> curChar;
            if(strchr(":*-+", curChar)){
                operatii.push_back(curChar);
            }else{
                pair <char, int> p;
                p.first = curChar;
                if(strchr("([{", curChar)){
                    p.second = numere.size();
                }else{
                    p.second = numere.size();
                }
                paranteze.push_back(p);
            }
        }
    }
}

bool verifParanteze(){
    stack <char> paranteze;
    for(auto x : calcul){
        switch (x) {
            case '(':
                paranteze.push(x);
                break;
            case '{':
                paranteze.push(x);
                break;
            case '[':
                paranteze.push(x);
                break;
            case ')':
                if (paranteze.empty() || paranteze.top() != '(')
                    return false;
                paranteze.pop();
                break;
            case '}':
                if (paranteze.empty() || paranteze.top() != '{')
                    return false;
                paranteze.pop();
                break;
            case ']':
                if (paranteze.empty() || paranteze.top() != '[')
                    return false;
                paranteze.pop();
        }
    }
    return paranteze.empty();
}

void aranjareParanteze(){
    for(int i = 0; i < paranteze.size(); i++){
        pair <int, int> aux;
        switch (paranteze[i].first) {
            case '(':
                aux.first = paranteze[i].second;
                for(int j = i + 1; j < paranteze.size(); j++){
                    if(paranteze[j].first == ')'){
                        aux.second = paranteze[j].second;
                        break;
                    }
                }
                parantezeRotunde.push_back(aux);
                break;
            case '[':
                aux.first = paranteze[i].second;
                for(int j = i + 1; j < paranteze.size(); j++){
                    if(paranteze[j].first == ']'){
                        aux.second = paranteze[j].second;
                        break;
                    }
                }
                parantezeRotunde.push_back(aux);
                break;
            case '{':
                aux.first = paranteze[i].second;
                for(int j = i + 1; j < paranteze.size(); j++){
                    if(paranteze[j].first == '}'){
                        aux.second = paranteze[j].second;
                        break;
                    }
                }
                parantezeRotunde.push_back(aux);
                break;
        }
    }

    for(auto x : parantezeRotunde)
        cout << x.first << " " << x.second << ";";
    cout << endl;
    for(auto x : parantezePatrate)
        cout << x.first << " " << x.second << ";";
    cout << endl;
    for(auto x : parantezeAcolade)
        cout << x.first << " " << x.second << ";";
    cout << endl;
}

void mutareParanteze(int x){
    for(auto p : parantezeRotunde){
        if(p.second > x)    p.second--;
        if(p.first > x) p.first--;
    }
    for(auto p : parantezePatrate){
        if(p.second > x)    p.second--;
        if(p.first > x) p.first--;
    }
    for(auto p : parantezeAcolade){
        if(p.second > x)    p.second--;
        if(p.first > x) p.first--;
    }
}

void solutie(){
    if(!verifParanteze) {
        cout << "EROARE";
        return;
    }
    aranjareParanteze();
    if(paranteze.size() == 0){
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == ':'){
                numere[i] = numere[i]/numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
            }
        }
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == '*'){
                numere[i] = numere[i]*numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
            }
        }
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == '-'){
                numere[i] = numere[i]-numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
                i = -1;
            }
        }
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == '+'){
                numere[i] = numere[i]+numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
                i = -1;
            }
        }
    }else{
        for(int i = 0; i < parantezeRotunde.size(); i++){
            for(int j = parantezeRotunde[i].first; j < parantezeRotunde[i].second - 1; j++){
                if(operatii[j] == ':'){
                    numere[j] = numere[j]/numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeRotunde[i].second--;
                    mutareParanteze(parantezeRotunde[i].second);
                }
            }

            for(int i = 0; i < numere.size()-1; i++){
                cout << numere[i] << operatii[i];
            }
            cout << numere[numere.size()-1] << endl;

            for(auto x : parantezeRotunde)
                cout << x.first << " " << x.second << ";";
            cout << endl;
            for(auto x : parantezePatrate)
                cout << x.first << " " << x.second << ";";
            cout << endl;
            for(auto x : parantezeAcolade)
                cout << x.first << " " << x.second << ";";
            cout << endl;

            for(int j = parantezeRotunde[i].first; j < parantezeRotunde[i].second - 1; j++){
                if(operatii[j] == '*'){
                    numere[j] = numere[j]*numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeRotunde[i].second--;
                    mutareParanteze(parantezeRotunde[i].second);
                }
            }

            for(int i = 0; i < numere.size()-1; i++){
                cout << numere[i] << operatii[i];
            }
            cout << numere[numere.size()-1] << endl;

            for(int j = parantezeRotunde[i].first; j < parantezeRotunde[i].second - 1; j++){
                if(operatii[j] == '-'){
                    numere[j] = numere[j]-numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeRotunde[i].second--;
                    mutareParanteze(parantezeRotunde[i].second);
                }
            }
            for(int j = parantezeRotunde[i].first; j < parantezeRotunde[i].second - 1; j++){
                if(operatii[j] == '+'){
                    numere[j] = numere[j]+numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeRotunde[i].second--;
                    mutareParanteze(parantezeRotunde[i].second);
                }
            }
        }
        for(int i = 0; i < parantezePatrate.size(); i++){
            for(int j = parantezePatrate[i].first; j < parantezePatrate[i].second - 1; j++){
                if(operatii[j] == ':'){
                    numere[j] = numere[j]/numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezePatrate[i].second--;
                    mutareParanteze(parantezePatrate[i].second);
                }
            }
            for(int j = parantezePatrate[i].first; j < parantezePatrate[i].second - 1; j++){
                if(operatii[j] == '*'){
                    numere[j] = numere[j]*numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezePatrate[i].second--;
                    mutareParanteze(parantezePatrate[i].second);
                }
            }
            for(int j = parantezePatrate[i].first; j < parantezePatrate[i].second - 1; j++){
                if(operatii[j] == '-'){
                    numere[j] = numere[j]-numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezePatrate[i].second--;
                    mutareParanteze(parantezePatrate[i].second);
                }
            }
            for(int j = parantezePatrate[i].first; j < parantezePatrate[i].second - 1; j++){
                if(operatii[j] == '+'){
                    numere[j] = numere[j]+numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezePatrate[i].second--;
                    mutareParanteze(parantezePatrate[i].second);
                }
            }
        }
        for(int i = 0; i < parantezeAcolade.size(); i++){
            for(int j = parantezeAcolade[i].first; j < parantezeAcolade[i].second - 1; j++){
                if(operatii[j] == ':'){
                    numere[j] = numere[j]/numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeAcolade[i].second--;
                    mutareParanteze(parantezeAcolade[i].second);
                }
            }
            for(int j = parantezeAcolade[i].first; j < parantezeAcolade[i].second - 1; j++){
                if(operatii[j] == '*'){
                    numere[j] = numere[j]*numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeAcolade[i].second--;
                    mutareParanteze(parantezeAcolade[i].second);
                }
            }
            for(int j = parantezeAcolade[i].first; j < parantezeAcolade[i].second - 1; j++){
                if(operatii[j] == '-'){
                    numere[j] = numere[j]-numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeAcolade[i].second--;
                    mutareParanteze(parantezeAcolade[i].second);
                }
            }
            for(int j = parantezeAcolade[i].first; j < parantezeAcolade[i].second - 1; j++){
                if(operatii[j] == '+'){
                    numere[j] = numere[j]+numere[j+1];
                    numere.erase(numere.begin() + j + 1);
                    operatii.erase(operatii.begin() + j);
                    parantezeAcolade[i].second--;
                    mutareParanteze(parantezeAcolade[i].second);
                }
            }
        }
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == ':'){
                numere[i] = numere[i]/numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
            }
        }
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == '*'){
                numere[i] = numere[i]*numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
            }
        }
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == '-'){
                numere[i] = numere[i]-numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
                i = -1;
            }
        }
        for(int i = 0; i < operatii.size(); i++){
            if(operatii[i] == '+'){
                numere[i] = numere[i]+numere[i+1];
                numere.erase(numere.begin() + i + 1);
                operatii.erase(operatii.begin() + i);
                i = -1;
            }
        }
    }
}

int main() {
    menu();
    citire();
//    for(int i = 0; i < numere.size()-1; i++){
//        cout << numere[i] << operatii[i];
//    }
//    cout << numere[numere.size()-1] << endl;


    solutie();

    //REZULTAT
    for(int i = 0; i < numere.size()-1; i++){
        cout << numere[i] << operatii[i];
    }
    cout << numere[numere.size()-1] << endl;
    return 0;
}