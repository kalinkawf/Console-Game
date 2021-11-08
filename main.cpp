#include <iostream>
#include <conio.h>

using namespace std;

const int L = 10, iloscPionow = 4;
int pola[L][L];

bool poprawnaKomenda(char komenda[2], int &x, int &y, bool &przerwano)
{
    if(komenda[0] == 'x')
    {
        przerwano = true;
        return false;
    }

    x = komenda[0] - 'a';
    if(x < 0)
        x = komenda[0] - 'A';

    if(x < 0)
        return false;
    if(x >= L)
        return false;

    y = komenda[1] - '1';
    if(y < 0)
        return false;
    if(y == 0)
        if(komenda[2] == '0')
            y = 9;
    if(y >= L)
        return false;
    return true;
}

bool ruch(bool bialyRuch, int &x, int &y, bool &przerwano)
{
    char komenda[3];
    int x1, y1, pole;

    cout << "Ruch gracza " << (bialyRuch ? "bialego (O)" : "czarnego (#)") << endl;
    cout << "Ktorym pionem ruszasz: ";
    cin >> komenda;
    if(!poprawnaKomenda(komenda, x1, y1, przerwano))
        return false;

    pole = pola[x1][y1];

    if(pole == 0)
        return false;
    if(bialyRuch)
    {
        if(pole != 1)
            return false;
    }
    else
    {
        if(pole != 2)
            return false;
    }

    int x2, y2;
    cout << "na ktore pole sie poruszasz?: ";
    cin >> komenda;
    if(!poprawnaKomenda(komenda, x2, y2, przerwano))
        return false;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if(dx == 0 && dy == 0)
        return false;

    if(dx == 0)
    {
        int k = 1;
        if(dy < 0)
            k = -1;

        for(int i = y1 + k; i != y2; i += k)
        {
            if(pola[x1][i] != 0)
                return false;
        }
    }
    else if(dy == 0)
    {
        int k = 1;
        if(dx < 0)
            k = -1;

        for(int i = x1 + k; i != x2; i += k)
        {
            if(pola[i][y1] != 0)
                return false;
        }
    }
    else if(dy == dx)
    {
        int k = 1;
        if(dx < 0)
            k = -1;

        for(int i = k; i != dx; i += k)
        {
            if(pola[x1 + i][y1 + i] != 0)
                return false;
        }
    }
    else if(dy == -dx)
    {
        int k = 1;
        if(dx < 0)
            k = -1;

        for(int i = k; i != dx; i += k)
        {
            if(pola[x1 + i][y1 - i] != 0)
                return false;
        }
    }
    else
        return false;

    pola[x2][y2] = pole;
    pola[x1][y1] = 0;

    x1 = x2;
    y1 = y2;

    cout << "w ktore pole strzelasz?: ";
    cin >> komenda;
    if(!poprawnaKomenda(komenda, x2, y2, przerwano))
        return false;

    dx = x2 - x1;
    dy = y2 - y1;

    if(dx == 0 && dy == 0)
        return false;

    if(dx == 0 || dy == 0 || dy == dx || dy == -dx)
    {
        if(pola[x2][y2] != 0)
            return false;
    }
    else
        return false;

    pola[x2][y2] = -1;

    return true;
}

int main()
{
    pola[3][0] = 1;
    pola[6][0] = 1;
    pola[0][3] = 1;
    pola[9][3] = 1;
    pola[0][6] = 2;
    pola[9][6] = 2;
    pola[3][9] = 2;
    pola[6][9] = 2;

    bool przerwano = false;
    bool wygrana = false;
    bool graTrwa = true;
    bool czyBialy = true;
    int x = -1, y = -1;

    cout << "Mozna wyjsc w kazdej chwili wpisujac 'x'" << endl;
    getch();

    while(graTrwa)
    {
        int pole;
        for(int i = L-1; i >= 0; i--)
        {
            cout << "  +";
            for(int j = 0; j < L; j++)
                cout << "-----+";
            cout << endl << "  |";
            for(int j = 0; j < L; j++)
            {
                pole = pola[j][i];
                if(pole == 0)
                    cout << "     |";
                else if(pole == 1)
                    cout << " OOO |";
                else if(pole == 2)
                    cout << " ### |";
                else
                    cout << ".....|";
            }
            cout << endl << (i+1) << (i == L-1 ? "" : " ") << "|";
            for(int j = 0; j < L; j++)
            {
                pole = pola[j][i];
                if(pole == 0)
                    cout << "     |";
                else if(pole == 1)
                    cout << " OOO |";
                else if(pole == 2)
                    cout << " ### |";
                else
                    cout << ".....|";
            }
            cout << endl;
        }
        cout << "  +";
        for(int j = 0; j < L; j++)
            cout << "-----+";
        cout << endl << endl << "  ";
        for(int j = 0; j < L; j++)
            cout << "   " << (char)(j + 'A') << "  ";
        cout << endl << endl;

        while(!ruch(czyBialy, x, y, przerwano))
        {
            if(przerwano)
            {
                cout << "Przerwano gre" << endl;
                break;
            }
            cout << "Wykryto nie poprawny ruch" << endl << "Wykonaj ruch jeszcze raz" << endl << endl;
        }
        if(przerwano)
            break;

        int czz = 0, blz = 0;
        for(int i = 0; i < L; i++)
        {
            for(int j = 0; j < L; j++)
            {
                if(pola[i][j] == 1)
                {
                    if(j != 0)
                    {
                        if(i != 0)
                        {
                            if(pola[i-1][j-1] == 0)
                                continue;
                        }
                        if(pola[i][j-1] == 0)
                            continue;
                        if(i != L-1)
                        {
                            if(pola[i+1][j-1] == 0)
                                continue;
                        }
                    }
                    if(i != 0)
                    {
                        if(pola[i-1][j] == 0)
                            continue;
                    }
                    if(i != L-1)
                    {
                        if(pola[i+1][j] == 0)
                            continue;
                    }
                    if(j != L-1)
                    {
                        if(i != 0)
                        {
                            if(pola[i-1][j+1] == 0)
                                continue;
                        }
                        if(pola[i][j+1] == 0)
                            continue;
                        if(i != L-1)
                        {
                            if(pola[i+1][j+1] == 0)
                                continue;
                        }
                    }

                    blz++;
                    if(blz == iloscPionow)
                        wygrana = true;
                }
                else if(pola[i][j] == 2)
                {
                    if(j != 0)
                    {
                        if(i != 0)
                        {
                            if(pola[i-1][j-1] == 0)
                                continue;
                        }
                        if(pola[i][j-1] == 0)
                            continue;
                        if(i != L-1)
                        {
                            if(pola[i+1][j-1] == 0)
                                continue;
                        }
                    }
                    if(i != 0)
                    {
                        if(pola[i-1][j] == 0)
                            continue;
                    }
                    if(i != L-1)
                    {
                        if(pola[i+1][j] == 0)
                            continue;
                    }
                    if(j != L-1)
                    {
                        if(i != 0)
                        {
                            if(pola[i-1][j+1] == 0)
                                continue;
                        }
                        if(pola[i][j+1] == 0)
                            continue;
                        if(i != L-1)
                        {
                            if(pola[i+1][j+1] == 0)
                                continue;
                        }
                    }

                    czz++;
                    if(czz == iloscPionow)
                        wygrana = true;
                }
            }
        }
        if(wygrana)
        {
            cout << "Koniec gry" << endl << "Jeden z graczy nie ma mozliwosci ruchu" << endl;
            graTrwa = false;
        }
        czyBialy = !czyBialy;
    }
    getch();
    return 0;
}
