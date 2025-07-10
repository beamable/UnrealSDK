#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveManifestResponse.h"

#include "SaveManifestResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="SaveManifestResponse To JSON String")
	static FString SaveManifestResponseToJsonString(const USaveManifestResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make SaveManifestResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="DiffUrl, Outer", NativeMakeFunc))
	static USaveManifestResponse* Make(FString Id, FString Checksum, FString Uid, int64 Created, FOptionalString DiffUrl, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break SaveManifestResponse", meta=(NativeBreakFunc))
	static void Break(const USaveManifestResponse* Serializable, FString& Id, FString& Checksum, FString& Uid, int64& Created, FOptionalString& DiffUrl);
};