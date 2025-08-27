#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/NewGameRequestBody.h"

#include "NewGameRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UNewGameRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="NewGameRequestBody To JSON String")
	static FString NewGameRequestBodyToJsonString(const UNewGameRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make NewGameRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UNewGameRequestBody* Make(FString GameName, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break NewGameRequestBody", meta=(NativeBreakFunc))
	static void Break(const UNewGameRequestBody* Serializable, FString& GameName);
};