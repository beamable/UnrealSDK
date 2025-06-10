#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalOrderRules.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMetadataView.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardView.h"

#include "LeaderboardDetails.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API ULeaderboardDetails : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Lbid", Category="Beam")
	FString Lbid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Number Of Entries", Category="Beam")
	int32 NumberOfEntries = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Full Name", Category="Beam")
	FString FullName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="View", Category="Beam")
	ULeaderBoardView* View = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Orules", Category="Beam")
	FOptionalOrderRules Orules = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Meta Data", Category="Beam")
	FOptionalMetadataView MetaData = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};