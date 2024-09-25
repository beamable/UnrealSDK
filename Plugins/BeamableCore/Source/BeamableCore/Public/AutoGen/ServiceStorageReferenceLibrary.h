#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ServiceStorageReference.h"

#include "ServiceStorageReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceStorageReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServiceStorageReference To JSON String")
	static FString ServiceStorageReferenceToJsonString(const UServiceStorageReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServiceStorageReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="TemplateId, Outer", NativeMakeFunc))
	static UServiceStorageReference* Make(bool bArchived, bool bEnabled, FString StorageType, FString Id, FString Checksum, FOptionalString TemplateId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServiceStorageReference", meta=(NativeBreakFunc))
	static void Break(const UServiceStorageReference* Serializable, bool& bArchived, bool& bEnabled, FString& StorageType, FString& Id, FString& Checksum, FOptionalString& TemplateId);
};