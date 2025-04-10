
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/TicketQueryResponse.h"

#include "ApiMatchmakingGetTicketsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UApiMatchmakingGetTicketsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players", Category="Beam")
	FOptionalArrayOfBeamGamerTag Players = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Include Inactive", Category="Beam")
	FOptionalBool bIncludeInactive = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Skip", Category="Beam")
	FOptionalInt32 Skip = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UApiMatchmakingGetTicketsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Matchmaking|Utils|Make/Break", DisplayName="Make ApiMatchmakingGetTickets",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Players,_bIncludeInactive,_Skip,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UApiMatchmakingGetTicketsRequest* Make(FOptionalArrayOfBeamGamerTag _Players, FOptionalBool _bIncludeInactive, FOptionalInt32 _Skip, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetTicketsSuccess, FBeamRequestContext, Context, UApiMatchmakingGetTicketsRequest*, Request, UTicketQueryResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiMatchmakingGetTicketsError, FBeamRequestContext, Context, UApiMatchmakingGetTicketsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnApiMatchmakingGetTicketsComplete, FBeamRequestContext, Context, UApiMatchmakingGetTicketsRequest*, Request);

using FApiMatchmakingGetTicketsFullResponse = FBeamFullResponse<UApiMatchmakingGetTicketsRequest*, UTicketQueryResponse*>;
DECLARE_DELEGATE_OneParam(FOnApiMatchmakingGetTicketsFullResponse, FApiMatchmakingGetTicketsFullResponse);
