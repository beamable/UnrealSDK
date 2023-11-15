#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AccountPortalView.h"

#include "AccountPortalViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAccountPortalViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AccountPortalView To JSON String")
	static FString AccountPortalViewToJsonString(const UAccountPortalView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AccountPortalView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Email, RoleString, Language, External, Roles, Outer", NativeMakeFunc))
	static UAccountPortalView* Make(FBeamAccountId Id, TArray<FString> Scopes, TArray<FString> ThirdPartyAppAssociations, FOptionalString Email, FOptionalString RoleString, FOptionalString Language, FOptionalArrayOfBeamExternalIdentity External, FOptionalArrayOfRoleMapping Roles, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AccountPortalView", meta=(NativeBreakFunc))
	static void Break(const UAccountPortalView* Serializable, FBeamAccountId& Id, TArray<FString>& Scopes, TArray<FString>& ThirdPartyAppAssociations, FOptionalString& Email, FOptionalString& RoleString, FOptionalString& Language, FOptionalArrayOfBeamExternalIdentity& External, FOptionalArrayOfRoleMapping& Roles);
};