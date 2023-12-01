#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#define righe 11
#define colonne 21

int x, y;
int N_code = 0, count = 0;

typedef struct lista
{
    int x;
    int y;
    struct lista *next;
} lista_t;

lista_t *Plista;

void Stampa_Coda(char arr[][colonne], int a, int b)
{
    if (N_code == 0)
    {
        arr[a][b] = 'O';
        arr[x][y] = ' ';
        x = a;
        y = b;
        Plista->x = x;
        Plista->y = y;
    }
    else
    {
        lista_t *CPlista = Plista->next;
        arr[a][b] = 'O';
        x = a;
        y = b;
        a = Plista->x;
        b = Plista->y;
        Plista->x = x;
        Plista->y = y;

        while (CPlista->next != NULL)
        {
            int as = a, bs = b;
            arr[a][b] = 'o';
            a = CPlista->x;
            b = CPlista->y;
            CPlista->x = as;
            CPlista->y = bs;
            CPlista = CPlista->next;
        }
        arr[a][b] = 'o';
        arr[CPlista->x][CPlista->y] = ' ';
        CPlista->x = a;
        CPlista->y = b;
    }
}

void Aggiungi_e_Stampa_Coda(char arr[][colonne], int a, int b)
{
    if (N_code == 0)
    {
        arr[a][b] = 'O';
        arr[x][y] = ' ';
        x = a;
        y = b;
        Plista->x = x;
        Plista->y = y;
    }
    else
    {
        int as, bs;

        lista_t *CPlista = Plista;
        while (CPlista->next != NULL)
        {
            CPlista = CPlista->next;
        }
        CPlista->next = (lista_t *)malloc(sizeof(lista_t));
        CPlista->next->next = NULL;
        CPlista->next->x = CPlista->x;
        CPlista->next->y = CPlista->y;

        CPlista = Plista->next;

        arr[a][b] = 'O';
        x = a;
        y = b;
        a = Plista->x;
        b = Plista->y;
        Plista->x = x;
        Plista->y = y;

        while (CPlista->next != NULL)
        {
            as = a;
            bs = b;
            arr[a][b] = 'o';
            a = CPlista->x;
            b = CPlista->y;
            CPlista->x = as;
            CPlista->y = bs;
            CPlista = CPlista->next;
        }
        arr[a][b] = 'o';
        arr[CPlista->x][CPlista->y] = 'o';
    }
}

void Elimina_Coda(char arr[][colonne], int a, int b)
{
    lista_t *CPlista = Plista;
    lista_t *CCPlista;
    int trovatiXY = 0;

    while(trovatiXY == 0 && CPlista->next != NULL)
    {
        if(CPlista->next->x == a && CPlista->next->y == b)
            trovatiXY = 1;
        CPlista = CPlista->next;
    }

    CCPlista = CPlista;
    while(CCPlista->next != NULL)
    {
        CCPlista = CCPlista->next;
        arr[CCPlista->x][CCPlista->y] = ' ';
    }

    free(CPlista->next);
    CPlista->next = NULL; 
}

void Dimezza_Coda(char arr[][colonne])
{
    lista_t *CPlista = Plista;
    N_code = (int) N_code/2;
    for(int i = 0; i < N_code; i++)
    {
        CPlista = CPlista->next;
    }

    lista_t *CCPlista = CPlista;

    while(CCPlista != NULL)
    {
        arr[CCPlista->x][CCPlista->y] = ' ';
        CCPlista = CCPlista->next;
    }

    CPlista->next = NULL;
}

void define_muro(char arr[][colonne])
{
    for (int i = 0; i < righe; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            if (arr[i][j] != 'O' && arr[i][j] != '_')
            {
                if (i == 1 || j == 1 || i == righe - 2 || j == colonne - 2)
                    arr[i][j] = '#'; // muro
                else if (arr[i][j] == 'T' || arr[i][j] == '$' || arr[i][j] == '!')
                {
                }
                else
                    arr[i][j] = ' ';
            }
            if (i == 0 || i == righe - 1)
                arr[i][j] = '-'; // limite
            if (j == 0 || j == colonne - 1)
                arr[i][j] = '|';
        }
    }
}

void mosseT(char arr[][colonne], char l)
{
    if (l == 's')
    {
        if (arr[x + 1][y] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x + 1, y);
        }
        else if (arr[x + 1][y] == 'o')
        {
            Elimina_Coda(arr, x + 1, y);
            Stampa_Coda(arr, x + 1, y);
        }
        else if (arr[x + 1][y] != '-')
        {
            if (arr[x + 1][y] == '#')
                count--;
            Stampa_Coda(arr, x + 1, y);
        }
    }
    else if (l == 'w')
    {
        if (arr[x - 1][y] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x - 1, y);
        }
        else if (arr[x - 1][y] == 'o')
        {
            Elimina_Coda(arr, x - 1, y);
            Stampa_Coda(arr, x - 1, y);
        }
        else if (arr[x - 1][y] != '-')
        {
            if (arr[x - 1][y] == '#')
                count--;
            Stampa_Coda(arr, x - 1, y);
        }
    }
    else if (l == 'd')
    {
        if (arr[x][y + 1] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x, y + 1);
        }
        else if (arr[x][y + 1] == 'o')
        {
            Elimina_Coda(arr, x, y + 1);
            Stampa_Coda(arr, x, y + 1);
        }
        else if (arr[x][y + 1] != '|')
        {
            if (arr[x][y + 1] == '#')
                count--;
            Stampa_Coda(arr, x, y + 1);
        }
    }
    else if (l == 'a')
    {
        if (arr[x][y - 1] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x, y - 1);
        }
        else if (arr[x][y - 1] == 'o')
        {
            Elimina_Coda(arr, x, y - 1);
            Stampa_Coda(arr, x, y - 1);
        }
        else if (arr[x][y - 1] != '|')
        {
            if (arr[x][y - 1] == '#')
                count--;
            Stampa_Coda(arr, x, y - 1);
        }
    }
}

void mosseS(char arr[][colonne], char l)
{
    if (l == 's')
    {
        if (arr[x + 1][y] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x + 1, y);
        }
        else if (arr[x + 1][y] == 'o')
        {
            Elimina_Coda(arr, x + 1, y);
            Stampa_Coda(arr, x + 1, y);
        }
        else if (arr[x + 1][y] != '#' && arr[x + 1][y] != '-')
            Stampa_Coda(arr, x + 1, y);
    }
    else if (l == 'w')
    {
        if (arr[x - 1][y] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x - 1, y);
        }
        else if (arr[x - 1][y] == 'o')
        {
            Elimina_Coda(arr, x - 1, y);
            Stampa_Coda(arr, x - 1, y);
        }
        else if (arr[x - 1][y] != '#' && arr[x - 1][y] != '-')
            Stampa_Coda(arr, x - 1, y);
    }
    else if (l == 'd')
    {
        if (arr[x][y + 1] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x, y + 1);
        }
        else if (arr[x][y + 1] == 'o')
        {
            Elimina_Coda(arr, x, y + 1);
            Stampa_Coda(arr, x, y + 1);
        }
        else if (arr[x][y + 1] != '#' && arr[x][y + 1] != '|')
            Stampa_Coda(arr, x, y + 1);
    }
    else if (l == 'a')
    {
        if (arr[x][y - 1] == '$')
        {
            N_code++;
            Aggiungi_e_Stampa_Coda(arr, x, y - 1);
        }
        else if (arr[x][y - 1] == 'o')
        {
            Elimina_Coda(arr, x, y - 1);
            Stampa_Coda(arr, x, y - 1);
        }
        else if (arr[x][y - 1] != '#' && arr[x][y - 1] != '|')
            Stampa_Coda(arr, x, y - 1);
    }
}

void print(char arr[][colonne])
{
    printf("\033[H\033[J");
    for (int k = 0; k < righe; k++)
    {
        for (int n = 0; n < colonne; n++)
            printf("%c", arr[k][n]);
        printf("\n\r");
    }
    printf("\n\r");
}

int main()
{
    char arr[righe][colonne];
    srand(time(NULL));

    x = 2 + rand() % (7);
    y = 1;
    int tx = 2 + rand() % (7);
    int ty = 2 + rand() % (17);
    int ex = 2 + rand() % (7);
    int ey = colonne - 2;
    int ix = 2 + rand() % (7);
    int iy = 2 + rand() % (17);

    int score = 0;
    int vita = 1000;
    bool uscita = 0;
    char l;

    arr[x][y] = 'O';
    arr[tx][ty] = 'T';
    arr[ex][ey] = '_';
    arr[ix][iy] = '!';
    for (int i = 0; i < 5; i++)
        arr[2 + rand() % (7)][2 + rand() % (17)] = '$';

    Plista = (lista_t *)malloc(sizeof(lista_t));
    Plista->next = NULL;
    Plista->x = x;
    Plista->y = y;

    define_muro(arr);
    print(arr);

    initscr();

    while (uscita == 0)
    {

        l = getch();

        if (arr[x][y] == arr[tx][ty])
        {
            count += 3;
            tx = -1;
            ty = -1;
        } else if (arr[x][y] == arr[ix][iy])
        {
            Dimezza_Coda(arr);
            ix = -1;
            iy = -1;
        }
        if (count == 0)
            mosseS(arr, l);
        else
            mosseT(arr, l);
        print(arr);
        printf("trapani %d\n\r", count);
        printf("vita %d\n\r", vita);
        printf("score %d\n\r", score);

        if (arr[x][y] == arr[ex][ey])
            uscita = 1;
    }

    printf("\n\r");

    return 0;
}
