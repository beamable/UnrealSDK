#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupScoreBinding.h"

#include "GroupScoreBindingLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupScoreBindingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupScoreBinding To JSON String")
	static FString GroupScoreBindingToJsonString(const UGroupScoreBinding* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupScoreBinding", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGroupScoreBinding* Make(FString Board, int64 Score, TArray<FString> Derivatives, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupScoreBinding", meta=(NativeBreakFunc))
	static void Break(const UGroupScoreBinding* Serializable, FString& Board, int64& Score, TArray<FString>& Derivatives);
};