
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "AliasAvailableResponse.generated.h"

UCLASS(BlueprintType)
class UAliasAvailableResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Alias")
	FString Alias;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Available")
	bool bAvailable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	int64 Cid;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};