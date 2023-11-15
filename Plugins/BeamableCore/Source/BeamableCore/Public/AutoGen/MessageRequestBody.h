#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "MessageRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMessageRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FOptionalString Body = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid", Category="Beam")
	FOptionalString Cid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid", Category="Beam")
	FOptionalString Pid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FOptionalString PlayerId = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};