
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/Ticket.h"

#include "GetTicketsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetTicketsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetTicketsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Matchmaking", DisplayName="Beam - Make GetTickets",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetTicketsRequest* Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTicketsSuccess, FBeamRequestContext, Context, UGetTicketsRequest*, Request, UTicket*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetTicketsError, FBeamRequestContext, Context, UGetTicketsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetTicketsComplete, FBeamRequestContext, Context, UGetTicketsRequest*, Request);

using FGetTicketsFullResponse = FBeamFullResponse<UGetTicketsRequest*, UTicket*>;
DECLARE_DELEGATE_OneParam(FOnGetTicketsFullResponse, FGetTicketsFullResponse);
