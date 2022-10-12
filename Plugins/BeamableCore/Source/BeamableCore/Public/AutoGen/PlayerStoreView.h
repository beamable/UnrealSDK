
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/PlayerListingView.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "PlayerStoreView.generated.h"

UCLASS(BlueprintType)
class UPlayerStoreView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listings")
	TArray<UPlayerListingView*> Listings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Next Delta Seconds")
	FOptionalInt64 NextDeltaSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title")
	FOptionalString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remain")
	FOptionalInt64 SecondsRemain;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};