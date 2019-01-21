#pragma hdrstop
#include "MoleculixHeaders.h"
#include "dslAxisSystem.h"

using namespace std;
using namespace dsl;

int main()
{
    Explorer e;

    //Creating two cartesian axes systems (frames of reference)
    AxisSystem MFrame, QFrame;

    //Setting Labels for the XYZ axes
    MFrame.setAxesLabels(StringList("Mx,My,Mz", ','));
    QFrame.setAxesLabels(StringList("Qx,Qy,Qz", ','));

    QFrame.setColor(Green);

    e.add(MFrame);
    e.add(QFrame);

    cout<<"Press 'e' to exit.\n";

    //Render the two frames
    e.resetCamera();
    e.explore();

    //Move the origin of the two frames
    MFrame.setOrigin(0.75,-0.75,0);
    QFrame.setOrigin(-0.75,0.75,0);

    //Render again
    e.explore();

    //Rotate the Q frame a little
    QFrame.rotateZ(-45);
    QFrame.rotateY(78);
    QFrame.rotateZ(23);

    //Render
    e.explore();

    //Find the Euler angles, alfa, beta and gamma, that relates
    //the two frames, QToM
    EulerAngleTriplet QToM(QFrame.getEulerAnglesTo(MFrame));

    //Transform the Q frame into the M frame
    QFrame.rotateZYZ(QToM);

    //Render
    e.explore();
    e.purge();
    return 0;
}

#include "mlx-autolink.h"
#include "third_party_libs-autolink.h"
#include "vtk-autolink.h"

