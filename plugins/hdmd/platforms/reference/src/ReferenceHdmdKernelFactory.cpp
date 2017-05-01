#include "ReferenceHdmdKernelFactory.h"
//#include "ReferenceHdmdKernels.h"
#include "ReferencePlatform.h"
#include "openmm/internal/ContextImpl.h"
#include "openmm/OpenMMException.h"

using namespace OpenMM;

extern "C" OPENMM_EXPORT void registerPlatforms() {
}

extern "C" OPENMM_EXPORT void registerKernelFactories() {
    for (int i = 0; i < Platform::getNumPlatforms(); i++) {
        Platform& platform = Platform::getPlatform(i);
        if (dynamic_cast<ReferencePlatform*>(&platform) != NULL) {
            ReferenceHdmdKernelFactory* factory = new ReferenceHdmdKernelFactory();
//            platform.registerKernelFactory(IntegrateRPMDStepKernel::Name(), factory);
        }
    }
}

extern "C" OPENMM_EXPORT void registerRpmdReferenceKernelFactories() {
    registerKernelFactories();
}

KernelImpl* ReferenceHdmdKernelFactory::createKernelImpl(std::string name, const Platform& platform, ContextImpl& context) const {
    // if (name == IntegrateRPMDStepKernel::Name())
    //     return new ReferenceIntegrateRPMDStepKernel(name, platform);
    throw OpenMMException((std::string("Tried to create kernel with illegal kernel name '") + name + "'").c_str());
}
