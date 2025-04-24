
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/OnlineStatusQuery.h"
#include "BeamableCore/Public/AutoGen/PlayersStatusResponse.h"

#include "PostQueryRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostQueryRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UOnlineStatusQuery* Body = {};

	// Beam Base Request Declaration
	UPostQueryRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Presence|Utils|Make/Break", DisplayName="Make PostQuery",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_PlayerIds,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostQueryRequest* Make(FOptionalArrayOfString _PlayerIds, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostQuerySuccess, FBeamRequestContext, Context, UPostQueryRequest*, Request, UPlayersStatusResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostQueryError, FBeamRequestContext, Context, UPostQueryRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostQueryComplete, FBeamRequestContext, Context, UPostQueryRequest*, Request);

using FPostQueryFullResponse = FBeamFullResponse<UPostQueryRequest*, UPlayersStatusResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostQueryFullResponse, FPostQueryFullResponse);
