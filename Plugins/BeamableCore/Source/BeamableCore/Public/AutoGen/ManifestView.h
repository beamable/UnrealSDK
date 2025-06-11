#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceStorageReference.h"
#include "BeamableCore/Public/AutoGen/ServiceReference.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "ManifestView.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UManifestView : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Checksum", Category="Beam")
	FString Checksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	int64 Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest", Category="Beam")
	TArray<UServiceReference*> Manifest = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created By Account Id", Category="Beam")
	FOptionalInt64 CreatedByAccountId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Comments", Category="Beam")
	FOptionalString Comments = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Reference", Category="Beam")
	FOptionalArrayOfServiceStorageReference StorageReference = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};