
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/TicketQueryResponse.h"

#include "GetMatchmakingTicketsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetMatchmakingTicketsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetMatchmakingTicketsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|PlayerTicket|Utils|Make/Break", DisplayName="Make GetMatchmakingTickets",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetMatchmakingTicketsRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMatchmakingTicketsSuccess, FBeamRequestContext, Context, UGetMatchmakingTicketsRequest*, Request, UTicketQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetMatchmakingTicketsError, FBeamRequestContext, Context, UGetMatchmakingTicketsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetMatchmakingTicketsComplete, FBeamRequestContext, Context, UGetMatchmakingTicketsRequest*, Request);

using FGetMatchmakingTicketsFullResponse = FBeamFullResponse<UGetMatchmakingTicketsRequest*, UTicketQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetMatchmakingTicketsFullResponse, FGetMatchmakingTicketsFullResponse);
