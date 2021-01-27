// 青蛙过河:

#include <stdio.h>

void print_road(int arrRoad[], int nLen)
{
    int i = 0;

    for (i = 0; i < nLen; i++)
    {
        if (arrRoad[i] < 0)
            printf("-> ");
        else if (arrRoad[i] > 0)
            printf("<- ");
        else
            printf("O ");
    }
    printf("\n\n");
}

void swap(int *nN1, int *nN2)
{
    int nTmp = 0;

    nTmp = *nN1;
    *nN1 = *nN2;
    *nN2 = nTmp;
}

// left side the number is less than 0
// right side the number is bigger than 0
// empty grid is 0
int move_frog(int arrRoad[], int nLen, int nEmptyGrid)
{
    int i = 0;
    int bMove = 1;
    int nSuccessCount = 0;

    // move the left side
    while (nSuccessCount < nLen - 1)
    {
        bMove = 1;
        for (i = 0; i < nEmptyGrid && bMove; i++)
        {
            if ((arrRoad[nEmptyGrid - 2] < 0) && (arrRoad[nEmptyGrid - 1] > 0))
            {
                swap(&arrRoad[nEmptyGrid - 2], &arrRoad[nEmptyGrid]);
                if (nEmptyGrid == nLen - 1)
                    nSuccessCount++;
                nEmptyGrid -= 2;
                print_road(arrRoad, nLen);
                bMove = 0;
                break;
            }
        }

        for (i = nLen - 1; i > nEmptyGrid && bMove; i--)
        {
            if ((arrRoad[nEmptyGrid + 2] > 0) && (arrRoad[nEmptyGrid + 1] < 0))
            {
                swap(&arrRoad[nEmptyGrid + 2], &arrRoad[nEmptyGrid]);
                if (nEmptyGrid == 0)
                    nSuccessCount++;

                print_road(arrRoad, nLen);
                nEmptyGrid += 2;
                bMove = 0;
                break;
            }
        }

        for (i = 0; i < nEmptyGrid && bMove; i++)
        {
            if ((arrRoad[nEmptyGrid - 1] < 0) && (nEmptyGrid < nLen - 2 && (arrRoad[nEmptyGrid - 2]) != arrRoad[nEmptyGrid + 1]))
            {
                swap(&arrRoad[nEmptyGrid - 1], &arrRoad[nEmptyGrid]);

                if (nEmptyGrid == nLen - 1)
                    nSuccessCount++;

                print_road(arrRoad, nLen);
                nEmptyGrid -= 1;
                bMove = 0;
                break;
            }
        }

        for (i = nLen - 1; i > nEmptyGrid && bMove; i--)
        {
            if ((arrRoad[nEmptyGrid + 1] > 0) && (nEmptyGrid > 0 && arrRoad[nEmptyGrid + 2] != arrRoad[nEmptyGrid - 1]))
            {
                swap(&arrRoad[nEmptyGrid + 1], &arrRoad[nEmptyGrid]);

                if (nEmptyGrid == 0)
                    nSuccessCount++;

                print_road(arrRoad, nLen);
                nEmptyGrid += 1;
                bMove = 0;
                break;
            }
        }
    }
}

int main()
{
    int arrTest[7] = {-1, -1, -1, 0, 1, 1, 1};
    int n = 0;

    print_road(arrTest, 7);
    move_frog(arrTest, 7, 3);

    scanf("%d", &n);
    return 0;
}