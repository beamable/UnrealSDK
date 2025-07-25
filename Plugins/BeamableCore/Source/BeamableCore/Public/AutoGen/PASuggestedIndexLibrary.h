#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PASuggestedIndex.h"

#include "PASuggestedIndexLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPASuggestedIndexLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="PASuggestedIndex To JSON String")
	static FString PASuggestedIndexToJsonString(const UPASuggestedIndex* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PASuggestedIndex", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPASuggestedIndex* Make(FString Weight, FString Id, FString Namespace, TArray<FString> Impact, TArray<FString> Index, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break PASuggestedIndex", meta=(NativeBreakFunc))
	static void Break(const UPASuggestedIndex* Serializable, FString& Weight, FString& Id, FString& Namespace, TArray<FString>& Impact, TArray<FString>& Index);
};