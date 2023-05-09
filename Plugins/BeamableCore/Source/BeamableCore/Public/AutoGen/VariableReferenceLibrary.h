#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/VariableReference.h"

#include "VariableReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UVariableReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - VariableReference To JSON String")
	static FString VariableReferenceToJsonString(const UVariableReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make VariableReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UVariableReference* Make(FString Name, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break VariableReference", meta=(NativeBreakFunc))
	static void Break(const UVariableReference* Serializable, FString& Name);
};