# include <stdio.h>
# include <conio.h>
#include <stdlib.h>

// наша структура
struct node {
    int info; // інформаційне поле
    struct node *l, *r;// ліва та права частини дерева
};

struct node *tree = NULL; // оголошуємо змінну, тип якої структура Дерево

void print(struct node *t, int u);

void search(struct node *t, int a);

void push(int a, struct node **t);

int Delete(struct node **R, int target);

void DeleteTree(struct node **t);

void ClearTree(struct node **t);

int getAverage() ;
int main() {
    int n; // кількість елементів
    int s; //  число, що передається в дерево
    printf("Enter number of elements  ");
    scanf("%i", &n); // вводимо кількість елементів

    for (int i = 0; i < n; ++i) {
        printf("Enter number %d", i);
        scanf("%d", &s); // зчитуємо елемент за елементом
        push(s, &tree); // і кожен розміщуємо в дерево
    }
    printf("your tree\n");
    print(tree, 0); // друк дерева


    int a;
    printf("Enter value for search:");
    scanf("%d", &a); // зчитуємо елемент для пошуку
    search(tree, a);

    printf("\n \n Your tree\n");
    print(tree, 0);

    int b;
    printf("Enter value  for delete: ");
    scanf("%i", &b); // зчитуємо елемент для видалення
    Delete(&tree, b);
    printf("\n \n Your tree after deletion of element\n");
    print(tree, 0);


/*
    Обчислити середнє арифметичне елементів дерева заданого рівня
*/
    int c;
    printf("Enter the level of tree");
    scanf("%d", &c); //задаємо рівень
    printf("%d", getAverage()); // обчислюємо середнє арифметичне і повертаємо резутьтат

   /* ClearTree(&tree);
    printf("\n \n Your tree after deletion\nNULL");
    print(tree, 0);*/

    getch();
    return 0;
}

/* використовувати зворотній алгоритм для проходження вузлів дерева і видалити кожен вузол при його відвідуванні */
void DeleteTree(struct node **t) {
    if (*t != NULL) {
        DeleteTree(&((*t)->l));
        DeleteTree(&((*t)->r));
    } else return;
}

/* викликати функцію DeleteTree для видалення вузлів дерева. Потім обнулити вказівник на його корінь */
void ClearTree(struct node **t) {
    DeleteTree(&(*t));

    *t = NULL;  // тепер корінь порожній
}

int Delete(struct node **R, int target) {
    if ((*R) == 0) return 0; // якщо елемента дерева не існує, повертаємо 0
    if ((*R)->info == target) // порівнюємо значення поточного елемента дерева з елементом, що знаходимо для видалення
    {
        if (((*R)->l != 0) && ((*R)->r != 0)) // якщо елемент дерева має два дочірні елементи:
        {
            struct node *P = NULL;
            P = malloc(sizeof(struct node)); // виділяємо пам'ять для допоміжного елементу типу node
            P = (*R)->l; // вказуєм на допоміжний елемент вказівник лівого піддерева
            if (P->r == 0) // якщо для допоміжного елементу не існує правого піддерева
            {
                (*R)->info = P->info; // змінюємо вказівник з видаленого елемента на новий
                (*R)->l = P->l;
            } else {
                while (P->r->r != 0) P = P->r;
                (*R)->info = P->r->info; // змінюємо вказівник з видаленого елемента на новий
                P->r = 0;
            }
            return 0; // функція повертає 0
        } else
            return 1; // функція повертає 1
    }
    if (Delete(&((*R)->l),
               target)) // за допомогою рекурсії відвідуємо ліве піддерево для пошуку елементу, який буде видалений
    {
        if ((*R)->l->l == 0)
            (*R)->l = (*R)->l->r;
        else
            (*R)->l = (*R)->l->l;
        return 0; // функція повертає 0
    }
    if (Delete(&((*R)->r),
               target)) // за допомогою рекурсії відвідуємо праве піддерево для пошуку елементу, який буде видалений
    {
        if ((*R)->r->l == 0)
            (*R)->r = (*R)->r->r;
        else
            (*R)->r = (*R)->r->l;
        return 0; // функція повертає 0
    }
    return 0; // функція повертає 0
}

/* ФУНКЦІЯ ЗАПИСУ ЕЛЕМЕНТА В БІНАРНЕ ДЕРЕВО */
void push(int a, struct node **t) {
    if ((*t) == NULL) // якщо дерева не існує
    {
        (*t) = malloc(sizeof(struct node)); // виділяємо пам'ять
        (*t)->info = a; // розміщуємо в виділене місце аргумент a
        (*t)->l = (*t)->r = NULL; // очищуємо пам'ять для наступного зростання
        return; // вихід з функції
    }
    // дерево є
    if (a > (*t)->info) push(a, &(*t)->r); // якщо аргумент а більше ніж поточний елемент, розміщуємо його праворуч
    else push(a, &(*t)->l); // інакше розміщуємо його ліворуч
}

/* ФУНКЦІЯ ВІДОБРАЖЕННЯ ДЕРЕВА НА ЕКРАН*/
void print(struct node *t, int u) {
    if (t == NULL) { // якщо дерево порожнє, то виводимо на екран NULL, виходимо з функції
        return;
    }

    print(t->l, ++u);// за допомогою рекурсії відвідуємо ліве піддерево
    for (int i = 0; i < u; ++i) printf(" - ");
    printf("%i\n", t->info); // і показуємо елемент
    u--;

    print(t->r, ++u); // за допомогою рекурсії відвідуємо праве піддерево
}

void search(struct node *t, int a) {
    if (t == NULL) return; // якщо дерево порожнє, то відображати нічого, виходимо з функції

    if (t->info == a) { // порівнюємо поточний елемент з заданим значенням
        t->info += 1; // збільшуємо знайдений елемент на одиницю
        return; // вихід з функції
    }

    search(t->l, a); // за допомогою рекурсії відвідуємо ліве піддерево

    search(t->r, a); // за допомогою рекурсії відвідуємо праве піддерево
}

int getAverage(/*?????????????*/) {
   /*???????????????*/
}