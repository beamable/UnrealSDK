#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/AccountsBasicAccount.h"
#include "BeamableCore/Public/AutoGen/StatsResponse.h"
#include "BeamableCore/Public/AutoGen/ListAuditResponse.h"

#include "AccountPersonallyIdentifiableInformationResponse.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UAccountPersonallyIdentifiableInformationResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Account", Category="Beam")
	UAccountsBasicAccount* Account = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Payment Audits", Category="Beam")
	UListAuditResponse* PaymentAudits = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Stats", Category="Beam")
	TArray<UStatsResponse*> Stats = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};