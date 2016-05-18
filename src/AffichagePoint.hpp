/**
 * @file AffichagePoint.hpp
 * @brief
 * @author Zhuying LIU p1306849
 * @author Bardoux Laurent p1108365
 * @version 1.0
 */

#ifndef AFFICHAGEPOINT_HPP
#define AFFICHAGEPOINT_HPP

#include <vector>
#include <list>
#include "Grapic.h"
#include "PointValue.hpp"
#include "Simplex.hpp"

//! @brief La taille de la fenetre
#define DIMW 500


/**
 * @brief Affiche le contenu de \a points
 */
void affichagePoints2D(const std::vector<Point<2>*> &points);

/**
 * @brief Affiche une ligne allant de \a debut à \a fin.
 */
void affichageLigne2D(const Point<2> *const debut, const Point<2> *const fin);

/**
 * @brief Calcule le point correspondant à la position de la souris
 */
Point<2> calculSouris(const int x, const int y);

/**
 * @brief Affiche un triangle ( \a p1, \a p2, \a p3 )
 */
void affichageTriangle2D(const Point<2> *const p1, const Point<2> *const p2, const Point<2> *const p3);

/**
 * @brief Permet d'écrire via Grapic les coordonnés et la valeur de \b pt .
 * @param pt [IN] le Point dont on doit écrire les coordonnés.
 * @param x [IN] la coordonné x dans GraPic.
 * @param y [IN] la coordonné y dans GraPic.
 * @cond
 *  pt doit en fait etre un PointValue !
 * @endcond
 */
void afficherPoint2DGrapic(const Point<2> *const pt, const int x, const int y);

/**
 * @brief Permet d'afficher un compte rendu sur l'interpolation.
 * @param simpl [IN] le simplex dans lequel la souris se trouve.
 * @param pt [IN] le point sur lequel est la souris.
 */
void afficherInterpolation2D(const Simplex<2, 3> &simpl, const Point<2> &pt);

#endif
