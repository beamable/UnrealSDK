#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentReference.h"

#include "ContentReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|4 - Json", DisplayName="ContentReference To JSON String")
	static FString ContentReferenceToJsonString(const UContentReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Make ContentReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Checksum, LastChanged, Created, Outer", NativeMakeFunc))
	static UContentReference* Make(FString Tag, FString Uri, FString Version, FBeamContentId Id, FString Type, EContentVisibility Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalInt64 LastChanged, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Break ContentReference", meta=(NativeBreakFunc))
	static void Break(const UContentReference* Serializable, FString& Tag, FString& Uri, FString& Version, FBeamContentId& Id, FString& Type, EContentVisibility& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalInt64& LastChanged, FOptionalInt64& Created);
};