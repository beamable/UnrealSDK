
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/UpdateRole.h"

#include "UpdateRoleLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateRoleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UpdateRole To JSON String")
	static FString UpdateRoleToJsonString(const UUpdateRole* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UpdateRole", meta=(DefaultToSelf="Outer", AdvancedDisplay="Cid, Realm, Role, Outer", NativeMakeFunc))
	static UUpdateRole* Make(FOptionalString Cid, FOptionalString Realm, FOptionalString Role, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UpdateRole", meta=(NativeBreakFunc))
	static void Break(const UUpdateRole* Serializable, FOptionalString& Cid, FOptionalString& Realm, FOptionalString& Role);
};