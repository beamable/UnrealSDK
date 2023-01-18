
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/BinaryReference.h"

#include "BinaryReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBinaryReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BinaryReference To JSON String")
	static FString BinaryReferenceToJsonString(const UBinaryReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BinaryReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Checksum, LastChanged, Created, Outer", NativeMakeFunc))
	static UBinaryReference* Make(FString UploadMethod, FString ContentPrefix, FString Uri, FString Version, FBeamContentId Id, FString UploadUri, FString Type, EContentVisibility Visibility, TArray<FString> Tags, FOptionalString Checksum, FOptionalInt64 LastChanged, FOptionalInt64 Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BinaryReference", meta=(NativeBreakFunc))
	static void Break(const UBinaryReference* Serializable, FString& UploadMethod, FString& ContentPrefix, FString& Uri, FString& Version, FBeamContentId& Id, FString& UploadUri, FString& Type, EContentVisibility& Visibility, TArray<FString>& Tags, FOptionalString& Checksum, FOptionalInt64& LastChanged, FOptionalInt64& Created);
};