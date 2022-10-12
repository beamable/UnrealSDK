
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Reference.h"

#include "Manifest.generated.h"

UCLASS(BlueprintType)
class UManifest : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Manifest")
	TArray<UReference*> Manifest;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	int64 Created;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Replacement")
	bool bReplacement;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};