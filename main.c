#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//1- Difine The data Structure that contains the information of student 
typedef struct information
{
    int CODE;
    char L_NAME[10];
    float MARK;
} INFO;

typedef struct s_noeud
{
    INFO student;
    struct s_noeud *gauche;
    struct s_noeud *droit;
} noeud;
typedef noeud *s_tree;



//2- Impliment the creation and insertion From the CSV file to BST
s_tree cree_arbre(INFO *item)
{
    s_tree temp = (noeud *)malloc(sizeof(noeud));
    temp->student.CODE = item->CODE;
    strcpy(temp->student.L_NAME, item->L_NAME);
    temp->student.MARK = item->MARK;
    temp->gauche = temp->droit = NULL;
    return temp;
}


s_tree insert(s_tree a, INFO *data)
{
    if (a == NULL)
        return cree_arbre(data);
    if (data->MARK < a->student.MARK)
        a->gauche = insert(a->gauche, data);
    else if (data->MARK > a->student.MARK)
        a->droit = insert(a->droit, data);
    return a;
}


//3- Impliment the Search function using the Mark of the Student as a Key 
s_tree Search(s_tree *a, float m)
{
    if ((*a) == NULL)
        return NULL;
    if (m == (*a)->student.MARK)
    {
        return *a;
    }
    else if (m < (*a)->student.MARK)
    {
        return Search(&(*a)->gauche, m);
    }
    else if (m > (*a)->student.MARK)
    {
        return Search(&(*a)->droit, m);
    }
}


// this function Print All the element of the BST in preotder Travesall 
void preorder(s_tree root)
{
    if (root != NULL)
    {

        printf("%d\t%s\t    %.2f\n", root->student.CODE, root->student.L_NAME, root->student.MARK);
        preorder(root->gauche);
        preorder(root->droit);
    }
}



int main()
{
    // Start reading The CSV file 
    FILE *file;
    file = fopen("data.csv", "r");
    if (file == NULL)
    {
        printf("Error While opening file.\n");
        return 1;
    }
    INFO students[100]; // the maximun number of student is 100
    int read = 0;       // read => columns
    int records = 0;    // records => rows
    // Store the information of the CSV file in a the Struct STUDENTS[100]
    do
    {
        read = fscanf(file,
                      "%d,%49[^,],%f\n",
                      &students[records].CODE,
                      students[records].L_NAME,
                      &students[records].MARK);
        if (read == 3) // code , Name , Mark
            records++;

        if (read != 3 && !feof(file))
        {
            printf("File format incorrect.\n");
            return 1;
        }

        if (ferror(file))
        {
            printf("Error while reading file.\n");
            return 1;
        }

    } while (!feof(file));
    fclose(file);
    //end Reading The CSV File 


    //print The CSV File that stored in the struct STUDENTS[100]
    printf("\n%d Ligns readed.\n\n", records);
    printf("the csv file readed : \n\n");
    printf("-----------------------------\n");
    for (int i = 0; i < records; i++)
        printf("%d\t%s\t    %.2f\n",
               students[i].CODE,
               students[i].L_NAME,
               students[i].MARK);
    printf("-----------------------------\n");


    //Declare the first element of the tree 
    s_tree a = NULL;
    a = cree_arbre(students);


    INFO *d = students;//its a pointer to the STUDENTS[100] WE WILL use it to Traverse to all the students 

    //insert All the Students in the Struct STUDENTS[100] in a Binarry Search Tree
    for (int i = 1; i < records; i++)
    {
        ++d;
        insert(a, d);
    }


    //Display the Elements of the BST in preorder traversal 
    printf("\n\ndisplaying the binarry search tree : \n\n");
    preorder(a);
    printf("\n\n press any key to continue ... ");
    getch();



    // Testing the Search of a Student function 
    printf(" \n\n\n\t\t\t\t\t Testing the Search function : \n");
    float m;
    s_tree check;
    char choise;
    printf("\n\nEnter The Mark of the student : ");
    scanf("%f", &m);
    check = Search(&a, m);

    if (check)
        printf("\n  Student Founded Successfully \n\nhis informations : %d %s %.2f\n\n", check->student.CODE, check->student.L_NAME, check->student.MARK);
    else
        printf("\nStudent not Founded !!!  \n\n");
    getch();
    printf("\n\n\n");

    while (1)
    {
        printf("Do U want to Search for an other student : ");
        printf("\n y => Yes ");
        printf("\n n => No\n");
        scanf(" %c", &choise);
        while (choise != 'n' && choise != 'N' && choise != 'y' && choise != 'Y')
        {
            printf("invalide option \nTry again : ");
            printf("\n y => Yes ");
            printf("\n n => No\n");
            scanf(" %c", &choise);
        }
        if (choise == 'y' || choise == 'Y')
        {
            printf("\nEnter The Mark of the student : ");
            scanf("%f", &m);
            check = Search(&a, m);
            if (check)
                printf("\n  Student Founded Successfully \n\nhis informations : %d %s %.2f\n\n", check->student.CODE, check->student.L_NAME, check->student.MARK);
            else
                printf("\nStudent not Founded !!!  \n\n");
            getch();
            printf("\n\n\n");
        }

        else if (choise == 'n' || choise == 'N')
        {
            printf("\n\tokk )_) \n");
            break;
        }
    }


    return 0;
}
