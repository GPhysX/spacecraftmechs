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

struct timespec operator-(struct timespec x, struct timespec y)
{
    struct timespec ret;

    ret.tv_sec = x.tv_sec - y.tv_sec;
    ret.tv_nsec = x.tv_nsec - y.tv_nsec;

    if(ret.tv_nsec < 0)
    {
        ret.tv_sec -= 1;
        ret.tv_nsec += 1000000000;
    }

    return ret;
}

ostream & operator<<(ostream & o, struct timespec ts)
{
    o << ts.tv_sec << ts.tv_nsec << endl;

    return o;
}

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

        struct timespec ts_last, ts_now;
        while(clock_gettime(CLOCK_MONOTONIC,&ts_last) != 0)
            continue;

		while (!vertexLoop (0) && !VERTEX_KEY_PRESSED (VERTEX_KEY_ESCAPE))
		{
            if(clock_gettime(CLOCK_MONOTONIC,&ts_now) != 0)
                continue;

            struct timespec ts_delta = ts_now - ts_last;
            long long delta = ((long long)ts_delta.tv_sec) * 1000000000LL + (long long)ts_delta.tv_nsec;

            ts_last = ts_now;

		    VectorD vt(0, 0, 0);   // translation command
		    VectorD vr(0, 0, 0);   // rotation command
		    QuaternionD q(0, 0, 0, 0); // rotation result

            double dangle = 2 * M_PI / 10;
		    if(VERTEX_KEY_PRESSED(VERTEX_KEY_UP))
                craft.Step(((double)delta) * 1e-9, VectorD(0, 0, 0), VectorD(dangle, 0, 0));
		    else if(VERTEX_KEY_PRESSED(VERTEX_KEY_DOWN))
                craft.Step(((double)delta) * 1e-9, VectorD(0, 0, 0), VectorD(-dangle, 0, 0));
		    else
                craft.Step(((double)delta) * 1e-9, VectorD(0, 0, 0), VectorD(0, 0, 0));

			glLoadIdentity ();

			// Craft transformation
			{
                QuaternionD q = craft.get_orientation();

                VectorD tmp(q.get_u(), q.get_v(), q.get_w());

                double angle = atan2f( sqrt(tmp.get_norm2()), q.get_a() ) * 180 / M_PI;
                cout << q << " " << angle <<endl;

                glRotated(angle, q.get_u(), q.get_v(), q.get_w());
			}
			// End Craft transformation

			glTranslatef (0.0, 0.0, -50.0);
			glColor3f (1, 1, 1);
			gluSphere (quadric, 1.0, 16, 16);

			glTranslatef (0.0, 0.0, 100.0);
			glColor3f (1, 1, 1);
			gluSphere (quadric, 1.0, 16, 16);

			glTranslatef (0.0, 50.0, -150.0);
			glColor3f (1, 1, 1);
			gluSphere (quadric, 1.0, 16, 16);

			glTranslatef (0.0, -100.0, 100.0);
			glColor3f (1, 1, 1);
			gluSphere (quadric, 1.0, 16, 16);

			glTranslatef (0.0, 50.0, -50.0);
			glColor3f (1, 1, 1);
			gluSphere (quadric, 1.0, 16, 16);
		}

		gluDeleteQuadric (quadric);

		vertexStop ();
	}

	return 0;
}
