#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/UpdateRole.h"

#include "UpdateRoleLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateRoleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UpdateRole To JSON String")
	static FString UpdateRoleToJsonString(const UUpdateRole* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UpdateRole", meta=(DefaultToSelf="Outer", AdvancedDisplay="Cid, Realm, Role, Outer", NativeMakeFunc))
	static UUpdateRole* Make(FOptionalBeamCid Cid, FOptionalBeamPid Realm, FOptionalString Role, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UpdateRole", meta=(NativeBreakFunc))
	static void Break(const UUpdateRole* Serializable, FOptionalBeamCid& Cid, FOptionalBeamPid& Realm, FOptionalString& Role);
};