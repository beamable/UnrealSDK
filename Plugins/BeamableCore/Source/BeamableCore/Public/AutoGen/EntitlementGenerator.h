
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalEntitlementClaimWindow.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "EntitlementGenerator.generated.h"

UCLASS(BlueprintType)
class UEntitlementGenerator : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Quantity")
	FOptionalInt32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Claim Window")
	FOptionalEntitlementClaimWindow ClaimWindow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Params")
	FOptionalMapOfString Params;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Specialization")
	FOptionalString Specialization;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Action")
	FString Action;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};