
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Listing.h"
#include "AutoGen/Optionals/OptionalBool.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "Store.generated.h"

UCLASS(BlueprintType)
class UStore : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Listing Limit")
	FOptionalInt32 ActiveListingLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Choose")
	FOptionalInt32 Choose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listings")
	TArray<UListing*> Listings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Show Inactive Listings")
	FOptionalBool bShowInactiveListings;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol")
	FString Symbol;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Time")
	FOptionalInt32 RefreshTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title")
	FOptionalString Title;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};