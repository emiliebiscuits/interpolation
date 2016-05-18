#include <sstream>
#include <vector>
#include <utility>

#include "AffichagePoint.hpp"

/**
 * @def CENTRE
 * @brief
 */
#define CENTRE 250

/**
 * @def UNITE
 * @brief
 */
#define UNITE 5


/**
 * @enum position_t
 * @brief Permet de limiter les choix possibles pour \b convertir()
 */
typedef enum {
    POS_X = 1,
    POS_Y = 2
} position_t;

/**
 * @fn static double convertir(const Point<2> *const p, const position_t N)
 * @brief Cette fonction convertir la Nième coordonné d'un Point<2> \b p vers le système de coordonnés de GraPic.
 * @param p [IN] le Point<2> dont on va calculer la Nième coordonné.
 * @param N [IN] la Nième coordonné voulue.
 * @return la coordonné N convertit dans le système GraPic.
 */
static double convertir(const Point<2> *const p, const position_t N)
{
    return (CENTRE + p->getCoordonne(N)*UNITE);
}

/**
 * @fn static double deconvertir(const double valeur)
 * @brief Permet de passer d'une coordonné GraPic vers le système de coordonnés classique.
 * @param valeur [IN] la valeur à convertir vers le système classique.
 * @return Cette valeur calculée.
 */
static double deconvertir(const double valeur)
{
    return (valeur - (double)CENTRE)/(double)UNITE;
}

void affichagePoints2D(const std::vector<Point<2>*> &points)
{
    const int RAYON_POINT = 4;
	for(auto i=points.begin();i!=points.end();++i)
    {
        double x = convertir((*i), POS_X);
        double y = convertir((*i), POS_Y);
        grapic::rectangleFill(x-RAYON_POINT, y-RAYON_POINT, x+RAYON_POINT, y+RAYON_POINT);
    }
}

void affichageLigne2D(const Point<2> *const debut, const Point<2> *const fin)
{
    grapic::line(convertir(debut, POS_X), convertir(debut, POS_Y), convertir(fin, POS_X), convertir(fin, POS_Y));
}

Point<2> calculSouris(const int x, const int y)
{
    return Point<2>({deconvertir(x), deconvertir(y)});
}

void affichageTriangle2D(const Point<2> *const p1, const Point<2> *const p2, const Point<2> *const p3)
{
    affichageLigne2D(p1, p2);
    affichageLigne2D(p1, p3);
    affichageLigne2D(p2, p3);
}


void afficherPoint2DGrapic(const Point<2> *const pt, const int x, const int y)
{
    std::ostringstream os;
    os.precision(2);
    os << "(" << std::fixed << pt->getCoordonne(1) << ", " << std::fixed << pt->getCoordonne(2) << ")";
    if (dynamic_cast<const PointValue<2, float> *const>(pt))
    {
        const PointValue<2, float> *const ptv = static_cast<const PointValue<2, float> *const>(pt);
        os << " : " << std::fixed << ptv->valeur();
    }
    grapic::print(x, y, os.str().c_str());
}

void afficherInterpolation2D(const Simplex<2, 3> &simpl, const Point<2> &pt)
{
    grapic::color();
    for(unsigned int i=0;i<3;++i)
    {
        afficherPoint2DGrapic(simpl.points[i], 400, 20*(i));
    }
    afficherPoint2DGrapic(&pt, 400, 470);
    std::vector<std::pair<double, Point<2>*>> calculs = simpl.calculBarycentre(pt);
    std::ostringstream os;
    double fQ = 0.0f;
    unsigned int compteur = 2;
    os.precision(2);
    os << "f(Q) = ";
    for(auto it=calculs.begin();it!=calculs.end();++it)
    {
        PointValue<2, float> *tmp = static_cast<PointValue<2, float>*>((*it).second);
        os << std::fixed << (*it).first << "*" << tmp->valeur();
        if (compteur > 0)
        {
            os << " + ";
        }
        --compteur;
        fQ += (*it).first*tmp->valeur();
    }
    grapic::print(400, 450, os.str().c_str());
    os.str(std::string());
    os << "f(Q) = " << std::fixed << fQ;
    grapic::print(400, 430, os.str().c_str());
    grapic::color(0, 128, 255);
    affichageTriangle2D(simpl.points[0], &pt, simpl.points[1]);
    affichageTriangle2D(simpl.points[0], &pt, simpl.points[2]);
    affichageTriangle2D(simpl.points[1], &pt, simpl.points[2]);
}
