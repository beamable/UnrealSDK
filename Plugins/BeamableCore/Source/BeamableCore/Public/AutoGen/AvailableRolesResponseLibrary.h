#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AvailableRolesResponse.h"

#include "AvailableRolesResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAvailableRolesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="AvailableRolesResponse To JSON String")
	static FString AvailableRolesResponseToJsonString(const UAvailableRolesResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make AvailableRolesResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAvailableRolesResponse* Make(TArray<FString> Roles, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break AvailableRolesResponse", meta=(NativeBreakFunc))
	static void Break(const UAvailableRolesResponse* Serializable, TArray<FString>& Roles);
};