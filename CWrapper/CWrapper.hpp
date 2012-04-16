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

    void *             __declspec(dllexport) SpaceCraft_Create     (double * at, double speedMax, double * ar, double angularSpeedMax);
    void               __declspec(dllexport) SpaceCraft_Release    (void * craft);
    void               __declspec(dllexport) SpaceCraft_Step       (void * craft, double delta, double rxCommand, double rzCommand, double throttle);
    struct Position    __declspec(dllexport) SpaceCraft_GetPosition(void * craft);
    struct Orientation __declspec(dllexport) SpaceCraft_GetOrientation(void * craft);
}
