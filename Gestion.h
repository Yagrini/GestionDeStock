
#ifndef Gestion_h
#define Gestion_h
struct _Article;
typedef struct _Article Article;

Article* CreerArticle(int N);
void AfficherArticle(Article A);
void AjouterFin(Article** AdrListe,Article* AdrA);
void AfficherListe(Article* Liste);
Article* ListeParRubrique(Article* Liste,char* Rubrique);
Article* ListeParQuantity(Article* Liste,int seuil);
Article* ListeParRayon(Article* Liste,int rayon);
void SupprimerArticle(Article** AdrListe,int ID);
void RechercheArticle(Article* Liste,int ID);
void ModifierArticle(Article* Liste,int ID);
void TrierListe(Article *Liste);
void ChargerStock(Article* Liste,int ID,int Quantity);
void DechargerStock(Article* Liste,int ID,int Quantity);
void ElimineDoublons(Article* Liste);
int Taille(Article* Liste);
#endif /* Gestion_h */
