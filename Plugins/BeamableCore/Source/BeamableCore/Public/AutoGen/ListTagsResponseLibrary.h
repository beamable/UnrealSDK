#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListTagsResponse.h"

#include "ListTagsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListTagsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="ListTagsResponse To JSON String")
	static FString ListTagsResponseToJsonString(const UListTagsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make ListTagsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListTagsResponse* Make(TArray<FString> Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break ListTagsResponse", meta=(NativeBreakFunc))
	static void Break(const UListTagsResponse* Serializable, TArray<FString>& Tags);
};