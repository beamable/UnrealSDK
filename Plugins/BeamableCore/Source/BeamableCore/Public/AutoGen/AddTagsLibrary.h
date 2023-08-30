#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AddTags.h"

#include "AddTagsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAddTagsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AddTags To JSON String")
	static FString AddTagsToJsonString(const UAddTags* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AddTags", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, bReplace, Tags, Outer", NativeMakeFunc))
	static UAddTags* Make(FOptionalString PlayerId, FOptionalBool bReplace, FOptionalArrayOfTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AddTags", meta=(NativeBreakFunc))
	static void Break(const UAddTags* Serializable, FOptionalString& PlayerId, FOptionalBool& bReplace, FOptionalArrayOfTag& Tags);
};