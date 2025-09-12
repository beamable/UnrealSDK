#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentTagFilter.h"

#include "ContentTagFilterLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentTagFilterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="ContentTagFilter To JSON String")
	static FString ContentTagFilterToJsonString(const UContentTagFilter* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make ContentTagFilter", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UContentTagFilter* Make(TArray<FString> AllOf, TArray<FString> AnyOf, TArray<FString> NoneOf, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break ContentTagFilter", meta=(NativeBreakFunc))
	static void Break(const UContentTagFilter* Serializable, TArray<FString>& AllOf, TArray<FString>& AnyOf, TArray<FString>& NoneOf);
};