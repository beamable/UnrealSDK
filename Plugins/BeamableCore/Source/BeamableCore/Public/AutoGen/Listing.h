#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/CohortRequirement.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Price.h"
#include "BeamableCore/Public/AutoGen/PlayerStatRequirement.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "BeamableCore/Public/AutoGen/EntitlementRequirement.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSchedule.h"
#include "BeamableCore/Public/AutoGen/OfferRequirement.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPeriod.h"

#include "Listing.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UListing : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offer Symbol", Category="Beam")
	FString OfferSymbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Price", Category="Beam")
	UPrice* Price = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cohort Requirements", Category="Beam")
	TArray<UCohortRequirement*> CohortRequirements = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Stat Requirements", Category="Beam")
	TArray<UPlayerStatRequirement*> PlayerStatRequirements = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entitlement Requirements", Category="Beam")
	TArray<UEntitlementRequirement*> EntitlementRequirements = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offer Requirements", Category="Beam")
	TArray<UOfferRequirement*> OfferRequirements = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data", Category="Beam")
	TMap<FString, FString> ClientData = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Purchase Limit", Category="Beam")
	FOptionalInt32 PurchaseLimit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Schedule Instance Purchase Limit", Category="Beam")
	FOptionalInt32 ScheduleInstancePurchaseLimit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Schedule", Category="Beam")
	FOptionalSchedule Schedule = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Duration Cool Down Seconds", Category="Beam")
	FOptionalInt32 ActiveDurationCoolDownSeconds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Duration Seconds", Category="Beam")
	FOptionalInt32 ActiveDurationSeconds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Duration Purchase Limit", Category="Beam")
	FOptionalInt32 ActiveDurationPurchaseLimit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Period", Category="Beam")
	FOptionalPeriod ActivePeriod = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Button Text", Category="Beam")
	FOptionalMapOfString ButtonText = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};