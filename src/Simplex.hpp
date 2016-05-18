#ifndef SIMPLEX_HPP_INCLUDED
#define SIMPLEX_HPP_INCLUDED
#include <list>
#include <utility>
#include "Point.hpp"
#include "Matrice.hpp"
/**
 *@class Simplex
 * @brief
 */
template<unsigned int D, unsigned int P>
class Simplex{
    public:
        Simplex(void);
        Point<D>* points[P];
    public:

        /**
         * @brief Permet de construire un simplex composé de Point<D>.
         * Cela se passe par des arguments multiples, par exemple :
         * @code
         *      Point<2> p1, p2, p3;
         *      // initialiser les points, bien entendus
         *      Simplex<2,3> m( {p1, p2, p3} );
         * @endcode
         * @param[in] points La liste des arguments multiples de points.
         */
        Simplex(std::initializer_list<Point<D>*> points);

        //! @brief Le destructeur de ce Simplex.
        ~Simplex(void);

        /**
         * @brief Ajoute le contenu de \a points dans ce simplex
         * @param[in] points La liste de Point qu'il faut mettre dans ce simplex
         */
        void ajoutePoints(const std::list<Point<D>*> &points);

        /**
        * @brief Verifie si un point est dans le Simplex
        * @param[in] p Le point dont on souhaite tester l'apartenance au Simplex
        * @return vrai si le point est dans le Simplex
        */
        bool isIn(const Point<D>& p) const;

        /**
        * @brief Créer un Simplex à partir du Simplex avec un point en moins
        * @param[in] i l'indice du point à enlever
        * @return Un simplex de même dimension avec un point en moins
        */
        Simplex<D,P-1> removeIniemePoint(unsigned int i)const;

        /**
        * @brief Verifie si deux points sont du même côté du Simplex
        * @param[in] p Le premier point
        * @param[in] p Le deuxième point
        * @return vrai si les deux points sont du même côté du Simplex
        */
        bool sontDuMemeCote(const Point<D>& p1,const Point<D>& p2)const ;

        /**
        * @brief Retourne le determinant d'un point par rapport au Simplex
        * @param[in] p Le point dont on souhaite connaitre le determinant par rapport au Simplex
        * @return le determinant d'un point par rapport au Simplex
        */
        double determinant(const Point<D>& p)const ;


        /**
         * @brief Calcule les coefficients barycentrique de \b p dans ce simplex.
         * @param[in] p Le Point trouvé dans ce simplex.
         * @return un tableau à N pair (coef et Point concerné)
         */
        std::vector<std::pair<double, Point<D>*>> calculBarycentre(const Point<D> &p) const;
};

/**
 * @brief Permet de tester l'égalité entre \a s1 et \a s2
 * @param[in] m1 Le premier Simplex à comparer.
 * @param[in] m2 Le deuxième Simplex à comparer.
 * @return true si les deux Simpelx sont égaux
 */
template<unsigned int D, unsigned int P>
bool operator==(const Simplex<D,P> &s1, const Simplex<D,P> &s2);

/**
 * @brief Permet d'afficher \a s sur \a fluxSortie.
 * @param[in] fluxSortie Le flux sur lequel écrire.
 * @param[in] m Le Simplex à afficher.
 * @return le fluxSortie, pour les enchainements d'affichages.
 */
template<unsigned int D, unsigned int P>
std::ostream& operator<<(std::ostream &fluxSortie, const Simplex<D,P> &s);

#include "Simplex.c"
#endif // SIMPLEX_HPP_INCLUDED
