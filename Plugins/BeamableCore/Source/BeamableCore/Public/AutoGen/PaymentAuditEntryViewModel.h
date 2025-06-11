#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/PaymentHistoryEntryViewModel.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCurrencyChange.h"
#include "BeamableCore/Public/AutoGen/EntitlementGenerator.h"
#include "BeamableCore/Public/AutoGen/PaymentDetailsEntryViewModel.h"

#include "PaymentAuditEntryViewModel.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UPaymentAuditEntryViewModel : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Providerid", Category="Beam")
	FString Providerid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txid", Category="Beam")
	int64 Txid = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Providername", Category="Beam")
	FString Providername = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txstate", Category="Beam")
	FString Txstate = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Details", Category="Beam")
	UPaymentDetailsEntryViewModel* Details = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gt", Category="Beam")
	int64 Gt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="History", Category="Beam")
	TArray<UPaymentHistoryEntryViewModel*> History = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entitlements", Category="Beam")
	TArray<UEntitlementGenerator*> Entitlements = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version", Category="Beam")
	FOptionalString Version = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated", Category="Beam")
	FOptionalInt64 Updated = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Replay Guard Value", Category="Beam")
	FOptionalString ReplayGuardValue = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	FOptionalInt64 Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Items", Category="Beam")
	FOptionalArrayOfItemCreateRequestBody ObtainItems = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Currency", Category="Beam")
	FOptionalArrayOfCurrencyChange ObtainCurrency = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};