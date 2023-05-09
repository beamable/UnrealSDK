#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetGameResponse.h"

#include "GetGameResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetGameResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetGameResponse To JSON String")
	static FString GetGameResponseToJsonString(const UGetGameResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetGameResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetGameResponse* Make(TArray<UProjectView*> Projects, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetGameResponse", meta=(NativeBreakFunc))
	static void Break(const UGetGameResponse* Serializable, TArray<UProjectView*>& Projects);
};