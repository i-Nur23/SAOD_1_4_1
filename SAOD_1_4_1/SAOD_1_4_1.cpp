#include <iostream>
#include <locale>
#include <set>

using namespace std;

struct BiListItem
{
    int info;
    BiListItem* pNext;
    BiListItem* pPrev;
};

BiListItem* pHead;

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int CheckedInput() // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        break;
    }
    return choice;
}

void InitList() 
{
    pHead->info = 0;
    pHead->pNext = pHead;
    pHead->pPrev = pHead;
}

bool isEmpty()
{
    if (pHead->pNext == pHead)
    {
        return true;
    }
    return false;
}

void PrintList(bool isDirect)
{
    if (isDirect)
    {
        cout << "Список в прямом направлении: ";
        BiListItem* Current = pHead->pNext;
        while (Current != pHead)
        {
            cout << Current->info << " ";
            Current = Current->pNext;
        }
    }
    else
    {
        cout << "Список в обратном направлении: ";
        BiListItem* Current = pHead->pPrev;
        while (Current != pHead)
        {
            cout << Current->info << " ";
            Current = Current->pPrev;
        }
    }
}

BiListItem* Search(bool isDirect, int infoToSearch)
{
    if (isDirect)
    {
        BiListItem* Current = pHead->pNext;
        while (Current != pHead)
        {
            if (Current->info == infoToSearch)
            {
                return Current;
            }
            Current = Current->pNext;
        }
    }
    else
    {
        cout << "Список в обратном направлении: ";
        BiListItem* Current = pHead->pPrev;
        while (Current != pHead)
        {
            if (Current->info == infoToSearch)
            {
                return Current;
            }
            Current = Current->pPrev;
        }
    }
    return NULL;
}

void Add(bool isBefore, BiListItem* newItem, int elemInList)
{
    BiListItem* pTemp = Search(true,elemInList);
    if (isBefore)
    {
        newItem->pPrev = pTemp->pPrev;
        newItem->pNext = pTemp;
        (pTemp->pPrev)->pNext = newItem;
        pTemp->pPrev = newItem;
    }
    else
    {
        newItem->pNext = pTemp->pNext;
        newItem->pPrev = pTemp;
        (pTemp->pNext)->pPrev = newItem;
        pTemp->pNext = newItem;
    }
}

void Add(BiListItem* newItem)
{
    int infoToAdd;
    cout << "Введите элемент, который хотели бы добавить: "; infoToAdd = CheckedInput();
    newItem->info = infoToAdd;
    pHead->pNext = newItem; pHead->pPrev = newItem;
    newItem->pNext = pHead; newItem->pPrev = pHead;
}

void Delete(int infoToDelete)
{
    BiListItem* delItem = Search(true, infoToDelete);
    if (delItem == NULL)
    {
        cout << "Заданного элемента нет в списке. "; return;
    }
    (delItem->pPrev)->pNext = delItem->pNext;
    (delItem->pNext)->pPrev = delItem->pPrev;
    delete delItem;
}

void DeleteAll()
{
    if (!isEmpty())
    {
        BiListItem* pTemp;
        BiListItem* pCur = pHead->pNext;;
        while (pCur != pHead)
        {
            pTemp = pCur;
            pCur = pTemp->pNext;
            delete pTemp;
        }
    }
    delete pHead;
}

void CallMenu()
{
    bool work = true;
    int choice;
    while (work)
    {
        cout << "Выбор действия:\n1 - Вывод списка в прямом направлении\n2 - Вывод списка в обратном направлении\n3 - Поиск элемента в прямом направлении\n";
        cout << "4 - Поиск элемента в обратном направлении\n5 - Добавление элемента перед заданным\n6 - Добавление элемента после заданного\n7 - Удаление элемента\n";
        cout << "8 - Завершение работы\n";
        cout << "Действие: "; choice = CheckedInput(1, 8);
        int infoToSearch, infoToAdd, elemInList;
        BiListItem* newItem;
        switch (choice)
        {
        case 1:
            if (isEmpty())
            {
                cout << "Список пустой.\n\n"; break;
            }
            PrintList(true);
            cout << "\n\n";
            break;
        case 2:
            if (isEmpty())
            {
                cout << "Список пустой.\n\n"; break;
            }
            PrintList(false);
            cout << "\n\n";
            break;
            cout << "\n\n";
            break;
        case 3:
            cout << "Введите элемент, который требуется найти: "; infoToSearch = CheckedInput();
            if (Search(true, infoToSearch) != NULL)
            {
                cout <<"Элемент " << infoToSearch <<" нашёлся.";
            }
            else
            {
                cout << "Такого элемента в списке нет.";
            }
            cout << "\n\n";
            break;
        case 4:
            cout << "Введите элемент, который требуется найти: "; infoToSearch = CheckedInput();
            if (Search(false, infoToSearch) != NULL)
            {
                cout << "Элемент " << infoToSearch << " нашёлся.";
            }
            else
            {
                cout << "Такого элемента в списке нет.";
            }
            cout << "\n\n";
            break;
        case 5:
            try
            {
                newItem = new BiListItem;
            }
            catch (const std::exception&)
            {
                cout << "Список переполнен\n\n"; break;
            }
            
            if (isEmpty())
            {
                Add(newItem); cout << "\n\n"; break;
            }
            
            cout << "Введите элемент, перед которым хотите добавить: "; elemInList = CheckedInput();
            if (Search(true, elemInList) == NULL)
            { 
                cout << "Заданного элемента нет в списке\n\n"; break;
            }
            
            cout << "Введите элемент, который хотели бы добавить: "; infoToAdd = CheckedInput();
            newItem->info = infoToAdd;
            Add(true, newItem, elemInList);
            cout << "\n\n";
            break;
        case 6:
            try
            {
                newItem = new BiListItem;
            }
            catch (const std::exception&)
            {
                cout << "Список переполнен\n\n"; break;
            }
            
            if (isEmpty())
            {
                Add(newItem); cout << "\n\n"; break;
            }
            
            cout << "Введите элемент, после которого хотите добавить: "; elemInList = CheckedInput();
            if (Search(true, elemInList) == NULL)
            {
                cout << "Заданного элемента нет в списке\n\n"; break;
            }
            
            cout << "Введите элемент, который хотели бы добавить: "; infoToAdd = CheckedInput();
            newItem->info = infoToAdd;
            Add(false, newItem, elemInList);
            cout << "\n\n";
            break;
        case 7:
            cout << "Введите элемент, который хотели бы удалить: "; Delete(CheckedInput());
            cout << "\n\n";
            break;
        case 8:
            work = false;
            DeleteAll();
            break;
        default:
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    pHead = new BiListItem;
    InitList();
    CallMenu();
}