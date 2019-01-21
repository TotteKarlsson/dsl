#include "MoleculixHeaders.h"

using namespace dsl;
using namespace std;

int main()
{
    //Creating a viewer object
    Explorer e;
    AxisSystem axes1;
    AxisSystem axes2;

    cout<<"Press 'c' to start mouse interaction. \n";
    cout<<"Press 'e' to exit or go to next exploring view\n";
    e.add(axes1);
    e.add(axes2);
    axes1.setOrigin(0,0,0);
    axes2.setOrigin(1,1,1);

    e.resetCamera();
    e.render();

    e.explore();

    axes2.rotateZ(45);
    axes2.rotateY(45);
    axes2.rotateZ(45);

    e.explore();

    EulerAngleTriplet angle(axes2.getEulerAnglesTo(axes1));

    axes2.rotateZYZ(angle);

    e.explore();
    e.purge();
    return 0;
}

#include "mlx-autolink.h"
#include "third_party_libs-autolink.h"
#include "vtk-autolink.h"
