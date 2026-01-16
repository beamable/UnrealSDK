#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TagList.h"

#include "TagListLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTagListLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Json", DisplayName="TagList To JSON String")
	static FString TagListToJsonString(const UTagList* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Make TagList", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tags, Outer", NativeMakeFunc))
	static UTagList* Make(FOptionalArrayOfBeamTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Make/Break", DisplayName="Break TagList", meta=(NativeBreakFunc))
	static void Break(const UTagList* Serializable, FOptionalArrayOfBeamTag& Tags);
};