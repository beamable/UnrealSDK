#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/GetManifestRequestJson.h"

#include "GetManifestRequestJsonLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestRequestJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetManifestRequestJson To JSON String")
	static FString GetManifestRequestJsonToJsonString(const UGetManifestRequestJson* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetManifestRequestJson", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Outer", NativeMakeFunc))
	static UGetManifestRequestJson* Make(FOptionalBeamContentManifestId Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetManifestRequestJson", meta=(NativeBreakFunc))
	static void Break(const UGetManifestRequestJson* Serializable, FOptionalBeamContentManifestId& Id);
};