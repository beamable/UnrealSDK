#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MetadataPair.h"

#include "MetadataPairLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMetadataPairLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MetadataPair To JSON String")
	static FString MetadataPairToJsonString(const UMetadataPair* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MetadataPair", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMetadataPair* Make(FString Key, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MetadataPair", meta=(NativeBreakFunc))
	static void Break(const UMetadataPair* Serializable, FString& Key, FString& Value);
};