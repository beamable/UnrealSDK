#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupMetaData.h"

#include "GroupMetaDataLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupMetaDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupMetaData To JSON String")
	static FString GroupMetaDataToJsonString(const UGroupMetaData* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupMetaData", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Tag, Outer", NativeMakeFunc))
	static UGroupMetaData* Make(int64 Id, FOptionalString Name, FOptionalString Tag, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupMetaData", meta=(NativeBreakFunc))
	static void Break(const UGroupMetaData* Serializable, int64& Id, FOptionalString& Name, FOptionalString& Tag);
};