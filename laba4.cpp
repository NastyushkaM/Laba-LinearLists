#include <iostream>
#include <iomanip>
using namespace std;

// cтруктура для представления элемента списка
struct List {
    double data;         // элемент
    List* next;          // указатель на следующий элемент
    List* prev;          // указатель на предыдущий элемент
};

// рекурсивная ф-я вывода элемента списка с заданным индексом
void PrintIndex(List* head, int index)
{
    List* ptr = head;  // временный указатель на начало списка
    int current_index = 0;  // текущий индекс элемента

    // перебор элементов списка
    while (ptr != nullptr)
    {
        if (current_index == index)
        {
            // при достижении заданного индекса - вывод значения и завершение цикла
            cout << fixed << setprecision(1) << "[" << index << "] -- " << ptr->data << endl; // с одной цифрой после запятой
            return;
        }
        ptr = ptr->next;  // переход к следующему элементу списка
        current_index++;
    }//while

    cout << "Элемент с индексом " << index << " не найден" << endl;
}//PrintIndex

// вывод списка
void PrintList(List* head, int size)
{
    for (int i = 0; i < size; i++)
    {
        PrintIndex(head, i); // рекурсивный вызов функции
    }
}

// добавление нового элемента в конец кольцевого двусвязного списка
void Append(List*& head, double newData)
{
    // создание нового элемента
    List* newList = new List;  // выделение памяти под новый элемент
    newList->data = newData;   // присвоение новому элементу значения

    // следующий и предыдущий элементы пока что отсутствуют
    newList->next = nullptr;
    newList->prev = nullptr;

    // проверка, пустой ли список
    if (head != nullptr)
    {
        List* temp = head;

        // переход к последнему элементу списка
        while (temp->next != head)
        {
            temp = temp->next;
        }

        // добавление нового элемента в конец
        temp->next = newList;
        newList->prev = temp;

        // связь между первыми и последним элементами (т.к. кольцевой список)
        newList->next = head;
        head->prev = newList;
    }

    else
    {
        // если список пуст, новый элемент становится головой списка 
        // и будет указывать сам на себя (т.к. кольцевой список)
        head = newList;
        head->next = head;
        head->prev = head;
    }
}//Append

// удаление списка
void DeleteList(List*& head)
{
    List* current = head; // текущий элемент
    List* temp; // временный указатель для удаляемого элемента

    // проверка, пустой ли список
    if (!current)
    {
        cout << "Список пустой \n";
        return;
    }

    // удаление всех элементов кроме последнего
    while (current->next != head)
    {
        temp = current; // временно сохраняем текущий элемент
        current = current->next; // переход к следующему
        delete temp; // удаление предыдущего элемента
    }

    delete current; // удаление последнего элемента
    head = nullptr;  // обнуление указателя на голову 
}//DeleteList

// поиск элемента в списке
int Search(struct List* head, double x)
{
    struct List* temp = head; // временная переменная

    int count = 0; // индекс элемента 
    int flag = 0; // флаг для обозначения того, что элемент был найден или нет   

    // проверка, пустой ли список
    if (temp == NULL)
        return -1;

    else
    {
        /*перемещение указателя temp будет происходить до тех пор,
        пока temp->next не станет равен head, т.е. пока не пройден весь список*/
        while (temp->next != head)
        {
            count++;
            if (temp->data == x) // если элемент найден
            {
                flag = 1; // элемент найден
                count--; // тк счет начинается с нуля 
                break;
            }

            temp = temp->next; // сдвиг на следующий элемент
        }//while

        // проверка, содержится ли значение в последнем элементе списка
        if (temp->data == x)
        {
            count++;
            flag = 1; // элемент найден
        }

        if (flag == 1)
            cout << "Элемент " << x << " найден с индексом [" << count - 1 << "]" << endl;
        else
            cout << "Элемент " << x << " не найден" << endl;
    }
}//Search

// вставка нового элемента в список
void Add(List*& head, double data_new, int position)
{
    List* new_elem = new List;  // создание нового элемента

    new_elem->data = data_new; // присвоение значения  

    /*если список пуст или позиция - 0,
    вставка происходит в начало списка*/
    if (head == nullptr || position == 0)
    {
        new_elem->prev = nullptr; // указатель на предыдущий элемент для нового 
        new_elem->next = head; // указатель на следующий элемент для нового 

        // если список не пуст
        if (head != nullptr)
        {
            // обновление указателя на предыдущий элемент у текущей головы списка
            head->prev = new_elem;
        }

        head = new_elem;  // новый элемент - голова списка
        return;
    }

    List* temp = head;  // текущая голова списка
    int count = 0;

    // поиск элемента на позиции position
    while (temp != nullptr && count < position)
    {
        temp = temp->next;  // переход к следующему элементу
        count++;
    }

    // вставка нового элемента на позицию position
    new_elem->prev = temp->prev; // указатель на предыдущий элемент для нового 
    new_elem->next = temp; // указатель на следующий элемент для нового 

    /*если у предыдущего элемента есть следующий,
    обновляется его указателя на новый элемент*/
    if (temp->prev != nullptr)
        temp->prev->next = new_elem;

    else
        head = new_elem;  // голова - новый элемент

    temp->prev = new_elem; // указатель на предыдущий элемент для текущего 
}//Add

// удаление элемента из начала списка
void DeleteFirst(List*& head)
{
    // проверка, пустой ли список
    if (head == nullptr)
    {
        cout << "Список пустой \n";
        return;
    }

    List* last = head->prev;  // указатель last получает значение указателя на предыдущий элемент

    // если в списке только один элемент
    if (head == last)
    {
        delete head; // удаление головы (единственного элемента)
        head = nullptr;
    }

    else
    {
        List* newHead = head->next;  // новая голова списка - следующий элемент для текущего
        newHead->prev = last; // указатель на предыдущий элемент для новой головы
        last->next = newHead; // указатель на следующий элемент для последнего элемента

        delete head; // удаление текущей головы
        head = newHead; // указатель на новую голову
    }
}//DeleteFirst

int main()
{
    List* head = nullptr;  // голова списка
    setlocale(LC_ALL, "Russian");

    int size = 20; // размерность списка

    // добавление элементов в список
    for (int i = 0; i < size; i++)
    {
        // случайное вещественное число
        double rand_element = round((2.0 + ((double)rand() / RAND_MAX) * 48.0) * 10.0) / 10.0;
        Append(head, rand_element);
    }

    cout << "Элементы списка и их индексы" << endl;
    PrintList(head, size);

    // поиск
    cout << "-------------Поиск элемента-------------\n";
    double x;
    cout << "Введите элемент для поиска: ";
    cin >> x;

    Search(head, x);
    cout << "\n";

    // вставка
    cout << "------------Вставка элемента------------\n";
    int index;
    double new_elem;

    cout << "Введите индекс для вставки нового элемента: ";
    cin >> index;

    cout << "Введите значение элемента: ";
    cin >> new_elem;

    Add(head, new_elem, index);
    PrintList(head, size + 1);
    cout << "\n";

    // удаление из начала
    cout << "------Удаление элемента из начала------\n";
    DeleteFirst(head);
    PrintList(head, size);
    cout << "\n";

    // удаление списка
    cout << "------------Удаление списка------------\n";
    DeleteList(head);
    PrintList(head, size);

}//main
