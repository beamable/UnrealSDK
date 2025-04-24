#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentDefinition.h"

#include "ContentDefinitionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ContentDefinition To JSON String")
	static FString ContentDefinitionToJsonString(const UContentDefinition* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ContentDefinition", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tags, Variants, Outer", NativeMakeFunc))
	static UContentDefinition* Make(FBeamContentId Id, FString Checksum, TMap<FString, UContentMeta*> Properties, FOptionalArrayOfString Tags, FOptionalArrayOfMapOfContentMeta Variants, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ContentDefinition", meta=(NativeBreakFunc))
	static void Break(const UContentDefinition* Serializable, FBeamContentId& Id, FString& Checksum, TMap<FString, UContentMeta*>& Properties, FOptionalArrayOfString& Tags, FOptionalArrayOfMapOfContentMeta& Variants);
};