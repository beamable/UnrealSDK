#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicReference.h"

#include "CloudsavingBasicReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCloudsavingBasicReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Json", DisplayName="CloudsavingBasicReference To JSON String")
	static FString CloudsavingBasicReferenceToJsonString(const UCloudsavingBasicReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make CloudsavingBasicReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="ETag, Outer", NativeMakeFunc))
	static UCloudsavingBasicReference* Make(int64 Size, int64 LastModified, FString Key, FString BucketName, FOptionalString ETag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Break CloudsavingBasicReference", meta=(NativeBreakFunc))
	static void Break(const UCloudsavingBasicReference* Serializable, int64& Size, int64& LastModified, FString& Key, FString& BucketName, FOptionalString& ETag);
};