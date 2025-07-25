#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "BeamoV2ServiceStorageStatus.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2ServiceStorageStatus : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Current", Category="Beam")
	FOptionalBool bIsCurrent = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Running", Category="Beam")
	FOptionalBool bIsRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Type", Category="Beam")
	FOptionalString StorageType = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};