template<unsigned int N, typename V>
PointValue<N, V>::PointValue(void) : Point<N>()
{

}

template<unsigned int N, typename V>
PointValue<N, V>::PointValue(const PointValue<N, V> &autre) : Point<N>(autre)
{
    this->_valeur = autre._valeur;
}

template<unsigned int N, typename V>
PointValue<N, V>::PointValue(PointValue<N, V> &&autre) : Point<N>(std::move(autre))
{
    this->_valeur = autre._valeur;
}

template<unsigned int N, typename V>
PointValue<N, V>::PointValue(std::initializer_list<double> valeurs) : Point<N>(valeurs)
{

}

template<unsigned int N, typename V>
PointValue<N, V>::PointValue(const std::vector<double> &coord) : Point<N>(coord)
{

}

template<unsigned int N, typename V>
PointValue<N, V>::~PointValue(void)
{

}

template<unsigned int N, typename V>
PointValue<N, V>& PointValue<N, V>::operator=(const PointValue<N, V> &autre)
{
    Point<N>::operator=(autre);
    this->_valeur = autre._valeur;
    return *this;
}

template<unsigned int N, typename V>
PointValue<N, V>& PointValue<N, V>::operator=(PointValue<N, V> &&autre)
{
    if (this != &autre)
    {
        Point<N>::operator=(std::move(autre));
        this->_valeur = autre._valeur;
    }
    return *this;
}

template<unsigned int N, typename V>
V PointValue<N, V>::valeur(void) const
{
    return this->_valeur;
}

template<unsigned int N, typename V>
void PointValue<N, V>::valeur(const V val)
{
    this->_valeur = val;
}
