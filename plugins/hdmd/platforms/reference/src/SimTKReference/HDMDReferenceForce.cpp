#include "HDMDReferenceForce.h"

using namespace OpenMM;
using namespace std;

#include <cmath>

double HDMDReferenceForce::periodicDifference(double val1, double val2, double period) {
    double diff = val1-val2;
    double base = floor(diff/period+0.5)*period;
    return diff-base;
}

void HDMDReferenceForce::getDeltaR(const Vec4& atomCoordinatesI, const Vec4& atomCoordinatesJ,
                                   double* deltaR) {
   deltaR[XIndex]    = atomCoordinatesJ[0] - atomCoordinatesI[0];
   deltaR[YIndex]    = atomCoordinatesJ[1] - atomCoordinatesI[1];
   deltaR[ZIndex]    = atomCoordinatesJ[2] - atomCoordinatesI[2];
   deltaR[WIndex]    = atomCoordinatesJ[3] - atomCoordinatesI[3];

   deltaR[R2Index]   = DOT4(deltaR, deltaR);
   deltaR[RIndex]    = sqrt(deltaR[R2Index]);
}

void HDMDReferenceForce::getDeltaRPeriodic(const Vec4& atomCoordinatesI, const Vec4& atomCoordinatesJ,
                                           const double* boxSize, double* deltaR) {
   deltaR[XIndex]    = periodicDifference(atomCoordinatesJ[0], atomCoordinatesI[0], boxSize[0]);
   deltaR[YIndex]    = periodicDifference(atomCoordinatesJ[1], atomCoordinatesI[1], boxSize[1]);
   deltaR[ZIndex]    = periodicDifference(atomCoordinatesJ[2], atomCoordinatesI[2], boxSize[2]);
   deltaR[WIndex]    = periodicDifference(atomCoordinatesJ[3], atomCoordinatesI[3], boxSize[3]);

   deltaR[R2Index]   = DOT4(deltaR, deltaR);
   deltaR[RIndex]    = sqrt(deltaR[R2Index]);
}
