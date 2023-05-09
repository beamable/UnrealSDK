#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListTagsResponse.h"

#include "ListTagsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListTagsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ListTagsResponse To JSON String")
	static FString ListTagsResponseToJsonString(const UListTagsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ListTagsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListTagsResponse* Make(TArray<FString> Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ListTagsResponse", meta=(NativeBreakFunc))
	static void Break(const UListTagsResponse* Serializable, TArray<FString>& Tags);
};