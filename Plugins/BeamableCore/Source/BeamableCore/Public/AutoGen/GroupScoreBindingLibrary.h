#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupScoreBinding.h"

#include "GroupScoreBindingLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupScoreBindingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|4 - Json", DisplayName="GroupScoreBinding To JSON String")
	static FString GroupScoreBindingToJsonString(const UGroupScoreBinding* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|3 - Backend", DisplayName="Make GroupScoreBinding", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGroupScoreBinding* Make(FString Board, int64 Score, TArray<FString> Derivatives, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|3 - Backend", DisplayName="Break GroupScoreBinding", meta=(NativeBreakFunc))
	static void Break(const UGroupScoreBinding* Serializable, FString& Board, int64& Score, TArray<FString>& Derivatives);
};