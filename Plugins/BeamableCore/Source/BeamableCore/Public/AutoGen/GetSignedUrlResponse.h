
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/GetLogsUrlHeader.h"

#include "GetSignedUrlResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSignedUrlResponse : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Url", Category="Beam")
	FString Url;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Body", Category="Beam")
	FString Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Method", Category="Beam")
	FString Method;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Headers", Category="Beam")
	TArray<UGetLogsUrlHeader*> Headers;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};