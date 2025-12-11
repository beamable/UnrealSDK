#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicNewGameRequestBody.h"

#include "RealmsBasicNewGameRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicNewGameRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicNewGameRequestBody To JSON String")
	static FString RealmsBasicNewGameRequestBodyToJsonString(const URealmsBasicNewGameRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicNewGameRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmsBasicNewGameRequestBody* Make(FString GameName, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicNewGameRequestBody", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicNewGameRequestBody* Serializable, FString& GameName);
};