#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RemoveTags.h"

#include "RemoveTagsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URemoveTagsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RemoveTags To JSON String")
	static FString RemoveTagsToJsonString(const URemoveTags* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RemoveTags", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Tags, Outer", NativeMakeFunc))
	static URemoveTags* Make(FOptionalString PlayerId, FOptionalArrayOfString Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RemoveTags", meta=(NativeBreakFunc))
	static void Break(const URemoveTags* Serializable, FOptionalString& PlayerId, FOptionalArrayOfString& Tags);
};