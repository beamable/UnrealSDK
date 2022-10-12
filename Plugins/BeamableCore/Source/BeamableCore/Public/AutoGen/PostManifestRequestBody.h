
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/ServiceReference.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceStorageReference.h"

#include "PostManifestRequestBody.generated.h"

UCLASS(BlueprintType)
class UPostManifestRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest")
	TArray<UServiceReference*> Manifest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Comments")
	FOptionalString Comments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Auto Deploy")
	FOptionalBool bAutoDeploy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage References")
	FOptionalArrayOfServiceStorageReference StorageReferences;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};