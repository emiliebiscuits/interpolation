/**
 * @file LecteurFichier.hpp
 * @brief Offre une fonction de lecture de fichiers formatés contenant des Points à N dimension.
 * @author Laurent Bardoux p1108365
 * @version 1.0
 */
#ifndef LECTEURFICHIER_HPP_INCLUDED
#define LECTEURFICHIER_HPP_INCLUDED

//! @cond
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>

#include "PointValue.hpp"
//! @endcond


/**
 * @brief Ouvre \a nomFichier en lecture sur \a fichier .
 * @param[in]  nomFichier Le nom du fichier (en relatif par rapport à l'execution courante ou en absolu).
 * @param[out] fichier    Le ifstream qui sera ouvert par la fonction sur \a nomFichier .
 * @details En cas d'échec à l'ouverture, la commande \b exit(1) sera appelée.
 * Il est également à noter que la \b fermeture du fichier est  \b à  \b faire \b soi-meme.
 * Par exemple :
 * @code
 * #include <string>
 * #include <sstream>
 * #include <fstream>
 * #include "LecteurFichier.hpp"
 *
 * int main(int argc, char **argv)
 * {
 *      std::ifstream fichier;
 *      ouvrirEnLecture(std::string("monFichier.txt"), fichier);
 *
 *      // Actions de lectures ici, comme >>, getline, etc
 *
 *      fichier.close();
 *      return 0;
 * }
 * @endcode
 */
void ouvrirEnLecture(const std::string &nomFichier, std::ifstream &fichier);

/**
 * @brief Permet de lire et \b allouer les \b PointValue contenus dans le fichier \a nomFichier .
 * @param[in] nomFichier Le nom du fichier (en relatif par rapport à l'execution courante ou en absolu).
 * @return Un tableau contenant les adresses des Points, alloués et initialisés.
 * @details Le fichier de nom \a nomFichier doit etre créé depuis le script \b generate.py pour etre fonctionnel.
 * Par exemple :
 * @code
 * #include <iostream>
 * #include <vector>
 * #include <string>
 * #include "Point.hpp"
 * #include "LecteurFichier.hpp"
 *
 * int main(int argc, char **argv)
 * {
 *      // Lecture des points
 *      std::vector<Point<2>*> points = lirePointsDepuisFichier(std::string("points.txt"));
 *
 *      // Affichage
 *      for(auto it : points)
 *      {
 *          std::cout << *it << std::endl;
 *      }
 *      return 0;
 * }
 * @endcode
 */
template<unsigned int Dimension>
std::vector<Point<Dimension>*> lirePointsDepuisFichier(const std::string &nomFichier);

#include "LecteurFichier.c"

#endif // LECTEURFICHIER_HPP_INCLUDED
