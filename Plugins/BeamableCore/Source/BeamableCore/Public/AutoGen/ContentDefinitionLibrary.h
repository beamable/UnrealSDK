#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentDefinition.h"

#include "ContentDefinitionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|4 - Json", DisplayName="ContentDefinition To JSON String")
	static FString ContentDefinitionToJsonString(const UContentDefinition* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Make ContentDefinition", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tags, Variants, Outer", NativeMakeFunc))
	static UContentDefinition* Make(FBeamContentId Id, FString Checksum, TMap<FString, UContentMeta*> Properties, FOptionalArrayOfString Tags, FOptionalArrayOfMapOfContentMeta Variants, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Break ContentDefinition", meta=(NativeBreakFunc))
	static void Break(const UContentDefinition* Serializable, FBeamContentId& Id, FString& Checksum, TMap<FString, UContentMeta*>& Properties, FOptionalArrayOfString& Tags, FOptionalArrayOfMapOfContentMeta& Variants);
};