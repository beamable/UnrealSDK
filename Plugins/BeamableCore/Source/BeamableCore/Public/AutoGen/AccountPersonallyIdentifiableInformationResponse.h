
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/AccountsBasicAccount.h"
#include "AutoGen/StatsResponse.h"
#include "AutoGen/ListAuditResponse.h"

#include "AccountPersonallyIdentifiableInformationResponse.generated.h"

UCLASS(BlueprintType)
class UAccountPersonallyIdentifiableInformationResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account")
	UAccountsBasicAccount* Account;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats")
	TArray<UStatsResponse*> Stats;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payment Audits")
	UListAuditResponse* PaymentAudits;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};