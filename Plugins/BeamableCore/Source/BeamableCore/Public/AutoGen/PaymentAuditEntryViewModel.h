
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/PaymentHistoryEntryViewModel.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalArrayOfCurrencyChange.h"
#include "AutoGen/EntitlementGenerator.h"
#include "AutoGen/PaymentDetailsEntryViewModel.h"

#include "PaymentAuditEntryViewModel.generated.h"

UCLASS(BlueprintType)
class UPaymentAuditEntryViewModel : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Providerid")
	FString Providerid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="History")
	TArray<UPaymentHistoryEntryViewModel*> History;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txid")
	int64 Txid;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Providername")
	FString Providername;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Version")
	FOptionalString Version;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Items")
	FOptionalArrayOfItemCreateRequestBody ObtainItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Txstate")
	FString Txstate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated")
	FOptionalInt64 Updated;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Obtain Currency")
	FOptionalArrayOfCurrencyChange ObtainCurrency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Entitlements")
	TArray<UEntitlementGenerator*> Entitlements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Details")
	UPaymentDetailsEntryViewModel* Details;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Replay Guard Value")
	FOptionalString ReplayGuardValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gt")
	int64 Gt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created")
	FOptionalInt64 Created;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};