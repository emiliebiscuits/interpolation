/**
 * @file Point.hpp
 * @brief Ce module offre une classe décrivant un point générique dans un espace à D dimensions.
 * De ce fait, les calculs communs aux autres points devront êtres implémentés ici.
 * @author Laurent Bardoux p1108365
 * @version 1.0
 */
#ifndef POINT_HPP_INCLUDED
#define POINT_HPP_INCLUDED

//! @code
#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>
//! @endcode


/**
 * @brief Une previous déclaration pour la classe Simplex, qui sera utilisé plus tard.
 */
template<unsigned int D, unsigned int P>
class Simplex;


/**
 * @class Point
 * @brief La classe décrivant un point à D dimension.
 * @details La dimension est alors gérée par le template, et tous les calculs se basant dessus devront
 * avoir recours à ce D.
 */
template<unsigned int D>
class Point
{
	protected:
		std::vector<double> coordonnes; /*! Le vecteur contenant D coordonnés pour ce Point */

        //! @brief Ré-initialise le conteneur des coordonnés.
		void RaZCoordonnes(void);

	public:
		/**
		 * @brief Le constructeur par défaut
		 * Ce constructeur va permettre de créer un Point situé sur l'origine du repère utilisé.
		 * Soit (0, 0, ..., 0)
		 */
		Point(void);

		/**
		 * @brief Ce constructeur permet d'initialiser les coordonnés du Point créé.
		 * Attention, le vector coordonnés doit contenir D éléments !
		 * @param[in] _coordonnes Le vector contenant les coordonnés voulues pour ce Point.
		 */
		Point(const std::vector<double> &_coordonnes);

		/**
		 * @brief Le constructeur par copie.
		 * @param[in] autre Le point dont tous les éléments vont être copiés.
		 */
		Point(const Point<D> &autre);

		/**
		 * @brief Le constructeur par rvalue.
		 * Il y aura peut-être des cas particuliers ici.
		 * @param[in] autre Le point dont tous les éléments vont être copiés.
		 */
		Point(Point<D> &&autre);

		/**
		 * @brief Un constructeur prenant un nombre variable d'arguments
		 * Ceci permet de remplir le point en énumérant les valeurs que l'on veut lui donner.
		 * @param[in] valeurs Un ensemble de double à entrer comme coordonnés.
		 *
		 * USAGE :
		 * @code
		 *      Point<2> p( {2.5f, 5.8f} );
		 * @endcode
		 */
		Point(std::initializer_list<double> valeurs);

        //! @brief Le destructeur de ce Point.
		virtual ~Point(void);

		/**
		 * @brief Redéfinition de l'opérateur d'affectation pour un élément normal.
		 * @param[in] autre Le point dont il va falloir copier tous le contenu.
		 * @return Une référence sur le point concerné (pour les a = b = c par exemple).
		 */
		Point& operator=(const Point<D> &autre);

		/**
		 * @brief Redéfinition de l'opérateur d'affectation pour une rvalue.
		 * @param[in,out] autre Le point dont il va falloir copier tous le contenu.
		 * @return Une référence sur le point concerné (pour les a = b = c par exemple).
		 */
		Point& operator=(Point<D> &&autre);


		/**
		 * @brief Un accesseur en lecture pour la \a n ième coordonnés du Point.
		 * @param[in] n Un entier entre 1 et D
		 * @throw out_of_range en cas de dépassement de n.
		 * @return la n-ième coordonné de ce Point.
		 */
		double getCoordonne(const unsigned int n) const;

        /**
         * @brief Permet d'affecter un tableau de coordonnés à ce Point.
         * @param[in] coordonnes Le tableau contenant D coordonnés.
         */
		void setCoordonnes(const std::vector<double> &coordonnes);

		/**
		 * @brief Calcule la distance entre ce point et \a autre.
		 * @param[in] autre Le second point pour le calcul de la distance
		 * @return un double contenant cette distance.
		 */
		double distanceEntre(const Point<D> &autre) const;

};


/**
 * @brief Permet d'afficher \a cible sur \a fluxSortie.
 * @param[in,out] fluxSortie Le flux sur lequel écrire le contenu du Point.
 * @param[in] cible Le Point qu'il faut écrire sur \a fluxSortie
 * @return fluxSortie modifié (pour les out << Point1 << Point2 par exemple).
 */
template<unsigned int D>
std::ostream& operator<<(std::ostream &fluxSortie, const Point<D> &cible);

/**
 * @brief Permet de faire la différence entre \a p1 et \a p2
 * @param[in] p1 Le premier point dont on veut faire la soustraction.
 * @param[in] p2 Le second point dont on veut faire la soustraction.
 * @return un Point contenant p1-p2.
 */
template<unsigned int D>
Point<D> operator-(const Point<D> &p1, const Point<D> &p2);

/**
 * @brief Permet de faire la somme de \a p1 et \a p2
 * @param[in] p1 Le premier point.
 * @param[in] p2 Le second point.
 * @return un Point contenant p1+p2.
 */
template<unsigned int D>
Point<D> operator+(const Point<D> &p1, const Point<D> &p2);

/**
 * @brief Permet la multiplication de \a p par un scalaire \a t
 * @param[in] t Le scalaire par lequel multiplier.
 * @param[in] p Le Point qu'il faut multiplier.
 * Note : cette fonction est accompagnée de sa jumelle, qui ne sera pas documentée.
 * @return le Point résultat.
 */
template<unsigned int D>
Point<D> operator*(const double t, const Point<D> &p);

template<unsigned int D>
Point<D> operator*(const Point<D> &p, const double t);

/**
 * @brief Teste l'égalité entre \a p1 et \a p2
 * @param[in] p1 Le premier point.
 * @param[in] p2 Le second point.
 * @return true s'ils sont égaux, false sinon.
 */
template<unsigned int D>
bool operator==(const Point<D> &p1, const Point<D> &p2);

#include "Point.c"

#endif // POINT_HPP_INCLUDED
