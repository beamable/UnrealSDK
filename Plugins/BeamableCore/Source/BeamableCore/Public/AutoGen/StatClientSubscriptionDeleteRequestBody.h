#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "StatClientSubscriptionDeleteRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatClientSubscriptionDeleteRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Target Gamer Tag", Category="Beam")
	FBeamGamerTag TargetGamerTag = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Keys", Category="Beam")
	TArray<FString> Keys = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Delete All", Category="Beam")
	FOptionalBool bDeleteAll = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};