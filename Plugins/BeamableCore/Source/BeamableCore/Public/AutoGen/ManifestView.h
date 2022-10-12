
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceStorageReference.h"
#include "AutoGen/ServiceReference.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "ManifestView.generated.h"

UCLASS(BlueprintType)
class UManifestView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created By Account Id")
	int64 CreatedByAccountId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Checksum")
	FString Checksum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Reference")
	FOptionalArrayOfServiceStorageReference StorageReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest")
	TArray<UServiceReference*> Manifest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	int64 Created;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Comments")
	FOptionalString Comments;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};