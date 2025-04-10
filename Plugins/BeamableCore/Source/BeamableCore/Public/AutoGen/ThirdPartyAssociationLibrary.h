#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ThirdPartyAssociation.h"

#include "ThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="ThirdPartyAssociation To JSON String")
	static FString ThirdPartyAssociationToJsonString(const UThirdPartyAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make ThirdPartyAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Email, UserBusinessId, Outer", NativeMakeFunc))
	static UThirdPartyAssociation* Make(FString Name, FString UserAppId, FString AppId, TMap<FString, FString> Meta, FOptionalString Email, FOptionalString UserBusinessId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break ThirdPartyAssociation", meta=(NativeBreakFunc))
	static void Break(const UThirdPartyAssociation* Serializable, FString& Name, FString& UserAppId, FString& AppId, TMap<FString, FString>& Meta, FOptionalString& Email, FOptionalString& UserBusinessId);
};