
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/RewardsRequestBody.h"
#include "BeamableCore/Public/AutoGen/RewardsResponse.h"

#include "PostRewardsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostRewardsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	URewardsRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostRewardsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make PostRewards",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_TournamentId,_ContentId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostRewardsRequest* Make(FOptionalString _TournamentId, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRewardsSuccess, FBeamRequestContext, Context, UPostRewardsRequest*, Request, URewardsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostRewardsError, FBeamRequestContext, Context, UPostRewardsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostRewardsComplete, FBeamRequestContext, Context, UPostRewardsRequest*, Request);

using FPostRewardsFullResponse = FBeamFullResponse<UPostRewardsRequest*, URewardsResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostRewardsFullResponse, FPostRewardsFullResponse);
