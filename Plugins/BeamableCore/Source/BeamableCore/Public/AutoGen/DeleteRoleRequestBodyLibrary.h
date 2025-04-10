#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteRoleRequestBody.h"

#include "DeleteRoleRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteRoleRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="DeleteRoleRequestBody To JSON String")
	static FString DeleteRoleRequestBodyToJsonString(const UDeleteRoleRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make DeleteRoleRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Realm, Role, Outer", NativeMakeFunc))
	static UDeleteRoleRequestBody* Make(FOptionalBeamPid Realm, FOptionalString Role, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break DeleteRoleRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteRoleRequestBody* Serializable, FOptionalBeamPid& Realm, FOptionalString& Role);
};