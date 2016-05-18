#include <vector>
#include <iostream>
#include "Point.hpp"
#include "Simplex.hpp"
#include "Matrice.hpp"
/*
Ecrire les tests unitaires ici !
Made by : Laurent Bardoux
Bien respecter l'écriture
*/


//!!!!!!!!!!!!!!!!!!!!TEST POINT!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TEST(point1 - point2 en 2D)
{
    Point<2> p1({5.0,5.0});
    Point<2> p2({2.0,2.0});
    Point<2> oracle({3.0,3.0});

    Point<2> res = (p1 - p2);
    for(unsigned int i=1;i<=2;++i)
    {
        CHECK(res.getCoordonne(i) == oracle.getCoordonne(i));
    }
}

TEST(initialise point avec liste)
{
    Point<4> p({25.0f, 21.0f, 5.2f, 0.0f});
    CHECK(p.getCoordonne(1) == 25.0f);
    CHECK(p.getCoordonne(2) == 21.0f);
    CHECK(p.getCoordonne(3) == 5.2f);
    CHECK(p.getCoordonne(4) == 0.0f);
}

TEST(distance 1d)
{
	std::vector<double> v0(1,0.0);
	std::vector<double> v1(1,1.0);
	std::vector<double> v42(1,42.0);
	Point<1> p0(v0);
	Point<1> p1(v1);
	Point<1> p42(v42);
	CHECK(p0.distanceEntre(p1) == 1);
	CHECK(p1.distanceEntre(p0) == 1);
	CHECK(p0.distanceEntre(p42) == 42);
	CHECK(p1.distanceEntre(p42) == 41);
}
TEST(distance 2d)
{
	Point<2> p0_0;
	Point<2> p3_4;
	Point<2> p42_0;
	std::vector<double> v0_0(2,0.0);
	std::vector<double> v3_4(2,3.0);
	v3_4[1]=4;
	std::vector<double> v42_0(2,42.0);
	v42_0[1]=0;
	p0_0.setCoordonnes(v0_0);
	p3_4.setCoordonnes(v3_4);
	p42_0.setCoordonnes(v42_0);
	CHECK(p0_0.distanceEntre(p42_0) == 42);
	CHECK(p0_0.distanceEntre(p3_4) == 5);
	CHECK(p3_4.distanceEntre(p0_0) == 5);
}

TEST(somme points 3D)
{
    Point<3> p({5.0, 2.0, 8.0});
    Point<3> p2({1.0, 2.0, 4.0});
    Point<3> oracle({6.0, 4.0, 12.0});
    CHECK((p+p2) == oracle);
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!SIMPLEX!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TEST(simplex not=)
{
    Point<2> p1({1.0,2.0});
    Point<2> p2({3.0,4.0});
    Simplex<2,2> s1({&p1,&p2});
    Point<2> p3({1.0,3.0});
    Point<2> p4({6.0,6.0});
    Simplex<2,2> s2({&p3,&p4});
	CHECK(!(s1 == s2));
}

TEST(simplex ==)
{
    Point<2> p1({1.0,2.0});
    Point<2> p2({3.0,4.0});
    Simplex<2,2> s1({&p1,&p2});
    Point<2> p3({1.0,2.0});
    Point<2> p4({3.0,4.0});
    Simplex<2,2> s2({&p3,&p4});
	CHECK(s1 == s2);
}

//!!!!!!!!!!!!!!!!!!!!!!MATRICE!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
TEST(constructeur par defaut matrice)
{
    Matrice<4> m;
    for(unsigned int i=0;i<4;++i)
    {
        for(unsigned int j=0;j<4;++j)
        {
            CHECK(m.getElement(i, j) == 0.0);
        }
    }
}

TEST(liste initialisation points)
{
    std::vector<double> v(3, 3.0);
    Point<3> p1(v);
    Matrice<3> m({p1, p1, p1});
    for(unsigned int i=0;i<m.taille();++i)
    {
        for(unsigned int j=0;j<m.taille();++j)
        {
            CHECK(m.getElement(i, j) == 3.0);
        }
    }
}
TEST(sous matrice)
{
    Matrice<1> mat;
    CHECK(mat.construireSousMatriceMoinsColonneXLigneY(0,0).taille() == 0);
}

TEST(sous matrice 3d)
{
    Point<3> p1({1.0,2.0,3.0});
    Point<3> p2({4.0,5.0,6.0});
    Point<2> p12({5.0,6.0});
    Point<2> p22({2.0,3.0});
    Matrice<3> m({p1, p2, p1});
    Matrice<2> m2({p12, p22});
    CHECK(m.construireSousMatriceMoinsColonneXLigneY(0, 0) == m2);
}
TEST(sous matrice 3d centre)
{
    Point<3> p1({1.0,2.0,3.0});
    Point<3> p2({4.0,5.0,6.0});
    Point<2> p12({1.0,3.0});
    Point<2> p22({1.0,3.0});
    Matrice<3> m({p1, p2, p1});
    Matrice<2> m2({p12, p22});
    CHECK(m.construireSousMatriceMoinsColonneXLigneY(1, 1) == m2);
}
TEST(determinant 11 0)
{
    Point<1> p1;
    std::vector<double> v1(1, 5.0);
    p1.setCoordonnes(v1);
    Matrice<1> m({p1});
    CHECK(m.determinant() == 5.0);
}
TEST(determinant 22 0)
{
    Point<2> p1;
    std::vector<double> v1(2, 5.0);
    v1[1]=3;
    p1.setCoordonnes(v1);
    Matrice<2> m({p1, p1});
    CHECK(m.determinant() == 0);
}
TEST(determinant 33 0)
{
    Point<3> p1;
    Point<3> p2;
    Point<3> p3;
    std::vector<double> v1(3, 1.0);
    std::vector<double> v2(3, 2.0);
    std::vector<double> v3(3, 3.0);
    v1[2]=5;
    v2[2]=6;
    v3[2]=7;
    v3[1]=4;
    p1.setCoordonnes(v1);
    p2.setCoordonnes(v2);
    p3.setCoordonnes(v3);
    Matrice<3> m({p1, p2,p3});
    CHECK(m.determinant() == 4);
}

TEST(simplex removeInieme 0)
{
    Point<2> p1({1.3,2.3});
    Point<2> p2({3.3,4.3});
    Simplex<2,2> s1({&p1,&p2});
    Point<2> p3({3.3,4.3});
    Simplex<2,1> s2({&p3});
    s1.removeIniemePoint(0);
	CHECK(s1.removeIniemePoint(0) == s2);
}

TEST(sontDuMemeCote 1 1)
{
    Point<1> p1({1});
    Simplex<1,1> s1({&p1});
    Point<1> p2({2});
    Simplex<1,1> s2({&p2});
    Point<1> p3({3});
    Simplex<1,1> s3({&p3});
    CHECK(s1.sontDuMemeCote(p2,p3));
    CHECK(!s2.sontDuMemeCote(p1,p3));
    CHECK(s3.sontDuMemeCote(p1,p2));
}

TEST(sontDuMemeCote 2 2)
{
    Point<2> p1({1,1});
    Point<2> p2({2,-3});
    Simplex<2,2> s1({&p1,&p2});
    Point<2> p3({-3,5});
    Simplex<2,2> s2({&p1,&p3});
    Simplex<2,2> s3({&p2,&p3});
    Point<2> p4({-4,-42});
    Simplex<2,2> s4({&p1,&p4});
    Simplex<2,2> s5({&p2,&p4});
    Simplex<2,2> s6({&p3,&p4});
    CHECK(s1.sontDuMemeCote(p3,p4));
    CHECK(s1.sontDuMemeCote(p4,p3));
    CHECK(s2.sontDuMemeCote(p2,p4));
    CHECK(!s3.sontDuMemeCote(p1,p4));
    CHECK(!s4.sontDuMemeCote(p2,p3));
    CHECK(s5.sontDuMemeCote(p1,p3));
    CHECK(s6.sontDuMemeCote(p1,p2));
}

TEST(isIn 2 2)
{
    Point<2> p1({2,2});
    Point<2> p2({3,-2});
    Point<2> p3({-5,1});
    Simplex<2,3> s1({&p1,&p2,&p3});
    Point<2> pt({0,0});
    CHECK(s1.isIn(pt));
    pt=Point<2>({1,0});
    CHECK(s1.isIn(pt));
    pt=Point<2>({0,1});
    CHECK(s1.isIn(pt));
    pt=Point<2>({1,1});
    CHECK(s1.isIn(pt));
    pt=Point<2>({1,2});
    CHECK(!s1.isIn(pt));
    pt=Point<2>({2,1});
    CHECK(s1.isIn(pt));
}
TEST(isIn2 2 2)
{
    Point<2> p1({1,0});
    Point<2> p2({0,1});
    Point<2> p3({1,1});
    Simplex<2,3> s1({&p1,&p2,&p3});
    Point<2> pt({0,0});
    CHECK(!s1.isIn(pt));
    pt=Point<2>({0.4,0.4});
    CHECK(!s1.isIn(pt));
    pt=Point<2>({0.51,0.51});
    CHECK(s1.isIn(pt));
}
