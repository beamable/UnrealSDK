
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "GetStatusForGroupsRequestBody.generated.h"

UCLASS(BlueprintType)
class UGetStatusForGroupsRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Ids")
	TArray<int64> GroupIds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FString ContentId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};