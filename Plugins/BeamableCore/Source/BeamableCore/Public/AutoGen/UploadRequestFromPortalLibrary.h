#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UploadRequestFromPortal.h"

#include "UploadRequestFromPortalLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUploadRequestFromPortalLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UploadRequestFromPortal To JSON String")
	static FString UploadRequestFromPortalToJsonString(const UUploadRequestFromPortal* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UploadRequestFromPortal", meta=(DefaultToSelf="Outer", AdvancedDisplay="LastModified, Metadata, Outer", NativeMakeFunc))
	static UUploadRequestFromPortal* Make(FString ObjectKey, int64 SizeInBytes, FOptionalInt64 LastModified, FOptionalArrayOfMetadataPair Metadata, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UploadRequestFromPortal", meta=(NativeBreakFunc))
	static void Break(const UUploadRequestFromPortal* Serializable, FString& ObjectKey, int64& SizeInBytes, FOptionalInt64& LastModified, FOptionalArrayOfMetadataPair& Metadata);
};