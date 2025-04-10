#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BinaryDefinition.h"

#include "BinaryDefinitionLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBinaryDefinitionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="BinaryDefinition To JSON String")
	static FString BinaryDefinitionToJsonString(const UBinaryDefinition* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BinaryDefinition", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tags, Outer", NativeMakeFunc))
	static UBinaryDefinition* Make(FBeamContentId Id, FString Checksum, FString UploadContentType, FOptionalArrayOfString Tags, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break BinaryDefinition", meta=(NativeBreakFunc))
	static void Break(const UBinaryDefinition* Serializable, FBeamContentId& Id, FString& Checksum, FString& UploadContentType, FOptionalArrayOfString& Tags);
};