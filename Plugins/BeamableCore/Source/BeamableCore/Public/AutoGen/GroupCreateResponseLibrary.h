#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupCreateResponse.h"

#include "GroupCreateResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupCreateResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GroupCreateResponse To JSON String")
	static FString GroupCreateResponseToJsonString(const UGroupCreateResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GroupCreateResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGroupCreateResponse* Make(UGroupMetaData* Group, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GroupCreateResponse", meta=(NativeBreakFunc))
	static void Break(const UGroupCreateResponse* Serializable, UGroupMetaData*& Group);
};