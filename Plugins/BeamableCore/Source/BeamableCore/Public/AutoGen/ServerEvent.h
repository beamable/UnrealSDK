
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "ServerEvent.generated.h"

UCLASS(BlueprintType)
class UServerEvent : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Event")
	FString Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payload")
	FOptionalString Payload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B To All")
	bool bToAll;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};