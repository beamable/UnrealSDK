
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "ListTokensRequestBody.generated.h"

UCLASS(BlueprintType)
class UListTokensRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page Size")
	int32 PageSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Page")
	int32 Page;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cid")
	FOptionalInt64 Cid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pid")
	FOptionalString Pid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag Or Account Id")
	int64 GamerTagOrAccountId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};