#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ObjectMetadataResponse.h"

#include "ObjectMetadataResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UObjectMetadataResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Json", DisplayName="ObjectMetadataResponse To JSON String")
	static FString ObjectMetadataResponseToJsonString(const UObjectMetadataResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Make ObjectMetadataResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UObjectMetadataResponse* Make(FString ObjectKey, TMap<FString, FString> Metadata, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Cloudsaving|Utils|Make/Break", DisplayName="Break ObjectMetadataResponse", meta=(NativeBreakFunc))
	static void Break(const UObjectMetadataResponse* Serializable, FString& ObjectKey, TMap<FString, FString>& Metadata);
};