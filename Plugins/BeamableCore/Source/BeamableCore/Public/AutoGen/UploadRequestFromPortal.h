
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfMetadataPair.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "UploadRequestFromPortal.generated.h"

UCLASS(BlueprintType)
class UUploadRequestFromPortal : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Key")
	FString ObjectKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Size In Bytes")
	int64 SizeInBytes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Metadata")
	FOptionalArrayOfMetadataPair Metadata;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Modified")
	FOptionalInt64 LastModified;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};