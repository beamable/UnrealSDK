#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"

#include "PlayerStatRequirement.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UPlayerStatRequirement : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stat", Category="Beam")
	FString Stat = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Constraint", Category="Beam")
	FString Constraint = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category="Beam")
	FString Value = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Domain", Category="Beam")
	FOptionalString Domain = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Access", Category="Beam")
	FOptionalString Access = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};