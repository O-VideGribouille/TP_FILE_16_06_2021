#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define WINDOW_WIDTH 724
#define WINDOW_HEIGHT 480

SDL_Window *pWindow=NULL;
SDL_Renderer *pRenderer=NULL;
SDL_Surface *pSurface=NULL;
SDL_Texture *pTexture=NULL;

typedef struct ElementListe{
    //char *chr_donnee;
    SDL_Texture *pIMG;
    struct ElementListe *p_suivant;
}Element;

typedef struct FileImg{
    Element *fl_debut;
    Element *fl_fin;
    int n_taille;
}FileImg;


void initFile(FileImg* File); // initialisation des données à 0 ou NULL
int insertElement(FileImg * File , Element * courant, SDL_Texture *pTexture); // inseration d'un élément dans la file
int suppElement(FileImg * File);
void afficheFile(FileImg *File);


int main(int argc, char *argv[])
{
    SDL_Event events;
    SDL_bool isOpen = SDL_TRUE;

    //Ecran SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        SDL_Log("Erreur d'initialisation SDL : %s\n", SDL_GetError());
        return 1;
    }else{
        pWindow=SDL_CreateWindow("An SDL2 window",100,100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);//sdl_window_shown affiche la fenetre

        //le renderer est le rendu graphique

        if(pWindow){
            pRenderer=SDL_CreateRenderer(pWindow, -1,SDL_RENDERER_PRESENTVSYNC);
        } // rendu dessin, texture, etc.
    }

        //Déclaration du file + malloc
    FileImg* File = NULL;
    File = (FileImg*)malloc(sizeof(FileImg));

    //Initialisation des données
    initFile(File);

    if(pRenderer){
        //set color
        SDL_SetRenderDrawColor(pRenderer,255,255,224,SDL_ALPHA_OPAQUE);
        //CLear Render
        SDL_RenderClear(pRenderer);

        pSurface = IMG_Load("./assets/Red.png");
        pTexture = SDL_CreateTextureFromSurface(pRenderer,pSurface);
        // Insertion d'un élément dans la file
        insertElement(File, File->fl_fin, pTexture);

        afficheFile(File);
        SDL_Delay(1000);

        pSurface = IMG_Load("./assets/Green.png");
        pTexture = SDL_CreateTextureFromSurface(pRenderer,pSurface);
        // Insertion d'un élément dans la file
        insertElement(File, File->fl_fin, pTexture);

        afficheFile(File);
        SDL_Delay(1000);

        pSurface = IMG_Load("./assets/Blue.png");
        pTexture = SDL_CreateTextureFromSurface(pRenderer,pSurface);
        // Insertion d'un élément dans la file
        insertElement(File, File->fl_fin, pTexture);
        afficheFile(File);
        SDL_Delay(1000);

        pSurface = IMG_Load("./assets/Cyan.png");
        pTexture = SDL_CreateTextureFromSurface(pRenderer,pSurface);
        // Insertion d'un élément dans la file
        insertElement(File, File->fl_fin, pTexture);

        afficheFile(File);
        SDL_Delay(1000);

        pSurface = IMG_Load("./assets/Magenta.png");
        pTexture = SDL_CreateTextureFromSurface(pRenderer,pSurface);
        // Insertion d'un élément dans la file
        insertElement(File, File->fl_fin, pTexture);

        afficheFile(File);


    }

    while (isOpen)
    {
         while (SDL_PollEvent(&events))
        {
            switch (events.type)
            {
            case SDL_QUIT:
                isOpen = SDL_FALSE ;
                break;
            }
        }

        //afficheFile(File);

        //Update render
       // SDL_RenderPresent(pRenderer);

    }


    if ((File = (FileImg *)malloc(sizeof(FileImg))) == NULL){
        return 0;
    }

    // Suppression ecran SDL

    if(pRenderer){
        SDL_DestroyRenderer(pRenderer);
    }

    if(pWindow){
       SDL_DestroyWindow(pWindow);
    }

    //SDL_FreeSurface();

    SDL_Quit(); //détruit tout ce qui constitut la SDL

  return 0;
}

//Initialisation
void initFile(FileImg* File){

    File->fl_debut = NULL;
    File->fl_fin = NULL;
    File->n_taille = 0;

}

// Insertion d'un élément dans la file
int insertElement (FileImg * File , Element * courant, SDL_Texture *pTexture){
    Element* nv_element = NULL;
    nv_element = (Element*)malloc(sizeof(Element));


    if (nv_element == NULL){
        return 0;
    }

    nv_element->pIMG = pTexture;

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
int suppElement(FileImg * File){
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
void afficheFile(FileImg *File){
    Element *courant;
    int n_i;
    courant = File->fl_debut;
    SDL_Rect rect = {0,0,0,0};

    for(n_i=0; n_i<File->n_taille; n_i++){

        if(!courant->pIMG){
            SDL_Log("Unable to set texture: %s", SDL_GetError());
        }else{
            rect.x = 100*n_i ;
            rect.y = 0;
            rect.w = 100;
            rect.h = 100;
            SDL_RenderCopy(pRenderer, courant->pIMG, NULL, &rect);
        }
        courant = courant->p_suivant;


         //Update render
        SDL_RenderPresent(pRenderer);

    }
}

