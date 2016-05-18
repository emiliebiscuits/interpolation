#include <iostream>
template<unsigned int D>
Application<D>::~Application(void)
{
    for(unsigned int i=0;i<this->points.size();++i)
    {
        delete this->points.at(i);
    }
    this->points.clear();
    for(auto it=this->simplexes.begin();it!=this->simplexes.end();++it)
    {
        delete *it;
    }
    this->simplexes.clear();
}

template<unsigned int D>
void Application<D>::creerPoints(const std::vector<Point<D>*> &points)
{
    const unsigned int NB_POINTS_ENGLOBANTS = this->NB_POINTS_PAR_SIMPLEX;
    this->points.resize(points.size()+NB_POINTS_ENGLOBANTS);

    auto debut = this->points.begin();
    std::advance(debut, NB_POINTS_ENGLOBANTS);

    std::copy(points.begin(), points.end(), debut);
}

template<unsigned int D>
void Application<D>::creerSimplex(const std::list<Point<D>*> &pourSimplex)
{
    simplex_t *s = new simplex_t();
    s->ajoutePoints(pourSimplex);
    this->simplexes.push_back(s);
}

template<unsigned int D>
double Application<D>::trouver_t(void)
{
    const double COEFFICIENT = 3.0f;
    auto it = this->points.begin();
    double t = 0.0f;
    std::advance(it, D+1);
    for(;it!=this->points.end();++it)
    {
        for(unsigned int i=1;i<=D;++i)
        {
            t = std::max(std::abs((*it)->getCoordonne(i)), t);
        }
    }
    return (t == 0.0f) ? 45 : t*COEFFICIENT;
}

template<unsigned int D>
void Application<D>::creerSimplexEnglobant(void)
{
    double t = this->trouver_t();
    std::list<Point<D>*> pourSimplex;
    std::vector<double> coordonnes(D, 0.0f);
	std::vector<double> coordonnes2(D, -t);
	PointValue<D, float> *tmp = nullptr;

    // Création des D premiers points du simplex englobant
    for(unsigned int i=0;i<D;++i)
    {
        coordonnes.at(i) = t;
        tmp = new PointValue<D, float>(coordonnes);
        tmp->valeur(0.0f);
        this->points.at(i+1) = tmp;
        pourSimplex.push_back(this->points.at(i+1));
        coordonnes.at(i) = 0.0f;
    }

    // Le point avec -t partout
    tmp = new PointValue<D, float>(coordonnes2);
    tmp->valeur(0.0f);
    this->points.at(0) = tmp;
    pourSimplex.push_back(this->points.at(0));

    this->creerSimplex(pourSimplex);
}

template<unsigned int D>
void Application<D>::remplirApplication(const std::vector<Point<D>*> &points)
{
    this->creerPoints(points);
    this->creerSimplexEnglobant();

    //! A partir de là, les D+1 premiers points sont ceux du simplex englobant
    for(unsigned int i=this->NB_POINTS_PAR_SIMPLEX;i<this->points.size();++i)
    {
        for(auto sim=this->simplexes.begin();sim!=this->simplexes.end();++sim)
        {
            if ((*sim)->isIn(*(this->points.at(i))))
            {
                std::vector<Point<D>*> pts(this->NB_POINTS_PAR_SIMPLEX, nullptr);
                for(unsigned int p=0;p<D+1;++p)
                {
                    pts.at(p) = (*sim)->points[p];
                }

                std::list<Point<D>*> pourSimplex;
                for(unsigned int exclu=0;exclu<this->NB_POINTS_PAR_SIMPLEX;++exclu)
                {
                    pourSimplex.push_back(this->points.at(i));
                    for(unsigned int j=0;j<this->NB_POINTS_PAR_SIMPLEX;++j)
                    {
                        if (j != exclu)
                        {
                            pourSimplex.push_back(pts.at(j));
                        }
                    }
                    this->creerSimplex(pourSimplex);
                    pourSimplex.clear();
                }

                simplex_t *temp = *sim;
                this->simplexes.remove(*sim);
                delete temp;
                break;
            }
        }
    }
}

template<unsigned int D>
void Application<D>::ajouterPointDansSimplex(const Point<D> &pt, simplex_t *s)
{
    this->simplexes.remove(s);
    PointValue<D> *point = new PointValue<D>();
    std::vector<double> coordonne(D, 0.0f);
    for(unsigned int i=1;i<=D;++i)
    {
        coordonne.at(i-1) = pt.getCoordonne(i);
    }
    point->setCoordonnes(coordonne);
    this->points.push_back(point);

    std::vector<std::pair<double, Point<D>*>> calculs = s->calculBarycentre(pt);
    float valeur = 0.0f;
    std::for_each(calculs.begin(), calculs.end(), [&valeur](std::pair<double, Point<D>*> &v){
        if (dynamic_cast<PointValue<D>*>(v.second))
        {
            PointValue<D> *pt = static_cast<PointValue<D>*>(v.second);
            valeur += v.first*pt->valeur();
        }
    });
    point->valeur(valeur);
    std::cout << "Création d'un point (" << point->getCoordonne(1) << ", " << point->getCoordonne(2);
    std::cout << ") : " << valeur << std::endl;

    std::list<Point<D>*> pourSimplex;
    for(unsigned int exclu=0;exclu<this->NB_POINTS_PAR_SIMPLEX;++exclu)
    {
        pourSimplex.push_back(point);
        for(unsigned int j=0;j<this->NB_POINTS_PAR_SIMPLEX;++j)
        {
            if (j != exclu)
            {
                pourSimplex.push_back(s->points[j]);
            }
        }
        this->creerSimplex(pourSimplex);
        pourSimplex.clear();
    }

    delete s;
}










