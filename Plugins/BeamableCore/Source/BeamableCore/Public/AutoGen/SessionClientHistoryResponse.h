#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/LocalDate.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"

#include "SessionClientHistoryResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USessionClientHistoryResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Date", Category="Beam")
	ULocalDate* Date = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Days Played", Category="Beam")
	int32 DaysPlayed = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Sessions", Category="Beam")
	TArray<FString> Sessions = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Install Date", Category="Beam")
	FOptionalString InstallDate = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};