#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "GetPlayerLevelResult.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UGetPlayerLevelResult : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Level", Category="Beam")
	int32 Level = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Success", Category="Beam")
	bool bSuccess = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Total Xp", Category="Beam")
	int32 TotalXp = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Xp For Current Level", Category="Beam")
	int32 XpForCurrentLevel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Xp Into Current Level", Category="Beam")
	int32 XpIntoCurrentLevel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message", Category="Beam")
	FString Message = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};