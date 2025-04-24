
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/ApiPlayersPartiesDeletePlayerPartyResponse.h"

#include "DeletePartiesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeletePartiesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeletePartiesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Party|Utils|Make/Break", DisplayName="Make DeleteParties",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeletePartiesRequest* Make(FString _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeletePartiesSuccess, FBeamRequestContext, Context, UDeletePartiesRequest*, Request, UApiPlayersPartiesDeletePlayerPartyResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeletePartiesError, FBeamRequestContext, Context, UDeletePartiesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeletePartiesComplete, FBeamRequestContext, Context, UDeletePartiesRequest*, Request);

using FDeletePartiesFullResponse = FBeamFullResponse<UDeletePartiesRequest*, UApiPlayersPartiesDeletePlayerPartyResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeletePartiesFullResponse, FDeletePartiesFullResponse);
