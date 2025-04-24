#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListTagsRequestBody.h"

#include "ListTagsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListTagsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="ListTagsRequestBody To JSON String")
	static FString ListTagsRequestBodyToJsonString(const UListTagsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make ListTagsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="TagNameFilter, Outer", NativeMakeFunc))
	static UListTagsRequestBody* Make(FOptionalString TagNameFilter, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break ListTagsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UListTagsRequestBody* Serializable, FOptionalString& TagNameFilter);
};