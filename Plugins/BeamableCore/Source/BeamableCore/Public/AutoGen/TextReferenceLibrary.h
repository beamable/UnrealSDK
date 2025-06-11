#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TextReference.h"

#include "TextReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTextReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="TextReference To JSON String")
	static FString TextReferenceToJsonString(const UTextReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make TextReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Checksum, LastChanged, Created, Outer", NativeMakeFunc))
	static UTextReference* Make(FString Uri, FString Version, FBeamContentId Id, FString Type, FString Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalInt64 LastChanged, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break TextReference", meta=(NativeBreakFunc))
	static void Break(const UTextReference* Serializable, FString& Uri, FString& Version, FBeamContentId& Id, FString& Type, FString& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalInt64& LastChanged, FOptionalInt64& Created);
};