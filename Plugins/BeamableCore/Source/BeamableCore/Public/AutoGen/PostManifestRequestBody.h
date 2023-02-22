
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/ServiceReference.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceStorageReference.h"

#include "PostManifestRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPostManifestRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest", Category="Beam")
	TArray<UServiceReference*> Manifest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Auto Deploy", Category="Beam")
	FOptionalBool bAutoDeploy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Comments", Category="Beam")
	FOptionalString Comments;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage References", Category="Beam")
	FOptionalArrayOfServiceStorageReference StorageReferences;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};