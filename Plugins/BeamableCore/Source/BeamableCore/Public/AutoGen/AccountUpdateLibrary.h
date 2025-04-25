#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountUpdate.h"

#include "AccountUpdateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="AccountUpdate To JSON String")
	static FString AccountUpdateToJsonString(const UAccountUpdate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make AccountUpdate", meta=(DefaultToSelf="Outer", AdvancedDisplay="ThirdParty, Country, Language, GamerTagAssoc, Token, DeviceId, UserName, External, Outer", NativeMakeFunc))
	static UAccountUpdate* Make(bool bHasThirdPartyToken, FOptionalString ThirdParty, FOptionalString Country, FOptionalString Language, FOptionalGamerTagAssociation GamerTagAssoc, FOptionalString Token, FOptionalString DeviceId, FOptionalString UserName, FOptionalArrayOfBeamExternalIdentity External, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break AccountUpdate", meta=(NativeBreakFunc))
	static void Break(const UAccountUpdate* Serializable, bool& bHasThirdPartyToken, FOptionalString& ThirdParty, FOptionalString& Country, FOptionalString& Language, FOptionalGamerTagAssociation& GamerTagAssoc, FOptionalString& Token, FOptionalString& DeviceId, FOptionalString& UserName, FOptionalArrayOfBeamExternalIdentity& External);
};