
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/JoinRequestBody.h"
#include "BeamableCore/Public/AutoGen/PlayerStatus.h"

#include "PostTournamentsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTournamentsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UJoinRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTournamentsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Tournaments|Utils|Make/Break", DisplayName="Make PostTournaments",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ContentId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTournamentsRequest* Make(FString _TournamentId, FOptionalString _ContentId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTournamentsSuccess, FBeamRequestContext, Context, UPostTournamentsRequest*, Request, UPlayerStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTournamentsError, FBeamRequestContext, Context, UPostTournamentsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTournamentsComplete, FBeamRequestContext, Context, UPostTournamentsRequest*, Request);

using FPostTournamentsFullResponse = FBeamFullResponse<UPostTournamentsRequest*, UPlayerStatus*>;
DECLARE_DELEGATE_OneParam(FOnPostTournamentsFullResponse, FPostTournamentsFullResponse);
