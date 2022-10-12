
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/ScoreRequestBody.h"
#include "AutoGen/EmptyResponse.h"

#include "PostScoreRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostScoreRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UScoreRequestBody* Body;

	// Beam Base Request Declaration
	UPostScoreRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_Stats,_bIncrement,Outer"))
	static UPostScoreRequest* MakePostScoreRequest(FString _TournamentId, FOptionalMapOfString _Stats, double _Score, int64 _PlayerId, FOptionalBool _bIncrement, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostScoreSuccess, FBeamRequestContext, Context, UPostScoreRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostScoreError, FBeamRequestContext, Context, UPostScoreRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostScoreComplete, FBeamRequestContext, Context, UPostScoreRequest*, Request);

using FPostScoreFullResponse = FBeamFullResponse<UPostScoreRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostScoreFullResponse, FPostScoreFullResponse);
