
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/ScoreRequestBody.h"
#include "BeamableCore/Public/AutoGen/EmptyResponse.h"

#include "PostScoreRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostScoreRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UScoreRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostScoreRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make PostScore",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bIncrement,_ContentId,_Stats,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostScoreRequest* Make(FString _TournamentId, double _Score, int64 _PlayerId, FOptionalBool _bIncrement, FOptionalString _ContentId, FOptionalMapOfString _Stats, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostScoreSuccess, FBeamRequestContext, Context, UPostScoreRequest*, Request, UEmptyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostScoreError, FBeamRequestContext, Context, UPostScoreRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostScoreComplete, FBeamRequestContext, Context, UPostScoreRequest*, Request);

using FPostScoreFullResponse = FBeamFullResponse<UPostScoreRequest*, UEmptyResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostScoreFullResponse, FPostScoreFullResponse);
