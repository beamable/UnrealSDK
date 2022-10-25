#pragma once

#include "BeamBaseResponseBodyInterface.generated.h"

/**
 * @brief Wraps around all Beamable Serializable types that we codegen and are used as responses.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every response that goes out while maintaining BP compatibility and keeping compile times low. 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UBeamBaseResponseBodyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Wraps around all Beamable Serializable types that we codegen and are used as responses.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every response that goes out while maintaining BP compatibility and keeping compile times low. 
 */
class BEAMABLECORE_API IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()
};
