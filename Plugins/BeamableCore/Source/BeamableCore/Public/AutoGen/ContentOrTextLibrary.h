#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentOrText.h"

#include "ContentOrTextLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentOrTextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ContentOrText To JSON String")
	static FString ContentOrTextToJsonString(const UContentOrText* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ContentOrText", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UContentOrText* Make(FBeamContentId Id, FString Version, TMap<FString, FString> Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ContentOrText", meta=(NativeBreakFunc))
	static void Break(const UContentOrText* Serializable, FBeamContentId& Id, FString& Version, TMap<FString, FString>& Properties);
};