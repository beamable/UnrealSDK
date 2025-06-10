#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Listing.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "Store.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UStore : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Symbol", Category="Beam")
	FString Symbol = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Listings", Category="Beam")
	TArray<UListing*> Listings = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Show Inactive Listings", Category="Beam")
	FOptionalBool bShowInactiveListings = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Active Listing Limit", Category="Beam")
	FOptionalInt32 ActiveListingLimit = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Choose", Category="Beam")
	FOptionalInt32 Choose = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Refresh Time", Category="Beam")
	FOptionalInt32 RefreshTime = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Title", Category="Beam")
	FOptionalString Title = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};