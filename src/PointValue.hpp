/**
 * @file PointValue.hpp
 * @brief Définit un Point à N dimension possédant une valeur flottante interne, pour des calculs d'interpolations.
 * @author Laurent Bardoux p1108365
 * @version 1.0
 */
#ifndef POINTVALUE_HPP_INCLUDED
#define POINTVALUE_HPP_INCLUDED

//! @cond
#include <initializer_list>

#include "Point.hpp"
//! @endcond


/**
 * @class PointValue
 * @brief Laisse le soin à Point de se charger des traitements liés aux simplexes, et se focalise sur la gestion de donnée(s)
 */
template<unsigned int N, typename V=float>
class PointValue final : public Point<N>
{
    private:
        V _valeur; /*! Une valeur stockée dans ce point */

    public:
        /**
         * @brief Le constructeur par défaut
         * @details _valeur aura donc sa valeur par ... défaut !
         * Appel au constructeur par défaut de Point<N> également.
         */
        PointValue(void);

        /**
         * @brief Constructeur par copie
         * @param[in] autre Le point à copier.
         */
        PointValue(const PointValue<N, V> &autre);

        /**
         * @brief Constructeur par déplacement.
         * @param[in,out] autre Le point auquel prendre ses attributs.
         */
        PointValue(PointValue<N, V> &&autre);

        /**
         * @brief Un constructeur prenant un nombre variable de valeurs pour les coordonnés.
         * @param[in] valeurs La liste des coordonnés pour ce points.
         * @code
         * // crée un point de coordonnés x=2.5, y=5.2.
         * PointValue<2, int> point({2.5, 5.2});
         * @endcode
         */
        PointValue(std::initializer_list<double> valeurs);

        /**
         * @brief Un constructeur prenant un tableau de coordonnés en paramètre.
         * @param[in] coord Le tableau de coordonnés.
         */
        PointValue(const std::vector<double> &coord);

         //! @brief Le destructeur
        ~PointValue(void);

        /**
         * @brief Affectation par copie de \a autre.
         * @param[in] autre Le point à copier.
         * @return Une référence sur this.
         */
        PointValue<N, V>& operator=(const PointValue<N, V> &autre);

        /**
         * @brief Affection via la Rvalue \a autre
         * @param[in,out] autre Le point auquel prendre ses attributs.
         * @return Une référence sur this.
         */
        PointValue<N, V>& operator=(PointValue<N, V> &&autre);

        /**
         * @brief Un accesseur pour la valeur de ce Point.
         * @return cette valeur
         */
        V valeur(void) const;

        /**
         * @brief Affecte \a val à ce PointValue.
         * @param[in] val La nouvelle valeur que le Point va devoir contenir.
         */
        void valeur(const V val);

};

#include "PointValue.c"

#endif // POINTVALUE_HPP_INCLUDED
