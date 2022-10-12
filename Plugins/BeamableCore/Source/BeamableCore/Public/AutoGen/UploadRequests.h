
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/UploadRequestBody.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "UploadRequests.generated.h"

UCLASS(BlueprintType)
class UUploadRequests : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Request")
	TArray<UUploadRequestBody*> Request;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	FOptionalInt64 PlayerId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};