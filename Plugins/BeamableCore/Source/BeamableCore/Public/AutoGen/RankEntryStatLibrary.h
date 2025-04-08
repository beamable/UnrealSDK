#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RankEntryStat.h"

#include "RankEntryStatLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URankEntryStatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="RankEntryStat To JSON String")
	static FString RankEntryStatToJsonString(const URankEntryStat* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make RankEntryStat", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URankEntryStat* Make(FString Name, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break RankEntryStat", meta=(NativeBreakFunc))
	static void Break(const URankEntryStat* Serializable, FString& Name, FString& Value);
};