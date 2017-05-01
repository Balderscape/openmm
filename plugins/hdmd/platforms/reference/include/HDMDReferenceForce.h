#ifndef __HDMDReferenceForce_H__
#define __HDMDReferenceForce_H__

#include "openmm/Vec4.h"
#include "openmm/internal/windowsExport.h"

namespace OpenMM {

#define DOT4(u,v) ((u[0])*(v[0]) + (u[1])*(v[1]) + (u[2])*(v[2]) + (u[3])*(v[3]))

class OPENMM_EXPORT  HDMDReferenceForce {
public:

    HDMDReferenceForce() {};
    ~HDMDReferenceForce() {};    
    
    static const int XIndex             = 0;
    static const int YIndex             = 1;
    static const int ZIndex             = 2;
    static const int WIndex             = 3;
    static const int R2Index            = 4;
    static const int RIndex             = 5;
    static const int LastDeltaRIndex    = 6;

    static const int DeltaRMaxIndex     = 6;
   
    /**---------------------------------------------------------------------------------------
      
       Get deltaR and distance and distance**2 between atomI and atomJ (static method)
       deltaR: j - i
      
       @param atomCoordinatesI    atom i coordinates
       @param atomCoordinatesI    atom j coordinates
       @param deltaR              deltaX, deltaY, deltaZ, deltaW, R2, R upon return
      
       --------------------------------------------------------------------------------------- */
      
    static void getDeltaR(const OpenMM::Vec4& atomCoordinatesI, const OpenMM::Vec4& atomCoordinatesJ,
                          double* deltaR);

    /**---------------------------------------------------------------------------------------

       Get deltaR and distance and distance**2 between atomI and atomJ, assuming periodic
       boundary conditions (static method); deltaR: j - i

       @param atomCoordinatesI    atom i coordinates
       @param atomCoordinatesI    atom j coordinates
       @param boxSize             X, Y, Z, and W sizes of the periodic box
       @param deltaR              deltaX, deltaY, deltaZ, deltaW, R2, R upon return

         --------------------------------------------------------------------------------------- */

    static void getDeltaRPeriodic(const OpenMM::Vec4& atomCoordinatesI, const OpenMM::Vec4& atomCoordinatesJ,
                                    const double* boxSize, double* deltaR);

private:
    static double periodicDifference(double val1, double val2, double period);

};

} // namespace OpenMM

#endif // __HDMDReferenceForce_H__