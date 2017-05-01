
#include "HDMDReferenceHarmonicBond.h"
#include "HDMDReferenceForce.h"

using std::vector;
using namespace OpenMM;

HDMDReferenceHarmonicBond::HDMDReferenceHarmonicBond() : usePeriodic(false) {
}

HDMDReferenceHarmonicBond::~HDMDReferenceHarmonicBond() {
}

void HDMDReferenceHarmonicBond::setPeriodic(double x, double y, double z, double w) {
    usePeriodic = true;
    boxVectors[0] = x;
    boxVectors[1] = y;
    boxVectors[2] = z;
    boxVectors[3] = w;
}

double HDMDReferenceHarmonicBond::calculateBondIxn(int* atomIndices,
                                                vector<Vec4>& atomCoordinates,
                                                double* parameters,
                                                vector<Vec4>& forces) {
   double deltaR[HDMDReferenceForce::LastDeltaRIndex];

   // ---------------------------------------------------------------------------------------

   // get deltaR, R2, and R between 2 atoms
   int atomAIndex = atomIndices[0];
   int atomBIndex = atomIndices[1];
   if (usePeriodic)
       HDMDReferenceForce::getDeltaRPeriodic(atomCoordinates[atomAIndex], atomCoordinates[atomBIndex], boxVectors, deltaR);
   else
       HDMDReferenceForce::getDeltaR(atomCoordinates[atomAIndex], atomCoordinates[atomBIndex], deltaR);

   // deltaIdeal = r - r_0

   double deltaIdeal      = deltaR[HDMDReferenceForce::RIndex] - parameters[0];
   double deltaIdeal2     = deltaIdeal * deltaIdeal;

   double dEdR            = parameters[1] * deltaIdeal;

   // chain rule

   dEdR                       = deltaR[HDMDReferenceForce::RIndex] > 0.0 ? (dEdR/deltaR[HDMDReferenceForce::RIndex]) : 0.0;

   forces[atomAIndex][0]     += dEdR * deltaR[HDMDReferenceForce::XIndex];
   forces[atomAIndex][1]     += dEdR * deltaR[HDMDReferenceForce::YIndex];
   forces[atomAIndex][2]     += dEdR * deltaR[HDMDReferenceForce::ZIndex];
   forces[atomAIndex][3]     += dEdR * deltaR[HDMDReferenceForce::WIndex];

   forces[atomBIndex][0]     -= dEdR * deltaR[HDMDReferenceForce::XIndex];
   forces[atomBIndex][1]     -= dEdR * deltaR[HDMDReferenceForce::YIndex];
   forces[atomBIndex][2]     -= dEdR * deltaR[HDMDReferenceForce::ZIndex];
   forces[atomBIndex][3]     -= dEdR * deltaR[HDMDReferenceForce::WIndex];

   return 0.5 * parameters[1] * deltaIdeal2;
}
