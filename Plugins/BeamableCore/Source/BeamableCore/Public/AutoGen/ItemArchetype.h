
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArchetypeProxy.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalClientPermission.h"

#include "ItemArchetype.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UItemArchetype : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="External", Category="Beam")
	FOptionalArchetypeProxy External;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Permission", Category="Beam")
	FOptionalClientPermission ClientPermission;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};