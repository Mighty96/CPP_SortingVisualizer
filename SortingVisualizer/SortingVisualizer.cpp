#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

// 커서숨기기
void CursorView(char show)
{
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

// 콘솔 커서 이동
void gotoxy(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 카운트다운 출력
void countDown(int length)
{
    int timer = 3;
    while (timer > 0)
    {
        gotoxy(0, length);
        std::cout << timer << "초 후 시작합니다." << '\n';
        Sleep(1000);
        timer--;
    }
    gotoxy(0, length);
    std::cout << "                                        \n";
}

// 초기셋팅
void init(int& select, int& length)
{
    system("cls");
    gotoxy(0, 0);
    Sleep(10);

    std::cout <<
        "--------------------------------------\n" <<
        "| 1. BubbleSort                      |\n" <<
        "| 2. SelectSort                      |\n" <<
        "| 3. InsertSort                      |\n" <<
        "| 4. MergeSort                       |\n" <<
        "| 5. HeapSort                        |\n" <<
        "| 6. QuickSort                       |\n" <<
        "--------------------------------------\n";
    std::cout << "원하는 정렬을 선택해주세요.(1~6)" << '\n';
    std::cin >> select;
    while (select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6)
    {
        std::cout << "올바른 번호를 입력해주세요.(1~6)" << '\n';
        std::cin >> select;
    }

    std::cout << "배열의 길이를 설정해주세요.(최솟값 : 10 | 최댓값 : 50)" << '\n';
    std::cin >> length;
    while (length < 10 || length > 50)
    {
        std::cout << "올바른 길이를 입력해주세요. (10~50)" << '\n';
        std::cin >> length;
    }
    system("cls");
}

// 랜덤배열 생성
void makeArr(int* arr, int length)
{
    int temp;
    srand((unsigned int)time(NULL));

    for (int i = 1; i <= length; i++)
    {
        arr[i] = i;
    }

    for (int i = 1; i <= length * 3; i++)
    {
        int x = rand() % length + 1;
        int y = rand() % length + 1;

        if (x != y)
        {
            temp = arr[x];
            arr[x] = arr[y];
            arr[y] = temp;
        }
    }
}

// 바뀐 인덱스 새로 그리기
void draw(int* arr, int idx, int length)
{
    std::string temp;

    temp = "";

    for (int k = 1; k <= arr[idx]; k++)
    {
        temp += "■";
    }
    for (int k = arr[idx] + 1; k <= length; k++)
    {
        temp += "  ";
    }

    gotoxy(0, idx - 1);
    std::cout << temp << '\n';
}

// BubbleSort
void bubbleSort(int* arr, int length)
{
    int temp;

    for (int i = length - 1; i > 1; i--)
    {
        for (int j = 1; j <= i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                draw(arr, j, length);
                draw(arr, j + 1, length);

                Sleep(700 / length);
            }
        }
    }
}

// SelectSort
void selectSort(int* arr, int length)
{
    int idx;
    int temp;

    for (int i = 1; i < length; i++)
    {
        idx = i;
        for (int j = i + 1; j <= length; j++)
        {
            if (arr[idx] > arr[j])
            {
                idx = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[idx];
        arr[idx] = temp;

        draw(arr, i, length);
        draw(arr, idx, length);

        Sleep(200);
    }
}

// InserSort
void insertSort(int *arr, int length)
{
    int temp;

    for (int i = 1; i <= length; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if (arr[j] > arr[i])
            {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;

                draw(arr, i, length);
                draw(arr, j, length);

                Sleep(700 / length);
            }
        }
    }
}

// MergeSort 1
void merge(int* arr, int left, int right, int length)
{
    int mid = (left + right) / 2;
    int new_left = left;
    int new_right = mid + 1;
    int temp_arr[51] = { 0 };
    int idx = left;

    while (new_left <= mid && new_right <= right)
    {
        if (arr[new_left] < arr[new_right])
        {
            temp_arr[idx++] = arr[new_left++];
        }
        else
        {
            temp_arr[idx++] = arr[new_right++];
        }
    }

    while (new_left <= mid)
    {
        temp_arr[idx++] = arr[new_left++];
    }
    
    while (new_right <= right)
    {
        temp_arr[idx++] = arr[new_right++];
    }

    for (int i = left; i <= right; i++)
    {
        arr[i] = temp_arr[i];
        draw(arr, i, length);
        Sleep(1000 / length);
    }
}

// MergeSort 2
void mergeSort(int *arr, int left, int right, int length)
{
    int mid = (left + right) / 2;

    if (left < right)
    {
        mergeSort(arr, left, mid, length);
        mergeSort(arr, mid + 1, right, length);
        merge(arr, left, right, length);
    }
}

// HeapSort
void heapSort(int *arr, int length)
{
    int node;
    int temp;

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 1; j <= length - i; j++)
        {
            node = j;

            while (node / 2 >= 1)
            {
                if (arr[node] > arr[node / 2])
                {
                    temp = arr[node];
                    arr[node] = arr[node / 2];
                    arr[node / 2] = temp;

                    draw(arr, node, length);
                    draw(arr, node / 2, length);

                    node /= 2;
                    Sleep(700 / length);
                }
                else
                {
                    break;
                }
            }
        }
        temp = arr[1];
        arr[1] = arr[length - i];
        arr[length - i] = temp;

        draw(arr, 1, length);
        draw(arr, length - i, length);

        Sleep(700 / length);
    }
}

// QuickSort
void quickSort(int *arr, int left, int right, int length)
{
    if (left >= right)
    {
        return;
    }
    int pivot = left;
    int new_left = left + 1;
    int new_right = right;
    int temp;
    while (new_left <= new_right)
    {
        if (arr[new_left] < arr[pivot])
        {
            new_left++;
        }
        else if (arr[new_right] > arr[pivot])
        {
            new_right--;
        }
        else
        {
            temp = arr[new_left];
            arr[new_left] = arr[new_right];
            arr[new_right] = temp;

            draw(arr, new_left, length);
            draw(arr, new_right, length);

            Sleep(1500 / length);

            new_left++;
            new_right--;
        }
    }

    temp = arr[new_right];
    arr[new_right] = arr[pivot];
    arr[pivot] = temp;

    draw(arr, new_right, length);
    draw(arr, pivot, length);

    Sleep(1500 / length);

    if (left < right)
    {
        quickSort(arr, left, new_right - 1, length);
        quickSort(arr, new_left, right, length);
    }
}

int main()
{
    int select = 0;
    int length = 0;
    int arr[51];

    CursorView(false);
    system("mode con: cols=120 lines=55");


    while (true)
    {
        init(select, length);

        makeArr(arr, length);

        for (int i = 1; i <= length; i++)
        {
            draw(arr, i, length);
        }
       
        countDown(length);

        /*
        정렬 분기
        */
        switch (select)
        {
        case 1:
            bubbleSort(arr, length);
            break;
        case 2:
            selectSort(arr, length);
            break;
        case 3:
            insertSort(arr, length);
            break;
        case 4:
            mergeSort(arr, 1, length, length);
            break;
        case 5:
            heapSort(arr, length);
            break;
        case 6:
            quickSort(arr, 1, length, length);
            break;
        }

        gotoxy(0, length);
        std::cout << "정렬완료. 3초후 초기화면으로 돌아갑니다.";
        Sleep(3000);
    }
}