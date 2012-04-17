extern "C"
{
    struct Position
    {
        double x, y, z;
    };

    struct Orientation
    {
        double a, u, v, w;
    };

#ifndef __WIN32__
#define __declspec(dllexport)
#endif

    void * __declspec(dllexport) SpaceCraft_Create         (double * at, double speedMax, double * ar, double angularSpeedMax);
    void   __declspec(dllexport) SpaceCraft_Release        (void * craft);
    void   __declspec(dllexport) SpaceCraft_Step           (void * craft, double delta, double rxCommand, double rzCommand, double throttle);
    void   __declspec(dllexport) SpaceCraft_GetPosition    (void * craft, struct Position * p);
    void   __declspec(dllexport) SpaceCraft_GetOrientation (void * craft, struct Orientation * o);
}
