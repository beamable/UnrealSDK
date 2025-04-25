#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmRolesReport.h"

#include "RealmRolesReportLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmRolesReportLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="RealmRolesReport To JSON String")
	static FString RealmRolesReportToJsonString(const URealmRolesReport* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make RealmRolesReport", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmRolesReport* Make(FString RealmName, FString RealmDisplayName, TArray<FString> Roles, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break RealmRolesReport", meta=(NativeBreakFunc))
	static void Break(const URealmRolesReport* Serializable, FString& RealmName, FString& RealmDisplayName, TArray<FString>& Roles);
};