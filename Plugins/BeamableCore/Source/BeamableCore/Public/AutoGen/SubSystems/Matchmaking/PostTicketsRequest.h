
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/TicketReservationRequestBody.h"
#include "BeamableCore/Public/AutoGen/TicketReservationResponse.h"

#include "PostTicketsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostTicketsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UTicketReservationRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostTicketsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Make PostTickets",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bWatchOnlineStatus,_MaxWaitDurationSecs,_Team,_Players,_MatchTypes,_Tags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostTicketsRequest* Make(FOptionalBool _bWatchOnlineStatus, FOptionalInt32 _MaxWaitDurationSecs, FOptionalString _Team, FOptionalArrayOfBeamGamerTag _Players, FOptionalArrayOfBeamContentId _MatchTypes, FOptionalArrayOfBeamTag _Tags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTicketsSuccess, FBeamRequestContext, Context, UPostTicketsRequest*, Request, UTicketReservationResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostTicketsError, FBeamRequestContext, Context, UPostTicketsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostTicketsComplete, FBeamRequestContext, Context, UPostTicketsRequest*, Request);

using FPostTicketsFullResponse = FBeamFullResponse<UPostTicketsRequest*, UTicketReservationResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostTicketsFullResponse, FPostTicketsFullResponse);
