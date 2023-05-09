#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FacebookUpdatedEntry.h"

#include "FacebookUpdatedEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFacebookUpdatedEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - FacebookUpdatedEntry To JSON String")
	static FString FacebookUpdatedEntryToJsonString(const UFacebookUpdatedEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make FacebookUpdatedEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFacebookUpdatedEntry* Make(FString Id, int64 Time, TArray<FString> ChangedFields, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break FacebookUpdatedEntry", meta=(NativeBreakFunc))
	static void Break(const UFacebookUpdatedEntry* Serializable, FString& Id, int64& Time, TArray<FString>& ChangedFields);
};