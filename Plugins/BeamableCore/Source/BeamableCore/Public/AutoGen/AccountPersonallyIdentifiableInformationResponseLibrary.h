#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountPersonallyIdentifiableInformationResponse.h"

#include "AccountPersonallyIdentifiableInformationResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountPersonallyIdentifiableInformationResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="AccountPersonallyIdentifiableInformationResponse To JSON String")
	static FString AccountPersonallyIdentifiableInformationResponseToJsonString(const UAccountPersonallyIdentifiableInformationResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make AccountPersonallyIdentifiableInformationResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAccountPersonallyIdentifiableInformationResponse* Make(UAccountsBasicAccount* Account, UListAuditResponse* PaymentAudits, TArray<UStatsResponse*> Stats, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break AccountPersonallyIdentifiableInformationResponse", meta=(NativeBreakFunc))
	static void Break(const UAccountPersonallyIdentifiableInformationResponse* Serializable, UAccountsBasicAccount*& Account, UListAuditResponse*& PaymentAudits, TArray<UStatsResponse*>& Stats);
};