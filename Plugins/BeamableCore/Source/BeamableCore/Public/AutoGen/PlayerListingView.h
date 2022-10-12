
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/ClientDataEntry.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/PlayerOfferView.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "PlayerListingView.generated.h"

UCLASS(BlueprintType)
class UPlayerListingView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data List")
	TArray<UClientDataEntry*> ClientDataList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Client Data")
	TMap<FString, FString> ClientData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cooldown")
	FOptionalInt32 Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Active")
	int64 SecondsActive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offer")
	UPlayerOfferView* Offer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Query After Purchase")
	bool bQueryAfterPurchase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Purchases Remain")
	FOptionalInt32 PurchasesRemain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remain")
	FOptionalInt64 SecondsRemain;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Active")
	bool bActive;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};