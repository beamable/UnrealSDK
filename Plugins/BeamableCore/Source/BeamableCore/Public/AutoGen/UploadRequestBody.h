#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfMetadataPair.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "UploadRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UUploadRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Key", Category="Beam")
	FString ObjectKey = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Size In Bytes", Category="Beam")
	int64 SizeInBytes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Deleted", Category="Beam")
	FOptionalBool bDeleted = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Modified", Category="Beam")
	FOptionalInt64 LastModified = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Checksum", Category="Beam")
	FOptionalString Checksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Metadata", Category="Beam")
	FOptionalArrayOfMetadataPair Metadata = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};