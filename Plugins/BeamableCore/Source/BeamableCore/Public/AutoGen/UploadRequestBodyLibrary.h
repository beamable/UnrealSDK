#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UploadRequestBody.h"

#include "UploadRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUploadRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Json", DisplayName="UploadRequestBody To JSON String")
	static FString UploadRequestBodyToJsonString(const UUploadRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make UploadRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bDeleted, LastModified, Checksum, Metadata, Outer", NativeMakeFunc))
	static UUploadRequestBody* Make(FString ObjectKey, int64 SizeInBytes, FOptionalBool bDeleted, FOptionalInt64 LastModified, FOptionalString Checksum, FOptionalArrayOfMetadataPair Metadata, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Break UploadRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUploadRequestBody* Serializable, FString& ObjectKey, int64& SizeInBytes, FOptionalBool& bDeleted, FOptionalInt64& LastModified, FOptionalString& Checksum, FOptionalArrayOfMetadataPair& Metadata);
};