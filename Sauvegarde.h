//
//  Sauvegarde.h
//  YOU
//
//  Created by Youness Lagrini on 12/07/2016.
//  Copyright © 2016 Youness Lagrini. All rights reserved.
//

#ifndef Sauvegarde_h
#define Sauvegarde_h
struct _Article;
typedef struct _Article Article;

int ExistanceFichier(char* NomFichier);
void CreerFichier(Article *Liste,int N);
Article* LireFichier(int* N);

#endif /* Sauvegarde_h */
