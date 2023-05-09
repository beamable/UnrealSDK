#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClientPermission.h"

#include "ClientPermissionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientPermissionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ClientPermission To JSON String")
	static FString ClientPermissionToJsonString(const UClientPermission* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ClientPermission", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UClientPermission* Make(bool bWriteSelf, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ClientPermission", meta=(NativeBreakFunc))
	static void Break(const UClientPermission* Serializable, bool& bWriteSelf);
};