#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/GetContentRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "GetBinaryDownloadUrlsRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UGetBinaryDownloadUrlsRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Requests", Category="Beam")
	TArray<UGetContentRequestBody*> Requests = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expiration Seconds", Category="Beam")
	FOptionalInt64 ExpirationSeconds = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};