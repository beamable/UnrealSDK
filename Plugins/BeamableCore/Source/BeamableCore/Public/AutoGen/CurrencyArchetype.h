
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInventoryProxySettings.h"
#include "AutoGen/Optionals/OptionalClientPermission.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "CurrencyArchetype.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyArchetype : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Proxy", Category="Beam")
	FOptionalInventoryProxySettings Proxy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Permission", Category="Beam")
	FOptionalClientPermission ClientPermission;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Starting Amount", Category="Beam")
	FOptionalInt64 StartingAmount;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};