#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ObjectsMetadataResponse.h"

#include "ObjectsMetadataResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UObjectsMetadataResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ObjectsMetadataResponse To JSON String")
	static FString ObjectsMetadataResponseToJsonString(const UObjectsMetadataResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ObjectsMetadataResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UObjectsMetadataResponse* Make(TArray<UObjectMetadataResponse*> Response, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ObjectsMetadataResponse", meta=(NativeBreakFunc))
	static void Break(const UObjectsMetadataResponse* Serializable, TArray<UObjectMetadataResponse*>& Response);
};