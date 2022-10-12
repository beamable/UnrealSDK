
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/RewardsRequestBody.h"
#include "AutoGen/RewardsResponse.h"

#include "PostRewardsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostRewardsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	URewardsRequestBody* Body;

	// Beam Base Request Declaration
	UPostRewardsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_TournamentId,_ContentId,Outer"))
	static UPostRewardsRequest* MakePostRewardsRequest(FOptionalString _TournamentId, FOptionalString _ContentId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRewardsSuccess, FBeamRequestContext, Context, UPostRewardsRequest*, Request, URewardsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRewardsError, FBeamRequestContext, Context, UPostRewardsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostRewardsComplete, FBeamRequestContext, Context, UPostRewardsRequest*, Request);

using FPostRewardsFullResponse = FBeamFullResponse<UPostRewardsRequest*, URewardsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostRewardsFullResponse, FPostRewardsFullResponse);
