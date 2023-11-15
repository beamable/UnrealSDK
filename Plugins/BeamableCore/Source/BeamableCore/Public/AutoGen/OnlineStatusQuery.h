#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "OnlineStatusQuery.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOnlineStatusQuery : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B To Many Requests", Category="Beam")
	FOptionalBool bToManyRequests = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Ids", Category="Beam")
	FOptionalArrayOfString PlayerIds = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};