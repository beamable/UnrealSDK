#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupRole.h"

#include "GroupRoleLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupRoleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GroupRole To JSON String")
	static FString GroupRoleToJsonString(const UGroupRole* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GroupRole", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGroupRole* Make(FString Name, TArray<FString> Permissions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GroupRole", meta=(NativeBreakFunc))
	static void Break(const UGroupRole* Serializable, FString& Name, TArray<FString>& Permissions);
};