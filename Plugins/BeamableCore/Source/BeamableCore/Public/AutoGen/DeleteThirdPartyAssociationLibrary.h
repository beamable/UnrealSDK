#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteThirdPartyAssociation.h"

#include "DeleteThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DeleteThirdPartyAssociation To JSON String")
	static FString DeleteThirdPartyAssociationToJsonString(const UDeleteThirdPartyAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DeleteThirdPartyAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDeleteThirdPartyAssociation* Make(FString ThirdParty, FString UserAppId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DeleteThirdPartyAssociation", meta=(NativeBreakFunc))
	static void Break(const UDeleteThirdPartyAssociation* Serializable, FString& ThirdParty, FString& UserAppId);
};