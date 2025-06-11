
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ApiMatchmakingTicketsDeleteTicketResponse.h"

#include "DeleteTicketsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteTicketsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteTicketsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Make DeleteTickets",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteTicketsRequest* Make(FGuid _Id, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTicketsSuccess, FBeamRequestContext, Context, UDeleteTicketsRequest*, Request, UApiMatchmakingTicketsDeleteTicketResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteTicketsError, FBeamRequestContext, Context, UDeleteTicketsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteTicketsComplete, FBeamRequestContext, Context, UDeleteTicketsRequest*, Request);

using FDeleteTicketsFullResponse = FBeamFullResponse<UDeleteTicketsRequest*, UApiMatchmakingTicketsDeleteTicketResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteTicketsFullResponse, FDeleteTicketsFullResponse);
