#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTransactionState.h"
#include "BeamableCore/Public/AutoGen/TransactionDetails.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTransactionHistoryEntry.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

#include "Transaction.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTransaction : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	int64 PlayerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Transaction Id", Category="Beam")
	int64 TransactionId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Name", Category="Beam")
	FString ProviderName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Details", Category="Beam")
	UTransactionDetails* Details = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is In Terminal State", Category="Beam")
	FOptionalBool bIsInTerminalState = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="State", Category="Beam")
	FOptionalTransactionState State = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Provider Id", Category="Beam")
	FOptionalString ProviderId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	FOptionalDateTime Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated", Category="Beam")
	FOptionalDateTime Updated = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FOptionalString Version = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Replay Guard Value", Category="Beam")
	FOptionalString ReplayGuardValue = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="History", Category="Beam")
	FOptionalArrayOfTransactionHistoryEntry History = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};