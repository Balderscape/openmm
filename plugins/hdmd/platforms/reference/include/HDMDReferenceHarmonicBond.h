#ifndef __HDMDReferenceHarmonicBond_H__
#define __HDMDReferenceHarmonicBond_H__

#include "openmm/Vec4.h"
#include <vector>

namespace OpenMM {

class HDMDReferenceHarmonicBond {

public:

    HDMDReferenceHarmonicBond();
    ~HDMDReferenceHarmonicBond();

    void setPeriodic(double x, double y, double z, double w);

    /**---------------------------------------------------------------------------------------      
    Calculate 4D Harmonic Bond Ixn    
        @param atomIndices      two bond indices
        @param atomCoordinates  atom coordinates
        @param parameters       parameters: parameters[0] = ideal bond length
                                                parameters[1] = bond k
        @param forces           force array (forces added)

        @return total energy
    --------------------------------------------------------------------------------------- */
    
    double calculateBondIxn(int* atomIndices, 
                        std::vector<OpenMM::Vec4>& atomCoordinates,
                        double* parameters, 
                        std::vector<OpenMM::Vec4>& forces
                        );

private:
    bool usePeriodic;
    double boxVectors[4];     

};

} // namespace OpenMM

#endif // _HDMDReferenceHarmonicBond___
