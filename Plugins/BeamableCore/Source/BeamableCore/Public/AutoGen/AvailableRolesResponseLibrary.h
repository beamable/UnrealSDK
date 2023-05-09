#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AvailableRolesResponse.h"

#include "AvailableRolesResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAvailableRolesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AvailableRolesResponse To JSON String")
	static FString AvailableRolesResponseToJsonString(const UAvailableRolesResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AvailableRolesResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAvailableRolesResponse* Make(TArray<FString> Roles, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AvailableRolesResponse", meta=(NativeBreakFunc))
	static void Break(const UAvailableRolesResponse* Serializable, TArray<FString>& Roles);
};