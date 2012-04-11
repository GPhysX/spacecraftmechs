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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		vertexSetMouse (0, 1);
		vertexSetWindow ("Spacecraft test", NULL);
		vertexLoop (0);

		glVertex.factor = 0.001;

		while (!vertexLoop (0) && !VERTEX_KEY_PRESSED (VERTEX_KEY_ESCAPE))
		{
		    VectorD vt(0, 0, 0);   // translation command
		    VectorD vr(0, 0, 0);   // rotation command

            double rzCommand = 0, rxCommand = 0, throttle = 0;

		    if(VERTEX_KEY_PRESSED(VERTEX_KEY_UP))
                rxCommand = -1;
		    else if(VERTEX_KEY_PRESSED(VERTEX_KEY_DOWN))
                rxCommand = 1;

		    if(VERTEX_KEY_PRESSED(VERTEX_KEY_LEFT))
                rzCommand = 1;
		    else if(VERTEX_KEY_PRESSED(VERTEX_KEY_RIGHT))
                rzCommand = -1;

		    if(VERTEX_KEY_PRESSED('Z'))
                throttle = 1;

            if(glVertex.speed > 1e-5)
                craft.Step(glVertex.speed, rxCommand, rzCommand, 0);

			glLoadIdentity();

			// Craft transformation
                QuaternionD q = craft.get_orientation();

                VectorD tmp(q.get_u(), q.get_v(), q.get_w());

                double angle = atan2f( sqrt(tmp.get_norm2()), q.get_a() ) * 180 / M_PI;

                glRotated(- 2 * angle, q.get_u(), q.get_v(), q.get_w());
			// End Craft transformation

            glPushMatrix();
			glTranslatef (0.0, 0.0, 0.0);
			glColor3f (1, 0, 0);
			gluSphere (quadric, 100.0, 30, 30);
			glPopMatrix();
		}

		gluDeleteQuadric (quadric);

		vertexStop ();
	}

	return 0;
}
