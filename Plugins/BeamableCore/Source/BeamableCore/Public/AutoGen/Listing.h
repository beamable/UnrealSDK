
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/CohortRequirement.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Price.h"
#include "AutoGen/PlayerStatRequirement.h"
#include "AutoGen/Optionals/OptionalMapOfString.h"
#include "AutoGen/EntitlementRequirement.h"
#include "AutoGen/Optionals/OptionalSchedule.h"
#include "AutoGen/OfferRequirement.h"
#include "AutoGen/Optionals/OptionalPeriod.h"

#include "Listing.generated.h"

UCLASS(BlueprintType)
class UListing : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Requirements")
	TArray<UCohortRequirement*> CohortRequirements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offer Symbol")
	FString OfferSymbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Purchase Limit")
	FOptionalInt32 PurchaseLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price")
	UPrice* Price;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Stat Requirements")
	TArray<UPlayerStatRequirement*> PlayerStatRequirements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Button Text")
	FOptionalMapOfString ButtonText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Schedule Instance Purchase Limit")
	FOptionalInt32 ScheduleInstancePurchaseLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entitlement Requirements")
	TArray<UEntitlementRequirement*> EntitlementRequirements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data")
	TMap<FString, FString> ClientData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Schedule")
	FOptionalSchedule Schedule;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Duration Cool Down Seconds")
	FOptionalInt32 ActiveDurationCoolDownSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Duration Seconds")
	FOptionalInt32 ActiveDurationSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Duration Purchase Limit")
	FOptionalInt32 ActiveDurationPurchaseLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offer Requirements")
	TArray<UOfferRequirement*> OfferRequirements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Period")
	FOptionalPeriod ActivePeriod;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};