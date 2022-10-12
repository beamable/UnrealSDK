
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "ReplaceObjectsRequestBody.generated.h"

UCLASS(BlueprintType)
class UReplaceObjectsRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Source Player Id")
	int64 SourcePlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Target Player Id")
	int64 TargetPlayerId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};