#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListTokensRequestBody.h"

#include "ListTokensRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListTokensRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ListTokensRequestBody To JSON String")
	static FString ListTokensRequestBodyToJsonString(const UListTokensRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ListTokensRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Cid, Pid, Outer", NativeMakeFunc))
	static UListTokensRequestBody* Make(int32 PageSize, int32 Page, int64 GamerTagOrAccountId, FOptionalBeamCid Cid, FOptionalBeamPid Pid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ListTokensRequestBody", meta=(NativeBreakFunc))
	static void Break(const UListTokensRequestBody* Serializable, int32& PageSize, int32& Page, int64& GamerTagOrAccountId, FOptionalBeamCid& Cid, FOptionalBeamPid& Pid);
};