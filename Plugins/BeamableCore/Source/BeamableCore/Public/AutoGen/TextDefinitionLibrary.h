#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TextDefinition.h"

#include "TextDefinitionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTextDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="TextDefinition To JSON String")
	static FString TextDefinitionToJsonString(const UTextDefinition* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make TextDefinition", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tags, Outer", NativeMakeFunc))
	static UTextDefinition* Make(FBeamContentId Id, FString Checksum, TMap<FString, FString> Properties, FOptionalArrayOfString Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break TextDefinition", meta=(NativeBreakFunc))
	static void Break(const UTextDefinition* Serializable, FBeamContentId& Id, FString& Checksum, TMap<FString, FString>& Properties, FOptionalArrayOfString& Tags);
};