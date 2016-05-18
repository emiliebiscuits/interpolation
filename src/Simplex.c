
template<unsigned int D,unsigned int P>
Simplex<D,P>::Simplex(void)
{
    for(unsigned int i=0;i<P;++i)
    {
        this->points[i] = nullptr;
    }
}

template<unsigned int D,unsigned int P>
Simplex<D,P>::Simplex(std::initializer_list<Point<D>*> points)
{
    unsigned int x = 0;
    for(auto p : points)
    {
        this->points[x]= p;
        ++x;
        if (x >= P)
        {
            break;
        }
    }
}

template<unsigned int D,unsigned int P>
Simplex<D,P>::~Simplex(void)
{

}

template<unsigned int D, unsigned int P>
void Simplex<D,P>::ajoutePoints(const std::list<Point<D>*> &points)
{
    unsigned int x = 0;
    for(auto p : points)
    {
        this->points[x]= p;
        ++x;
        if (x >= P)
        {
            break;
        }
    }
}

template<unsigned int D, unsigned int P>
bool operator==(const Simplex<D,P> &s1, const Simplex<D,P> &s2){
    for(unsigned int x=0;x<P;++x)
    {
        if(!((*(s1.points[x]))==(*(s2.points[x])))){
                return false;
        }
    }
    return true;
}

template<unsigned int D,unsigned int P>
bool Simplex<D,P>::isIn(const Point<D>& p) const
{
    for(unsigned int i=0;i<P;i++)
    {
        Simplex<D,P-1> s=this->removeIniemePoint(i);
        if(!(s.sontDuMemeCote((*points[i]),p)))
        {
            return false;
        }
    }
    return true;
}


template<unsigned int D,unsigned int P>
Simplex<D,P-1> Simplex<D,P>::removeIniemePoint(unsigned int i) const
{
    Simplex<D,P-1> nouveau;
    for(unsigned int i2=0;i2<P-1;i2++)
    {
        unsigned int i3 = (i2 >= i) ? i2+1 : i2;
        nouveau.points[i2] = this->points[i3];
    }
    return nouveau;
}

template<unsigned int D,unsigned int P>
bool Simplex<D,P>::sontDuMemeCote(const Point<D>& p1,const Point<D>& p2) const
{
    return determinant(p1)*determinant(p2)>=0;
}

template<unsigned int D,unsigned int P>
double Simplex<D,P>::determinant(const Point<D>& p)const
{
    Matrice<P> m;
    for(unsigned int x=0;x<P;x++)
    {
        for(unsigned int y=1;y<=D;y++)
        {
            m.setElement(x,y-1,points[x]->getCoordonne(y)-p.getCoordonne(y));
        }
    }
    return m.determinant();
}


template<unsigned int D, unsigned int P>
std::ostream& operator<<(std::ostream &fluxSortie, const Simplex<D,P> &s)
{
	fluxSortie << "Un simplexe " << D << " dimension(s) : " << P <<" Points "<<std::endl;
	for(int i=0; i<P; i++)
	{
		fluxSortie << *(s.points[i]);
	}
	fluxSortie << "......."<<std::endl;
	return fluxSortie;
}


//! Calcul une factoriel
static unsigned int factoriel(unsigned int n)
{
    return (n == 0 || n == 1) ? 1 : factoriel(n-1)*n;
}

template<unsigned int D, unsigned int P>
std::vector<std::pair<double, Point<D>*>> Simplex<D,P>::calculBarycentre(const Point<D> &p) const
{
    std::vector<std::pair<double, Point<D>*>> resultats;
    resultats.resize(P);
    double factoD = (1.0f/(double)factoriel(D));
    for(unsigned int i=0;i<P;++i)
    {
        Simplex<D, P-1> tmp = this->removeIniemePoint(i);

        double volumeP = std::abs(tmp.determinant(p)*factoD);
        double volumeBase = std::abs(tmp.determinant(*(this->points[i]))*factoD);

        resultats.at(i) = std::make_pair(volumeP/volumeBase, this->points[i]);
    }
    return resultats;
}






