
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalOrderRules.h"
#include "AutoGen/Optionals/OptionalMetadataView.h"
#include "AutoGen/LeaderBoardView.h"

#include "LeaderboardDetails.generated.h"

UCLASS(BlueprintType)
class ULeaderboardDetails : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Lbid")
	FString Lbid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Orules")
	FOptionalOrderRules Orules;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Number Of Entries")
	int32 NumberOfEntries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Full Name")
	FString FullName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Meta Data")
	FOptionalMetadataView MetaData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="View")
	ULeaderBoardView* View;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};