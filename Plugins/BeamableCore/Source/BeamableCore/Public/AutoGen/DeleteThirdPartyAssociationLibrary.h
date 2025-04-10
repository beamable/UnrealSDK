#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteThirdPartyAssociation.h"

#include "DeleteThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|4 - Json", DisplayName="DeleteThirdPartyAssociation To JSON String")
	static FString DeleteThirdPartyAssociationToJsonString(const UDeleteThirdPartyAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Make DeleteThirdPartyAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeleteThirdPartyAssociation* Make(FString ThirdParty, FString UserAppId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|3 - Backend", DisplayName="Break DeleteThirdPartyAssociation", meta=(NativeBreakFunc))
	static void Break(const UDeleteThirdPartyAssociation* Serializable, FString& ThirdParty, FString& UserAppId);
};