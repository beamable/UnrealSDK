
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/GetLogsUrlHeader.h"

#include "GetSignedUrlResponse.generated.h"

UCLASS(BlueprintType)
class UGetSignedUrlResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Headers")
	TArray<UGetLogsUrlHeader*> Headers;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Url")
	FString Url;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body")
	FString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Method")
	FString Method;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};