#include<stdio.h>
#include<stdlib.h>
#include<string.h>





//*******************************************ETAPE 0*********************************************


//Structure Article
typedef struct Article Article;

struct Article {
    int ID;
    char Rubrique[30];
    char Unit[20];
    char Designation[50];
    int Quantity;
    int Rayon;
    struct Article *next;
};
#include "Menu.h"

int main()
{
    MenuPrincipale();
    system("pause");
    return 0;
}

//*******************************************ETAPE 1*********************************************
//La fontion de creér un article
Article* CreerArticle(int N)
{
    Article *article=malloc(sizeof(Article));
    char rubTab[4][30]={"Fourniture de bureau","Matériel informatique","Produit de nettoyage","Mat́eriel enseignement"};
    char unitTab[4][10]={"Kg","Boite","Litre","Unité"};
    // affecter N+1 à ID de l'article
    article->ID=N+1;
    
    printf("Veuillez entrer les informations suivantes : \n");
    
    int choix;
    
    do{
        printf("Rubrique (1. Fourniture de bureau  2. Matériel informatique  3. Produit de nettoyage 4. Matériel d’enseignement) : \n");
        scanf("%d",&choix);
    }while(choix!=4 && choix!=1 && choix!=2 && choix!=3);
    strcpy(article->Rubrique, rubTab[choix-1]);
    
    do{
        printf("Unit (1. Kg  2. Boite  3. Litre  4. Unité) : \n");
        scanf("%d",&choix);
    }while(choix!=4 && choix!=1 && choix!=2 && choix!=3);
    strcpy(article->Unit, unitTab[choix-1]);
    
    do{
        printf("Designation (50 caractères max) : \n");
        scanf(" %[^\n]s",article->Designation);
    }while(strlen(article->Designation)>50);
    
    printf("Qantity : \n");
    scanf("%d",&article->Quantity);
    
    do{
        printf("Rayon (1-5) : \n");
        scanf("%d",&choix);
    }while(choix>5 || choix<1);
    article->Rayon=choix;
    
    article->next=NULL;
    
    return article;
}
//La fonction d'affichage
void AfficherArticle(Article A)
{
    printf("les informations de l\'article: (ID=%d)\n",A.ID);
    printf("\t -Rubrique: %s \n",A.Rubrique);
    printf("\t -Unit: %s \n",A.Unit);
    printf("\t -Designation: %s \n",A.Designation);
    printf("\t -Quantity: %d \n",A.Quantity);
    printf("\t -Rayon: %d \n",A.Rayon);
}
//La fonction d'ajouter un article à la fin de la liste
void AjouterFin(Article** AdrListe,Article* AdrA)
{
    if(*AdrListe==NULL)
    {
        *AdrListe=AdrA;
    }
    else
    {
        Article* FIN=*AdrListe;
        while(FIN->next) FIN=FIN->next;
        FIN->next=AdrA;
    }
    AdrA->next=NULL;
}
//La fonction d'affichage de la liste entière
void AfficherListe(Article* Liste)
{
    if(Liste==NULL)
    {
        printf("La liste est vide\n");
    }
    else
    {
        Article* fin=Liste;
        while(fin!=NULL)
        {
            AfficherArticle(*fin);
            fin=fin->next;
        }
    }
}
//La fonction affichage les acticles de même rubrique
Article* ListeParRubrique(Article* Liste,char* Rubrique)
{
    Article* listeRub=NULL;
    Article* tmp=Liste;
    while(tmp)
    {
        if(strcmp(tmp->Rubrique,Rubrique)==0)
        {
            Article* A=(Article*)malloc(sizeof(Article));
            *A=*tmp;
            AjouterFin(&listeRub,A);
        }
        tmp=tmp->next;
    }
    return listeRub;
}
//La fonction affichage les acticles qui ont une quantité inferieur ou égale le sueil
Article* ListeParQuantity(Article* Liste,int seuil)
{
    Article* listeQuan=NULL;
    Article* tmp=Liste;
    while(tmp)
    {
        if(tmp->Quantity<=seuil)
        {
            Article* A=(Article*)malloc(sizeof(Article));
            *A=*tmp;
            AjouterFin(&listeQuan,A);
        }
        tmp=tmp->next;
    }
    return listeQuan;
}
//La fonction affichage les acticles de même Rayon

Article* ListeParRayon(Article* Liste,int rayon)
{
    Article* listeRayon=NULL;
    Article* tmp=Liste;
    while(tmp)
    {
        if(tmp->Rayon==rayon)
        {
            Article* A=(Article*)malloc(sizeof(Article));
            *A=*tmp;
            AjouterFin(&listeRayon,A);
        }
        tmp=tmp->next;
    }
    return listeRayon;
}
// La fonction de sipprimer un article de la liste
void SupprimerArticle(Article** AdrListe,int ID)
{
    int trouve=0;
    Article* tmp=*AdrListe;
    if((*AdrListe)->ID==ID)
    {
        *AdrListe=(*AdrListe)->next;
        trouve=1;
    }
    else
    {
        while(tmp)
        {
            if(tmp->next==NULL)
            {
                break;
            }
            if((tmp->next)->ID==ID)
            {
                tmp->next=(tmp->next)->next;
                trouve=1;
                break;
            }
            tmp=tmp->next;
        }
        
    }
    if(trouve)
    {
        printf("L\'article dont l\'ID = %d a ete supprime avec succes\n",ID);
    }
    else
    {
        printf("L\'article dont l\'ID = %d introuvable\n",ID);
    }
}
//La fonction de recherche d'un article dans la liste
void RechercheArticle(Article* Liste,int ID)
{
    Article* tmp=Liste;
    Article A;
    int trouve=0;
    if(tmp==NULL)
    {
        printf("Article non trouve\n");
    }
    else
    {
        while(tmp)
        {
            if(tmp->ID==ID)
            {
                A=*tmp;
                printf("Article %d trouve ",tmp->ID);
                AfficherArticle(A);
                trouve=1;
                break;
            }
            tmp=tmp->next;
        }
    }
    if(trouve==0)
    {
        printf("Article non trouve\n");
    }
}
//La fonction de modifier un article
void ModifierArticle(Article* Liste,int ID)
{
    Article* tmp=Liste;
    while(tmp && tmp->ID!=ID)
        tmp=tmp->next;
    
    if(tmp==NULL)
    {
        printf("L\'article dont l'identificateur = %d n'existe pas!!\n",ID);
    }
    else
    {
        Article* nextSecours=tmp->next;
        *tmp=*(CreerArticle(ID-1));
        tmp->next=nextSecours;
    }
}
//La fonction de trier une liste
void TrierListe(Article *Liste)
{
    
    Article *I,*J,*Min,*SuivSecoursI,*SuivSecoursMin;
    Article Aide;
    I=Liste;
    while(I)
    {
        Min=I;
        J=I->next;
        while(J)
        {
            if(Min->Quantity>J->Quantity)
                Min=J;
            J=J->next;
        }
        SuivSecoursI=I->next;
        SuivSecoursMin=Min->next;
        Aide=*I;
        *I=*Min;
        *Min=Aide;
        
        I->next=SuivSecoursI;
        Min->next=SuivSecoursMin;
        I=I->next;
    }
}
//La fonction de charger le stock
void ChargerStock(Article* Liste,int ID,int Quantity)
{
    Article* tmp=Liste;
    int trouve=0;
    if(tmp==NULL)
    {
        printf("Article non trouve\n");
    }
    else
    {
        while(tmp)
        {
            if(tmp->ID==ID)
            {
                printf("Article %d trouve ",tmp->ID);
                tmp->Quantity+=Quantity;
                trouve=1;
                break;
            }
            tmp=tmp->next;
        }
    }
    if(trouve==0)
    {
        printf("Article non trouve\n");
    }
}
//La fonction de décharger le stock
void DechargerStock(Article* Liste,int ID,int Quantity)
{
    Article* tmp=Liste;
    int trouve=0;
    if(tmp==NULL)
    {
        printf("Article non trouve\n");
    }
    else
    {
        while(tmp)
        {
            if(tmp->ID==ID)
            {
                printf("Article %d trouve ",tmp->ID);
                trouve=1;
                if(tmp->Quantity<Quantity)
                {
                    printf("la quantite de l\'article est insufisante\n");
                    break;
                }
                tmp->Quantity-=Quantity;
                break;
            }
            tmp=tmp->next;
        }
    }
    if(trouve==0)
    {
        printf("Article non trouve\n");
    }
}
//La fonction qui décrémente la quantité de l’article dont l’identificateur = ID par Quantity. Si Quantity est supérieure à la disponibilité il faudra en alerter l’utilisateur.
void ElimineDoublons(Article* Liste)
{
    Article* tmp=Liste;
    Article* tmpSecours=tmp->next;
    if(Liste==NULL || Liste->next==NULL)
    {
        printf("Aucun doublon trouve\n");
    }
    else
    {
        while(tmp)
        {
            while(tmpSecours)
            {
                if(strcmp(tmp->Rubrique,tmpSecours->Rubrique)==0 && strcmp(tmp->Designation,tmpSecours->Designation)==0)
                {
                    printf("Les articles (ID=%d) et (ID=%d) ont été fusionné\n",tmp->ID,tmpSecours->ID);
                    tmp->Quantity+=tmpSecours->Quantity;
                    SupprimerArticle(&tmp,tmpSecours->ID);
                }
                tmpSecours=tmpSecours->next;
            }
            tmp=tmp->next;
        }
    }
}
//La fonction qui retourne la taille de la liste Liste.
int Taille(Article* Liste)
{
    Article* tmp=Liste;
    int L=0;
    while(tmp)
    {
        L++;
        tmp=tmp->next;
    }
    return L;
}


//*******************************************ETAPE 2*********************************************

//La fonction Qui retourne 1 si le fichier dont le nom = NomFichier existe et 0 sinon.
int ExistanceFichier(char* NomFichier)
{
    int resultat=1;
    FILE *Fichier=fopen(NomFichier,"r");
    if(Fichier==NULL)
        resultat=0;
    else
        fclose(Fichier);
    return resultat;
}
//Une fonction qui nous permet de sauvegarder la liste des articles Liste et le dernier ID utilisé N dans un fichier texte.
void CreerFichier(Article *Liste,int N){
    char NomFichier[100];
    FILE *Fichier;
    Article *TMP=Liste;
    char choix='A';
    //Saisi du nom du fichier
    do{
        printf("\n\nDonner le nom du fichier a cree : ");
        scanf("%s",NomFichier);
        printf("%s",NomFichier);
        
        if(ExistanceFichier(NomFichier)==1){
            printf("\nLe fichier existe deja, voulez-vous l'ecraser?\nTaper '1' si oui et autre que '1' sinon : ");
            scanf("%c",&choix);
        }
        else break;
    }while(choix!='1');
    
    //Création du fichier
    Fichier=fopen(NomFichier,"w");
    
    //Enregistrer N au début du fichier
    printf("%d",N);
    fprintf(Fichier,"%d",N);
    
    //Insertion des données des étudiants dns le fichier
    while(TMP){
        fprintf(Fichier,"\n%d\n%s\n%s\n%s\n%d\n%d",TMP->ID,TMP->Rubrique,TMP->Unit,TMP->Designation,TMP->Quantity,TMP->Rayon);
        TMP=TMP->next;
    }
    //fermuture du fichier
    fclose(Fichier);
    printf("\n\nVos donnees ont ete bien enregistre dans le fichier %s\n\n",NomFichier);
    system("pause");
}
//La fonction utilisée pour Lire à partir d’un fichier le dernier ID utilisé et le mettre dans l’adresse N, et la liste des articles retournée comme résultat.
Article* LireFichier(int* N)
{
    char NomFichier[30];
    FILE *Fichier;
    Article* Liste=NULL;
    //Saisi du nom du fichier
    do
    {
        printf("\n\nDonner le nom du fichier a lire : ");
        scanf("%s",NomFichier);
        if(ExistanceFichier(NomFichier)==0)
            printf("\nLe fichier %s n'existe pas!!\a\n ",NomFichier);
        
    }while(ExistanceFichier(NomFichier)==0);
    
    //Ouverture du fichier en lecure
    Fichier=fopen(NomFichier,"r");
    
    //Lire N au début du fichier
    fscanf(Fichier,"%d\n",N);
    printf("Votre base de donnees contienne %d article .\n\n",*N);
    //Lecture des données des étudiants dans le fichier et les insérer dans Liste
    while(!feof(Fichier))
    {
        Article *TMP=(Article*)malloc(sizeof(Article));
        fscanf(Fichier,"%d\n",&TMP->ID);
        fscanf(Fichier,"%[^\n]s\n",TMP->Rubrique);
        fscanf(Fichier,"%s\n",TMP->Unit);
        fscanf(Fichier,"%s\n",TMP->Designation);
        fscanf(Fichier,"%d\n",&TMP->Quantity);
        fscanf(Fichier,"%d\n",&TMP->Rayon);
        AjouterFin(&Liste,TMP);
    }
    //fermuture du fichier
    fclose(Fichier);
    printf("\n\nVos donnees ont ete bien lues a partir du fichier %s\n\n",NomFichier);
    system("pause");
    return Liste;
}
//*******************************************ETAPE 3*********************************************

//La fonction utilisé pour la création et la sauvegarde d’une nouvelle base de données selon le souhait de l’utilisateur.
void NouvelleBase()
{
    char reponse='A';
    int N=0;
    Article *Liste=NULL;
    printf("*****************Creation d'une nouvelle base de donnees*****************");
    while(reponse!='0'){
        printf("\n\nTaper n'importe quelle touche pour ajouter un nouveau étudiant et 0 sinon : ");
        getchar();
        scanf("%c",&reponse);
        if(reponse!='0'){
            AjouterFin(&Liste,CreerArticle(N));
            N++;
            
        }
    }
    printf("\nVous avez creer une liste avec une taille = %d",Taille(Liste));
    CreerFichier(Liste,N);
}
//La fonction qui Qui offre à l’utilisateur un menu avec deux choix :
// Création d’un nouvelle base de données.
// La gestion d’une base de données existante.
void MenuPrincipale()
{
    char reponse;
    do{
    
        printf("\nVeuillez choisir une option: \n\n   Taper '1' pour la creation d'une nouvelle base de donnees.\n   Taper '2' pour la gestion d'une base de donnees existante.\n   Taper '0' pour quitter le programme.\n\nDonner votre option : ");
        scanf("%c",&reponse);
        switch(reponse){
            case '0': exit(-1);
            case '1': NouvelleBase(); reponse='3'; break;
            case '2': MenuGestion(); reponse='3'; break;
        }
    }while(reponse!=0 && reponse!=1 && reponse!=2 );
}
//La fonction qui offre à l’utilisateur un menu avec plusieurs choix :
// Affichage de la base de données,
// Rechercher un article,
// Supprimer un article,
// Modifier un article,
// Trier la base de données,
// Afficher la liste des articles par rubrique,
// Afficher la liste des articles par rayon,
// Afficher la liste des articles par quantité suivant un seuil donné,
// Eliminer les doublons,
// Ajouter un nouvel article,
// Charger le stock,
// Décharger le stock,
void MenuGestion()
{
    printf("*****************Bienvenue au menu de Gestion***************** \n ");
    Article* Liste;
    int N;
    Liste=LireFichier(&N);
    
    int reponse;
    char rubrique[30];
    int ID,rayon,seuil,qte;
    do
    {
        printf("\nVeuillez choisir une option: \n\n\t Taper '1' Pour l'affichage de la base de donnees.\n\t Taper '2' Pour Rechercher un article.\n\t Taper '3' Pour Supprimer un article.\n\t Taper '4' Pour la modification d'un article de la base de donnees.\n\t Taper '5' Pour trier la base de donnees.\n\t Taper '6' Pour Afficher la liste des articles par rubrique.\n\t Taper '7' Pour Afficher la liste des articles par rayon.\n\t Taper '8' Pour Afficher la liste des articles par quantité suivant un seuil donné.\n\t Taper '9' Pour Eliminer les doublons.\n\t Taper'10' Pour Ajouter un nouvel article.\n\t Taper '11' Pour Charger le stock.\n\t Taper '12' Pour Décharger le stock.\n\t Taper '0' Pour retourner ves le menu principale.\n\nDonner votre option : ");
        scanf("%d",&reponse);
        switch(reponse)
        {
            case 0: MenuPrincipale();
            case 1: AfficherListe(Liste); reponse='15'; break;
            case 2: printf("Donner l'ID de l'article a chercher :"); scanf("%d",&ID); RechercheArticle(Liste,ID);reponse='15'; break;
            case 3: printf("Donner l'ID de l'article a supprimer : "); scanf("%d",&ID); SupprimerArticle(&Liste,ID); reponse='15'; break;
            case 4: printf("Donner l'ID de l'article a modifier : "); scanf("%d",&ID); ModifierArticle(Liste,ID); reponse='15'; break;
            case 5: TrierListe(Liste); printf("Votre base de donnees est triee\n\n"); reponse='15'; break;
            case 6: printf("Donner la rubrique a chercher : "); getchar(); scanf("%[^\n]s",&rubrique); AfficherListe(ListeParRubrique(Liste,rubrique)); reponse='15'; break;
            case 7: printf("Donner le rayon a consulter : "); scanf("%d",&rayon); AfficherListe(ListeParRayon(Liste,rayon)); reponse='15'; break;
            case 8: printf("Donner le seuil de quantite : "); scanf("%d",&seuil); AfficherListe(ListeParQuantity(Liste,seuil)); reponse='15'; break;
            case 9: ElimineDoublons(Liste); reponse='15'; break;
            case 10: AjouterFin(&Liste,CreerArticle(Taille(Liste))); reponse='15'; break;
            case 11: printf("entrez l\'ID de l\'article"); printf("entrez la quantite a ajouter"); scanf("%d",&qte); ChargerStock(Liste,ID,qte); reponse='15'; break;
            case 12: printf("entrez l\'ID de l\'article"); scanf("%d",&ID); printf("entrez la quantite a soustraire"); scanf("%d",&qte); DechargerStock(Liste,ID,qte); reponse='15'; break;
        }
    }while(reponse!=0 && reponse!=1 && reponse!=2 && reponse!=3 && reponse!=4 && reponse!=5 && reponse!=6 && reponse!=7 && reponse!=8 && reponse!=9 && reponse!=10 && reponse!=11 && reponse!=12);
    
}


