#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Vecteur.h"
#include "Alphabet.h"
#include "Chevalets.h"

#include <assert.h>

char piochePaquet(Alphabet* Alpha) {
    assert(taille(&Alpha->lettres) > 0);
    int r = rand() % taille(&Alpha->lettres);
    Lettre La = obtenir(&Alpha->lettres, r);
    char lettre =AfficherLettre(&La);
    MoinsAlpha(Alpha,lettre);
    return lettre;
}

void InitPartie(Alphabet* Alpha_jeu, PAQUETS* joueur1, PAQUETS* joueur2) {
    assert(NbLettreRestantAlphabet(Alpha_jeu)>0);
    initVecteur(&joueur1->lettres, NBLETTREJOUEURDEBUT);
    initVecteur(&joueur2->lettres, NBLETTREJOUEURDEBUT);
    for (int i = 0; i < NBLETTREJOUEURDEBUT; i++) {
        char L1 = piochePaquet(Alpha_jeu);
        char L2 = piochePaquet(Alpha_jeu);
        Lettre l1;
        Lettre l2;
        InitLettres(&l1, L1);
        InitLettres(&l2, L2);
        ajouter(&joueur1->lettres, l1);
        ajouter(&joueur2->lettres, l2);
    }
}

void InitPartiedejfait(PAQUETS* joueur1, PAQUETS* joueur2) {
    initVecteur(&joueur1->lettres, NBLETTREJOUEURDEBUT);
    initVecteur(&joueur2->lettres, NBLETTREJOUEURDEBUT);
    for (char i = 'A'; i < NBLETTREJOUEURDEBUT + 'A'; i++) {

        Lettre l1;
        Lettre l2;
        InitLettres(&l1, i);
        InitLettres(&l2, i);
        ajouter(&joueur1->lettres, l1);
        ajouter(&joueur2->lettres, l2);
    }
}

void AfficherPaquettrier(PAQUETS* paquet) {
    qsort(paquet->lettres.elements, taille(&paquet->lettres), sizeof(Lettre), comparerLettre);
    for (int i = 0; i < taille(&paquet->lettres); i++) {
        Lettre La = obtenir(&paquet->lettres, i);
        printf("%c,",AfficherLettre(&La));
    }
    printf("\n");
}

int comparerLettre(const void* a, const void* b) {
    const Lettre* lettreA = (const Lettre*)a;
    const Lettre* lettreB = (const Lettre*)b;
    return AfficherLettre(lettreA) - AfficherLettre(lettreB);
}

void EchangePioche(Alphabet* Alpha, Lettre* L) {
    char lettre_in = AfficherLettre(L);
    PlusAlpha(Alpha, lettre_in);
    char lettre_out  = piochePaquet(Alpha);
    InitLettres(L, lettre_out);
}

int est_dans(const PAQUETS* paquet, const char L) {
    for (int i =0; i < taille(&paquet->lettres);i++) {
        Lettre Le = obtenir(&paquet->lettres, i);
        if (L == AfficherLettre(&Le))
            return 1;
    }
    return 0;
}

void DupliquerPaquet(const PAQUETS* source, PAQUETS* destination) {
    initVecteur(&destination->lettres, NBLETTREJOUEURDEBUT);
    for (int i = 0; i < taille(&source->lettres); i++) {
        Lettre Le = obtenir(&source->lettres, i);
        ajouter(&destination->lettres, Le);
    }
}

void MoinsPaquet(PAQUETS *P, char L) {
    if (est_dans(P, L)) {
        for (int i = 0; i < taille(&P->lettres); i++) {
            Lettre La = obtenir(&P->lettres, i);
            if (AfficherLettre(&La) == L) {
                supprimer(&P->lettres, i);
                break;
            }
        }
    }
}

void PlusPaquet(PAQUETS *P, char L) {
    Lettre lettre;
    InitLettres(&lettre,L);
    ajouter(&P->lettres, lettre);
}


void LibererPaquets(PAQUETS* P) {
    detruireVecteur(&P->lettres);
}