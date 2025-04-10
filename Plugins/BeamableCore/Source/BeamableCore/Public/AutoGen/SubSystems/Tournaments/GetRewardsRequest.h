
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/RewardsResponse.h"

#include "GetRewardsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRewardsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id", Category="Beam")
	FOptionalString TournamentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id", Category="Beam")
	FOptionalString ContentId = {};

	// Body Params
	

	// Beam Base Request Declaration
	UGetRewardsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make GetRewards",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_TournamentId,_ContentId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetRewardsRequest* Make(FOptionalString _TournamentId, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRewardsSuccess, FBeamRequestContext, Context, UGetRewardsRequest*, Request, URewardsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRewardsError, FBeamRequestContext, Context, UGetRewardsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRewardsComplete, FBeamRequestContext, Context, UGetRewardsRequest*, Request);

using FGetRewardsFullResponse = FBeamFullResponse<UGetRewardsRequest*, URewardsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRewardsFullResponse, FGetRewardsFullResponse);
