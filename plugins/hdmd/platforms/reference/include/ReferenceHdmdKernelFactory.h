#ifndef OPENMM_REFERENCEHDMDKERNELFACTORY_H_
#define OPENMM_REFERENCEHDMDKERNELFACTORY_H_

#include "openmm/KernelFactory.h"

namespace OpenMM {

/**
 * This KernelFactory creates kernels for the reference implementation of HDMDIntegrator.
 */

class ReferenceHdmdKernelFactory : public KernelFactory {
public:
    KernelImpl* createKernelImpl(std::string name, const Platform& platform, ContextImpl& context) const;
};

} // namespace OpenMM

#endif /*OPENMM_REFERENCEHDMDKERNELFACTORY_H_*/
