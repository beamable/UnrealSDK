#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTag.h"

#include "JoinLobbyByPasscode.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UJoinLobbyByPasscode : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Passcode", Category="Beam")
	FOptionalString Passcode = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	FOptionalArrayOfTag Tags = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};