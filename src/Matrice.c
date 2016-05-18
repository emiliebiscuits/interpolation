template<unsigned int N>
Matrice<N>::Matrice(void)
{
    this->valeurs.resize(N);
    for(unsigned int i=0;i<N;++i)
    {
        this->valeurs[i].resize(N);
        for(unsigned int j=0;j<N;++j)
        {
            this->valeurs[i][j] = 0.0f;
        }
    }
}

template<unsigned int N>
Matrice<N>::Matrice(const Matrice<N> &autre)
{
    this->valeurs.resize(N);
    for(unsigned int i=0;i<N;++i)
    {
        this->valeurs[i].resize(N);
        std::copy(autre.valeurs[i].begin(), autre.valeurs[i].end(), this->valeurs[i].begin());
    }
}

template<unsigned int N>
Matrice<N>::Matrice(Matrice<N> &&autre)
{
    this->valeurs.resize(N);
    for(unsigned int i=0;i<N;++i)
    {
        this->valeurs[i].resize(N);
        std::copy(autre.valeurs[i].begin(), autre.valeurs[i].end(), this->valeurs[i].begin());
        autre.valeurs[i].clear();
    }
    autre.valeurs.clear();
}

template<unsigned int N>
Matrice<N>::Matrice(std::initializer_list<Point<N>> points)
{
    this->valeurs.resize(N);
    unsigned int x = 0;
    for(auto p : points)
    {
        this->valeurs[x].resize(N);
        for(unsigned int y=0;y<N;++y)
        {
            this->valeurs[x][y] = p.getCoordonne(y+1);
        }
        ++x;
        if (x == N)
        {
            break;
        }
    }
}

template<unsigned int N>
Matrice<N>::~Matrice(void)
{
    for(unsigned int i=0;i<N;++i)
    {
        this->valeurs[i].clear();
    }
    this->valeurs.clear();
}

template<unsigned int N>
Matrice<N>& Matrice<N>::operator=(const Matrice<N> &autre)
{
    for(unsigned int i=0;i<N;++i)
    {
        std::copy(autre.valeurs[i].begin(), autre.valeurs[i].end(), this->valeurs[i].begin());
    }
    return *this;
}

template<unsigned int N>
Matrice<N>& Matrice<N>::operator=(Matrice<N> &&autre)
{
    for(unsigned int i=0;i<N;++i)
    {
        std::copy(autre.valeurs[i].begin(), autre.valeurs[i].end(), this->valeurs[i].begin());
        autre.valeurs[i].clear();
    }
    autre.valeurs.clear();
    return *this;
}

template<unsigned int N>
std::vector<double>& Matrice<N>::operator[](const size_t i)
{
    return this->valeurs.at(i);
}

template<unsigned int N>
double Matrice<N>::getElement(const unsigned int x, const unsigned int y) const
{
    return this->valeurs.at(x).at(y);
}

template<unsigned int N>
void Matrice<N>::setElement(const unsigned int x, const unsigned int y, const double valeur)
{
    this->valeurs.at(x).at(y) = valeur;
}

template<unsigned int N>
unsigned int Matrice<N>::taille(void) const
{
    return N;
}

template<unsigned int N>
std::ostream& operator<<(std::ostream &fluxSortie, const Matrice<N> &m)
{
    fluxSortie << "Matrice (" << N << " x " << N << "):" << std::endl;
    for(unsigned int x=0;x<m.taille();++x)
    {
        fluxSortie << "[ ";
        for(unsigned int y=0;y<m.taille();++y)
        {
            fluxSortie << m.getElement(y, x ) << " ";
        }
        fluxSortie << "]" << std::endl;
    }
    return fluxSortie;
}

template<unsigned int N>
bool operator==(const Matrice<N> &m1, const Matrice<N> &m2)
{
    for(unsigned int x=0;x<N;++x)
    {
        for(unsigned int y=0;y<N;++y)
        {
            if (m1.getElement(x, y) != m2.getElement(x, y)){
                return false;
            }
        }
    }
    return true;
}

template<>
inline double Matrice<0>::determinant(void) const
{
    return 1;
}

template<unsigned int N>
double Matrice<N>::determinant(void) const
{
    double d = 0.0;
    int signe = -1;
    for(unsigned int x=0;x<N;x+=1)
    {
        signe *= -1.0;
        d += signe*getElement(x,0)*construireSousMatriceMoinsColonneXLigneY(x,0).determinant();
    }
    return d;
}



template<unsigned int N>
Matrice<N-1> Matrice<N>::construireSousMatriceMoinsColonneXLigneY(const unsigned int x, const unsigned int y) const
{
    Matrice<N-1> matrice;
    for(unsigned int y2=0;y2<N-1;y2++)
    {
        unsigned int y3 = (y2 >= y) ? y2+1 : y2;
        for(unsigned int x2=0;x2<N-1;x2++)
        {
            unsigned int x3 = (x2 >= x) ? x2+1 : x2;
            matrice.setElement(x2, y2, valeurs[x3][y3]);
        }
    }
    return matrice;
}
