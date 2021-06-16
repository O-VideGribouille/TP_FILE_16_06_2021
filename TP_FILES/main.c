#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ElementListe{
    char *chr_donnee;
    struct ElementListe *p_suivant;
}Element;

typedef struct ListeChar{ //équivaut Liste_entier -----------
    Element *fl_debut;
    Element *fl_fin;
    int n_taille;
}ListeChar;

// Consulter le premier élément de la file
#define file_donnee1(File) File->fl_debut->chr_donnee
//ne le supprimera pas de la liste

// Consulter le dernier élément de la file
#define file_donnee2(File) File->fl_fin->chr_donnee


void initFile(ListeChar* File); // initialisation des données à 0 ou NULL
int insertElement(ListeChar * File , Element * courant, char *chr_donnee); // inseration d'un élément dans la file
int suppElement(ListeChar * File);
void afficheFile(ListeChar *File);


int main()
{
    printf("TP Files 16.06.2021\n");


    ListeChar* File = NULL;
    File = (ListeChar*)malloc(sizeof(ListeChar));

    //File *fl_suite;

    char *chr_nom;
    if ((File = (ListeChar *)malloc(sizeof(ListeChar))) == NULL){
        return 0;
    }
    if ((chr_nom = (char *)malloc(50 * sizeof (char))) == NULL){
        return 0;
    }
    //Initialisation des données
    initFile(File); //dans l'exemple du tuto suite équivaut à mon FIle ---------


    // Insertion d'un élément dans la file
    printf("Entrez un mot : ");
    scanf("%s", chr_nom);
    insertElement(File, File->fl_fin, chr_nom);
    // Retourner la taille de la file
    printf("La file (%d/3 elements) \n", File->n_taille);
    printf("\nDebut de la FILE [ ");
    //Affichage File
    afficheFile(File);      //le premier entré sera affiché
    printf(" ] Fin de la FILE\n\n");


    // Insertion 2
    printf("Entrez un mot : ");
    scanf("%s", chr_nom);
    insertElement(File, File->fl_fin, chr_nom);
    // Retourner la taille de la file
    printf("La file (%d/3 elements)\n", File->n_taille);
    printf("\nDebut de la FILE [ ");
    //Affichage File
    afficheFile(File);
    printf(" ] Fin de la FILE\n\n");

    // Insertion 3
    printf("Entrez un mot : ");
    scanf("%s", chr_nom);
    insertElement(File, File->fl_fin, chr_nom);
    // Retourner la taille de la file
    printf("La file (%d/3 elements)\n", File->n_taille);
    printf("\nDebut de la FILE [ ");
    //Affichage File
    afficheFile(File);
    printf(" ] Fin de la FILE\n\n");

    //Consulter le premier element
    printf ("\nLe premier entré est [ %s ] \n",
                    file_donnee1(File));

    // Consutler le dernier element
    printf ("\nLe dernier entré est [ %s ] \n",
                    file_donnee2(File));

    //Enlever un élément de la file
    printf ("\nLe premier entre est supprime\n");
    suppElement(File);
    // Retourner la taille de la file
    printf("La file (%d/3 elements)\n", File->n_taille);
    printf("\nDebut de la FILE [ ");
    //Affichage File
    afficheFile(File);
    printf(" ] Fin de la FILE\n\n");

  return 0;
}

//Initialisation
void initFile(ListeChar* File){

    File->fl_debut = NULL;
    File->fl_fin = NULL;
    File->n_taille = 0;

}

// Insertion d'un élément dans la file
int insertElement (ListeChar * File , Element * courant, char *chr_donnee){
    Element* nv_element = NULL;
    nv_element = (Element*)malloc(sizeof(Element));
    nv_element->chr_donnee = (char *)malloc(50 * sizeof(char));

    if (nv_element == NULL){
        return 0;
    }
    if (nv_element->chr_donnee == NULL){
        return 0;
    }
    strcpy (nv_element->chr_donnee, chr_donnee);

    if(courant == NULL){
        if(File->n_taille == 0){
            File->fl_fin = nv_element;
        }
         nv_element->p_suivant = File->fl_debut;
         File->fl_debut = nv_element;
        }else{
            if(courant->p_suivant == NULL){
                File->fl_fin = nv_element;
                }
                nv_element->p_suivant = courant->p_suivant;
                courant->p_suivant = nv_element;
         }
    File->n_taille++;
    return 1;
}

// Enlever un élément de la file
int suppElement(ListeChar * File){
     if(File->n_taille == 0){
        return 0;
     }

     Element* supp = NULL;
     supp = File->fl_debut;
     File->fl_debut = File->fl_debut->p_suivant;

     if(File->n_taille == 1){
        File->fl_fin = NULL;
     }

     free(supp);
     File->n_taille--;

     return 1;
}
// Afficher la file
void afficheFile(ListeChar *File){
    Element *courant;
    int n_i;
    courant = File->fl_debut;

    for(n_i=0; n_i<File->n_taille; n_i++){
        printf(" %s ", courant->chr_donnee);
        courant = courant->p_suivant;
    }
}

