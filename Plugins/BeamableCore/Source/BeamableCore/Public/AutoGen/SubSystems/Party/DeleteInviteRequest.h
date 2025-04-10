
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CancelInviteToParty.h"
#include "BeamableCore/Public/AutoGen/ApiPartiesInviteDeletePartyResponse.h"

#include "DeleteInviteRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteInviteRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FGuid Id = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCancelInviteToParty* Body = {};

	// Beam Base Request Declaration
	UDeleteInviteRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make DeleteInvite",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerId,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteInviteRequest* Make(FGuid _Id, FOptionalBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteInviteSuccess, FBeamRequestContext, Context, UDeleteInviteRequest*, Request, UApiPartiesInviteDeletePartyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteInviteError, FBeamRequestContext, Context, UDeleteInviteRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteInviteComplete, FBeamRequestContext, Context, UDeleteInviteRequest*, Request);

using FDeleteInviteFullResponse = FBeamFullResponse<UDeleteInviteRequest*, UApiPartiesInviteDeletePartyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteInviteFullResponse, FDeleteInviteFullResponse);
