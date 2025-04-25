#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListMailCategoriesResponse.h"

#include "ListMailCategoriesResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListMailCategoriesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="ListMailCategoriesResponse To JSON String")
	static FString ListMailCategoriesResponseToJsonString(const UListMailCategoriesResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make ListMailCategoriesResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListMailCategoriesResponse* Make(TArray<FString> Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break ListMailCategoriesResponse", meta=(NativeBreakFunc))
	static void Break(const UListMailCategoriesResponse* Serializable, TArray<FString>& Result);
};