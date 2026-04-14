#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ThirdPartyAssociation.h"

#include "ThirdPartyAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UThirdPartyAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="ThirdPartyAssociation To JSON String")
	static FString ThirdPartyAssociationToJsonString(const UThirdPartyAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make ThirdPartyAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, AppId, UserAppId, UserBusinessId, Email, Meta, Outer", NativeMakeFunc))
	static UThirdPartyAssociation* Make(FOptionalString Name, FOptionalString AppId, FOptionalString UserAppId, FOptionalString UserBusinessId, FOptionalString Email, FOptionalMapOfString Meta, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break ThirdPartyAssociation", meta=(NativeBreakFunc))
	static void Break(const UThirdPartyAssociation* Serializable, FOptionalString& Name, FOptionalString& AppId, FOptionalString& UserAppId, FOptionalString& UserBusinessId, FOptionalString& Email, FOptionalMapOfString& Meta);
};