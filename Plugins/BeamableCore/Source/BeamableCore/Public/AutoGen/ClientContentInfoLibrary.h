#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClientContentInfo.h"

#include "ClientContentInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientContentInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ClientContentInfo To JSON String")
	static FString ClientContentInfoToJsonString(const UClientContentInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ClientContentInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="UpdatedAt, Checksum, CreatedAt, Outer", NativeMakeFunc))
	static UClientContentInfo* Make(FString Uri, FString Version, FBeamContentId ContentId, EBeamContentType Type, TArray<FString> Tags, FOptionalInt64 UpdatedAt, FOptionalString Checksum, FOptionalInt64 CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ClientContentInfo", meta=(NativeBreakFunc))
	static void Break(const UClientContentInfo* Serializable, FString& Uri, FString& Version, FBeamContentId& ContentId, EBeamContentType& Type, TArray<FString>& Tags, FOptionalInt64& UpdatedAt, FOptionalString& Checksum, FOptionalInt64& CreatedAt);
};