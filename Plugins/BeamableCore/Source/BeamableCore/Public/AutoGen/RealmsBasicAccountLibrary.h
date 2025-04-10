#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicAccount.h"

#include "RealmsBasicAccountLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicAccountLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|4 - Json", DisplayName="RealmsBasicAccount To JSON String")
	static FString RealmsBasicAccountToJsonString(const URealmsBasicAccount* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Make RealmsBasicAccount", meta=(DefaultToSelf="Outer", AdvancedDisplay="Created, Outer", NativeMakeFunc))
	static URealmsBasicAccount* Make(FString User, FString Password, TArray<FString> Projects, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|3 - Backend", DisplayName="Break RealmsBasicAccount", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicAccount* Serializable, FString& User, FString& Password, TArray<FString>& Projects, FOptionalInt64& Created);
};