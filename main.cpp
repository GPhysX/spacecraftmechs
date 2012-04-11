//
// main.cc for graviball in
//
// Made by
// Login   <@epita.fr>
//
// Started on  Sun Nov 19 14:51:54 2006
// Last update Sun Nov 19 19:22:44 2006
//

#include <iostream>
#include "factory/vertex.h"

#include "MathTools/Vector.hpp"
#include "MathTools/Quaternion.hpp"
#include "SpaceCraft/SpaceCraft.hpp"

using namespace std;
using namespace MathTools;

double at[] = {0, 1, 1};
double ar[] = {1, 1};

SpaceCraftMech::SpaceCraft craft(at, ar);

int					main (int argc __attribute__ ((unused)), char* argv[] __attribute__ ((unused)))
{
	GLUquadricObj*	quadric;

	if (!vertexInit (640, 480, 16, 0))
	{
		quadric = gluNewQuadric ();
		gluQuadricNormals (quadric, GLU_SMOOTH);
		gluQuadricTexture (quadric, GL_TRUE);

		vertexSetMouse (0, 1);
		vertexSetWindow ("Spacecraft test", NULL);
		vertexLoop (0);

        const double dangle = 2 * M_PI / 10;
		glVertex.factor = 1e-3;

		while (!vertexLoop (0) && !VERTEX_KEY_PRESSED (VERTEX_KEY_ESCAPE))
		{
		    VectorD vt(0, 0, 0);   // translation command
		    VectorD vr(0, 0, 0);   // rotation command

            double rzCommand = 0, rxCommand = 0;

		    if(VERTEX_KEY_PRESSED(VERTEX_KEY_UP))
                rxCommand = -dangle;
		    else if(VERTEX_KEY_PRESSED(VERTEX_KEY_DOWN))
                rxCommand = dangle;

		    if(VERTEX_KEY_PRESSED(VERTEX_KEY_LEFT))
                rzCommand = dangle;
		    else if(VERTEX_KEY_PRESSED(VERTEX_KEY_RIGHT))
                rzCommand = -dangle;

            craft.Step(glVertex.speed, rxCommand, rzCommand, 0);

			glLoadIdentity();

			// Craft transformation
                QuaternionD q = craft.get_orientation();

                VectorD tmp(q.get_u(), q.get_v(), q.get_w());

                double angle = atan2f( sqrt(tmp.get_norm2()), q.get_a() ) * 180 / M_PI;
                cout << Rotate(VectorD(0,0,1), q) << " " << angle <<endl;

                glRotated(- 2 * angle, q.get_u(), q.get_v(), q.get_w());
			// End Craft transformation

            glPushMatrix();
			glTranslatef (0.0, 0.0, -50.0);
			glColor3f (1, 0, 0);
			gluSphere (quadric, 1.0, 3, 3);
			glPopMatrix();

            glPushMatrix();
			glTranslatef (0.0, -50.0, 0.0);
			glColor3f (0, 1, 0);
			gluSphere (quadric, 1.0, 3, 3);
			glPopMatrix();

            glPushMatrix();
			glTranslatef (0.0, 0.0, 50.0);
			glColor3f (0, 0, 1);
			gluSphere (quadric, 1.0, 16, 16);
			glPopMatrix();

            glPushMatrix();
			glTranslatef (0.0, 50.0, 0.0);
			glColor3f (1, 0, 1);
			gluSphere (quadric, 1.0, 16, 16);
			glPopMatrix();
		}

		gluDeleteQuadric (quadric);

		vertexStop ();
	}

	return 0;
}
