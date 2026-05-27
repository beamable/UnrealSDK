#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"

#include "CollectResearchResult.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UCollectResearchResult : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Output Content Id", Category="Beam")
	FString OutputContentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Output Quantity", Category="Beam")
	int32 OutputQuantity = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Output Type", Category="Beam")
	FString OutputType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message", Category="Beam")
	FString Message = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Success", Category="Beam")
	bool bSuccess = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};