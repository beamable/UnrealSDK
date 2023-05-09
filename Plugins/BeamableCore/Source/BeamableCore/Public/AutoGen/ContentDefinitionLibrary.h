#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentDefinition.h"

#include "ContentDefinitionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ContentDefinition To JSON String")
	static FString ContentDefinitionToJsonString(const UContentDefinition* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ContentDefinition", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tags, Variants, Outer", NativeMakeFunc))
	static UContentDefinition* Make(FString Prefix, FBeamContentId Id, FString Checksum, TMap<FString, UContentMeta*> Properties, FOptionalArrayOfString Tags, FOptionalArrayOfMapOfContentMeta Variants, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ContentDefinition", meta=(NativeBreakFunc))
	static void Break(const UContentDefinition* Serializable, FString& Prefix, FBeamContentId& Id, FString& Checksum, TMap<FString, UContentMeta*>& Properties, FOptionalArrayOfString& Tags, FOptionalArrayOfMapOfContentMeta& Variants);
};