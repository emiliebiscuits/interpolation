template<unsigned int Dimension>
std::vector<Point<Dimension>*> lirePointsDepuisFichier(const std::string &nomFichier)
{
    std::ifstream fichier;
    ouvrirEnLecture(nomFichier, fichier);

    std::vector<Point<Dimension>*> resultat;
    std::string ligne;
    while(std::getline(fichier, ligne))
    {
        std::vector<double> valeurs;
        std::stringstream s(ligne);
        double valeur;

        // Chaque ligne contient (Dimension) valeurs, et la dernière valeur est à stocker dans le Point.
        while(s >> valeur)
        {
            valeurs.push_back(valeur);
        }
        float val = static_cast<float>(valeurs.at(Dimension));
        valeurs.pop_back();

        PointValue<Dimension> *p = new PointValue<Dimension>(valeurs);
        p->valeur(val);
        resultat.push_back(p);
    }
    fichier.close();
    return resultat;
}
