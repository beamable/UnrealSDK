
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponse.h"

#include "GetPartyInvitesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPartyInvitesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetPartyInvitesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make GetPartyInvites",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetPartyInvitesRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPartyInvitesSuccess, FBeamRequestContext, Context, UGetPartyInvitesRequest*, Request, UPartyInvitesForPlayerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPartyInvitesError, FBeamRequestContext, Context, UGetPartyInvitesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPartyInvitesComplete, FBeamRequestContext, Context, UGetPartyInvitesRequest*, Request);

using FGetPartyInvitesFullResponse = FBeamFullResponse<UGetPartyInvitesRequest*, UPartyInvitesForPlayerResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetPartyInvitesFullResponse, FGetPartyInvitesFullResponse);
