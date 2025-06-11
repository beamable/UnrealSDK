#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "CloudsavingBasicReference.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCloudsavingBasicReference : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Size", Category="Beam")
	int64 Size = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Modified", Category="Beam")
	int64 LastModified = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Key", Category="Beam")
	FString Key = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Bucket Name", Category="Beam")
	FString BucketName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="E Tag", Category="Beam")
	FOptionalString ETag = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};