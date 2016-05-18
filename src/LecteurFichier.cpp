#include "LecteurFichier.hpp"

void ouvrirEnLecture(const std::string &nomFichier, std::ifstream &fichier)
{
    fichier.open(nomFichier.c_str(), std::ifstream::in);
    if (!fichier.good())
    {
        std::cerr << "Echec lors de l'ouverture de " << nomFichier << " !" << std::endl;
        exit(EXIT_FAILURE);
    }
}
