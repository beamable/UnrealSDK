
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/PlayerListingView.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "PlayerStoreView.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPlayerStoreView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listings", Category="Beam")
	TArray<UPlayerListingView*> Listings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Next Delta Seconds", Category="Beam")
	FOptionalInt64 NextDeltaSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title", Category="Beam")
	FOptionalString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remain", Category="Beam")
	FOptionalInt64 SecondsRemain;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};