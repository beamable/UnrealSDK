#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BinaryReference.h"

#include "BinaryReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBinaryReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="BinaryReference To JSON String")
	static FString BinaryReferenceToJsonString(const UBinaryReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make BinaryReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Checksum, LastChanged, Created, Outer", NativeMakeFunc))
	static UBinaryReference* Make(FString UploadMethod, FString Uri, FString Version, FBeamContentId Id, FString UploadUri, FString Type, FString Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalString LastChanged, FOptionalString Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break BinaryReference", meta=(NativeBreakFunc))
	static void Break(const UBinaryReference* Serializable, FString& UploadMethod, FString& Uri, FString& Version, FBeamContentId& Id, FString& UploadUri, FString& Type, FString& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalString& LastChanged, FOptionalString& Created);
};