#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/AdminActorInFlightMessage.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"

#include "AdminActorInFlightFailure.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAdminActorInFlightFailure : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Failure Id", Category="Beam")
	FString FailureId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Object Id", Category="Beam")
	FString ServiceObjectId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="In Flight Message", Category="Beam")
	UAdminActorInFlightMessage* InFlightMessage = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Error", Category="Beam")
	FString LastError = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Timestamp", Category="Beam")
	FOptionalDateTime Timestamp = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};