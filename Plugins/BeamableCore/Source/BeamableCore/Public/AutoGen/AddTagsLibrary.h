#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AddTags.h"

#include "AddTagsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAddTagsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|4 - Json", DisplayName="AddTags To JSON String")
	static FString AddTagsToJsonString(const UAddTags* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|3 - Backend", DisplayName="Make AddTags", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, bReplace, Tags, Outer", NativeMakeFunc))
	static UAddTags* Make(FOptionalBeamGamerTag PlayerId, FOptionalBool bReplace, FOptionalArrayOfBeamTag Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|3 - Backend", DisplayName="Break AddTags", meta=(NativeBreakFunc))
	static void Break(const UAddTags* Serializable, FOptionalBeamGamerTag& PlayerId, FOptionalBool& bReplace, FOptionalArrayOfBeamTag& Tags);
};