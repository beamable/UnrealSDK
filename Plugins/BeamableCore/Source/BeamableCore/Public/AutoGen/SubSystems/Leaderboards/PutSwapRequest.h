
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaderboardSwapRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PutSwapRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutSwapRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	ULeaderboardSwapRequestBody* Body = {};

	// Beam Base Request Declaration
	UPutSwapRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make PutSwap",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_WinnerId,_LoserId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutSwapRequest* Make(FString _ObjectId, int64 _SwapBase, int64 _Delta, FOptionalInt64 _WinnerId, FOptionalInt64 _LoserId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSwapSuccess, FBeamRequestContext, Context, UPutSwapRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutSwapError, FBeamRequestContext, Context, UPutSwapRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutSwapComplete, FBeamRequestContext, Context, UPutSwapRequest*, Request);

using FPutSwapFullResponse = FBeamFullResponse<UPutSwapRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPutSwapFullResponse, FPutSwapFullResponse);
