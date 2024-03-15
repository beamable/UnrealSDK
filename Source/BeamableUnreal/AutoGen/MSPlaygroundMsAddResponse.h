#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/InFlightFailureResponse.h
#include "BeamableCore/Public/AutoGen/InFlightFailure.h"

#include "InFlightFailureResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UInFlightFailureResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
========


#include "MSPlaygroundMsAddResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UMSPlaygroundMsAddResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
>>>>>>>> main:Source/BeamableUnreal/AutoGen/MSPlaygroundMsAddResponse.h
{
	GENERATED_BODY()

public:
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/InFlightFailureResponse.h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Failures", Category="Beam")
	TArray<UInFlightFailure*> Failures = {};
========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category="Beam")
	int32 Value = {};
>>>>>>>> main:Source/BeamableUnreal/AutoGen/MSPlaygroundMsAddResponse.h

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};