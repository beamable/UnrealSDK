#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceStorageReference.h"

#include "ServiceStorageReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceStorageReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceStorageReference To JSON String")
	static FString ServiceStorageReferenceToJsonString(const UServiceStorageReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceStorageReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, bEnabled, Id, StorageType, TemplateId, Checksum, Outer", NativeMakeFunc))
	static UServiceStorageReference* Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString Id, FOptionalString StorageType, FOptionalString TemplateId, FOptionalString Checksum, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceStorageReference", meta=(NativeBreakFunc))
	static void Break(const UServiceStorageReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& Id, FOptionalString& StorageType, FOptionalString& TemplateId, FOptionalString& Checksum);
};