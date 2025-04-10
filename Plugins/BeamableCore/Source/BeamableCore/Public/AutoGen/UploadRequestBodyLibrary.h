#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UploadRequestBody.h"

#include "UploadRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUploadRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|4 - Json", DisplayName="UploadRequestBody To JSON String")
	static FString UploadRequestBodyToJsonString(const UUploadRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|3 - Backend", DisplayName="Make UploadRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bDeleted, LastModified, Checksum, Metadata, Outer", NativeMakeFunc))
	static UUploadRequestBody* Make(FString ObjectKey, int64 SizeInBytes, FOptionalBool bDeleted, FOptionalInt64 LastModified, FOptionalString Checksum, FOptionalArrayOfMetadataPair Metadata, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|3 - Backend", DisplayName="Break UploadRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUploadRequestBody* Serializable, FString& ObjectKey, int64& SizeInBytes, FOptionalBool& bDeleted, FOptionalInt64& LastModified, FOptionalString& Checksum, FOptionalArrayOfMetadataPair& Metadata);
};