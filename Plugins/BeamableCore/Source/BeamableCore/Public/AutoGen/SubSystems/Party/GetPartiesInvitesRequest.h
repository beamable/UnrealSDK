
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/PartyInvitesForPlayerResponse.h"

#include "GetPartiesInvitesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetPartiesInvitesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetPartiesInvitesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make GetPartiesInvites",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetPartiesInvitesRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPartiesInvitesSuccess, FBeamRequestContext, Context, UGetPartiesInvitesRequest*, Request, UPartyInvitesForPlayerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetPartiesInvitesError, FBeamRequestContext, Context, UGetPartiesInvitesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetPartiesInvitesComplete, FBeamRequestContext, Context, UGetPartiesInvitesRequest*, Request);

using FGetPartiesInvitesFullResponse = FBeamFullResponse<UGetPartiesInvitesRequest*, UPartyInvitesForPlayerResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetPartiesInvitesFullResponse, FGetPartiesInvitesFullResponse);
