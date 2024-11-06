#pragma once
#include "BeamFullResponse.h"
#include "BeamLogging.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamBaseResponseBodyInterface.generated.h"

class UGenericBeamRequest;
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

public:
	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent);
};

inline void IBeamBaseResponseBodyInterface::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	unimplemented();

	// if the implementing class is a FBeamJsonSerializable we should code gen this implementation.
	// {
	// 	OuterOwner = RequestData;
	// 	BeamDeserialize(ResponseContent);		
	// }
	// else
	// {
	// 	UE_LOG(LogBeamBackend, Warning, TEXT("Unsupported response type."))
	// }	
}


UCLASS(BlueprintType)
class BEAMABLECORE_API UGenericBeamResponse : public UObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	FString ResponseBody;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override
	{
		ResponseBody = ResponseContent;
	}
};

using FGenericBeamRequestFullResponse = FBeamFullResponse<UGenericBeamRequest*, UGenericBeamResponse*>;
DECLARE_DELEGATE_OneParam(FOnGenericBeamRequestFullResponse, FGenericBeamRequestFullResponse);