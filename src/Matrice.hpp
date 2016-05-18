/**
 * @file Matrice.hpp
 * @brief Ce fichier décrit tous les éléments pours des matrices carrées de taille N
 * @author Laurent Bardoux p1108365
 * @version 1.0
 */
#ifndef MATRICE_HPP_INCLUDED
#define MATRICE_HPP_INCLUDED

//! @cond
#include <vector>
#include <initializer_list>
#include <cstdlib>

#include "Point.hpp"
//! @endcond


/**
 * @brief Cette classe décrit une matrice carré de taille N
 * Exemple d'usage, la valeur (x, y) s'obtient via valeurs[x][y].
 * Encore une fois, j'ai choisi des std::vector à la place de tableau
 * statique, pour plusieurs raisons :
 *  - vérifications des bornes lors des accès en lecture.
 *  - Accès aux itérateurs (std::copy, etc).
 */
template<unsigned int N>
class Matrice final
{
    private:
        std::vector<std::vector<double>> valeurs; /*! le premier vector représente x (une colonne), le second y (la ligne).*/

        /**
         * @brief Une manière de simplifier l'accès à une colonne de la matrice.
         * @param[in] i La ième colonne voulue.
         * @throw out_of_range en cas de dépassement de capacité.
         * @return une référence sur la colonne demandée si elle existe.
         */
        std::vector<double>& operator[](const size_t i);

    public:
        //! @brief Initialise une matrice carré avec des 0.0 partout.
        Matrice(void);

        /**
         * @brief Le constructeur par copie.
         * @param[in] autre La matrice à copier.
         */
        Matrice(const Matrice<N> &autre);

        /**
         * @brief Le constructeur par déplacement.
         * @param[in,out] autre La matrice à "déplacer".
         */
        Matrice(Matrice<N> &&autre);

        /**
         * @brief Permet de construire une matrice avec un Point<N> par colonne.
         * Cela se passe par des arguments multiples, par exemple :
         * @code
         *      Point p1, p2;
         *      // initialiser les points, bien entendus
         *      Matrice<2> m( {p1, p2} );
         * @endcode
         * @param[in] points La liste des arguments multiples de points.
         */
        Matrice(std::initializer_list<Point<N>> points);

         //! @brief Le destructeur, qui va désallouer les valeurs.
        ~Matrice(void);

        /**
         * @brief L'opérateur d'affectation avec une lvalue.
         * @param[in] autre La matrice à copier.
         * @return cette matrice dont le contenu de autre a été copié.
         */
        Matrice<N>& operator=(const Matrice<N> &autre);

        /**
         * @brief L'opérateur d'affectation avec une rvalue.
         * @param[in] autre La matrice à copier.
         * @return cette matrice dont le contenu de autre a été "déplacé".
         */
        Matrice<N>& operator=(Matrice<N> &&autre);

        /**
         * @brief Permet de récupérer l'élément de la matrice( \a x , \a y ).
         * @param[in] x Le numéro de la colonne que vous voulez (de 0 à N exclu).
         * @param[in] y Le numéro de la ligne que vous voulez (de 0 à N exclu).
         * @return l'élément à la position ( \a x , \a y )
         * @throw out_of_range si \a x et/ou \a y ne rentre pas dans les bornes.
         */
        double getElement(const unsigned int x, const unsigned int y) const;

        /**
         * @brief Permet de modifier l'élément de la colonne \a x et de la ligne \a y avec \a valeur
         * @param[in] x      Le numéro de la colonne que vous voulez modifier (de 0 à N exclu).
         * @param[in] y      Le numéro de la ligne que vous voulez modifier (de 0 à N exclu).
         * @param[in] valeur La valeur que vous voulez mettre à (x, y) sur la matrice.
         * @throw out_of_range en cas de dépassement de capacité
         */
        void setElement(const unsigned int x, const unsigned int y, const double valeur);

        /**
         * @brief Renvoie la taille de la matrice carrée.
         * @return la taille.
         */
        unsigned int taille(void) const;

        /**
        * @brief Renvoie le determinant de la matrice
        * @return la valeur calculée du determinant.
        */
        double determinant(void) const;

        /**
         * @brief Renvoie une matrice privé de sa colonne \a x et de sa ligne \a y .
         * @param[in] x La colonne que l'on veut supprimer
         * @param[in] y La ligne que l'on veut supprimer
         * @return La matrice privé de sa colonne \a x et de sa ligne \a y
         */
        Matrice<N-1> construireSousMatriceMoinsColonneXLigneY(const unsigned int x, const unsigned int y) const;

};


/**
 * @brief Permet d'afficher \a m sur \a fluxSortie.
 * @param[in] fluxSortie Le flux sur lequel écrire.
 * @param[in] m La matrice à afficher.
 * @return le fluxSortie, pour les enchainements d'affichages.
 */
template<unsigned int N>
std::ostream& operator<<(std::ostream &fluxSortie, const Matrice<N> &m);

/**
 * @brief Permet de tester l'égalité entre \a m1 et \a m2
 * @param[in] m1 La première matrice de taille NxN à comparer.
 * @param[in] m2 La seconde matrice de taille NxN à comparer.
 * @return true si elles sont égales, false sinon.
 */
template<unsigned int N>
bool operator==(const Matrice<N> &m1, const Matrice<N> &m2);

#include "Matrice.c"

#endif // MATRICE_HPP_INCLUDED
