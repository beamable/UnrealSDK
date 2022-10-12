
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/RewardsResponse.h"

#include "GetRewardsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetRewardsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FOptionalString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FOptionalString ContentId;

	// Body Params
	

	// Beam Base Request Declaration
	UGetRewardsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_TournamentId,_ContentId,Outer"))
	static UGetRewardsRequest* MakeGetRewardsRequest(FOptionalString _TournamentId, FOptionalString _ContentId, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRewardsSuccess, FBeamRequestContext, Context, UGetRewardsRequest*, Request, URewardsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetRewardsError, FBeamRequestContext, Context, UGetRewardsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetRewardsComplete, FBeamRequestContext, Context, UGetRewardsRequest*, Request);

using FGetRewardsFullResponse = FBeamFullResponse<UGetRewardsRequest*, URewardsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetRewardsFullResponse, FGetRewardsFullResponse);
