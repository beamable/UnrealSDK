#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

#include "SessionClientHistoryResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USessionClientHistoryResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Date", Category="Beam")
	FOptionalString Date = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Install Date", Category="Beam")
	FOptionalString InstallDate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Days Played", Category="Beam")
	FOptionalInt32 DaysPlayed = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sessions", Category="Beam")
	FOptionalArrayOfString Sessions = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};