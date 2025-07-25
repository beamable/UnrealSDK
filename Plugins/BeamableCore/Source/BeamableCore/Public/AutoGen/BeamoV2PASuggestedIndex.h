#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Maps/MapOfInt32.h"

#include "BeamoV2PASuggestedIndex.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2PASuggestedIndex : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Namespace", Category="Beam")
	FString Namespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Weight", Category="Beam")
	double Weight = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Impact", Category="Beam")
	TArray<FString> Impact = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Index", Category="Beam")
	TArray<FMapOfInt32> Index = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};