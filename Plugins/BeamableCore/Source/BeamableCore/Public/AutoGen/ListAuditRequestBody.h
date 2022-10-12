
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "ListAuditRequestBody.generated.h"

UCLASS(BlueprintType)
class UListAuditRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Providerid")
	FOptionalString Providerid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider")
	FOptionalString Provider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State")
	FOptionalString State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txid")
	FOptionalInt64 Txid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player")
	FOptionalInt64 Player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start")
	FOptionalInt32 Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};