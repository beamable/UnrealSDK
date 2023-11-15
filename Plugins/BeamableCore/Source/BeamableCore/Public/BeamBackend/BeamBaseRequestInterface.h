#pragma once

#include "CoreMinimal.h"
#include "RequestType.h"
#include "BeamBaseRequestInterface.generated.h"

/**
* @brief Wraps around all Request UObjects that we codegen.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every request that goes out while maintaining BP compatibility and keeping compile times low. 
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UBeamBaseRequestInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Wraps around all Request UObjects that we codegen.
 * Enables UBeamBackend to provide guarantees about the lifecycle of every request that goes out while maintaining BP compatibility and keeping compile times low. 
 */
class BEAMABLECORE_API IBeamBaseRequestInterface
{
	GENERATED_BODY()

public:	
	TMap<FString, FString> CustomHeaders;
	
	virtual FRequestType GetRequestType() const
	{
		return FRequestType{this->_getUObject()->GetClass()->GetAuthoredName()};
	}
	
	virtual void BuildVerb(FString& VerbString) const
	{
	}

	virtual void BuildRoute(FString& RouteString) const
	{
	}

	virtual void BuildBody(FString& BodyString) const
	{
	}
};