
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LeaderboardSwapRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PutSwapRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutSwapRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	ULeaderboardSwapRequestBody* Body;

	// Beam Base Request Declaration
	UPutSwapRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_WinnerId,_LoserId,Outer"))
	static UPutSwapRequest* MakePutSwapRequest(FString _ObjectId, FOptionalInt64 _WinnerId, FOptionalInt64 _LoserId, int64 _SwapBase, int64 _Delta, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSwapSuccess, FBeamRequestContext, Context, UPutSwapRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSwapError, FBeamRequestContext, Context, UPutSwapRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutSwapComplete, FBeamRequestContext, Context, UPutSwapRequest*, Request);

using FPutSwapFullResponse = FBeamFullResponse<UPutSwapRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutSwapFullResponse, FPutSwapFullResponse);
