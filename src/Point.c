template<unsigned int D>
void Point<D>::RaZCoordonnes(void)
{
    this->coordonnes.clear();
    this->coordonnes.resize(D, 0.0f);
}

template<unsigned int D>
Point<D>::Point(void)
{
	this->coordonnes.resize(D, 0.0f);
}

template<unsigned int D>
Point<D>::Point(const std::vector<double> &_coordonnes)
{
	this->coordonnes.resize(D, 0.0f);
	std::copy(_coordonnes.begin(), _coordonnes.end(), this->coordonnes.begin());
}

template<unsigned int D>
Point<D>::Point(const Point<D> &autre)
{
	this->coordonnes.resize(D, 0.0f);
	std::copy(autre.coordonnes.begin(), autre.coordonnes.end(), this->coordonnes.begin());
}

template<unsigned int D>
Point<D>::Point(Point<D> &&autre)
{
	this->coordonnes.resize(D, 0.0f);
	std::copy(autre.coordonnes.begin(), autre.coordonnes.end(), this->coordonnes.begin());
	autre.coordonnes.clear();
}

template<unsigned int D>
Point<D>::Point(std::initializer_list<double> valeurs)
{
    unsigned int compteur = 0;
    this->coordonnes.resize(D, 0.0f);
    for(auto v : valeurs)
    {
        if (compteur == D)
        {
            break;
        }
        this->coordonnes[compteur] = v;
        ++compteur;
    }
}

template<unsigned int D>
Point<D>::~Point(void)
{
	this->coordonnes.clear();
}

template<unsigned int D>
Point<D>& Point<D>::operator=(const Point<D> &autre)
{
	this->RaZCoordonnes();
	std::copy(autre.coordonnes.begin(), autre.coordonnes.end(), this->coordonnes.begin());
	return *this;
}

template<unsigned int D>
Point<D>& Point<D>::operator=(Point<D> &&autre)
{
	this->RaZCoordonnes();
    std::copy(autre.coordonnes.begin(), autre.coordonnes.end(), this->coordonnes.begin());
	autre.coordonnes.clear();
	return *this;
}

template<unsigned int D>
Point<D> operator-(const Point<D> &p1, const Point<D> &p2)
{
    std::vector<double> coordonnes(D, 0.0f);
    for(unsigned int i=1;i<=D;++i)
    {
        coordonnes.at(i-1) = p1.getCoordonne(i) - p2.getCoordonne(i);
    }
    return Point<D>(coordonnes);
}

template<unsigned int D>
Point<D> operator+(const Point<D> &p1, const Point<D> &p2)
{
    std::vector<double> coordonnes(D, 0.0f);
    for(unsigned int i=1;i<=D;++i)
    {
        coordonnes.at(i-1) = p1.getCoordonne(i) + p2.getCoordonne(i);
    }
    return Point<D>(coordonnes);
}

template<unsigned int D>
double Point<D>::getCoordonne(const unsigned int n) const
{
	return this->coordonnes.at(n-1);
}

template<unsigned int D>
void Point<D>::setCoordonnes(const std::vector<double> &coordonnes)
{
    this->RaZCoordonnes();
    std::copy(coordonnes.begin(), coordonnes.end(), this->coordonnes.begin());
}

template<unsigned int D>
double Point<D>::distanceEntre(const Point<D> &autre) const
{
	double somme = 0.0f;
	//! sqrt((x_autre - x_this)² + etc...)
	for(unsigned int i=0;i<this->coordonnes.size();++i)
	{
		somme += std::pow(autre.coordonnes.at(i) - this->coordonnes.at(i), 2.0f);
	}
	return std::sqrt(somme);
}

template<unsigned int D>
std::ostream& operator<<(std::ostream &fluxSortie, const Point<D> &cible)
{
	fluxSortie << "Un point à " << D << " dimension(s) :" << std::endl << "\t(";
	for(unsigned int i=1;i<=D;++i)
	{
        fluxSortie << cible.getCoordonne(i) << ", ";
	}
	fluxSortie << "\b\b)" << std::endl;
	return fluxSortie;
}


template<unsigned int D>
bool operator==(const Point<D> &p1, const Point<D> &p2)
{
	for(unsigned int i=1;i<=D;++i)
	{
		if (p1.getCoordonne(i) != p2.getCoordonne(i))
		{
			return false;
		}
    }
	return true;
}

template<unsigned int D>
Point<D> operator*(const double t, const Point<D> &p)
{
    std::vector<double> coordonnes(D, 0.0);
    for(unsigned int i=0;i<D;++i)
    {
        coordonnes.at(i) = p.getCoordonne(i+1)*t;
    }
    return Point<D>(coordonnes);
}

template<unsigned int D>
Point<D> operator*(const Point<D> &p, const double t)
{
    return t*p;
}
