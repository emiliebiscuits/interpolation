#include <string>
#include <cassert>
#include <iostream>

#include "Application.hpp"
#include "LecteurFichier.hpp"
#include "AffichagePoint.hpp"
#include "Grapic.h"
#include "PointValue.hpp"


int main(int argc, char **argv)
{
    assert(argc == 1 && argv != NULL);
    std::string fichier("points.txt");
    auto points = lirePointsDepuisFichier<2>(fichier);
    Application<2> app;
    app.remplirApplication(points);
    int timer = 60;
    bool decroit = false;

    bool stop=false;
    int posx, posy;
    grapic::winInit("Projet MIF31", DIMW+300, DIMW);
    while( !stop )
    {
        grapic::backgroundColor(0, 0, 0);
        grapic::winClear();
        stop = grapic::winManageEvent();

        grapic::color(255, 255, 255);
        for(auto i=app.simplexes.begin(); i!=app.simplexes.end(); i++)
		{
			affichageTriangle2D((*i)->points[0], (*i)->points[1], (*i)->points[2]);
		}

        grapic::color(255, 0, 0);
        affichagePoints2D(app.points);

		grapic::mousePos(posx, posy);
		Point<2> p = calculSouris(posx, posy);
		for(auto i=app.simplexes.begin(); i!=app.simplexes.end(); i++)
		{
			if((*i)->isIn(p))
			{
                afficherInterpolation2D(*(*i), p);
                if (grapic::isMousePressed(1) && decroit == false)
                {
                    app.ajouterPointDansSimplex(p, *i);
                    decroit = true;
                }
				break;
			}
		}

        grapic::winDisplay();
        grapic::delay(33);
        timer--;
        if (timer == 0)
        {
            timer = 60;
            decroit = false;
        }
    }
    grapic::winQuit();
	return EXIT_SUCCESS;
}
