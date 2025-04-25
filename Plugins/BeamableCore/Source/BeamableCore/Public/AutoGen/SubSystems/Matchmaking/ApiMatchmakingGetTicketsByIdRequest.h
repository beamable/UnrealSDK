
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Ticket.h"

#include "ApiMatchmakingGetTicketsByIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiMatchmakingGetTicketsByIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UApiMatchmakingGetTicketsByIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Make ApiMatchmakingGetTicketsById",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiMatchmakingGetTicketsByIdRequest* Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetTicketsByIdSuccess, FBeamRequestContext, Context, UApiMatchmakingGetTicketsByIdRequest*, Request, UTicket*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetTicketsByIdError, FBeamRequestContext, Context, UApiMatchmakingGetTicketsByIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiMatchmakingGetTicketsByIdComplete, FBeamRequestContext, Context, UApiMatchmakingGetTicketsByIdRequest*, Request);

using FApiMatchmakingGetTicketsByIdFullResponse = FBeamFullResponse<UApiMatchmakingGetTicketsByIdRequest*, UTicket*>;
DECLARE_DELEGATE_OneParam(FOnApiMatchmakingGetTicketsByIdFullResponse, FApiMatchmakingGetTicketsByIdFullResponse);
