/**
 * @file Application.hpp
 * @brief Ce fichier contient une classe qui va etre la structure englobante de l'application
 * @author Laurent Bardoux p1108365
 * @version 1.0
 */
#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

//! @cond
#include <list>
#include <algorithm>

#include "PointValue.hpp"
#include "Simplex.hpp"
//! @endcond


/**
 * @class Application
 * @brief Permet de stocker les éléments Point(s) et Simplex(s)
 * Du fait de sa nature de conteneur simple, les éléments sont accessible directement en lecture.
 * Elle a également la charge de générer les simplexes associés à des Points préalablement lus.
 * Son destructeur va, quant à lui, désallouer les simplexes et Points.
 */
template<unsigned int D>
class Application final
{
    public:
        static const unsigned int NB_POINTS_PAR_SIMPLEX = D+1;
        typedef Simplex<D, NB_POINTS_PAR_SIMPLEX> simplex_t;

        std::vector<Point<D>*> points;   /*! Un conteneur de Points */

        std::list<simplex_t*> simplexes; /*! Un conteneur de Simplexes ND à N+1 points */


        //! On laisse le langage générer ce constructeur par lui meme
        Application(void) = default;

         //! @brief Le destructeur de cette classe, qui va désallouer les points et simplex.
        ~Application(void);

        /**
         * @brief Utilise les \b points pour mailler avec des simplexes.
         * @param[in] points Un ensemble de points lus et valides/alloués.
         */
        void remplirApplication(const std::vector<Point<D>*> &points);

        /**
         * @brief Découpe \a s en D+1 simplexes, ayant \a pt comme point commun.
         * @details \b ATTENTION s est invalidé à la fin de la fonction !
         * @param[in] pt    Le point à ajouter dans l'application.
         * @param[in,out] s Le simplex qui va devoir etre splitter.
         */
        void ajouterPointDansSimplex(const Point<D> &pt, simplex_t *s);

    private:
        /**
         * @brief Calcule un simplex englobant tous les points de l'application.
         * Ceci va ajouter artificiellement D+1 points, qui engloberont tous les autres.
         * Algorithme :
         *      Pour toutes les coordonnés de chaque Point
         *          t = max(t, |coordonné lue|)
         *      t *= 3 (pour tout englober)
         *      création des points (t, 0, ..., 0), (0, t, 0, ..., 0), ..., (0, ..., t)
         *      création du point (-t, -t, ...., -t)
         *      création du simplex
         *
         * A noter que les points sont ajoutés en tete du vector de points.
         */
        void creerSimplexEnglobant(void);

        /**
         * @brief Alloue un simplex en se basant sur \a pourSimplex
         * @param[in] pourSimplex Une liste contenant des adresses de points pour le simplex.
         */
        void creerSimplex(const std::list<Point<D>*> &pourSimplex);

        /**
         * @brief Alloue les points lus dans \a points dans l'application
         * @param[in] points Les points lus en entrée du programme.
         */
        void creerPoints(const std::vector<Point<D>*> &points);

        /**
         * @brief Calcule un t permettant d'englober tous les points.
         * @return La valeur trouvée.
         */
        double trouver_t(void);


        //! On supprime ces fonctions, inutiles.
        Application(const Application<D> &autre) = delete;
        Application(Application<D> &&autre) = delete;
        Application<D>& operator=(const Application<D> &autre) = delete;
        Application<D>& operator=(Application<D> &&autre) = delete;

};

#include "Application.c"

#endif // APPLICATION_HPP_INCLUDED
